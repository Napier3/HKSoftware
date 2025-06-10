#include "stdafx.h"
#include "PpsttEngineCreator.h"
#ifndef NOT_USE_PPSTTENGINE
#include"PpEngine_Stt.h"
#endif
#include "PpSttIotEngine.h"
#include "PpMqttIotEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern BOOL g_bShowTestWndTop;
//////////////////////////////////////////////////////////////////////////
//CPpsttEngineCreator
CPpsttEngineCreator::CPpsttEngineCreator()
{
	
}

CPpsttEngineCreator::~CPpsttEngineCreator()
{
	
}

//2023-8-19  lijunqing ���ݸ���ͨ��ģʽ
CProtocolEngineInterface* CPpsttEngineCreator::NewProtocolEngine(const CString &strEngineMode, const CString &strPpEngineProgID)
{
	if (strEngineMode == STT_CMD_PARA_EngineMode_STT || strPpEngineProgID == STT_CMD_PARA_EngineMode_STT)
	{
		return new CPpSttIotEngine;
	}

	if (strEngineMode == STT_CMD_PARA_EngineMode_MQTT || strPpEngineProgID == STT_CMD_PARA_EngineMode_MQTT)
	{
		return new CPpMqttIotEngine;
	}

	//��ʽ1������ _T("PpEngine");
	if (strPpEngineProgID == g_strSttEngine_PXI)   //_T("PpEngine");
		{
#ifndef NOT_USE_PPSTTENGINE
		return new CPpsttEngine;
#else
		return new CPpSttIotEngine;;  //Ĭ��ΪSTTģʽ
#endif
		}

	//��ʽ2������   // _T("PpSttIotEngine");
	if(strPpEngineProgID == g_strSttEngine_IOT)
		{
		return new CPpSttIotEngine;
		}

	//��ʽ3������   //_T("PpSttMqttEngine");
	if(strPpEngineProgID == g_strSttEngine_IOT)
		{
		return new CPpMqttIotEngine;
		}

	//��ʽ4���������STT.
	if (strPpEngineProgID.Left(4) == _T("STT."))
	{
		return new CPpSttIotEngine;
	}

	//��ʽ6���������MQTT.
	if (strPpEngineProgID.Left(5) == _T("MQTT."))
	{
		return new CPpMqttIotEngine;
	}

	//��ʽ7��Ĭ��ΪSTTģʽ
	return new CPpSttIotEngine;
}

CProtocolEngineInterface* CPpsttEngineCreator::GetProtocolEngine(const CString &strEngineMode, const CString &strPpEngineProgID)
{
	CProtocolEngineInterface *pEngine = (CProtocolEngineInterface *)FindByID(strPpEngineProgID);

	if (pEngine != NULL)
	{
		return pEngine;
	}

	pEngine = NewProtocolEngine(strEngineMode, strPpEngineProgID);

	if (strPpEngineProgID.GetLength() > 0)
	{
		pEngine->m_strID = strPpEngineProgID;
	}
	else
	{
		pEngine->m_strID = g_strSttEngine_IOT;
	}

		AddNewChild(pEngine);

	return pEngine;
}

void CPpsttEngineCreator::ReleasePpEngine(const CString &strProgID)
{
	CProtocolEngineInterface *pEngine = (CProtocolEngineInterface *)FindByID(strProgID);

	if (pEngine != NULL)
	{
		pEngine->ReleaseAllDevice();
		//�����ӶϿ����ӵȣ�
		Delete(pEngine);
	}
}

void CPpsttEngineCreator::ReleasePpEngine()
{
	POS pos = GetHeadPosition();
	CProtocolEngineInterface *pEngine = NULL;

	while (pos != NULL)
	{
		pEngine = (CProtocolEngineInterface *)GetNext(pos);
		pEngine->ReleaseAllDevice();
		//�����ӶϿ����ӵȣ�
	}

	DeleteAll();
}


void CPpsttEngineCreator::StopProtocolParseForReadSoe(BOOL bStop)
{
	CProtocolEngineInterface *pEngine = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pEngine = (CProtocolEngineInterface *)GetNext(pos);
		pEngine->SetProtocolParse(bStop);
	}
}

BOOL CPpsttEngineCreator::HasPpEngine()
{
	return GetCount() > 0;
}

void CPpsttEngineCreator::InitPpEngineShowSpyWnd()
{
	CProtocolEngineInterface *pEngine = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pEngine = (CProtocolEngineInterface *)GetNext(pos);
		pEngine->ShowSpyWnd(g_bShowTestWndTop);
	}
}

 long CPpsttEngineCreator::ConfigEngine()
 {
    return 0;
 }


