/**********************************************************************************************************
  * @file    relay-voice-control-google.ino
  * @author  KinCony ELECTRONICS CO.,LTD https://www.kincony.com
  * @version V1.0.1
  * @date    06-May-2019
  * @brief   KC868-H8&H32 Voice Assistant----Voice Control by Google Home
  ********************************************************************************************************
  * @attention
  *
  * Before coding you should install the USB-RS232 adapter driver for download firmware. 
  * Register smart control skill on sinric.com.
  * Change parameter "MyApiKey","MySSID","MyWifiPassword","Relay1"-"RelayX" begin code line 29
  * "MyApiKey" is a API key after you registe the sinric.com skill you will see it.
  * "MySSID","MyWifiPassword" is your WiFi wireless router's WiFi SSID name and Password.
  * If you connect the voice module with KC868-H8, set "Relay1"-"Relay8"; KC868-H32 set "Relay1"-"Relay32" 
  *********************************************************************************************************/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include <StreamString.h>

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
WiFiClient client;

#define MyApiKey "1330c3cc-2e31-49ab-91cb-0b2b2cc91659" // TODO: Change to your sinric API Key. Your API Key is displayed on sinric.com dashboard
#define MySSID "KC_J" // TODO: Change to your Wifi network SSID
#define MyWifiPassword "1234567890" // TODO: Change to your Wifi network password


#define Relay1 "5cbd7f7d6bd4b204f33b74b2" // Device ID of Relay1 , which is displayed on sinric.com dashboard
#define Relay2 "5cbd5e976bd4b204f33b6d30" // Device ID of Relay2 , which is displayed on sinric.com dashboard
#define Relay3 "5cbd81826bd4b204f33b751f" // Device ID of Relay3 , which is displayed on sinric.com dashboard
#define Relay4 "5cbd818a6bd4b204f33b7521" // Device ID of Relay4 , which is displayed on sinric.com dashboard
#define Relay5 "5cbd81906bd4b204f33b7526" // Device ID of Relay5 , which is displayed on sinric.com dashboard
#define Relay6 "5cbd81986bd4b204f33b7528" // Device ID of Relay6 , which is displayed on sinric.com dashboard
#define Relay7 "5cbd819e6bd4b204f33b752d" // Device ID of Relay7 , which is displayed on sinric.com dashboard
#define Relay8 "5cbd81a56bd4b204f33b752f" // Device ID of Relay8 , which is displayed on sinric.com dashboard
#define Relay9 "5cbe7915d9de190de153a056" // Device ID of Relay9 , which is displayed on sinric.com dashboard
#define Relay10 "5cbe7923d9de190de153a05c" // Device ID of Relay10 , which is displayed on sinric.com dashboard
#define Relay11 "5cbe792bd9de190de153a062" // Device ID of Relay11 , which is displayed on sinric.com dashboard
#define Relay12 "5cbe7933d9de190de153a068" // Device ID of Relay12 , which is displayed on sinric.com dashboard
#define Relay13 "5cbe793ad9de190de153a06a" // Device ID of Relay13 , which is displayed on sinric.com dashboard
#define Relay14 "5cbe7940d9de190de153a070" // Device ID of Relay14 , which is displayed on sinric.com dashboard
#define Relay15 "5cbe7946d9de190de153a076" // Device ID of Relay15 , which is displayed on sinric.com dashboard
#define Relay16 "5cbe794dd9de190de153a078" // Device ID of Relay16 , which is displayed on sinric.com dashboard
#define Relay17 "5cbe7953d9de190de153a07e" // Device ID of Relay17 , which is displayed on sinric.com dashboard
#define Relay18 "5cbe795ad9de190de153a080" // Device ID of Relay18 , which is displayed on sinric.com dashboard
#define Relay19 "5cbe7960d9de190de153a086" // Device ID of Relay19 , which is displayed on sinric.com dashboard
#define Relay20 "5cbe7968d9de190de153a08c" // Device ID of Relay20 , which is displayed on sinric.com dashboard
#define Relay21 "5cbe796ed9de190de153a08e" // Device ID of Relay21 , which is displayed on sinric.com dashboard
#define Relay22 "5cbe7973d9de190de153a094" // Device ID of Relay22 , which is displayed on sinric.com dashboard
#define Relay23 "5cbe7979d9de190de153a096" // Device ID of Relay23 , which is displayed on sinric.com dashboard
#define Relay24 "5cbe7980d9de190de153a09c" // Device ID of Relay24 , which is displayed on sinric.com dashboard
#define Relay25 "5cbe7986d9de190de153a0a2" // Device ID of Relay25 , which is displayed on sinric.com dashboard
#define Relay26 "5cbe798cd9de190de153a0a4" // Device ID of Relay26 , which is displayed on sinric.com dashboard
#define Relay27 "5cbe7992d9de190de153a0aa" // Device ID of Relay27 , which is displayed on sinric.com dashboard
#define Relay28 "5cbe7998d9de190de153a0ac" // Device ID of Relay28 , which is displayed on sinric.com dashboard
#define Relay29 "5cbe799ed9de190de153a0b2" // Device ID of Relay29 , which is displayed on sinric.com dashboard
#define Relay30 "5cbe79a7d9de190de153a0b8" // Device ID of Relay30 , which is displayed on sinric.com dashboard
#define Relay31 "5cbe79acd9de190de153a0ba" // Device ID of Relay31 , which is displayed on sinric.com dashboard
#define Relay32 "5cbe79b1d9de190de153a0c0" // Device ID of Relay32 , which is displayed on sinric.com dashboard

