struct Actuation
{
  int throttle = 1500;
  int steering = 1500;
  int brake = 1500;
};
struct VehicleState
{
  float speed = -1.0;
  Actuation *act = new Actuation();
};
