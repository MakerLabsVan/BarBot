
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  char data=Serial.read();

  switch (data){
    case '1': digitalWrite(LED_BUILTIN,HIGH);break;
    case '2': digitalWrite(LED_BUILTIN,LOW);break;

  }
  Serial.println(data);
  delay(1000);
}
