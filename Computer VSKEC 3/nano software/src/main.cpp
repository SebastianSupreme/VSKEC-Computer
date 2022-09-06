 //Projekt Computer VSKEC 3
 //Version 2.0
 //Der Computer VSKEC 3 wurde von Sebastian Köller entwickelt, also gebaut und programmiert.
 //Programmliste: RGB-LED, Messen, Musik, Rechner, Editor

#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial ss(11, 10);

//Variablen

//Für die Hardware
const byte lightSensorPin = A3;
int lightSensorValue;
const byte tempSensorPin = A7;
int tempSensorValue;
const byte piezoPin = 7;
int frequenz = 0;
const byte greenPin = 6;
const byte bluePin = 5;
const byte redPin = 4;
byte red = 0;
byte green = 0;
byte blue = 0;

const byte potiPin = A4;
byte potiState;
const byte backPin = 8;
byte backState = 0;
const byte continuePin = 9;
byte continueState = 0;
const byte actionPin = 2;
byte actionState = 0;
const byte enterPin = 3;
byte enterState = 0;

//Für die Software
boolean rgbLed = false, messungen = false, musik = false, rechner = false, editor = false;
boolean redFertig = false, blueFertig = false, greenFertig = false;
boolean sendPoti = false;
char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

//Serial
String input;

//Functions
void reset();

