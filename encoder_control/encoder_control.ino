#define encCLK  3
#define encDT  2
#define encSW  4

bool flag = 0;
bool oldencCLK;
bool oldencDT;

int ledizq = 5;
int ledder = 6;
int encEdo = 0;

void setup() 
{
  Serial.begin (9600);
  
  pinMode (encCLK, INPUT);
  pinMode (encDT, INPUT);
  pinMode (encSW, INPUT_PULLUP);

  pinMode(ledizq, OUTPUT);
  pinMode(ledder, OUTPUT);

  
  oldencCLK = digitalRead (encCLK);
  oldencDT = digitalRead (encDT);
}

bool detect_mov(bool *der, bool *izq);



void loop() 
{
  
  bool der = LOW, izq =LOW;
  
  if (detect_mov(&der, &izq) == true)
  {
    if(flag == 0)
    {
      if(der == HIGH)
        Serial.println("izquierda");
      else
        Serial.println("derecha");
      digitalWrite(ledder, der);
      digitalWrite(ledizq, izq);
    }
    flag = !flag;
  }
  
}

bool detect_mov(bool *der, bool *izq)
{
 bool newencCLK = digitalRead (encCLK);
 bool newencDT = digitalRead (encDT);
 
 if(newencCLK == oldencCLK && newencDT == oldencDT)
    return false;
 
 
 if(oldencCLK == LOW)
 {
    if(newencCLK == LOW)
       *der = HIGH;
    else
      *der = LOW;
 }
 else
   if(oldencCLK == HIGH)
   {
      
      if(newencCLK == HIGH)
         *der = HIGH;
      else
        *der = LOW;
   }
 //Serial.println(*der);
 *izq = !*der;
 oldencCLK = digitalRead(encCLK);
 oldencDT = digitalRead(encDT);
 return true;
}
