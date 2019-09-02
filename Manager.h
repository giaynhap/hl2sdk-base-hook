#pragma once
#ifndef INC_MANAGER
#define INC_MANAGER 1

#include "stdafx.h"

class Manager
{
public:
	Manager();
	~Manager();
public :
	gn_player_info_t playinfo[33];
	team_score_t teamscore;
};
extern Manager* g_Manager;
#endif // !INC_MANAGER