

void calibration_one(CAPTOR_PINS *capteur){
  if (capteur -> max == 1){
    capteur -> min = capteur -> sens;
    capteur -> max = capteur -> sens +1;
  }
  else{ 
    if (capteur -> min > capteur -> sens){capteur -> min = capteur -> sens;}
    if (capteur -> max < capteur -> sens){capteur -> max = capteur -> sens;}
  }
}

void calibration(){
  calibration_one(&MG);
  calibration_one(&IG);
  calibration_one(&PG);
  calibration_one(&PD);
  calibration_one(&ID);
  calibration_one(&MD);
}
