//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowShape.cpp  CVFlowShape


#include "stdafx.h"
#include "VFlowShape.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVFlowShape::CVFlowShape()
{
	//初始化属性

	//初始化成员变量
	m_bHasAttachCalc = FALSE;
}

CVFlowShape::~CVFlowShape()
{
	m_oInLines.RemoveAll();
	m_oOutLines.RemoveAll();
}

long CVFlowShape::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShapeBase::XmlReadOwn(oNode, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShape::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShapeBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShape::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CVFlowShape::InitAfterRead()
{
}

BOOL CVFlowShape::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CVFlowShapeBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CVFlowShape *p = (CVFlowShape*)pObj;

	return TRUE;
}

BOOL CVFlowShape::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CVFlowShapeBase::CopyOwn(pDest);

	CVFlowShape *p = (CVFlowShape*)pDest;

	return TRUE;
}

CBaseObject* CVFlowShape::Clone()
{
	CVFlowShape *p = new CVFlowShape();
	Copy(p);
	return p;
}

CBaseObject* CVFlowShape::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CVFlowShape *p = new CVFlowShape();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CVFlowShape::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CVFlowShape::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CVFlowShape::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

void CVFlowShape::UpdateLineType_Color()
{
	CVFlowShapeBase::UpdateLineType_Color();
}

void CVFlowShape::InitDataTypeUnit()
{
	CString strValue;

	if (GetPropertyValueByID(VFLOW_VISIO_DATA_TYPE,strValue))
	{
		m_strDataType = strValue;
	}

	if (GetPropertyValueByID(VFLOW_VISIO_UNIT,strValue))
	{
		m_strUnit = strValue;
	}

	SetPropertyDataTypeUnitByID(VFLOW_VISIO_TAG_VALUE,m_strDataType,m_strUnit);
	m_oOutLines.InitDataTypeUnit(m_strDataType,m_strUnit);
}

