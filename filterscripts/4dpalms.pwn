
#include <a_samp>
#include <streamer>

public OnFilterScriptInit()
{
	CreateDynamicObject(712, 1996.0625, 1039.1094, 19.4297, 0.0, 0.0, 0.0, 0, 0, -1, STREAMER_OBJECT_SD); // vgs_palm03
	CreateDynamicObject(712, 1996.0625, 1055.4141, 19.4297, 0.0, 0.0, 0.0, 0, 0, -1, STREAMER_OBJECT_SD); // vgs_palm03
	CreateDynamicObject(712, 2014.0313, 1039.5938, 19.4297, 0.0, 0.0, 0.0, 0, 0, -1, STREAMER_OBJECT_SD); // vgs_palm03
	CreateDynamicObject(712, 2014.0313, 1055.8984, 19.4297, 0.0, 0.0, 0.0, 0, 0, -1, STREAMER_OBJECT_SD); // vgs_palm03
	CreateDynamicObject(710, 2005.9219, 1036.5859, 25.3047, 0.0, 0.0, 0.0, 0, 0, -1, STREAMER_OBJECT_SD); // vgs_palm01
	CreateDynamicObject(710, 2005.9219, 1048.2266, 25.3047, 0.0, 0.0, 0.0, 0, 0, -1, STREAMER_OBJECT_SD); // vgs_palm01
	CreateDynamicObject(710, 2013.3281, 1047.4844, 25.3047, 0.0, 0.0, 0.0, 0, 0, -1, STREAMER_OBJECT_SD); // vgs_palm01
	CreateDynamicObject(710, 2005.9219, 1059.8672, 25.3047, 0.0, 0.0, 0.0, 0, 0, -1, STREAMER_OBJECT_SD); // vgs_palm01

	return 1;
}

public OnPlayerConnect(playerid)
{
	RemoveBuildingForPlayer(playerid, 712, 1996.0625, 1039.1094, 19.4297, 1.0); // vgs_palm03
	RemoveBuildingForPlayer(playerid, 712, 1996.0625, 1055.4141, 19.4297, 1.0); // vgs_palm03
	RemoveBuildingForPlayer(playerid, 712, 2014.0313, 1039.5938, 19.4297, 1.0); // vgs_palm03
	RemoveBuildingForPlayer(playerid, 712, 2014.0313, 1055.8984, 19.4297, 1.0); // vgs_palm03
	RemoveBuildingForPlayer(playerid, 710, 2005.9219, 1036.5859, 25.3047, 1.0); // vgs_palm01
	RemoveBuildingForPlayer(playerid, 710, 2005.9219, 1048.2266, 25.3047, 1.0); // vgs_palm01
	RemoveBuildingForPlayer(playerid, 710, 2013.3281, 1047.4844, 25.3047, 1.0); // vgs_palm01
	RemoveBuildingForPlayer(playerid, 710, 2005.9219, 1059.8672, 25.3047, 1.0); // vgs_palm01

	return 1;
}

