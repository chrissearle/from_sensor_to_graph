# Demo Setup

Note that we use the default/standard users and passwords for most of this setup. It goes without saying that this is not good for a real installation :)

## Network

For this demo I used an old ADSL modem/router I had lying around. It was configured to provide DHCP over both wireless and wired networks.

| Setting                             | Value            |
| ----------------------------------- | ---------------- |
| Network                             | 192.168.27.0/24  |
| Gateway (but no upstream connected) | 192.168.27.1     |
| SSID                                | DEMO             |
| Wifi password (WPA)                 | ohdo1EerauGh1ooX |
| Router login                        | admin/password   |


## Pi

The main server for this demo was a raspberry pi 3b+.

Before the demo this was set to DHCP while doing the setup, for the demo it will get the fixed IP 192.168.27.2

### Info

| Service            | Username | Password  |
| ------------------ | -------- | --------- |
| SSH                | pi       | raspberry |
| Node-RED dashboard | chris    | chris     |
| Node-RED admin     | admin    | password  |
| Grafana            | admin    | password  |


Node-RED: [http://192.168.27.2:1880/](http://192.168.27.2:1880/)

Grafana: [http://192.168.27.2:3000/](http://192.168.27.2:3000/)

## Installation

### Raspbian

Start by installing the latest version of raspbian lite (in this case 2018-11-13-raspbian-stretch-lite) onto a blank micro SD card.

Then create an empty file on the root of the card called `ssh`

Put the card into the PI, connect to ethernet and power on.

Login over SSH as the user `pi` (default password `raspberry`)

Update the current packages

    sudo apt update
    sudo apt upgrade
    sudo reboot

### The Script

This handles installing Node-RED, InfluxDB, Grafana and more. 

SSH in (as `pi`) and get the script and run it

When prompted - make sure that only the first Node/Node-RED choice is selected and that Grafana/influx is added:

    wget --no-check-certificate  https://bitbucket.org/api/2.0/snippets/scargill/qexexb/master/files/script.sh
    bash script.sh
    sudo reboot

### MQTT

Set up the arduino user

    sudo mosquitto_passwd  passwords arduino

When prompted - set the password to arduino

Do the same with user nodered password nodered

Then restart mosquitto

    sudo /etc/init.d/mosquitto restart

### InfluxDB

First we need to enable the http endpoint.

Edit `/etc/influxdb/influxdb.conf` and find the [http] section

Uncomment the lines

- enabled = true
- bind-address = ":8086"

Save the file.

Now we need to create an admin user.

Run `influx` then enter

    CREATE USER "pi" WITH PASSWORD 'raspberry' WITH ALL PRIVILEGES

    CREATE DATABASE dht

### Node-RED

For some users the script is not installing the InfluxDB node into Node-RED.

Open the Node-RED interface, login and then choose `manage palatte > install`, search fornode-red-contrib-influxdb and install it.

# Resources

* Video: https://www.youtube.com/watch?v=JdV4x925au0
* The script: https://tech.scargill.net/the-script/
