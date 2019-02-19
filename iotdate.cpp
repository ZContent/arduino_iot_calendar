/*
 * Smart Date Icons
 * Dan Cogliano
 * DanTheGeek.com
 */

#include "iotdate.h"

iotDate::iotDate(long timeoffset)
{
  _timeoffset = timeoffset * 60;
  initTime();
}

iotDate::iotDate(iotCalendar &iotc)
{
	HTTPClient http;
	String url, jsondata;
	jsondata = iotc.getTZOffset();
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(jsondata);

	if (!root.success()) {
		Serial.println("Timezone parseObject() failed");
	}
	else
	{
		int timeoffset = root["offset"];
		_timeoffset = timeoffset * 60;
		Serial.println("got timeoffset " + String(_timeoffset));
		initTime();
	}
}

void iotDate::initTime()
{
  NTPClient timeClient(_timeoffset);
  // Initialize a NTPClient to get time
  timeClient.begin();
  timeClient.forceUpdate();
  time_t _timestamp = timeClient.getRawTime();

  struct tm *t = gmtime(&_timestamp);
  _month = t->tm_mon;
  _day = t->tm_mday;
  _wday = t->tm_wday;
  _year = t->tm_year + 1900;
  _hour = t->tm_hour;
  _minute = t->tm_min;
  _second = t->tm_sec;
}

const char *iotDate::getShortMonthString(int month)
{
	  const char* months[] = {
	  SHORT_MONTH_0,SHORT_MONTH_1,SHORT_MONTH_2,SHORT_MONTH_3,SHORT_MONTH_4,SHORT_MONTH_5,
	  SHORT_MONTH_6,SHORT_MONTH_7,SHORT_MONTH_8,SHORT_MONTH_9,SHORT_MONTH_10,SHORT_MONTH_11
	  };
	return months[month];
}

const char *iotDate::getMonthString(int month)
{
	const char* months[] = {
		MONTH_0,MONTH_1,MONTH_2,MONTH_3,MONTH_4,MONTH_5,
		MONTH_6,MONTH_7,MONTH_8,MONTH_9,MONTH_10,MONTH_11
	};
	return months[month%12];
}

const char *iotDate::getDOWString(int dow)
{
	  const char* dows[7] = {
		  DOW_0,DOW_1,DOW_2,DOW_3,DOW_4,DOW_5,DOW_6
	  };
	return dows[dow%7];
}

const char *iotDate::getShortDOWString(int dow)
{
	  const char* dows[7] = {
		  SHORT_DOW_0,SHORT_DOW_1,SHORT_DOW_2,SHORT_DOW_3,SHORT_DOW_4,SHORT_DOW_5,SHORT_DOW_6
	  };
	return dows[dow%7];
}

bool iotDate::isLeapYear(int year) {
	if (year % 4 != 0) return false;
	if (year % 100 == 0 && year % 400 != 0) return false;
	if (year % 400 == 0) return true;
	return true;
}

int iotDate::getDaysInMonth(int month, int year) {
	int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	Serial.println("getDaysInMonth " +String(month) + " " + String(year));
	Serial.println(daysInMonth[month%12]);
	if (month != 1) return daysInMonth[month%12];
	return isLeapYear(year) ? 29 : 28;
}

