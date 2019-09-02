#include "stdafx.h"
#include "Hook.h"
#include <Windows.h>
 

CSurface gSurface;
CFont* g_pMyFont = NULL;

CVMethod g_pClient;
CVMethod g_pVGUI;
CVMethod g_pPanel;
CVMethod g_pGameEvent;

bool __stdcall CreateMove(float flInputSampleTime, CUserCmd *cmd)
{
	//typedef bool ( __thiscall *tCreateMove)( void*, float flInputSampleTime, CUserCmd *cmd );
	//bool bResult = GetClientMode()->GetMethod< tCreateMove >( 21 )( GetClientMode()->GetInstance(), flInputSampleTime, cmd ); 
	RunClient(cmd);
	return false;
}
void __stdcall PaintTraverse( unsigned int vguiPanel, bool forceRepaint, bool allowForce )
{
	typedef unsigned int ( __thiscall *tGetPanel )( void*, int type );
 

		
		if (gSurface.IsReady()) { 

			//g_pMyFont->PrintString(0, 0, 255, 0, 0, 255, 0, ":'( Please, Don't crash");

			RunFrame(vguiPanel);
		 
			
		}
	
	typedef void ( __thiscall *tPaintTraverse)( void*, unsigned int vguiPanel, bool forceRepaint, bool allowForce );	
	g_pPanel.GetMethod< tPaintTraverse >( 41 )( g_pPanel.GetInstance( ), vguiPanel, forceRepaint, allowForce ); 
}

void __stdcall HudUpdate(bool bActive)
{


	HubUpdate();
	typedef bool ( __thiscall *tHudUpdate)( void*, bool);
	 bool bResult = g_pClient.GetMethod< tHudUpdate >(10)(g_pClient.GetInstance(), bActive);
	// LogWriter("Hub update");
	//GClient->HudUpdate(bActive);
}

void __stdcall HudVidInit()
{
	
	Render_HudVidInt();

	typedef int(__thiscall *tHudUpdate)(void*);
	 g_pClient.GetMethod< tHudUpdate >(8)(g_pClient.GetInstance());

}
 
bool __stdcall Hooked_FireEventClientSide(IGameEvent * event )
{
 
	bool success = true;
	if (event)
	{
		success = HookEventMessage(event);
	}
	if (success) {
		typedef bool(__thiscall *tFireEvent)(void*, IGameEvent*);
		bool bResult = g_pGameEvent.GetMethod< tFireEvent >(8)(g_pGameEvent.GetInstance(), event);
	}
	return 0;
}


bool __stdcall Hooked_FireEvent(IGameEvent * event,bool board)
{

	bool success = true;
	if (event)
	{
		success = HookEventMessage_2(event);
	}
	if (success) {
		typedef bool(__thiscall *tFireEvent)(void*, IGameEvent*,bool);
		bool bResult = g_pGameEvent.GetMethod< tFireEvent >(7)(g_pGameEvent.GetInstance(), event, board);
	}
	return 0;
}



 
bool __stdcall Hook( void ){
	DWORD* pdwClient = (DWORD*)*(DWORD*)GClient;
	GGlobals = ( CGlobalVarsBase* )**( DWORD** )( pdwClient[0] + 0x3A );

	//
	LogWriter("HOOK SURFACE");
	gSurface.Init((PDWORD_PTR*)GSurface);
	LogWriter("HOOK VGUI");
	g_pVGUI.Init( (PDWORD_PTR*)GEnginevgui );
	g_pPanel.Init( (PDWORD_PTR* )g_pVGuiPanel );
	g_pPanel.HookMethod( 41, (DWORD_PTR)PaintTraverse );
	g_pClient.Init((PDWORD_PTR*)GClient);
	g_pGameEvent.Init((PDWORD_PTR*)GGameEventManager);
	g_pGameEvent.HookMethod(8, (DWORD_PTR)Hooked_FireEventClientSide);
	g_pGameEvent.HookMethod(7, (DWORD_PTR)Hooked_FireEvent);
	g_pClient.HookMethod(10, (DWORD_PTR)HudUpdate);
	g_pClient.HookMethod(8, (DWORD_PTR)HudVidInit);
 
	//GetClientMode()->HookMethod( 21, (DWORD_PTR)CreateMove );
	return true;
}