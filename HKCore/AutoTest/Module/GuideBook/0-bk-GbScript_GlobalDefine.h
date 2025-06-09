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

		m_pCurrSelectGbItem = NULL;   //��ǰѡ�е���Ŀ
		m_pCurrSelectReport = NULL;   //��ǰѡ�е���Ŀ�ı������
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
	CAutoCriticSection m_oAutoCriticSection;	//�ű�ִ�еĻ�����
	char m_pszSysToLuaBuffer[2048];			//ϵͳ������LUA�����ַ������ݽ�����ȫ�ֻ�����

	CScriptText *m_pScriptText;					//��ǰִ�еĽű�
	CDevice      *m_pDevice;						//�ű��������豸������ű������ȶ���ΪJobGuide����m_pDevice==NULL
	void SetScriptText(CScriptText *pScript);
	long SelectGbItems(const char* pszPath, CGbItemBaseList &oListDest);
	CExBaseObject* SelectGbItem();
	CExBaseObject* SelectGbItem_CommCmd();



public:
	CExBaseObject *m_pCurrSelectGbItem;   //��ǰѡ�е���Ŀ
	CExBaseObject *m_pCurrSelectReport;   //��ǰѡ�е���Ŀ�ı������

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