#define HEARTBEAT_INTERVAL 300000 // 5 Minutes 

uint64_t heartbeatTimestamp = 0;
bool isConnected = false;

 
void turnOn(String deviceId) {
  if (deviceId == Relay1) // Device ID of first device
  {  
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,1,1");
    delay(500);
  } 
  else if (deviceId == Relay2) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,2,1");
    delay(500);
  }
  else if (deviceId == Relay3) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,3,1");
    delay(500);
  }
  else if (deviceId == Relay4) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,4,1");
    delay(500);
  }
  else if (deviceId == Relay5) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,5,1");
    delay(500);
  }
  else if (deviceId == Relay6) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,6,1");
    delay(500);
  }
  else if (deviceId == Relay7) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,7,1");
    delay(500);
  }
  else if (deviceId == Relay8) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,8,1");
    delay(500);
  }
  else if (deviceId == Relay9) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,9,1");
    delay(500);
  }
  else if (deviceId == Relay10) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,10,1");
    delay(500);
  }
  else if (deviceId == Relay11) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,11,1");
    delay(500);
  }
  else if (deviceId == Relay12) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,12,1");
    delay(500);
  }
  else if (deviceId == Relay13) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,13,1");
    delay(500);
  }
  else if (deviceId == Relay14) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,14,1");
    delay(500);
  }
  else if (deviceId == Relay15) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,15,1");
    delay(500);
  }
  else if (deviceId == Relay16) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,16,1");
    delay(500);
  }
  else if (deviceId == Relay17) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,17,1");
    delay(500);
  }
  else if (deviceId == Relay18) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,18,1");
    delay(500);
  }
  else if (deviceId == Relay19) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,19,1");
    delay(500);
  }
  else if (deviceId == Relay20) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,20,1");
    delay(500);
  }
  else if (deviceId == Relay21) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,21,1");
    delay(500);
  }
  else if (deviceId == Relay22) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,22,1");
    delay(500);
  }  
  else if (deviceId == Relay23) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,23,1");
    delay(500);
  }
  else if (deviceId == Relay24) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,24,1");
    delay(500);
  }
  else if (deviceId == Relay25) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,25,1");
    delay(500);
  }  
    else if (deviceId == Relay26) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,26,1");
    delay(500);
  }
  else if (deviceId == Relay27) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,27,1");
    delay(500);
  }
  else if (deviceId == Relay28) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,28,1");
    delay(500);
  }  
    else if (deviceId == Relay29) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,29,1");
    delay(500);
  }
  else if (deviceId == Relay30) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,30,1");
    delay(500);
  }
  else if (deviceId == Relay31) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,31,1");
    delay(500);
  }  
    else if (deviceId == Relay32) // Device ID of second device
  { 
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("RELAY-SET-1,32,1");
    delay(500);
  }
   
}

