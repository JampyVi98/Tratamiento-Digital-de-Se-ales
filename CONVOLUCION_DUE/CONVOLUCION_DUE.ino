/*
float32_t
uint32_t
*/
#define ARM_MATH_CM3
#include <arm_math.h>
#define tam_imputSignal 320
#define tam_impulse 29
extern float32_t InputSignal_1kHz_15kHz[tam_imputSignal];
extern float32_t  Impulse_response[tam_impulse];
float32_t prom, desv, var;
float32_t sigOut[tam_imputSignal+tam_impulse];
uint32_t i=0;


void setup() {
  Serial.begin(9600);
  arm_mean_f32(&InputSignal_1kHz_15kHz[0],tam_imputSignal,&prom);
  arm_var_f32(&InputSignal_1kHz_15kHz[0],tam_imputSignal,&var);
  arm_var_f32(&InputSignal_1kHz_15kHz[0],tam_imputSignal,&desv);
  Serial.println(prom);
  Serial.println(var);
  Serial.println(desv);
}

void plot(float32_t *sigIn, uint32_t tamSig){
  uint32_t i;
  for(i = 0;i<tamSig;i++){
    Serial.println(sigIn[i]*100);
    delay(10);
  }
}

void conv(float32_t *sigIn, float32_t *sigIm, uint32_t tamSig, uint32_t tamIm){
  uint32_t i=0,j=0;
  for(i=0;i<tamSig;i++){
    for(j=0;j<tamIm;i++){
      sigOut[i+j]=sigOut[i+j] + sigIn[i]*sigIm[j];
    }
  }
}

void loop() {
//  conv(InputSignal_1kHz_15kHz,Impulse_response, tam_imputSignal, tam_impulse);
  arm_conv_f32(&InputSignal_1kHz_15kHz[0], tam_imputSignal,
            &Impulse_response[0], tam_impulse, &sigOut[0]);
  plot(sigOut,tam_imputSignal+tam_impulse);
}
