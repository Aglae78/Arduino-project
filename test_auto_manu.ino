#include <Servo.h>

int haut;
int gauche;
int droite;
int bas;
int axe=1;
int val1;
int ancien_val1=1;
int val2;
int ancien_val2=1;
int state;
int mode=1;
const int ButtonUDLR=3;
const int ButtonMode=4;
const int reglage=A4;  //potentiomètre
const int LDR1=0;   //gauche
const int LDR2=1;   //droite
const int LDR3=2;   //haut
const int LDR4=3;   //bas
Servo servoUD;
Servo servoLR;

void setup() {
  pinMode(ButtonUDLR,INPUT);
  pinMode(ButtonMode,INPUT);
  pinMode(reglage, INPUT);
  servoUD.attach(5);
  servoLR.attach(6);
  Serial.begin(9600);

}

void loop() {
  char   Mode;
  val1 = digitalRead(4);
  Serial.print(val1);
  Serial.print(" : ");
  Serial.println(ancien_val1);
  if (val1!= ancien_val1)   {
    if (val1 == HIGH) {
      if (mode == 1) {
        mode = 0;
      } else {
         mode = 1;
      }
    }
  }
  ancien_val1 = val1;
  delay(100);
  if (mode == 0) {
    Mode='M';
     Serial.println(Mode);    
    manualTracker();
   } 
   else { // mode automatic
    Mode = 'A';
    Serial.println(Mode);      
    automaticTracker(); 
    } 
}

void manualTracker(){
  Serial.print("val2 : ancien_etat2"
  val2   = digitalRead(3);
  if (val2 != ancien_val2) {
    if (val2   == HIGH) {
      if   (axe == 1) {
        axe = 0;
        delay(50);
      } else {
        axe = 1;
        delay(50);
      }
     }
  }
  Serial.print("l'axe est ");
  Serial.println(axe);
  ancien_val2 = val2;
  delay(50);
  if (axe == 0) {
    servoLR.write(map(analogRead(A4),   0, 1023, 0, 180));
  } else {
    servoUD.write(map(analogRead(A4),   0, 1023, 0, 180));
  } 
}
void automaticTracker(){
  gauche=analogRead(LDR1);
  droite=analogRead(LDR2);
  haut=analogRead(LDR3);
  bas=analogRead(LDR4);
  gauche=map(gauche,1,959,0,180);  //étalonnage fait
  droite=map(droite,0,977,0,180);  //étalonnage fait
  haut=map(haut,2,967,0,180);   //étalonnage fait
  bas=map(bas,0,978,0,180);   //étalonnage fait 
  int diffHB=haut-bas;
  int diffGD=gauche-droite;

  if (abs(diffHB)>2){
    if (diffHB<0){
      if (servoUD.read()<180){
        servoUD.write(servoUD.read()+1);    
      }
    }
    else{ 
      if (servoUD.read()>0){
        servoUD.write(servoUD.read()-1);
      }
    }
  }
  if (abs(diffGD)>2){
    if (diffGD<0){
      if (servoLR.read()<180){
        servoLR.write(servoLR.read()+1);
      }
    }
    else{ 
      if (servoLR.read()>0){
        servoLR.write(servoLR.read()-1);
      }
    }
  }
}
