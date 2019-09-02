#include <sourcemod>
#include <sdktools>


new Handle:_atCleanTimer[MAXPLAYERS+1] = INVALID_HANDLE
 
new Float:_dTimerLength = 5.0;

public Plugin:myinfo = 
{
	name = "KillMark",
	author = "GiayNhap",
	description = "",
	version = "1.0",
	url = ""
}

public OnPluginStart()
{	
 
 RegConsoleCmd("sm_test", test); 
}
	
public OnMapStart()
{
PrepareOverlay("kill_1");
  PrintToServer("%s", "GNDM-OnMapStart");
}

public Action:test(client, args)
{
 ShowKillMessage(1,"kill_1")
 PrintToChatAll("Show kill");
}

 
	
ShowKillMessage(client,String:killName[])
{
	 
 
	if(client>0)
	{
	 
		
		if(_atCleanTimer[client] !=INVALID_HANDLE)
		{
			KillTimer(_atCleanTimer[client]);
			_atCleanTimer[client] =INVALID_HANDLE;
		}
		
		_atCleanTimer[client] = CreateTimer(_dTimerLength,CleanTimer,client);
		
		ClearScreen(client);
		ClientCommand(client, "r_screenoverlay \"killmessages/%s.vtf\"",killName);
	}
	return Plugin_Handled;
}

public ClearScreen(client)
{
	if(client>0)
	{
		ClientCommand(client, "r_screenoverlay \"\"");
	}
}

public Action:CleanTimer(Handle:Timer, any:client)
{
	_atCleanTimer[client] = INVALID_HANDLE;
	ClearScreen(client);
}

PrepareOverlay(String:files[])
{
	new String:overlays_file[64];
	new String:overlays_dltable[64];
	Format(overlays_file,sizeof(overlays_file),"killmessages/%s.vtf",files);
	PrecacheDecal(overlays_file,true);
	Format(overlays_dltable,sizeof(overlays_dltable),"materials/killmessages/%s.vtf",files);
	AddFileToDownloadsTable(overlays_dltable);
	Format(overlays_file,sizeof(overlays_file),"killmessages/%s.vmt",files);
	PrecacheDecal(overlays_file,true);
	Format(overlays_dltable,sizeof(overlays_dltable),"materials/killmessages/%s.vmt",files);
	AddFileToDownloadsTable(overlays_dltable);
	
	  PrintToServer("%s%s", "GNDM-",overlays_dltable);
	return Plugin_Handled;
}