//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowShapeProperty.cpp  CVFlowShapeProperty


#include "stdafx.h"
#include "VFlowShapeProperty.h"

#include "VFlowShapeBase.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVFlowShapeProperty::CVFlowShapeProperty()
{
	//初始化属性
	m_nRowIndex = 0;

	//初始化成员变量
}

CVFlowShapeProperty::~CVFlowShapeProperty()
{
}

long CVFlowShapeProperty::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strPathKey, oNode, m_strPath);
	xml_GetAttibuteValue(pXmlKeys->m_strRowIndexKey, oNode, m_nRowIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	return 0;
}

long CVFlowShapeProperty::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strPathKey, oElement, m_strPath);
	xml_SetAttributeValue(pXmlKeys->m_strRowIndexKey, oElement, m_nRowIndex);
	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	return 0;
}

long CVFlowShapeProperty::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strPath);
		BinarySerializeCalLen(oBinaryBuffer, m_nRowIndex);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strPath);
		BinarySerializeRead(oBinaryBuffer, m_nRowIndex);
		BinarySerializeRead(oBinaryBuffer, m_strDataType);
		BinarySerializeRead(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strPath);
		BinarySerializeWrite(oBinaryBuffer, m_nRowIndex);
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
		BinarySerializeWrite(oBinaryBuffer, m_strUnit);
	}
	return 0;
}

void CVFlowShapeProperty::InitAfterRead()
{
}

BOOL CVFlowShapeProperty::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CVFlowShapeProperty *p = (CVFlowShapeProperty*)pObj;

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_strPath != p->m_strPath)
	{
		return FALSE;
	}

	if(m_nRowIndex != p->m_nRowIndex)
	{
		return FALSE;
	}

	if(m_strDataType != p->m_strDataType)
	{
		return FALSE;
	}

	if(m_strUnit != p->m_strUnit)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CVFlowShapeProperty::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CVFlowShapeProperty *p = (CVFlowShapeProperty*)pDest;

	p->m_strValue = m_strValue;
	p->m_strPath = m_strPath;
	p->m_nRowIndex = m_nRowIndex;
	p->m_strDataType = m_strDataType;
	p->m_strUnit = m_strUnit;
	return TRUE;
}

CBaseObject* CVFlowShapeProperty::Clone()
{
	CVFlowShapeProperty *p = new CVFlowShapeProperty();
	Copy(p);
	return p;
}

CBaseObject* CVFlowShapeProperty::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CVFlowShapeProperty *p = new CVFlowShapeProperty();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CVFlowShapeProperty::SetValue_UI(const CString &strValue)
{
	m_strValue = strValue;
	return UpdataValue_UI();
}

BOOL CVFlowShapeProperty::UpdataValue_UI()
{
	CVFlowShapeBase *pParentShape = (CVFlowShapeBase*)GetParent();

	if (pParentShape == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前属性(Name=%s;ID=%s;Path=%s;)缺少父节点."),m_strName,m_strID,m_strPath);
		return FALSE;
	}

	if (pParentShape->m_oShape == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前属性(Name=%s;ID=%s;Path=%s;)的父节点(Name=%s;Data1=%s;)的m_oShape成员变量为空."),
			m_strName,m_strID,m_strPath,pParentShape->m_strName,pParentShape->m_strData1);
		return FALSE;
	}

	MSVisio15::CVCell oCurCell = NULL;

	try
	{
		oCurCell = pParentShape->m_oShape.get_CellsSRC(MSVisio15::visSectionProp,m_nRowIndex,MSVisio15::visCustPropsValue);

		if (oCurCell == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前Shape节点(Name=%s;Data1=%s;)的属性(RowIndex)不存在."),pParentShape->m_strName,pParentShape->m_strData1,m_nRowIndex);
			return FALSE;
		}

		oCurCell.put_FormulaU(m_strValue);//"值(V):"中填入的值
		return TRUE;

	}
	catch(...)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("设置形状(%s)对应的属性值(%ld)失败."),pParentShape->m_strName,m_nRowIndex);
		return FALSE;
	}
}

BOOL CVFlowShapeProperty::GetValue_UI(CString &strValue)
{
	CVFlowShapeBase *pParentShape = (CVFlowShapeBase*)GetParent();

	if (pParentShape == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前属性(Name=%s;ID=%s;Path=%s;)缺少父节点."),m_strName,m_strID,m_strPath);
		return FALSE;
	}

	if (pParentShape->m_oShape == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前属性(Name=%s;ID=%s;Path=%s;)的父节点(Name=%s;Data1=%s;)的m_oShape成员变量为空."),
			m_strName,m_strID,m_strPath,pParentShape->m_strName,pParentShape->m_strData1);
		return FALSE;
	}

	MSVisio15::CVCell oCurCell = NULL;

	try
	{
		oCurCell = pParentShape->m_oShape.get_CellsSRC(MSVisio15::visSectionProp,m_nRowIndex,MSVisio15::visCustPropsValue);

		if (oCurCell == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前Shape节点(Name=%s;Data1=%s;)的属性(RowIndex)不存在."),pParentShape->m_strName,pParentShape->m_strData1,m_nRowIndex);
			return FALSE;
		}

		strValue = oCurCell.get_FormulaU();//"值(V):"中填入的值
		strValue.Replace(_T("\""),_T(""));
		m_strValue = strValue;
		return TRUE;

	}
	catch(...)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("设置形状(%s)对应的属性值(%ld)失败."),pParentShape->m_strName,m_nRowIndex);
		return FALSE;
	}
}