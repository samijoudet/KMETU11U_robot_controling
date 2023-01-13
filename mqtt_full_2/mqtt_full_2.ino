/*********
 Based on Rui Santos work : https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide/
 File mqtt_full/mqtt_full.ino
 Modified by GM
*********/
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "classic_setup.h"
#include "format_json.h"
#include "commande.h"
//#include "OneWire.h"
//#include "DallasTemperature.h"


/*===== MQTT broker/server ========*/
const char* mqtt_server = "test.mosquitto.org"; // anynomous Ok in 2021

/*===== MQTT TOPICS ===============*/
#define TOPIC_TEMPERATURE  "uca/projet/sami/temperature"
#define TOPIC_COMMANDE  "uca/project/sami"
/*===== ESP is MQTT Client =======*/
WiFiClient espClient;           // Wifi 
PubSubClient client(espClient); // MQTT client

/*============VARIABLE============*/
unsigned long time_pub = 0; // temps depuis la dernière publication  
int dutyCycle = 255;
int temp = 0;
int commande = 0; // controle -> 0: pause , 1 : temperature , 2 : camera , 3 : voiture
int ordre = 0;// "0 : arret" -> codage du déplacement demander (voir fichier commande.ino)
String lieu = "vide";

/*========GLOBAL CONSTANTS======== */
// Setting PWM properties
// cycle <=> puissance moteur : 0-255 mais pas de réaction a moins de 200
// freq est arbitraire pour l'instant
const int FREQ = 30000;
const int RESOLUTION = 8;
const int MAX_DUTY_CYCLE = pow(2, RESOLUTION) - 1;
const String LOCATION = "NICE";
const String IDENTIFIER = "SAMIJ_voiture_1";
const char* ID_MQTT = "SAMIJ_voiture_1";
/*============= GPIO ==============*/
// setup output motor
MOTOR_PINS MOTORS_LEFT = {33, 32, 25, 0};
MOTOR_PINS MOTORS_RIGHT = {26, 27, 14, 1};
// setup input temp
// §§§§§§§ à faire §§§§§§§

/*====== ESP Statut =========================*/
unsigned long getUptime(){
  return millis();
  }
unsigned long getTemp(){
  return temp;
  }


/*============== CALLBACK ===================*/
void mqtt_pubcallback(char* topic, 
                      byte* message, 
                      unsigned int length) {
   
  //Callback if a message is published on this topic.
  Serial.print("Message arrived on topic : ");
  Serial.println(topic);
  Serial.print("=> ");

  // Byte list to String and print to Serial
  String messageTemp;
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // If a message is received on the topic,
  // you check if the topic message 
  // Changes the variable according to the message
  if (String(topic) == TOPIC_COMMANDE) {
    getStaticJsonDocument_frombytes(message);
    if (commande == 3) {
      controle(ordre,MOTORS_LEFT,MOTORS_RIGHT);
      time_pub = getUptime();
      }
    else {
      controle(0,MOTORS_LEFT,MOTORS_RIGHT);
    }
    if (commande == 2){//mouvement caméra non inplémenté
      }
    if (commande == 1){
      client.publish(TOPIC_TEMPERATURE,getJSONString_Temp().c_str());
      }
  }
}

/*============= SUBSCRIBE =====================*/
void mqtt_mysubscribe(char *topic) {
  /*
   * Subscribe to a MQTT topic 
   */
  while (!client.connected()) { // Loop until we're reconnected

    Serial.print("Attempting MQTT connection...");
    // Attempt to connect => https://pubsubclient.knolleary.net/api
    if (client.connect(ID_MQTT, /* Client Id when connecting to the server */
		                    NULL,    /* No credential */ 
		                    NULL)) {
      Serial.println("connected");
      // then Subscribe topic
      client.subscribe(topic);
    } 
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      
      Serial.println(" try again in 5 seconds");
      delay(5000); // Wait 5 seconds before retrying
    }
  }
}


/*===== Arduino IDE paradigm : setup+loop =====*/
void setup() {
  Serial.begin(9600);
  //while (!Serial); // wait for a serial connection. Needed for native USB port only

  // Initialize the output variables as outputs
  setupMotor(MOTORS_LEFT,FREQ, RESOLUTION);
  setupMotor(MOTORS_RIGHT,FREQ, RESOLUTION);
  // Connexion Wifi 
  connect_wifi(); 
  print_network_status();
  
  // initialiser capteur de température
  // §§§§§§ a complter §§§§§§§§§

  // set server of our client
  client.setServer(mqtt_server, 1883);
  // set callback when publishes arrive for the subscribed topic
  client.setCallback(mqtt_pubcallback); 
  client.setBufferSize(2048);
}
/*================= LOOP ======================*/
void loop() {
  int32_t period = 1000; // 1 sec

  if (getUptime()-time_pub > 2000) {
    controle(0,MOTORS_LEFT,MOTORS_RIGHT);
     Serial.println("stop");
    }
  if (!client.connected()) { 
    mqtt_mysubscribe((char *)(TOPIC_COMMANDE));
    client.subscribe(TOPIC_GANT);
  }
  delay(int32_t);
  client.loop();
}
