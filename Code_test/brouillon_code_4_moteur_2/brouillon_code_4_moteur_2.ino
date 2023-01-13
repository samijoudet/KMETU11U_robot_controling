
/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
  https://randomnerdtutorials.com/esp32-dc-motor-l298n-motor-driver-control-speed-direction/#more-61995
*********/

  
struct MOTOR_PINS
{
  const int INPUT_1_PIN; // Move backwards
  const int INPUT_2_PIN; // Move forwards
  const int ENABLE_PIN; // Motor enable status
  const int PWM_CHANNEL; // If motor enabled: speed proportional to duty cycle
};
MOTOR_PINS MOTORS_LEFT_AV = {33, 32, 25, 0}; // P1 P2 EA
MOTOR_PINS MOTORS_LEFT_AR = {22, 21, 23, 2}; // P1 P2 EA
MOTOR_PINS MOTORS_RIGHT_AR = {4, 18, 19, 4}; // P2 P1 EA
MOTOR_PINS MOTORS_RIGHT_AV = {26, 27, 14, 6};// P2 P1 EA

// Setting PWM properties 
// cycle <=> puissance moteur : 0-255 mais pas de réaction a moins de 200
// freq est arbitraire pour l'instant  

const int FREQ = 30000;
const int RESOLUTION = 8;
int dutyCycle = 255;

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

void setup() {
  // sets the pins as outputs:
  setupMotor(MOTORS_LEFT_AV,FREQ, RESOLUTION);
  setupMotor(MOTORS_RIGHT_AV,FREQ, RESOLUTION);
  setupMotor(MOTORS_LEFT_AR,FREQ, RESOLUTION);
  setupMotor(MOTORS_RIGHT_AR,FREQ, RESOLUTION);
  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");
}

void loop() {
  ledcWrite(MOTORS_LEFT_AV.PWM_CHANNEL, dutyCycle);
  ledcWrite(MOTORS_LEFT_AR.PWM_CHANNEL, dutyCycle);
  ledcWrite(MOTORS_RIGHT_AV.PWM_CHANNEL, dutyCycle);
  ledcWrite(MOTORS_RIGHT_AR.PWM_CHANNEL, dutyCycle);
  
  Serial.println("Moteur L_Av");
  digitalWrite(MOTORS_LEFT_AV.INPUT_1_PIN, LOW);
  digitalWrite(MOTORS_LEFT_AV.INPUT_2_PIN, HIGH);
  delay(2000);
  Serial.println("Moteur L_Ar");
  digitalWrite(MOTORS_LEFT_AR.INPUT_1_PIN, LOW);
  digitalWrite(MOTORS_LEFT_AR.INPUT_2_PIN, HIGH); 
  delay(2000);
  Serial.println("Moteur R_Av");
  digitalWrite(MOTORS_RIGHT_AV.INPUT_1_PIN, LOW);
  digitalWrite(MOTORS_RIGHT_AV.INPUT_2_PIN, HIGH); 
  delay(2000);
  Serial.println("Moteur R_Ar");
  digitalWrite(MOTORS_RIGHT_AR.INPUT_1_PIN, LOW);
  digitalWrite(MOTORS_RIGHT_AR.INPUT_2_PIN, HIGH); 
  delay(2000);
  digitalWrite(MOTORS_LEFT_AV.INPUT_2_PIN, LOW); 
  digitalWrite(MOTORS_LEFT_AR.INPUT_2_PIN, LOW);
  digitalWrite(MOTORS_RIGHT_AV.INPUT_2_PIN, LOW);
  digitalWrite(MOTORS_RIGHT_AR.INPUT_2_PIN, LOW);
  delay(10000);

}
