#if defined _wlib_map_included
    #endinput
#endif
#define _wlib_map_included

/**
 * Gets map prefix
 * 
 * @param map Map
 * @param buffer Buffer
 * @param length Buffer Length
 */
stock void GetMapPrefix(char[] map, char[] buffer, int length) {
	char buff[2][10];
	ExplodeString(map, "_", buff, 2, 10);
	
	strcopy(buffer, length, buff[0]);
}

/**
 * Gets current map prefix
 * @param buffer  Buffer
 * @param length  Buffer length
 */
stock void GetCurrentMapPrefix(char[] buffer, int length) {
	char map[64], buff[2][10];
	GetCurrentMap(map, 64);
	ExplodeString(map, "_", buff, 2, 10);

	strcopy(buffer, length, buff[0]);
}