// Funcode game demo based on C
// (C) SI-Xiaolong(ustb_stu_sixiaolong@outlook.com)
// (c) LU-Wanning
// (C) SONG-Yao
// MIT License
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//����ͷ�ļ�
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonAPI.h"
#include "LessonX.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//ȫ�ֱ���
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�ⲿ��ȫ�ֱ���ǣ������Ϸ״̬
int	g_iGameState = 1;				//��Ϸ״̬��0 -- ��Ϸ�����ȴ���ʼ״̬��1 -- ��ʼ����Ϸ��2 -- ��Ϸ�����У�
int	g_Play = 0;						//����Ƿ���Play��
int	g_About = 0;					//����Ƿ���About��
int g_Back = 0;						//����Ƿ���Back��
int g_GG = 0;						//����Ƿ��ڡ�ͨ�ء���
int MapLoad = 0;					//��Ϸ�ؿ�
int	g_BLevel = 0;					//��ǰ���
int	g_SLevel = 0;					//��ǰС��
float g_GameTime = 0;				//��Ϸ����ʱ��
float g_BossAttackTime1 = 1;		//BOSS����ʱ��1
float g_BossAttackTime2 = 1;		//BOSS����ʱ��2
float g_BossAttackTime3 = 1;		//BOSS����ʱ��3
float g_BossAttackTime4 = 1;
////////////////////////////////////////////////////////////////////////////////
//�ⲿ��ȫ�ֱ���ǣ������Ϸ��BOSS�����
int	g_BOSS1_HP = 100;				//��һBOSS��HP
int	g_BOSS2_HP = 200;				//�ڶ�BOSS��HP
int g_BOSS3_HP = 300;				//����BOSS��HP
int g_BOSS4_HP = 400;				//����BOSS��HP
int g_BOSS1IsAlive = 1;				//��һBoss�Ƿ���
int g_BOSS2IsAlive = 1;				//�ڶ�Boss�Ƿ���
int g_BOSS3IsAlive = 1;				//����Boss�Ƿ���
int g_BOSS4IsAlive = 1;				//����Boss�Ƿ���
int BossIsMeX;						//BOSSX������
int BossIsMeY;						//BOSSY������
///////////////////////////////////////////////////////////////////////////////
//�ⲿ���ǳ�ʼ���������С������ĺ������塣
void		GameInit();
void		GameRun(float fDeltaTime);
void		GameEnd();
///////////////////////////////////////////////////////////////////////////////
//λ��״̬��ص�ȫ�ֱ���
float StartX = 0;							//��һ���洢������λ��X
float StartY = 0;							//��һ���洢������λ��Y
float NowX = 0;								//���ڵ�����λ��X
float NowY = 0;								//���ڵ�����λ��Y
float NowVX = 0;							//���ڵ������ٶ�X
float NowVY = 0;							//���ڵ������ٶ�Y
///////////////////////////////////////////////////////////////////////////////
//׼���¾��������
char *destWQ = dMakeSpriteName("WQ", 0);					//���ǹ���1
char *destBOSSWQ = dMakeSpriteName("BOSSWQ", 0);			//BOSS����1
char *destBLD = dMakeSpriteName("BLD", 0);					//����Ч��
char *destBOSSBLD = dMakeSpriteName("BOSSBLD", 0);			//BOSS����Ч��
char *destSSLM = dMakeSpriteName("SSLM", 0);				//�����µķɵ�
char *destZSLMTT = dMakeSpriteName("ZSLMTT", 0);			//�����µķɵ�
///////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//������
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//==============================================================================
//
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�


