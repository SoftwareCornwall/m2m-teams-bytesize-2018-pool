# Rover Starter Files
The starter files for Software Cornwalls Mission to Mars rover robots. Using these,
you'll have the rovers whizzing about in no time.

## Usage Instructions
Clone the project locally and edit the main.ino file for starters.

The following examples will help you to begin working with the rovers. Try adding
some to the loop within the main.ino file. As you begin to develop your rover
instruction set, you'll likely want to encapsulate these groups of instructions
into functions.

### Motor Usage

**Motors Forwards**

    left_motor.forward(speed);
    right_motor.forward(speed);

**Motors Reverse**

    left_motor.reverse(speed);
    right_motor.reverse(speed);

**Turn off the motors**

    left_motor.stop();
    right_motor.stop();

### Distance Sensor Usage

Returns an integer value for the distance between the sensor and nearest object in cm.
Note: There should be a minimum delay of 50ms between each ping of the sensor.

    sensor.distance_forwards();
    sensor.distance_down();

### Light Sensor Usage

    sensor.left_light_sensor();
    sensor.center_light_sensor();
    sensor.right_light_sensor();

### Interrupt Usage

Returns an integer value for the number of pulses created by the hall effect sensor.

    left_motor.get_pulse_count();
    right_motor.get_pulse_count();
