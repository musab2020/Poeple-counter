#include <ESP8266WiFi.h>
 
String apiKey = "XTR61NRWIQ6S8YLE";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "H369AD79503Telefoon";  // name of your wifi
const char *pass =  "........";  // password of your wifi
const char* server = "api.thingspeak.com";
 
int Motion_Detected =  D1; // Input for HC-SR501
int ledPin = D2;   // Red LED

 //There are zero people
int counter = 0;


WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       delay(30);
       pinMode(Motion_Detected,INPUT);
       pinMode(ledPin, OUTPUT);
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
  
int pir = digitalRead(Motion_Detected);

//als sensor iets detecteert
 if (pir == 1){
  counter+=1;
  delay(1000);
  digitalWrite(ledPin, HIGH);
  delay(400);
  
}
else if (pir ==0)
{
    digitalWrite(ledPin, LOW);
  delay(30);
  }   
      


   if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
    {  
      
       String postStr = apiKey;
       postStr +="&field1=";
       postStr += String(counter);
       postStr += "\r\n\r\n";

       client.print("POST /update HTTP/1.1\n");
       client.print("Host: api.thingspeak.com\n");
       client.print("Connection: close\n");
       client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
       client.print("Content-Type: application/x-www-form-urlencoded\n");
       client.print("Content-Length: ");
       client.print(postStr.length());
       client.print("\n\n");
       client.print(postStr);
       
       
       Serial.print("Er zijn ");
       Serial.print(counter);
       Serial.print(" mensen");
       Serial.println(" , Send to Thingspeak.");
    }
   client.stop();
  
  // thingspeak needs minimum 15 sec delay between updates
}
