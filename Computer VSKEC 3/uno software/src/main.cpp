//Projekt Computer VSKEC 3
//Version 2.0
//Der Computer VSKEC 3 wurde von Sebastian Köller entwickelt, also gebaut und programmiert.
//Programmliste: RGB-LED, Messen, Musik, Rechner, Editor

#include <Arduino.h>
#include <LiquidCrystal.h>
LiquidCrystal screen(7, 6, 5, 4, 3, 2);
#include <SuperSerial.h>
SuperSerial superserial;
#include <SoftwareSerial.h>
SoftwareSerial softwareserial(10, 11);

//Variablen

//Für die Software

boolean menu = true, menuClose = true, credits = false;
boolean rgbLed = false, messungen = false, musik = false, rechner = false, editor = false;
boolean red = true,green = false, blue = false;
int redC = 0, greenC = 0, blueC = 0;
byte Gue[] = {B01010, B00000, B10001, B10001, B10001, B10001, B01110, B00000};
byte celsiusCircle[] = {B01110, B01010, B01110, B00000, B00000, B00000, B00000, B00000};
byte koe[] = {B01010, B00000, B01110, B10001, B10001, B10001, B01110, B00000};
boolean rgbEinleitung = true, messEinleitung = true, musikEinleitung = true, rechnerEinleitung = true, editorEinleitung = true;
boolean creditsEinleitung = true;
//Welcher Knopf wurde am Nano gedrückt?
boolean backButton = false,continueButton = false;
boolean actionButton = false,enterButton = false;
float tempW = 0.0;
int lichtW = 0;
boolean lw = false, tw = true;
int frequenz = 0;
String DatenFuerEmpfang = "";
int menuVal;
boolean flushen = true;
byte digit;
String digitString;
String getZahl1 = "";
String getZahl2 = "";
boolean zahl1Fertig = false;
boolean zahl2Fertig = false;
boolean calculateOperatorFertig = false;
String calculateOperator = "";
double zahl1;
double zahl2;
double ergebnis;
boolean ergebnisFertig = false;
boolean rechnerStart = false;
char letter;
char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
String notiz = "";
boolean noteFinished = false;

  //Serial
  String input = "";
  String nanoinput = "";
  int nanointput;
  char nanocharput;
  
