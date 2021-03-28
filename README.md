# 387_earthquake
An Earthquake Sensor using Arduino Uno and vibration sensors.

MAIN GOAL: Detect "Earthquakes" on a desk, and display the strength of the vibration on an LCD screen. 
I define earthquakes as any vibration on a plane over a certain strength.

PARTS NECESSARY:
- Arduino Uno R3
- Vibration Sensor(s)
  - Analog
  - Piezoelectric would be easier, spring-based is likely doable with changes.
- LCD Screen
  - This project will not use an I2C equipped screen. Rewrites will be necessary if you would like to use one.

IDEAS FOR EXPANSION:
- Use several sensors to triangulate the origin of the vibration based on the detected strength.
- Tune sensitivities to detect stronger or weaker vibrations. A form of filtering.
  - Make this easily done in software.
