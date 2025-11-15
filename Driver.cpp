#include "FirebaseESP8266.h" 
#include <ESP8266WiFi.h> 
#include <Servo.h>
 
Servo myservo;

#define FIREBASE_HOST "abacusboat-cb5bc-default-rtdb.europe-west1.firebasedatabase.app" 
#define FIREBASE_AUTH "CphT37V3btRLIfJcjwU27DIgRxQL3I5fgQRfuNXy"

#define WIFI_SSID "Hitachigymnasiet_2.4"
#define WIFI_PASSWORD "mittwifiarsabra"

FirebaseData firebaseData; 

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  myservo.attach(16);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300); 
  }

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}
void loop(){
  
  if (Firebase.getInt(firebaseData, "/servoValue")) {
   if (firebaseData.dataType() == "int") {
      int val = firebaseData.intData();
      myservo.write(val);
    }
  }
}