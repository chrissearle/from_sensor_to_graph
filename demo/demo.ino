
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <dht.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

WiFiClient wifiClient;
PubSubClient client(wifiClient);

long lastMsg = 0;
char msg[100];

dht DHT;

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

void read()
{
    int chk = DHT.read22(D1);

    switch (chk)
    {
    case DHTLIB_OK:
        Serial.print("OK,\t");
        break;
    case DHTLIB_ERROR_CHECKSUM:
        Serial.print("Checksum error,\t");
        break;
    case DHTLIB_ERROR_TIMEOUT:
        Serial.print("Time out error,\t");
        break;
    default:
        Serial.print("Unknown error,\t");
        break;
    }
}

void send()
{
  snprintf(msg, 100, "{ \"location\": \"DemoSensor\", \"temperature\": %f, \"humidity\": %f }",
    DHT.temperature, DHT.humidity);
    
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

  if (now - lastMsg > (10 * 1000))
  {
    lastMsg = now;
    read();
    send();
  }
}
