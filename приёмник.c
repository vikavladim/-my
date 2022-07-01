#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#define BUTTONPIN 3

RF24 radio(9, 10); 

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; 

int prevButtonState=0;

void setup() {
  Serial.begin(9600); 

  radio.begin(); 
  radio.setAutoAck(1);         
  radio.setRetries(0, 15);  
  radio.enableAckPayload();  
  radio.setPayloadSize(32);

  radio.openReadingPipe(1, address[0]);
  radio.openWritingPipe(address[1]);
  
  radio.setChannel(0x60);

  radio.setPALevel (RF24_PA_MAX); 
  radio.setDataRate (RF24_250KBPS); 

  radio.powerUp(); 
  radio.startListening();  

  pinMode(BUTTONPIN, INPUT);
  prevButtonState=digitalRead(BUTTONPIN);
}



void loop() {
  byte pipeNo = 0, gotByte;
  int buttonState=digitalRead(BUTTONPIN);
  delay(300);
      Serial.println(F("Send request..."));
      radio.stopListening();
      uint8_t num=buttonState==HIGH?1:0;
      radio.write(&num, sizeof(num));
      radio.startListening();
}
