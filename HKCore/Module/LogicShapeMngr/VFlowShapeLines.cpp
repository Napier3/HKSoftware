//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowShapeLines.cpp  CVFlowShapeLines


#include "stdafx.h"
#include "VFlowShapeLines.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVFlowShapeLines::CVFlowShapeLines()
{
	//初始化属性

	//初始化成员变量
}

CVFlowShapeLines::~CVFlowShapeLines()
{
}

long CVFlowShapeLines::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShapesBase::XmlReadOwn(oNode, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShapeLines::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShapesBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShapeLines::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CVFlowShapesBase::SerializeOwn(oBinaryBuffer);
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

void CVFlowShapeLines::InitAfterRead()
{
}

BOOL CVFlowShapeLines::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CVFlowShapesBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CVFlowShapeLines *p = (CVFlowShapeLines*)pObj;

	return TRUE;
}

BOOL CVFlowShapeLines::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CVFlowShapesBase::CopyOwn(pDest);

	CVFlowShapeLines *p = (CVFlowShapeLines*)pDest;

	return TRUE;
}

CBaseObject* CVFlowShapeLines::Clone()
{
	CVFlowShapeLines *p = new CVFlowShapeLines();
	Copy(p);
	return p;
}

CBaseObject* CVFlowShapeLines::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CVFlowShapeLines *p = new CVFlowShapeLines();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CVFlowShapeLines::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CVFLOWSHAPELINE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CVFlowShapeLines::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCVFlowShapeLineKey)
	{
		pNew = new CVFlowShapeLine();
	}

	return pNew;
}

CExBaseObject* CVFlowShapeLines::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CVFLOWSHAPELINE)
	{
		pNew = new CVFlowShapeLine();
	}

	return pNew;
}

void CVFlowShapeLines::InitDataTypeUnit(const CString &strDataType,const CString &strUnit)
{
	CVFlowShapeLine *pCurLine = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pCurLine = (CVFlowShapeLine *)GetNext(pos);
		pCurLine->m_strDataType = strDataType;
		pCurLine->m_strUnit = strUnit;
	}
}