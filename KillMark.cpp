#include "KillMark.h"

#define killTime 5000.0
#define showTime  2000.0
KillMark::KillMark()
{
	prepare();
}


KillMark::~KillMark()
{
	 
}

void KillMark::prepare()
{
	Graphic::createImage("hud/killmark/badge_multi1", killMarks[0]);
	Graphic::createImage("hud/killmark/badge_multi2", killMarks[1]);
	Graphic::createImage("hud/killmark/badge_multi3", killMarks[2]);
	Graphic::createImage("hud/killmark/badge_multi4", killMarks[3]);
	Graphic::createImage("hud/killmark/badge_multi5", killMarks[4]);
	Graphic::createImage("hud/killmark/badge_multi6", killMarks[5]);
	Graphic::createImage("hud/killmark/FIRSTKILL", killMarks[6]);
	Graphic::createImage("hud/killmark/badge_headshot", killMarks[7]);
 
}
void KillMark::Render()
{
	if (!GEngine->IsInGame() && !GEngine->IsConnected()) return;
	if (!isShow) return;
	float currenTime = GEngine->Time() * 1000;
	static float scale = 0.0;
	static int move = 0;
	float delTatime = fabs(currenTime - m_startTime);
	if (delTatime< showTime) {
		if (delTatime < 50)
		{
			scale = 0;
			move = 0;
		}
		int alpha = 255;
		 
		if (move == 0 && scale <= 1.3) {
			scale = delTatime / (showTime - 1800)*delTatime / (showTime - 1800);

			if (scale >= 1.3) { 

				move =1;
			};
		}
		else {
			scale -= 0.5*delTatime / 3000;
			if (scale < 1) scale = 1;
		}

		if (delTatime > showTime - 300)
		{
			alpha = (int)(((showTime - delTatime) / 300.0)*255.0);
		}
		Graphic::drawImage(0, 150, killMarks[killIndexImg], SCR_H_CENTER | SCR_V_RIGHT | IMG_H_CENTER|IMG_V_CENTER  , scale, alpha);
		if (killIndexImg < 6)
		{
		//	Graphic::drawImage(0, 150, killEffect[killIndexImg], SCR_H_CENTER | SCR_V_RIGHT | IMG_H_CENTER | IMG_V_CENTER, scale, alpha);

		}
	}
	else {
		
		isShow = false;
	}
}
void KillMark::startKillmark(bool isHeadShot, int weaponType, bool revengeKill) {
	 
	  killIndexImg = 0;
	  float currenTime = GEngine->Time() * 1000;

	  if (fabs(m_startTime - currenTime) > killTime)
	  {
		  scoreKill = 1;
	  }
	  else {
		  scoreKill++;
		  if (scoreKill > 6) {
			  scoreKill = 6;
		  }
	  }

	  if (!isHeadShot)
	  {
		  killIndexImg = scoreKill-1;
	  }
	  else {
		  killIndexImg = 7;
	  }
	  if (g_Manager->teamscore.ct == 0 && g_Manager->teamscore.ter == 0)
	  {
		  killIndexImg = 6;
	  }
	  isShow = true;
	  m_startTime = GEngine->Time() * 1000;
	  char time[32];
	  sprintf(time,"start-current %f", m_startTime);
	  LogWriter(time);
}

void KillMark::revFromDeathMessage(int uid, bool isHeadShot, int weaponType, bool revengeKill) {
	if (uid == GEngine->GetLocalPlayer())
	{
		startKillmark(isHeadShot, weaponType, revengeKill);
	}
}
