Q：因为非root用户无法获得读取串口的数据
    临时：sudo chmod 777 /dev/ttyUSB0
    永久：sudo usermod -aG dialout 【当前用户名】



KnowHow:
1. 如何获取本地->target或target->本地的报文信息？
    A：使用Fiddler软件，打开软件后在右侧的工具栏依次选择Inspectors->Raw则可看到报文信息。