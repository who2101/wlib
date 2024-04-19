#if defined _wlib_mod_included
    #endinput
#endif
#define _wlib_mod_included

/*
	% operator for older sourcepawn version below 1.11
	
	@param value	Value
	@param div		Divider
*/
stock int IntMod(int value, int div) {
	return value - value/div * div;
}

/*
	% operator for older sourcepawn version below 1.11
	
	@param value	Value
	@param div		Divider
*/
stock float FloatMod(float value, float div) {
	return value - value/div * div;
}