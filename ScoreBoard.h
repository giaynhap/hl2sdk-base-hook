#pragma once
#ifndef INC_SCOREBOARD
#define INC_SCOREBOARD 1
#include "stdafx.h"

class ScoreBoard
{
public:
	ScoreBoard();
	~ScoreBoard();
	void Render();
	void Prepare();
 
private:
	bool isPrepare = false;
	image_t idImgBoard_BL;
	image_t idImgBoard_GR ;
	int srcWidth, srcHeight;

};

extern ScoreBoard* g_ScoreBoard;
#endif // !INC_SCOREBOARD