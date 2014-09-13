#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"

#define ADAFRUIT_CC3000_IRQ   7
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10

Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIVIDER); // you can change this clock speed but DI
                                         
//Please enter the SSID and password of the router you want to connect

#define WLAN_SSID       "Feynman"        // cannot be longer than 32 characters!
#define WLAN_PASS       "###"	   // 

// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

void DoConnect(void)
{ 
  cc3000.disconnect();
  
  if (!cc3000.deleteProfiles()) {
    Serial.println(F("Failed!"));
    while(1);
  }

  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }  

  Serial.println(F("Connected!"));
  
  /* Wait for DHCP to complete */
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }  
  
  Serial.println(F("Got an IP address!"));  
}

void setup(void)
{
  Serial.begin(115200);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }  
  
  if (!cc3000.begin())
  {
    Serial.println(F("Unable to initialise the CC3000! Check your wiring?"));
    while(1);
  } 
  
  DoConnect(); 
}

void loop(void)
{
  delay(1000 * 60);
  
  Serial.println("Checking connection status..."); 
  
  uint32_t ip = 0;
  if  (!  cc3000.getHostByName("cn.bing.com", &ip))  {
    Serial.println(F("Couldn't resolve!"));
  }  
  else{
    Serial.print("Still connected!");
  }
}
