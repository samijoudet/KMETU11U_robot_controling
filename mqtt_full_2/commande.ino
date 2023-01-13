/*********
 * Many sources :
 => G.Menez
 => https://raw.githubusercontent.com/RuiSantosdotme/ESP32-Course/master/code/WiFi_Web_Server_DHT/WiFi_Web_Server_DHT.ino
 => https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-web-server-arduino-ide/
 => Kevin Levy
 => Rui Santos
  Complete project details at http://randomnerdtutorials.com
  https://randomnerdtutorials.com/esp32-dc-motor-l298n-motor-driver-control-speed-direction/#more-61995
*********/

void setupMotor(MOTOR_PINS MOTOR,int FREQ,int RESOLUTION)
{
  // sets the pins as outputs:
  pinMode(MOTOR.INPUT_1_PIN, OUTPUT); // on/off avancer puissance 100%
  pinMode(MOTOR.INPUT_2_PIN, OUTPUT); // on/off reculer puissance 100%
  pinMode(MOTOR.ENABLE_PIN, OUTPUT);  // contrôle la vitesse

  // configure LED PWM functionalitites
  ledcSetup(MOTOR.PWM_CHANNEL, FREQ, RESOLUTION);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(MOTOR.ENABLE_PIN, MOTOR.PWM_CHANNEL);
}



void setSpeed(MOTOR_PINS MOTOR, int requiredDutyCycle)
{
  ledcWrite(MOTOR.PWM_CHANNEL, requiredDutyCycle);
}

void moveForward(MOTOR_PINS MOTOR_L, MOTOR_PINS MOTOR_R)
{
  digitalWrite(MOTOR_L.INPUT_1_PIN, LOW);
  digitalWrite(MOTOR_L.INPUT_2_PIN, HIGH);
  digitalWrite(MOTOR_R.INPUT_1_PIN, LOW);
  digitalWrite(MOTOR_R.INPUT_2_PIN, HIGH);  
}

void moveBackwards(MOTOR_PINS MOTOR_L, MOTOR_PINS MOTOR_R)
{
  digitalWrite(MOTOR_L.INPUT_1_PIN, HIGH);
  digitalWrite(MOTOR_L.INPUT_2_PIN, LOW);
  digitalWrite(MOTOR_R.INPUT_1_PIN, HIGH);
  digitalWrite(MOTOR_R.INPUT_2_PIN, LOW);
}

void stop(MOTOR_PINS MOTOR_L, MOTOR_PINS MOTOR_R)
{
  digitalWrite(MOTOR_L.INPUT_1_PIN, LOW);
  digitalWrite(MOTOR_L.INPUT_2_PIN, LOW);
  digitalWrite(MOTOR_R.INPUT_1_PIN, LOW);
  digitalWrite(MOTOR_R.INPUT_2_PIN, LOW);
}

void right(MOTOR_PINS MOTOR_L, MOTOR_PINS MOTOR_R)
{
 setSpeed(MOTOR_L, 255);
 setSpeed(MOTOR_R, 180);
}

void left(MOTOR_PINS MOTOR_L, MOTOR_PINS MOTOR_R)
{
 setSpeed(MOTOR_L, 180);
 setSpeed(MOTOR_R, 255);
}

void straight(MOTOR_PINS MOTOR_L, MOTOR_PINS MOTOR_R)
{
 setSpeed(MOTOR_L, 220);
 setSpeed(MOTOR_R, 220);
}

void testRobotMovement(MOTOR_PINS MOTOR_LEFT, MOTOR_PINS MOTOR_RIGHT)
{
  setSpeed(MOTORS_LEFT, dutyCycle);
  setSpeed(MOTORS_RIGHT, dutyCycle);

  Serial.println("Move forward");
  straight(MOTORS_LEFT, MOTORS_RIGHT);
  moveForward(MOTORS_LEFT, MOTORS_RIGHT);
  delay(2000);

  Serial.println("Stop");
  stop(MOTORS_LEFT,MOTORS_RIGHT);
  delay(1000);

  Serial.println("Move backwards");
  straight(MOTORS_LEFT, MOTORS_RIGHT);
  moveBackwards(MOTORS_LEFT,MOTORS_RIGHT);

  delay(2000);

  Serial.println("Stop");
  stop(MOTORS_LEFT,MOTORS_RIGHT);
  delay(1000);
}



void controle(int com,MOTOR_PINS MOTORS_L,MOTOR_PINS MOTORS_R){ 
  if (com==1 || com==4){straight(MOTORS_L,MOTORS_R); }
  if (com==2 || com==5){left(MOTORS_L,MOTORS_R); }
  if (com==3 || com==6){right(MOTORS_L,MOTORS_R); }
  
  if (com==0){
    stop(MOTORS_L,MOTORS_R);
  }
  else if (com<4){
    moveForward(MOTORS_L,MOTORS_R);
  }
  else {
    moveBackwards(MOTORS_L,MOTORS_R);
    }
}
