// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

struct Actuation
{
  float throttle = 0.0f;
  float steering = 0.0f;
  float brake = 0.0f;
};

struct TargetActions
{
  float speed = 0.0;
  float steering = 0.0;
  float brake = 0.0;
};
struct VehicleState
{
  TargetActions *target = new TargetActions();
  Actuation *act = new Actuation();
  float speed = -1.0;
  bool is_auto = false;
  bool isSteeringLeftLimiterOn = false;
  bool isSteeringRightLimiterOn = false;
  float angle = 0.0;
};
