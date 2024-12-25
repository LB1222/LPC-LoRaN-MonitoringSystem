--- 模块功能：MQTT客户端数据接收处理
-- @author openLuat
-- @module mqtt.mqttInMsg
-- @license MIT
-- @copyright openLuat
-- @release 2018.03.28

module(...,package.seeall)


pmd.ldoset(15,pmd.LDO_VLCD)

local led_pin = pins.setup(pio.P0_4, 0)
local led_pin_state=0;

--- MQTT客户端数据接收处理
-- @param mqttClient，MQTT客户端对象
-- @return 处理成功返回true，处理出错返回false
-- @usage mqttInMsg.proc(mqttClient)
function proc(mqttClient)
    local result,data
    while true do
        result,data = mqttClient:receive(10,"APP_SOCKET_SEND_DATA")
        --接收到数据
        if result then
            log.info("mqttInMsg.proc",data.topic,string.toHex(data.payload))
            log.info("mqttInMsg.proc",data.topic, data.payload)

            if  data.payload == "{\"data\":\"switch\",\"bit\":\"1\",\"status\":\"1\"}" then
                led_pin(1);led_pin_state=1;--控制LED
                sys.publish("sys_publish_mqtt_send",data.payload)--发送消息通知
            elseif  data.payload == "{\"data\":\"switch\",\"bit\":\"1\",\"status\":\"0\"}" then
                led_pin(0);led_pin_state=0;--控制LED
                sys.publish("sys_publish_mqtt_send",data.payload)--发送消息通知
            elseif data.payload == "{\"data\":\"DeviceState\"}" then
                local msg = "{\"data\":\"switch\",\"bit\":\"1\",\"status\":\""..led_pin_state.."\"}"
                sys.publish("sys_publish_mqtt_send",msg)--发送消息通知
            end
        else
            break
        end
    end
	
    return result or data=="timeout" or data=="APP_SOCKET_SEND_DATA"
end


