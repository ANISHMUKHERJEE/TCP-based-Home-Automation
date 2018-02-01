#include<ESP8266WiFi.h>

WiFiServer server(80);

char* ssid="Qazi";
char* password="Irise@1234";


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

pinMode(LED_BUILTIN,OUTPUT);
WiFi.begin(ssid,password);
delay(1000);

while(WiFi.status()!=WL_CONNECTED)
{
  delay(1000);
  Serial.println("Wait for sometime");
}

Serial.println("Connected");

Serial.println(WiFi.localIP());
server.begin();
}

void loop() 
{
  WiFiClient client=server.available();
  if(!client)
  {
    return;
  }


  
  String s=client.readStringUntil('\r');
 
  int value=LOW;
  if (s.indexOf("/LED=ON")!=-1)
  {
    digitalWrite(LED_BUILTIN,HIGH);
    Serial.println("LED is ON");
    value=HIGH;
  }
  else if(s.indexOf("/LED=OFF")!=-1)
  {
    digitalWrite(LED_BUILTIN,LOW);
    Serial.println("LED is OFF");
    value=LOW;
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type; text/html");
   client.println("");
 client.println("<!DOCTYPE HTML>");
  client.println("<html>");

   client.println("led pin is now: ");

   if(value==HIGH)
   {
     client.println("ON");
     }
     else
     {
       client.println("OFF");
   }
   client.println("<br><br>");
    client.println("<a href=\"/LED=ON\"\"><button>Turn On</a>");
     client.println("<a href=\"/LED=OFF\"\"><button>Turn Off</button></a><br/>");
      client.println("</html>");

      delay(1);
       Serial.println("disconnected");
        Serial.println("");


}
      
  
  



