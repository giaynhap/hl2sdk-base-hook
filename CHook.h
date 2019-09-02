#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <future>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <sys\stat.h>
#include <string>
 

class CHook
{
private:
	CHook(const CHook&) = delete;
	CHook& operator=(const CHook&) = delete;

public:
	CHook(void* pInstance);
	~CHook(void);

	void HookMethod(void* pHooked, size_t nIndex);

	void Unhook();
	void Rehook();

	template<typename T>
	T GetMethod(size_t nIndex)
	{
		return (T)m_pBackVmt[nIndex];
	}

private:
	uintptr_t**	m_pInstance;
	uintptr_t*	m_pCustomVmt;
	uintptr_t*	m_pBackVmt;
	size_t		m_nSize;
};