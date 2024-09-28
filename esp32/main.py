'''
访问网站端口为5000,程序打印出ip地址后，在ip地址加上端口即可访问
如 192.168.31.233:5000
microdot.py和asynic文件夹放入到esp32根目录下
'''
from microdot import Microdot,send_file
import time,network
import camera
from machine import reset,UART
camera_flip = False
'''
初始化摄像头
'''
try:
    camera.init(0, format=camera.JPEG, fb_location=camera.PSRAM)
except OSError:
    camera.deinit()
    camera.init(0, format=camera.JPEG, fb_location=camera.PSRAM)
camera.flip(camera_flip)
#camera.framesize(camera.FRAME_QVGA)
camera.quality(20) #设置摄像头质量，10为最高
print("Camera ready")
uart1 = UART(1,baudrate = 9600,tx = 12,rx = 13)
uart1.write("Camera ready") # 初始化成功发送至机器人
'''
连接网络
'''
def do_connect():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        print('正在连接网络...')
        wlan.connect('填入账号','填入密码')
    print('network config:', wlan.ifconfig())
    return wlan.ifconfig()[0]
#time.sleep(5)  延时的作用是防止下次网络连接报错，可不用
do_connect()
app = Microdot()
'''
以下网页接受代码参考B站Up主 red润老师
Microdot()框架的使用可以在https://juejin.cn/post/7246340035065249829#heading-6 查看
目前Microdot已更新，相对于介绍内容更强大
'''
@app.route('/')
async def index(request):
    return send_file('/index.html')
@app.get('/go')
async def index(request):
    uart1.write("go")
    print("go")
    return "前进"
@app.get('/back')
async def index(request):
    uart1.write("back")
    print("back")
    return "后退"
@app.get('/left')
async def index(request):
    uart1.write("left")
    print("left")
    return "左转"
@app.get('/right')
async def index(request):
    uart1.write("right")
    print("right")
    return "右转"
@app.get('/turn')
async def index(request):
    global camera_flip
    uart1.write("turn")
    camera_flip = not camera_flip
    camera.flip(camera_flip)
    print("turn")
    return "翻转"
'''
网页图传
代码来源于B站up主"F的工作室"老师
'''
@app.route('/video_feed')
async def video_feed(request):
    def stream():
        yield b'--frame\r\n'
        while True:
            frame = camera.capture()
            yield b'Content-Type: image/jpeg\r\n\r\n' + frame + \
                b'\r\n--frame\r\n'

    return stream(), 200, {'Content-Type':
                           'multipart/x-mixed-replace; boundary=frame'}



app.run()