void turnOff(String deviceId) {
   if (deviceId == Relay1) // Device ID of first device
   {  
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,1,0");
     delay(500);
   }
   else if (deviceId == Relay2) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,2,0");
     delay(500);
  }
   else if (deviceId == Relay3) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,3,0");
     delay(500);
  }
   else if (deviceId == Relay4) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,4,0");
     delay(500);
  }
   else if (deviceId == Relay5) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,5,0");
     delay(500);
  }
   else if (deviceId == Relay6) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,6,0");
     delay(500);
  }
   else if (deviceId == Relay7) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,7,0");
     delay(500);
  }
   else if (deviceId == Relay8) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,8,0");
     delay(500);
  }
   else if (deviceId == Relay9) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,9,0");
     delay(500);
  }
   else if (deviceId == Relay10) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,10,0");
     delay(500);
  }
   else if (deviceId == Relay11) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,11,0");
     delay(500);
  }
   else if (deviceId == Relay12) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,12,0");
     delay(500);
  }
   else if (deviceId == Relay13) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,13,0");
     delay(500);
  }
   else if (deviceId == Relay14) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,14,0");
     delay(500);
  }
   else if (deviceId == Relay15) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,15,0");
     delay(500);
  }
   else if (deviceId == Relay16) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,16,0");
     delay(500);
  }
   else if (deviceId == Relay17) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,17,0");
     delay(500);
  }
   else if (deviceId == Relay18) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,18,0");
     delay(500);
  }
   else if (deviceId == Relay19) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,19,0");
     delay(500);
  }
   else if (deviceId == Relay20) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,20,0");
     delay(500);
  }
   else if (deviceId == Relay21) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,21,0");
     delay(500);
  }
   else if (deviceId == Relay22) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,22,0");
     delay(500);
  }
   else if (deviceId == Relay23) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,23,0");
     delay(500);
  }
   else if (deviceId == Relay24) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,24,0");
     delay(500);
  }
   else if (deviceId == Relay25) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,25,0");
     delay(500);
  }
   else if (deviceId == Relay26) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,26,0");
     delay(500);
  }
   else if (deviceId == Relay27) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,27,0");
     delay(500);
  }
   else if (deviceId == Relay28) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,28,0");
     delay(500);
  }
   else if (deviceId == Relay29) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,29,0");
     delay(500);
  }
   else if (deviceId == Relay30) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,30,0");
     delay(500);
  }
   else if (deviceId == Relay31) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,31,0");
     delay(500);
  }
   else if (deviceId == Relay32) // Device ID of second device
   { 
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     Serial.print("RELAY-SET-1,32,0");
     delay(500);
  }

}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      isConnected = false;    
  //    Serial.printf("[WSc] Webservice disconnected from sinric.com!\n");
      break;
    case WStype_CONNECTED: {
      isConnected = true;
 //     Serial.printf("[WSc] Service connected to sinric.com at url: %s\n", payload);
 //     Serial.printf("Waiting for commands from sinric.com ...\n");        
      }
      break;
    case WStype_TEXT: {
  //      Serial.printf("[WSc] get text: %s\n", payload);
        // Example payloads

        // For Switch  types
        // {"deviceId":"xxx","action":"action.devices.commands.OnOff","value":{"on":true}} // https://developers.google.com/actions/smarthome/traits/onoff
        // {"deviceId":"xxx","action":"action.devices.commands.OnOff","value":{"on":false}}

        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject((char*)payload); 
        String deviceId = json ["deviceId"];     
        String action = json ["action"];
        
        if(action == "action.devices.commands.OnOff") { // Switch 
            String value = json ["value"]["on"];
    //        Serial.println(value); 
            
            if(value == "true") {
                turnOn(deviceId);
            } else {
                turnOff(deviceId);
            }
        }
        else if (action == "test") {
   //         Serial.println("[WSc] received test command from sinric.com");
        }
      }
      break;
    case WStype_BIN:
  //    Serial.printf("[WSc] get binary length: %u\n", length);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  
  WiFiMulti.addAP(MySSID, MyWifiPassword);
//  Serial.println();
//  Serial.print("Connecting to Wifi: ");
//  Serial.println(MySSID);  
  pinMode(LED_BUILTIN, OUTPUT); 

  // Waiting for Wifi connect
  while(WiFiMulti.run() != WL_CONNECTED) {
    delay(500);
 //   Serial.print(".");
  }
  if(WiFiMulti.run() == WL_CONNECTED) {
 //   Serial.println("");
 //   Serial.print("WiFi connected. ");
 //   Serial.print("IP address: ");
//    Serial.println(WiFi.localIP());
  }

  // server address, port and URL
  webSocket.begin("iot.sinric.com", 80, "/"); //"iot.sinric.com", 80

  // event handler
  webSocket.onEvent(webSocketEvent);
  webSocket.setAuthorization("apikey", MyApiKey);
  
  // try again every 5000ms if connection has failed
  webSocket.setReconnectInterval(5000);   // If you see 'class WebSocketsClient' has no member named 'setReconnectInterval' error update arduinoWebSockets
  Serial.print("RELAY-TEST-NOW");
}

void loop() {
  webSocket.loop();
  
  if(isConnected) {
      uint64_t now = millis();
      
      // Send heartbeat in order to avoid disconnections during ISP resetting IPs over night. Thanks @MacSass
      if((now - heartbeatTimestamp) > HEARTBEAT_INTERVAL) {
          heartbeatTimestamp = now;
          webSocket.sendTXT("H");          
      }
  }   
}
 
