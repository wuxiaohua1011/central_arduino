// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef _MODELS_h
#define _MODELS_h

/**
In C++, the main difference between a struct and a class is the default access level. A struct is considered a public type, while a class is considered a private type. This means that by default, all members of a struct are public, while all members of a class are private.
In addition to this, structs have no inheritance while a class has this feature.
Another difference is that structs are typically used to represent a collection of data, while classes are used to represent objects with both data and behavior (methods).
However, struct and class are very similar in C++, the only real difference is the default access level and some people use struct for POD (Plain Old Data) and class for object with behavior. You can use struct or class interchangeably in most cases.
*/
struct Actuation
{
    float throttle = 0.0f;
    float steering = 0.0f;
    float brake = 0.0f;
    bool reverse = false;
};

struct VehicleState
{
    Actuation *manual_actuation = new Actuation();
    Actuation *auto_actuation = new Actuation();
    Actuation *current_actuation = new Actuation();
    bool is_auto = false;
    bool is_left_limiter_ON = false;
    bool is_right_limiter_ON = false;
    float angle = 0.0;
    float angular_velocity = 0.0;
};
#endif //_MODELS_h