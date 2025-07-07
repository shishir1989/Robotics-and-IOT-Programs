#include<Wire.h>
#include<LiquidCrystal_I2C.h>


int soilpin=A2;
int soilvalue=0;
int relay=8;
LiquidCrystal_I2C lcd(0X27,16,2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(relay,OUTPUT);
  Serial.begin(9600);
  
 

}

void loop() {
  soilvalue=digitalRead(soilpin);
  lcd.setCursor(0,0);
  lcd.println("Soilvalue=");
  lcd.print(soilvalue);
  
  if(soilvalue==HIGH){
    lcd.setCursor(0,1);
    lcd.print("wet");
    digitalWrite(relay,HIGH);
  }
  else{
    lcd.setCursor(0,1);
    lcd.print("dry");
    digitalWrite(relay,LOW);
  }

  delay(1000);

}
