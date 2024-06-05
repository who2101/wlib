#if defined _wlib_clients_included
    #endinput
#endif
#define _wlib_clients_included

#include <sdktools_functions>
#include <cstrike>

/*
	Prints message to admins
	
	@param fmt Formatting rules.
	@param any... Variable number of format parameters.
*/
stock void PrintToAdmins(const char[] fmt, any ...) {
	char bfr[1024];
	VFormat(bfr, sizeof bfr, fmt, 2);
	
	for(int i = 1; i <= MaxClients; i++)
		if(IsClientInGame(i) && !IsFakeClient(i) && GetUserFlagBits(i) & ADMFLAG_ROOT)
			PrintToChat(i, bfr);
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
	Sets client money
	
	@param client Client Index
	@param money Money
	@error Invalid entity
*/
stock void SetClientMoney(int client, int money) {
	SetEntData(client, FindSendPropInfo("CCSPlayer", "m_iAccount"), money, _, true);
}

/*
	Adds client money
	
	@param client Client Index
	@param money Money
	@error Invalid entity
*/
stock void AddClientMoney(int client, int money) {
	int offset = FindSendPropInfo("CCSPlayer", "m_iAccount");
	
	SetEntData(client, offset, GetEntData(client, offset)+money, _, true);
}

/*
	Gets client money
	
	@param client Client Index
	@param money Money
	@error Invalid entity
*/
stock int GetClientMoney(int client) {
	return GetEntData(client, FindSendPropInfo("CCSPlayer", "m_iAccount"));
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
stock int GetServerPlayers() {
	int count;

	for(int i = 1; i <= MaxClients; i++) if(IsClientInGame(i) && !IsFakeClient(i))
		count++;
	
	return count;
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
	Gets only numbers from steam3
	
	@param client Client Index
	@param onlynumber Only Numbers
	
	@return SteamID3 but only numbers
*/
stock int GetClientSteam3(int client, bool onlynumbers=true) {
	char auth[128];
	GetClientAuthId(client, AuthId_Steam3, auth, sizeof(auth));

	ReplaceString(auth, sizeof(auth), "[U:0:", NULL_STRING);
	ReplaceString(auth, sizeof(auth), "[U:1:", NULL_STRING);
	ReplaceString(auth, sizeof(auth), "]", NULL_STRING);

	return StringToInt(auth);
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

stock char[] GetClientIPEx(int client, bool remport=true) {
	char buffer[128];
	GetClientIP(client, buffer, sizeof(buffer), remport);
	return buffer;
}