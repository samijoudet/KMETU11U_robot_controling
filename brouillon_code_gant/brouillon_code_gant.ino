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
#define TOPIC_TEMPERATURE  "uca/projet/sami/temperature"
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
const int analogInPin_MG = A0; //VP ou 36
const int analogInPin_IG = A3; //VN ou 39
const int analogInPin_PG = A6; //D34 ou 34 
const int analogInPin_PD = A7; //D35 ou 35
const int analogInPin_ID = A4; //D32 ou 32
const int analogInPin_MD = A5; //D33 ou 33

// valeur lus et valeur calibrée des capteurs de flexion
int sensorValue_MG  = 0;    // value read from the pot    
int outputValue_MG  = 0;    // value output (analog out)
int sensorValue_IG  = 0;        
int outputValue_IG  = 0;
int sensorValue_PG  = 0;        
int outputValue_PG  = 0;
int sensorValue_MD  = 0;        
int outputValue_MD  = 0;
int sensorValue_ID  = 0;        
int outputValue_ID  = 0;
int sensorValue_PD  = 0; 
int outputValue_PD  = 0;

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
  pinMode(analogInPin_MG, INPUT);
  pinMode(analogInPin_IG, INPUT);
  pinMode(analogInPin_PG, INPUT);
  pinMode(analogInPin_PD, INPUT);
  pinMode(analogInPin_ID, INPUT);
  pinMode(analogInPin_MD, INPUT);

  // Connexion Wifi
  connect_wifi(); 
  print_network_status();

  client.setServer(mqtt_server, 1883);
}

  
void loop() {

  if (!client.connected()) {
    mqtt_conection();
  }
  // read the analog in value:
  sensorValue_MG = analogRead(analogInPin_MG);
  sensorValue_IG = analogRead(analogInPin_IG);
  sensorValue_PG = analogRead(analogInPin_PG);
  sensorValue_PD = analogRead(analogInPin_PD);
  sensorValue_ID = analogRead(analogInPin_ID);
  sensorValue_MD = analogRead(analogInPin_MD);

  // maping the résult (valeur min et max en entrée à calibrer)
  // ouverture des d
  outputValue_MG  = map(sensorValue_MG, 3000,3250, 0,100); // puissance
  outputValue_IG  = map(sensorValue_IG, 3150,3600, 0,100); // puissance
  outputValue_PG  = map(sensorValue_PG, 3000,3300, 0,100); // puissance
  outputValue_PD  = map(sensorValue_PD, 2800,3150, 0,100); // valeur () fléchi ou non 
  outputValue_ID  = map(sensorValue_ID, 2900,3400, 0,100);
  outputValue_MD  = map(sensorValue_MD, 2800,3400, 0,100);
  // print the results to the Serial Monitor:
  
  Serial.print("sensor = ");
  Serial.print(sensorValue_MG);
  Serial.print(" ");
  Serial.print(sensorValue_IG);
  Serial.print(" "); 
  Serial.print(sensorValue_PG);
  Serial.print(" ");
  Serial.print(sensorValue_PD);
  Serial.print(" ");
  Serial.print(sensorValue_ID);
  Serial.print(" ");
  Serial.print(sensorValue_MD);
  Serial.print("\t output = ");
  Serial.print(outputValue_MG);
  Serial.print(" ");
  Serial.print(outputValue_IG);
  Serial.print(" ");
  Serial.print(outputValue_PG);
  Serial.print(" ");
  Serial.print(outputValue_PD);
  Serial.print(" ");
  Serial.print(outputValue_ID);
  Serial.print(" ");
  Serial.print(outputValue_MD);
  Serial.println();

  controle(outputValue_MG,outputValue_IG,outputValue_PG,outputValue_PD,outputValue_ID,outputValue_MD);
  client.publish(TOPIC_GANT, getJSONString_voiture(commande,ordre,pwm, lieu).c_str());
 
  // wait 200 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(1000);
}
