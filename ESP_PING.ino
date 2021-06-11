#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266Ping.h>
int relayPin = D1;
unsigned long int sleepTime= 600000000;
const char* ssid     = "Pollinibash";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "Pass=w0rd";
void setup() {
  pinMode(relayPin,OUTPUT);
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {// Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

void loop() { 
  bool pingGoogle= Ping.ping("www.google.com");
  bool pingfb= Ping.ping("www.facebook.com");
  bool pingyahoo=Ping.ping("www.yahoo.com");
  int avg_time= Ping.averageTime();
  Serial.print("Average Time: ");
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
    delay(3000);
    digitalWrite(relayPin,LOW);
  }
  
  delay(1000);
  Serial.print("zzzzzz....");
  ESP.deepSleep(sleepTime);
 }