//==============================================================================
//
// ��Ϸ��ѭ�����˺���������ͣ�ĵ��ã�����ÿˢ��һ����Ļ���˺�����������һ��
// ���Դ�����Ϸ�Ŀ�ʼ�������С������ȸ���״̬. 
// ��������fDeltaTime : �ϴε��ñ��������˴ε��ñ�������ʱ��������λ����
void GameMainLoop( float	fDeltaTime )
{
	switch( g_iGameState )
	{
		// ��ʼ����Ϸ�������һ���������
	case 1:
		{
			GameInit();
			g_iGameState	=	2; // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
		}
		break;

		// ��Ϸ�����У����������Ϸ�߼�
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
// ÿ�ֿ�ʼǰ���г�ʼ���������һ���������
void GameInit()
{
	//������ʼ��
	g_BossAttackTime1 = 1;		//BOSS����ʱ��1
	g_BossAttackTime2 = 1;		//BOSS����ʱ��2
	g_BossAttackTime3 = 1;		//BOSS����ʱ��3
	g_BossAttackTime4 = 1;
	g_BOSS1_HP = 100;				//��һBOSS��HP
	g_BOSS2_HP = 200;				//�ڶ�BOSS��HP
	g_BOSS3_HP = 300;
	g_BOSS4_HP = 400;
	g_BOSS1IsAlive = 1;				//��һBoss�Ƿ���
	g_BOSS2IsAlive = 1;				//�ڶ�Boss�Ƿ���
	g_BOSS3IsAlive = 1;
	g_BOSS4IsAlive = 1;

	dAnimateSpritePlayAnimation("main", "xingxiong4Animation1", 0);
	MapSelection();			//��ͼѡ��
	NPC1();					//NPC��Ϊ
	StartX = dGetSpritePositionX("main");
	StartY = dGetSpritePositionY("main");

	//dSetSpriteLinearVelocityX("YCBJ", 20);
	dSetSpriteLinearVelocityPolar("SSLM", 80, 30);

}
//==============================================================================
//
// ÿ����Ϸ������
void GameRun( float fDeltaTime )
{
	GravitySimulation();	//����ģ��

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
// ����ƶ�
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void OnMouseMove( const float fMouseX, const float fMouseY )
{
	g_Play = dIsPointInSprite("Play", fMouseX, fMouseY);
	g_GG = dIsPointInSprite("GG", fMouseX, fMouseY);
	g_Back = dIsPointInSprite("BACK", fMouseX, fMouseY);
	g_About = dIsPointInSprite("About", fMouseX, fMouseY);
}
//==========================================================================
//
// �����
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
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
// ���̰���
// ���� iKey�������µļ���ֵ�� enum KeyCodes �궨��
// ���� iAltPress, iShiftPress��iCtrlPress�������ϵĹ��ܼ�Alt��Ctrl��Shift��ǰ�Ƿ�Ҳ���ڰ���״̬(0δ���£�1����)
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
// ���̵���
// ���� iKey������ļ���ֵ�� enum KeyCodes �궨��
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
// �����뾫����ײ
// ���� szSrcName��������ײ�ľ�������
// ���� szTarName������ײ�ľ�������
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
		//����BLD��destBLD
		dCloneSprite("BLD", destBLD);
		//BLD����
		dSetSpritePosition(destBLD, 26, -22);
	}

	else if (strstr(szTarName, "W") && strstr(szSrcName, destWQ))
	{
		g_BOSS2_HP -= 1;
		//����BLD��destBLD
		dCloneSprite("BLD", destBLD);
		//BLD����
		dSetSpritePosition(destBLD, 26, -22);
	}

	else if (strstr(szTarName, "FS") && strstr(szSrcName, destWQ))
	{
		g_BOSS3_HP -= 1;
		//����BLD��destBLD
		dCloneSprite("BLD", destBLD);
		//BLD����
		dSetSpritePosition(destBLD, 26, -22);
	}

	else if (strstr(szTarName, "V") && strstr(szSrcName, destWQ))
	{
		g_BOSS4_HP -= 1;
		//����BLD��destBLD
		dCloneSprite("BLD", destBLD);
		//BLD����
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
// ����������߽���ײ
// ���� szName����ײ���߽�ľ�������
// ���� iColSide����ײ���ı߽� 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
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
//�Զ��幦����
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
//
//��ͼѡ��
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
//��һ�ŵ�ͼ
void MapNext()
{
	MapLoad += 1;
	g_iGameState = 1;
}
//===========================================================================
//
//����ģ��
void GravitySimulation()
{
	if(g_BLevel == 4)
		dSetSpriteConstantForceY("main", 100);
	else
		dSetSpriteConstantForceY("main", 40);
}
//===========================================================================
//
//��������
void Dead()
{
	//����BLD��destBLD
	dCloneSprite("BLD", destBLD);
	//BLD����
	dSetSpritePosition(destBLD, NowX, NowY);
	//main�ָ��ϸ�����
	dSetSpritePosition("main", StartX, StartY);
	//ͣ��
	dSetSpriteLinearVelocityX("main", 0);
}
//===========================================================================
//
//BOSS1��Ϊ
void BOSS1()
{
	if (g_BLevel == 1 && g_SLevel == 4)
	{
		//��ȡBOSSX������
		BossIsMeX = dGetSpritePositionX("SJZ");
		BossIsMeY = dGetSpritePositionY("SJZ");

		if (g_BossAttackTime1 - g_GameTime < 0 && NowX > -38 && NowY < 12 && g_BOSS1_HP > 0)
		{
			//����WQ��destWQ
			dCloneSprite("BOSSWQ", destBOSSWQ);
			//������BOSS����
			dSetSpritePosition(destBOSSWQ, BossIsMeX, NowY);
			dSetSpriteLinearVelocityX(destBOSSWQ, -60);
			dSetSpriteAngularVelocity(destBOSSWQ, 500);
			g_BossAttackTime1 = g_GameTime + 1;
		}
		else if (g_BOSS1_HP < 0 && g_BOSS1IsAlive == 1)	//DEAD
		{
			//����BLD��destBLD
			dCloneSprite("BOSSBLD", destBOSSBLD);
			//BLD����
			dSetSpritePosition(destBOSSBLD, BossIsMeX, BossIsMeY);
			//ɾ��boss����
			dDeleteSprite("SJZ");
			g_BOSS1IsAlive = 0;
			dDeleteSprite("BK_OUT");
		}
	}
}
//===========================================================================
//
//BOSS2��Ϊ
void BOSS2()
{
	if (g_BLevel == 2 && g_SLevel == 4)
	{
		//��ȡBOSSX������
		BossIsMeX = dGetSpritePositionX("W");
		BossIsMeY = dGetSpritePositionY("W");

		if (g_BossAttackTime2 - g_GameTime < 0 && g_BOSS2_HP > 100)
		{
			//����WQ��destWQ
			dCloneSprite("BOSSWQ", destBOSSWQ);
			//������BOSS����
			dSetSpritePosition(destBOSSWQ, NowX, -32);
			dSetSpriteLinearVelocityY(destBOSSWQ, 60);
			dSetSpriteAngularVelocity(destBOSSWQ, 500);
			g_BossAttackTime2 = g_GameTime + 1;
		}
		else if (g_BossAttackTime2 - g_GameTime < 0 && g_BOSS2_HP < 100 && g_BOSS2_HP >0)
		{
			for (int i = 0; i < 20; i++)
			{
				//����WQ��destWQ
				dCloneSprite("BOSSWQ", destBOSSWQ);
				//������BOSS����
				dSetSpritePosition(destBOSSWQ, 26, -22);
				dSetSpriteLinearVelocityPolar(destBOSSWQ, 80, (18 * i));
				dSetSpriteAngularVelocity(destBOSSWQ, 500);
			}
			g_BossAttackTime2 = g_GameTime + 2;
		}
		else if (g_BOSS2_HP < 0 && g_BOSS2IsAlive == 1)	//DEAD
		{
			//����BLD��destBLD
			dCloneSprite("BOSSBLD", destBOSSBLD);
			//BLD����
			dSetSpritePosition(destBOSSBLD, 26, -22);
			//ɾ��boss����
			dDeleteSprite("W");
			g_BOSS2IsAlive = 0;
			dDeleteSprite("BK_OUT");
		}
	}
}
//===========================================================================
//
//BOSS3��Ϊ
void BOSS3()
{
	if (g_BLevel == 3 && g_SLevel == 4)
	{
		//��ȡBOSSX������
		BossIsMeX = dGetSpritePositionX("FS");
		BossIsMeY = dGetSpritePositionY("FS");

		if (g_BossAttackTime3 - g_GameTime < 0 && g_BOSS3_HP > 200)
		{
			//����WQ��destWQ
			dCloneSprite("BOSSWQ", destBOSSWQ);
			//������BOSS����
			dSetSpritePosition(destBOSSWQ, NowX, -37);
			dSetSpriteLinearVelocityY(destBOSSWQ, 60);
			dSetSpriteAngularVelocity(destBOSSWQ, 500);
			g_BossAttackTime3 = g_GameTime + 1;
		}
		else if (g_BossAttackTime3 - g_GameTime < 0 && g_BOSS3_HP < 200 && g_BOSS3_HP >100)
		{
			for (int i = 0; i < 10; i++)
			{
				//����WQ��destWQ
				dCloneSprite("BOSSWQ", destBOSSWQ);
				//������BOSS����
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
				//����WQ��destWQ
				dCloneSprite("BOSSWQ", destBOSSWQ);
				//������BOSS����
				dSetSpritePosition(destBOSSWQ, 26, -22);
				dSetSpriteLinearVelocityPolar(destBOSSWQ, 80, (9 * i));
				dSetSpriteAngularVelocity(destBOSSWQ, 500);
			}
			g_BossAttackTime3 = g_GameTime + 2;
		}
		else if (g_BOSS3_HP < 0 && g_BOSS3IsAlive == 1)	//DEAD
		{
			//����BLD��destBLD
			dCloneSprite("BOSSBLD", destBOSSBLD);
			//BLD����
			dSetSpritePosition(destBOSSBLD, 26, -22);
			//ɾ��boss����
			dDeleteSprite("FS");
			g_BOSS3IsAlive = 0;
			dDeleteSprite("BK_OUT");
		}
	}
}
//===========================================================================
//
//BOSS4��Ϊ
void BOSS4()
{
	if (g_BLevel == 4 && g_SLevel == 4)
	{
		//��ȡBOSSX������
		BossIsMeX = dGetSpritePositionX("V");
		BossIsMeY = dGetSpritePositionY("V");

		if (g_BossAttackTime4 - g_GameTime < 0 && g_BOSS4_HP > 300)
		{
			//����WQ��destWQ
			dCloneSprite("BOSSWQ", destBOSSWQ);
			//������BOSS����
			dSetSpritePosition(destBOSSWQ, NowX, -37);
			dSetSpriteLinearVelocityY(destBOSSWQ, 60);
			dSetSpriteAngularVelocity(destBOSSWQ, 500);
			g_BossAttackTime4 = g_GameTime + 1;
		}
		else if (g_BossAttackTime4 - g_GameTime < 0 && g_BOSS4_HP < 300 && g_BOSS4_HP > 200)
		{
			for (int i = 0; i < 10; i++)
			{
				//����WQ��destWQ
				dCloneSprite("BOSSWQ", destBOSSWQ);
				//������BOSS����
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
				//����WQ��destWQ
				dCloneSprite("BOSSWQ", destBOSSWQ);
				//������BOSS����
				dSetSpritePosition(destBOSSWQ, 26, -22);
				dSetSpriteLinearVelocityPolar(destBOSSWQ, 80, (36 * i));
				dSetSpriteAngularVelocity(destBOSSWQ, 500);
			}
			g_BossAttackTime4 = g_GameTime + 2;
		}
		else if (g_BossAttackTime4 - g_GameTime < 0 && g_BOSS4_HP < 100 && g_BOSS4_HP > 0)
		{
			//����WQ��destWQ
			dCloneSprite("BOSSWQ", destBOSSWQ);
			//������BOSS����
			dSetSpritePosition(destBOSSWQ, NowX, -37);
			dSetSpriteLinearVelocityY(destBOSSWQ, 60);
			dSetSpriteAngularVelocity(destBOSSWQ, 500);
			g_BossAttackTime4 = g_GameTime + 1;
			for (int i = 0; i < 10; i++)
			{
				//����WQ��destWQ
				dCloneSprite("BOSSWQ", destBOSSWQ);
				//������BOSS����
				dSetSpritePosition(destBOSSWQ, 26, -22);
				dSetSpriteLinearVelocityPolar(destBOSSWQ, 80, (36 * i));
				dSetSpriteAngularVelocity(destBOSSWQ, 500);
			}
			g_BossAttackTime4 = g_GameTime + 2;
		}
		else if (g_BOSS4_HP < 0 && g_BOSS4IsAlive == 1)	//DEAD
		{
			//����BLD��destBLD
			dCloneSprite("BOSSBLD", destBOSSBLD);
			//BLD����
			dSetSpritePosition(destBOSSBLD, 26, -22);
			//ɾ��boss����
			dDeleteSprite("V");
			g_BOSS4IsAlive = 0;
			MapLoad += 1;
			g_iGameState = 1;
		}
	}
}
//
//
//����1
void Attack1()
{
	//����WQ��destWQ
	dCloneSprite("WQ", destWQ);
	//��ȡ���ﳯ��
	int a = dGetSpriteFlipX("main");
	//������main����
	dSetSpritePosition(destWQ, NowX, NowY);
	//��֧����
	if (a == 0)
	{
		dSetSpriteLinearVelocityX(destWQ, 60);
		dSetSpriteAngularVelocity(destWQ, 500);
	}
	//��֧����
	if (a == 1)
	{
		dSetSpriteLinearVelocityX(destWQ, -60);
		dSetSpriteAngularVelocity(destWQ, 500);
	}
}
//
//
//����2
void Attack2()
{
	//����WQ��destWQ
	dCloneSprite("WQ", destWQ);
	//��ȡ���ﳯ��
	int a = dGetSpriteFlipX("main");
	//������main����
	dSetSpritePosition(destWQ, NowX, NowY);
	//��֧����
	if (a == 0)
	{
		dSetSpriteLinearVelocity(destWQ, 80, -40);
		dSetSpriteAngularVelocity(destWQ, 500);
	}
	//��֧����
	if (a == 1)
	{
		dSetSpriteLinearVelocity(destWQ, -80, -40);
		dSetSpriteAngularVelocity(destWQ, 500);
	}
}
//
//
//����3
void Attack3()
{
	//����WQ��destWQ
	dCloneSprite("WQ", destWQ);
	//��ȡ���ﳯ��
	int a = dGetSpriteFlipX("main");
	//������main����
	dSetSpritePosition(destWQ, NowX, NowY);
	//��֧����
	if (a == 0)
	{
		dSetSpriteLinearVelocity(destWQ, 80, 40);
		dSetSpriteAngularVelocity(destWQ, 500);
	}
	//��֧����
	if (a == 1)
	{
		dSetSpriteLinearVelocity(destWQ, -80, 40);
		dSetSpriteAngularVelocity(destWQ, 500);
	}
}
//
//
//����4
void Attack4()
{
	for (int i = 0; i < 20; i++)
	{
		//����WQ��destWQ
		dCloneSprite("WQ", destWQ);
		//��ȡ���ﳯ��
		int a = dGetSpriteFlipX("main");
		//��ȡmain������
		const float mainX = dGetSpritePositionX("main");
		const float mainY = dGetSpritePositionY("main");
		//������main����
		dSetSpritePosition(destWQ, mainX, mainY);
		dSetSpriteLinearVelocityPolar(destWQ, 80, (18 * i));
		dSetSpriteAngularVelocity(destWQ, 500);
	}
}
//
//
//����С����켣
void NPC1()
{
	//��һ��
	///����С��
	dSetSpriteLinearVelocityY("TSLM1", 40);
	dSetSpriteLinearVelocityY("TSLM2", 80);
	dSetSpriteLinearVelocityY("TSLM3", 80);

	//�ڶ���
	///��һС��
	dSetSpriteLinearVelocityY("SLM1", 40);
	dSetSpriteLinearVelocityY("SLM2", 80);
	dSetSpriteLinearVelocityX("SLM3", 80);
	///�ڶ�С��
	dSetSpriteLinearVelocityY("SLM4", 80);
	///����С��
	dSetSpriteLinearVelocityY("BK_1", -10);
	dSetSpriteLinearVelocityY("BK_2", -11);
	dSetSpriteLinearVelocityX("BK_3", -12);
	dSetSpriteLinearVelocityY("BK_4", -13);
	
	//������
	///�ڶ�С��
	dSetSpriteLinearVelocityY("MU_01", -10);
	dSetSpriteLinearVelocityY("MU_02", 20);
	///����С��
	dSetSpriteLinearVelocity("TTTSLM01", -10, 22);
	dSetSpriteLinearVelocity("TTTSLM02", 22, 10);
	dSetSpriteLinearVelocity("TTTSLM03", 19, 15);

	//���Ĺ�
	///��һС��
	for (int i = 0; i < 30; i++)
	{
		dCloneSprite("SSLM", destSSLM);
		dSetSpritePosition(destSSLM, -1, -7);
		dSetSpriteLinearVelocityPolar(destSSLM, 80, ((10 * i)+30));
	}
	///�ڶ�С��
	for (int i = 0; i < 35; i++)
	{
		dCloneSprite("ZSLMTT", destZSLMTT);
		dSetSpritePosition(destZSLMTT, -1, -7);
		dSetSpriteLinearVelocityPolar(destZSLMTT, 80, ((10 * i) + 30));
	}
}