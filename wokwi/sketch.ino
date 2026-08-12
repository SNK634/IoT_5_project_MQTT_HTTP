#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <ArduinoJson.h>

#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

const char* MQTT_SERVER = "broker.hivemq.com";
const int MQTT_PORT = 1883;
const char* MQTT_TOPIC = "esp32/dht11/data/tam";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

int packetId = 1;

void connectWiFi() {
  Serial.print("Dang ket noi WiFi");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Da ket noi WiFi");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Dang ket noi MQTT...");

    String clientId = "ESP32_TAM_" + String(random(1000, 9999));

    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("Thanh cong");
    } else {
      Serial.print("That bai, rc=");
      Serial.println(mqttClient.state());
      delay(2000);
    }
  }
}

void sendMQTT(float temperature, float humidity) {
  StaticJsonDocument<200> doc;

  doc["packet_id"] = packetId;
  doc["temperature"] = temperature;
  doc["humidity"] = humidity;
  doc["protocol"] = "MQTT";
  doc["send_time"] = millis();

  char jsonBuffer[256];
  serializeJson(doc, jsonBuffer);

  unsigned long startTime = millis();
  bool result = mqttClient.publish(MQTT_TOPIC, jsonBuffer);
  unsigned long endTime = millis();

  Serial.println("===== MQTT DATA =====");
  Serial.print("Data: ");
  Serial.println(jsonBuffer);

  if (result) {
    Serial.println("MQTT gui thanh cong");
  } else {
    Serial.println("MQTT gui that bai");
  }

  Serial.print("Thoi gian gui MQTT: ");
  Serial.print(endTime - startTime);
  Serial.println(" ms");

  packetId++;
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  connectWiFi();

  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  connectMQTT();
}

void loop() {
  if (!mqttClient.connected()) {
    connectMQTT();
  }

  mqttClient.loop();

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Loi doc cam bien DHT");
    delay(2000);
    return;
  }

  Serial.print("Nhiet do: ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("Do am: ");
  Serial.print(humidity);
  Serial.println(" %");

  sendMQTT(temperature, humidity);

  delay(5000);
}