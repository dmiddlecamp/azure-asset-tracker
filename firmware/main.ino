
#include "Adafruit_GPS.h"
#include <math.h>

#define mySerial Serial1
Adafruit_GPS GPS(&mySerial);


// echo all the raw GPS data to the USB serial port?
#define GPSECHO  true

// what version are we?
#define APP_VERSION 11



FuelGauge fuel;

uint32_t timer;
String _gpsDebugLines;

void setup() {
    pinMode(D6, OUTPUT);
    digitalWrite(D6, LOW);

    Particle.function("gpsNMEA", gpsNMEA);

    
    // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
    GPS.begin(9600);
    mySerial.begin(9600);

    Serial.begin(9600);
    
    
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_OFF);
    delay(100);
    
    
    // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_ALLDATA);
    delay(100);
    
    // Set the update rate
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
    delay(100);

    // Mute antenna status events
    GPS.sendCommand(PGCMD_NOANTENNA);
    delay(100);


    Particle.publish("GPS", "{ status: \"started up! "+String(APP_VERSION)+"\"}", 60, PRIVATE );
    timer = millis();

}

int publishCount = 0;
float lastVCC = 0;

void loop() {
    // did millis() wrap?
    if (timer > millis())  {
        timer = millis();
    }

    char c = GPS.read();
    if (GPSECHO && c) {
        Serial.print(c);
    }

    //something new?
    if (GPS.newNMEAreceived()) {

        // try to parse it
        if (!GPS.parse(GPS.lastNMEA()))   {

            //didn't work?
            if ((millis() - timer) > 60000) {
                Particle.publish("GPS", "{ error:\"failed to parse\", last: \""+String(GPS.lastNMEA())+"\"}", 60, PRIVATE );
                timer = millis(); // reset the timer
            }

          return;
        }
    }


    // has it been a minute?
    if (millis() - timer > 60000) {
        timer = millis(); // reset the timer

        printDebugInfo();

        bool hasLocation = (GPS.latitude != 0);
        bool batteryChanged = (fuel.getVCell() != lastVCC);

        // do we have a location?
        if (hasLocation || batteryChanged) {

            Particle.publish("GPS_coords",
            "{\"lat\": " + String(convertDegMinToDecDeg(GPS.latitude))
            + ",\"lon\": -" + String(convertDegMinToDecDeg(GPS.longitude))
            + ",\"a\": " + String(GPS.altitude)
            + ",\"q\": " + String(GPS.fixquality)
            + ",\"s\": " + String(GPS.satellites)
            + ",\"vcc\": " + String(fuel.getVCell())
            + ",\"soc\": " + String(fuel.getSoC())
            + "}",
            60, PRIVATE
            );

            lastVCC = fuel.getVCell();
        }

//        // send our battery status
//        if (fuel.getVCell() != lastVCC) {
//            Particle.publish("GPS_battery",
//            "{\"vcc\": " + String(fuel.getVCell())
//            + ",\"soc\": " + String(fuel.getSoC())
//            + "}",
//            60, PRIVATE
//            );
//
//            lastVCC = fuel.getVCell();
//        }

        publishCount++;
    }

  // optional sleep after every 10 publishes for 30 minutes, etc
//   if (publishCount > 10) {
//       // sleep for 30 minutes
//       System.sleep(SLEEP_MODE_DEEP, 30 * 60);
//   }
}
 
 
 //http://arduinodev.woofex.net/2013/02/06/adafruit_gps_forma/
double convertDegMinToDecDeg (float degMin) {
  double min = 0.0;
  double decDeg = 0.0;
 
  //get the minutes, fmod() requires double
  min = fmod((double)degMin, 100.0);
 
  //rebuild coordinates in decimal degrees
  degMin = (int) ( degMin / 100 );
  decDeg = degMin + ( min / 60 );
 
  return decDeg;
}
 
int gpsNMEA(String cmd) {
    Particle.publish("GPS_NMEA", String(GPS.lastNMEA()), 60, PRIVATE);
    return 1;
}

 
 
 
void printDebugInfo() {
    
    Serial.print("\nTime: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality); 
    
    //if (GPS.fix) 
    //{
    Serial.print("Location: ");
    Serial.print(GPS.latitude, 4); 
    Serial.print(GPS.lat);
    Serial.print(", "); 
    
    Serial.print(GPS.longitude, 4); 
    Serial.println(GPS.lon);
    
    Serial.print("Speed (knots): "); Serial.println(GPS.speed);
    Serial.print("Angle: "); Serial.println(GPS.angle);
    Serial.print("Altitude: "); Serial.println(GPS.altitude);
    Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
}
 
 

 