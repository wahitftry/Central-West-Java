#include <a_samp>
#include <discord-connector>

new DCC_Channel:g_Discord_Chat;

public OnFilterScriptInit()
{
	g_Discord_Chat = DCC_FindChannelById("729238185762095175"); // Discord channel ID
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
    if(channel == g_Discord_Chat && !IsBot) //!IsBot will block BOT's message in game
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
    g_Discord_Chat = DCC_FindChannelById("729238185762095175"); // Discord channel ID

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
    g_Discord_Chat = DCC_FindChannelById("729238185762095175"); // Discord channel ID

    new string[128];
    format(string, sizeof string, " ```diff\n- %s Has Left The Server (%s) :(\n```", name, szDisconnectReason[reason]);
    DCC_SendChannelMessage(g_Discord_Chat, string);
    return 1;
}
