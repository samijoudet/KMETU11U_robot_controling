/*
 * "Standard" ?? JSON representation of the ESP 
 * breadboard.
 * File : format_json/format_json.ino
 * Author : GM
 */

#include <ArduinoJson.h>

/*========================================================*/

void getStaticJsonDocument_frombytes(byte* message ){
  
  StaticJsonDocument<1000> doc;

  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
  }
  commande = doc["status"]["commande"];
  ordre = doc["status"]["ordre"];
  dutyCycle = doc["status"]["pwm"];
}



String getJSONString_Temp(){
  /*
   * put all relevant data from esp in a "json formatted" String
   */
  StaticJsonDocument<1000> jsondoc;
  jsondoc["status"]["temp"] = getTemp();
  jsondoc["status"]["lieu"] = lieu;

  jsondoc["info"]["loc"] = LOCATION;
  jsondoc["info"]["user"] = IDENTIFIER;
  jsondoc["info"]["uptime"] = getUptime();
  
  String data = "";
  serializeJson(jsondoc, data);
  return data;
}
