#include <ESP8266WiFi.h>

int hallsensor = 2;                // Hall sensor at pin 2

volatile byte counter;

unsigned int rpm;
unsigned int v;

unsigned long passedtime;


void isr()

 {

   //Each rotation, this interrupt function is run twice, so take that into consideration for

   //calculating RPM

   //Update count

      counter++;

 }
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "SSID"
#define WLAN_PASS       "Password"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "USERNAME"
#define AIO_KEY         "AIO KEY"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup feeds for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish Rpm = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/rpm");
Adafruit_MQTT_Publish Velocity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/velocity");
// Setup feeds subscribing to changes.

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
  Serial.begin(115200);
 
  delay(10);
pinMode(D2,OUTPUT);
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
   attachInterrupt(0, isr, RISING); //Interrupts are called on Rise of Input

   pinMode(hallsensor, INPUT); //Sets hallsensor as input

   counter = 0;

   rpm = 0;

   passedtime = 0; //Initialise the values

  
 
}

uint32_t x=0;

void loop() {
 
  MQTT_connect();
 
 // Now we can publish stuff!
  detachInterrupt(0); //Interrupts are disabled

   rpm = 30*1000/(millis() - passedtime)*counter;

   passedtime = millis();

   counter = 0;

   v=0;

   Serial.print("RPM=");

   Serial.println(rpm); //Print out result to monitor

   
  Serial.print(F("\nSending RPM and Velocity Values "));
 
  if (! Rpm.publish(rpm)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
  if (! Velocity.publish(v)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
  delay(1000);

  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */
  attachInterrupt(0, isr, RISING);   //Restart the interrupt processing
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
