struct Actuation
{
  int throttle = 1500;
  int steering = 1500;
  int brake = 1500;
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
