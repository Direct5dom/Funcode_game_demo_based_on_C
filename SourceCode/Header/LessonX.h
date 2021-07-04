/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>

extern void	GameMainLoop( float	fDeltaTime );
extern void OnMouseMove( const float fMouseX, const float fMouseY );
extern void OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY );
extern void OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY );
extern void OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress );
extern void OnKeyUp( const int iKey );
extern void OnSpriteColSprite( const char *szSrcName, const char *szTarName );
extern void OnSpriteColWorldLimit( const char *szName, const int iColSide );
extern void MapSelection();
extern void MapNext();
extern void GravitySimulation();
extern void Dead();
extern void BOSS1();
extern void BOSS2();
extern void BOSS3();
extern void BOSS4();
extern void Attack1();
extern void Attack2();
extern void Attack4();
extern void NPC1();
extern void Attack3();
#endif // _LESSON_X_H_