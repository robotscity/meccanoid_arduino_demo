# meccanoid_arduino_demo
This is an example for Meccanoid Arduino library.

To try it you'll need the following:

1. Meccanoid G15 in its human form
2. Any Arduino
3. Motor shield or motor driver, to drive robot's wheels. I tried the one based on L293D and it was quite decent
4. Tamiya Mini female connector with wires - to connect to the robots' battery
5. Male connectors: CWF-2 to connect one motor and PLS-2 (it fits but not ideally, if you know the exact name of the connectors - please write me) to connect another
6. 3 resistors of 22 kOhm and 3 resistors of 1 kOhm - to make pullup resistors (according to the manual)
7. Download the [library](http://cdn.meccano.com/open-source/meccanoid-library.zip) and add it to Arduino environment using Sketch -> Add library -> Add ZIP library
8. Try this example: open demo_meccanoids.ino, change pin numbers accourding to your board, and upload it to your Arduino board

You can also check out the [reference material](http://cdn.meccano.com/open-source/Meccano_SmartModuleProtocols_2015.pdf), to understand, how do the Smart Modules work


The result of this demo code: see [video] (https://youtu.be/HYVo0rqz0PA)

![alt text](https://cloud.githubusercontent.com/assets/7447910/12682678/c18a852e-c6c5-11e5-8186-a6897cf008fb.jpg "Meccanoid DOFs")
