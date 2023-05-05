
#include <a_samp>

native SendClientCheck(playerid, type, arg, offset, size);

//#pragma warning disable 239

//#define IsPlayerAndroid(%0) GetPVarInt(%0, "NotAndroid") == 0

public OnPlayerConnect(playerid)
{
	SendClientCheck(playerid, 0x48, 0, 0, 2);

	return 1;
}

forward OnClientCheckResponse(playerid, type, arg, response);

public OnClientCheckResponse(playerid, type, arg, response)
{
	switch (type)
	{
		case 0x48:
		{
			SetPVarInt(playerid, "NotAndroid", 1);
		}
	}
	return 1;
}