//Functions
int Poti(int minimum, int maximum);
void SoftSerialFlush();
void reset();

  void setup() {
  
  Serial.begin(9600);
  softwareserial.begin(4800);
  screen.begin(16,2);
  
  screen.clear();
  screen.setCursor(0,0);
  screen.print("Computer VSKEC 3");
  screen.setCursor(0,1);
  screen.print("Programm: ");
  screen.createChar(0, Gue);
  screen.createChar(1, celsiusCircle);
  screen.createChar(2, koe);
  softwareserial.write("reset");
  softwareserial.flush();
  delay(500);
  }
  
  void loop() {

  //SuperSerial
  if(Serial.available()>0){
  input = superserial.readString();
  if(input != "Verbindungstest Anfrage" && input != "empfangen"
  && input != "nicht empfangen" && input != "rgb-led"
  && input != "messen" && input != "musik" && input != "credits"
  && input != "rechner" && input != "editor" && input != "menu"){
    screen.clear();
    screen.setCursor(0,0);
    screen.print(input);
    delay(1500);
    if(menu == true){
      delay(1000);
      screen.clear();
  screen.setCursor(0,0);
  screen.print("Computer VSKEC 3");
  screen.setCursor(0,1);
  screen.print("Programm: ");
    }
  }
  }

if(input == "Verbindungstest Anfrage"){
  superserial.write("Verbindungstest Antwort");
  delay(2500);
  
}else if(input == "empfangen"){
  superserial.write(DatenFuerEmpfang);
  delay(2500);
  
}else if(input == "menu"){
rgbLed = false;
messungen = false;
musik = false;
rechner = false;
editor = false;
menu = true;
reset();

}else if(input == "rgb-led"){
rgbLed = true;
menu = false;
if(flushen == true){
SoftSerialFlush();
flushen = false;
}

}else if(input == "messen"){
messungen = true;
menu = false;
if(flushen == true){
SoftSerialFlush();
flushen = false;
}

}else if(input == "musik"){
musik = true;
menu = false;
if(flushen == true){
SoftSerialFlush();
flushen = false;
}

}else if(input == "rechner"){
rechner = true;
menu = false;

}else if(input == "editor"){
editor = true;
menu = false;

}else if(input == "credits"){
credits = true;
menu = false;

}

if(menu == false){
  if(menuClose == true){
    SoftSerialFlush();
    menuClose = false;
  }
  }
  
  //SoftwareSerial
  if(softwareserial.available()>0){
    if(rgbLed == true){
     nanointput = softwareserial.read();
    }else if(messungen == true){
      nanoinput = softwareserial.readString();
    }else if(musik == true){
      nanoinput = softwareserial.readString();
    }else if(rechner == true){
       nanocharput = softwareserial.read();
    }else if(editor == true){
      nanocharput = softwareserial.read();
    }else{
     nanoinput = softwareserial.readString();
    }
  }
 

  //nanoinput auswerten
if(nanoinput.indexOf("backState")==0){
  nanoinput = "";
  backButton = true;
}else if(nanoinput.indexOf("continueState")==0){
  nanoinput = "";
  continueButton = true;
}else if(nanoinput.indexOf("actionState")==0){
  nanoinput = "";
  actionButton = true;
}else if(nanoinput.indexOf("enterState")==0){
  nanoinput = "";
  enterButton = true;
}

if(credits == true){
   screen.clear();
  screen.setCursor(0,0);
  if(creditsEinleitung == true){
    creditsEinleitung = false;
    screen.print("Credits");
    delay(1500);
    screen.clear();
    screen.setCursor(0,0);
  }
  screen.print("VSKEC 3 von");
  screen.setCursor(0,1);
  screen.print("Sebastian K");
  screen.write(byte(2));
  screen.print("ller");
  DatenFuerEmpfang = "VSKEC 3 von Sebastian Köller";
}

//Wenn im Menü ein Knopf gedrückt, kein Menü mehr
if(menu == true){

if(actionButton == true){
  menu = false;
  actionButton = false;
  credits = true;
}
  
 if(enterButton == true){
  enterButton = false;
  
  switch(menuVal){
    case 1:menu = false;rgbLed = true;messungen = false;musik = false;rechner = false;editor = false;break;
    case 2:menu = false;rgbLed = false;messungen = true;musik = false;rechner = false;editor = false;break;
    case 3:menu = false;rgbLed = false;messungen = false;musik = true;rechner = false;editor = false;break;
    case 4:menu = false;rgbLed = false;messungen = false;musik = false;rechner = true;editor = false;break;
    case 5:menu = false;rgbLed = false;messungen = false;musik = false;rechner = false;editor = true;break;
  }
  
}
}

if(menu == true){
screen.setCursor(11,1);
menuVal = Poti(1,5);
screen.print(menuVal);
screen.print("     ");
}else{

//Programme

//RGB-LED
if(rgbLed == true){
  
if(rgbEinleitung == true){
screen.clear();
screen.setCursor(0,0);
screen.print("1: RGB-LED");

softwareserial.write("rgb-led");
softwareserial.flush();
delay(1500);

screen.clear();
screen.setCursor(0,0);
screen.print("ROT: GR");
screen.write(byte(0));
screen.print("N: BLAU:");
rgbEinleitung = false;
redC = 0;
greenC = 0;
blueC = 0;
}

if(nanointput == 2){
red = false;
green = true;
nanointput = 0;
}else if(nanointput == 3){
  green = false;
  blue = true;
  nanointput = 0;
}else if(nanointput == 4){
  red = true;
  green = true;
  blue = true;
  nanointput = 0;
}

screen.setCursor(0,0);
screen.print("ROT: GR");
screen.write(byte(0));
screen.print("N: BLAU:");
screen.setCursor(0,1);
screen.print(redC);
screen.setCursor(6,1);
screen.print(greenC);
screen.setCursor(12,1);
screen.print(blueC);

DatenFuerEmpfang = "R: " + String(redC) + " G: " + String(greenC)
+ " B: " + String(blueC);

if(red == true && green == false && blue == false){
screen.setCursor(0,1);
if(nanointput > redC){
  redC = nanointput;
}
screen.print(redC);
}else if(red == false && green == true && blue == false){
  screen.setCursor(6,1);
  if(nanointput > greenC){
  greenC = nanointput;
}
  screen.print(greenC);
}else if(red == false && green == false && blue == true){
  screen.setCursor(12,1);
  if(nanointput > blueC){
  blueC = nanointput;
}
  screen.print(blueC);
}




//Messungen
}else if(messungen == true){
if(messEinleitung == true){
screen.clear();
screen.setCursor(0,0);
screen.print("2: Messungen");
softwareserial.write("messungen");
softwareserial.flush();
delay(1500);
screen.clear();
screen.setCursor(0,0);
messEinleitung = false;
}

if(nanoinput.indexOf("temp")==0){
  String tempV = nanoinput.substring(nanoinput.indexOf(' ')+1,nanoinput.length());
    tempW = (((tempV.toInt() / 1024.0) * 5.0) - 0.5) * 100.0;
}else if(nanoinput.indexOf("licht")==0){
  String lichtV = nanoinput.substring(nanoinput.indexOf(' ')+1, nanoinput.length());
lichtW = lichtV.toInt() / 4;
}

DatenFuerEmpfang = "Temp: " + String(tempW) + " Grad C, Licht: " + String(lichtW) + " RGB";

screen.setCursor(0,0);
screen.print("Temp: ");
screen.print(tempW);
screen.write(byte(1));
screen.print("C");
screen.print(" ");
screen.setCursor(0,1);
screen.print("Licht: ");
screen.print(lichtW);
screen.print(" RGB");

//Musik
}else if(musik == true){
if(musikEinleitung == true){
screen.clear();
screen.setCursor(0,0);
screen.print("3: Musik");
softwareserial.write("musik");
softwareserial.flush();
delay(1500);
screen.clear();
screen.setCursor(0,0);
musikEinleitung = false;
screen.print("Frequenz:");
}

screen.setCursor(0,0);
screen.print("Frequenz:");

if(nanoinput.indexOf("frequenz") == 0){
String frequenzString = nanoinput.substring(nanoinput.indexOf(' ')+1,nanoinput.length());
frequenz = frequenzString.toInt();
}

DatenFuerEmpfang = "Frequenz: " + String(frequenz) + " Hz";

screen.setCursor(0,1);
screen.print(frequenz);
screen.print(" Hz");



//Rechner
}else if(rechner == true){

if(rechnerEinleitung == true){
  rechnerEinleitung = false;
screen.clear();
screen.setCursor(0,0);
screen.print("4: Rechner");
  softwareserial.write("rechner");
  softwareserial.flush();
  delay(1500);
}
    if (ergebnisFertig == false) {
      screen.clear();
      screen.setCursor(0, 0);
      screen.print(digit);
      screen.print(" ");
      screen.print(getZahl1);
      screen.print(" ");
      screen.print(calculateOperator);
      screen.print(" ");
      screen.print(getZahl2);
    }


if(nanocharput == '<'){
 backButton = true;
}else if(nanocharput == '>'){
  continueButton = true;
}else if(nanocharput == '!'){
  actionButton = true;
}else if(nanocharput == '='){
  enterButton = true;
}else{
    digit = nanocharput;
}

    
    if (actionButton == true) {
      actionButton = false;

        if (zahl1Fertig == false && calculateOperatorFertig == false && zahl2Fertig == false) {
          digitString = String(digit);
          getZahl1 += digitString;
        }
        else if (zahl1Fertig == true && calculateOperatorFertig == true && zahl2Fertig == false) {
          digitString = String(digit);
          getZahl2 += digitString;
        }
        else if (zahl1Fertig == true && calculateOperatorFertig == false && zahl2Fertig == false) {
          calculateOperatorFertig = true;
          calculateOperator = "*";
        }
    }

    if (backButton == true) {
      backButton = false;
      if (zahl1Fertig == true && calculateOperatorFertig == true && zahl2Fertig == false) {
        getZahl2 += "-";
      }
      if (zahl1Fertig == true && calculateOperatorFertig == false && zahl2Fertig == false) {
        calculateOperator = "+";
        calculateOperatorFertig = true;
      }
      if (zahl1Fertig == false && calculateOperatorFertig == false && zahl2Fertig == false) {
        getZahl1 += "-";
      }

    }
    if (continueButton == true) {
      continueButton = false;
      if (zahl1Fertig == true && calculateOperatorFertig == true && zahl2Fertig == false) {
        getZahl2 += ".";
      }
      if (zahl1Fertig == true && calculateOperatorFertig == false && zahl2Fertig == false) {
        calculateOperator = "-";
        calculateOperatorFertig = true;
      }
      if (zahl1Fertig == false && calculateOperatorFertig == false && zahl2Fertig == false) {
        getZahl1 += ".";
      }
    }

    if (enterButton == true) {
      enterButton = false;
        if (zahl1Fertig == true && calculateOperatorFertig == true && zahl2Fertig == true) {
          ergebnisFertig = true;
          if (calculateOperator == "+") {
            ergebnis = zahl1 + zahl2;
          } else if (calculateOperator == "-") {
            ergebnis = zahl1 - zahl2;
          } else if (calculateOperator == "*") {
            ergebnis = zahl1 * zahl2;
          } else if (calculateOperator == "/") {
            ergebnis = zahl1 / zahl2;
          }
          screen.setCursor(0, 0);
          screen.print(zahl1);
          screen.print(" ");
          screen.print(calculateOperator);
          screen.print(" ");
          screen.print(zahl2);
          screen.setCursor(0, 1);
          screen.print("= ");
          screen.print(ergebnis);

 String s = String(zahl1) + " " + String(calculateOperator) + " " + String(zahl2) + " = " + String(ergebnis);
 DatenFuerEmpfang = s;
          
        }
        if (zahl1Fertig == true && calculateOperatorFertig == true && zahl2Fertig == false) {
          zahl2Fertig = true;
          zahl2 = getZahl2.toDouble();
        }
        if (zahl1Fertig == true && calculateOperatorFertig == false && zahl2Fertig == false) {
          calculateOperatorFertig = true;
          calculateOperator = "/";
        }
        if (zahl1Fertig == false && calculateOperatorFertig == false && zahl2Fertig == false) {
          zahl1Fertig = true;
          zahl1 = getZahl1.toDouble();
        }
        
      }

  //Texteditor
}else if(editor == true){
  
  if(editorEinleitung == true){
  editorEinleitung = false;
screen.clear();
screen.setCursor(0,0);
screen.print("5: Texteditor");
  softwareserial.write("editor");
  softwareserial.flush();
  delay(1500);
}

if (noteFinished == false) {
      screen.clear();
      screen.setCursor(0, 0);
      screen.print(letter);
      screen.print(" ");
      screen.print(notiz);
    }

if(nanocharput == '<'){
  notiz = notiz.substring(0,notiz.length()-1);
}else if(nanocharput == '>'){
  notiz += " ";
}else if(nanocharput == '!'){
  notiz += letter;
}else if(nanocharput == '='){
  noteFinished = true;
  screen.clear();
  screen.setCursor(0,0);
  screen.print(notiz);
  DatenFuerEmpfang = notiz;
}else{
    letter = nanocharput;
}

}
}
//-------------------------------------------------------------------------------------

  delay(500);
}



void(* resetFunc) (void) = 0;
void reset(){
  resetFunc();
}

void SoftSerialFlush(){
    softwareserial.write("no menu");
    softwareserial.flush();
    delay(1500);
    while(softwareserial.available()>0){
      char c = softwareserial.read();
    }
}

int Poti(int minimum, int maximum){
softwareserial.write("menu");
delay(1500);
String s;
byte b;
if(nanoinput.indexOf("potiState")==0){
  s = nanoinput.substring(nanoinput.indexOf(" ")+1,nanoinput.length());
  b = (byte) s.toInt();
}
b = map(b,0,255,minimum,maximum);
    return b;
  }