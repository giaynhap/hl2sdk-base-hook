#include "stdafx.h"
#include "ISBObject.h"
#ifndef FONT_H
#define FONT_H



enum
{
	kFontFlag_NONE,
	kFontFlag_ITALIC		= 0x001,
	kFontFlag_UNDERLINE		= 0x002,
	kFontFlag_STRIKEOUT		= 0x004,
	kFontFlag_SYMBOL		= 0x008,
	kFontFlag_ANTIALIAS		= 0x010,
	kFontFlag_GAUSSIANBLUR	= 0x020,
	kFontFlag_ROTARY		= 0x040,
	kFontFlag_DROPSHADOW	= 0x080,
	kFontFlag_ADDITIVE		= 0x100,
	kFontFlag_OUTLINE		= 0x200,
	kFontFlag_CUSTOM		= 0x400,
};

enum
{
	kAlign_CenterV	= 0x1,
	kAlign_CenterH	= 0x2,
	kAlign_Left		= 0x4,
	kAlign_Right	= 0x8,
};

#ifndef SAFE_DELETE
#define SAFE_DELETE( x ) if( x ){ delete x; x = NULL; }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY( x ) if( x ){ delete [] x; x = NULL; }
#endif

class CFont : public ISBObject
{
	friend class CSourceBase;

public:
	// inherited virtual destroyer
	virtual void Destroy();
	
	void PrintString( int x, int y, int r, int g, int b, int a, DWORD_PTR dwAlign, const char* szText, ... );
	int GetTextHeight() { return m_size; }
	static CFont* CreateFont(const char* szFace, int iSize, int iWeight, int iFlags);
private:
	unsigned long	m_id;
	int				m_size;
};

#endif