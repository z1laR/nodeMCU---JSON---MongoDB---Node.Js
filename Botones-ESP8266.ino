#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//const char* ssid = "INFINITUM055F";
//const char* password = "0434776648";

const char* ssid = "IZZI-MANCILLA";
const char* password = "25014978";

#define pushbutton1 D0
#define pushbutton2 D1

boolean lastbuttonstate1 = false;
boolean lastbuttonstate2 = false;

void setup()
{
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(ssid);

    WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  //pinMode(ledpin,OUTPUT);
  pinMode(pushbutton1,INPUT);
  pinMode(pushbutton2,INPUT);

  Serial.println(F("|-------------------------------------------------|"));
  Serial.println(F("|          PROCESAMIENTO EN PARALELO P/L          |"));
  Serial.println(F("|  API REST / Node.JS / MongoDB / nodeMCU / JSON  |"));
  Serial.println(F("|-------------------------------------------------|"));
}

void loop()
{
  String boton = "";
  
  if(digitalRead(pushbutton1)== HIGH && digitalRead(pushbutton2) == LOW && lastbuttonstate1 == false)
   {

    Serial.print("BOTON IZQUIERDO OPRIMIDO");
    Serial.println(F(" \n "));
    Serial.println(F("PETICION ENVIADA"));
    Serial.println(F(" \n "));

    post(boton);

    //boton = "";
    
   }
   
 else if(digitalRead(pushbutton1) == LOW && digitalRead(pushbutton2)== LOW && lastbuttonstate1 == HIGH)
   {

    Serial.print("BOTON DERECHO OPRIMIDO");
    Serial.println(F(" \n "));
    Serial.println(F("PETICION ENVIADA"));
    Serial.println(F(" \n "));

    post(boton);

    //boton = "";
    
   }
}

void post(String boton)
{
  HTTPClient http;
  String json = "{}";
  String server = "http://192.168.0.4:3000/api/product/";
  server.concat(boton);
  

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  Serial.println(server);
  http.begin(server);

  http.addHeader("Content-Type", "application/json");
  Serial.println("");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
  Serial.println("FIN MyPost");
  Serial.println("");
}
