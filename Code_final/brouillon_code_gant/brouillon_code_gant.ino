/*
  This example code is in the public domain.
  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "classic_setup.h"
#include "format_json.h"
#include "commande.h"


/*===== MQTT broker/server ========*/
const char* mqtt_server = "test.mosquitto.org"; // anynomous Ok in 2021

/*===== MQTT TOPICS ===============*/
#define TOPIC_GANT  "uca/projet/sami/gant"
#define TOPIC_COMMANDE  "uca/project/sami"
#define TOPIC_TEST "sami/message/test"

/*===== ESP is MQTT Client =======*/
WiFiClient espClient;           // Wifi 
PubSubClient client(espClient); // MQTT client

/*======== Constante ============ */
const String LOCATION = "NICE";
const String IDENTIFIER = "SAMIJ_gant_1";
const char* ID_MQTT = "SAMIJ_gant_1";

/* GLOBAL VARIABLES */
String lieu = "vide"; // a initialiser
int commande = 0;
int ordre = 0;
int pwm = 0;

// Analog input pin that the potentiometer is attached to
// These constants won't change. They're used to give names to the pins used:
// M : Majeur , I : Index , P : Pouce , G : Gauche , D : Droit  

CAPTOR_PINS MG = {A0,"MG",0,0,0,1}; //VP ou 36
CAPTOR_PINS IG = {A3,"IG",0,0,0,1}; //VN ou 39
CAPTOR_PINS PG = {A6,"PG",0,0,0,1}; //D34 ou 34
CAPTOR_PINS MD = {A5,"MD",0,0,0,1}; //D35 ou 35
CAPTOR_PINS ID = {A4,"ID",0,0,0,1}; //D32 ou 32
CAPTOR_PINS PD = {A7,"PD",0,0,0,1}; //D33 ou 33

unsigned long time_ = 0 ; 

// valeur lus et valeur calibrée des capteurs de flexion

/*====== ESP Statut =========================*/
String getUptime(){
  unsigned long time = millis(); // / 1000UL;
  return String(time);
}

void mqtt_conection() {
  
  while (!client.connected()) { // Loop until we're reconnected
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect => https://pubsubclient.knolleary.net/api
    if (client.connect(ID_MQTT, /* Client Id when connecting to the server */
                        NULL,    /* No credential */ 
                        NULL)) {
      Serial.println("connected");
    } 
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000); // Wait 5 seconds before retrying
      }
    }
}


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  // sets the pins as inputs:
  pinMode(MG.pin, INPUT);
  pinMode(IG.pin, INPUT);
  pinMode(PG.pin, INPUT);
  pinMode(PD.pin, INPUT);
  pinMode(ID.pin, INPUT);
  pinMode(MD.pin, INPUT);  
  // Connexion Wifi
  connect_wifi(); 
  print_network_status();

  client.setServer(mqtt_server, 1883);

  time_ = millis();
}

  
void loop() {

  if (!client.connected()) {
    mqtt_conection();
  }
  // read the analog in value:
  MG.sens = analogRead(MG.pin);
  IG.sens = analogRead(IG.pin);
  PG.sens = analogRead(PG.pin);
  PD.sens = analogRead(PD.pin);
  ID.sens = analogRead(ID.pin);
  MD.sens = analogRead(MD.pin);

  // maping the result (valeur min et max en entrée à calibrer)
  MG.out = map(MG.sens, MG.min,MG.max, 0,100); // puissance
  IG.out = map(IG.sens, IG.min,IG.max, 0,100); // puissance
  PG.out = map(PG.sens, PG.min,PG.max, 0,100); // puissance
  PD.out = map(PD.sens, PD.min,PD.max, 0,100); // valeur () fléchi ou non 
  ID.out = map(ID.sens, ID.min,ID.max, 0,100);
  MD.out = map(MD.sens, MD.min,MD.max, 0,100);
  // print the results to the Serial Monitor:
  
  Serial.print("sensor = ");
  Serial.print(MG.sens);
  Serial.print(" ");
  Serial.print(IG.sens);
  Serial.print(" "); 
  Serial.print(PG.sens);
  Serial.print(" ");
  Serial.print(PD.sens);
  Serial.print(" ");
  Serial.print(ID.sens);
  Serial.print(" ");
  Serial.print(MD.sens);
  Serial.print("\t output = ");
  Serial.print(MG.out);
  Serial.print(" ");
  Serial.print(IG.out);
  Serial.print(" ");
  Serial.print(PG.out);
  Serial.print(" ");
  Serial.print(PD.out);
  Serial.print(" ");
  Serial.print(ID.out);
  Serial.print(" ");
  Serial.print(MD.out);
  

  if (millis()-time_ < 10UL*1000){
    calibration();
    Serial.print("   calibration =");
    Serial.print(millis()-time_ );
  }
  else {
  controle(MG.out,IG.out,PG.out,PD.out,ID.out,MD.out);
  client.publish(TOPIC_COMMANDE, getJSONString_voiture(commande,ordre,pwm, lieu).c_str());
  }
  // wait 200 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(1000);
  Serial.println();
}
