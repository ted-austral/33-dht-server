/*
 *  Project 33-dht-server - main.cpp
 *      Asynchronous server
 *      for humidity and temperature
 *
 *  Austral - IntroComp -2022 - EAM
 */

/*
 *  System Includes
 */

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#include <WiFi.h>
#include <AsyncTCP.h>

#include <ESPAsyncWebServer.h>

/*
 *  Project includes
 */

#include "wifi_ruts.h"

/*
 *  Definitions
 */

/*
 *  From platformio.ini
 *      DHTPIN          GPIO DHT PIN
 *      DHTTYPE         DHT TYPE
 *      SERIAL_BAUD     Serial Baud rate
 */

static const long interval = 4000;        // Updates DHT readings

/*
 *  Objects invocation
 */

DHT dht(DHTPIN, DHTTYPE);           // Object DHT
AsyncWebServer server(80);          // Create AsyncWebServer object on port 80

/*
 *  Global variables
 */

static float t, h;                         // current temperature & humidity, updated in loop()
static unsigned long previousMillis = 0;   // will store last time DHT was updated

#include "html_page.h"              // page in HTML

/*
 *  Auxiliary functions
 */

//  proccesor function to be quested by server

static String
processor(const String &var)
{
    return var == "TEMPERATURE" ? String(t): String(h);
}

/*
 * get_temp_hum:
 *  called by loop to get data and set in variables quested by server
 *  return 0 on error, 1 otherwise
 */

static int
get_temp_hum( float *pt, float *ph )
{
    *pt = dht.readTemperature();
    *ph = dht.readHumidity();
    return !isnan(*pt) && !isnan(*ph);
}

/*
 *  Public functions
 */

void
setup( void )
{
    Serial.begin(115200);
    dht.begin();

    wifi_connect();

    // Route for root / web page

    server.on("/", HTTP_GET,
            [](AsyncWebServerRequest *request) { request->send_P(200, "text/html", index_html, processor); });
    server.on("/temperature", HTTP_GET,
            [](AsyncWebServerRequest *request) { request->send_P(200, "text/plain", String(t).c_str()); });
    server.on("/humidity", HTTP_GET,
            [](AsyncWebServerRequest *request) { request->send_P(200, "text/plain", String(h).c_str()); });

    // Start server
    server.begin();
}

void
loop( void )
{
    unsigned long currentMillis = millis();     //  Initialized in each loop entry

    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;         // save the last time you updated the DHT values
        if( get_temp_hum( &t, &h ) )    
        {
            Serial.print( "Temperature = " );
            Serial.print( t, 1 );
            Serial.print( "\tHumidity = " );
            Serial.println( h, 1 );
        }
        else
            Serial.println("Failed to read from DHT sensor!");
    }
}
