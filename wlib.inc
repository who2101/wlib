#if defined _wlib_included
    #endinput
#endif
#define _wlib_included

#define LIBRARY_NAME "wlib"

/* 
	You can add gamemodes here
	WARNING: Dont delete GM_CUSTOM 
*/
enum Gamemodes {
	GM_CUSTOM,
	GM_BHOP,
	GM_SURF,
	GM_DE,
	GM_CS,
	GM_CTF,
	GM_AWP,
	GM_35HP,
	GM_MULTI1V1,
	GM_AIM,
	GM_PROPHUNT,
	GM_PROPS,
	GM_DEATHRUN
}

char cssWeapons[][] = {
	"weapon_ak47", 
	"weapon_aug", 
	"weapon_awp",
	"weapon_deagle",
	"weapon_elite", 
	"weapon_famas",
	"weapon_fiveseven",
	"weapon_g3sg1",
	"weapon_galil",
	"weapon_glock", 
	"weapon_m249", 
	"weapon_m3",
	"weapon_m4a1", 
	"weapon_mac10", 
	"weapon_mp5navy",
	"weapon_p228", 
	"weapon_p90", 
	"weapon_scout",
	"weapon_sg550", 
	"weapon_sg552", 
	"weapon_tmp",
	"weapon_ump45", 
	"weapon_usp", 
	"weapon_xm1014"
};
char goWeapons[][] = {
	"weapon_nova",
	"weapon_xm1014",
	"weapon_sawedoff",
	"weapon_mag7",
	"weapon_m249",
	"weapon_negev",
	"weapon_mac10",
	"weapon_mp5sd",
	"weapon_mp7",
	"weapon_mp9",
	"weapon_ump45",
	"weapon_p90",
	"weapon_bizon",
	"weapon_galilar",
	"weapon_famas",
	"weapon_ak47",
	"weapon_m4a1",
	"weapon_m4a1_silencer",
	"weapon_aug",
	"weapon_sg556",
	"weapon_ssg08",
	"weapon_awp",
	"weapon_g3sg1",
	"weapon_scar20",
	"weapon_glock",
	"weapon_usp_silencer",
	"weapon_hkp2000",
	"weapon_fiveseven",
	"weapon_elite",
	"weapon_p250",
	"weapon_tec9",
	"weapon_cz75a",
	"weapon_deagle",
	"weapon_revolver",
	"weapon_knife",
	"weapon_fists",
	"weapon_hammer",
	"weapon_spanner",
	"weapon_axe",
	"weapon_taser",
	"weapon_molotov",
	"weapon_incgrenade",
	"weapon_decoy",
	"weapon_flashbang",
	"weapon_hegrenade",
	"weapon_smokegrenade",
	"weapon_tagrenade",
	"weapon_frag_grenade",
	"weapon_diversion",
	"weapon_firebomb",
	"weapon_snowball"
};

/*
	Get weapon list for current game
	Note: This function return string with weapons from library

	@param buffer Buffer
	@param length Buffer length
	
	@error Game is not CSS or CSGO
*/
stock void GetWeaponsList(char[] buffer, int length) {
	switch(GetEngineVersion()) {
		case Engine_CSGO: strcopy(buffer, length, goWeapons); // CSGO
		case Engine_SourceSDK2006: strcopy(buffer, length, cssWeapons); // CSS v34
		case Engine_CSS: strcopy(buffer, length, cssWeapons); // CSS Steam
		default: ThrowError("GetWeapons: Library '%s' only for CSS/CSGO", LIBRARY_NAME);
	}
}

/*
	Get weapon list for current game
	Note: This function return string with weapons from library

	@error Game is not CSS or CSGO

	@return string
*/
stock char[] GetWeaponsList2() {
	switch(GetEngineVersion()) {
		case Engine_CSGO: return goWeapons; // CSGO
		case Engine_SourceSDK2006: return cssWeapons; // CSS v34
		case Engine_CSS: return cssWeapons; // CSS Steam
		default: ThrowError("GetWeapons: Library '%s' only for CSS/CSGO", LIBRARY_NAME);
	}
}

