#if defined _wlib_clients_included
    #endinput
#endif
#define _wlib_clients_included

#include <sdktools_functions>
#include <cstrike>

/*
	Replaces player weapon or just giving them

	@error Invalid client index, client not in game
*/
stock bool ReplaceWeapon(int client, const char[] weapon, int slot = -1) {
	if(client <= 0)
		return false;
	
	if(!IsClientInGame(client) || IsFakeClient(client))
		return false;

	if (slot != -1) {
		int wpn;
		
		if ((wpn = GetPlayerWeaponSlot(client, slot)) != -1)
			RemoveEntity(wpn);
	}
	
	GivePlayerItem(client, weapon);

	return true;
}

/*
	Removes all dropped weapons

	@error Offset 'CBaseCombatWeapon::m_hOwnerEntity' not found
*/
stock void RemoveAllDroppedWeapon() {
	int offset;

	if ((offset = FindSendPropInfo("CBaseCombatWeapon", "m_hOwnerEntity")) == -1)SetFailState("Offset 'CBaseCombatWeapon::m_hOwnerEntity' not found!");

	char clsname[128];
	for (int ent = GetEntityCount(); MaxClients < ent; ent--)if (IsValidEdict(ent) && GetEdictClassname(ent, clsname, 8) && strncmp(clsname, "weapon_", 7) == 0 && GetEntDataEnt2(ent, offset) == -1)
	{
		RemoveEdict(ent);
	}
}

/*
	Prints message to admins
	
	@param fmt Formatting rules.
	@param any... Variable number of format parameters.
*/
stock void PrintToAdmins(const char[] fmt, any ...) {
	char bfr[1024];
	VFormat(bfr, sizeof bfr, fmt, 2);
	
	for(int i = 1; i <= MaxClients; i++)
		if(IsClientInGame(i) && !IsFakeClient(i) && GetUserFlagBits(i) & ADMFLAG_GENERIC)
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
	Gets server online
	
	@return value
*/
stock int GetCurrentPlayers() {
	int count;

	for(int i = 1; i <= MaxClients; i++) if(IsClientInGame(i) && !IsFakeClient(i))
		count++;
	
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

/**
 * Gets steam3 from client
 * 
 * @param Client Client Index
 * 
 * @error returns -1 if GetClientAuthId is false
 */
stock int GetClientSteam3(int client) {
	char auth[128];

	if(!GetClientAuthId(client, AuthId_Steam3, auth, sizeof(auth)))
		return -1;

	ReplaceString(auth, sizeof(auth), "[U:0:", NULL_STRING);
	ReplaceString(auth, sizeof(auth), "[U:1:", NULL_STRING);
	ReplaceString(auth, sizeof(auth), "]", NULL_STRING);

	return StringToInt(auth);
}

/**
 * Sends msay panel
 * @param from  Client Index
 * @param msg   Message
 */
stock void SendPanelToAll(int from, char[] msg)
{
	char title[100];
	FormatEx(title, 64, "%N:", from);
	
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

/**
 * Sets player speed (m_flLaggedMovementValue)
 * @param client  Client Index
 * @param speed   Speed
 */
stock void SetPlayerSpeed(int client, float speed = 1.0)
{
	SetEntPropFloat(client, Prop_Send, "m_flLaggedMovementValue", speed);
}

/**
 * Removes grenades from player
 * @param client  Client Index
 */
stock void RemoveGrenades(int client)
{
	int ent;

	while((ent = GetPlayerWeaponSlot(client, 3)) != -1)
	{
		RemoveEdict(ent);
	}
}

/**
 * Sends msay panel for client
 * @param client   Client Index
 * @param title    Panel Title
 * @param message  Message
 */
stock void SendPanelToClient2(int client, const char[] title, char[] message)
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