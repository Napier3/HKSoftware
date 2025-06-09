//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MacroScriptMngrGlobal.cpp

#include "stdafx.h"
#include "MacroScriptMngrGlobal.h"
#include "TestMacroScript.h"

#include "../../Module/TestMacro/TestMacroInterface.h"
#include "../../Module/DataMngr/ShortData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CMacroScriptMngrXmlRWKeys

CMacroScriptMngrXmlRWKeys* CMacroScriptMngrXmlRWKeys::g_pXmlKeys = NULL;
long CMacroScriptMngrXmlRWKeys::g_nTMSRef = 0;


CMacroScriptMngrXmlRWKeys::CMacroScriptMngrXmlRWKeys()
{
	m_strCGbUIMacroKey = L"macro";
	m_strCGbUIMacroConfigKey = L"gbui-macro-config";
	m_strCTmScptGroupCmdKey = L"gcmd";
	m_strCTestMacroScriptMngrKey = L"macro-scripts";
	m_strCTestMacroScriptKey = L"macro-script";
	m_strCTmScptDataKey = L"data";
	m_strCTmScptValueKey = L"value";
	m_strCTmScptCmdKey = L"cmd";
	m_strDataIDKey = L"data-id";
	m_strAttrIDKey = L"attr-id";
	m_strValueKey = L"value";
	m_strMacroIDKey = L"macro-id";
	m_strGroupIDKey = L"group-id";
	m_strDLLKey = L"dll";
}

CMacroScriptMngrXmlRWKeys::~CMacroScriptMngrXmlRWKeys()
{
}

CMacroScriptMngrXmlRWKeys* CMacroScriptMngrXmlRWKeys::Create()
{
	g_nTMSRef++;

	if (g_nTMSRef == 1)
	{
		g_pXmlKeys = new CMacroScriptMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CMacroScriptMngrXmlRWKeys::Release()
{
	g_nTMSRef--;

	if (g_nTMSRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CMacroScriptMngrConstGlobal

long CMacroScriptMngrConstGlobal::g_nGlobalRef = 0;
CMacroScriptMngrConstGlobal* CMacroScriptMngrConstGlobal::g_pGlobal = NULL;


CMacroScriptMngrConstGlobal::CMacroScriptMngrConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CMacroScriptMngrConstGlobal::~CMacroScriptMngrConstGlobal()
{
}

CMacroScriptMngrConstGlobal* CMacroScriptMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CMacroScriptMngrConstGlobal();
	}

	return g_pGlobal;
}

void CMacroScriptMngrConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//定义全局常量，例如  static CString g_pstrVariableType_CString;


#define TMS_DATA_ENABLE   0X000000001
#define TMS_DATA_SHOW    0X000000002

BOOL TMS_IsDataEnable(CShortData *pData)
{
	return ((pData->m_nReserved & TMS_DATA_ENABLE) == TMS_DATA_ENABLE);
}

void TMS_SetDataEnable(CShortData *pData, BOOL bEnable)
{
	if (bEnable)
	{
		pData->m_nReserved |= TMS_DATA_ENABLE;
	}
	else
	{
		pData->m_nReserved &= (~TMS_DATA_ENABLE);
	}
}

BOOL TMS_IsDataShow(CShortData *pData)
{
	return ((pData->m_nReserved & TMS_DATA_SHOW) == TMS_DATA_SHOW);
}

void TMS_SetDataShow(CShortData *pData, BOOL bShow)
{
	if (bShow)
	{
		pData->m_nReserved |= TMS_DATA_SHOW;
	}
	else
	{
		pData->m_nReserved &= (~TMS_DATA_SHOW);
	}
}

long TMS_SetDataAttr(CShortData *pData, const CString &strAttrID, const CString &strValue)
{
	if (strAttrID == g_strDataAttrID_Show)
	{
		TMS_SetDataShow(pData, CString_To_long(strValue));
	}
	else if (strAttrID == g_strDataAttrID_Enable)
	{
		TMS_SetDataEnable(pData, CString_To_long(strValue));
	}
	else if (strAttrID ==g_strDataAttrID_Unit)
	{
		pData->m_strUnit = strValue;
	}
	else if (strAttrID == g_strDataAttrID_DataType)
	{
		pData->m_strDataTypeID = strValue;
	}
	else if (strAttrID == g_strDataAttrID_Name)
	{
		pData->m_strName = strValue;
	}
	else if (strAttrID == g_strDataAttrID_Value)
	{
		pData->m_strValue = strValue;
	}
	else
	{
		return 0;
	}

	return 1;
}


long TMS_SetDatasAttr(CExBaseList *pDatas, const CString &strAttrID, const CString &strValue)
{
	POS pos = pDatas->GetHeadPosition();
	CShortData *pData = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		pData = (CShortData *)pDatas->GetNext(pos);
		nCount += TMS_SetDataAttr(pData, strAttrID, strValue);
	}

	return nCount;
}


long TMS_GetDatasByGroupID(CExBaseList *pDatas, const CString &strGroupID, CExBaseList *pList)
{
	POS pos = pDatas->GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CShortData *)pDatas->GetNext(pos);

		if (pData->m_strRemark == strGroupID)
		{
			pList->AddTail(pData);
		}
	}

	return pList->GetCount();
}

