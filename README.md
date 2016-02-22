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


What's all here?
====

Checkout the firmware folder for an example app and guide to flash to your Electron, and checkout the webhook folder for
an example webhook and guide for getting your data into Azure!  Checkout the build directory for example photos of
how you can assemble the project.

Thanks!
