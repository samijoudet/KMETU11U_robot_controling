/* PINS */

int out_value_to_pwm(int output_value);

// 0:arret 1,2,3 : avant (forward,left,right) 4,5,6 : arrière ((forward,left,right))
void controle(int V_MG,int V_IG,int V_PG,int V_PD,int V_ID,int V_MD);
