# From Sensor to Graph

---

## DHT22

![left](dht22.jpg)

- Sensor with both temperature and humidty
- Three pins to connect to arduino
  - power - ground - data

---

## Arduino

![right](d1mini.jpg)

- Arduino
- ESP8266/ESP32

---

## MQTT

- Simple publish/subscribe server designed for IoT usage
- Publish bytes of data to a topic
- Subscribe to the topic and get sent bytes of data

---

## Arduino coding

Arduino is basically C++ with some extras

---

### DHT22

```c++
// Add sensor on arduino pin D1
DHT dht(D1, DHT22);

float temperature = dht.readTemperature();
float humidity = dht.readHumidity();
```

---

### MQTT

```c++
// Create and configure
PubSubClient client(wifiClient);
client.setServer(MQTT_SERVER, 1883);

// Connect
client.connect(CLIENT_NAME, MQTT_USER, MQTT_PASSWORD);

// Publish
client.publish(MQTT_TOPIC, message);
```

---

## Demo

Arduino Serial Console

---

## Node-RED

TODO - Screenshot

> Node-RED provides a browser-based flow editor that makes it easy to wire together flows using the wide range of nodes in the palette.[^1]

[^1]: [https://nodered.org/](https://nodered.org/)

---

### Demo

Node-RED pipelines - debug node

---

## Influx DB

> InfluxDB is an open-source time series database [^2]

[^2]: [https://en.wikipedia.org/wiki/InfluxDB](https://en.wikipedia.org/wiki/InfluxDB)

---

### Demo

InfluxDB data

---

## Grafana

> Grafana is an open-source, general purpose dashboard and graph composer, which runs as a web application [^3]

[^3]: [https://wiki.archlinux.org/index.php/Grafana](https://wiki.archlinux.org/index.php/Grafana)

---

### Demo

Sensor data on Grafana graph

---

## Links

- Video from Andreas Spiess:

  - https://www.youtube.com/watch?v=JdV4x925au0

- The installation script:
  - https://tech.scargill.net/the-script/
