Asset Tracker Example Firmware
====

Hello!  This example firmware uses the 
Particle Asset Tracker Shield ( https://docs.particle.io/datasheets/photon-shields/#electron-asset-tracker ), 
and an Electron ( https://docs.particle.io/datasheets/electron-datasheet/ ).

What does it do?
===

It enables power to the GPS module and starts listening for location data.  Once it gets location data or detects a 
change in the Electron's battery, it will publish an updated "GPS_coords" event with any available location data,
as well as the battery voltage and state of charge.  It will then wait at least a minute before publishing again.

This app is meant to demonstrate the shield and help easily provide this location data to other services, it's not
trying to be the most efficient application data wise.  So be warned, this will consume some data, but it's good
for debugging / rapid development.



What should I do?
===

Make sure you have the particle-cli installed, and build the firmware:

```
cd azure-asset-tracker
cd firmware
./build.sh
# or particle compile electron . --saveTo electron_gps.bin

# connect your electron to your shield, put it into DFU mode, and flash with:

./flash.sh
# or particle flash --usb electron_gps.bin

#watch your data stream with:
particle subscribe GPS mine

```

How do I get my data into Azure?
===

Checkout the webhook folder for an example hook and guide on getting connected to Azure.

Thanks!
