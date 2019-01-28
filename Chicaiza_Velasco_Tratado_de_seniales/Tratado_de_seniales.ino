#define ARM_MATH_CM3
#include <arm_math.h>
#define tamSig1 640
#define tamSig2 500
#define tam_impulse 29
extern float32_t sig1[tamSig1];
extern float32_t sig2[tamSig2];
extern float32_t  Impulse_response[tam_impulse];
extern float32_t sigOut[tamSig1+tam_impulse];
float32_t desv1, var1, desv2, var2;
uint32_t i=0;

void setup() {
  Serial.begin(9600);
  des_estand();
  suma_resta();
  
}

void loop() {
  
  convolucion();
  plot(sigOut,tam_Sig1+tam_impulse);
}

void des_estand(){
  arm_var_f32(&sig1[0],tamSig1,&var1);
  desv1 = sqrt(var1);
  arm_var_f32(&sig2[0],tamSig2,&var2);
  desv2 = sqrt(var2);
  Serial.print("La varianza de la primera base de datos es de: ");
  Serial.println(var1);
  Serial.print("La desviación estandar de la primera base de datos es de: ");
  Serial.println(desv1);
  Serial.print("La varianza de la segunda base de datos es de: ");
  Serial.println(var2);
  Serial.print("La desviación estandar de la segunda base de datos es de: ");
  Serial.println(desv2);
}

void convolucion(){
  arm_conv_f32(&sig1[0], tamSig1,
            &Impulse_response[0], tam_impulse, &sigOut[0]);
}

void plot(float32_t *sigIn, uint32_t tamSig){
  uint32_t i;
  for(i = 0;i<tamSig;i++){
    Serial.println(sigIn[i]*100);
    delay(10);
  }
}

void suma_resta(){
  
}
