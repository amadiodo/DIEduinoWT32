#include <WiFiUdp.h>
#include <global.h>
#include <AsyncElegantOTA.h>
#include <LittleFS.h>
#include <ESP32Ping.h>

const char* ssidA         = "Laboratorio Sistemi";          //da modificare secondo le necessita'
const char* passwordA     = "Piergentili11235813213455";
const char* ssidB         = "diego2";       
const char* passwordB     = "diegorita";
const char* ssidD         = "ibit";
const char* passwordD     = "qwertyuiop";
uint32_t ping_timer, WiFi_connection_timeout;
uint8_t ping_counter;
uint8_t WiFi_Attemps = 1;
AsyncWebServer WEBserver(80);
/**************************************************************************/
/*!
    @brief  Try to connect to WiFi network
    @return 1 if success, 0 if fail
*/
/**************************************************************************/
bool wifi_initialization() { 
  WiFi.mode(WIFI_STA);
  // debug_prefix();
  switch(WiFi_Attemps++) {
    case 0:
      sprintf(stri, "Trying SSID: %s\t", ssidA);
      print_debug(stri, true);
      WiFi.begin(ssidA, passwordA);
    break;
    case 1:
      sprintf(stri, "Trying SSID: %s\t", ssidB);
      print_debug(stri, true);
      WiFi.begin(ssidB, passwordB);
    break;
    case 2:
      sprintf(stri, "Trying SSID: %s\t", ssidD);
      print_debug(stri, true);
      WiFi.begin(ssidD, passwordD);
    break;
  };
  if(WiFi_Attemps == 3) WiFi_Attemps = 0;
  #ifdef POWER_BOARD
    WiFi.setHostname("PowerBoard");
  #endif
  #ifdef GREENCUBE_OBC
    WiFi.setHostname("GreencubeGSE");
  #endif
  #ifdef PROPAGATOR
    WiFi.setHostname("DIEduinoESP");
  #endif
  WiFi_connection_timeout = millis();
  while (WiFi.status() != WL_CONNECTED) {
    if(millis() - WiFi_connection_timeout > 10000) {
      sprintf(stri, "WiFi_Error\r\n");
      print_debug(stri, true);
      WiFi.disconnect();
      delay(500);
      return false;
    }
    delay(10);
  }
  sprintf(stri, "\r\n");
  print_debug(stri, true);
  // sprintf(stri, "\r\n");
  // print_debug(stri, true);
  // // debug_prefix();
  sprintf(stri, "WiFi connected, CH: %d, IP: \t\t%d.%d.%d.%d\r\n", WiFi.channel(), WiFi.localIP()[0], WiFi.localIP()[1],WiFi.localIP()[2],WiFi.localIP()[3]);
  print_debug(stri, true);
  WiFi.setAutoReconnect(1);
  // TCP_attempt =0;

  #ifdef GREENCUBE_OBC
    WEBserver.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {request->send(200, "text/plain", "GreencubeGSE");});
  #endif
  // #ifdef PROPAGATOR
  //   WEBserver.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {request->send(200, "text/plain", "DIEduinoESP");});
  // #endif

  AsyncElegantOTA.begin(&WEBserver);    // Start ElegantOTA
  WEBserver.begin();
  connectivity_check(true);
  return true;
}
uint32_t RSSI_check_old;
/**************************************************************************/
/*!
    @brief  Check internet connection and reset WiFi if needed
    @param force If 1 do it also timer is not triggered
*/
/**************************************************************************/
bool connectivity_check(bool force) {
  if(millis() - ping_timer > 1000 * 600  || force) {
    ping_timer = millis();
    if(Ping.ping(WiFi.gatewayIP(), 2)) {
      uint32_t a = Ping.averageTime();
      sprintf(stri, "WiFi Ping: %d ms, RSSI: %d\t\tOK\r\n", a, WiFi.RSSI());
      print_debug(stri, true);
    }
    else {
      sprintf(stri, "WiFi Ping: \t\t\t\tError (%d)\r\n",ping_counter);
      print_debug(stri, true);
      WiFi.disconnect();
      return false;
    }
    return true;
    
  } else return true;

}

void WiFi_RSSI() {
    if(millis() - RSSI_check_old > 10000) {
    RSSI_check_old = millis();
    power_board.RSSI = -WiFi.RSSI();
  }
}