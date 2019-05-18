# Cheat Sheet

## Setup

Set the date and time at boot of the pi - it's not on the internet to see a date server

    sudo date -s "Thu May 23 hh:mm:ss CET 2019"

Clear out any measurement

    influx
    use dht
    drop measurement demo

## Influx

> show databases;

> use dht

> show measurements

> select * from demo

> select * from demo where "location" = 'DemoSensor'

> select * from demo where time > '2019-05-23  12:00:00'

> select mean("temperature") from demo where time > '2019-05-23  12:00:00' group by time(1h)

## Grafana

