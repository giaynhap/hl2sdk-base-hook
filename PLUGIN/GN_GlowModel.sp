
#include <sourcemod>
#include <sdktools>
#include <sdktools>
#include <sdkhooks>

#define EF_BONEMERGE                (1 << 0) 
#define EF_NOSHADOW                 (1 << 4) 
#define EF_NORECEIVESHADOW          (1 << 6) 
#define EF_PARENT_ANIMATES          (1 << 9) 

#define CPS_RENDER                  (1 << 0) 
#define CPS_NOATTACHMENT            (1 << 1) 
#define CPS_IGNOREDEATH             (1 << 2)  

int gPlayerModels[MAXPLAYERS+1] = {INVALID_ENT_REFERENCE,...};
 new g_sprite;
 
 
public Plugin:myinfo = 
{
	name = "GN GlowModel",
	author = "GiayNhap",
	description = "<- Description ->",
	version = "1.0",
	url = "<- URL ->"
}

public OnPluginStart()
{
	// RegConsoleCmd("sm_test", test); 
	// HookEvent("player_spawn", Event_PlayerSpawn);
}
public OnMapStart()
{
	//UnlockConsoleCommandAndConvar("r_screenoverlay");
//	PrepareOverlays();
}
UnlockConsoleCommandAndConvar(const String:command[])
{
    new flags = GetCommandFlags(command);
    if (flags != INVALID_FCVAR_FLAGS)
    {
        SetCommandFlags(command, flags & ~FCVAR_CHEAT);
    }
    
    new Handle:cvar = FindConVar(command);
    if (cvar != INVALID_HANDLE)
    {
        flags = GetConVarFlags(cvar);
        SetConVarFlags(cvar, flags & ~FCVAR_CHEAT);
    }
} 
 public ShowKillMessage(client)
{
	//debug code////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	decl String: client_name[192];
	GetClientName(client, client_name, sizeof(client_name));
	
	//end debug code
	//ClientCommand(client, "r_screenoverlay \"overlays/galil.vtf\"");
	
	g_sprite = AttachSprite(client,"overlays/galil.vmt")
}
 
 
 
 
 public Event_PlayerSpawn(Handle:event, const String:name[], bool:dontBroadcast)
{
	new client = GetClientOfUserId(GetEventInt(event, "userid"));
	ShowKillMessage(client);

}

public PrepareOverlays()
{
	AddFile("g3sg1");
	AddFile("galil");
}

AddFile( String:fileName[])
{
	new String:overlays_file[64];
	Format(overlays_file,sizeof(overlays_file),"overlays/%s.vtf",fileName);
	PrecacheDecal(overlays_file,true);
	
	Format(overlays_file,sizeof(overlays_file),"materials/overlays/%s.vtf",fileName);
	AddFileToDownloadsTable(overlays_file);
	
	
	Format(overlays_file,sizeof(overlays_file),"overlays/%s.vmt",fileName);
	PrecacheDecal(overlays_file,true);
	
	Format(overlays_file,sizeof(overlays_file),"materials/overlays/%s.vmt",fileName);
	AddFileToDownloadsTable(overlays_file);
	
	return PrecacheModel(overlays_file);
}

stock AttachSprite(Client, String:sprite[])
{
if(!IsPlayerAlive(Client)) return -1;
decl String:iTarget[16];
Format(iTarget, 16, "Client%d", Client);
DispatchKeyValue(Client, "targetname", iTarget);
decl Float:Origin[3];
GetClientEyePosition(Client,Origin);
Origin[2] += 0.0;
Origin[1] += 20.0;
new Ent = CreateEntityByName("env_sprite");
if(!Ent) return -1;
DispatchKeyValue(Ent, "model", sprite);
DispatchKeyValue(Ent, "classname", "env_sprite");
DispatchKeyValue(Ent, "spawnflags", "1");
DispatchKeyValue(Ent, "scale", "0.1");
DispatchKeyValue(Ent, "rendermode", "1");
DispatchKeyValue(Ent, "rendercolor", "255 255 255");
DispatchSpawn(Ent);
TeleportEntity(Ent, Origin, NULL_VECTOR, NULL_VECTOR);
SetVariantString(iTarget);
AcceptEntityInput(Ent, "Display", Ent, Ent, 0);
PrintToChatAll(sprite);

return Ent;
} 


public Action:test(client, args)
{
decl Float:pos[3];
GetClientAbsOrigin(1, pos);
pos[1]+=100;
TE_SetupExplosion(pos, g_sprite, 5.0, 1, 0, 100, 5000);
TE_SendToAll();
AttachSprite(1, "overlays/galil.vmt")

ShowGameText("HELLO")
}

ShowGameText(const String:text[])
{
	new entity = CreateEntityByName("game_text");
	DispatchKeyValue(entity, "message", text);
	DispatchKeyValue(entity, "display_to_team", "0");
	DispatchKeyValue(entity, "icon", "ico_build");
	DispatchKeyValue(entity, "targetname", "game_text1");
	DispatchKeyValue(entity, "background", "2");
	DispatchSpawn(entity);
	AcceptEntityInput(entity, "Display", entity, entity);
	//CreateTimer(10.0, KillGameText, entity);
}

