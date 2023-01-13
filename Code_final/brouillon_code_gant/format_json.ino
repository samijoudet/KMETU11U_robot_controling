/*
 * "Standard" ?? JSON representation of the ESP 
 * breadboard.
 * File : format_json/format_json.ino
 * Author : GM
 */

#include <ArduinoJson.h>

/*========================================================*/

String getJSONString_voiture(int commande, int ordre,int pwm, String lieu){
  /*
   * put all relevant data from esp in a "json formatted" String
   */
  StaticJsonDocument<1000> jsondoc;
  jsondoc["status"]["commande"] = commande;
  jsondoc["status"]["ordre"] = ordre;
  jsondoc["status"]["pwm"] = pwm;
  jsondoc["status"]["lieu"] = lieu;

  jsondoc["info"]["loc"] = LOCATION;
  jsondoc["info"]["user"] = IDENTIFIER;
  jsondoc["info"]["uptime"] = getUptime();
  
  String data = "";
  serializeJson(jsondoc, data);
  return data;
}
