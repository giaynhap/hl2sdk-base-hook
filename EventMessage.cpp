#include "stdafx.h"
Manager * g_Manager;
bool HookEventMessage(IGameEvent * event)
{
	const char *eventName = event->GetName();
 
	if (strcmpi(eventName, "player_team") == 0)
	{
 
		int userid = event->GetInt("userid");
		int id = GEngine->GetPlayerForUserID(userid);

		int team = event->GetInt("team");
		if (id >= 0 && id <= 32) {
			g_Manager->playinfo[id].team = team;
		}

	}
	else if(strcmpi(eventName, "player_class") == 0) {
		char modelname[64];
		int userid = event->GetInt("userid");
		int id = GEngine->GetPlayerForUserID(userid);
		event->GetString("class", modelname);
		if (id <= 0 && id > 32)  goto end;
		strcpy(g_Manager->playinfo[id].modelname, modelname);
	}
	else if (strcmpi(eventName, "player_info") == 0) {
		char name[512];
		int userid = event->GetInt("userid");
		int id = GEngine->GetPlayerForUserID(userid);
		bool isBot = event->GetBool("bot");
		event->GetString("name", name);
		if (id <= 0 && id > 32)  goto end;
		strcpy(g_Manager->playinfo[id].name, name);
		g_Manager->playinfo[id].isbot = isBot;

	}
	else if (strcmpi(eventName, "player_connect_client") == 0) {
		char name[512];
		int userid = event->GetInt("userid");
		int id = GEngine->GetPlayerForUserID(userid);
		event->GetString("name", name);
		if (id <= 0 && id > 32)  goto end;
		strcpy(g_Manager->playinfo[id].name, name);
	}
	else if (strcmpi(eventName, "player_spawn") == 0) {
		int userid = event->GetInt("userid");
		int id = GEngine->GetPlayerForUserID(userid);
		g_Manager->playinfo[id].health = 100;
		g_Manager->playinfo[id].alive = true;
	}
	else if (strcmpi(eventName, "player_hurt") == 0) {
		int userid = event->GetInt("userid");
		int id = GEngine->GetPlayerForUserID(userid);
		int health = event->GetInt("health");
		int armor = event->GetInt("armor");
		g_Manager->playinfo[id].health = health;
		g_Manager->playinfo[id].armor = armor;
	}
	else if (strcmpi(eventName, "player_death") == 0) {
		char weapon[64];
		int userid = event->GetInt("userid");
		int id = GEngine->GetPlayerForUserID(userid);
		int attacker = event->GetInt("attacker");
		int attacker_id = GEngine->GetPlayerForUserID(attacker);
		 event->GetString("weapon", weapon);
		int headshot = event->GetInt("headshot");
		int dominated = event->GetInt("dominated");
		int revenge = event->GetInt("revenge");
		g_Manager->playinfo[id].alive = false;
		char info[128];
		sprintf(info, "userid %d - attacker %d - headshot %d", id, attacker_id, headshot);
		LogWriter(info);
		g_Killmark->revFromDeathMessage(attacker_id, headshot, 0, revenge == 1);
	}
	else if (strcmpi(eventName, "bomb_beginplant") == 0) {
		int userid = event->GetInt("userid");
		int id = GEngine->GetPlayerForUserID(userid);
		int site = event->GetInt("site");
	}
	
	end:
	return true;
}

bool HookEventMessage_2(IGameEvent * event)
{
	const char *eventName = event->GetName();


	LogWriter(eventName);
	    if (strcmpi(eventName, "set_team_score") == 0) {

		  int ctScore = event->GetInt("ctscore");
		  int terScore = event->GetInt("terscore");
		  int total = event->GetInt("totalscore");
		  g_Manager->teamscore.ct = ctScore;
		  g_Manager->teamscore.ter = terScore;
		  g_Manager->teamscore.score = total;

	  }
	  else if (strcmpi(eventName, "set_weapon") == 0) {
		  char weapon[64];
		  int userid = event->GetInt("userid");
		  event->GetString("weapon", weapon);
		  int clip = event->GetInt("clip");
		  int ammo = event->GetInt("ammo");
		  char info[128];
		  sprintf(info, "userid %d - weapon %s - clip %d - ammo %d", userid, weapon, clip, ammo);
		  LogWriter(info);
	  }
	  else  if (strcmpi(eventName, "test") == 0) {

		  g_Killmark->startKillmark(false, 0, false);
	  }
end:
	return true;
}