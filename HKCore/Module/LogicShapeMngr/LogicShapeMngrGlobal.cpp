//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//LogicShapeMngrGlobal.cpp

#include "stdafx.h"
#include "LogicShapeMngrGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CLogicShapeMngrXmlRWKeys

CLogicShapeMngrXmlRWKeys* CLogicShapeMngrXmlRWKeys::g_pXmlKeys = NULL;
long CLogicShapeMngrXmlRWKeys::g_nMngrRef = 0;


CLogicShapeMngrXmlRWKeys::CLogicShapeMngrXmlRWKeys()
{
	m_strCVFlowShapePropertyKey = L"shape-property";
	m_strCVFlowExec_VisioKey = L"flow-exec-visio";
	m_strCVFlowShapeLinesKey = L"flow-shape-lines";
	m_strCVFlowShapesKey = L"flow-shapes";
	m_strCVFlowShape_ThresholdKey = L"flow-shape-threshold";
	m_strCVFlowShape_ExpressionKey = L"flow-shape-expression";
	m_strCVFlowShape_BranchKey = L"flow-shape-branch";
	m_strCVFlowShape_LogicKey = L"flow-shape-logic";
	m_strCVFlowShape_DataKey = L"flow-shape-data";
	m_strCVFlowShapeKey = L"flow-shape";
	m_strCVFlowShapeLineKey = L"flow-shape-line";
	m_strCVFlowShapesBaseKey = L"flow-shapes-base";
	m_strCVFlowShapeBaseKey = L"flow-shape-base";
	m_strVisioIDKey = L"visio-id";
	m_strDataTypeKey = L"data-type";
	m_strHelpKey = L"help";
	m_strData1Key = L"data1";
	m_strData2Key = L"data2";
	m_strData3Key = L"data3";
	m_strUnitKey = L"unit";
	m_strValueKey = L"value";
	m_strPathKey = L"path";
	m_strRowIndexKey = L"row-index";
}

CLogicShapeMngrXmlRWKeys::~CLogicShapeMngrXmlRWKeys()
{
}

CLogicShapeMngrXmlRWKeys* CLogicShapeMngrXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CLogicShapeMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CLogicShapeMngrXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CLogicShapeMngrConstGlobal

long CLogicShapeMngrConstGlobal::g_nGlobalRef = 0;
CLogicShapeMngrConstGlobal* CLogicShapeMngrConstGlobal::g_pGlobal = NULL;


CLogicShapeMngrConstGlobal::CLogicShapeMngrConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CLogicShapeMngrConstGlobal::~CLogicShapeMngrConstGlobal()
{
}

CLogicShapeMngrConstGlobal* CLogicShapeMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CLogicShapeMngrConstGlobal();
	}

	return g_pGlobal;
}

void CLogicShapeMngrConstGlobal::Release()
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

BOOL Global_GetValueUnit(const CString &strData,CString &strValue, CString &strUnit)
{
	long nTotalLenth = strData.GetLength();
	long nValueLenth = 0;
	char zfChar = NULL;

	while(nValueLenth<nTotalLenth)
	{
		zfChar = strData.GetAt(nValueLenth);

		if (((zfChar>='0')&&(zfChar<='9'))||(zfChar=='.'))
		{
			nValueLenth++;
		}
		else
		{
			break;
		}
	}

	if (nValueLenth == 0)
	{
		strValue = _T("0");
		strUnit = strData;
	}
	else if (nValueLenth == nTotalLenth)
	{
		strValue = strData;
		strUnit = _T("");
	}
	else
	{
		strValue = strData.Left(nValueLenth);
		strUnit = strData.Mid(nValueLenth);
	}

	return TRUE;
}
