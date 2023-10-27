
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

uint8_t indoor1 = 6;
uint8_t indoor2 = 8;
uint8_t outdoor1 = 7;
uint8_t outdoor2 = 9;
uint8_t buzzer   = 12;
uint8_t sncar[]={22,23,24,25};
uint8_t outputgreen[]={26,27,28,29};
uint8_t outputred  []={30,31,32,33};
int count1 = 0;
boolean enablecount = false;
byte datax = 0b0000;
byte indexcar = 0x00;
LiquidCrystal_I2C lcd(0x27,16,2);
Servo myservo1;  
Servo myservo2; 
void setup() {
  Serial.begin(9600);
  Serial.println("program start");
 for(uint8_t index =  0; index<4; index+=1){
  pinMode(sncar[index],INPUT);
  pinMode(outputgreen[index],OUTPUT);
  pinMode(outputred[index],OUTPUT);
  digitalWrite(sncar[index],LOW);
  digitalWrite(outputgreen[index],LOW);
  digitalWrite(outputred[index],LOW);
 }
  pinMode(indoor1,INPUT);
  pinMode(indoor2,INPUT);
  pinMode(outdoor1,INPUT);
  pinMode(outdoor2,INPUT);
  pinMode(buzzer,OUTPUT);
  myservo1.attach(10);  
  myservo2.attach(11); 
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.clear();
  delay(100);
}
void loop() {
 /* static unsigned long timer1 = millis();
  if((millis()-timer1)>=1000){
    timer1 = millis();
    Serial.print("timeq1 = ");
    Serial.print(timer1/1000);
    Serial.println(" sec");
  }*/
  if(enablecount==true){
   // Serial.println("yeet");
     count1+=1; 
     if(count1>=100){
       myservo1.write(90);
       enablecount = false;
       Serial.println("ok");
       count1=0;
     }
  }

  for(byte i =0; i<4;i+=1){
    bitWrite(datax,i,digitalRead(sncar[i])); 
}
  for(byte i =0; i<4;i+=1){
    bitWrite(datax,i,digitalRead(sncar[i])); 
      //Serial.print(bitRead(datax,i),BIN);
       indexcar = indexcar+!bitRead(datax,i);
      if(i==3){
        //Serial.println("");
       lcd.setCursor(0,0);
       lcd.print("Total : "+String(indexcar)+" car");
       lcd.setCursor(0,1);
       if(indexcar==4){
       lcd.print(String(!bitRead(datax,0))+" "+String(!bitRead(datax,1))+" "+String(!bitRead(datax,2))+" "+String(!bitRead(datax,3))+" "+"FULL CAR");
       }
       else{
       lcd.print(String(!bitRead(datax,0))+" "+String(!bitRead(datax,1))+" "+String(!bitRead(datax,2))+" "+String(!bitRead(datax,3))+" "+"Emptycar"); 
       }
        indexcar = 0;
      }
}
  if(digitalRead(indoor1)==0 && datax!= 0b0000){
  myservo1.write(180);
  count1=0;
  }
  if(digitalRead(outdoor1)==0 || datax == 0b0000 ){
  enablecount = true;
  }
  if(digitalRead(indoor2)==0){
  myservo2.write(180);
  }
  if(digitalRead(outdoor2)==0){
  myservo2.write(90);
   }
   for(uint8_t index =  0; index<4; index+=1){
  digitalWrite(outputgreen[index],!digitalRead(sncar[index]));
  digitalWrite(outputred[index],digitalRead(sncar[index]));
 }
   delay(10);
}
