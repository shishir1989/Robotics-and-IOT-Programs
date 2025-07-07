int buttonPin = 2;
int count=0;
int buttonPin2 = 4;
int count2=0;

void setup(){
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(buttonPin2,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop(){
  if (digitalRead(buttonPin)==LOW){
	count++;
    Serial.print("Party 1 Voted= ");
    Serial.println(count);
    Serial.print("Party 2= ");
    Serial.println(count2);
    delay(500);
  }
  else if(digitalRead(buttonPin2)==LOW){
	count2++;
    Serial.print("Party 2 Voted= ");
    Serial.println(count2);
    Serial.print("Party 1= ");
    Serial.println(count);
    delay(500);
    
}
}
    