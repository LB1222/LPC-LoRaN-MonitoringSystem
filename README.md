
# 低功耗Lora自组网络监测系统

##
**有四个分支：**
**1. main**          该说明文档为最初版本，描述项目的相关功能不太完善。  
**2. Images**        图片/测试视频    
**3. PCB**           所有版本的LoRa节点和LoRa网关的PCB设计源文件（已验证），下载后使用立创EDA打开即可。  
                     BOM直接导出就行，有少数是自己画的封装。  
**4. code**          包含无人机、4G模组、微信小程序、节点和网关的代码。    
##
## 功能简介
森林防火是保护自然资源的需要，林区往往地形复杂，辽阔无垠，难以及时确定火灾发生的具体位置，   
每年维护林区安全需要花费大量人力物力，本文提出了一种基于LoRa自组网络小型消防监测系统，    
在无网络、无电路的地区也能够实时监控周围情况，花费较低的成本将能够稳定、高效的防护林区，精准掌控林区资源。   
首先，通过对LoRa节点的硬件设计分析，硬件上完成了电子开关、功耗监测设计以及对传感器低功耗选型，   
实现了电路PCB硬件上的低功耗设计。   
其次，软件上完成了对LoRa节点周围温度、湿度、光照强度、CO2浓度的定时采样以及对节点数据边缘化计算，   
当采样数据异常时将立即获取节点的经纬度、海拔高度并将所有数据通过LoRa模块无线传输LoRa网关；   
设计了私有组网字节通信协议，MCU休眠唤醒切换机制等降低软件功耗的方法。   
最后，上位机微信小程序上完成了节点数据可视化、GIS地图导航、BLE蓝牙近距离通信、无人机控制与接收采集图像等功能。   
此系统能够工作在不同的环境下，具有较好的应用前景。   

##
## 系统总体方案设计

<img src="https://github.com/LB1222/LPC-LoRaN-MonitoringSystem/raw/Images/图片1.png" width="500" height="400" />

##  LoRa节点硬件设计框图
<img src="https://github.com/LB1222/LPC-LoRaN-MonitoringSystem/raw/Images/图片2.png" width="500" height="400" />

##   LoRa网关硬件设计框图

<img src="https://github.com/LB1222/LPC-LoRaN-MonitoringSystem/raw/Images/图片3.png" width="500" height="400" />

### LoRa节点PCB尺寸为长77.4mm、宽54.6mm，顶层主要作为MCU、传感器模块的搭载区域，底层为GPS模块及通信模块。
<img src="https://github.com/LB1222/LPC-LoRaN-MonitoringSystem/raw/Images/图片4.png" width="450" height="300" />

### LoRa网关PCB板子尺寸为长97.9mm、宽56.5mm。顶层主要作为MCU、BlE蓝牙5.0音频报警器和OLED显示屏模块的搭载区域，底层通信模块。
<img src="https://github.com/LB1222/LPC-LoRaN-MonitoringSystem/raw/Images/图片5.png" width="450" height="300" />

## Lora节点实物展示
  正式板由4层板改为2层板，一是降低成本，二是打板速度更快。除了传感器使用排母，所有器件都是手搓，用 热台的速度会快些，但是元器件种类比较多，这块儿比较耽误时间。Lora节点板1.2所有功能全测暂时没有遇到问题，布线没有4层板漂亮。
   **部分0603的贴片可以换成0805的，MCU不建议用我这款**
   **CH583做主控会好很多，串口多1个，功耗更低**
![Engelbart|50](https://github.com/LB1222/-Lora-/assets/126633339/c29866b7-c6a0-4070-aa3e-788a7c527a2d)
![694a518a653c25b6004f019dfa1083d](https://github.com/LB1222/-Lora-/assets/126633339/60263a39-fed9-4b76-8f5e-f4e7e3a1c5f3)

## Lora网关实物展示
![7a296af19bac07903ce41ec1df438a8](https://github.com/LB1222/-Lora-/assets/126633339/a441b06f-aa81-4f70-a873-71dbfaafd18a)

可以看到有根飞线，因为原理图的LM2596S-ADJ芯片的feedback引脚画的时候相交了，没注意到！！！
![image](https://github.com/LB1222/-Lora-/assets/126633339/ec732df0-e005-43f9-a85b-400ea6b55d3f)

实际上是这样：

![image](https://github.com/LB1222/-Lora-/assets/126633339/1b4ae15a-6b54-4bff-8a56-410d768e1075)

Lora节点与Lora网关通信正常后，Lora网关的显示屏才会正常显示温湿度数据，播放音乐->其实是一个语音报警器。下面是一个简单的视频展示，完整的视频展示：无人机拍照、小程序数据可视化、GIS地图、异常报警展示等等吧，可以先看初版的说明文档，后面都会放上来。

https://youtu.be/Au_wNHMcgvk









