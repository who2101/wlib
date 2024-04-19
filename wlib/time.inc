#if defined _wlib_time_included
    #endinput
#endif
#define _wlib_time_included

#include "wlib/mod.inc"

/*
	Returns the days, hours, minutes and seconds in string.
	
	@param seconds Seconds
	
	@return time string
*/
stock char[] CalculateTime(int seconds) {
	char buffer[128];

	int minutes = seconds / 60;
	int remainingSeconds = IntMod(seconds, 60);
	int hours = minutes / 60;
	int remainingMinutes = IntMod(seconds / 60, 60);
	int days = hours / 24;
	int remainingHours = IntMod(hours, 24);

	FormatEx(buffer, sizeof(buffer), "%d д. %d ч. %d мин. %d сек.", days, remainingHours, remainingMinutes, remainingSeconds);
	return buffer;
}