#ifndef _SDK_H_
#define _SDK_H_

#ifndef CLIENT_DLL
#define CLIENT_DLL
#endif

#ifdef _UNICODE
#undef _UNICODE
#endif

#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )
#pragma warning( disable : 4541 )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4183 )

#pragma comment ( lib, "SDK/lib/public/vstdlib.lib" )
#pragma comment ( lib, "SDK/lib/public/vgui_controls.lib" )
#pragma comment ( lib, "SDK/lib/public/matsys_controls.lib" )
#pragma comment ( lib, "SDK/lib/public/mathlib.lib" )
#pragma comment ( lib, "SDK/lib/public/tier0.lib" )
#pragma comment ( lib, "SDK/lib/public/tier1.lib" )
#pragma comment ( lib, "SDK/lib/public/tier2.lib" )
#pragma comment ( lib, "SDK/lib/public/tier3.lib" )

// First
#include "SDK\\public\\tier0\\wchartypes.h"

// Public
#include "SDK\\public\\cdll_int.h"
#include "SDK\\public\\iprediction.h"
#include "SDK\\public\\bone_setup.h"
#include "SDK\\public\\icliententitylist.h"
#include "SDK\\public\\ienginevgui.h"
#include "SDK\\public\\IGameUIFuncs.h"
#include "SDK\\public\\dlight.h"
#include "SDK\\public\\iefx.h" 
#include "SDK\\public\\igameevents.h"
#include "SDK\\public\\view_shared.h"

// Client
#include "SDK\\game\\client\\imessagechars.h"
#include "SDK\\game\\client\\iclientmode.h"
#include "SDK\\game\\client\\cliententitylist.h"
#include "SDK\\game\\client\\cdll_client_int.h"
#include "SDK\\game\\client\\cbase.h"
#include "SDK\\game\\client\\c_baseanimating.h"
#include "SDK\\game\\client\\c_basecombatweapon.h"
#include "SDK\\game\\client\\c_baseplayer.h"
#include "SDK\\game\\client\\enginesprite.h"
#include "SDK\\game\\client\\input.h"
#include "SDK\\game\\client\\c_playerresource.h"
#include "SDK\\game\\client\\hl2mp\\c_hl2mp_player.h"
#include "SDK\\game\\client\\iviewrender.h"
#include "SDK\\game\\client\\viewrender.h"
#include "SDK\\game\\client\\game_controls\\commandmenu.h"
#include "SDK\\game\\client\\hudelement.h"

// Server
// #include "SDK\\game\\server\\bg2\\weapon_bg2base.h"

// Engine
#include "SDK\\public\\engine\\ivmodelrender.h"
#include "SDK\\public\\engine\\ivdebugoverlay.h"
#include "SDK\\public\\engine\\ivmodelinfo.h"
#include "SDK\\public\\engine\\IEngineTrace.h"
#include "SDK\\public\\engine\\IEngineSound.h"

// Material System
#include "SDK\\public\\materialsystem\\imaterialsystemstub.h"
#include "SDK\\public\\materialsystem\\itexture.h"
#include "SDK\\public\\materialsystem\\IMaterialVar.h"

// VGUI
#include "SDK\\public\\matsys_controls\\matsyscontrols.h"
#include "SDK\\public\\vgui\\IClientPanel.h"
#include "SDK\\public\\vgui\\IPanel.h"
#include "SDK\\public\\vgui\\ISurface.h"
#include "SDK\\public\\vgui\\ILocalize.h"

// VGUI Controls
#include "SDK\\public\\vgui_controls\\Panel.h"

// VGUI Material Surface
#include "SDK\\public\\VGuiMatSurface\\IMatSystemSurface.h"

// Shared
#include "SDK\\game\\shared\\usermessages.h"
#include "SDK\\game\\shared\\basecombatweapon_shared.h"
#include "SDK\\game\\shared\\takedamageinfo.h"

#include <windows.h>
#include <tlhelp32.h>
#include <winsock.h>
#include <algorithm>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <vector>
#include <fstream>
#include <istream>
#include <string.h>

#define SECURITY_WIN32
#define WIN32_LEAN_AND_MEAN

