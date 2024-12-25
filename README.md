# 低功耗Lora自组网络监测系统
目前暂时上传项目说明文档，源代码还需要完善，敬请期待！

**GitHub的MARKDOWN语言似乎跟Obsidian的MARKDOWN有区别** 图片大小暂时这样！
## 系统总体方案设计
![Image 1](https://github.com/LB1222/LPC-LoRaN-MonitoringSystem/raw/Images/图片1.png)
## LoRa节点硬件设计框图
![image](https://github.com/user-attachments/assets/8f102672-e017-464b-850f-83c94b68a914)

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









