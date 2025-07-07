#include<Wire.h>
#include<LiquidCrystal_I2C.h>


int soilpin=A2;
int soilvalue=0;
LiquidCrystal_I2C lcd(0*20,16,2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  Serial.begin(9600);
 

}

void loop() {
  soilvalue=analogRead(soilpin);
  lcd.println("Soilvalue=");
  lcd.print(soilvalue);

  delay(100);

}
