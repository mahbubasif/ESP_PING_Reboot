#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266Ping.h>        //Include the ESP8266Ping
int relayPin = D1;
unsigned long int sleepTime= 600000000;
const char* ssid     = "";         // Enter the SSID
const char* password = "";         // Enter Passowrd; Leave it blank for open SSID
void setup() {
  pinMode(relayPin,OUTPUT);
  Serial.begin(115200);         // Start the Serial communication
  delay(10);
  Serial.println('\n');
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {// Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' '); //Keep printing a number until wifi connects
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

void loop() { 
  bool pingGoogle= Ping.ping("www.google.com"); //ping google
  bool pingfb= Ping.ping("www.facebook.com");  //ping facebook
  bool pingyahoo=Ping.ping("www.yahoo.com");   //ping yahoo
  int avg_time= Ping.averageTime(); 
  Serial.print("Average Time: ");            //prints the average ping time
  Serial.print(avg_time);
  Serial.print("ms");
  
  if(pingGoogle== 1 || pingfb==1 || pingyahoo==1){
    Serial.print("\nInternet is okay!");
    Serial.println("\n. . . . . . . . .");
    digitalWrite(relayPin,LOW);
  }
  
  else{
    Serial.println("\nInternet is not okay");
    Serial.println("\n . . . . . . . . .");
    digitalWrite(relayPin,HIGH);
    delay(3000); //wait three second
    digitalWrite(relayPin,LOW);
  }
  
  delay(1000);
  Serial.print("zzzzzz....");
  ESP.deepSleep(sleepTime); //goes to sleep for 10 minutes
 }
