//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowShape_Branch.cpp  CVFlowShape_Branch


#include "stdafx.h"
#include "VFlowShape_Branch.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVFlowShape_Branch::CVFlowShape_Branch()
{
	//初始化属性

	//初始化成员变量
}

CVFlowShape_Branch::~CVFlowShape_Branch()
{
}

long CVFlowShape_Branch::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShape::XmlReadOwn(oNode, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShape_Branch::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShape::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShape_Branch::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CVFlowShape_Branch::InitAfterRead()
{
}

BOOL CVFlowShape_Branch::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CVFlowShape::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CVFlowShape_Branch *p = (CVFlowShape_Branch*)pObj;

	return TRUE;
}

BOOL CVFlowShape_Branch::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CVFlowShape::CopyOwn(pDest);

	CVFlowShape_Branch *p = (CVFlowShape_Branch*)pDest;

	return TRUE;
}

CBaseObject* CVFlowShape_Branch::Clone()
{
	CVFlowShape_Branch *p = new CVFlowShape_Branch();
	Copy(p);
	return p;
}

CBaseObject* CVFlowShape_Branch::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CVFlowShape_Branch *p = new CVFlowShape_Branch();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CVFlowShape_Branch::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CVFlowShape_Branch::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CVFlowShape_Branch::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

CVFlowShape* CVFlowShape_Branch::GetBeginShape_Connected()
{
	CVFlowShapeLine *pInLine = (CVFlowShapeLine*)m_oInLines.GetHead(); 

	if (pInLine == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前分支节点Shape(%s)前端无连接线,错误."),m_strName);
		return NULL;
	}

	if (pInLine->m_pBeginShape == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前line(%s)无首端Shape,错误."),pInLine->m_strName);
		return NULL;
	}

	return (CVFlowShape*)pInLine->m_pBeginShape;
}

void CVFlowShape_Branch::UpdateLineType_Color()
{
	CVFlowShape *pInShape = GetBeginShape_Connected(); 

	if (pInShape == NULL)
	{
		return;
	}

	m_strData3 = pInShape->m_strData3;
	CVFlowShape::UpdateLineType_Color();

	CString strValue,strUnit;
	Global_GetValueUnit(m_strData3,strValue,strUnit);
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

	m_oOutLines.UpdateAllShapes();
}

void CVFlowShape_Branch::InitDataTypeUnit()
{
	CVFlowShape *pInShape = GetBeginShape_Connected();

	if (pInShape == NULL)
	{
		return;
	}

	CString strValue;

	if (pInShape->GetPropertyValueByID(VFLOW_VISIO_DATA_TYPE,strValue))
	{
		m_strDataType = strValue;
	}

	if (pInShape->GetPropertyValueByID(VFLOW_VISIO_UNIT,strValue))
	{
		m_strUnit = strValue;
	}

	SetPropertyDataTypeUnitByID(VFLOW_VISIO_TAG_VALUE,m_strDataType,m_strUnit);
	m_oOutLines.InitDataTypeUnit(m_strDataType,m_strUnit);
}

