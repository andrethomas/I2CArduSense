***EXPERIMENTAL***

This project is still under development and not ready for testing

Basic idea is to create generic code for a arduino board to act as a I2C slave
which may be interacted with from the Sonoff-Tasmota firmware by Theo Arendst

Provision is made for callbacks for up to 16 sensors that may be running on an
external arduino based board.

The Tasmota firmware will be able to probe a specific sensor number by reading
its I2C register and receiving a pre-processed JSON response which may then
be processed to MQT by Tasmota.

Theoretically it may be used by other firmware but the main aim is to add extended
off-loaded sensor processing to the Tasmota firmware.
