#include "Keyboard.h"
#include "Mouse.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const unsigned char menu_bmp [] PROGMEM = {
  // 'Menu, 128x32px
  0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 
  0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 
  0x00, 0x1f, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xf8, 0x00, 
  0x03, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xc0, 
  0x01, 0xff, 0xff, 0xff, 0x80, 0x00, 0x07, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xff, 0x80, 
  0x00, 0xff, 0xff, 0xfc, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x07, 0xff, 0xff, 0x00, 
  0x10, 0x7f, 0xff, 0xe0, 0x03, 0xf8, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0xff, 0xff, 0x08, 
  0x18, 0x3f, 0xff, 0x00, 0x7f, 0xf0, 0x0e, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x1f, 0xfe, 0x18, 
  0x1e, 0x1f, 0xfc, 0x03, 0xff, 0xff, 0x1c, 0x7f, 0xff, 0xff, 0xff, 0xf9, 0xf8, 0x07, 0xfc, 0x38, 
  0x1f, 0x1f, 0xf8, 0x1f, 0xff, 0xff, 0x18, 0x73, 0xff, 0xff, 0xff, 0xf3, 0xff, 0x03, 0xf8, 0x78, 
  0x9f, 0x9f, 0xf0, 0x7f, 0xff, 0xff, 0x10, 0x61, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xc1, 0xf8, 0xf9, 
  0xff, 0xff, 0xe1, 0xff, 0xff, 0xfe, 0x00, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 
  0xff, 0xff, 0xc3, 0xff, 0xff, 0xfe, 0x08, 0x83, 0xc0, 0xf1, 0xc7, 0x88, 0xff, 0xf8, 0x7f, 0xff, 
  0xff, 0xff, 0xc7, 0xff, 0xff, 0xfe, 0x18, 0x03, 0x08, 0xf1, 0x8f, 0x18, 0xff, 0xfc, 0x7f, 0xff, 
  0xff, 0xff, 0xc7, 0xff, 0xff, 0xfc, 0x18, 0x47, 0x18, 0xf0, 0x0f, 0x18, 0xff, 0xfc, 0x7f, 0xff, 
  0xff, 0xff, 0xc7, 0xff, 0xff, 0xfc, 0x30, 0xc7, 0x1f, 0xe0, 0x0e, 0x11, 0xff, 0xfc, 0x7f, 0xff, 
  0xff, 0xff, 0xc3, 0xff, 0xff, 0xfc, 0x71, 0x8f, 0x1f, 0xe1, 0x1e, 0x31, 0xff, 0xf8, 0x7f, 0xff, 
  0xff, 0xff, 0xe1, 0xff, 0xff, 0xf8, 0xf3, 0x80, 0x80, 0x07, 0x00, 0x00, 0x1f, 0xf0, 0xff, 0xff, 
  0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xff, 0xff, 
  0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 
  0xff, 0xff, 0xfc, 0x03, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xf8, 0x07, 0xff, 0xff, 
  0x9f, 0x1f, 0xff, 0x00, 0x7f, 0xff, 0xff, 0xff, 0x80, 0x3f, 0xff, 0x00, 0x00, 0x1f, 0xf9, 0xf9, 
  0x1e, 0x1f, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf8, 0xf8, 
  0x1c, 0x3f, 0xff, 0xfc, 0x00, 0x1f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xf8, 0x78, 
  0x18, 0x7f, 0xff, 0xff, 0x80, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xfc, 0x18, 
  0x10, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xfe, 0x08, 
  0x00, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 
  0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xff, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0x80, 
  0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xc0, 
  0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 
  0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 
  0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00
};



#define encCLK  5
#define encDT  6
#define encSW  7

#define pb1 4
#define pb2 8
#define pb3 9
#define pb4 10


short int  flag = 0;
bool menu_flag = true;

bool oldencCLK;
bool oldencDT;



void drawbitmap(int num_fig);

void encoderButtonPressed();
void detect_encoder_mov();
bool detect_dir(bool *der, bool *izq);
void mueve_encoder(bool mov);

void pressBoton1();
void pressBoton2();
void pressBoton3();
void pressBoton4();

void setup() 
{
  Serial.begin (9600);
  Keyboard.begin();
  Mouse.begin();

  // Iniciar pantalla OLED en la dirección 0x3C
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  else
    Serial.println("Pantalla iniciada");
    
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Limpir buffer
  display.clearDisplay();
  display.display();
  
  pinMode (encCLK, INPUT);
  pinMode (encDT, INPUT);
  pinMode (encSW, INPUT_PULLUP);

  pinMode (pb1, INPUT_PULLUP);
  pinMode (pb2, INPUT_PULLUP);
  pinMode (pb3, INPUT_PULLUP);
  pinMode (pb4, INPUT_PULLUP);
  
  oldencCLK = digitalRead (encCLK);
  oldencDT = digitalRead (encDT);
}


void encoderButtonPressed()
{
 
  Serial.println("presionado");
  //Keyboard.print("Hello!");
  if(menu_flag == true)
  {
    drawbitmap(0);
    menu_flag = false;
  }
  else
  {
    display.invertDisplay(false);
    display.clearDisplay();
    display.display();
    menu_flag = true;
  }
}

bool old_encoderbutton = LOW;
bool old_pb1 = LOW;
bool old_pb2 = LOW;
bool old_pb3 = LOW;
bool old_pb4 = LOW;


void loop() 
{
  
  //attachInterrupt(digitalPinToInterrupt(encSW),encoderButtonPressed,FALLING); 
  bool new_enoderbutton = digitalRead(encSW);
  bool new_pb1 = digitalRead(pb1);
  bool new_pb2 = digitalRead(pb2);
  bool new_pb3 = digitalRead(pb3);
  bool new_pb4 = digitalRead(pb4);

  detect_encoder_mov();

  if(new_enoderbutton == HIGH && new_enoderbutton != old_encoderbutton)
    encoderButtonPressed();
  old_encoderbutton = new_enoderbutton;
  
  if(new_pb1 == HIGH && new_pb1 != old_pb1)
    pressBoton1();
  old_pb1 = new_pb1;
  
  if(new_pb2 == HIGH && new_pb2 != old_pb2)
    pressBoton2();
  old_pb2 = new_pb2;
  
  if(new_pb3 == HIGH && new_pb3 != old_pb3)
    pressBoton3();
  old_pb3 = new_pb3;
  
  if(new_pb4 == HIGH && new_pb4 != old_pb4)
    pressBoton4();
  old_pb4 = new_pb4;
}

void detect_encoder_mov()
{
  bool der = LOW, izq =LOW;
  if (detect_dir(&der, &izq) == true)
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


bool detect_dir(bool *der, bool *izq)
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



void pressBoton1()
{
  Serial.println("botn1");
}


void pressBoton2()
{
  Serial.println("botn2");
  
}


void pressBoton3()
{
  Serial.println("botn3");
  
}


void pressBoton4()
{
  Serial.println("botn4");
  
}



void drawbitmap(int num_fig)
{
  
  display.clearDisplay();
  display.invertDisplay(true);
  if(num_fig == 0)
    display.drawBitmap(0, 0, menu_bmp, 128, 32, 1);
  display.display();
  delay(1000);
}
