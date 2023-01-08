// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

struct Actuation
{
  float throttle = 0.0f;
  float steering = 0.0f;
  float brake = 0.0f;
};
struct VehicleState
{
  float speed = -1.0;
  bool is_auto = false;
  Actuation *act = new Actuation();
  bool isSteeringLeftLimiterOn = false;
  bool isSteeringRightLimiterOn = false;
  float angle = 0.0;
};
