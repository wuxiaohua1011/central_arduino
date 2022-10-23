# Embedded software for autonomous GoKart

File structure
- `main.cpp`
- `include`
  - `led.h`
  - `main.h`
  - `pin.h`
  - `pwm_voltage_converter.h`
  - `radiolink.h`
  - `SerialCommunication.h`
  - `spark_max.h`
  - `speed_estimation.h`
  - `steering_limiter.h`
  - `utilities.h`


`main.cpp` contains the driver function, namely `setup()` and `loop()`. 
the `include` directory contains logic for each component. We separate them out for ease of debugging and reduce merge conflicts


## Serial Communication Protocol

### Protocol V0.0.1
Communication via the Arduino to host machine will be via USB Serial protocol at the baudrate of 9600.

#### Arduino -> Host
The message from Arduino to host will be in the format of 
`<data1,data2,data3,...>`. Namely with `startMarker` and `endMarker` wrapping each message, data encoded as string, and `,` as delimiter between data. 

#### Host -> Arduino
The message for mat from host -> Arduino will be in the format of
`<ACTION, OPTIONAL, OPTIONAL>` 
where ACTION = `s` or `a`, standing for `state` or `action` respectively. 

if ACTION = `s`, the arduino is not expecting `OPTIONAL` parameters, so the message is simply `<s>`, and the arduino will respond with the current state of the vehicle 

if ACTION = `a`, the arduino is expecting throttle, steering, brake respectively. Sample message: `<a, 1600, 1500, 1500>`. 

#### Special note
The Arduino is not going to respond to `action` if the manual control mode is `ON` for the vehicle. To turn manual control `OFF`, simply press and hold the button on the Radio controller. 



## Other Notes
- This repository is under constant development, documentation might not be up-to-date. Please contact Michael Wu <wuxiaohua1011@gmail.com> for any questions. 
