/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
  https://randomnerdtutorials.com/esp32-dc-motor-l298n-motor-driver-control-speed-direction/#more-61995
*********/
/*
// Motor A : avant_droit (EA, P2, P1) => (bleu,vert,jaune)
int motor_a_Pin1 = 16; 
int motor_a_Pin2 = 17; 
int enable_a_Pin = 4;

//Motor B : arrière_droit (EA, P4, P3) => (rouge, orange, jaune)
int motor_b_Pin1 = 19; 
int motor_b_Pin2 = 18; 
int enable_b_Pin =18;
*/
//Motor C : droite (EA, P1, P2) => (violet, gris, blanc)
int motor_c_Pin1 = 26; 
int motor_c_Pin2 = 27; 
int enable_c_Pin = 14;

//Motor D : gauche (EA, P4, P3) => (noir, marron, rouge)
int motor_d_Pin1 = 33; 
int motor_d_Pin2 = 32; 
int enable_d_Pin = 25;


// Setting PWM properties 
// cycle <=> puissance moteur : 0-255 mais pas de réaction a moins de 200
// freq est arbitraire pour l'instant  

const int freq = 30000;
//const int pwmChannel_a = 0;
//const int pwmChannel_b = 0;
const int pwmChannel_c = 0;
const int pwmChannel_d = 0;
const int resolution = 8;
int dutyCycle = 255;

void setup() {
  // sets the pins as outputs:
  /*
  pinMode(motor_a_Pin1, OUTPUT); // on/off reculer puissance 100%
  pinMode(motor_a_Pin2, OUTPUT); // on/off avancer puissance 100%
  pinMode(enable_a_Pin, OUTPUT); // contrôle la vitesse

  pinMode(motor_b_Pin1, OUTPUT); // on/off reculer puissance 100%
  pinMode(motor_b_Pin2, OUTPUT); // on/off avancer puissance 100%
  pinMode(enable_b_Pin, OUTPUT); // contrôle la vitesse
  */
  pinMode(motor_c_Pin1, OUTPUT); // on/off reculer puissance 100%
  pinMode(motor_c_Pin2, OUTPUT); // on/off avancer puissance 100%
  pinMode(enable_c_Pin, OUTPUT); // contrôle la vitesse  
  
  pinMode(motor_d_Pin1, OUTPUT); // on/off reculer puissance 100%
  pinMode(motor_d_Pin2, OUTPUT); // on/off avancer puissance 100%
  pinMode(enable_d_Pin, OUTPUT); // contrôle la vitesse
  
  // configure LED PWM functionalitites
  //ledcSetup(pwmChannel_a, freq, resolution);
  //ledcSetup(pwmChannel_b, freq, resolution);
  ledcSetup(pwmChannel_c, freq, resolution);
  ledcSetup(pwmChannel_d, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  //ledcAttachPin(enable_a_Pin, pwmChannel_a);
  //ledcAttachPin(enable_b_Pin, pwmChannel_b);
  ledcAttachPin(enable_c_Pin, pwmChannel_c);
  ledcAttachPin(enable_d_Pin, pwmChannel_d);

  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");
}

void loop() {
  //ledcWrite(pwmChannel_a, dutyCycle);
  //ledcWrite(pwmChannel_b, dutyCycle);
  ledcWrite(pwmChannel_c, dutyCycle);
  ledcWrite(pwmChannel_d, dutyCycle);
  /*
  Serial.println("Moteur A");
  digitalWrite(motor_a_Pin1, LOW);
  digitalWrite(motor_a_Pin2, HIGH); 
  delay(2000);
  Serial.println("Moteur B");
  digitalWrite(motor_b_Pin1, LOW);
  digitalWrite(motor_b_Pin2, HIGH); 
  delay(2000)
  */
  
  Serial.println("Avant");
  digitalWrite(motor_c_Pin1, LOW);
  digitalWrite(motor_c_Pin2, HIGH); 
  digitalWrite(motor_d_Pin1, LOW);
  digitalWrite(motor_d_Pin2, HIGH); 
  delay(2000);
  Serial.println("Arret");
  digitalWrite(motor_c_Pin1, LOW);
  digitalWrite(motor_c_Pin2, LOW);  
  digitalWrite(motor_d_Pin1, LOW);
  digitalWrite(motor_d_Pin2, LOW);
  delay(2000);
  Serial.println("Arrière");
  digitalWrite(motor_c_Pin1, HIGH);
  digitalWrite(motor_c_Pin2, LOW); 
  digitalWrite(motor_d_Pin1, HIGH);
  digitalWrite(motor_d_Pin2, LOW); 
  delay(2000);
  Serial.println("Arret");
  digitalWrite(motor_c_Pin1, LOW);
  digitalWrite(motor_c_Pin2, LOW);  
  digitalWrite(motor_d_Pin1, LOW);
  digitalWrite(motor_d_Pin2, LOW);
  
  /*
  digitalWrite(motor_a_Pin1, LOW);  
  digitalWrite(motor_a_Pin2, LOW); 
  digitalWrite(motor_b_Pin1, LOW);
  digitalWrite(motor_b_Pin2, LOW);
  */
  delay(10000);
  
  /*
  // Move the DC motor forward at maximum speed
  ledcWrite(pwmChannel, dutyCycle);
  Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  delay(1000);

  // Move DC motor backwards at maximum speed
  Serial.println("Moving Backwards");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  delay(1000);

  // Move DC motor forward with increasing speed
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  while (dutyCycle <= 255){
    ledcWrite(pwmChannel, dutyCycle);  // vitesse proportienelle au "dutyCycle"
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(500);
  }
  dutyCycle = 200;
  */
}
