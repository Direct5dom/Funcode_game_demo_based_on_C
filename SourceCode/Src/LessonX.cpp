// Funcode game demo based on C
// (C) SI-Xiaolong(ustb_stu_sixiaolong@outlook.com)
// (c) LU-Wanning
// (C) SONG-Yao
// Apache License 2.0
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//包含头文件
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonAPI.h"
#include "LessonX.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//全局变量
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//这部分全局变量牵扯到游戏状态
int	g_iGameState = 1;				//游戏状态，0 -- 游戏结束等待开始状态；1 -- 初始化游戏；2 -- 游戏进行中；
int	g_Play = 0;						//鼠标是否在Play上
int	g_About = 0;					//鼠标是否在About上
int g_Back = 0;						//鼠标是否在Back上
int g_GG = 0;						//鼠标是否在“通关”上
int MapLoad = 0;					//游戏关卡
int	g_BLevel = 0;					//当前大关
int	g_SLevel = 0;					//当前小关
float g_GameTime = 0;				//游戏运行时间
float g_BossAttackTime1 = 1;		//BOSS攻击时间1
float g_BossAttackTime2 = 1;		//BOSS攻击时间2
float g_BossAttackTime3 = 1;		//BOSS攻击时间3
float g_BossAttackTime4 = 1;
////////////////////////////////////////////////////////////////////////////////
//这部分全局变量牵扯到游戏的BOSS关设计
int	g_BOSS1_HP = 100;				//第一BOSS的HP
int	g_BOSS2_HP = 200;				//第二BOSS的HP
int g_BOSS3_HP = 300;				//第三BOSS的HP
int g_BOSS4_HP = 400;				//第四BOSS的HP
int g_BOSS1IsAlive = 1;				//第一Boss是否存活
int g_BOSS2IsAlive = 1;				//第二Boss是否存活
int g_BOSS3IsAlive = 1;				//第三Boss是否存活
int g_BOSS4IsAlive = 1;				//第四Boss是否存活
int BossIsMeX;						//BOSSX轴坐标
int BossIsMeY;						//BOSSY轴坐标
///////////////////////////////////////////////////////////////////////////////
//这部分是初始化、进行中、结束的函数定义。
void		GameInit();
void		GameRun(float fDeltaTime);
void		GameEnd();
///////////////////////////////////////////////////////////////////////////////
//位移状态相关的全局变量
float StartX = 0;							//上一个存储的主角位置X
float StartY = 0;							//上一个存储的主角位置Y
float NowX = 0;								//现在的主角位置X
float NowY = 0;								//现在的主角位置Y
float NowVX = 0;							//现在的主角速度X
float NowVY = 0;							//现在的主角速度Y
///////////////////////////////////////////////////////////////////////////////
//准备新精灵的名字
char *destWQ = dMakeSpriteName("WQ", 0);					//主角攻击1
char *destBOSSWQ = dMakeSpriteName("BOSSWQ", 0);			//BOSS攻击1
char *destBLD = dMakeSpriteName("BLD", 0);					//死亡效果
char *destBOSSBLD = dMakeSpriteName("BOSSBLD", 0);			//BOSS死亡效果
char *destSSLM = dMakeSpriteName("SSLM", 0);				//第四章的飞碟
char *destZSLMTT = dMakeSpriteName("ZSLMTT", 0);			//第四章的飞碟
///////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//函数区
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//==============================================================================
//
// 大体的程序流程为：GameMainLoop函数为主循环函数，在引擎每帧刷新屏幕图像之后，都会被调用一次。


