#include "UnoJoy.h"

#define ch3 3
#define ch2 5
#define ch1 6
#define ch4 9

int u3 = 0,u6 = 0,u5 = 0,u9 = 0;
int chanelnumber = 16;
int chanel[16];
void setup() {
  setupPins();
  setupUnoJoy();
  //Serial.begin(9600);
}
int tolerancia(int valor,int p){
  int ult;
  switch(p)
  {
    case 3 : ult = u3;
    break;
    case 2 : ult = u5;
    break;
    case 1 : ult = u6;
    break;
    case 4 : ult = u9;
    break; 
  }
  
 if((valor > ult + 50) || (valor < ult - 50) )
 {

   
   switch(p)
  {
    case 3 : u3 = valor;
    break;
    case 2 : u5  = valor;
    break;
    case 1 :u6  = valor;
    break;
    case 4 :u9  = valor;
    break; 
  }
  ult = valor;
   
 }

int ret = map(ult, 1010, 1972, 0, 256);
     if(ret < 0 )
   {
     ret = 1;
   }
 return ret;
}
// the loop function runs over and over again forever
void loop() {
  dataForController_t controllerData = getControllerData();
  setControllerData(controllerData);
/*  
Serial.print(controllerData.leftStickX);
Serial.print("  ");
Serial.print(controllerData.leftStickY);
Serial.print("  ");
Serial.print(controllerData.rightStickX);
Serial.print("  ");
Serial.print(controllerData.rightStickY);
Serial.print("  ");

*/


//Serial.print(map(pulseIn(ch2,HIGH), 1010, 1972, 0, 1024) );
//Serial.print("  ");
//Serial.print(map(pulseIn(ch3,HIGH) , 1010, 1972, 0, 1024));
//Serial.print("  ");
//Serial.print(map(pulseIn(ch4,HIGH) , 1010, 1972, 0, 1024));
//Serial.print("  ");
 //Serial.print("\n");
}

void setupPins(void){
  // Set all the digital pins as inputs
  // with the pull-up enabled, except for the 
  // two serial line pins
  for (int i = 2; i <= 12; i++){
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }

}


dataForController_t getControllerData(void){

  dataForController_t controllerData = getBlankDataForController();

  //  8 bit number that we can use  
  controllerData.leftStickX = tolerancia(pulseIn(ch4,HIGH),4);
  controllerData.leftStickY = tolerancia(pulseIn(ch3,HIGH),3);
  controllerData.rightStickX = tolerancia(pulseIn(ch1,HIGH),1);
  controllerData.rightStickY = tolerancia(pulseIn(ch2,HIGH),2);
  // And return the data!
  return controllerData;
}

