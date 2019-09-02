

#include "Font.h"
 
void CFont::Destroy()
{
	// cleanup
}

////////////////////////////////////////////////////////////////////////////////
// CFont::PrintString
//! Print some text to the screen
//! 
//! \param x - x location in pixels
//! \param y - y location in pixels
//! \param r - red value
//! \param g - green value
//! \param b - blue value
//! \param a - alpha value
//! \param dwAlign - alignment flags
//! \param szText - text to be printed
//! \param ... - variable arguments
//! \return void - 
////////////////////////////////////////////////////////////////////////////////
void CFont::PrintString( int x, int y, int r, int g, int b, int a, DWORD_PTR dwAlign, const char* szText, ... )
{
	va_list		va_alist;
	char		szBuf[1024];
	int			iLen;
	int			iWidth;
	int			iHeight;	

	va_start( va_alist, szText );
	_vsnprintf( szBuf, sizeof( szBuf ), szText, va_alist );
	va_end( va_alist );

	iLen = strlen( szBuf );

	wchar_t* pszFmt = new wchar_t[ iLen+1 ];
	mbstowcs( pszFmt, szBuf, iLen+1 );

	GSurface->GetTextSize( m_id, pszFmt, iWidth, iHeight );

	if( dwAlign & kAlign_Right )
		x -= iWidth;
	else if( dwAlign & kAlign_CenterH )
		x -= iWidth/2;
	if( dwAlign & kAlign_CenterV )
		y -= iHeight/2;

	GSurface->DrawSetTextColor( r, g, b, a );
	GSurface->DrawSetTextFont( m_id );
	GSurface->DrawSetTextPos( x, y );
	GSurface->DrawPrintText( pszFmt, iLen );

	SAFE_DELETE_ARRAY( pszFmt );
}

  CFont* CFont::CreateFont(const char* szFace, int iSize, int iWeight, int iFlags) {
	CFont* pFont = new CFont;

	if (!pFont)
	{
		return NULL;
	}

	pFont->m_id = GSurface->CreateFont();

	if (!pFont->m_id)
	{
		SAFE_DELETE(pFont);
		return NULL;
	}

	if (!GSurface->SetFontGlyphSet(pFont->m_id, szFace, iSize, iWeight, 0, 0, iFlags))
	{
		SAFE_DELETE(pFont);
		return NULL;
	}

	pFont->m_size = iSize;
 

	return pFont;
}