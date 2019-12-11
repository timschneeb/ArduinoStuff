bool DEBUG = true;   //show more logs
int responseTime = 10; //communication timeout

void setup()
{
  pinMode(13, OUTPUT); //set build in led as output
  pinMode(2, OUTPUT);
  pinMode(11, OUTPUT);   /////used if connecting a LED to pin 11
  digitalWrite(11, LOW);
  // pinMode(52,OUTPUT);
  //digitalWrite(52,HIGH);
  // Open serial communications and wait for port to open esp8266:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial2.begin(115200);
  while (!Serial2) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  sendToWifi("AT+CWMODE=1", responseTime, DEBUG); // configure as access point

  //sendToWifi("AT+CWJAP=\"GS\",\"weissbraun287Tim\"",responseTime,DEBUG);
  sendToWifi("AT+CIFSR", responseTime, DEBUG); // get ip address
  sendToWifi("AT+CIPMUX=1", responseTime, DEBUG); // configure for multiple connections
  sendToWifi("AT+CIPSERVER=1,80", responseTime, DEBUG); // turn on server on port 80

  sendToUno("Wifi connection is running!", responseTime, DEBUG);
  digitalWrite(2, LOW);

}

float sensetemp() ///////function to sense temperature.
{
  return (78);
}

int connectionId;
void loop()
{

}


/*
  Name: sendData
  Description: Function used to send string to tcp client using cipsend
  Params:
  Returns: void
*/
void espsend(String d)
{
  String cipSend = " AT+CIPSEND=";
  cipSend += connectionId;
  cipSend += ",";
  cipSend += d.length();
  cipSend += "\r\n";
  sendData(cipSend, 1000, DEBUG);
  sendData(d, 1000, DEBUG);
}

String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  Serial2.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (Serial2.available())
    {
      char c = Serial2.read(); // read the next character.
      response += c;
    }
  }

  if (debug)
  {
    Serial.print(response); //displays the esp response messages in arduino Serial monitor
  }
  return response;
}

/*
  Name: find
  Description: Function used to match two string
  Params:
  Returns: true if match else false
*/
boolean find(String string, String value) {
  if (string.indexOf(value) >= 0)
    return true;
  return false;
}


/*
  Name: readSerialMessage
  Description: Function used to read data from Arduino Serial.
  Params:
  Returns: The response from the Arduino (if there is a reponse)
*/
String  readSerialMessage() {
  char value[100];
  int index_count = 0;
  while (Serial.available() > 0) {
    value[index_count] = Serial.read();
    index_count++;
    value[index_count] = '\0'; // Null terminate the string
  }
  String str(value);
  str.trim();
  return str;
}



/*
  Name: readWifiSerialMessage
  Description: Function used to read data from ESP8266 Serial.
  Params:
  Returns: The response from the esp8266 (if there is a reponse)
*/
String  readWifiSerialMessage() {
  char value[100];
  int index_count = 0;
  while (Serial2.available() > 0) {
    value[index_count] = Serial2.read();
    index_count++;
    value[index_count] = '\0'; // Null terminate the string
  }
  String str(value);
  str.trim();
  return str;
}



/*
  Name: sendToWifi
  Description: Function used to send data to ESP8266.
  Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
  Returns: The response from the esp8266 (if there is a reponse)
*/
String sendToWifi(String command, const int timeout, boolean debug) {
  String response = "";
  Serial2.println(command); // send the read character to the esp8266
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (Serial2.available())
    {
      // The esp has data so display its output to the serial window
      char c = Serial2.read(); // read the next character.
      response += c;
    }
  }
  if (debug)
  {
    Serial.println(response);
  }
  return response;
}

/*
  Name: sendToWifi
  Description: Function used to send data to ESP8266.
  Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
  Returns: The response from the esp8266 (if there is a reponse)
*/
String sendToUno(String command, const int timeout, boolean debug) {
  String response = "";
  Serial.println(command); // send the read character to the esp8266
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (Serial.available())
    {
      // The esp has data so display its output to the serial window
      char c = Serial.read(); // read the next character.
      response += c;
    }
  }
  if (debug)
  {
    Serial.println(response);
  }
  return response;
}
