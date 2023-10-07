#include <a_samp>
#include <streamer>
#include <utils>

new sExplode[VEHICLES] = {-1, ...};
new bool:tCount[VEHICLES];

#define S_EXPLODE_X 2.4015
#define S_EXPLODE_Y 29.2775
#define S_EXPLODE_Z 1199.593
#define S_EXPLODE_RANGE 13.4

forward ExplodeShamal(vehicleid);

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if (ispassenger != 0 && GetVehicleModel(vehicleid) == 519)
	{
		SetPlayerVirtualWorld2(playerid, cellmax-(vehicleid-1));
		SetPlayerInterior(playerid, 1);
		SetPlayerPos2(playerid, 3.839, 22.977, 1199.601, 1);
		SetPlayerFacingAngle(playerid, 90.0);
		SetCameraBehindPlayer(playerid);
	}
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	new vehicleid = GetPlayerShamalID(playerid);
	if (newkeys & KEY_SECONDARY_ATTACK && vehicleid != 0 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		GivePlayerWeapon(playerid, 46, 1);
		new string[128];
		GetPlayerName(playerid, string, MAX_PLAYER_NAME);
		for (new i = 0; i < PLAYERS; i++) {
			if (pilotrespond[i][playerid][0] != 0) {
				pilotrespond[i][playerid][0] = 0;
				if (pilotrespond[i][playerid][1] != 0) {
					pilotrespond[playerid][i][0] = 0;
					pilotrespond[i][playerid][1] = 0;
					SetPVarInt(playerid, "destination", 0);
//					SetPVarInt(i, "destination", 0);
					gPlayerCheckpointStatus[i] = 0;
					Streamer_ToggleItemUpdate2(i, STREAMER_TYPE_CP, 1);
					TogglePlayerAllDynamicCPs(i, 1);
				}
				format(string, 128, "%s has cancelled their request for a flight.", string);
				SendClientMessage(i, 0xFF0000FF, string);
			}
		}
		new Float:x, Float:y, Float:z, Float:a;
		GetVehiclePos(vehicleid, x, y, z);
		GetVehicleZAngle(vehicleid, a);
		x += (5.0*floatsin(-(a-45.0), degrees));
		y += (5.0*floatcos(-(a-45.0), degrees));
		SetPlayerVirtualWorld2(playerid, GetVehicleVirtualWorld(vehicleid));
		SetPlayerInterior(playerid, GetVehicleInterior2(vehicleid));
		SetPlayerPos2(playerid, x, y, z-0.94, GetVehicleVirtualWorld(vehicleid));
		SetPlayerFacingAngle(playerid, a);
	}
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	if (GetVehicleModel(vehicleid) == 519)
	{
		for (new i = 0; i < PLAYERS; i++)
		{
			if (GetPlayerShamalID(i) == vehicleid)
			{
				CallRemoteFunction("KillPlayer", "d", i);
				CreateExplosionForPlayer(i, S_EXPLODE_X, S_EXPLODE_Y, S_EXPLODE_Z, 2, S_EXPLODE_RANGE);
			}
		}
		if (sExplode[vehicleid-1] != -1)
		{
			KillTimer(sExplode[vehicleid-1]);
		}
		sExplode[vehicleid-1] = SetTimerEx("ExplodeShamal", 700, 0, "d", vehicleid);
		tCount[vehicleid-1] = true;
	}
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	tCount[vehicleid-1] = false;
	return 1;
}

public ExplodeShamal(vehicleid)
{
	KillTimer(sExplode[vehicleid-1]);
	if (tCount[vehicleid-1])
	{
		for (new i = 0; i < PLAYERS; i++)
		{
			if (GetPlayerShamalID(i) == vehicleid)
			{
				CreateExplosionForPlayer(i, S_EXPLODE_X, S_EXPLODE_Y, S_EXPLODE_Z, 2, S_EXPLODE_RANGE);
			}
		}
		sExplode[vehicleid-1] = SetTimerEx("ExplodeShamal", random(1300) + 100, 0, "d", vehicleid);
	}
	else
	{
		sExplode[vehicleid-1] = -1;
	}
}

