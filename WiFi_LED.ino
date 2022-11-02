/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP32     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include <WiFi.h>

String  req;
WiFiServer server(80);

WiFiClient client;

String myresultat;

String ReadIncomingRequest(){
while(client.available()) {
String ClientRequest = (client.readStringUntil('\r'));
 if ((ClientRequest.indexOf("HTTP/1.1")>0)&&(ClientRequest.indexOf("/favicon.ico")<0)){
myresultat = ClientRequest;
}
}
return myresultat;
}

void setup()
{
req = "";

Serial.begin(9600);

pinMode(2, OUTPUT);
  WiFi.disconnect();
  WiFi.begin("Noey","11501150");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.println("......");

  }
  Serial.println("Connected!");
  server.begin();
  Serial.println((WiFi.localIP()));

}


void loop()
{

    client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    req = (ReadIncomingRequest());
    client.flush();
    if (req.indexOf("LED=ON") != -1) {
      digitalWrite(2,HIGH);

    }
    if (req.indexOf("LED=OFF") != -1) {
      digitalWrite(2,LOW);

    }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("</head>");
    client.println("<body>");
      client.println("<h1 style=""color:#ff0000"">");
      client.println("Press Control LED");
      client.println("</h1>");
      client.println("<h2 style=""color:#0000ff"">");
      client.println("ESP32s Connected!");
      client.println("</h2>");
      client.println("<a href=");
      client.println("LED=ON");
      client.println("><button>");
      client.println("ON");
      client.println("</button></a>");
      client.println("<a href=");
      client.println("LED=OFF");
      client.println("><button>");
      client.println("OFF");
      client.println("</button></a>");
    client.println("</body>");
    client.println("</html>");
    delay(1);

}