#pragma optimize( "gsy", on )
#include <Security.h>
#include <shlwapi.h>

class CVMTHook
{
private:
	PDWORD m_pdwClassTable;
	int m_iFunctionIndex;
	PDWORD m_pdwFuntionPointer;
	DWORD m_dwNewFunction;
	DWORD m_dwOriginalFunction;
	DWORD m_dwOldProtect;
public:
	DWORD Hook( DWORD new_Function, PDWORD pClass, int Index ){
		m_dwNewFunction = new_Function;
		m_pdwClassTable = ( PDWORD ) * ( PDWORD ) pClass;
		m_iFunctionIndex = Index;
		m_pdwFuntionPointer = ( m_pdwClassTable + ( 0x4 * m_iFunctionIndex ) );
		m_dwOriginalFunction = m_pdwClassTable[ m_iFunctionIndex ];
		VirtualProtect( ( LPVOID ) m_pdwFuntionPointer, 4, PAGE_EXECUTE_READWRITE, &m_dwOldProtect );
		m_pdwClassTable[ m_iFunctionIndex ] = m_dwNewFunction;
		VirtualProtect( ( LPVOID ) m_pdwFuntionPointer, 4, m_dwOldProtect, NULL );
		return m_dwOriginalFunction;
	}

	void UnHook( void ){
		VirtualProtect( ( LPVOID ) m_pdwFuntionPointer, 4, PAGE_EXECUTE_READWRITE, &m_dwOldProtect );
		m_pdwClassTable[ m_iFunctionIndex ] = m_dwOriginalFunction;
		VirtualProtect( ( LPVOID ) m_pdwFuntionPointer, 4, m_dwOldProtect, NULL );
	}
	void ReHook( void ){
		VirtualProtect( ( LPVOID ) m_pdwFuntionPointer, 4, PAGE_EXECUTE_READWRITE, &m_dwOldProtect );
		m_pdwClassTable[ m_iFunctionIndex ] = m_dwNewFunction;
		VirtualProtect( ( LPVOID ) m_pdwFuntionPointer, 4, m_dwOldProtect, NULL );
	}
    DWORD FunctionAddress( void ){
		return m_dwOriginalFunction;
	}
};

#define IN_ATTACK					(1 << 0)
#define IN_JUMP						(1 << 1)
#define IN_DUCK						(1 << 2)
#define IN_FORWARD					(1 << 3)
#define IN_BACK						(1 << 4)
#define IN_USE						(1 << 5)
#define IN_CANCEL					(1 << 6)
#define IN_LEFT						(1 << 7)
#define IN_RIGHT					(1 << 8)
#define IN_MOVELEFT					(1 << 9)
#define IN_MOVERIGHT				(1 << 10)
#define IN_ATTACK2					(1 << 11)
#define IN_RUN						(1 << 12)
#define IN_RELOAD					(1 << 13)
#define IN_ALT1						(1 << 14)
#define IN_ALT2						(1 << 15)
#define IN_SCORE					(1 << 16)
#define IN_SPEED					(1 << 17)
#define IN_WALK						(1 << 18)
#define IN_ZOOM						(1 << 19)
#define IN_WEAPON1					(1 << 20)
#define IN_WEAPON2					(1 << 21)
#define IN_BULLRUSH					(1 << 22)

#define	HIDEHUD_WEAPONSELECTION		( 1<<0 )
#define	HIDEHUD_FLASHLIGHT			( 1<<1 )
#define	HIDEHUD_ALL					( 1<<2 )
#define HIDEHUD_HEALTH				( 1<<3 )
#define HIDEHUD_PLAYERDEAD			( 1<<4 )
#define HIDEHUD_NEEDSUIT			( 1<<5 )
#define HIDEHUD_MISCSTATUS			( 1<<6 )
#define HIDEHUD_CHAT				( 1<<7 )
#define	HIDEHUD_CROSSHAIR			( 1<<8 )
#define	HIDEHUD_VEHICLE_CROSSHAIR	( 1<<9 )
#define HIDEHUD_INVEHICLE			( 1<<10 )
#define HIDEHUD_SCOPE				( 1<<11 )

