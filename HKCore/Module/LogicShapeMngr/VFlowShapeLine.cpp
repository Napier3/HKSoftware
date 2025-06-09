//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowShapeLine.cpp  CVFlowShapeLine


#include "stdafx.h"
#include "VFlowShapeLine.h"
#include "VFlowShape_Branch.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVFlowShapeLine::CVFlowShapeLine()
{
	//初始化属性

	//初始化成员变量
	m_pBeginShape = NULL;
	m_pEndShape = NULL;
}

CVFlowShapeLine::~CVFlowShapeLine()
{
}

long CVFlowShapeLine::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShapeBase::XmlReadOwn(oNode, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShapeLine::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShapeBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShapeLine::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CVFlowShapeBase::SerializeOwn(oBinaryBuffer);
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

void CVFlowShapeLine::InitAfterRead()
{
}

BOOL CVFlowShapeLine::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CVFlowShapeBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CVFlowShapeLine *p = (CVFlowShapeLine*)pObj;

	return TRUE;
}

BOOL CVFlowShapeLine::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CVFlowShapeBase::CopyOwn(pDest);

	CVFlowShapeLine *p = (CVFlowShapeLine*)pDest;

	return TRUE;
}

CBaseObject* CVFlowShapeLine::Clone()
{
	CVFlowShapeLine *p = new CVFlowShapeLine();
	Copy(p);
	return p;
}

CBaseObject* CVFlowShapeLine::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CVFlowShapeLine *p = new CVFlowShapeLine();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CVFlowShapeLine::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CVFlowShapeLine::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CVFlowShapeLine::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

void CVFlowShapeLine::UpdateLineType_Color()
{
	ASSERT(m_pBeginShape);
	CVFlowShape *pValueRefShape = (CVFlowShape*)m_pBeginShape;

	if (m_pBeginShape->GetClassID() == MNGRCLASSID_CVFLOWSHAPE_BRANCH)//对于分支节点，需要特殊处理
	{
		CVFlowShape_Branch *pShapeBranch = (CVFlowShape_Branch*)m_pBeginShape;
		pValueRefShape = (CVFlowShape*)pShapeBranch->GetBeginShape_Connected();
		ASSERT(pValueRefShape);
	}

	m_strData3 = pValueRefShape->m_strData3;

	if (pValueRefShape->GetClassID() == MNGRCLASSID_CVFLOWSHAPE_DATA)
	{
		SetShapeLineType(VISIO_SHAPE_SHOW_LINE_TYPE_DATA);
		SetShapeColor(VISIO_SHAPE_SHOW_TYPE_COLOR_DATA);
	}
	else
	{
		CString strValue,strUnit;
		Global_GetValueUnit(pValueRefShape->m_strData3,strValue,strUnit);
		long nValue = CString_To_long(strValue);

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
	}
}
