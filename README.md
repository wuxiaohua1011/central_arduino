<!--
 Copyright 2023 michael. All rights reserved.
 Use of this source code is governed by a BSD-style
 license that can be found in the LICENSE file.
-->

# Embedded software for autonomous GoKart
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


##### The Include directory
This directory is intended for project header files.

A header file is a file containing C declarations and macro definitions
to be shared between several project source files. You request the use of a
header file in your project source file (C, C++, etc) located in `src` folder
by including it, with the C preprocessing directive `#include'.

```src/main.c

#include "header.h"

int main (void)
{
 ...
}
```

Including a header file produces the same results as copying the header file
into each source file that needs it. Such copying would be time-consuming
and error-prone. With a header file, the related declarations appear
in only one place. If they need to be changed, they can be changed in one
place, and programs that include the header file will automatically use the
new version when next recompiled. The header file eliminates the labor of
finding and changing all the copies as well as the risk that a failure to
find one copy will result in inconsistencies within a program.

In C, the usual convention is to give header files names that end with `.h'.
It is most portable to use only letters, digits, dashes, and underscores in
header file names, and at most one dot.


Here is a tutorial on CPP header files
https://www.simplilearn.com/tutorials/cpp-tutorial/guide-to-understand-cpp-header-files#:~:text=DevelopmentExplore%20Program-,What%20Are%20C%2B%2B%20Header%20Files%3F,processed%20prior%20to%20the%20compilation.



## Other Notes
- This repository is under constant development, documentation might not be up-to-date. Please contact Michael Wu <wuxiaohua1011@gmail.com> for any questions. 

