#include <brake.h>

mcp2515_can CAN(SPI_CS_PIN);
int output_brake_max = 2000;
int output_brake_min = 1500;
int prev_brake = 1000;

void overwriteBuf(volatile byte *buf, int b0, int b1, int b2, int b3, int b4, int b5, int b6, int b7)
{
    buf[0] = b0;
    buf[1] = b1;
    buf[2] = b2;
    buf[3] = b3;
    buf[4] = b4;
    buf[5] = b5;
    buf[6] = b6;
    buf[7] = b7;
}

/*
 *   inputs a hex string (without prefix 0x)
 *   and return the int value
 */
int strHexToInt(char str[])
{
    // inputs a hex string (without prefix 0x)
    // and return the int value
    return (int)strtol(str, 0, 16);
}

/*
 *   Format Byte 3 as String given clutch, motor flags
 *   and significant byte of position
 */
String posCmdBite3Parser(int ce, int m, String dpos_hi)
{
    return String((int)(ce * pow(2, 7) + m * pow(2, 6) + strHexToInt(const_cast<char *>(dpos_hi.c_str()))), HEX);
}

/*
 *   Initialize the Actuator
 */
void actuatorInit()
{
    while (CAN_OK != CAN.begin(CAN_250KBPS))
    { // init can bus : baudrate = 500k
        // Serial.println("CAN init fail, retry...");
        delay(10);
    }
    // Serial.println("CAN init ok!");

    //    // Disable everything
    //    CAN.sendMsgBuf(COMMAND_ID, 1, 8, CLUTCH_MOTOR_OFF);
    //    delay(20);

    // Enable clutch for loop input
    CAN.sendMsgBuf(COMMAND_ID, CAN_EXT_ID, CAN_RTR_BIT, CLUTCH_ON);
    delay(20);

    setActuatorPosition(MIN_DIST);
    delay(3000);
}

/*
 *   Move the Actuator to designated position in inches.
 *   The Actuator will execute whatever
 *   the latest command is immediately.
 */
void setActuatorPosition(float inputDist)
{
    unsigned char data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    String bite2;
    String bite3;
    String dpos_lo;
    String dpos_hi;

    // Clipping input range
    if (inputDist < 0.0)
    {
        inputDist = 0.0;
    }
    if (inputDist > MAX_DIST)
    {
        inputDist = MAX_DIST;
    }

    // Convert input to hex
    int intDist = inputDist * 1000 + 500; // in 0.001” steps
    String hexDist = String(intDist, HEX);
    int hexDistLen = hexDist.length();

    // the least significant byte of position
    dpos_lo = hexDist.substring(hexDistLen - 2);
    bite2 = dpos_lo;
    // The most significant byte of position
    dpos_hi = hexDist.substring(0, hexDistLen - 2);

    // Clutch on, Motor on and move to the desired position
    bite3 = posCmdBite3Parser(1, 1, dpos_hi);
    overwriteBuf(data, 0x0F, 0x4A, strHexToInt(const_cast<char *>(bite2.c_str())), strHexToInt(const_cast<char *>(bite3.c_str())), 0, 0, 0, 0);

    CAN.sendMsgBuf(COMMAND_ID, CAN_EXT_ID, CAN_RTR_BIT, data);
}

void setupBrake()
{
    actuatorInit();
}

/**
 * @param brake value from 1000 - 2000
 */
void writeToBrake(int brake)
{
    float brake_out = float(constrain(brake, output_brake_min, output_brake_max));

    if (brake_out != prev_brake && brake_out > 1800)
    {
        prev_brake = brake_out;
        float actuator_out = map(brake_out, output_brake_min, output_brake_max, MIN_DIST, MAX_DIST);
        setActuatorPosition(actuator_out);
        return;
    }

    if (brake_out != prev_brake && brake_out < 1200)
    {
        prev_brake = brake_out;
        float actuator_out = map(brake_out, output_brake_min, output_brake_max, MIN_DIST, MAX_DIST);
        setActuatorPosition(actuator_out);
        return;
    }
}