/************************************************************/
/* thisgamesux css basehook 2010 for the orange box update  */
/* by s0beit												*/
/************************************************************/

#include "stdafx.h"

IBaseClientDLL*				GClient;
IVRenderView*				GRenderView;
IFileSystem*				GFileSystem;
IPrediction*				GPrediction;
IVModelRender*				GModelRender;
IClientEntityList*			GEntList;
IMatSystemSurface*			GMatSurface;
vgui::ISurface*				GSurface;
IVEfx*						GEffects;
ICvar*						GCvarInterface;
IPanel*						GPanel;
IVEngineClient*				GEngine;
IEngineTrace*				GEnginetrace;
IVModelInfo*				GModelinfo;
IEngineVGui*				GEnginevgui;
IVDebugOverlay*				GDebugOverlay;
CInput*						GInput;
CGlobalVarsBase*			GGlobals;
IGameEventManager2*			GGameEventManager;
IMaterialSystem*			GMatSystem;
IPhysicsSurfaceProps*		GPhysicAPI;
IUniformRandomStream*		GRandom;
IShadowMgr*					GShadowMgr;
IGameUIFuncs*				GGameUIFuncs;
IEngineSound*				GEngineSound;
 
bool needNetVarUpdate = true;

CreateInterfaceFn CaptureFactory( char *pszFactoryModule )
{
	CreateInterfaceFn fn = NULL;
	
	while( fn == NULL )
	{
		HMODULE hFactoryModule = GetModuleHandleA( pszFactoryModule );

		if( hFactoryModule )
		{
			fn = reinterpret_cast< CreateInterfaceFn >( GetProcAddress( hFactoryModule, "CreateInterface" ) );
		}

		Sleep( 10 );
	}

	return fn;
}

void *CaptureInterface( CreateInterfaceFn fn, char *pszInterfaceName )
{
    unsigned long *ptr = NULL;
    char newname[100] = "";
	ptr = reinterpret_cast< unsigned long* >(fn(pszInterfaceName, NULL));
	if (ptr) return ptr;
    for(int i = 1; i < 100;i++) {
        memset(newname,0,strlen(newname));
        char integer_string[32];
        sprintf(integer_string, "%d", i);
        strcat(newname,pszInterfaceName);
        if(i<10) strcat(newname,"0");
        strcat(newname,integer_string);
        ptr = reinterpret_cast< unsigned long* >( fn( newname, NULL ) );
        if(ptr) break;
        Sleep( 10 );
    }

	return ptr;
}

DWORD WINAPI HookThread( LPVOID lpParams )
{
	while( FindWindowA( "Valve001", NULL ) == NULL )
		Sleep( 100 );

	while( GetModuleHandleA( "engine.dll" ) == NULL || GetModuleHandleA( "client.dll" ) == NULL )
		Sleep( 100 );

	CreateInterfaceFn fnClient		= CaptureFactory( "client.dll" );
	CreateInterfaceFn fnEngine		= CaptureFactory( "engine.dll" );
	CreateInterfaceFn fnVGUI		= CaptureFactory( "vgui2.dll" );
	CreateInterfaceFn fnVPhysics	= CaptureFactory( "vphysics.dll" );
	CreateInterfaceFn fnVStd		= CaptureFactory( "vstdlib.dll" );
	CreateInterfaceFn fnMatSystem	= CaptureFactory( "MaterialSystem.dll" );
	CreateInterfaceFn fnMatSurface	= CaptureFactory( "vguimatsurface.dll" );
 
	GClient							= reinterpret_cast< IBaseClientDLL* >( CaptureInterface( fnClient, "VClient0" ) );
	GRenderView						= reinterpret_cast< IVRenderView* >( CaptureInterface( fnEngine, "VEngineRenderView0" ) );
	GPrediction						= reinterpret_cast< IPrediction* >( CaptureInterface( fnClient, "VClientPrediction0" ) );
	GModelRender					= reinterpret_cast< IVModelRender* >( CaptureInterface( fnEngine, "VEngineModel0" ) );
	GEntList						= reinterpret_cast< IClientEntityList* >( CaptureInterface( fnClient, "VClientEntityList0" ) );
	GEffects						= reinterpret_cast< IVEfx* >( CaptureInterface( fnEngine, "VEngineEffects0" ) );
	GCvarInterface					= reinterpret_cast< ICvar* >( CaptureInterface( fnVStd, "VEngineCvar0" ) );
	g_pVGuiPanel					= reinterpret_cast< IPanel* >( CaptureInterface( fnVGUI, "VGUI_Panel0" ) );
	GEngine							= reinterpret_cast< IVEngineClient* >( CaptureInterface( fnEngine, "VEngineClient0" ) );
	GEnginetrace					= reinterpret_cast< IEngineTrace* >( CaptureInterface( fnEngine, "EngineTraceClient0" ) );
	GModelinfo						= reinterpret_cast< IVModelInfo* >( CaptureInterface( fnEngine, "VModelInfoClient0" ) );
	GEnginevgui						= reinterpret_cast< IEngineVGui* >( CaptureInterface( fnEngine, "VEngineVGui0" ) );
	GDebugOverlay					= reinterpret_cast< IVDebugOverlay* >( CaptureInterface( fnEngine, "VDebugOverlay0" ) );
	GGameEventManager				= reinterpret_cast< IGameEventManager2* >( CaptureInterface( fnEngine, "GAMEEVENTSMANAGER002" ) );
	GMatSystem						= reinterpret_cast< IMaterialSystem* >( CaptureInterface( fnMatSystem, "VMaterialSystem0" ) );
	GPhysicAPI						= reinterpret_cast< IPhysicsSurfaceProps* >( CaptureInterface( fnVPhysics, "VPhysicsSurfaceProps0" ) );
	GRandom							= reinterpret_cast< IUniformRandomStream* >( CaptureInterface( fnEngine, "VEngineRandom0" ) );
	GShadowMgr						= reinterpret_cast< IShadowMgr* >( CaptureInterface( fnEngine, "VEngineShadowMgr0" ) );
	GGameUIFuncs					= reinterpret_cast< IGameUIFuncs* >( CaptureInterface( fnEngine, "VENGINE_GAMEUIFUNCS_VERSION0" ) );
	GEngineSound					= reinterpret_cast< IEngineSound* >( CaptureInterface( fnEngine, "IEngineSoundClient0" ) );
	  
	GSurface						= reinterpret_cast< vgui::ISurface* >( CaptureInterface( fnMatSurface, "VGUI_Surface0" ) );
	GMatSurface						= reinterpret_cast< IMatSystemSurface* >( GSurface );
	 g_Manager = new Manager();
	 
	while (Hook() == false) {
		Sleep(10);
		LogWriter("HOOK Failed");
	}
	LogWriter("HOOKED");

	return 0;
}

void hook(){

}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
	if( dwReason == DLL_PROCESS_ATTACH )
	{
		LogWriter("CallHook");
		CreateThread( 0, 0, HookThread, 0, 0, 0 );
	}

    return TRUE;
}