
#define PLAYERS 60

#define VEHICLES MAX_VEHICLES

#define MAX_STRING 255

new pilotrespond[PLAYERS][PLAYERS][2];

new gPlayerCheckpointStatus[PLAYERS];

stock GetPlayerShamalID(playerid)
{
	return GetPlayerVirtualWorld(playerid) > cellmax - VEHICLES ? cellmax - GetPlayerVirtualWorld(playerid) + 1 : 0;
}

new vehicleinterior[VEHICLES + 1];

stock GetVehicleInterior2(vehicleid)
{
	return vehicleinterior[vehicleid];
}

stock SetPlayerPos2(playerid, Float:x, Float:y, Float:z, interiorid, isspawned = 0)
{
	CallRemoteFunction("PlayerSetPosition", "dfffdd", playerid, x, y, z, interiorid, isspawned);
}

stock SetPlayerVirtualWorld2(playerid, worldid)
{
	new oldworld = GetPlayerVirtualWorld(playerid);
	SetPlayerVirtualWorld(playerid, worldid);
	if (worldid != oldworld) {
		CallRemoteFunction("OnPlayerVirtualWorldChange", "ddd", playerid, worldid, oldworld);
	}
}

stock Streamer_ToggleItemUpdate2(playerid, type, toggle)
{
	if (type == STREAMER_TYPE_CP && toggle == 0) {
		Streamer_ToggleAllItems(playerid, STREAMER_TYPE_CP, 0);
		Streamer_Update(playerid);
	}
	Streamer_ToggleItemUpdate(playerid, type, toggle);
}

stock Float:Angle2D(Float:PointA1, Float:PointA2, Float:PointB1, Float:PointB2)
{
	new bool:A_LS_B[2], Float:Dist[2], Float:Angle;
	A_LS_B[0] = PointA1 < PointB1;
	Dist[0] = A_LS_B[0] ? PointB1 - PointA1 : PointA1 - PointB1;
	A_LS_B[1] = PointA2 < PointB2;
	Dist[1] = A_LS_B[1] ? PointB2 - PointA2 : PointA2 - PointB2;
	Angle = atan2(Dist[1], Dist[0]);
	Angle = A_LS_B[0] ? 270.0 + Angle : 90.0 - Angle;
	Angle = A_LS_B[1] ? Angle : 180.0 - Angle;
	return Angle;
}

stock IsPlayerInAreaEx(playerid, Float:...)
{
	new count = numargs(), j;
	new Float:xe[255], Float:ye[255];
	for (new i = 1; i < count; i += 2) {
		xe[j] = Float:getarg(i);
		ye[j] = Float:getarg(i+1);
		j ++;
	}
	xe[j] = xe[0];
	ye[j] = ye[0];
	new lines, Float:xcut;
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	for (new i = 0; i < j; i++) {
		xcut = xe[i]+((y-ye[i])*(xe[i+1]-xe[i])/(ye[i+1]-ye[i]));
		if (((y >= ye[i] && y <= ye[i+1]) || (y >= ye[i+1] && y <= ye[i])) && xcut < x)
			lines ++;
	}
	if (lines%2 == 1) return 1;
	return 0;
}

stock GetVehicleCount()
{
	new count;
	for (new id = 1; id <= MAX_VEHICLES; id++) {
		if (GetVehicleModel(id) != 0) count ++;
	}
	return count;
}

stock HexToInt(string[])
{
	if (string[0] == 0) return 0;
	new i;
	new cur = 1;
	new res = 0;
	for (i = strlen(string); i > 0; i--) {
		if (string[i-1] < 58) res = res + cur * (string[i-1] - 48); else res = res + cur * (string[i-1] - 65 + 10);
		cur = cur * 16;
	}
	return res;
}

stock isNumeric(const string[])
{
	new length = strlen(string);
	if (length == 0) return false;
	for (new i = 0; i < length; i++) {
		if ((string[i] > '9' || string[i] < '0' && string[i] != '-' && string[i] != '+') || (string[i] == '-' && i != 0) || (string[i] == '+' && i != 0)) return false;
	}
	if (length == 1 && (string[0] == '-' || string[0] == '+')) return false;
	return true;
}

stock strtok(const string[], &index, seperator = ' ')
{
	new length = strlen(string);
	new offset = index;
	new result[MAX_STRING];
	while ((index < length) && (string[index] != seperator) && ((index - offset) < (sizeof(result) - 1))) {
		result[index - offset] = string[index];
		index ++;
	}
	result[index - offset] = EOS;
	if ((index < length) && (string[index] == seperator)) {
		index ++;
	}
	return result;
}
