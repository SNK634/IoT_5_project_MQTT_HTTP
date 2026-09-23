#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <ArduinoJson.h>

// =======================
// DHT SENSOR
// =======================

#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// =======================
// WIFI WOKWI
// =======================

const char *WIFI_SSID = "Wokwi-GUEST";
const char *WIFI_PASSWORD = "";

// =======================
// MQTT CONFIG
// =======================

const char *MQTT_SERVER = "broker.hivemq.com";
const int MQTT_PORT = 1883;

const char *MQTT_TOPIC =
    "esp32/dht11/data/tam";

// =======================
// HTTP CONFIG
// =======================

// URL hien tai cua localtunnel
// Them /data vi server nhan POST tai endpoint /data
const char *HTTP_SERVER_URL =
    "https://iot-5-project-mqtt-http-1.onrender.com/data";

// =======================
// OBJECT
// =======================

WiFiClient espClient;
PubSubClient mqttClient(espClient);

int sampleId = 1;

// =======================
// CONNECT WIFI
// =======================

void connectWiFi()
{
  Serial.print("Dang ket noi WiFi");

  WiFi.begin(
      WIFI_SSID,
      WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  Serial.println(
      "Da ket noi WiFi thanh cong");

  Serial.print(
      "IP: ");

  Serial.println(
      WiFi.localIP());
}

// =======================
// CONNECT MQTT
// =======================

void connectMQTT()
{
  while (!mqttClient.connected())
  {
    Serial.print(
        "Dang ket noi MQTT...");

    String clientId =
        "ESP32_TAM_" + String(random(1000, 9999));

    if (
        mqttClient.connect(
            clientId.c_str()))
    {
      Serial.println(
          "Thanh cong");
    }
    else
    {
      Serial.print(
          "That bai rc=");

      Serial.println(
          mqttClient.state());

      delay(2000);
    }
  }
}

// =======================
// CREATE JSON
// =======================

String createJsonData(
    int id,
    float temperature,
    float humidity,
    const char *protocol)
{
  StaticJsonDocument<256> doc;

  doc["sample_id"] = id;
  doc["temperature"] = temperature;
  doc["humidity"] = humidity;
  doc["protocol"] = protocol;
  doc["send_time"] = millis();

  String json;

  serializeJson(
      doc,
      json);

  return json;
}

// =======================
// SEND MQTT
// =======================

void sendMQTT(
    int id,
    float temperature,
    float humidity)
{
  String jsonData =
      createJsonData(
          id,
          temperature,
          humidity,
          "MQTT");

  unsigned long start =
      millis();

  bool result =
      mqttClient.publish(
          MQTT_TOPIC,
          jsonData.c_str());

  unsigned long end =
      millis();

  Serial.println();

  Serial.println(
      "========== MQTT ==========");

  Serial.println(
      jsonData);

  if (result)
  {
    Serial.println(
        "MQTT gui thanh cong");
  }
  else
  {
    Serial.println(
        "MQTT gui that bai");
  }

  Serial.print(
      "Thoi gian MQTT: ");

  Serial.print(
      end - start);

  Serial.println(
      " ms");
}

// =======================
// SEND HTTP
// =======================

void sendHTTP(
    int id,
    float temperature,
    float humidity)
{
  String jsonData =
      createJsonData(
          id,
          temperature,
          humidity,
          "HTTP");

  WiFiClientSecure secureClient;

  // Bo qua kiem tra chung chi HTTPS
  // Dung cho moi truong mo phong/demo
  secureClient.setInsecure();

  HTTPClient http;

  Serial.println();

  Serial.println(
      "========== HTTP ==========");

  unsigned long start =
      millis();

  if (
      http.begin(
          secureClient,
          HTTP_SERVER_URL))
  {
    http.addHeader(
        "Content-Type",
        "application/json");

    int responseCode =
        http.POST(
            jsonData);

    unsigned long end =
        millis();

    Serial.println(
        jsonData);

    Serial.print(
        "HTTP Response Code: ");

    Serial.println(
        responseCode);

    // Chi xem 2xx la gui thanh cong
    if (
        responseCode >= 200 &&
        responseCode < 300)
    {
      Serial.println(
          "HTTP gui thanh cong");

      String response =
          http.getString();

      Serial.print(
          "Server Response: ");

      Serial.println(
          response);
    }
    else
    {
      Serial.println(
          "HTTP gui that bai");
    }

    Serial.print(
        "Thoi gian HTTP: ");

    Serial.print(
        end - start);

    Serial.println(
        " ms");

    http.end();
  }
  else
  {
    Serial.println(
        "Khong mo duoc HTTP connection");
  }
}

// =======================
// SETUP
// =======================

void setup()
{
  Serial.begin(115200);

  delay(1000);

  Serial.println(
      "=== ESP32 BAT DAU ===");

  dht.begin();

  connectWiFi();

  mqttClient.setServer(
      MQTT_SERVER,
      MQTT_PORT);

  connectMQTT();
}

// =======================
// LOOP
// =======================

void loop()
{
  // Dam bao MQTT van ket noi
  if (!mqttClient.connected())
  {
    connectMQTT();
  }

  mqttClient.loop();

  // Doc cam bien
  float temperature =
      dht.readTemperature();

  float humidity =
      dht.readHumidity();

  // Kiem tra loi doc DHT22
  if (
      isnan(temperature) ||
      isnan(humidity))
  {
    Serial.println(
        "Loi doc cam bien DHT");

    delay(2000);

    return;
  }

  Serial.println();

  Serial.println(
      "==============================");

  Serial.print(
      "Sample ID: ");

  Serial.println(
      sampleId);

  Serial.print(
      "Nhiet do: ");

  Serial.print(
      temperature);

  Serial.println(
      " C");

  Serial.print(
      "Do am: ");

  Serial.print(
      humidity);

  Serial.println(
      " %");

  // =======================
  // GUI MQTT
  // =======================

  sendMQTT(
      sampleId,
      temperature,
      humidity);

  // =======================
  // GUI HTTP
  // =======================

  sendHTTP(
      sampleId,
      temperature,
      humidity);

  // Tang ma mau
  sampleId++;

  // Cho 5 giay truoc khi gui mau tiep theo
  delay(5000);
}