/*
 * The IoT Calendar Library for Arduino
 *
 * Written by Dan Cogliano - DanTheGeek.com
 *
 * The iotCalendar class utilizes the IoT Calendar Service at
 * iotcalendar.org
 */

#ifndef IOT_CALENDAR_H
#define IOT_CALENDAR_H

#include <time.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#else
  #include <WiFi.h>
#endif
//#include <HTTPClient.h>
#include <ESPHTTPClient.h>

class iotCalendar
{
	public:
		iotCalendar(bool secure = false);
		iotCalendar(String apikey, String tzid, bool secure = false);
		String getTZOffset(bool pretty = false);
		String getDayEvents(String url, String days, int size = 10, bool pretty = false);
		void setAPIKey(String apikey){ _apikey = apikey;};
		void setTzid(String tzid){ _tzid = tzid;};
		void setDebug(int debuglevel){_debuglevel = debuglevel;};
		void resetError(){_errorcode = 0; _errorstring = "";};
		int getErrorCode(){return _errorcode;};
		String getError(){return _errorstring;};

	private:
		bool _secure;
		String _apikey;
		String _tzid;
		HTTPClient _http;
		String _getURLResponse(String url);
		int _debuglevel;
		int _errorcode;
		String _errorstring;
		void _debugPrint(int debuglevel, String msg);
		void _debugPrintln(int debuglevel, String msg);
};

#endif
