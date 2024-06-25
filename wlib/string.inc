#if defined _wlib_string_included
    #endinput
#endif
#define _wlib_string_included

/*
	Removes all spaces and leaves only 1
	
	@param str String
*/
stock void removeExtraSpaces(char[] str) {
    int i = 0, j = 0;
    bool space = false;

    while (str[i]) {
        if (str[i] == ' ') {
            if (!space) {
                str[j++] = str[i];
                space = true;
            }
        } else {
            str[j++] = str[i];
            space = false;
        }
        i++;
    }
    str[j] = '\0';
}

stock char[] subStr(char[] myString, int startPos, int len = -1)
{
    char outStr[1024];

    if(len == -1) strcopy(outStr, sizeof outStr, myString[startPos]);
    else
    {
        strcopy(outStr, len, myString[startPos]);
        outStr[len] = 0;
    }

    return outStr; 
}

/*
	Checks if the whole string consists of spaces
	
	@param str String
*/
stock bool IsWhitespaced(const char[] str) {
	for(int i; i < strlen(str); i++)
		if(str[i] != ' ')
			return false;
	
	return true;
}