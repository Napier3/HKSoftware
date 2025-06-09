#pragma once

#include "GuideBookDefine.h"
#include "../CriticalSection/SynCriticalSection.h"
#include "GbItemBase.h"
#include "Device.h"
#include "../API/StringApi.h"
#include "ScriptText.h"

#include "../GpsPcTime/GpsPcTime.h"
#include "../../../Module/DataMngr/DatasetValid/DsvSequence.h"

class _CGbScriptGlobalDefine
{
public:
	_CGbScriptGlobalDefine()
	{
		m_pScriptText = NULL;
		*m_pszSysToLuaBuffer = 0;

		m_pCurrSelectGbItem = NULL;   //当前选中的项目
		m_pCurrSelectReport = NULL;   //当前选中的项目的报告对象
	}

	virtual ~_CGbScriptGlobalDefine()
	{
		m_oListRptExFilter.RemoveAll();

		m_oListLogs.RemoveAll();
		m_oListLogDatas.RemoveAll();
	}

	static long g_nGbScriptGlobalDefineRef;
	static _CGbScriptGlobalDefine *g_pGbScriptGlobalDefine;

	static _CGbScriptGlobalDefine* Create()
	{
		g_nGbScriptGlobalDefineRef++;

		if (g_nGbScriptGlobalDefineRef == 1)
		{
			g_pGbScriptGlobalDefine = new _CGbScriptGlobalDefine();
		}

		return g_pGbScriptGlobalDefine;
	}

	static void Release()
	{
		g_nGbScriptGlobalDefineRef--;

		if (g_nGbScriptGlobalDefineRef == 0)
		{
			delete g_pGbScriptGlobalDefine;
			g_pGbScriptGlobalDefine = NULL;
		}
	}

public:
	CAutoCriticSection m_oAutoCriticSection;	//脚本执行的互斥量
	char m_pszSysToLuaBuffer[2048];			//系统程序与LUA进行字符串数据交互的全局缓冲区

	CScriptText *m_pScriptText;					//当前执行的脚本
	CDevice      *m_pDevice;						//脚本所属的设备，如果脚本的祖先对象为JobGuide，则m_pDevice==NULL
	void SetScriptText(CScriptText *pScript);
	long SelectGbItems(const char* pszPath, CGbItemBaseList &oListDest);
	CExBaseObject* SelectGbItem();
	CExBaseObject* SelectGbItem_CommCmd();



public:
	CExBaseObject *m_pCurrSelectGbItem;   //当前选中的项目
	CExBaseObject *m_pCurrSelectReport;   //当前选中的项目的报告对象

	CExBaseObject* SelectGbItem(const char* pszPath);
	CExBaseObject* SelectGbItemReport(long nReportIndex);

	CDvmDataset m_oListRptExFilter;

	CExBaseList m_oListLogs;
	CExBaseList m_oListLogDatas;

protected:
	CDsvSequence m_oDsvSequence;


public:
	static CDsvSequence* GetDsvSequence()	{	return &(g_pGbScriptGlobalDefine->m_oDsvSequence);	}

};

void GBS_LogTime_PcTime(PPCTIME pTm);
void GBS_LogTime_GpsTime(PGPSTIME pTm);