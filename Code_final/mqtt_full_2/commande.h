/* PINS */

struct MOTOR_PINS
{
  const int INPUT_1_PIN; // Move backwards
  const int INPUT_2_PIN; // Move forwards
  const int ENABLE_PIN; // Motor enable status
  const int PWM_CHANNEL; // If motor enabled: speed proportional to duty cycle
};

void setupMotor(MOTOR_PINS MOTOR,int FREQ,int RESOLUTION);

void setSpeed(MOTOR_PINS MOTOR, int requiredDutyCycle);

void testRobotMovement(MOTOR_PINS MOTOR_L, MOTOR_PINS MOTOR_R);

void moveForward(MOTOR_PINS MOTOR_L, MOTOR_PINS MOTOR_R);

void moveBackwards(MOTOR_PINS MOTOR_L, MOTOR_PINS MOTOR_R);

void stop(MOTOR_PINS MOTOR_L, MOTOR_PINS MOTOR_R);

void right(MOTOR_PINS MOTOR_L, MOTOR_PINS MOTOR_R);

void left(MOTOR_PINS MOTOR_L, MOTOR_PINS MOTOR_R);

void straight(MOTOR_PINS MOTOR_L, MOTOR_PINS MOTOR_R);

// 0:arret 1,2,3 : avant (forward,left,right) 4,5,6 : arrière ((forward,left,right))
void controle(int com,MOTOR_PINS MOTORS_L,MOTOR_PINS MOTORS_R);
