#ifndef __VAR_HEADER__
#define __VAR_HEADER__
#include "stdafx.h"
namespace NNetworkedVariables
{
	namespace DT_BasePlayer
	{
		extern netvar_prop_t*		m_lifeState;
		extern netvar_prop_t*		m_iHealth;
		extern netvar_prop_t*		m_fFlags;
	};

	namespace DT_BaseEntity
	{
		extern netvar_prop_t*		m_iTeamNum;
		extern netvar_prop_t*		m_nModelIndex;
	};

	namespace DT_BaseCombatWeapon
	{
		extern netvar_prop_t*		m_iState;
	};

	namespace DT_BaseCSGrenade
	{
		extern netvar_prop_t*		m_bPinPulled;
		extern netvar_prop_t*		m_fThrowTime;
	};

	namespace DT_BaseCombatCharacter
	{
		extern netvar_prop_t*		m_hActiveWeapon;
	};

	namespace DT_BaseGrenade
	{
		extern netvar_prop_t*		m_DmgRadius;
	};
};

#define NETWORKED_VARIABLE_MACRO( C, V ) NNetworkedVariables::C::V = GNetworkedVariables.GetPropFromTable( #C, #V );

bool Var_Initialize(void);
bool Var_DynamicReady();
bool StoreDynamicVariables(void);

#endif