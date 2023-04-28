# G2C Environment Monitor

In this example you'll create a Web dashboard to measure environmental variables such as temperature, humidity, pressure and gas resistance.

## Packages

This packages must be installed in order to compile this example, in NECTO Studio go to the Show tab and select Package_manager, then use the search bar and install the following packages:

- [Environment click](https://www.mikroe.com/environment-click)
- [G2C click](https://www.mikroe.com/g2c-click)

## Libraries

This project requires the following libraries from [mikroSDK](https://docs.mikroe.com/mikrosdk/user-manual/index.html), they are already included:

- Board
- Conversions
- Log

### Device manifest

This project connects to the [clickcloud iot service](https://www.mikroe.com/click-cloud-iot-service), a free IoT dashboard, therefore you'll have to create an account in order to use this project.

Clickloud connects to your device using a device key and device password, in order to get them you'll have to create a device first.

Devices in Clickcloud require a device manifest, in simple terms, this manifest is a template that contains information of sensors, actuators and some other metadata of the device. For this example we've provided the device manifest, that you can just import.

We encourage you to follow the interactive tutorial on Cliclcloud to get the ropes of how the service works, experiment and have fun!.