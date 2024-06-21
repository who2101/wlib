#if defined _wlib_string_included
    #endinput
#endif
#define _wlib_string_included

/*
	Removes all spaces and leaves only 1
	
	@param str String
*/
void removeExtraSpaces(char[] str) {
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

/*
	Checks if the whole string consists of spaces
	
	@param str String
*/
bool IsWhitespaced(const char[] str) {
	for(int i; i < strlen(str); i++)
		if(str[i] != ' ')
			return false;
	
	return true;
}