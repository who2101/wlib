#if defined _wlib_hex_included
    #endinput
#endif
#define _wlib_hex_included

/*
	Generates random hex string
	
	Example: #FFFFFF
*/
char[] GenerateRandomHex() {
	int r = GetRandomInt(1, 255);
	int g = GetRandomInt(1, 255);
	int b = GetRandomInt(1, 255);
	
	char result[32];
	
	FormatEx(result, sizeof(result), "%s", RGBToHex((r << 16) | (g << 8) | b));
	return result;
}

/*
	Converts rgb into a hex string
	
	@param color RGB color
	
	@return hex string
*/
char[] RGBToHex(int color) {
	int r = color >> 16 & 0xFF;
	int g = color >> 8 & 0xFF;
	int b = color & 0xFF;
	
	char hex[7];
	FormatEx(hex, sizeof(hex), "%02X%02X%02X", r, g, b);
	
	return hex;
}

/*
	Converts the character representing a hexadecimal digit to its decimal representation.
	
	@param c Character

	@return decimal digit
*/
int strtohex(char c) {
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'A' && c <= 'F')
		return 10 + (c - 'A');
	else if (c >= 'a' && c <= 'f')
		return 10 + (c - 'a');
	
	return -1;
}