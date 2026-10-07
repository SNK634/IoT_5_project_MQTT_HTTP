#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

const char* MQTT_BROKER = "broker.hivemq.com";
const int MQTT_PORT = 1883;

const char* TOPIC_TEMPERATURE = "iot/demo/temperature";
const char* TOPIC_HUMIDITY = "iot/demo/humidity";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

int sampleId = 1;

void connectWiFi() {
  Serial.println("Dang ket noi WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi da ket noi");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.println("Dang ket noi MQTT Broker...");

    String clientId = "ESP32_DHT22_Wokwi_" + String(random(1000, 9999));

    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("MQTT da ket noi");
    } else {
      Serial.print("Ket noi MQTT that bai, rc=");
      Serial.println(mqttClient.state());
      Serial.println("Thu lai sau 2 giay...");
      delay(2000);
    }
  }
}

String getTemperatureAlert(float temperature) {
  if (temperature > 45) {
    return "CANH BAO NONG";
  }
  return "Binh thuong";
}

String getHumidityAlert(float humidity) {
  if (humidity < 50) {
    return "CANH BAO KHO";
  }
  return "Binh thuong";
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  connectWiFi();

  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);

  Serial.println("He thong ESP32 DHT22 MQTT da san sang");
}

void loop() {
  if (!mqttClient.connected()) {
    connectMQTT();
  }

  mqttClient.loop();

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Loi doc du lieu tu cam bien DHT22");
    delay(3000);
    return;
  }

  String temperatureAlert = getTemperatureAlert(temperature);
  String humidityAlert = getHumidityAlert(humidity);

  String temperatureMessage = "NHIET DO: " + String(temperature, 1) + " C | " + temperatureAlert + " | Mau: " + String(sampleId);
  String humidityMessage = "DO AM: " + String(humidity, 1) + " % | " + humidityAlert + " | Mau: " + String(sampleId);

  mqttClient.publish(TOPIC_TEMPERATURE, temperatureMessage.c_str());
  mqttClient.publish(TOPIC_HUMIDITY, humidityMessage.c_str());

  Serial.println("Da gui MQTT:");
  Serial.println(temperatureMessage);
  Serial.println(humidityMessage);
  Serial.println("-------------------------");

  sampleId++;

  delay(3000);
}