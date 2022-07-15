#include "Keyboard.h"
#include "Mouse.h"

#define encCLK  3
#define encDT  4
#define encSW  2

short int  flag = 0;
bool oldencCLK;
bool oldencDT;

int encEdo = 0;

void setup() 
{
  Serial.begin (9600);
  Keyboard.begin();
  Mouse.begin();
  
  pinMode (encCLK, INPUT);
  pinMode (encDT, INPUT);
  pinMode (encSW, INPUT_PULLUP);

  
  oldencCLK = digitalRead (encCLK);
  oldencDT = digitalRead (encDT);
}

bool detect_mov(bool *der, bool *izq);
void mueve_encoder(bool mov);

void encoderButtonPressed()
{
  Serial.println("presionado");
  Keyboard.print("Hello!");
}

void loop() 
{
  attachInterrupt(digitalPinToInterrupt(2),encoderButtonPressed,FALLING); 
  bool der = LOW, izq =LOW;
  
  if (detect_mov(&der, &izq) == true)
  {
     if(flag % 2 == 0)
     {
       mueve_encoder(der);
       flag = 0;
     }
     flag++;   
  }
  
  
}

void mueve_encoder(bool mov)
{
  
  Serial.println(flag);
  if(mov == HIGH)
  {
    //Serial.println("izquierda");
    Mouse.move(-10, 0);
  }
  else
  {
    //Serial.println("derecha");
    Mouse.move(10, 0);
  }
}


bool detect_mov(bool *der, bool *izq)
{
 bool newencCLK;
 bool newencDT;
 bool mov;
 
 if(oldencCLK == LOW && oldencDT == LOW)
 {
    newencDT = digitalRead (encDT);
    newencCLK = digitalRead (encCLK);
    mov = newencDT;
 }
 else
 { 
    newencCLK = digitalRead (encCLK);
    newencDT = digitalRead (encDT);
    mov = newencCLK;
 }
 
 if(oldencCLK == newencCLK && oldencDT == newencDT)
  return false;
 
 *der = mov;        
 oldencCLK = newencCLK;
 oldencDT = newencDT;
 return true;
}
