#if defined _wlib_entity_included
    #endinput
#endif
#define _wlib_entity_included

#include <sdktools_trace>

/*
	Gets entity basevelocity

	@param entity Entity Index
	@param vec    Vector
*/
stock void GetBaseVelocity(int entity, float vec[3]) {
	GetEntPropVector(entity, Prop_Data, "m_vecBaseVelocity", vec);
}

/*
	Gets trigger_push push direction

	@param entity Entity Index
	@param vec    Vector
*/
stock void GetTriggerPushDirection(int entity, float vec[3]) {
	GetEntPropVector(entity, Prop_Data, "m_vecPushDir", vec);
}

/*
	Gets trigger_push push speed

	@param entity Entity Index

	@return push speed
*/
stock float GetTriggerPushSpeed(int entity) {
	return GetEntPropFloat(entity, Prop_Data, "m_flSpeed");
}

/*
	Sets entity basevelocity

	@param entity Entity Index
	@param vec    Vector
*/
stock void SetBaseVelocity(int entity, const float vec[3]) {
	SetEntPropVector(entity, Prop_Data, "m_vecBaseVelocity", vec);
}

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
	Changes player collision
	
	@param client 		Client Index
	@param collision	Collision
	
	@error Invalid client index, client not in game
*/
stock void ChangeEntityCollision(int client, bool collision) {
	SetEntData(client, FindSendPropInfo("CBaseEntity", "m_CollisionGroup"), collision?5:2, 4, true);
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

/**
 * Removes player nades
 * 
 * @param client Client Index
 */
stock void RemoveNades(int client)
{
	SetEntProp(client, Prop_Send, "m_iAmmo", 0, _, 11);
	SetEntProp(client, Prop_Send, "m_iAmmo", 0, _, 12);
	SetEntProp(client, Prop_Send, "m_iAmmo", 0, _, 13);
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