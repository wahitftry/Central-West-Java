#include <a_samp>

native SendClientCheck(playerid, type, arg, offset, size);

public OnPlayerConnect(playerid)
{
    SendClientCheck(playerid, 0x48, 0, 0, 2);
	return 1;
}

forward OnClientCheckResponse(playerid, type, arg, response);

public OnClientCheckResponse(playerid, type, arg, response)
{
    if (type == 0x48)
    {
        SetPVarInt(playerid, "NotAndroid", true);
    }
	return 1;
}
