# xplane_cockpit_toliss_a321

These are instructions to build a simple A321 Xplane cokpit. This build assumes that you already own:

o Toliss A321: https://store.x-plane.org/Airbus-A321-by-Toliss_p_1174.html
o Thrustmaster TCA Pack Airbus Edition: https://shop.thrustmaster.com/en_gb/tca-officer-pack-airbus-edition.html
o Saitek Multi Panel: https://www.logitechg.com/en-gb/products/flight/flight-simulator-autopilot-multipanel.945-000009.html
o Saitek Radio Panel: https://www.logitechg.com/en-gb/products/flight/flight-simulator-cockpit-radio-panel.945-000011.html

You need to install the *.ino file on a Teensy microcontroller an connect it on a different USB bus than the Saitek panels. The panels won't work if the Saitek panels are on the same bus than the Teensy microcontroller: https://www.pjrc.com/store/teensy41.html

The wiring instructions can be found in the Fritzing file (*.fzz) https://fritzing.org/
