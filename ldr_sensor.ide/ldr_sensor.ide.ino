int ldrpin=10;
int led =4;


void setup() {
  pinMode(ldrpin,INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);

}

void loop() {
 int ldrread= analogRead(ldrpin);
 Serial.print(ldrread);
 delay(100);
 if(ldrread>=200){
  digitalWrite(led,HIGH);
 }
 else{
  digitalWrite(led,LOW);                                                                                                          
 }

}
