////////////////////////////////////////////////////////////////////////////////

#ifndef SURFACE_H
#define SURFACE_H

#include "stdafx.h"
#define ID_CREATEMOVE 21
#define ID_SETCURSORPOS 6
#define ID_GETCURSORPOS 7
#define ID_PAINTTRAVERSE 40
#define ID_GETVIEWANGLES 19
#define ID_SETVIEWANGLES 20
#define ID_WORLDTOSCREENMATRIX 36
#define ID_FINDCVAR 12
#define ID_TRACERAY 4
#define ID_DRAWSETCOLOUR 11
#define ID_DRAWLINE 15
#define ID_DRAWFILLEDRECT 12
#define ID_CREATEFONT 65
#define ID_SETFONTGLYPHSET 66
#define ID_GETTEXTSIZE 73
#define ID_DRAWSETTEXTCOLOUR 19
#define ID_DRAWSETTEXTFONT 17
#define ID_DRAWSETTEXTPOS 20
#define ID_DRAWPRINTTEXT 22
#define ID_GETMODELMATERIALCOUNT 15

class CSurface : public CVMethod
{
public:
	void			DrawSetColour( int r, int g, int b, int a );
	void			DrawLine( int x0, int y0, int x1, int y1 );
	void			DrawFilledRect( int x, int y, int w, int h );
	unsigned long	CreateFont( );
	bool			SetFontGlyphSet( unsigned long font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags );
	void			GetTextSize( unsigned long font, const wchar_t *text, int &wide, int &tall );
	void			DrawSetTextColour( int r, int g, int b, int a );
	void			DrawSetTextFont( unsigned long font );
	void			DrawSetTextPos( int x, int y );
	void			DrawPrintText( const wchar_t *text, int textLen );
};
extern CSurface gSurface;
#endif // SURFACE_H