#include "iotcalendar.h"

// Initialize iotCalendar class
iotCalendar::iotCalendar(bool secure)
{
	_secure = secure;
	setDebug(0);
	resetError();
}

// Initialize iotCalendar class with API key and tzid
iotCalendar::iotCalendar(String apikey, String tzid, bool secure)
{
	_apikey = apikey;
	_tzid = tzid;
	_secure = secure;

	setDebug(0);
	resetError();
}

// Get timezone offset using IoT Calendar service
// pretty: format JSON data for easy viewing
String iotCalendar::getTZOffset(bool pretty)
{
	String scheme = "http";
	if(_secure)
		scheme = "https";
	String url = scheme + "://iotcalendar.org/iottzoffset?apikey=" + _apikey + "&tzid=" + _tzid;
	if(pretty)
		url += "&pretty";
	String jsonstring = _getURLResponse(url);
	return jsonstring;
}

// Get events for specified day(s) using the IoT Calendar service
// url: icalendar URL to retrieve events
// days: comma separated list of event days to retrieve events from
// size: maximum # of events to return
// pretty: format JSON data for easy viewing
String iotCalendar::getDayEvents(String url, String days, int size, bool pretty)
{
	String newurl,jsonstring;

	String scheme = "http";
	if(_secure)
		scheme = "https";
	newurl = scheme + "://iotcalendar.org/iotevents?apikey=" + _apikey + "&tzid=" + _tzid + "&url=" + url;
	newurl += "&days=" + days;
	newurl += "&size=" + String(size);
	if(pretty)
		newurl += "&pretty";
	jsonstring = _getURLResponse(newurl);
	return jsonstring;
}

// Retrieve page response from given URL
String iotCalendar::_getURLResponse(String url)
{

	String jsonstring = "";
	_debugPrintln(1,"getting url: " + url);
	if(_http.begin(url))
	{
		_debugPrint(1,"[HTTP] GET...\n");
		// start connection and send HTTP header
		int httpCode = _http.GET();

		// httpCode will be negative on error
		if (httpCode > 0) {
			// HTTP header has been send and Server response header has been handled
			_debugPrintln(1,"[HTTP] GET... code: " + String(httpCode));

			// file found at server
			if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
			jsonstring = _http.getString();
			_debugPrintln(1,jsonstring);
		}
		} else {
			_debugPrintln(1,"[HTTP] GET... failed, error: " + _http.errorToString(httpCode));
			_errorcode = httpCode;
			_errorstring = _http.errorToString(_errorcode);
		}
		_http.end();
	}
	else {
		_debugPrintln(1,"[HTTP] Unable to connect");
	}
	return jsonstring;
}

void iotCalendar::_debugPrint(int debuglevel, String msg)
{
	if(_debuglevel >= debuglevel)
	{
		Serial.print(msg);
	}
}

void iotCalendar::_debugPrintln(int debuglevel, String msg)
{
	if(_debuglevel >= debuglevel)
	{
		Serial.println(msg);
	}
}