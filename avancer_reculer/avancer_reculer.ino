/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
  https://randomnerdtutorials.com/esp32-dc-motor-l298n-motor-driver-control-speed-direction/#more-61995
*********/

//Motor D : droite 
int motor_D_Pin1 = 26; 
int motor_D_Pin2 = 27; 
int enable_D_Pin = 14;

//Motor G : gauche 
int motor_G_Pin1 = 33; 
int motor_G_Pin2 = 32; 
int enable_G_Pin = 25;


// Setting PWM properties 
// cycle <=> puissance moteur : 0-255 mais pas de réaction a moins de 200
// freq est arbitraire pour l'instant  

const int freq = 30000;
const int pwmChannel_D = 0;
const int pwmChannel_G = 0;
const int resolution = 8;
int dutyCycle = 255;

void setup() {
  // sets the pins as outputs:

  pinMode(motor_D_Pin1, OUTPUT); // on/off reculer puissance 100%
  pinMode(motor_D_Pin2, OUTPUT); // on/off avancer puissance 100%
  pinMode(enable_D_Pin, OUTPUT); // contrôle la vitesse  
  
  pinMode(motor_G_Pin1, OUTPUT); // on/off reculer puissance 100%
  pinMode(motor_G_Pin2, OUTPUT); // on/off avancer puissance 100%
  pinMode(enable_G_Pin, OUTPUT); // contrôle la vitesse
  
  // configure LED PWM functionalitites

  ledcSetup(pwmChannel_D, freq, resolution);
  ledcSetup(pwmChannel_G, freq, resolution);
  
  // attach the channel to the GPIO to be controlled

  ledcAttachPin(enable_D_Pin, pwmChannel_c);
  ledcAttachPin(enable_G_Pin, pwmChannel_d);

  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");
}

void loop() {

  ledcWrite(pwmChannel_D, dutyCycle);
  ledcWrite(pwmChannel_G, dutyCycle);

  Serial.println("Avant");
  digitalWrite(motor_D_Pin1, LOW);
  digitalWrite(motor_D_Pin2, HIGH); 
  digitalWrite(motor_G_Pin1, LOW);
  digitalWrite(motor_G_Pin2, HIGH); 
  delay(2000);
  Serial.println("Arret");
  digitalWrite(motor_D_Pin1, LOW);
  digitalWrite(motor_D_Pin2, LOW);  
  digitalWrite(motor_G_Pin1, LOW);
  digitalWrite(motor_G_Pin2, LOW);
  delay(2000);
  Serial.println("Arrière");
  digitalWrite(motor_D_Pin1, HIGH);
  digitalWrite(motor_D_Pin2, LOW); 
  digitalWrite(motor_G_Pin1, HIGH);
  digitalWrite(motor_G_Pin2, LOW); 
  delay(2000);
  Serial.println("Arret");
  digitalWrite(motor_D_Pin1, LOW);
  digitalWrite(motor_D_Pin2, LOW);  
  digitalWrite(motor_G_Pin1, LOW);
  digitalWrite(motor_G_Pin2, LOW);

  delay(10000);
 
}
