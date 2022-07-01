#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include <iarduino_RTC.h>

#include <SPI.h>         
#include <iarduino_RTC.h>
#define LEDPIN 3
RF24 radio(9, 10); 

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};

byte counter;

unsigned long nextSession = 0;
unsigned long periodSession = 10000;

void setup() {
  Serial.begin(9600); 

  radio.begin();
  radio.setAutoAck(1);     
  radio.setRetries(0, 15);    
  radio.enableAckPayload();    
  radio.setPayloadSize(32);   

  radio.openReadingPipe(1, address[1]);   
  radio.openWritingPipe(address[0]); 
  radio.setChannel(0x60);

  radio.setPALevel (RF24_PA_MAX); 
  radio.setDataRate (RF24_250KBPS);
  radio.powerUp(); 
  radio.startListening();  
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
  counter = 0;
}

void loop() {
  byte pipeNo;
  unsigned long currentTick = millis();  
  boolean timeout = false; 
    uint8_t num=0;
  if(radio.available(&pipeNo)){
    radio.read(&num, sizeof( uint8_t));
    Serial.println(F("Request received!"));
    nextSession=currentTick;
  }  
  
  if(currentTick>=nextSession) {
    nextSession+=periodSession;
  radio.stopListening();
  radio.startListening();
  digitalWrite(LEDPIN, num==0?HIGH:LOW);
  }
}
