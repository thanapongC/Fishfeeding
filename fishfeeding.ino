#include <ArduinoJson.h>
#include <ESP8266WiFi.h> 
#include <FirebaseArduino.h>
#include <time.h>
#include <Stepper.h>

Stepper stepper(200,D5,D6,D7,D8);
//const char* ssid = "NOOMJUNGLE"; 
//const char* pass = "0876641405"; 

//const char* ssid = "NoomJungle"; 
//const char* pass = "0876641405"; 

//const char* ssid = ".iApp"; 
//const char* pass = "innovation"; 

const char* ssid = "ICTES_Lab-2G"; 
const char* pass = "officett4321"; 

//const char* ssid = "Not_2.4GHz"; 
//const char* pass = "0894122322"; 

const String deviceNumber = "140";

int timezone = 7 * 3600;
int dst = 0;

//define//https://basketofgrow.firebaseio.com
#define FIREBASE_HOST "basketofgrow.firebaseio.com"
#define FIREBASE_KEY "CPZ7GRwCunbmhTPXlXtSAynaJxH9BiRSPduqdGte"

void setup() {
  stepper.setSpeed(50);  
  Serial.begin(115200);  
 
  Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);

  Serial.println("Starting...");

       WiFi.begin(ssid, pass);
       while (WiFi.status() != WL_CONNECTED) 
       {
          delay(250);
          Serial.print(".");
       }

   Serial.println("WiFi connected");  
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
   
      configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
      Serial.println("\nLoading time");
              while (!time(nullptr)) {
              Serial.print("*");
              delay(1000);
              }
}

void loop() {
      
           configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");  
           time_t now = time(nullptr);
           struct tm* p_tm = localtime(&now);
   
    String startfeedfirebase = Firebase.getString("grow/"+deviceNumber + "/device/feedstart");
    int intstartfeedfirebase = startfeedfirebase.toInt();
    String endfeedfirebase = Firebase.getString("grow/"+deviceNumber + "/device/feedend");
    int intendfeedfirebase = endfeedfirebase.toInt();
    String timenowhour = String(p_tm->tm_hour);
    
    if(timenowhour == "0" || timenowhour == "1" || timenowhour == "2" || timenowhour == "3" || timenowhour == "4" ||
       timenowhour == "5" || timenowhour == "6" || timenowhour == "7" || timenowhour == "8" || timenowhour == "9")
    {
     timenowhour = "0"+timenowhour;
    }else{
     timenowhour = timenowhour;
      }
      
    String timenowmin = String(p_tm->tm_min);

    if(timenowmin == "0" || timenowmin == "1" || timenowmin == "2" || timenowmin == "3" || timenowmin == "4" ||
       timenowmin == "5" || timenowmin == "6" || timenowmin == "7" || timenowmin == "8" || timenowmin == "9")
    {
     timenowmin = "0"+timenowmin;
    }else{
     timenowmin = timenowmin;
      }

    String timenowsec = String(p_tm->tm_sec);

    if(timenowsec == "0" || timenowsec == "1" || timenowsec == "2" || timenowsec == "3" || timenowsec == "4" ||
       timenowsec == "5" || timenowsec == "6" || timenowsec == "7" || timenowsec == "8" || timenowsec == "9")
    {
     timenowsec = "0"+timenowsec;
    }else{
     timenowsec = timenowsec;
      }
      
    String timenow = timenowhour+timenowmin+timenowsec;
    int inttimenow = timenow.toInt();
  
              Serial.print("startfeedfirebasess : ");
              Serial.print(startfeedfirebase);
              Serial.print("/ ");
              Serial.print("endfeedfirebase : ");
              Serial.print(endfeedfirebase);
              Serial.println("/ ");
              delay(1000);
              if(intstartfeedfirebase <= inttimenow && intendfeedfirebase >= inttimenow){
                 stepper.step(200);
              }else{
                  stepper.step(0);
                  }

      }






    
      

