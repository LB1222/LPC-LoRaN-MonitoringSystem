--- 模块功能：蓝牙功能测试
-- @author openLuat
-- @module bluetooth.slave
-- @license MIT
-- @copyright openLuat
-- @release 2020.09.27
-- @注意 需要使用core(Luat_VXXXX_RDA8910_BT_FLOAT)版本
module(..., package.seeall)

require "wifiScan"
require "uart"

-- 初始化串口1
uart.setup(1, 115200, 8, uart.PAR_NONE, uart.STOP_1)

local function init()
    log.info("bt", "init")
    rtos.on(rtos.MSG_BLUETOOTH, function(msg)
        if msg.event == btcore.MSG_OPEN_CNF then
            -- 蓝牙打开成功
            sys.publish("BLE_OPEN")
        elseif msg.event == btcore.MSG_CLOSE_CNF then
            -- 蓝牙关闭成功
        elseif msg.event == btcore.MSG_BLE_CONNECT_IND then
            -- 蓝牙连接结果
            sys.publish("BT_CONNECT_IND", {["handle"] = msg.handle, ["result"] = msg.result})
        elseif msg.event == btcore.MSG_BLE_DISCONNECT_IND then
            -- 蓝牙断开连接
        elseif msg.event == btcore.MSG_BLE_DATA_IND then
            -- 蓝牙收到消息
           log.info("bt.data_ind", msg.result)
           uart.write(1, tostring(msg.result))
          -- uart.write(1, 0xAA, 0xAA, 0xAA)
            -- 这里可以添加处理接收到数据的逻辑
           -- processReceivedData(msg.result)
        end
    end)
    
end

-- 处理接收到的数据
-- local function processReceivedData(data)
--     -- 在这里添加你的逻辑，例如更新页面显示等
--      -- 打印接收到的原始数据
--      log.info("Received raw data:", data)

--      -- 在这里添加解析和处理数据的逻辑
--      -- 下面是一个示例，将接收到的数据转换为字符串并打印
--      local receivedString = string.fromHex(data)
--      log.info("Received data as string:", receivedString)
--     -- 下面是示例代码，将接收到的数据通过串口1发送字节0xAA、0xAA、0xAA
   
-- end


local function poweron()
    log.info("bt", "poweron")
    btcore.open(0) -- 打开蓝牙从模式
    _, result = sys.waitUntil("BLE_OPEN", 5000) -- 等待蓝牙打开成功
end

local function service(uuid, struct)
    btcore.addservice(uuid) -- 添加服务
    for i = 1, #struct do
        btcore.addcharacteristic(struct[i][1], struct[i][2], struct[i][3]) -- 添加特征
        if type(struct[i][4]) == "table" then
            for j = 1, #struct[i][4] do
                btcore.adddescriptor(struct[i][4][j][1], struct[i][4][j][2])  -- 添加描述
            end
        end
    end
end

local function advertising()
    -- 设置广播数据，包括服务 UUID
    btcore.setadvdata(string.fromHex("02010604ff000203") .. "11" .. "07" .. "10" .. "00" .. "00" .. "10" .. "00" .. "80" .. "00" .. "80" .. "5F9B34FB")

    -- 添加你的服务和读特征
    local struct1 = {
        {0x1800, 0x2800, 0x0002},
        {0x2A00, 0x2A01, 0x0002, {{0x2901, "MyDeviceName"}}},
        -- 添加你的服务和读特征
        {0x1800, 0x2A00, 0x0002, {{0x2901, "READ_Characteristic"}}},
    }
    service(0x1800, struct1) -- 添加通用访问服务（Generic Access Service）

    local struct2 = {
        {0xfee0, 0x08, 0x0002},
        {0xfee2, 0x1c, 0x0003, {{0x2902, 0x0003}, {0x2901, "123456"}}}, -- {特征uuid, 特征属性, 特征权限, {特征描述uuid, 描述属性}}
    }
    service(0xfee0, struct2) -- 添加你的自定义服务（替换为你的服务 UUID）

    -- 打开广播
    btcore.advertising(1)
end


local function data_trans()
    _, bt_connect = sys.waitUntil("BT_CONNECT_IND")
    if bt_connect.result ~= 0 then -- 连接失败
        return false
    end

    while true do
        sys.wait(1000) -- 每隔1秒

        local dataToSend = "Temp:32.5c,Hum:50%,LT:88%,CO2:2000PPM" -- 2个字节的数据，可以根据需要修改

        log.info("bt.send_data", dataToSend)
        btcore.send(dataToSend, 0xfee2, bt_connect.handle) -- 发送数据(数据 对应特征uuid 连接句柄)
    end
end

-- 蓝牙wifi分时复用测试方法：
-- 1、测试wifi搜索热点功能
-- 2、打开蓝牙，配置为从模式；手机上可以安装一个app，连接模块蓝牙，向模块发送数据测试；
--    当手机app向模块发送5个字节的数据close时，模块会主动断开并且关闭蓝牙
-- 3、延时5秒钟，继续从第1步开始测试
sys.taskInit(function()
    init()
    poweron()
    advertising()
    data_trans()
end)




