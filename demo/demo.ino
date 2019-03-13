#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

WiFiClient wifiClient;
PubSubClient client(wifiClient);

long lastMsg = 0;
char msg[100];

DHT dht(D1, DHT22);

const char *MQTT_SERVER = "192.168.27.2";
const char *MQTT_USER = "arduino";
const char *MQTT_PASSWORD = "arduino";
const char *MQTT_TOPIC = "demo/dht";

void setup()
{
  Serial.begin(115200);

  Serial.print("Connecting to WiFi");

  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");

  Serial.print("Configuring MQTT");
  client.setServer(MQTT_SERVER, 1883);
}

void send()
{
  snprintf(msg, 100, "{ \"location\": \"DemoSensor\", \"temperature\": %f, \"humidity\": %f }",
    dht.readTemperature(), dht.readHumidity());
    
  Serial.print("Publish message: ");
  Serial.println(msg);

  client.publish(MQTT_TOPIC, msg);
}

void reconnect()
{
  Serial.print("MQTT not connected - reconnect");

  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("DemoClient", MQTT_USER, MQTT_PASSWORD))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }

  client.loop();

  long now = millis();

  if (now - lastMsg > (60 * 1000))
  {
    lastMsg = now;
    send();
  }
}
