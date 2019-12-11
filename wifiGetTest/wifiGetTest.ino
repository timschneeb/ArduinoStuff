unsigned long lastTimeMillis = 0;

void setup() {
  Serial.begin(115200);   
  Serial2.begin(115200);
  delay(1000);
  

}

void printResponse() {
  while (Serial2.available()) {
    Serial.println(Serial2.readStringUntil('\n')); 
  }
  
}

void loop() {

  if (millis() - lastTimeMillis > 10000) {
    lastTimeMillis = millis();
    Serial2.println("AT+CIPMUX=1");
    delay(1000);
    printResponse();

    Serial2.println("AT+CIPSTART=4,\"TCP\",\"thebone.ml\",80");
    delay(1000);
    printResponse();

    String cmd = "GET /api/dsb/read.php HTTP/1.1\r\nHost: thebone.ml\r\nUser-Agent: wget/1.12";
    
    Serial2.println("AT+CIPSEND=4," + String(cmd.length() + 4));
    delay(1000);

    Serial2.println(cmd);
    delay(1000);
    Serial2.println(""); 
  }

 if (Serial2.available()) {
    Serial.write(Serial2.read());
  }

}