/*
	Get gamemode
	Note: If gamemode not found then returns GM_CUSTOM
	
	@return Gamemode (enum)
*/
stock Gamemodes GetGamemode() {
	switch(GetCurrentMapPrefix2()) {
		case "bhop": return GM_BHOP;
		case "surf": return GM_SURF;
		case "de": return GM_DE;
		case "cs": return GM_CS;
		case "ctf": return GM_CTF;
		case "awp": return GM_AWP;
		case "35hp": return GM_35HP;
		case "am": return GM_MULTI1V1;
		case "1v1": return GM_MULTI1V1;
		case "aim": return GM_AIM;
		case "prop": return GM_PROPHUNT;
		case "props": return GM_PROPS;
		case "deathrun": return GM_DEATHRUN;
		case "dr": return GM_DEATHRUN;
	}
	
	return GM_CUSTOM;
}

/*
	Toggles MoveType between MOVETYPE_NONE and MOVETYPE_WALK
	
	@param client Client Index
	@error Invalid client index, client not in game
*/
stock void ToggleFreeze(int client) {
	SetEntityMoveType(int client, GetEntityMoveType(int client) == MOVETYPE_NONE ? MOVETYPE_WALK : MOVETYPE_NONE);
}

/*
	Sets client MoveType on MOVETYPE_NONE or MOVETYPE_WALK
	
	@param client Client Index
	@param freeze Freeze or unfreeze
	@error Invalid client index, client not in game
*/
stock void FreezeClient(int client, bool freeze=true) {
	SetEntityMoveType(client, freeze ? MOVETYPE_NONE : MOVETYPE_WALK);
}

/*
	Get map prefix
	
	@param map Map
	@return string
*/
stock char[] GetMapPrefix2(char[] map) {
	char buffer[2][10];
	ExplodeString(map, "_", buffer, 2, 10);
	
	return buffer[0];
}

/*
	Get current map prefix
	
	@return string
*/
stock char[] GetCurrentMapPrefix2() {
	char map[64], buffer[2][10];
	GetCurrentMap(map, 64);
	ExplodeString(map, "_", buffer, 2, 10);
	
	return buffer[0];
}

/*
	Get map prefix
	
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
	Get current map prefix
	
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
	Get current map
	
	@return current map
*/
stock char[] GetCurrentMap2() {
	char map[64];
	GetCurrentMap(map, 64);

	return map;
}

/*
	Get players count in client team
	
	@param client	Client index
*/
stock int GetClientTeamCount(int client) {
	return GetTeamClientCount(GetClientTeam(client));
}

/*
	Get server online
	
	@param alive Only alive players
	
	@return online
*/
stock int GetOnline() {
	int count;
	
	for(int i = 1; i <= MaxClients; i++) if(IsClientInGame(i) && !IsFakeClient(i))
	{
		count++;
	}
	
	return count;
}

/*
	Like % from newer sourcepawn versions
	
	@param value	Value
	@param div		Divider
*/
stock int IntMod(int value, int div) {
  return value - value/div * div;
}

/*
	Like % from newer sourcepawn versions
	
	@param value	Value
	@param div		Divider
*/
stock float FloatMod(float value, float div) {
  return value - value/div * div;
}

/*
	Get min or max value from array
	
	@param array Array
	
	@return value
*/
stock int GetIntValue(const int[] array, bool max=true)
{
	static int size = sizeof(array[]);
	static int[] buffer = new int[size];
	
	for(int i; i <= size; i++)
		buffer[i] = array[i];
	
	SortIntegers(buffer, size, max ? Sort_Descending : Sort_Ascending);

	return buffer[0];
}

/*
	Get min or max value from array
	
	@param array Array
	
	@return value
*/
stock float GetFloatValue(const float[] array, bool max=true)
{
	static int size = sizeof(array[]);
	static float[] buffer = new int[size];

	for(int i; i <= size; i++)
		buffer[i] = array[i];

	SortFloats(buffer, size, max ? Sort_Descending : Sort_Ascending);

	return buffer[0];
}

/*
	Gets count of alive players
	
	@param spec Add specs
	
	@return value
*/
stock int GetPlayersAlive(bool spec) {
	int count;
	
	for(int i = 1; i <= MaxClients; i++) if (IsClientInGame(i) && !IsFakeClient(i) && IsPlayerAlive(i))
	{
		switch(spec) {
			case true: if (GetClientTeam(i) == 1) count++;
			case false:count++;
		}
	}

	return count;
}

/*
	Gets dead players
	
	@return value
*/
stock int GetDeadPlayers() {
	int count;

	for(int i = 1; i <= MaxClients; i++) if(IsClientInGame(i) && !IsFakeClient(i) && GetClientTeam(i) > 1 && !IsPlayerAlive(i))
	{
		count++;
	}
	
	return count;
}

