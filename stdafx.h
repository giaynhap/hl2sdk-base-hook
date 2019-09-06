// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef _DEBUG
#error "Please compile me in Release mode!"
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <d3d9.h>
/*
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")
*/

#pragma comment (lib, "d3d9.lib")


#include "detours.h"
#pragma comment(lib,"detours.lib")


 

// Additional includes (core)
#include "HL2_SDK.h"


#include <string>
#include <vector>
typedef struct {
	int team;
	char name[512];
	int health;
	char modelname[64];
	bool isbot;
	bool isConnect;
	int armor;
	bool alive;
	int score;
} gn_player_info_t;

typedef struct {
	int ct;
	int ter;
	int score;
}team_score_t;
 


#include "Manager.h"

#include "Render.h"
#include "Hook.h"
#include "Log.h"
#include "VMethod.h"
#include "Surface.h"
#include "Font.h"
bool HookEventMessage(IGameEvent * event);
bool HookEventMessage_2(IGameEvent * event);
// super-global
extern IBaseClientDLL*				GClient;
extern IVRenderView*				GRenderView;
extern IFileSystem*					GFileSystem;
extern IPrediction*					GPrediction;
extern IVModelRender*				GModelRender;
extern IClientEntityList*			GEntList;
extern IMatSystemSurface*			GMatSurface;
extern vgui::ISurface*				GSurface;
extern IVEfx*						GEffects;
extern ICvar*						GCvarInterface;
extern IPanel*						GPanel;
extern IVEngineClient*				GEngine;
extern IEngineTrace*				GEnginetrace;
extern IVModelInfo*					GModelinfo;
extern IEngineVGui*					GEnginevgui;
extern IVDebugOverlay*				GDebugOverlay;
extern CInput*						GInput;
extern CGlobalVarsBase*				GGlobals;
extern IGameEventManager2*			GGameEventManager;
extern IMaterialSystem*				GMatSystem;
extern IPhysicsSurfaceProps*		GPhysicAPI;
extern IUniformRandomStream*		GRandom;
extern IShadowMgr*					GShadowMgr;
extern IGameUIFuncs*				GGameUIFuncs;
extern IEngineSound*				GEngineSound;
 
#ifndef INCLUDE
#define INCLUDE

extern CVMethod g_pClient;
extern CVMethod g_pVGUI;
extern CVMethod g_pPanel;
 
extern int scr_Size[2];



typedef struct {
	long id;
	int width;
	int height;
} image_t;

#include "Graphic.h"
#include "ScoreBoard.h"
#include "KillMark.h"

#ifdef GNHOOOK_API
#define GNHOOOK_API __declspec(dllexport)
#else
#define GNHOOOK_API __declspec(dllimport)
#endif
extern "C" GNHOOOK_API  void gn_hook_init();

#endif