//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowShape_Logic.cpp  CVFlowShape_Logic


#include "stdafx.h"
#include "VFlowShape_Logic.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVFlowShape_Logic::CVFlowShape_Logic()
{
	//初始化属性

	//初始化成员变量
}

CVFlowShape_Logic::~CVFlowShape_Logic()
{
}

long CVFlowShape_Logic::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShape::XmlReadOwn(oNode, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShape_Logic::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShape::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShape_Logic::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CVFlowShape::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CVFlowShape_Logic::InitAfterRead()
{
}

BOOL CVFlowShape_Logic::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CVFlowShape::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CVFlowShape_Logic *p = (CVFlowShape_Logic*)pObj;

	return TRUE;
}

BOOL CVFlowShape_Logic::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CVFlowShape::CopyOwn(pDest);

	CVFlowShape_Logic *p = (CVFlowShape_Logic*)pDest;

	return TRUE;
}

CBaseObject* CVFlowShape_Logic::Clone()
{
	CVFlowShape_Logic *p = new CVFlowShape_Logic();
	Copy(p);
	return p;
}

CBaseObject* CVFlowShape_Logic::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CVFlowShape_Logic *p = new CVFlowShape_Logic();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CVFlowShape_Logic::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CVFlowShape_Logic::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CVFlowShape_Logic::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

long CVFlowShape_Logic::CalcLogicValue_AND()
{
	if (m_oInLines.GetCount() == 0)
	{
		return 0;
	}

	long nInValue=1;
	CString strValue,strUnit;
	CVFlowShapeLine *pCurLine = NULL;
	POS pos = m_oInLines.GetHeadPosition();

	while(pos)
	{
		pCurLine = (CVFlowShapeLine *)m_oInLines.GetNext(pos);
		ASSERT(pCurLine->m_pBeginShape);
		Global_GetValueUnit(pCurLine->m_pBeginShape->m_strData3,strValue,strUnit);
		nInValue = CString_To_long(strValue);

		if (nInValue == 0)
			return 0;
	}

	return 1;
}

long CVFlowShape_Logic::CalcLogicValue_OR()
{
	long nInValue=1;
	CString strValue,strUnit;
	CVFlowShapeLine *pCurLine = NULL;
	POS pos = m_oInLines.GetHeadPosition();

	while(pos)
	{
		pCurLine = (CVFlowShapeLine *)m_oInLines.GetNext(pos);
		ASSERT(pCurLine->m_pBeginShape);
		Global_GetValueUnit(pCurLine->m_pBeginShape->m_strData3,strValue,strUnit);
		nInValue = CString_To_long(strValue);

		if (nInValue != 0)
			return 1;
	}

	return 0;
}

long CVFlowShape_Logic::CalcLogicValue_NOT()
{
	if (m_oInLines.GetCount() == 0)
	{
		return 0;
	}

	long nInValue=1;
	CString strValue,strUnit;
	CVFlowShapeLine *pCurLine = (CVFlowShapeLine*)m_oInLines.GetHead();
	ASSERT(pCurLine->m_pBeginShape);
	Global_GetValueUnit(pCurLine->m_pBeginShape->m_strData3,strValue,strUnit);
	nInValue = CString_To_long(strValue);
	return nInValue;
}

long CVFlowShape_Logic::CalcLogicValue()
{
	long nInValue=0;

	if (m_strData1 == _T("AND"))
	{
		nInValue = CalcLogicValue_AND();
	}
	else if (m_strData1 == _T("OR"))
	{
		nInValue = CalcLogicValue_OR();
	}
	else if (m_strData1 == _T("NOT"))
	{
		nInValue = CalcLogicValue_NOT();
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前逻辑节点Shape(%s)逻辑运算符号(%s)不存在."),m_strName,m_strData1);
	}

	m_strData3.Format(_T("%ld"),nInValue);
	return nInValue;
}

void CVFlowShape_Logic::UpdateLineType_Color()
{
	long nValue = CalcLogicValue();
	CVFlowShape::UpdateLineType_Color();

	CVFlowShapeProperty *pProperty = (CVFlowShapeProperty*)FindByID(VFLOW_VISIO_ACT_TIME);

	if ((pProperty != NULL)&&(nValue==0))
	{
		pProperty->SetValue_UI(_T("-1"));
	}

	if (nValue>0)
	{
		SetShapeLineType(VISIO_SHAPE_SHOW_LINE_TYPE_TRUE);
		SetShapeColor(VISIO_SHAPE_SHOW_TYPE_COLOR_TRUE);
	} 
	else
	{
		SetShapeLineType(VISIO_SHAPE_SHOW_LINE_TYPE_FALSE);
		SetShapeColor(VISIO_SHAPE_SHOW_TYPE_COLOR_FALSE);
	}

	m_oOutLines.UpdateAllShapes();
}


