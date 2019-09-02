#include "ScoreBoard.h"

bool getClass = false;
ScoreBoard::ScoreBoard()
{
	this->Prepare();
}
void ScoreBoard::Render(){
	
 if (!GEngine->IsInGame()&& !GEngine->IsConnected()) return;
 if (g_Manager->teamscore.score < 0) return;
	int localId = GEngine->GetLocalPlayer();
	
	int total = g_Manager->teamscore.score;
	int left = g_Manager->teamscore.ter;
	int right = g_Manager->teamscore.ct;
	player_info_t player;
	if (g_Manager->playinfo[localId].team == 3) {
		Graphic::drawImage(0, 5, idImgBoard_GR, SCR_H_CENTER | IMG_H_CENTER);
		  left = g_Manager->teamscore.ct;
		  right = g_Manager->teamscore.ter;
	}
	else
	{ 
		Graphic::drawImage(0, 5, idImgBoard_BL, SCR_H_CENTER | IMG_H_CENTER);
	}
	
	
	  
	
	 Graphic::drawNumber(scr_Size[0]/2, 10, total, IMG_H_CENTER);
	 Graphic::drawNumber(scr_Size[0]/2 - 25, 10 , left, IMG_H_RIGHT);
	 Graphic::drawNumber(scr_Size[0]/2 + 30, 10,right, IMG_H_LEFT);
	// GetBasePlayerHealth(GEntList->GetClientEntity(GEngine->GetLocalPlayer())->GetBaseEntity());
	/* char info[64];
	 sprintf(info, "TeamInfo: %d", localId);
	 LogWriter(info);
	 */
}


void ScoreBoard::Prepare() {
	if (this->isPrepare) return;
	this->isPrepare = true;

	// get screen size
//	GSurface->GetScreenSize(srcWidth, srcHeight);

	// prepare image
 	Graphic::createImage("hud/BLScore", idImgBoard_BL);
 	Graphic::createImage("hud/GRScore", idImgBoard_GR);
 //	CFont * g_pMyFont = CFont::CreateFont("Impact", 14, 300, kFontFlag_DROPSHADOW);

	

	//("Prepare scoreboard");
	// char info[128];
	 // sprintf(info, "w:%d, h:%d - [%d]", idImgBoard_BL.width, idImgBoard_BL.height, idImgBoard_BL.id);
	 // LogWriter(info);
}
 
ScoreBoard::~ScoreBoard()
{
	
	
}