/*
	Gets dead players from team
	
	@param team Team Index
	
	@return value
*/
stock int GetDeadTeamPlayers(int team) {
	int count;

	for(int i = 1; i <= MaxClients; i++) if(IsClientInGame(i) && !IsFakeClient(i) && GetClientTeam(i) == team && !IsPlayerAlive(i))
	{
		count++;
	}
	
	return count;
}

/*
	Check client valid
	
	@param client Client Index
	
	@return true if client in game
*/
stock bool IsValidClient(int client) {
	return IsClientInGame(client) && !IsFakeClient(client);
}

/*
	Get random player
	
	@return player index
*/
stock int GetRandomClient() {
	int[] players = new int[MAXPLAYERS+1];

	for(int i = 1, j = 0; i <= MaxClients; i++) if(IsValidClient(i))
	{
		players[j] = i;
		j++;
	}

	return players[GetRandomInt(0, sizeof(players[]))];
}

/*
	Delete clients weapons
	
	@param client Client Index
*/
stock void StripWeapons(int client) {
	int weapon;

	for (int slot = CS_SLOT_PRIMARY; slot <= CS_SLOT_C4; slot++)
	{
		while ((weapon = GetPlayerWeaponSlot(client, slot)) != -1)
		{
			RemovePlayerItem(client, weapon);
			RemoveEdict(weapon);
		}
	}
}

/*
	Gets m_iName from entity
	
	@param entity Entity Index
	
	@return Entity Name
*/
stock char[] GetPropName(int entity) {
	char Name[64];

	if (IsValidEntity(entity))
		GetEntPropString(entity, Prop_Data, "m_iName", Name, sizeof(Name));

	return Name;
}

/*
	Gets a network property as a string
	
	@param entity Edict Index
	@param type Property type
	@param prop Property to use
	@param element Element # (starting from 0) if property is an array
	
	@return string
	
	@error Invalid entity, offset out of reasonable bounds, or property is not a valid string.
*/
stock char[] GetEntPropString2(int entity, PropType type, const char[] prop, int element = 0) {
	char bff[128];
	GetEntPropString(entity, Prop_Data, prop, bff, sizeof(bff), element);
	
	return bff;
}

/*
	Returns the client`s name.
	
	@param client Client Index
	
	@return True on success, false otherwise
	@error If the client is not connected an error will be thrown.
*/
stock char[] GetClientName2(int client) {
	static char buffer[128];
	GetClientName(client, buffer, 128);
	
	return buffer;
}

/*
	Returns the client`s name.
	
	@param client Client Index
	
	@return True on success, false otherwise
	@error If the client is not connected an error will be thrown.
*/
stock char[] GetClientAuthId2(int client, AuthIdType type=AuthId_Steam2, bool validate=true) {
	static char buffer[128];
	GetClientAuthId(client, type, buffer, sizeof(buffer), validate);
	
	return buffer;
}

/*
	Returns the client`s name.
	
	@param client Client Index (If 0 - send to all)
	@param duration Alert duration
	@param msg Message
	@param ... Format
*/
stock void AlertText(int client=0, int duration, const char[] msg, any ...) {
    Event event = CreateEvent("show_survival_respawn_status", true);

    static char buff[512];
    VFormat(buff, sizeof(buff), msg, 4);
    event.SetString("loc_token", buff);
    event.SetInt("duration", duration);
    event.SetInt("userid", -1);

    if(client) {
        event.FireToClient(client);
        event.Close();

        return;
    }

    for(int i = 1; i <= MaxClients; i++)
        if(IsClientInGame(i) && !IsFakeClient(i))
            event.FireToClient(i);

    event.Close();
}

stock void GetTeamPlayers(int &buffer, int team) {
	for(int j, i = 1; i <= MaxClients; i++) if(IsClientInGame(i) && !IsFakeClient(i) && GetClientTeam(i) == team)
	{
		buffer[j] = i;
		j++;
	}
}

stock int[] GetTeamPlayers2(int team) {
	int[] buffer = new int[MAXPLAYERS+1];
	
	for(int j, i = 1; i <= MaxClients; i++) if(IsClientInGame(i) && !IsFakeClient(i) && GetClientTeam(i) == team)
	{
		buffer[j] = i;
		j++;
	}
	
	return buffer;
}

stock char[] GetClientIP2(int client, bool remport=true) {
	char buffer[128];
	GetClientIP(client, buffer, sizeof(buffer), remport);
	return buffer;
}

/*
	Returns the days, hours, minutes and seconds in string.
	
	@param seconds Seconds
	
	@return time string
*/
char[] CalculateTime(int seconds) {
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