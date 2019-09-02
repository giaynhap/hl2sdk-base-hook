////////////////////////////////////////////////////////////////////////////////
//! SourceBase By Chod
#include "Surface.h"


////////////////////////////////////////////////////////////////////////////////
// CSurface::DrawSetColour
//! DESCRIPTION
//! 
//! \param r - 
//! \param g - 
//! \param b - 
//! \param a - 
//! \return void - 
////////////////////////////////////////////////////////////////////////////////
void CSurface::DrawSetColour( int r, int g, int b, int a )
{
	typedef void ( __thiscall *tDrawSetColor )( void*, int, int, int, int );
	GetMethod< tDrawSetColor >( ID_DRAWSETCOLOUR )( GetInstance(), r, g, b, a );
}

////////////////////////////////////////////////////////////////////////////////
// CSurface::DrawLine
//! DESCRIPTION
//! 
//! \param x0 - 
//! \param y0 - 
//! \param x1 - 
//! \param y1 - 
//! \return void - 
////////////////////////////////////////////////////////////////////////////////
void CSurface::DrawLine( int x0, int y0, int x1, int y1 )
{
	typedef void ( __thiscall *tDrawLine )( void*, int x0, int y0, int x1, int y1 );
	GetMethod< tDrawLine >( ID_DRAWLINE )( GetInstance(), x0, y0, x1, y1 );
}

////////////////////////////////////////////////////////////////////////////////
// CSurface::DrawFilledRect
//! DESCRIPTION
//! 
//! \param x - 
//! \param y - 
//! \param w - 
//! \param h - 
//! \return void - 
////////////////////////////////////////////////////////////////////////////////
void CSurface::DrawFilledRect( int x, int y, int w, int h )
{
	typedef void ( __thiscall *tDrawFilledRect )( void*, int x0, int y0, int x1, int y1 );
	GetMethod< tDrawFilledRect >( ID_DRAWFILLEDRECT )( GetInstance(), x, y, x+w, y+h );
}

////////////////////////////////////////////////////////////////////////////////
// CSurface::CreateFont
//! DESCRIPTION
//! 
//! \return unsigned long - 
////////////////////////////////////////////////////////////////////////////////
unsigned long CSurface::CreateFont( )
{
	typedef unsigned long ( __thiscall *tCreateFont )( void* );
	return GetMethod< tCreateFont >( ID_CREATEFONT )( GetInstance() );
}

////////////////////////////////////////////////////////////////////////////////
// CSurface::SetFontGlyphSet
//! DESCRIPTION
//! 
//! \param long font - 
//! \param *windowsFontName - 
//! \param tall - 
//! \param weight - 
//! \param blur - 
//! \param scanlines - 
//! \param flags - 
//! \return bool - 
////////////////////////////////////////////////////////////////////////////////
bool CSurface::SetFontGlyphSet( unsigned long font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags )
{
	typedef bool ( __thiscall *tSetFontGlyphSet )( void*, unsigned long font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin, int nRangeMax );
	return GetMethod< tSetFontGlyphSet >( ID_SETFONTGLYPHSET )( GetInstance(), font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0 );
}


////////////////////////////////////////////////////////////////////////////////
// CSurface::GetTextSize
//! DESCRIPTION
//! 
//! \param long font - 
//! \param *text - 
//! \param &wide - 
//! \param &tall - 
//! \return void - 
////////////////////////////////////////////////////////////////////////////////
void CSurface::GetTextSize( unsigned long font, const wchar_t *text, int &wide, int &tall )
{
	typedef void ( __thiscall *tGetTextSize )( void*, unsigned long font, const wchar_t *text, int &wide, int &tall );
	GetMethod< tGetTextSize >( ID_GETTEXTSIZE )( GetInstance(), font, text, wide, tall );
}

////////////////////////////////////////////////////////////////////////////////
// CSurface::DrawSetTextColour
//! DESCRIPTION
//! 
//! \param r - 
//! \param g - 
//! \param b - 
//! \param a - 
//! \return void - 
////////////////////////////////////////////////////////////////////////////////
void CSurface::DrawSetTextColour( int r, int g, int b, int a )
{
	typedef void ( __thiscall *tDrawSetTextColor )( void*, int r, int g, int b, int a );
	GetMethod< tDrawSetTextColor >( ID_DRAWSETTEXTCOLOUR )( GetInstance(), r, g, b, a );
}

////////////////////////////////////////////////////////////////////////////////
// CSurface::DrawSetTextFont
//! DESCRIPTION
//! 
//! \param font - 
//! \return void - 
////////////////////////////////////////////////////////////////////////////////
void CSurface::DrawSetTextFont( unsigned long font )
{
	typedef void ( __thiscall *tDrawSetTextFont )( void*, unsigned long font );
	GetMethod< tDrawSetTextFont >( ID_DRAWSETTEXTFONT )( GetInstance(), font );
}

////////////////////////////////////////////////////////////////////////////////
// CSurface::DrawSetTextPos
//! DESCRIPTION
//! 
//! \param x - 
//! \param y - 
//! \return void - 
////////////////////////////////////////////////////////////////////////////////
void CSurface::DrawSetTextPos( int x, int y )
{
	typedef void ( __thiscall *tDrawSetTextPos )( void*, int x, int y );
	GetMethod< tDrawSetTextPos >( ID_DRAWSETTEXTPOS )( GetInstance(), x, y );
}

////////////////////////////////////////////////////////////////////////////////
// CSurface::DrawPrintText
//! DESCRIPTION
//! 
//! \param wchar_t *text - 
//! \param textLen - 
//! \return void - 
////////////////////////////////////////////////////////////////////////////////
void CSurface::DrawPrintText( const wchar_t *text, int textLen )
{
	typedef void ( __thiscall *tDrawPrintText )( void*, const wchar_t *text, int textLen, int drawType );
	GetMethod< tDrawPrintText >( ID_DRAWPRINTTEXT )( GetInstance(), text, textLen, 0 );
}