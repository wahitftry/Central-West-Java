#include <a_samp>
#include <discord-connector>

new DCC_Channel:g_Discord_Chat;

public OnFilterScriptInit()
{
	g_Discord_Chat = DCC_FindChannelById("729238185762095175"); 
    return 1;
}

forward DCC_OnMessageCreate(DCC_Message:message);

public DCC_OnMessageCreate(DCC_Message:message)
{
	new realMsg[100];
    DCC_GetMessageContent(message, realMsg, 100);
    new bool:IsBot;
    new DCC_Channel:channel;
 	DCC_GetMessageChannel(message, channel);
    new DCC_User:author;
	DCC_GetMessageAuthor(message, author);
    DCC_IsUserBot(author, IsBot);
    if(channel == g_Discord_Chat && !IsBot)
    {
        new user_name[32 + 1], str[152];
       	DCC_GetUserName(author, user_name, 32);
        format(str,sizeof(str), "{8a6cd1}[DISCORD] {aa1bb5}%s: {ffffff}%s",user_name, realMsg);
        SendClientMessageToAll(-1, str);
    }

    return 1;
}

public OnPlayerText(playerid, text[])
{

    new name[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, name, sizeof name);
    if(strfind("@everyone", text, true)!= -1 || strfind("@here", text, true)!= -1)
    {return 0;}
    else{
    new msg[128];
    format(msg, sizeof(msg), "**%s:** %s", name, text);
    DCC_SendChannelMessage(g_Discord_Chat, msg);}
    return 1;
}

public OnPlayerConnect(playerid)
{
   	new name[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, name, sizeof name);
    if(strfind("@everyone", name, true)!= -1 || strfind("@here", name, true)!= -1)
    {Kick(playerid);}
    else {
    if (_:g_Discord_Chat == 0)
    g_Discord_Chat = DCC_FindChannelById("729238185762095175");

    new string[128];
    format(string, sizeof string, " ```diff\n+ %s Joined The Server. :)\n```", name);
    DCC_SendChannelMessage(g_Discord_Chat, string);
    }
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    new name[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, name, sizeof name);

    new szDisconnectReason[3][] =
    {
        "Timeout/Crash",
        "Quit",
        "Kick/Ban"
    };
    
    if (_:g_Discord_Chat == 0)
    g_Discord_Chat = DCC_FindChannelById("729238185762095175");

    new string[128];
    format(string, sizeof string, " ```diff\n- %s Has Left The Server (%s) :(\n```", name, szDisconnectReason[reason]);
    DCC_SendChannelMessage(g_Discord_Chat, string);
    return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    new name[MAX_PLAYER_NAME + 1], name2[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof name);
    GetPlayerName(killerid, name2, sizeof name2);
    new msg[128], reasonMsg[128];
    if (killerid != INVALID_PLAYER_ID)
    {
        switch (reason)
        {
            case 0: reasonMsg = "Unarmed";
            case 1: reasonMsg = "Brass Knuckles";
            case 2: reasonMsg = "Golf Club";
            case 3: reasonMsg = "Night Stick";
            case 4: reasonMsg = "Knife";
            case 5: reasonMsg = "Baseball Bat";
            case 6: reasonMsg = "Shovel";
            case 7: reasonMsg = "Pool Cue";
            case 8: reasonMsg = "Katana";
            case 9: reasonMsg = "Chainsaw";
            case 10: reasonMsg = "Dildo";
            case 11: reasonMsg = "Dildo";
            case 12: reasonMsg = "Vibrator";
            case 13: reasonMsg = "Vibrator";
            case 14: reasonMsg = "Flowers";
            case 15: reasonMsg = "Cane";
            case 22: reasonMsg = "Pistol";
            case 23: reasonMsg = "Silenced Pistol";
            case 24: reasonMsg = "Desert Eagle";
            case 25: reasonMsg = "Shotgun";
            case 26: reasonMsg = "Sawn-off Shotgun";
            case 27: reasonMsg = "Combat Shotgun";
            case 28: reasonMsg = "MAC-10";
            case 29: reasonMsg = "MP5";
            case 30: reasonMsg = "AK-47";
            case 31: reasonMsg = "M4";
            case 32: reasonMsg = "TEC-9";
            case 33: reasonMsg = "Country Rifle";
            case 34: reasonMsg = "Sniper Rifle";
            case 37: reasonMsg = "Fire";
            case 38: reasonMsg = "Minigun";
            case 41: reasonMsg = "Spray Can";
            case 42: reasonMsg = "Fire Extinguisher";
            case 49: reasonMsg = "Vehicle Collision";
            case 50: reasonMsg = "Vehicle Collision";
            case 51: reasonMsg = "Explosion";
            default: reasonMsg = "Unknown";
        }
        format(msg, sizeof(msg), "```diff\n- %s killed %s. (%s)\n```", name2, name, reasonMsg);
    }
    else
    {
        switch (reason)
        {
            case 53: format(msg, sizeof(msg), "```diff\n- %s died. (Drowned)\n```", name);
            case 54: format(msg, sizeof(msg), "```diff\n- %s died. (Collision)\n```", name);
            default: format(msg, sizeof(msg), "```diff\n- %s died.\n```", name);
        }
    }
    //format(msg, sizeof(msg), "```diff\n- %s has been killed by %s[%i]\n```", name, name2, reason);
    DCC_SendChannelMessage(g_Discord_Chat, msg);
	return 1;
}
