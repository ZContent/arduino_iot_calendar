/*
 * iotcalendar_example
 * 
 * This example shows how to retrieve the timezone offset and events from an 
 * iCalendar subscription URL. More details about the IoT Calendar service
 * can be found at iotcalendar.org
 * 
 */
 
#include <iotcalendar.h>
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson

//String wifi_ssid="ssid";
//String wifi_password="password";

// Get an API key from IoTCalendar.org
//String apikey ="0000-0000-0000";
String apikey = "A8B4-2BE7-8F98";
// Select your timezone, using a PHP Timezone name
String tzid = "America/New_York";
// Choose your iCalendar URL to retrieve events
String icalurl = "http://americanhistorycalendar.com/eventscalendar?format=ical";
// Select date of events, either in "YYYYMMDD" format or relative day ("-1": yesterday).
// Search multiple dates by using a comma separated list of dates
String date ="20180828";

void setup() {
  iotCalendar iotc(apikey, tzid); 
  iotc.setDebug(1);
  
  Serial.begin(115200);
  //while(!Serial);

  Serial.print("Connecting to WiFi ");
  WiFi.begin(wifi_ssid.c_str(), wifi_password.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("connected");

	// get timezone offset in minutes
	String jsontz = iotc.getTZOffset();
  if(jsontz.length() > 0)
  {
    StaticJsonBuffer<400> jsonBuffer;
    JsonObject &jsonroot = jsonBuffer.parseObject(jsontz);
    if (!jsonroot.success()) {
      Serial.println("json parseObject() failed");
    }
    else
    {
      if(jsonroot["errors"].size() > 0)
      {
        String strerror = jsonroot["errors"][0];
        Serial.println("Error: " + strerror);
      }
      else
      {
        int offset = jsonroot["offset"];
        Serial.println("timezone offset is " + String(offset));
        
        // Any warnings? Display them here
        if(jsonroot["warnings"].size() > 0)
        {
          String strerror = jsonroot["warnings"][0];
          Serial.println("Warning: " + strerror);
        }
      }
    }
  }
 	
	// get events for specified date from an iCalendar subscription URL
	String jsonevents = iotc.getDayEvents(icalurl, date, 4, true);
  if(jsonevents.length() > 0)
  {
    StaticJsonBuffer<2000> jsonBuffer;
    JsonObject &jsonroot = jsonBuffer.parseObject(jsonevents);
    if (!jsonroot.success()) {
      Serial.println("json parseObject() failed");
    }
    else
    {
      if(jsonroot["errors"].size() > 0)
      {
        String strerror = jsonroot["errors"][0];
        Serial.println("Error: " + strerror);
      }
      else
      {
        Serial.println("Events for " + date + String(":"));
        for(int i = 0; i < jsonroot["events"].size(); i++)
        {
          String title = jsonroot["events"][i]["summary"];
          Serial.println(String(i + 1) + ": " + title);
        }
        
        // Any warnings? Display them here
        if(jsonroot["warnings"].size() > 0)
        {
          String strerror = jsonroot["warnings"][0];
          Serial.println("Warning: " + strerror);
        }
      }
    }
  }  
	Serial.println("done");
}

void loop() {

}
