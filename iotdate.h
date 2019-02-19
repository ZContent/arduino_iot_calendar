/*
 * The IoT Calendar Library for Arduino
 *
 * Written by Dan Cogliano - DanTheGeek.com
 *
 * The iotDate provides date routines for use with the IoT Calendar
 * Service.
 *
 * More information is at iotcalendar.org
 */

#ifndef IOT_DATE_H
#define IOT_DATE_H

#include <time.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#else
  #include <WiFi.h>
#endif
//#include <HTTPClient.h>
#include <ESPHTTPClient.h>
#include <ArduinoJson.h>        //https://github.com/bblanchon/ArduinoJson
#include <NTPClient.h>			//https://github.com/arduino-libraries/NTPClient

#include "iotcalendar.h"
#include "language_en.h"

class iotDate
{
	public:
		iotDate(long timeoffset);
		iotDate(iotCalendar &iotc);
		long getMonth(){return _month;};
		long getDay(){return _day;};
		long getWDay(){return _wday;};
		long getYear(){return _year;};
		long getHour(){return _hour;};
		long getMinute(){return _minute;};
		long getSecond(){return _second;};
		long getTimeOffset(){return _timeoffset;};
		time_t getTimeStamp(){return _timestamp;};
		const char *getShortMonthString(int month);
		const char *getMonthString(int month);
		const char *getDOWString(int dow);
		const char *getShortDOWString(int dow);

		bool isLeapYear(int year);
		bool isWeekend(int dow){return dow == 0 || dow == 6;};
		bool isWeekday(int dow){return !(dow == 0 || dow == 6);};
		int getDaysInMonth(int month, int year);
    	int getStringLength(char *str, int strlen = 0);

	private:
		time_t _timestamp;
		long _timeoffset;
		long _hour;
		long _minute;
		long _second;
		long _month;
		long _day;
		long _wday;
		long _year;

		void initTime();

};

#endif
