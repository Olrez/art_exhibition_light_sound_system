#include <SoftwareSerial.h>
#include "Adafruit_Soundboard.h"

// Choose any two pins that can be used with SoftwareSerial to RX & TX
#define SFX_TX 5
#define SFX_RX 6

// Connect to the RST pin on the Sound Board
#define SFX_RST 4

// Entradas
#define pinPir A1 // pin digital pir

// Salidas
#define pinOut1 9 // pin analogo pwm
#define pinOut2 10 // pin analogo pwm
#define pinOut3 11 // pin analogo pwm

// we'll be using software serial
SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);

// pass the software serial to Adafruit_soundboard, the second
// argument is the debug port (not used really) and the third 
// arg is the reset pin
Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);
// can also try hardware serial with
// Adafruit_Soundboard sfx = Adafruit_Soundboard(&Serial1, NULL, SFX_RST);

int modo=0;
uint8_t n = 0; //0

void setup() {
  // put your setup code here, to run once:
  pinMode(pinOut1, OUTPUT);
  pinMode(pinOut2, OUTPUT);
  pinMode(pinOut3, OUTPUT);
  Serial.begin(9600);
  // softwareserial at 9600 baud
  ss.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(digitalRead(pinPir)==HIGH){
    if (modo==0){
    modo=1;
    analogWrite(pinOut1, 128);  // enciende luces
    analogWrite(pinOut2, 128);  // enciende luces
    analogWrite(pinOut3, 128);  // enciende luces
    delay(10000); // espere 10 segundos (10000)
    sfx.playTrack(n);
    }  
    //aquí lógica de audio
    sfx.playTrack(n);
   if(modo==1){
   modo=2; 
  
    for (int i=128; i < 256;i++){ // loop de reducción de iluminación paulatina
      analogWrite(pinOut1, i);
      analogWrite(pinOut2, i);
      analogWrite(pinOut3, i);
      
      delay(130); //(60) 15 segundos
    }//end for
  }//end if
    analogWrite(pinOut1, 255);
    analogWrite(pinOut2, 255);
    analogWrite(pinOut3, 255);
   // sfx.playTrack(n);
    delay(1);
  }//end while
  while(digitalRead(pinPir)==LOW){ 

    // aquí lógica de apagado de audio
    sfx.stop();
    
    analogWrite(pinOut1, 255);
    analogWrite(pinOut2, 255);
    analogWrite(pinOut3, 255);
    modo=0;
    delay(1);
  }//end while
  }//end loop

