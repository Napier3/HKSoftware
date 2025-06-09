//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowShape_Data.cpp  CVFlowShape_Data


#include "stdafx.h"
#include "VFlowShape_Data.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVFlowShape_Data::CVFlowShape_Data()
{
	//初始化属性

	//初始化成员变量
}

CVFlowShape_Data::~CVFlowShape_Data()
{
}

long CVFlowShape_Data::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShape::XmlReadOwn(oNode, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShape_Data::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShape::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShape_Data::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CVFlowShape_Data::InitAfterRead()
{
}

BOOL CVFlowShape_Data::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CVFlowShape::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CVFlowShape_Data *p = (CVFlowShape_Data*)pObj;

	return TRUE;
}

BOOL CVFlowShape_Data::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CVFlowShape::CopyOwn(pDest);

	CVFlowShape_Data *p = (CVFlowShape_Data*)pDest;

	return TRUE;
}

CBaseObject* CVFlowShape_Data::Clone()
{
	CVFlowShape_Data *p = new CVFlowShape_Data();
	Copy(p);
	return p;
}

CBaseObject* CVFlowShape_Data::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CVFlowShape_Data *p = new CVFlowShape_Data();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CVFlowShape_Data::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CVFlowShape_Data::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CVFlowShape_Data::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	return pNew;
}

void CVFlowShape_Data::UpdateLineType_Color()
{
	CVFlowShape::UpdateLineType_Color();
	SetShapeLineType(VISIO_SHAPE_SHOW_LINE_TYPE_DATA);
	SetShapeColor(VISIO_SHAPE_SHOW_TYPE_COLOR_DATA);
	ASSERT(m_oInLines.GetCount() == 0);
	m_oOutLines.UpdateAllShapes();
}