//==============================================================================
//
// 游戏主循环，此函数将被不停的调用，引擎每刷新一次屏幕，此函数即被调用一次
// 用以处理游戏的开始、进行中、结束等各种状态. 
// 函数参数fDeltaTime : 上次调用本函数到此次调用本函数的时间间隔，单位：秒
void GameMainLoop( float	fDeltaTime )
{
	switch( g_iGameState )
	{
		// 初始化游戏，清空上一局相关数据
	case 1:
		{
			GameInit();
			g_iGameState	=	2; // 初始化之后，将游戏状态设置为进行中
		}
		break;

		// 游戏进行中，处理各种游戏逻辑
	case 2:
		{
			GameRun( fDeltaTime );
		}
		break;
	default:
		break;
	};
}
//==============================================================================
//
// 每局开始前进行初始化，清空上一局相关数据
void GameInit()
{
	//变量初始化
	g_BossAttackTime1 = 1;		//BOSS攻击时间1
	g_BossAttackTime2 = 1;		//BOSS攻击时间2
	g_BossAttackTime3 = 1;		//BOSS攻击时间3
	g_BossAttackTime4 = 1;
	g_BOSS1_HP = 100;				//第一BOSS的HP
	g_BOSS2_HP = 200;				//第二BOSS的HP
	g_BOSS3_HP = 300;
	g_BOSS4_HP = 400;
	g_BOSS1IsAlive = 1;				//第一Boss是否存活
	g_BOSS2IsAlive = 1;				//第二Boss是否存活
	g_BOSS3IsAlive = 1;
	g_BOSS4IsAlive = 1;

	dAnimateSpritePlayAnimation("main", "xingxiong4Animation1", 0);
	MapSelection();			//地图选择
	NPC1();					//NPC行为
	StartX = dGetSpritePositionX("main");
	StartY = dGetSpritePositionY("main");

	//dSetSpriteLinearVelocityX("YCBJ", 20);
	dSetSpriteLinearVelocityPolar("SSLM", 80, 30);

}
//==============================================================================
//
// 每局游戏进行中
void GameRun( float fDeltaTime )
{
	GravitySimulation();	//重力模拟

	dSetSpriteLinearVelocityY("P1T", -5);

	NowX = dGetSpritePositionX("main");
	NowY = dGetSpritePositionY("main");

	NowVX = dGetSpriteLinearVelocityX("main");
	NowVY = dGetSpriteLinearVelocityY("main");

	BOSS1();

	BOSS2();
	
	BOSS3();

	BOSS4();

	dSetTextValue("text1", g_BLevel);
	dSetTextValue("text2", g_SLevel);
}
//==========================================================================
//
// 鼠标移动
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void OnMouseMove( const float fMouseX, const float fMouseY )
{
	g_Play = dIsPointInSprite("Play", fMouseX, fMouseY);
	g_GG = dIsPointInSprite("GG", fMouseX, fMouseY);
	g_Back = dIsPointInSprite("BACK", fMouseX, fMouseY);
	g_About = dIsPointInSprite("About", fMouseX, fMouseY);
}
//==========================================================================
//
// 鼠标点击
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	if (MOUSE_LEFT == iMouseType && g_Play == 1)
	{
		MapLoad = 1;
		g_iGameState = 1;
	}
	else if (MOUSE_LEFT == iMouseType && g_GG == 1)
	{
		MapLoad = 0;
		g_iGameState = 1;
	}
	else if (MOUSE_LEFT == iMouseType && g_Back == 1)
	{
		MapLoad = 0;
		g_iGameState = 1;
	}
	else if (MOUSE_LEFT == iMouseType && g_About == 1)
	{
		MapLoad = 19;
		g_iGameState = 1;
	}
}

void OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY)
{

}
//==========================================================================
//
// 键盘按下
// 参数 iKey：被按下的键，值见 enum KeyCodes 宏定义
// 参数 iAltPress, iShiftPress，iCtrlPress：键盘上的功能键Alt，Ctrl，Shift当前是否也处于按下状态(0未按下，1按下)
void OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{	
	if (KEY_UP == iKey && 0 == dGetSpriteLinearVelocityY("main"))
	{
		dSetSpriteLinearVelocityY("main", -85);
	}

	else if (KEY_LEFT == iKey)
	{
		dSetSpriteLinearVelocityX("main", -60);
		dSetSpriteFlipX("main", 1);
		dAnimateSpritePlayAnimation("main", "xingxiong4Animation", 0);
	}

	else if (KEY_RIGHT == iKey)
	{
		dSetSpriteLinearVelocityX("main", 60);
		dSetSpriteFlipX("main", 0);
		dAnimateSpritePlayAnimation("main", "xingxiong4Animation", 0);
	}

	else if (KEY_Q == iKey && g_SLevel == 4)
	{
		Attack1();
	}

	else if (KEY_W == iKey && g_SLevel == 4)
	{
		Attack2();
	}

	else if (KEY_E == iKey && g_SLevel == 4)
	{
		Attack3();
	}

	else if (KEY_R == iKey && g_BLevel == 4)
	{
		Attack4();
	}
}
//==========================================================================
//
// 键盘弹起
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
void OnKeyUp(const int iKey)
{
	if (KEY_UP == iKey)
	{
		dAnimateSpritePlayAnimation("main", "xingxiong4Animation1", 0);
	}

	else if (KEY_LEFT == iKey)
	{
		dSetSpriteLinearVelocityX("main",0);
		dAnimateSpritePlayAnimation("main", "xingxiong4Animation1", 0);
	}

	else if (KEY_RIGHT == iKey)
	{
		dSetSpriteLinearVelocityX("main", 0);
		dAnimateSpritePlayAnimation("main", "xingxiong4Animation1", 0);
	}
}
//===========================================================================
//
// 精灵与精灵碰撞
// 参数 szSrcName：发起碰撞的精灵名字
// 参数 szTarName：被碰撞的精灵名字
void OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{


	if (strstr(szTarName, "C") && strstr(szSrcName, "main"))
	{
		Dead();
	}

	else if (strstr(szTarName, destBOSSWQ) && strstr(szSrcName, "main"))
	{
		Dead();
	}

	else if (strstr(szTarName, "SJZ") && strstr(szSrcName, destWQ))
	{
		g_BOSS1_HP -= 1;
		//拷贝BLD到destBLD
		dCloneSprite("BLD", destBLD);
		//BLD发出
		dSetSpritePosition(destBLD, 26, -22);
	}

	else if (strstr(szTarName, "W") && strstr(szSrcName, destWQ))
	{
		g_BOSS2_HP -= 1;
		//拷贝BLD到destBLD
		dCloneSprite("BLD", destBLD);
		//BLD发出
		dSetSpritePosition(destBLD, 26, -22);
	}

	else if (strstr(szTarName, "FS") && strstr(szSrcName, destWQ))
	{
		g_BOSS3_HP -= 1;
		//拷贝BLD到destBLD
		dCloneSprite("BLD", destBLD);
		//BLD发出
		dSetSpritePosition(destBLD, 26, -22);
	}

	else if (strstr(szTarName, "V") && strstr(szSrcName, destWQ))
	{
		g_BOSS4_HP -= 1;
		//拷贝BLD到destBLD
		dCloneSprite("BLD", destBLD);
		//BLD发出
		dSetSpritePosition(destBLD, 26, -22);
	}

	else if (((strstr(szTarName, "TSLM1")) || (strstr(szTarName, "TSLM2")) || (strstr(szTarName, "TSLM3")) || (strstr(szTarName, "SLM1")) || (strstr(szTarName, "SLM2")) || (strstr(szTarName, "SLM3")) && strstr(szSrcName, "main")))
	{
		Dead();
	}

	else if (strstr(szTarName, "BK_USE") && strstr(szSrcName, destBOSSWQ))
	{
		dDeleteSprite("BK_USE");
	}
}
//===========================================================================
//
// 精灵与世界边界碰撞
// 参数 szName：碰撞到边界的精灵名字
// 参数 iColSide：碰撞到的边界 0 左边，1 右边，2 上边，3 下边
void OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	if (strstr(szName, "P1T") != NULL)
	{
		if (iColSide == 2) 
		{
			MapLoad = 2;
			g_iGameState = 1;
		}
	}

	else if (strstr(szName, "main") != NULL)
	{
		if (iColSide == 0)
		{
			dSetSpriteLinearVelocityX("main", 0);
		}
		else if (iColSide == 1)
		{
			MapNext();
		}
		else if (iColSide == 3)
			Dead();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//自定义功能区
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
//
//地图选择
void MapSelection()
{
	switch (MapLoad) {
	case 0:
		dStopAllSound();
		dLoadMap("MU.t2d");
		dPlaySound("LifeLine.wav", 1, 1);
		break;
	case 1:
		dStopAllSound();
		dLoadMap("OP.t2d");
		dPlaySound("LTQF.wav", 1, 1);
		break;
	case 2:
		dStopAllSound();
		dLoadMap("T01.t2d");
		dPlaySound("TWP2_N.wav", 1, 1);
		g_BLevel = 1;
		g_SLevel = 1;
		break;
	case 3:
		dLoadMap("T02.t2d");
		g_BLevel = 1;
		g_SLevel = 2;
		break;
	case 4:
		dLoadMap("T03.t2d");
		g_BLevel = 1;
		g_SLevel = 3;
		break;
	case 5:
		dStopAllSound();
		dLoadMap("T04B.t2d");
		dPlaySound("FIGHT.wav", 1, 1);
		g_BLevel = 1;
		g_SLevel = 4;
		break;
	case 6:
		dStopAllSound();
		dLoadMap("TT01.t2d");
		dPlaySound("Synthetech.wav", 1, 1);
		g_BLevel = 2;
		g_SLevel = 1;
		break;
	case 7:
		dLoadMap("TT02.t2d");
		g_BLevel = 2; 
		g_SLevel = 2;
		break;
	case 8:
		dLoadMap("TT03.t2d");
		g_BLevel = 2;
		g_SLevel = 3;
		break;
	case 9:
		dStopAllSound();
		dLoadMap("TT04B.t2d");
		dPlaySound("ZQZ.wav", 1, 1);
		g_BLevel = 2;
		g_SLevel = 4;
		break;
	case 10:
		dStopAllSound();
		dLoadMap("TTT01.t2d");
		dPlaySound("YDZ.wav", 1, 1);
		g_BLevel = 3;
		g_SLevel = 1;
		break;
	case 11:
		dLoadMap("TTT02.t2d");
		g_BLevel = 3;
		g_SLevel = 2;
		break;
	case 12:
		dLoadMap("TTT03.t2d");
		g_BLevel = 3;
		g_SLevel = 3;
		break;
	case 13:
		dStopAllSound();
		dLoadMap("TTT04B.t2d");
		dPlaySound("ZJDKZ.wav", 1, 1);
		g_BLevel = 3;
		g_SLevel = 4;
		break;
	case 14:
		dStopAllSound();
		dLoadMap("TTTT01.t2d");
		dPlaySound("VeiledinBlack.wav", 1, 1);
		g_BLevel = 4;
		g_SLevel = 1;
		break;
	case 15:
		dLoadMap("TTTT02.t2d");
		g_BLevel = 4;
		g_SLevel = 2;
		break;
	case 16:
		dLoadMap("TTTT03.t2d");
		g_BLevel = 4;
		g_SLevel = 3;
		break;
	case 17:
		dStopAllSound();
		dLoadMap("TTTT04.t2d");
		dPlaySound("APOCALYPSISAQUARIUS.wav", 1, 1);
		g_BLevel = 4;
		g_SLevel = 4;
		break;
	case 18:
		dLoadMap("GG.t2d");
		g_BLevel = 0;
		g_SLevel = 0; 
		break;
	case 19:
		dLoadMap("ABOUT.t2d");
		g_BLevel = 0;
		g_SLevel = 0;
		break;
	default:
		break;
	}
}
//===========================================================================
//
//下一张地图
void MapNext()
{
	MapLoad += 1;
	g_iGameState = 1;
}
//===========================================================================
//
//重力模拟
void GravitySimulation()
{
	if(g_BLevel == 4)
		dSetSpriteConstantForceY("main", 100);
	else
		dSetSpriteConstantForceY("main", 40);
}
//===========================================================================
//
//死亡处理
void Dead()
{
	//拷贝BLD到destBLD
	dCloneSprite("BLD", destBLD);
	//BLD发出
	dSetSpritePosition(destBLD, NowX, NowY);
	//main恢复上个坐标
	dSetSpritePosition("main", StartX, StartY);
	//停稳
	dSetSpriteLinearVelocityX("main", 0);
}
//===========================================================================
//
//BOSS1行为
void BOSS1()
{
	if (g_BLevel == 1 && g_SLevel == 4)
	{
		//获取BOSSX的坐标
		BossIsMeX = dGetSpritePositionX("SJZ");
		BossIsMeY = dGetSpritePositionY("SJZ");

		if (g_BossAttackTime1 - g_GameTime < 0 && NowX > -38 && NowY < 12 && g_BOSS1_HP > 0)
		{
			//拷贝WQ到destWQ
			dCloneSprite("BOSSWQ", destBOSSWQ);
			//武器从BOSS发出
			dSetSpritePosition(destBOSSWQ, BossIsMeX, NowY);
			dSetSpriteLinearVelocityX(destBOSSWQ, -60);
			dSetSpriteAngularVelocity(destBOSSWQ, 500);
			g_BossAttackTime1 = g_GameTime + 1;
		}
		else if (g_BOSS1_HP < 0 && g_BOSS1IsAlive == 1)	//DEAD
		{
			//拷贝BLD到destBLD
			dCloneSprite("BOSSBLD", destBOSSBLD);
			//BLD发出
			dSetSpritePosition(destBOSSBLD, BossIsMeX, BossIsMeY);
			//删除boss精灵
			dDeleteSprite("SJZ");
			g_BOSS1IsAlive = 0;
			dDeleteSprite("BK_OUT");
		}
	}
}
//===========================================================================
//
//BOSS2行为
void BOSS2()
{
	if (g_BLevel == 2 && g_SLevel == 4)
	{
		//获取BOSSX的坐标
		BossIsMeX = dGetSpritePositionX("W");
		BossIsMeY = dGetSpritePositionY("W");

		if (g_BossAttackTime2 - g_GameTime < 0 && g_BOSS2_HP > 100)
		{
			//拷贝WQ到destWQ
			dCloneSprite("BOSSWQ", destBOSSWQ);
			//武器从BOSS发出
			dSetSpritePosition(destBOSSWQ, NowX, -32);
			dSetSpriteLinearVelocityY(destBOSSWQ, 60);
			dSetSpriteAngularVelocity(destBOSSWQ, 500);
			g_BossAttackTime2 = g_GameTime + 1;
		}
		else if (g_BossAttackTime2 - g_GameTime < 0 && g_BOSS2_HP < 100 && g_BOSS2_HP >0)
		{
			for (int i = 0; i < 20; i++)
			{
				//拷贝WQ到destWQ
				dCloneSprite("BOSSWQ", destBOSSWQ);
				//武器从BOSS发出
				dSetSpritePosition(destBOSSWQ, 26, -22);
				dSetSpriteLinearVelocityPolar(destBOSSWQ, 80, (18 * i));
				dSetSpriteAngularVelocity(destBOSSWQ, 500);
			}
			g_BossAttackTime2 = g_GameTime + 2;
		}
		else if (g_BOSS2_HP < 0 && g_BOSS2IsAlive == 1)	//DEAD
		{
			//拷贝BLD到destBLD
			dCloneSprite("BOSSBLD", destBOSSBLD);
			//BLD发出
			dSetSpritePosition(destBOSSBLD, 26, -22);
			//删除boss精灵
			dDeleteSprite("W");
			g_BOSS2IsAlive = 0;
			dDeleteSprite("BK_OUT");
		}
	}
}
//===========================================================================
//
//BOSS3行为
void BOSS3()
{
	if (g_BLevel == 3 && g_SLevel == 4)
	{
		//获取BOSSX的坐标
		BossIsMeX = dGetSpritePositionX("FS");
		BossIsMeY = dGetSpritePositionY("FS");

		if (g_BossAttackTime3 - g_GameTime < 0 && g_BOSS3_HP > 200)
		{
			//拷贝WQ到destWQ
			dCloneSprite("BOSSWQ", destBOSSWQ);
			//武器从BOSS发出
			dSetSpritePosition(destBOSSWQ, NowX, -37);
			dSetSpriteLinearVelocityY(destBOSSWQ, 60);
			dSetSpriteAngularVelocity(destBOSSWQ, 500);
			g_BossAttackTime3 = g_GameTime + 1;
		}
		else if (g_BossAttackTime3 - g_GameTime < 0 && g_BOSS3_HP < 200 && g_BOSS3_HP >100)
		{
			for (int i = 0; i < 10; i++)
			{
				//拷贝WQ到destWQ
				dCloneSprite("BOSSWQ", destBOSSWQ);
				//武器从BOSS发出
				dSetSpritePosition(destBOSSWQ, 26, -22);
				dSetSpriteLinearVelocityPolar(destBOSSWQ, 80, (36 * i));
				dSetSpriteAngularVelocity(destBOSSWQ, 500);
			}
			g_BossAttackTime3 = g_GameTime + 2;
		}
		else if (g_BossAttackTime3 - g_GameTime < 0 && g_BOSS3_HP < 100 && g_BOSS3_HP >0)
		{
			for (int i = 0; i < 40; i++)
			{
				//拷贝WQ到destWQ
				dCloneSprite("BOSSWQ", destBOSSWQ);
				//武器从BOSS发出
				dSetSpritePosition(destBOSSWQ, 26, -22);
				dSetSpriteLinearVelocityPolar(destBOSSWQ, 80, (9 * i));
				dSetSpriteAngularVelocity(destBOSSWQ, 500);
			}
			g_BossAttackTime3 = g_GameTime + 2;
		}
		else if (g_BOSS3_HP < 0 && g_BOSS3IsAlive == 1)	//DEAD
		{
			//拷贝BLD到destBLD
			dCloneSprite("BOSSBLD", destBOSSBLD);
			//BLD发出
			dSetSpritePosition(destBOSSBLD, 26, -22);
			//删除boss精灵
			dDeleteSprite("FS");
			g_BOSS3IsAlive = 0;
			dDeleteSprite("BK_OUT");
		}
	}
}
//===========================================================================
//
//BOSS4行为
void BOSS4()
{
	if (g_BLevel == 4 && g_SLevel == 4)
	{
		//获取BOSSX的坐标
		BossIsMeX = dGetSpritePositionX("V");
		BossIsMeY = dGetSpritePositionY("V");

		if (g_BossAttackTime4 - g_GameTime < 0 && g_BOSS4_HP > 300)
		{
			//拷贝WQ到destWQ
			dCloneSprite("BOSSWQ", destBOSSWQ);
			//武器从BOSS发出
			dSetSpritePosition(destBOSSWQ, NowX, -37);
			dSetSpriteLinearVelocityY(destBOSSWQ, 60);
			dSetSpriteAngularVelocity(destBOSSWQ, 500);
			g_BossAttackTime4 = g_GameTime + 1;
		}
		else if (g_BossAttackTime4 - g_GameTime < 0 && g_BOSS4_HP < 300 && g_BOSS4_HP > 200)
		{
			for (int i = 0; i < 10; i++)
			{
				//拷贝WQ到destWQ
				dCloneSprite("BOSSWQ", destBOSSWQ);
				//武器从BOSS发出
				dSetSpritePosition(destBOSSWQ, 26, -22);
				dSetSpriteLinearVelocityPolar(destBOSSWQ, 80, (36 * i));
				dSetSpriteAngularVelocity(destBOSSWQ, 500);
			}
			g_BossAttackTime4 = g_GameTime + 2;
		}
		else if (g_BossAttackTime4 - g_GameTime < 0 && g_BOSS4_HP < 200 && g_BOSS4_HP > 100)
		{
			for (int i = 0; i < 10; i++)
			{
				//拷贝WQ到destWQ
				dCloneSprite("BOSSWQ", destBOSSWQ);
				//武器从BOSS发出
				dSetSpritePosition(destBOSSWQ, 26, -22);
				dSetSpriteLinearVelocityPolar(destBOSSWQ, 80, (36 * i));
				dSetSpriteAngularVelocity(destBOSSWQ, 500);
			}
			g_BossAttackTime4 = g_GameTime + 2;
		}
		else if (g_BossAttackTime4 - g_GameTime < 0 && g_BOSS4_HP < 100 && g_BOSS4_HP > 0)
		{
			//拷贝WQ到destWQ
			dCloneSprite("BOSSWQ", destBOSSWQ);
			//武器从BOSS发出
			dSetSpritePosition(destBOSSWQ, NowX, -37);
			dSetSpriteLinearVelocityY(destBOSSWQ, 60);
			dSetSpriteAngularVelocity(destBOSSWQ, 500);
			g_BossAttackTime4 = g_GameTime + 1;
			for (int i = 0; i < 10; i++)
			{
				//拷贝WQ到destWQ
				dCloneSprite("BOSSWQ", destBOSSWQ);
				//武器从BOSS发出
				dSetSpritePosition(destBOSSWQ, 26, -22);
				dSetSpriteLinearVelocityPolar(destBOSSWQ, 80, (36 * i));
				dSetSpriteAngularVelocity(destBOSSWQ, 500);
			}
			g_BossAttackTime4 = g_GameTime + 2;
		}
		else if (g_BOSS4_HP < 0 && g_BOSS4IsAlive == 1)	//DEAD
		{
			//拷贝BLD到destBLD
			dCloneSprite("BOSSBLD", destBOSSBLD);
			//BLD发出
			dSetSpritePosition(destBOSSBLD, 26, -22);
			//删除boss精灵
			dDeleteSprite("V");
			g_BOSS4IsAlive = 0;
			MapLoad += 1;
			g_iGameState = 1;
		}
	}
}
//
//
//攻击1
void Attack1()
{
	//拷贝WQ到destWQ
	dCloneSprite("WQ", destWQ);
	//获取人物朝向
	int a = dGetSpriteFlipX("main");
	//武器从main发出
	dSetSpritePosition(destWQ, NowX, NowY);
	//分支向右
	if (a == 0)
	{
		dSetSpriteLinearVelocityX(destWQ, 60);
		dSetSpriteAngularVelocity(destWQ, 500);
	}
	//分支向左
	if (a == 1)
	{
		dSetSpriteLinearVelocityX(destWQ, -60);
		dSetSpriteAngularVelocity(destWQ, 500);
	}
}
//
//
//攻击2
void Attack2()
{
	//拷贝WQ到destWQ
	dCloneSprite("WQ", destWQ);
	//获取人物朝向
	int a = dGetSpriteFlipX("main");
	//武器从main发出
	dSetSpritePosition(destWQ, NowX, NowY);
	//分支向右
	if (a == 0)
	{
		dSetSpriteLinearVelocity(destWQ, 80, -40);
		dSetSpriteAngularVelocity(destWQ, 500);
	}
	//分支向左
	if (a == 1)
	{
		dSetSpriteLinearVelocity(destWQ, -80, -40);
		dSetSpriteAngularVelocity(destWQ, 500);
	}
}
//
//
//攻击3
void Attack3()
{
	//拷贝WQ到destWQ
	dCloneSprite("WQ", destWQ);
	//获取人物朝向
	int a = dGetSpriteFlipX("main");
	//武器从main发出
	dSetSpritePosition(destWQ, NowX, NowY);
	//分支向右
	if (a == 0)
	{
		dSetSpriteLinearVelocity(destWQ, 80, 40);
		dSetSpriteAngularVelocity(destWQ, 500);
	}
	//分支向左
	if (a == 1)
	{
		dSetSpriteLinearVelocity(destWQ, -80, 40);
		dSetSpriteAngularVelocity(destWQ, 500);
	}
}
//
//
//攻击4
void Attack4()
{
	for (int i = 0; i < 20; i++)
	{
		//拷贝WQ到destWQ
		dCloneSprite("WQ", destWQ);
		//获取人物朝向
		int a = dGetSpriteFlipX("main");
		//获取main的坐标
		const float mainX = dGetSpritePositionX("main");
		const float mainY = dGetSpritePositionY("main");
		//武器从main发出
		dSetSpritePosition(destWQ, mainX, mainY);
		dSetSpriteLinearVelocityPolar(destWQ, 80, (18 * i));
		dSetSpriteAngularVelocity(destWQ, 500);
	}
}
//
//
//敌人小兵活动轨迹
void NPC1()
{
	//第一关
	///第三小关
	dSetSpriteLinearVelocityY("TSLM1", 40);
	dSetSpriteLinearVelocityY("TSLM2", 80);
	dSetSpriteLinearVelocityY("TSLM3", 80);

	//第二关
	///第一小关
	dSetSpriteLinearVelocityY("SLM1", 40);
	dSetSpriteLinearVelocityY("SLM2", 80);
	dSetSpriteLinearVelocityX("SLM3", 80);
	///第二小关
	dSetSpriteLinearVelocityY("SLM4", 80);
	///第三小关
	dSetSpriteLinearVelocityY("BK_1", -10);
	dSetSpriteLinearVelocityY("BK_2", -11);
	dSetSpriteLinearVelocityX("BK_3", -12);
	dSetSpriteLinearVelocityY("BK_4", -13);
	
	//第三关
	///第二小关
	dSetSpriteLinearVelocityY("MU_01", -10);
	dSetSpriteLinearVelocityY("MU_02", 20);
	///第三小关
	dSetSpriteLinearVelocity("TTTSLM01", -10, 22);
	dSetSpriteLinearVelocity("TTTSLM02", 22, 10);
	dSetSpriteLinearVelocity("TTTSLM03", 19, 15);

	//第四关
	///第一小关
	for (int i = 0; i < 30; i++)
	{
		dCloneSprite("SSLM", destSSLM);
		dSetSpritePosition(destSSLM, -1, -7);
		dSetSpriteLinearVelocityPolar(destSSLM, 80, ((10 * i)+30));
	}
	///第二小关
	for (int i = 0; i < 35; i++)
	{
		dCloneSprite("ZSLMTT", destZSLMTT);
		dSetSpritePosition(destZSLMTT, -1, -7);
		dSetSpriteLinearVelocityPolar(destZSLMTT, 80, ((10 * i) + 30));
	}
}