long TMS_GetDatasByGroupID(CTestMacro *pMacro, const CString &strGroupID, CExBaseList *pList)
{
	TMS_GetDatasByGroupID(pMacro->GetFaultParas(), strGroupID, pList);
	TMS_GetDatasByGroupID(pMacro->GetSysParas(), strGroupID, pList);

	return pList->GetCount();
}

long TMS_SetDataAttrByGroupID(CTestMacro *pMacro, const CString &strDataID, const CString &strAttrID, const CString &strValue)
{
	CShortData *pData = NULL;
	CShortDatas *pDatas = pMacro->GetFaultParas();

	pData = (CShortData*)pDatas->FindByID(strDataID);

	if (pData == NULL)
	{
		pDatas = pMacro->GetSysParas();
		pData = (CShortData*)pDatas->FindByID(strDataID);
	}

	if (pData == NULL)
	{
		return 0;
	}

	return TMS_SetDataAttr(pData, strAttrID, strValue);
}

long TMS_SetDatasAttrByGroupID(CTestMacro *pMacro, const CString &strGroupID, const CString &strAttrID, const CString &strValue)
{
	CExBaseList oList;
	TMS_GetDatasByGroupID(pMacro, strGroupID, &oList);
	long nCount = TMS_SetDatasAttr(&oList, strAttrID, strValue);
	oList.RemoveAll();
	return nCount;
}

void TMS_InitDatasAttrEx(CExBaseList *pDatas)
{
	if (pDatas == NULL)
	{
		return;
	}

	POS pos = pDatas->GetHeadPosition();
	CShortData *pData = NULL;
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pDatas->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DTMCLASSID_CSHORTDATA)
		{
			((CShortData*)p)->m_nReserved = 0x0FFFFFFF;
		}
		else if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			TMS_InitDatasAttrEx((CExBaseList*)p);
		}
	}
}


void TMS_InitDatasAttr(CTestMacro *pMacro)
{
	TMS_InitDatasAttr(pMacro->GetFaultParas());
	TMS_InitDatasAttr(pMacro->GetSysParas());
	TMS_InitDatasAttrEx(pMacro->GetFaultParasEx());

	CTestMacroScript *pScript = TM_GetTestMacroScript(pMacro);

	if (pScript != NULL)
	{
		pScript->InitScript(pMacro);
	}
}

void TMS_InitDatasAttr(CExBaseList *pDatas)
{
	POS pos = pDatas->GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CShortData *)pDatas->GetNext(pos);
		pData->m_nReserved = 0x0FFFFFFF;
	}
}

BOOL TMS_RunScript(CTestMacro *pMacro, CShortData *pData)
{
	CTestMacroScript *pScript = TM_GetTestMacroScript(pMacro);
	BOOL bTrue = FALSE;

	if (pScript != NULL)
	{
		bTrue = pScript->RunScript(pMacro, pData);
	}

	return bTrue;
}