void setup() {
  
  ss.begin(4800);

  pinMode(backPin, INPUT);
  pinMode(continuePin, INPUT);
  pinMode(actionPin, INPUT);
  pinMode(enterPin, INPUT);
  pinMode(tempSensorPin, INPUT);
  pinMode(lightSensorPin, INPUT);
  pinMode(piezoPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(potiPin, INPUT);
  digitalWrite(redPin,0);
  digitalWrite(greenPin,0);
  digitalWrite(bluePin,0);
  noTone(piezoPin);
}

void loop() {

  backState = digitalRead(backPin);
  continueState = digitalRead(continuePin);
  actionState = digitalRead(actionPin);
  enterState = digitalRead(enterPin);
  potiState = map(analogRead(potiPin),0,1023,0,255);

  tempSensorValue = analogRead(tempSensorPin);
  lightSensorValue = analogRead(lightSensorPin);

if(ss.available()>0){
  input = ss.readString();
}

//Eingaben senden
if(rgbLed == false && messungen == false && musik == false && rechner == false && editor == false){
if(backState == 1){
  ss.write("backState 1");
}else if(continueState == 1){
  ss.write("continueState 1");
}else if(actionState == 1){
  ss.write("actionState 1");
}else if(enterState == 1){
  ss.write("enterState 1");
}
}

//Bei Reset von Arduino Uno
if(input.indexOf("reset")==0){
 reset();//Resetet aber nur die Software
 
}else if(input.indexOf("rgb-led")==0){
  rgbLed = true;
  messungen = false;
  musik = false;
  rechner = false;
  editor = false;
  input = "";
}else if(input.indexOf("messungen")==0){
  rgbLed = false;
  messungen = true;
  musik = false;
  rechner = false;
  editor = false;
  input = "";
}else if(input.indexOf("musik")==0){
  rgbLed = false;
  messungen = false;
  musik = true;
  rechner = false;
  editor = false;
  input = "";
}else if(input.indexOf("rechner")==0){
 rgbLed = false;
  messungen = false;
  musik = false;
  rechner = true;
  editor = false;
  input = "";
}else if(input.indexOf("editor")==0){
   rgbLed = false;
  messungen = false;
  musik = false;
  rechner = false;
  editor = true;
  input = "";
}else if(input.indexOf("menu")==0){
  sendPoti = true;
}else if(input.indexOf("no menu")==0){
  sendPoti = false;
}

if(sendPoti == true){
  String s = "potiState " + String(potiState);
  char ca[15];
  s.toCharArray(ca, sizeof(ca));
  ss.write(ca);
  ss.flush();
  delay(500);
}

//Programme

//RGB-LED

if(rgbLed == true && messungen == false && musik == false && rechner == false && editor == false){

if(redFertig == false && greenFertig == false && blueFertig == false){
  
  if(backState == 1){
    if(red + 100 <=255){
      red += 100;
      ss.write(red);
      ss.flush();
    }
  }else if(continueState == 1){
     if(red + 10 <=255){
      red += 10;
      ss.write(red);
      ss.flush();
    }
  }else if(actionState == 1){
     if(red + 5 <=255){
      red += 5;
      ss.write(red);
      ss.flush();
    }
  }else if(enterState == 1){
     redFertig = true;
     ss.write(2);
     ss.flush();
  }
}else if(redFertig == true && greenFertig == false && blueFertig == false){
   if(backState == 1){
    if(green + 100 <=255){
      green += 100;
      ss.write(green);
      ss.flush();
    }
  }else if(continueState == 1){
     if(green + 10 <=255){
      green += 10;
      ss.write(green);
      ss.flush();
    }
  }else if(actionState == 1){
     if(green + 5 <=255){
      green += 5;
      ss.write(green);
     ss.flush();
    }
  }else if(enterState == 1){
     greenFertig = true;
     ss.write(3);
    ss.flush();
  }
}else if(redFertig == true && greenFertig == true && blueFertig == false){
   if(backState == 1){
    if(blue + 100 <=255){
      blue += 100;
      ss.write(blue);
      ss.flush();
    }
  }else if(continueState == 1){
     if(blue + 10 <=255){
      blue += 10;
      ss.write(blue);
      ss.flush();
    }
  }else if(actionState == 1){
     if(blue + 5 <=255){
      blue += 5;
      ss.write(blue);
      ss.flush();
    }
  }else if(enterState == 1){
     blueFertig = true;
     ss.write(4);
     ss.flush();
     analogWrite(redPin,red);
     analogWrite(greenPin,green);
     analogWrite(bluePin, blue);
  }
}
  
}

//Messungen

else if(rgbLed == false && messungen == true && musik == false && rechner == false && editor == false){

String s = "temp " + String(tempSensorValue);
String s2 = "licht " + String(lightSensorValue);
char c[9];
char c2[11];
s.toCharArray(c,sizeof(c));
s2.toCharArray(c2,sizeof(c2));
ss.write(c);
ss.flush();
delay(1000);
ss.write(c2);
ss.flush();
}

//Musik
else if(rgbLed == false && messungen == false && musik == true && rechner == false && editor == false){
 
     String fs = "frequenz " + String(frequenz);
      char ca[16];
      fs.toCharArray(ca,sizeof(ca));
      ss.write(ca);
      ss.flush();
      delay(500);
      
  if(backState == 1){
      frequenz += 1000;
  }else if(continueState == 1){
      frequenz += 100;
  }else if(actionState == 1){
      frequenz += 10;
  }else if(enterState == 1){
    while(enterState == 1){
      tone(piezoPin,frequenz);
      if(digitalRead(enterPin) == 0){
        enterState = 0;
      }
    }
    noTone(piezoPin);
  }
}
//Rechner
else if(rgbLed == false && messungen == false && musik == false && rechner == true && editor == false){

  backState = digitalRead(backPin);
  continueState = digitalRead(continuePin);
  actionState = digitalRead(actionPin);
  enterState = digitalRead(enterPin);
  potiState = map(analogRead(potiPin),0,1023,0,255);

if(backState == 1){
  ss.write('<');
  ss.flush();
}else if(continueState == 1){
  ss.write('>');
  ss.flush();
}else if(actionState == 1){
  ss.write('!');
  ss.flush();
}else if(enterState == 1){
  ss.write('=');
  ss.flush();
}else{
  ss.write(map(potiState,0,255,0,9));
  ss.flush();
}
  
}
//Editor
else if(rgbLed == false && messungen == false && musik == false && rechner == false && editor == true){

  backState = digitalRead(backPin);
  continueState = digitalRead(continuePin);
  actionState = digitalRead(actionPin);
  enterState = digitalRead(enterPin);
  potiState = map(analogRead(potiPin),0,1023,0,255);

if(backState == 1){
  ss.write('<');
  ss.flush();
}else if(continueState == 1){
  ss.write('>');
  ss.flush();
}else if(actionState == 1){
  ss.write('!');
  ss.flush();
}else if(enterState == 1){
  ss.write('=');
  ss.flush();
}else{
  ss.write(alphabet[map(potiState,0,255,0,25)]);
  ss.flush();
}

}

//-----------------------------------------------

delay(500);
}

void(* resetFunc) (void) = 0;
void reset(){
  resetFunc();
}