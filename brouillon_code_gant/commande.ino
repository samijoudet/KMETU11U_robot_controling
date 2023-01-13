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


int out_value_to_pwm(int output_value){
  int val = map(output_value,50,100,200,255);
  if (val > 255){
    val=255;
    } 
  return val;
}

void controle (int V_MG,int V_IG,int V_PG,int V_PD,int V_ID,int V_MD){    // prend les valeurs du gant et les traite ??
  // controle -> 0: pause , 1 : temperature , 2 : camera , 3 : voiture
  // ordre -> 0:arret 1,2,3 : avant (forward,left,right) 4,5,6 : arrière ((forward,left,right)) pour la voiture; autre pour la caméra 
  // pwm -> puissance des moteurs
  
  if (V_MG > 60 ){ // commande température
    commande = 1;
    pwm =0;
    ordre = 1;
   }
  else if (V_IG >50 ){ // commande caméra, a completer
    commande = 2;
    //a completer
    pwm =out_value_to_pwm(V_PG);
    ordre = 1;
    }
  else if (V_PG>50){ // commande voiture
    commande=3;
    ordre=1;
    if (V_PD > 50){ordre += 3;}
    if (V_ID > 50){
      ordre++;
      if (V_MD > 50){
        ordre++;
      }
    }
    pwm =out_value_to_pwm(V_PG);
    }
  else{
    commande=0;
    ordre=0;
  }
}
