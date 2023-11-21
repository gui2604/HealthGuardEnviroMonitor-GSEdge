#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <DHTesp.h>
// Configurações de WiFi
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";  // Substitua pelo sua senha                                          
// Configurações de MQTT
const char *BROKER_MQTT = "broker.hivemq.com";
const int BROKER_PORT = 1883;
const char *ID_MQTT = "GBS_mqtt";
const char *TOPIC_PUBLISH_TEMPHUMI = "FIAP/edgeGS/HealthGuardEnviroMonitor/TempHumi";
const char *TOPIC_PUBLISH_LUMINOSITY = "FIAP/edgeGS/HealthGuardEnviroMonitor/Luminosity";
const char *TOPIC_SUBSCRIBE_ALERT = "FIAP/edgeGS/HealthGuardEnviroMonitor/Alert";
// Configurações de Hardware
#define LDR_PIN 34
#define DHT_PIN 12
#define RED_LED 27
#define YELLOW_LED 26
#define GREEN_LED 25
#define PUBLISH_DELAY 2000
// Variáveis globais
WiFiClient espClient;
PubSubClient MQTT(espClient);
DHTesp dht;
unsigned long publishUpdate = 0;
TempAndHumidity dhtValues;
const int TAMANHO = 200;
String flag;
// Protótipos de funções
void initWiFi();
void initMQTT();
void callbackMQTT(char *topic, byte *payload, unsigned int length);
void reconnectMQTT();
void reconnectWiFi();
void checkWiFIAndMQTT();
void updateSensorValues() {
  dhtValues = dht.getTempAndHumidity();
}
// *************************************************************************************
// INÍCIO CONFIGS ESP32
// *************************************************************************************
void initWiFi() {
  Serial.print("Conectando com a rede: ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado com sucesso: ");
  Serial.println(SSID);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(callbackMQTT);
}

void callbackMQTT(char *topic, byte *payload, unsigned int length) {
  String msg = String((char*)payload).substring(0, length);
  Serial.printf("Mensagem recebida via MQTT: %s do tópico: %s\n", msg.c_str(), topic);
}

void reconnectMQTT() {
  while (!MQTT.connected()) {
    Serial.print("Tentando conectar com o Broker MQTT: ");
    Serial.println(BROKER_MQTT);
    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado ao broker MQTT!");
      //entrar no mqtt
    } else {
      Serial.println("Falha na conexão com MQTT. Tentando novamente em 2 segundos.");
      delay(2000);
    }
  }
}

void checkWiFIAndMQTT() {
  if (WiFi.status() != WL_CONNECTED) reconnectWiFi();
  if (!MQTT.connected()) reconnectMQTT();
}

void reconnectWiFi(void) {
  if (WiFi.status() == WL_CONNECTED)
    return;
  WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Wifi conectado com sucesso");
  Serial.print(SSID);
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
}
// *************************************************************************************
// FIM CONFIGS ESP32
// *************************************************************************************

void setup() {
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  dht.setup(DHT_PIN, DHTesp::DHT22);
  initWiFi();
  initMQTT();
}

void loop() {
  checkWiFIAndMQTT();
  MQTT.loop();
  updateSensorValues();
  int lightValue = analogRead(LDR_PIN);

  if(dhtValues.temperature > 30 && dhtValues.humidity > 70 && lightValue < 500){
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    flag = "Cuidado, quarto muito quente, úmido e escuro alerta de proliferação de fungos e bactérias!";
  }else if(dhtValues.humidity < 20 && dhtValues.temperature > 25){
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    flag = "Cômodo muito seco e quente, lembre-se de se hidratar!";
  }else if(lightValue > 3000){
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    flag = "Luminosidade do cômodo muito intensa! Evite exposição prolongada à luz. Utilizar óculos de sol.";
  }else if(dhtValues.humidity < 20 && dhtValues.temperature < 15){
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    flag = "Quarto muito seco e muito frio. Cuidado com redução de imunidade, risco de resfriado e vírus da gripe!";
  }else{
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    flag = "Quarto com boa salubridade!";
  }
  delay(2000);
  if ((millis() - publishUpdate) >= PUBLISH_DELAY) {
    publishUpdate = millis();
    updateSensorValues();
    if (!isnan(dhtValues.temperature) && !isnan(dhtValues.humidity)) {
      StaticJsonDocument<TAMANHO> dhtDoc;
      dhtDoc["temperatura"] = dhtValues.temperature;
      dhtDoc["umidade"] = dhtValues.humidity;
      char tempHumiBuffer[TAMANHO];
      serializeJson(dhtDoc, tempHumiBuffer);
      MQTT.publish(TOPIC_PUBLISH_TEMPHUMI, tempHumiBuffer);
      Serial.println(tempHumiBuffer);
    }
    if (!isnan(lightValue)) {
    StaticJsonDocument<TAMANHO> lightDoc;
    lightDoc["luminosidade"] = lightValue;
    char lightBuffer[TAMANHO];
    serializeJson(lightDoc, lightBuffer);
    MQTT.publish(TOPIC_PUBLISH_LUMINOSITY, lightBuffer);
    Serial.println(lightBuffer);
    }
    if (flag) {
      StaticJsonDocument<TAMANHO> msgDoc;
      msgDoc["alerta"] = flag;
      char msgBuffer[TAMANHO];
      serializeJson(msgDoc, msgBuffer);
      MQTT.publish(TOPIC_SUBSCRIBE_ALERT, msgBuffer);
      Serial.println(msgBuffer);
    }
  }
}