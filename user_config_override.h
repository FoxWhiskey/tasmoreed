/*
  user_config_override.h - user configuration overrides my_user_config.h for Tasmota

  Copyright (C) 2021  Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

/*****************************************************************************************************\
 * USAGE:
 *   To modify the stock configuration without changing the my_user_config.h file:
 *   (1) copy this file to "user_config_override.h" (It will be ignored by Git)
 *   (2) define your own settings below
 *
 ******************************************************************************************************
 * ATTENTION:
 *   - Changes to SECTION1 PARAMETER defines will only override flash settings if you change define CFG_HOLDER.
 *   - Expect compiler warnings when no ifdef/undef/endif sequence is used.
 *   - You still need to update my_user_config.h for major define USE_MQTT_TLS.
 *   - All parameters can be persistent changed online using commands via MQTT, WebConsole or Serial.
\*****************************************************************************************************/


#define LOCATION1
//#define LOCATION2

// https://github.com/arendst/Tasmota/issues/8464
#ifdef MODULE
#undef MODULE
#endif
#define MODULE                 USER_MODULE   // [Module] Select default model (the list is kModuleNiceList() in file tasmota_template.h) USER_MODULE is the TEMPLATE

#ifdef FALLBACK_MODULE
#undef FALLBACK_MODULE
#endif
#define FALLBACK_MODULE        USER_MODULE   // to Select the default model as FALLBACK when the user does a RESET 1 

#ifdef USER_TEMPLATE
#undef USER_TEMPLATE
#endif
#define USER_TEMPLATE     "{\"NAME\":\"Wasserzähler(Reed)\",\"GPIO\":[0,0,352,0,0,0,0,0,0,0,0,0,0,0],\"FLAG\":0,\"BASE\":18}"

// https://github.com/arendst/Tasmota/discussions/15873
#ifndef START_SCRIPT_FROM_BOOT
#define START_SCRIPT_FROM_BOOT
#define PRECONFIGURED_SCRIPT ">D\ncv=0\nfm=0\nfh=-1\nfd=-1\nm:ma=0 60\nm:ha=0 24\np:sc=0\np:lp=0\n>B\ncv=sc+(lp*0.001*pc[1])\n>S\ncv=sc+(lp*0.001*pc[1])\nif upsecs%60==0\nthen\n  if ma[ma[0]]==0\n    then fm=-1\n  else\n     fm=(cv-ma[ma[0]])*1000\n  endif\n  if ma[ma[0]+1]==0\n    then fh=-1\n  else\n     fh=(cv-ma[ma[0]+1])*1000\n endif\n ma=cv\n print cv:%cv% ma[%0(ma[0]+1)%]:%0ma[ma[0]+1]% fm:%fm% fh:%fh% fd:%fd%\nendif\nif upsecs%3600==0\nthen\n  if ha[ha[0]+1]==0\n    then fd=-1\n  else\n     fd=(cv-ha[ha[0]+1])*1000\n  endif\n  ha=cv\nendif\nif chg[cv]>0\nor chg[fm]>0\nor chg[fh]>0\nor chg[fd]>0\nthen\n   =>publish /%prefix3%/%topic%/SENSOR {\"Garten\":{\"total\":%3cv%,\"flow60s\":%0fm%,\"flow60m\":%0fh%,\"flow24h\":%0fd%}}\nendif\n>E\n;cv=sc+(lp*0.001*pc[1])\n;print set:%cv%\n>W\n@<h2>Intitialwerte</h2>\nso(1)\nnm(0 100000 1 sc \"Zählerstand (m³) {m}\" 110 3)\nnm(1 20 1 lp \"Liter/Impuls \" 50 0)\n-----------------\n<h1><center>%3cv% m³</center></h1>\n-----------------\n<h2>Verbrauch</h2>\n{s}60sec {m} %0fm% l/min{e}\n60min {m} %0fh% l/h\n24hrs {m} %0fd% l/24h\n-----------------"
#endif

#ifndef USER_BACKLOG
#define USER_BACKLOG      "Hostname tasmoreed; FriendlyName1 Tasmoreed; Altitude 400;CounterDebounceHigh 500;CounterDebounceLow 500;CounterDebounce 1000;WebSensor1 0"
#endif

#ifdef LOCATION1
#ifdef  STA_SSID1
#undef  STA_SSID1
#endif
#define STA_SSID1         "<mySSID>"                // [Ssid1] Wifi SSID

#ifdef  STA_PASS1
#undef  STA_PASS1
#endif
#define STA_PASS1         "<myPASS>"                // [Password1] Wifi password

#ifdef  MQTT_HOST
#undef  MQTT_HOST
#endif
#define MQTT_HOST         "<myMQTThost>"            // [MqttHost]

#ifdef  NTP_SERVER1
#undef  NTP_SERVER1
#endif
#define NTP_SERVER1       "<myNTPserver>"           // [ntpserver1]
#endif                    //LOCATION1

#ifdef LOCATION2          //LOCATION2
#ifdef  STA_SSID1
#undef  STA_SSID1
#endif
#define STA_SSID1         "<mySSID>"                // [Ssid1] Wifi SSID

#ifdef  STA_PASS1
#undef  STA_PASS1
#endif
#define STA_PASS1         "<myPASS>"        // [Password1] Wifi password

#ifdef  NTP_SERVER1
#undef  NTP_SERVER1
#endif
#define NTP_SERVER1       "<myNTPserver>"      // [ntpserver1]
#endif                    //LOCATION2

#ifdef TELE_PERIOD
#undef TELE_PERIOD
#define TELE_PERIOD       60
#endif

#ifdef  MQTT_FULLTOPIC
#undef  MQTT_FULLTOPIC
#endif
#define MQTT_FULLTOPIC    "/%prefix%/%topic%/" // [FullTopic] Subscribe and Publish full topic name - Legacy topic

#ifdef  MQTT_TOPIC
#undef  MQTT_TOPIC
#endif
#define MQTT_TOPIC        "water"   // [Topic] unique MQTT device topic including (part of) device MAC address
  
#ifdef  NTP_SERVER2
#undef  NTP_SERVER2
#define NTP_SERVER2       ""
#endif
#ifdef  NTP_SERVER3
#undef  NTP_SERVER3
#define  NTP_SERVER3       ""
#endif

// Location
#ifdef LATITUDE
#undef LATITUDE
#undef LONGITUDE
#endif
#define LATITUDE          12.34567          // [Latitude] Your location to be used with sunrise and sunset
#define LONGITUDE          1.23456          // [Longitude] Your location to be used with sunrise and sunset

#ifdef APP_TIMEZONE
#undef APP_TIMEZONE
#define APP_TIMEZONE      99                // use STD/DST
#endif

#ifdef  MY_LANGUAGE
#undef  MY_LANGUAGE
#endif
#define MY_LANGUAGE            de_DE        // German in Germany

#ifdef USE_IR_REMOTE
#undef USE_IR_REMOTE
#endif
#ifdef USE_IR_RECEICE
#undef USE_IR_RECEIVE
#endif

#ifdef USE_DOMOTICZ
#undef USE_DOMOTICZ
#endif

#ifdef USE_RULES
#undef USE_RULES
#define USE_SCRIPT
#define USE_SCRIPT_WEB_DISPLAY
#endif
#ifndef USE_SCRIPT
#define USE_SCRIPT
#define USE_SCRIPT_WEB_DISPLAY
#endif

#endif  // _USER_CONFIG_OVERRIDE_H_
