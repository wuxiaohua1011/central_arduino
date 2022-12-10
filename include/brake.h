#include <SPI.h> // using CAN_BUS_Shield from Seeed Studio
#include "pin.h"
#include "mcp2515_can.h"
#define CAN_EXT_ID 1
#define CAN_RTR_BIT 8
const float MIN_DIST = 0.0;                // Minimum distance for actuator
const float MAX_DIST = 3.0;                // Maximum safe distance that the actuator can move (inches)
const unsigned long COMMAND_ID = 0xFF0000; // Default command ID for CAN Actuator
const unsigned long REPORT_ID = 0xFF0001;  // Default report ID for CAN Actuator
const char CLUTCH_MOTOR_OFF[8] = {0x0F, 0x4A, 0xC4, 0x09, 0, 0, 0, 0};
const byte CLUTCH_ON[8] = {0x0F, 0x4A, 0xC4, 0x89, 0, 0, 0, 0};
const char POS_ZERO[8] = {0x0F, 0x4A, 0xC0, 0x00, 0, 0, 0, 0};

extern mcp2515_can CAN; // Set CS pin
extern int output_brake_max;
extern int output_ibrake_min;
void overwriteBuf(volatile byte *buf, int b0, int b1, int b2, int b3, int b4, int b5, int b6, int b7);

/*
 *   inputs a hex string (without prefix 0x)
 *   and return the int value
 */
int strHexToInt(char str[]);

/*
 *   Format Byte 3 as String given clutch, motor flags
 *   and significant byte of position
 */
String posCmdBite3Parser(int ce, int m, String dpos_hi);

/*
 *   Initialize the Actuator
 */
void actuatorInit();

/*
 *   Move the Actuator to designated position in inches.
 *   The Actuator will execute whatever
 *   the latest command is immediately.
 */
void setActuatorPosition(float inputDist);

void setupBrake();

void writeToBrake(int brake);