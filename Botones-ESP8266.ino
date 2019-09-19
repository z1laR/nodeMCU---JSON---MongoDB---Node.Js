#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//char* ssid = "";
//char* password = "";

#define pushbutton1 D0
#define pushbutton2 D1

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
  
  pinMode(pushbutton1,INPUT);
  pinMode(pushbutton2,INPUT);
}

void loop()
{        
  boton_izquierdo();
  boton_derecho();
}
  
  String boton_izquierdo()
  {
    int estado = 0;
    int salida = 0;
    int estado_anterior = 0;
    String lado = "IZQUIERDO";
    
    estado = digitalRead(pushbutton1);
  
    if((estado == HIGH) && (estado_anterior == LOW))
    {
      salida = 1 - salida;
    }
  
    estado_anterior = estado;
    delay(80);
    
    if(salida == 1)
    {  
      Serial.print(lado);
      Serial.println(F(" \n "));
      Serial.println(F("PETICION ENVIADA"));
      Serial.println(F(" \n "));

      post(lado);

      return lado;
    }
      
    else
      {
        Serial.print("\n .");
      }
  }

  String boton_derecho()
  {
    int estado2 = 0;
    int salida2 = 0;
    int estado_anterior2 = 0;
    String lado = "DERECHO";
    
    estado2 = digitalRead(pushbutton2);
  
    if((estado2 == HIGH) && (estado_anterior2 == LOW))
    {
      salida2 = 1 - salida2;
    }
  
    estado_anterior2 = estado2;
    delay(80);
    
    if(salida2 == 1)
    {  
      Serial.print(lado);
      Serial.println(F(" \n "));
      Serial.println(F("PETICION ENVIADA"));
      Serial.println(F(" \n "));
  
      post(lado);

      return lado;
    }
      
    else
      {
        Serial.print("\n . ");
      }
  }

void post(String lado)
{
  HTTPClient http;
  String json = "";
  String server = "http://192.168.0.4:3000/api/product/";
  server.concat(lado);
  
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
