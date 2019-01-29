#define ARM_MATH_CM3
#include <arm_math.h>
#define tamSig1 640
#define tamSig2 500
#define tam_impulse 29
extern float32_t sig1[tamSig1];
extern float32_t sig2[tamSig2];
extern float32_t Impulse_response[tam_impulse];
float32_t REX1 [tamSig1 / 2];
float32_t IDX1 [tamSig1 / 2];
float32_t REX2 [tamSig2 / 2];
float32_t IDX2 [tamSig2 / 2];
float32_t desv1, var1, desv2, var2;
uint32_t i = 0;

void setup() {
  Serial.begin(9600);
  //  des_estand();
  /*//FOURIER señal 1
    float32_t sigOut[tamSig1];
    fourier(&sig1[0], &REX1[0], &IDX1[0], tamSig1);
    get_tdf(&REX1[0], &IDX1[0], &sigOut[0], tamSig1);
    plot_tdf(sigOut, tamSig1);*/
  //FOURIER señal 2
    float32_t sigOut[tamSig2];
    fourier(&sig2[0], &REX2[0], &IDX2[0], tamSig2);
    get_tdf(&REX2[0], &IDX2[0], &sigOut[0], tamSig2);
    plot_tdf(sigOut, tamSig2);

}

void loop() {
  /*//CONVOLUCIÓN
    float32_t sigOut[tamSig1 + tam_impulse];
    arm_conv_f32(&sig1[0], tamSig1, &Impulse_response[0], tam_impulse, &sigOut[0]);
    plot(sigOut, tamSig1 + tam_impulse);*/
  /*//SUMA/RESTA Señal 1
    float32_t sigOut_sum[tamSig1];
    float32_t sigOut_res[tamSig1];
    suma(&sig1[0], &sigOut_sum[0], tamSig1);
    resta(&sig1[0], &sigOut_res[0], tamSig1);
    plot_doble(sigOut_sum, sigOut_res, tamSig1);*/
  /*//SUMA/RESTA Señal 2
    float32_t sigOut_sum[tamSig2];
    float32_t sigOut_res[tamSig2];
    suma(&sig2[0], &sigOut_sum[0], tamSig2);
    resta(&sig2[0], &sigOut_res[0], tamSig2);
    plot_doble(sigOut_sum, sigOut_res, tamSig1);*/
}

void des_estand() {
  arm_var_f32(&sig1[0], tamSig1, &var1);
  desv1 = sqrt(var1);
  arm_var_f32(&sig2[0], tamSig2, &var2);
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

void plot_doble(float32_t *sigIn1, float32_t *sigIn2, uint32_t tamSig) {
  uint32_t i;
  for (i = 0; i < tamSig; i++) {
    Serial.print(sigIn1[i] * 100 + 10);
    Serial.print(",");
    Serial.println(sigIn2[i] - 5);
    delay(10);
  }
}

void suma(float32_t *input, float32_t *output, uint32_t tam) {
  for (uint32_t i = 0; i < tam; i++) {
    output[i] = input[i] + output[i - 1];
  }
}

void resta(float32_t *input, float32_t *output, uint32_t tam) {
  for (uint32_t i = 0; i < tam; i++) {
    output[i] = input[i] - output[i - 1];
  }
}

void plot(float32_t *sigIn, uint32_t tamSig) {
  uint32_t i;
  for (i = 0; i < tamSig; i++) {
    Serial.println(sigIn[i] * 100);
    delay(10);
  }
}

void fourier(float32_t *input_sig, float32_t *sig_rex, float32_t *sig_idx, uint32_t tam) {
  uint32_t i, j, k;

  for (j = 0; j < tam / 2; j++) {
    sig_rex[j] = 0;
    sig_idx[j] = 0;
  }

  for (k = 0; k < tam / 2; k++) {
    for (i = 0; i < tam; i++) {
      sig_rex[k] = sig_rex[k] + input_sig[i] * cos(2 * PI * k * i / tam);
      sig_idx[k] = sig_idx[k] - input_sig[i] * sin(2 * PI * k * i / tam);
    }
  }
}

void get_tdf(float32_t *sig_rex, float32_t *sig_idx, float32_t *sigOut, uint32_t tam) {
  uint32_t i;
  for (i = 0; i < tam / 2; i++) {
    sigOut[i] = sqrt(pow(sig_rex[i], 2) + pow(sig_idx[i], 2));
  }
}

void plot_tdf(float32_t *sigIn, uint32_t tam) {
  uint32_t i;
  for (i = 0; i < tam / 2; i++) {
    Serial.println(sigIn[i]);
    delay(10);
  }
}
