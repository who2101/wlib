#if defined _wlib_included
    #endinput
#endif
#define _wlib_included

#include <cstrike>
#include <sdktools_functions>

/*
	Toggles MoveType between MOVETYPE_NONE and MOVETYPE_WALK
	
	@param client Client Index
	@error Invalid client index, client not in game
*/
stock bool IsStuckInEnt(int client, int ent){
	float vecMin[3], vecMax[3], vecOrigin[3];
	
	GetClientMins(client, vecMin);
	GetClientMaxs(client, vecMax);
	
	GetClientAbsOrigin(client, vecOrigin);
	
	TR_TraceHullFilter(vecOrigin, vecOrigin, vecMin, vecMax, MASK_ALL, TraceRayHitOnlyEnt, ent);
	return TR_DidHit();
}

stock bool TraceRayHitOnlyEnt(int entityhit, int mask, data) {
	return entityhit==data;
}

/*
	Toggles MoveType between MOVETYPE_NONE and MOVETYPE_WALK
	
	@param client Client Index
	@error Invalid client index, client not in game
*/
stock void ToggleFreeze(int client) {
	SetEntityMoveType(client, GetEntityMoveType(client) == MOVETYPE_NONE ? MOVETYPE_WALK : MOVETYPE_NONE);
}

/*
	Changes player collision
	
	@param client 		Client Index
	@param collision	Collision
	
	@error Invalid client index, client not in game
*/
stock void ChangePlayerCollision(int client, bool collision) {
	SetEntData(client, FindSendPropInfo("CBaseEntity", "m_CollisionGroup"), collision?5:2, 4, true);
}

/*
	Sets client MoveType on MOVETYPE_NONE or MOVETYPE_WALK
	
	@param client Client Index
	@param freeze Freeze or unfreeze
	@error Invalid client index, client not in game
*/
stock void FreezeClient(int client, bool freeze=true){
    SetEntityMoveType(client, freeze ? MOVETYPE_NONE : MOVETYPE_WALK);
    SetEntityFlags(client, freeze ? (GetEntityFlags(client) | FL_FROZEN) : (GetEntityFlags(client) & ~FL_FROZEN));
}

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

/*
	Gets players count in client team
	
	@param client	Client index
*/
stock int GetClientTeamCount(int client) {
	return GetTeamClientCount(GetClientTeam(client));
}

/*
	Gets server online
	
	@return value
*/
stock int GetServerOnline() {
	int count;
	
	for(int i = 1; i <= MaxClients; i++) if(IsClientInGame(i) && !IsFakeClient(i))
	{
		count++;
	}
	
	return count;
}

/*
	% operator for older sp versions
	
	@param value	Value
	@param div		Divider
*/
stock int IntMod(int value, int div) {
  return value - value/div * div;
}

/*
	% operator for older sp versions
	
	@param value	Value
	@param div		Divider
*/
stock float FloatMod(float value, float div) {
  return value - value/div * div;
}

/*
	Gets count of alive players
	
	@param spec Add spectators
	
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
	Gets random player
	
	Note: May not work
	
	@return player index
*/
stock int GetRandomClient() {
	int[] players = new int[MAXPLAYERS+1];

	for(int i = 1, j = 0; i <= MaxClients; i++) if(IsClientInGame(i) && !IsFakeClient(i))
	{
		players[j] = i;
		j++;
	}

	return players[GetRandomInt(0, sizeof(players[]))];
}

/*
	Removes client weapons
	
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
	
	@return string
	@error If the client is not connected an error will be thrown.
*/
stock char[] GetClientNameEx(int client) {
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
stock char[] GetClientAuthIdEx(int client, AuthIdType type=AuthId_Steam2, bool validate=true) {
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
	
	Note: CSGO ONLY
*/
stock void AlertText(int client=0, int duration, const char[] msg, any ...) {
	if(GetEngineVersion() != Engine_CSGO) {
		LogError("wlib::AlertText cant used in this game");
		return;
	}
	
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

stock char[] GetClientIPEx(int client, bool remport=true) {
	char buffer[128];
	GetClientIP(client, buffer, sizeof(buffer), remport);
	return buffer;
}

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

/*
	Gets only numbers from steam3
	
	@param client Client Index
	@param onlynumber Only Numbers
	
	@return SteamID3 but only numbers
*/
stock int GetClientSteam3(int client, bool onlynumbers) {
	char auth[128];
	GetClientAuthId(client, AuthId_Steam3, auth, sizeof(auth));

	ReplaceString(auth, sizeof(auth), "[U:0:", NULL_STRING);
	ReplaceString(auth, sizeof(auth), "[U:1:", NULL_STRING);
	ReplaceString(auth, sizeof(auth), "]", NULL_STRING);

	return StringToInt(auth);
}

/*
	SQL_Query but with auto lock/unlock database
	
	@param database A database Handle
	@param query Query string
	@param len Optional parameter to specify the query length, in bytes.
	
	@return A new Query Handle on success, INVALID_HANDLE otherwise
	@error Invalid database handle
*/
stock DBResultSet SQL_QueryEx(Database database, const char[] query, int len=-1, bool autofetch=false) {
	SQL_LockDatabase(database);
	DBResultSet results = SQL_Query(database, query, len);
	SQL_UnlockDatabase(database);

	if(autofetch) {
		results.FetchRow();
	}

	return results;
}

stock void SendPanelToAll(int from, char[] msg)
{
	char title[100];
	Format(title, 64, "%N:", from);
	
	ReplaceString(msg, 192, "\\n", "\n");
	
	Panel mSayPanel = new Panel();
	mSayPanel.SetTitle(title);
	mSayPanel.DrawItem("", ITEMDRAW_SPACER);
	mSayPanel.DrawText(msg);
	mSayPanel.DrawItem("", ITEMDRAW_SPACER);
	mSayPanel.CurrentKey = GetMaxPageItems(mSayPanel.Style);
	mSayPanel.DrawItem("Exit", ITEMDRAW_CONTROL);

	for(int i = 1; i <= MaxClients; i++)
	{
		if(IsClientInGame(i) && !IsFakeClient(i))
		{
			mSayPanel.Send(i, Handler_DoNothing, 10);
		}
	}

	delete mSayPanel;
}

stock void SendPanelMsgToClient(int client, const char[] title, char[] message)
{	
	ReplaceString(message, 192, "\\n", "\n");
	
	Panel mSayPanel = new Panel();
	mSayPanel.SetTitle(title);
	mSayPanel.DrawItem("", ITEMDRAW_SPACER);
	mSayPanel.DrawText(message);
	mSayPanel.DrawItem("", ITEMDRAW_SPACER);
	mSayPanel.CurrentKey = GetMaxPageItems(mSayPanel.Style);
	mSayPanel.DrawItem("Exit", ITEMDRAW_CONTROL);
			
	mSayPanel.Send(client, Handler_DoNothing, 10);

	delete mSayPanel;
}

stock int Handler_DoNothing(Menu menu, MenuAction action, int param, int param2) {
	return 0;
}