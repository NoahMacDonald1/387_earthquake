# 387_earthquake
An Earthquake Sensor using Arduino Uno and vibration sensors.
Programmed using AVR toolchain.

MAIN GOAL: Detect "Earthquakes" on a desk, and display the strength of the vibration on an LCD screen. 
I define earthquakes as any vibration on a plane over a certain strength.

PARTS NECESSARY:
- Arduino Uno R3
- Vibration Sensor(s)
  - Analog
  - Piezoelectric would be easier, spring-based is likely doable with changes.
  - This project uses 2 sensors, but can easily scale up or down.
- LCD Screen
  - This project uses a standard 1602A LCD. Rewrites will be necessary if you would like to use one.
- 10K Ohm Potentiometer
  - For the LCD
- 220 Ohm Resistors
  - This project currently uses 3. One for the LCD, one for each LED. 
- LEDs (Optional)
- Capacitors (Optional)
- A breadboard

READ THE WIKI FOR MORE INFORMATION
