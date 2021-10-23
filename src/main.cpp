// Se utiliza un potenciometro en A0 para variar la frecuencia y duty 25% defecto

#include <Arduino.h>

#if defined(__AVR_ATmega328P__)
int pinPWM1=9;
int pinPWM2=10;
#elif defined(__AVR_ATmega2560__)
int pinPWM1 = 11;
int pinPWM2 = 12;
#endif
int frecuencia;
int TOP;
int escala;
int duty;     // 25%
int regDuty;


void setup() {
  Serial.begin(9600);
  pinMode(pinPWM1, OUTPUT);     // Configura pin PWM de salida 1 con TMR1
  pinMode(pinPWM2, OUTPUT);     // Congigura pin PWM de salida 2 con TMR1
  TCCR1A = _BV(COM1A1);         // 
  TCCR1B = _BV(WGM13)|_BV(CS10);      // Freq and phase correct ICR1 = TOP, prescaler 1
  escala = 1;
  frecuencia = 1000;
  duty = 25;

}

void loop() {
  frecuencia = analogRead(A0);
  TOP = (F_CPU / (2 * escala * frecuencia));
  regDuty = (25 * TOP) / 100;
  ICR1 = TOP;
  OCR1A = regDuty;
  delay(1000);
}