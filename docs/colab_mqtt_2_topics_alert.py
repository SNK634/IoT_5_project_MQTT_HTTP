import paho.mqtt.client as mqtt
import time
import random

broker = "broker.hivemq.com"
port = 1883

topic_temperature = "iot/demo/temperature"
topic_humidity = "iot/demo/humidity"

client = mqtt.Client(client_id="Colab_MQTT_Alert_Tam")
client.connect(broker, port, keepalive=60)

print("Da ket noi MQTT Broker")
print("Topic nhiet do:", topic_temperature)
print("Topic do am:", topic_humidity)

sample_id = 1

while True:
    temperature = random.randint(30, 55)
    humidity = random.randint(30, 80)

    if temperature > 45:
        temperature_message = f"NHIET DO: {temperature} C | CANH BAO NONG | Mau: {sample_id}"
    else:
        temperature_message = f"NHIET DO: {temperature} C | Binh thuong | Mau: {sample_id}"

    if humidity < 50:
        humidity_message = f"DO AM: {humidity} % | CANH BAO KHO | Mau: {sample_id}"
    else:
        humidity_message = f"DO AM: {humidity} % | Binh thuong | Mau: {sample_id}"

    client.publish(topic_temperature, temperature_message)
    client.publish(topic_humidity, humidity_message)

    print("Da gui:", temperature_message)
    print("Da gui:", humidity_message)
    print("--------------------------------")

    sample_id += 1
    time.sleep(3)