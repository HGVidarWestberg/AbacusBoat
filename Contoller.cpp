#include "FirebaseESP8266.h" 
#include <ESP8266WiFi.h> 

#define FIREBASE_HOST "abacusboat-cb5bc-default-rtdb.europe-west1.firebasedatabase.app" 
#define FIREBASE_AUTH "CphT37V3btRLIfJcjwU27DIgRxQL3I5fgQRfuNXy"

#define WIFI_SSID "Hitachigymnasiet_2.4"
#define WIFI_PASSWORD "mittwifiarsabra"

#define JOYS_VRX_PIN A0

FirebaseData firebaseData;
int counter = 0; 

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT); 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  Serial.print("Connecting to Wi-fi");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300); 
  }

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

   Firebase.setInt(firebaseData, "/servoValue", 90);
}
void loop(){
  int xValue = analogRead(JOYS_VRX_PIN);
  
  if (Firebase.getInt(firebaseData, "/servoValue")) {
   if (firebaseData.dataType() == "int") {
      int val = firebaseData.intData();
      Serial.println(val); // Skriver ut värdet
    }
  }
  
   Firebase.setInt(firebaseData, "/servoValue", ((xValue/12)+45));
}