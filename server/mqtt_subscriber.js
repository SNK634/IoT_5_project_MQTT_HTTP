const mqtt = require("mqtt");

// =======================
// MQTT CONFIG
// =======================

const MQTT_SERVER = "mqtt://broker.hivemq.com";
const MQTT_TOPIC = "esp32/dht11/data/tam";

// =======================
// CONNECT MQTT
// =======================

const client = mqtt.connect(MQTT_SERVER);

client.on("connect", () => {
  console.log("Da ket noi MQTT Broker");

  client.subscribe(MQTT_TOPIC, (err) => {
    if (err) {
      console.log("Subscribe that bai");
      console.log(err);
      return;
    }

    console.log("Subscribe thanh cong");
    console.log("Topic:", MQTT_TOPIC);
    console.log("==============================");
  });
});

// =======================
// RECEIVE MESSAGE
// =======================

client.on("message", (topic, message) => {
  console.log();
  console.log("========== MQTT DATA ==========");
  console.log("Topic:", topic);

  const text = message.toString();

  console.log("Raw data:", text);

  try {
    const data = JSON.parse(text);

    console.log("Sample ID:", data.sample_id);
    console.log("Nhiet do:", data.temperature);
    console.log("Do am:", data.humidity);
    console.log("Protocol:", data.protocol);
    console.log("Send time:", data.send_time);
  } catch (error) {
    console.log("Khong parse duoc JSON");
  }

  console.log("==============================");
});

// =======================
// ERROR
// =======================

client.on("error", (error) => {
  console.log("MQTT Error:");
  console.log(error);
});