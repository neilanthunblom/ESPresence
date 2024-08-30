# ESPresense Configuration

## Overview

This is a short guide that explains how to configure ESPresense to track the presence of an Apple Watch using its IRK and publish it to the MQTT Broker. Additionally it expains how to allow HomeAssistant to access the presence of the device from the MQTT broker.

## Prerequisites

1. A MQTT broker running on the network
2. ESPresense firmware flashed to an ESP32 device
3. ESP32 device connected to the network
4. ESP32 device configured to connect to an MQTT broker
5. Home Assistant instance running
6. Home Assistant configured to connect to the MQTT broker (using the MQTT integration)
7. A Mac with the logged into the same iCloud account as the Apple Watch

## Step 1: Find The IRKS of the devices to be tracked
 
### Apple Watch


#### Step 1: Find the Bluetooth Address of the Apple Watch

1. On Apple Watch, go to Settings > General > About
2. Scroll down to find the `Bluetooth` address and note it down.

#### Step 2: Find the IRK of the Apple Watch

1. Open Keychain Access On Mac ( `Cmd + Space` and search for `Keychain Access`)
2. Got to iCloud Keychain
3. Search for `Bluetooth`
4. Click through the entries until you find the one with the Bluetooth address of the Apple Watch
5. Check the show password box and enter your Mac password
6. Copy the XML from the `password` field
7. Convert the password to an IRK by opening the `DecodeAppleIRK.html` file in a browser and pasting the XML into the input field.
8. Copy the IRK value from the output field

## Step 2: Configure ESPresense to track the device

NOTE: This is assuming that the ESPresense firmware has already been flashed to the ESP32 and the device is connected to the network and configured to connect to the MQTT broker.

In order to track the device and publish its presence to the MQTT broker, the IRK of the device must be added to the ESPresense configuration. With devices other than the Apple Watch/iPhone you may be able to use the device's Bluetooth MAC address instead of the IRK, but YMMV.

1. Navigate to the device's web interface using its IP address
2. Scroll down to the `Scanning` section
3. Add the IRKs of the devices to be tracked in the `Known BLE identity resolving keys` field
4. Click `Save` and then `Restart`

## Step 3: Home Assistant Configuration

Inorder to access the room which the device is in from mqtt, you need to manually add the sensor to the `configuration.yaml` file.

1. SSH into the Home Assistant instance and navigate to the `config` directory
2. Enter the following command to add the IRK to the homeassistant configuration

```bash
vim configuration.yaml
```

3. Add the following configuration to the `configuration.yaml` file

```yaml
sensor:
  - platform: mqtt_room
    device_id: "irk:{YOUR_IRK}"
    name: 'ESP Apple Watch'
    state_topic: 'espresense/devices/irk:{YOUR_IRK}'
    timeout: 10
    away_timeout: 120
```

4. Save the file

```vim
:wq
```

5. Restart Home Assistant

```bash
sudo systemctl restart homeassistant
```