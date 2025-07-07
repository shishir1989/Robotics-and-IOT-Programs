#include<Keypad.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

 const byte ROWS =4;
 const byte COLS =4;
 String inputpassword="";
 String correctpassword="1234";

 int ledpin=13;

 char keys[ROWS][COLS]={

  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','/'},
  {'*','0','#','='}

 };

byte rowPins[ROWS]={2,3,4,5};
byte colPins[COLS]={6,7,8,9};

Keypad keypad=Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);
 

void setup() {
  pinMode(ledpin,OUTPUT);
  digitalWrite(ledpin,LOW);

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  Serial.print("input password followed by #:");  

}

void loop() {
 char key =keypad.getKey();
 if(key){
  if(key=='#'){
    // lcd.clear();
    if(inputpassword==correctpassword){
      lcd.print("Access Granted");
      digitalWrite(ledpin,HIGH);
    }else{
      lcd.print("Access Denied");
      digitalWrite(ledpin,LOW);
    }
    Serial.println(inputpassword);
    delay(2000);
    lcd.clear();
    lcd.print("enter password");
    inputpassword="";
  }
  else if(key>='0' && key<='9'){
    inputpassword +=key;
    lcd.setCursor(0,1);
    lcd.print(inputpassword);
  }
  // lcd.print("Pressed key:");
  // lcd.println(key);
  // Serial.print("pressed key:");
  // Serial.print(key);
  // delay(100);
  // lcd.clear();
 }

}

