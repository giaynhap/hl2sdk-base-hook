#include "stdafx.h"
Manager * g_Manager;
netvar_prop_t* NNetworkedVariables::DT_BasePlayer::m_lifeState = 0;
netvar_prop_t* NNetworkedVariables::DT_BasePlayer::m_iHealth = 0;
netvar_prop_t* NNetworkedVariables::DT_BasePlayer::m_fFlags = 0;
netvar_prop_t* NNetworkedVariables::DT_BaseEntity::m_iTeamNum = 0;
netvar_prop_t* NNetworkedVariables::DT_BaseEntity::m_nModelIndex = 0;
netvar_prop_t* NNetworkedVariables::DT_BaseCombatWeapon::m_iState = 0;
netvar_prop_t* NNetworkedVariables::DT_BaseCSGrenade::m_bPinPulled = 0;
netvar_prop_t* NNetworkedVariables::DT_BaseCSGrenade::m_fThrowTime = 0;
netvar_prop_t* NNetworkedVariables::DT_BaseCombatCharacter::m_hActiveWeapon = 0;
netvar_prop_t* NNetworkedVariables::DT_BaseGrenade::m_DmgRadius = 0;

bool Var_Initialize(void)
{
	return g_Manager->StoreNetworkedVariableInfo(GClient);
}

bool Var_DynamicReady()
{
	return (NNetworkedVariables::DT_BasePlayer::m_lifeState == NULL) == false;
}

bool StoreDynamicVariables(void)
{
	
	if (g_Manager->IsReady() == false)
	{
		return false;
	}

	NNetworkedVariables::DT_BasePlayer::m_lifeState =g_Manager->GetPropFromTable("DT_BasePlayer", "m_lifeState");
	NNetworkedVariables::DT_BasePlayer::m_iHealth =g_Manager->GetPropFromTable("DT_BasePlayer", "m_iHealth");
	NNetworkedVariables::DT_BasePlayer::m_fFlags =g_Manager->GetPropFromTable("DT_BasePlayer", "m_fFlags");

	NNetworkedVariables::DT_BaseEntity::m_iTeamNum =g_Manager->GetPropFromTable("DT_BaseEntity", "m_iTeamNum");
	NNetworkedVariables::DT_BaseEntity::m_nModelIndex =g_Manager->GetPropFromTable("DT_BaseEntity", "m_nModelIndex");

	NNetworkedVariables::DT_BaseCombatWeapon::m_iState =g_Manager->GetPropFromTable("DT_BaseCombatWeapon", "m_iState");

	NNetworkedVariables::DT_BaseCSGrenade::m_bPinPulled =g_Manager->GetPropFromTable("DT_BaseCSGrenade", "m_bPinPulled");
	NNetworkedVariables::DT_BaseCSGrenade::m_fThrowTime =g_Manager->GetPropFromTable("DT_BaseCSGrenade", "m_fThrowTime");

	NNetworkedVariables::DT_BaseGrenade::m_DmgRadius =g_Manager->GetPropFromTable("DT_BaseGrenade", "m_DmgRadius");

	NNetworkedVariables::DT_BaseCombatCharacter::m_hActiveWeapon =g_Manager->GetPropFromTable("DT_BaseCombatCharacter", "m_hActiveWeapon");

	return Var_DynamicReady();
}