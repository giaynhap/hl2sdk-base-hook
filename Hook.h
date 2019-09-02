#ifndef __CSS_DEV__
#define __CSS_DEV__

bool	__stdcall Hook( void );
void Render_HudVidInt();

extern bool needNetVarUpdate;

extern DWORD_PTR FindPattern( DWORD_PTR dwAddress, DWORD_PTR dwLen, DWORD_PTR offset, bool deref, BYTE *bMask, char * szMask );
#endif