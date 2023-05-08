#include <a_samp>
#include <dc>
#include <streamer>
#include <colandreas>

#include &lt;a_samp&gt;
#define admsys_isnull(%0) ((!(%0[0])) || (((%0[0]) == '\1') && (!(%0[1]))))
new name[MAX_PLAYER_NAME + 1];
new string[128];
static g_Discord_Chat = -1;
new DCC_Channel:g_Discord_Chat;
new exitstage = 0;
new exittimer = -1;

forward OnClientCheckResponse(playerid, actionid, memaddr, retndata);
native SendClientCheck(playerid, actionid, memaddr, memOffset, bytesCount);
enum(&lt;&lt;= 1)
{
        NULL = 0,
SOBEIT = 0x5E8606
};
public OnPlayerSpawn(playerid)
{
        SendClientCheck(playerid, 72, 0, 0, 2);
        SetTimerEx(&#34;sobeitcontrol&#34;, 100, true, &#34;i&#34;, playerid);
        return 1;
}

public OnClientCheckResponse(playerid, actionid, memaddr, retndata)
{
        if (retndata != 192 &amp;&amp; actionid != 72)
        {
            Kick(playerid);
        }

        return 1;
}
public sobeitcontrol(playerid)
{
    new actionid = 0x5, memaddr = SOBEIT, retndata = 0x4;
    SendClientCheck(playerid, actionid, memaddr, NULL, retndata);
    return 1;
}

stock Float:frandom(Float:max, Float:m2 = 0.0, dp = 3)
{
    new Float:mn = m2;
    if(m2 > max) {
        mn = max,
        max = m2;
    }
    m2 = floatpower(10.0, dp);
    
    return floatadd(floatdiv(float(random(floatround(floatmul(floatsub(max, mn), m2)))), m2), mn);
}

public OnFilterScriptInit()
{
	g_Discord_Chat = DCC_FindChannelById("729238185762095175"); 
    return 1;
}

forward FadeBlood(objectid, alpha);
public FadeBlood(objectid, alpha)
{
    alpha -= 5;
    
    if(alpha) {
        SetDynamicObjectMaterial(objectid, 0, -1, "none", "none", 0xFF0000 | (alpha << 24));
        SetTimerEx("FadeBlood", 50, false, "ii", objectid, alpha);
    }
    else {
        DestroyDynamicObject(objectid);
    }
}

forward kicktimer(playerid);
public kicktimer(playerid)
{
    Kick(playerid);
    return 1;
}

forward RestartTimer();

public RestartTimer()
{
    if (exitstage != 0) {
        if (exitstage == 1) {
            exitstage = 2;

            new pcount = 0;
            for (new i = 0; i < MAX_PLAYERS; i++) {
                if (!IsPlayerConnected(i)) continue;
                Kick(i);
                pcount ++;
            }

            KillTimer(exittimer);

            exittimer = SetTimer("RestartTimer", pcount * 100, 0);
        }
        else {// if (exitstage == 2) {
//          exitstage = 0;

            SendRconCommand("exit");

//          KillTimer(exittimer);
//          exittimer = -1;
        }
    }
}

forward DCC_OnMessageCreate(DCC_Message:message);
//
public DCC_OnMessageCreate(DCC_Message message)
{
    new content[MAX_MESSAGE_LENGTH];
    DCC_GetMessageContent(message, content, MAX_MESSAGE_LENGTH);

    new isBot;
    DCC_IsUserBot(DCC_GetMessageAuthor(message), isBot);

    if (DCC_GetMessageChannel(message) == g_Discord_Chat && !isBot)
    {
        new username[MAX_USERNAME_LENGTH];
        DCC_GetUserName(DCC_GetMessageAuthor(message), username, MAX_USERNAME_LENGTH);

        new message[MAX_MESSAGE_LENGTH + MAX_USERNAME_LENGTH + 20];
        format(message, sizeof(message), "[DISCORD] %s: %s", username, content);

        SendClientMessageToAll(-1, message);
    }

    return 1;
}

public OnPlayerText(playerid, text[])
{
    new name[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, name, sizeof(name));

    if (strfind("@everyone", text, true) != -1 || strfind("@here", text, true) != -1) {
        return 0;
    }

    new msg[128];
    format(msg, sizeof(msg), "**%s:** %s", name, text);
    DCC_SendChannelMessage(g_Discord_Chat, msg);

    return 1;
}

public OnPlayerConnect(playerid)
{
    GetPlayerName(playerid, name, sizeof name);
    if (strfind("@everyone", name, true) != -1 || strfind("@here", name, true) != -1) {
        Kick(playerid);
        return 0;
    }

    if (g_Discord_Chat == -1) {
        g_Discord_Chat = DCC_FindChannelById("729238185762095175");
        if (g_Discord_Chat == -1) {
            printf("Failed to find Discord chat channel!");
            return 0;
        }
    }

    format(string, sizeof string, " ```diff\n+ %s Joined The Server. :)\n```", name);
    DCC_SendChannelMessage(g_Discord_Chat, string);

    return 1;
}


public OnPlayerDisconnect(playerid, reason)
{
    new const szDisconnectReason[3][24] =
    {
        "Timeout/Crash",
        "Quit",
        "Kick/Ban"
    };

    g_Discord_Chat = g_Discord_Chat ? g_Discord_Chat : DCC_FindChannelById("729238185762095175");

    DCC_SendChannelMessage(g_Discord_Chat, "```diff\n- %s Has Left The Server (%s) :(\n```", GetPlayerName(playerid), szDisconnectReason[reason]);
    return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    new name[MAX_PLAYER_NAME + 1], name2[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
    GetPlayerName(killerid, name2, sizeof(name2));
    new msg[128], reasonMsg[128];

    static const char* reasonMsgs[] = {
        "Unarmed", "Brass Knuckles", "Golf Club", "Night Stick",
        "Knife", "Baseball Bat", "Shovel", "Pool Cue", "Katana",
        "Chainsaw", "Dildo", "Dildo", "Vibrator", "Vibrator", "Flowers",
        "Cane", "", "", "", "", "", "Pistol", "Silenced Pistol",
        "Desert Eagle", "Shotgun", "Sawn-off Shotgun", "Combat Shotgun", "MAC-10",
        "MP5", "AK-47", "M4", "TEC-9", "Country Rifle", "Sniper Rifle", "",
        "", "", "Fire", "Minigun", "", "", "Spray Can", "Fire Extinguisher",
        "", "", "Vehicle Collision", "Vehicle Collision", "Explosion"
    };

    if (killerid != INVALID_PLAYER_ID && reason >= 0 && reason < sizeof(reasonMsgs) / sizeof(reasonMsgs[0]))
    {
        format(msg, sizeof(msg), "```diff\n- %s killed %s. (%s)\n```", name2, name, reasonMsgs[reason]);
    }
    else
    {
        switch (reason)
        {
            case 53: format(msg, sizeof(msg), "```diff\n- %s died. (Drowned)\n```", name); break;
            case 54: format(msg, sizeof(msg), "```diff\n- %s died. (Collision)\n```", name); break;
            default: format(msg, sizeof(msg), "```diff\n- %s died.\n```", name); break;
        }
    }
    DCC_SendChannelMessage(g_Discord_Chat, msg);
    return 1;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ) {
    if(hittype == BULLET_HIT_TYPE_PLAYER) {
        new Float:rDist = frandom(-5.0, 6.0);
        if(rDist > 0.0) {
            new Float:vX, Float:vY, Float:vZ,
                Float:pX, Float:pY, Float:pZ,
                Float:randOffset = frandom(-0.5, 0.5),
                Float:size = 0.0;
            GetPlayerLastShotVectors(playerid, vX, vY, vZ, fX, fY, fZ);

            vX = fX - vX; 
            vY = fY - vY; 
            vZ = fZ - vZ; 

            size = VectorSize(vX, vY, vZ);
            vX /= size;
            vY /= size;
            vZ /= size;

            vX *= rDist;
            vY *= rDist;
            vZ *= rDist;

            vX += fX + randOffset;
            vY += fY + randOffset;
            vZ += fZ + randOffset;

            new Float:hitX, Float:hitY, Float:hitZ;
            if(CA_RayCastLineNormal(fX, fY, fZ, vX, vY, vZ, pX, pY, pZ, hitX, hitY, hitZ)) {
                randOffset = frandom(0.005, 0.020, 4);
                pX *= randOffset;
                pY *= randOffset;
                pZ *= randOffset;

                CA_RayCastLineAngle(fX, fY, fZ, vX, vY, vZ, hitX, hitY, hitZ, vX, vY, vZ);

                new objectid = CreateDynamicObjectEx(19836, fX + pX, fY + pY, fZ + pZ, vX, vY, vZ, -1, 0xFFFF0000);
                if(objectid) {
                    SetTimerEx("FadeBlood", 1500, false, "ii", objectid, 255);
                }
            }
        }
    }

    return 1;
}

DCCMD:kick(DCC_User:user, const args) {
    new playerId, playerName[MAX_PLAYER_NAME], string[64];
    if(sscanf(args, "u[24]", playerId)) {
        return SendDC(DISCORD_CHANNEL_ID, "```Usage: /kick [playerid]```");
    } else if(!IsPlayerConnected(playerId)) {
        return SendDC(DISCORD_CHANNEL_ID, "**Player is not connected.**");
    }
    GetPlayerName(playerId, playerName, MAX_PLAYER_NAME);
    SendDC(DISCORD_CHANNEL_ID, "```Player %s has been kicked.```", playerName);

    format(string, sizeof(string), "%s has been kicked from the server.", playerName);
    SendClientMessageToAll(COLOR_RED, string);
    SetTimerEx("kickTimer", 500, false, "i", playerId);

    return 1;
}

//
DCCMD:exit2(DCC_User user, const char[] args)
{
    new reason[200];
    if (exitstage != 0) {
        SendDC(DISCORD_CHANNEL_ID, "```Error: The server is already restarting.```");
        return 1;
    }
    if (sscanf(args, "%s", reason) == 1) {
        SendDC(DISCORD_CHANNEL_ID, "```The server has been restarted. Reason: %s```", reason);
    } else {
        SendDC(DISCORD_CHANNEL_ID, "```The server has been restarted.```");
    }
    new playername[MAX_PLAYER_NAME];
    DCC_GetUserName(user, playername, sizeof(playername));
    printf("[exit] %s has restarted the server.", playername);
    exitstage = 1;
    exittimer = SetTimer("RestartTimer", 10, 0);
    return 1;
}

DCCMD:freeze(DCC_User user, const char[] args)
{
    new playerid;
    if (sscanf(args, "u", playerid) != 1) {
        return SendDC(DISCORD_CHANNEL_ID, "```Usage: /freeze [playerid]```");
    }
    if (!IsPlayerConnected(playerid)) {
        return SendDC(DISCORD_CHANNEL_ID, "**Error: Inactive player id!**");
    }
    TogglePlayerControllable(playerid, 0);
    new playername[MAX_PLAYER_NAME];
    GetPlayerName(playerid, playername, sizeof(playername));
    SendClientMessage(playerid, COLOR_RED, "You have been frozen by an admin.");
    SendDC(DISCORD_CHANNEL_ID, "``` Player %s has been frozen.```", playername);
    return 1;
}

DCCMD:unfreeze(DCC_User user, const char[] args)
{
    new playerid;
    if (sscanf(args, "u", playerid) != 1) {
        return SendDC(DISCORD_CHANNEL_ID, "```Usage: /unfreeze [playerid]```");
    }
    if (!IsPlayerConnected(playerid)) {
        return SendDC(DISCORD_CHANNEL_ID, "**Error: Inactive player id!**");
    }
    TogglePlayerControllable(playerid, 1);
    new playername[MAX_PLAYER_NAME];
    GetPlayerName(playerid, playername, sizeof(playername));
    SendClientMessage(playerid, COLOR_RED, "You have been unfrozen by an admin.");
    SendDC(DISCORD_CHANNEL_ID, "``` Player %s has been unfrozen.```", playername);
    return 1;
}

DCCMD:players(DCC_User user, const char[] args)
{
    new count = 0;
    SendDC(DISCORD_CHANNEL_ID, "**__Online Players__**");
    for (new i = 0; i < MAX_PLAYERS; i++) {
        if (!IsPlayerConnected(i)) {
            continue;
        }
        new name[MAX_PLAYER_NAME], ip[50];
        GetPlayerName(i, name, sizeof(name));
        GetPlayerIp(i, ip, sizeof(ip));
        SendDC(DISCORD_CHANNEL_ID, "```%s(%d) %s %i```", name, i, ip, GetPlayerScore(i));
        count++;
    }
    if (count == 0) {
        SendDC(DISCORD_CHANNEL_ID, "There are no players online.");
    }
    return 1;
}