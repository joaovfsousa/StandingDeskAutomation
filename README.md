# TiMotion TDH6 Alexa integration

Use an ESP32 to connect a TiMotion TDH6 desk controller to Alexa.

Current implementation adds each button as a device in Alexa.

## Desks that use this controller

- GenioDesk Pro

## How to replicate

### Materials

1. 1 ESP32
2. 1 Fenolite plate at lead 7x9cm
3. 4 OctoCouplers 4N25
4. Around 25 cm of wire
5. Usb cable / Power supply for ESP32
6. Soldering material

### How to flash the firmware

1. Install [PlatformIO cli](https://docs.platformio.org/en/stable/core/installation/methods/index.html)
2. Connect your ESP32 to your computer using a usb cable.
3. Put your wifi credentials in the file `esp32/src/main.cpp` lines 8 and 9.
4. If you want to set the name that each button will display in Alexa, change them the lines 13 to 16.
5. Run `cd esp32`
6. Then `chmod +x flash`
7. And finally `./flash`

### Electrical scheme

Solder the components in the fenolite plate based on the diagram below.
As you can see, I'm definitely not a eletrical engineer or hardware guy, hope you can understand it.

![](./Excalidraw.png)

## Http Endpoint

Fauxmo exposes this endpoint, so you can control the device using a HTTP POST Request. A body is mandatory,
but the content doesn't matter.

`http://${YOUR_ESP_32_IP}:80/api/devices/lights/${MEMORY_BUTTON_NUMBER}/state/ON`

Using curl:
`curl -X POST http://${YOUR_ESP_32_IP}:80/api/devices/lights/${MEMORY_BUTTON_NUMBER}/state/ON -d 0`
