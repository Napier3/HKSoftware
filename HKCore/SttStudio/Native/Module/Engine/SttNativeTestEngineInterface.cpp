#include "stdafx.h"
#include "SttNativeTestEngineInterface.h"
#include "../SttCmd/GuideBook/SttCmdGuideBookTransTool.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CSttNativeTestEngineInterface
CSttNativeTestEngineInterface::CSttNativeTestEngineInterface()
{
	
}

CSttNativeTestEngineInterface::~CSttNativeTestEngineInterface()
{
	
}


//////////////////////////////////////////////////////////////////////////
//CSttNativeTestEngineInterfaces
CSttNativeTestEngineInterfaces *g_theNativeTestEngine = NULL;
long CSttNativeTestEngineInterfaces::g_nSttNativeTestEngineInterfaces = 0;
CSttNativeTestEngineInterfaces* CSttNativeTestEngineInterfaces::g_pNativeTestEngineInterfaces = 0;

CSttNativeTestEngineInterfaces::CSttNativeTestEngineInterfaces()
{
	g_theNativeTestEngine = this;
}

CSttNativeTestEngineInterfaces::~CSttNativeTestEngineInterfaces()
{
	RemoveAll();
}


void CSttNativeTestEngineInterfaces::Create()
{
	g_nSttNativeTestEngineInterfaces++;

	if (g_nSttNativeTestEngineInterfaces == 1)
	{
		g_pNativeTestEngineInterfaces = new CSttNativeTestEngineInterfaces();
	}
}

void CSttNativeTestEngineInterfaces::Release()
{
	g_nSttNativeTestEngineInterfaces--;

	if (g_nSttNativeTestEngineInterfaces == 0)
	{
		delete g_pNativeTestEngineInterfaces;
		g_pNativeTestEngineInterfaces = NULL;
	}
}

//CSttNativeTestEngineInterface
long CSttNativeTestEngineInterfaces::X_ReturnSysStateToChildren(void *pCommInterface, CSttSysState *pSysState)
{
	CSttNativeTestEngineInterface *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->X_ReturnSysStateToChildren(pCommInterface, pSysState);
	}

	return 0;
}

long CSttNativeTestEngineInterfaces::X_Ats_InputData(void *pCommInterface, CDataGroup *pDatas,CExBaseList *pMsgs)
{
	CSttNativeTestEngineInterface *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->X_Ats_InputData(pCommInterface, pDatas, pMsgs);
	}

	return 0;
}

void CSttNativeTestEngineInterfaces::DispatchMsg(unsigned char *pBuf, long nLen)
{
	CSttNativeTestEngineInterface *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->DispatchMsg(pBuf, nLen);
	}
}

void CSttNativeTestEngineInterfaces::OnCommCmdMessage(WPARAM wParam, LPARAM lParam)
{

}

void CSttNativeTestEngineInterfaces::OnSysMessage(WPARAM wParam, LPARAM lParam)
{

}

void CSttNativeTestEngineInterfaces::Return_Ats_Success(CSttAtsCmd *pAtsCmd, unsigned int nState, CDvmDataset *pDatas, CExBaseObject *pGuideBook)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(pAtsCmd);
	oSysState.Set_ExecStatus(nState);
	CSttParas *pParas = NULL;
	pParas = oSysState.GetSttParas();

	//2020-11-30   lijunqing
	if (pDatas != NULL)
	{
		pParas->AppendClone(*pDatas);
	}

#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
	//2020-12-01  lijunqing
	if (pGuideBook != NULL)
	{
		CSttGuideBook *pSttGuideBook = pParas->NewGuideBook();
		CSttCmdGuideBookTransTool oTool;
		oTool.Trans((CGuideBook*)pGuideBook, pSttGuideBook);
	}
#endif

	X_ReturnSysStateToChildren(NULL, &oSysState);

}

void CSttNativeTestEngineInterfaces::OnTimer()
{
	CSttNativeTestEngineInterface *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->OnTimer();
	}
}