#define WEAPON_NULL					0
#define WEAPON_AK47					1
#define WEAPON_AUG					2
#define WEAPON_AWP					3
#define WEAPON_DEAGLE				4
#define WEAPON_ELITES				5
#define WEAPON_FAMAS				6
#define WEAPON_FIVESEVEN			7
#define WEAPON_G3SG1				8
#define WEAPON_GALIL				9
#define WEAPON_GLOCK18				10
#define WEAPON_M249					11
#define WEAPON_M3					12
#define WEAPON_M4A1					13
#define WEAPON_MAC10				14
#define WEAPON_MP5					15
#define WEAPON_P228					16
#define WEAPON_P90					17
#define WEAPON_SCOUT				18
#define WEAPON_SG550				19  
#define WEAPON_SG552				20 
#define WEAPON_TMP					21
#define WEAPON_UMP45				22
#define WEAPON_USP45				23
#define WEAPON_XM1014				24
#define WEAPON_KNIFE				25
#define WEAPON_FLASHBANG			26 
#define WEAPON_HE_GRENADE			27
#define WEAPON_SMOKE_GRENADE		28 
#define WEAPON_C4					29

#define CHAR_TEX_CONCRETE			'C'
#define CHAR_TEX_METAL				'M'
#define CHAR_TEX_DIRT				'D'
#define CHAR_TEX_VENT				'V'
#define CHAR_TEX_GRATE				'G'
#define CHAR_TEX_TILE				'T'
#define CHAR_TEX_SLOSH				'S'
#define CHAR_TEX_WOOD				'W'
#define CHAR_TEX_COMPUTER			'P'
#define CHAR_TEX_GLASS				'Y'
#define CHAR_TEX_FLESH				'F'
#define CHAR_TEX_BLOODYFLESH		'B'
#define CHAR_TEX_CLIP				'I'
#define CHAR_TEX_ANTLION			'A'
#define CHAR_TEX_ALIENFLESH			'H'
#define CHAR_TEX_FOLIAGE			'O'
#define CHAR_TEX_SAND				'N'
#define CHAR_TEX_PLASTIC			'L'

#define COLORCODE(r,g,b,a)			((DWORD)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff)))
#define RED(COLORCODE)				((int) ( COLORCODE >> 24) )
#define BLUE(COLORCODE)				((int) ( COLORCODE >> 8 ) & 0xFF )
#define GREEN(COLORCODE)			((int) ( COLORCODE >> 16 ) & 0xFF )
#define ALPHA(COLORCODE)			((int) COLORCODE & 0xFF )
#define RGBA(COLORCODE)				RED( COLORCODE ), GREEN( COLORCODE ), BLUE( COLORCODE ), ALPHA( COLORCODE )

#define CHEAT_ORANGE				COLORCODE( 255, 100, 000, 255 )
#define CHEAT_YELLOW				COLORCODE( 255, 255, 0, 255 )
#define CHEAT_PURPLE				COLORCODE( 55, 25, 128, 255 )
#define CHEAT_RED					COLORCODE( 255, 0, 0, 255 )
#define CHEAT_GREEN					COLORCODE( 0, 255, 0, 255 )
#define CHEAT_BLUE					COLORCODE( 0, 0, 255, 255 )
#define CHEAT_BLACK					COLORCODE( 0, 0, 0, 255 )
#define CHEAT_WHITE					COLORCODE( 255, 255, 255, 255 )
#define CHEAT_GREY					COLORCODE( 47, 79, 79, 255 )

#define M_RADPI						57.295779513082f
#define SQUARE( a )					a*a

#define SDKProtectedHook( c, x ) \
	MEMORY_BASIC_INFORMATION mb##x; \
	VirtualQuery( ( LPVOID )&c->##x, &mb##x, sizeof( mb##x ) ); \
	VirtualProtect( mb##x.BaseAddress, mb##x.RegionSize, PAGE_EXECUTE_READWRITE, &mb##x.Protect ); \
	c->##x = &new_##x; \
	VirtualProtect( mb##x.BaseAddress, mb##x.RegionSize, mb##x.Protect, NULL ); \
	FlushInstructionCache( GetCurrentProcess( ), ( LPCVOID )&c->##x, sizeof( DWORD ) );

#endif