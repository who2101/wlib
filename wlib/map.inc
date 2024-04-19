#if defined _wlib_map_included
    #endinput
#endif
#define _wlib_map_included

/*
	Gets map prefix
	
	@param map Map
	@return string
*/
stock char[] GetMapPrefixEx(char[] map) {
	char buffer[2][10];
	ExplodeString(map, "_", buffer, 2, 10);
	
	return buffer[0];
}

/*
	Gets current map prefix
	
	@return string
*/
stock char[] GetCurrentMapPrefixEx() {
	char map[64], buffer[2][10];
	GetCurrentMap(map, 64);
	ExplodeString(map, "_", buffer, 2, 10);
	
	return buffer[0];
}

/*
	Gets map prefix
	
	@param map		Map
	@param buffer	Buffer for prefix
	@param length	Buffer length
*/
stock void GetMapPrefix(char[] map, char[] buffer, int length) {
	char buff[2][10];
	ExplodeString(map, "_", buff, 2, 10);
	
	strcopy(buffer, length, buff[0]);
}

/*
	Gets current map prefix
	
	@param buffer	Buffer for prefix
	@param length	Buffer length
*/
stock void GetCurrentMapPrefix(char[] buffer, int length) {
	char map[64], buff[2][10];
	GetCurrentMap(map, 64);
	ExplodeString(map, "_", buff, 2, 10);

	strcopy(buffer, length, buff[0]);
}

/*
	Gets current map
	
	@return current map
*/
stock char[] GetCurrentMapEx() {
	char map[64];
	GetCurrentMap(map, 64);

	return map;
}