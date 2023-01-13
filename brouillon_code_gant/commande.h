

struct CAPTOR_PINS 
{
  const int pin;     // pin d'entrée
  const String name; // nom du pin
  int sens;          // valeur enregistrer en entrer
  int out;           // valeur calibrer (min:0- max:100 lors de la calibration)
  int min;           // valeur minimum lors de la calibration
  int max;           // valeur maximum lors de la calibration
};


/* PINS */

int out_value_to_pwm(int output_value);

// 0:arret 1,2,3 : avant (forward,left,right) 4,5,6 : arrière ((forward,left,right))
void controle(int V_MG,int V_IG,int V_PG,int V_PD,int V_ID,int V_MD);
