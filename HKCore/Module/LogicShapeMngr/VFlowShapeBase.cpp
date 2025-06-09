//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowShapeBase.cpp  CVFlowShapeBase


#include "stdafx.h"
#include "VFlowShapeBase.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVFlowShapeBase::CVFlowShapeBase()
{
	//初始化属性
	m_nVisioID = 0;

	//初始化成员变量
	m_oShape = NULL;
}

CVFlowShapeBase::~CVFlowShapeBase()
{
	m_oShape = NULL;
}

long CVFlowShapeBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strVisioIDKey, oNode, m_nVisioID);
	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strHelpKey, oNode, m_strHelp);
	xml_GetAttibuteValue(pXmlKeys->m_strData1Key, oNode, m_strData1);
	xml_GetAttibuteValue(pXmlKeys->m_strData2Key, oNode, m_strData2);
	xml_GetAttibuteValue(pXmlKeys->m_strData3Key, oNode, m_strData3);
	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	return 0;
}

long CVFlowShapeBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strVisioIDKey, oElement, m_nVisioID);
	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
	xml_SetAttributeValue(pXmlKeys->m_strHelpKey, oElement, m_strHelp);
	xml_SetAttributeValue(pXmlKeys->m_strData1Key, oElement, m_strData1);
	xml_SetAttributeValue(pXmlKeys->m_strData2Key, oElement, m_strData2);
	xml_SetAttributeValue(pXmlKeys->m_strData3Key, oElement, m_strData3);
	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	return 0;
}

long CVFlowShapeBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nVisioID);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
		BinarySerializeCalLen(oBinaryBuffer, m_strHelp);
		BinarySerializeCalLen(oBinaryBuffer, m_strData1);
		BinarySerializeCalLen(oBinaryBuffer, m_strData2);
		BinarySerializeCalLen(oBinaryBuffer, m_strData3);
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nVisioID);
		BinarySerializeRead(oBinaryBuffer, m_strDataType);
		BinarySerializeRead(oBinaryBuffer, m_strHelp);
		BinarySerializeRead(oBinaryBuffer, m_strData1);
		BinarySerializeRead(oBinaryBuffer, m_strData2);
		BinarySerializeRead(oBinaryBuffer, m_strData3);
		BinarySerializeRead(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nVisioID);
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
		BinarySerializeWrite(oBinaryBuffer, m_strHelp);
		BinarySerializeWrite(oBinaryBuffer, m_strData1);
		BinarySerializeWrite(oBinaryBuffer, m_strData2);
		BinarySerializeWrite(oBinaryBuffer, m_strData3);
		BinarySerializeWrite(oBinaryBuffer, m_strUnit);
	}
	return 0;
}

void CVFlowShapeBase::InitAfterRead()
{
}

BOOL CVFlowShapeBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CVFlowShapeBase *p = (CVFlowShapeBase*)pObj;

	if(m_nVisioID != p->m_nVisioID)
	{
		return FALSE;
	}

	if(m_strDataType != p->m_strDataType)
	{
		return FALSE;
	}

	if(m_strHelp != p->m_strHelp)
	{
		return FALSE;
	}

	if(m_strData1 != p->m_strData1)
	{
		return FALSE;
	}

	if(m_strData2 != p->m_strData2)
	{
		return FALSE;
	}

	if(m_strData3 != p->m_strData3)
	{
		return FALSE;
	}

	if(m_strUnit != p->m_strUnit)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CVFlowShapeBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CVFlowShapeBase *p = (CVFlowShapeBase*)pDest;

	p->m_nVisioID = m_nVisioID;
	p->m_strDataType = m_strDataType;
	p->m_strHelp = m_strHelp;
	p->m_strData1 = m_strData1;
	p->m_strData2 = m_strData2;
	p->m_strData3 = m_strData3;
	p->m_strUnit = m_strUnit;
	return TRUE;
}

CBaseObject* CVFlowShapeBase::Clone()
{
	CVFlowShapeBase *p = new CVFlowShapeBase();
	Copy(p);
	return p;
}

CBaseObject* CVFlowShapeBase::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CVFlowShapeBase *p = new CVFlowShapeBase();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CVFlowShapeBase::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CVFLOWSHAPEPROPERTY)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CVFlowShapeBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCVFlowShapePropertyKey)
	{
		pNew = new CVFlowShapeProperty();
	}

	return pNew;
}

CExBaseObject* CVFlowShapeBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CVFLOWSHAPEPROPERTY)
	{
		pNew = new CVFlowShapeProperty();
	}

	return pNew;
}

CVFlowShapeProperty* CVFlowShapeBase::FindByPath(const CString &strPath)
{
	CVFlowShapeProperty *pProperty = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pProperty = (CVFlowShapeProperty*)GetNext(pos);

		if (pProperty->m_strPath == strPath)
		{
			return pProperty;
		}
	}

	return NULL;
}

BOOL CVFlowShapeBase::SetShapeLineType(const long &nLineType)
{
	if (!Has_VisioShapeObj())
	{
		return FALSE;
	}	

	try
	{
		MSVisio15::CVCell oCurCell = m_oShape.get_CellsSRC(MSVisio15::visSectionObject, MSVisio15::visRowLine, MSVisio15::visLinePattern);
		CString strLineType;
		strLineType.Format(_T("%ld"),nLineType);

		if (oCurCell != NULL)
		{
			oCurCell.put_FormulaU(strLineType);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前Shape(%s)线条类型(%ld)函数get_CellsSRC调用失败."),m_strName,nLineType);
			return FALSE;
		}

	}
	catch(...)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前Shape(%s)线条类型(%ld)设置失败."),m_strName,nLineType);
		return FALSE;
	}

	return TRUE;
}

BOOL CVFlowShapeBase::Has_VisioShapeObj()
{
	if (m_oShape == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前Shape节点(Name=%s;Data1=%s;)的m_oShape成员变量为空."),m_strName,m_strData1);
		return FALSE;
	}

	return TRUE;
}

BOOL CVFlowShapeBase::SetShapeColor(const CString &strColor)
{
	 if (!Has_VisioShapeObj())
	 {
		 return FALSE;
	 }	

	try
	{
		MSVisio15::CVCell oCurCell = m_oShape.get_CellsSRC(MSVisio15::visSectionObject, MSVisio15::visRowLine, MSVisio15::visLineColor);

		if (oCurCell != NULL)
		{
			oCurCell.put_FormulaU(strColor);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前Shape(%s)线条颜色(%s)设置函数get_CellsSRC调用失败."),m_strName,strColor);
			return FALSE;
		}

	}
	catch(...)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前Shape(%s)线条颜色(%s)设置失败."),m_strName,strColor);
		return FALSE;
	}

	return TRUE;
}

void CVFlowShapeBase::UpdateLineType_Color()
{
	CVFlowShapeProperty *pProperty = (CVFlowShapeProperty*)FindByID(VFLOW_VISIO_TAG_VALUE);

	if (pProperty != NULL)
	{
		pProperty->SetValue_UI(m_strData3);
	}

	pProperty = (CVFlowShapeProperty*)FindByID(VFLOW_VISIO_SETTING_VALUE);

	if (pProperty != NULL)
	{
		pProperty->UpdataValue_UI();
	}

	pProperty = (CVFlowShapeProperty*)FindByID(VFLOW_VISIO_REAL_VALUE);

	if (pProperty != NULL)
	{
		pProperty->UpdataValue_UI();
	}
}

void CVFlowShapeBase::AddNewProperty(const long &nRowIndex)
{
	CVFlowShapeProperty *pShapeProperty = new CVFlowShapeProperty;
	pShapeProperty->m_nRowIndex = nRowIndex;
	AddNewChild(pShapeProperty);
	GetPropertyValuesByRowIndex_UI(pShapeProperty);
}

BOOL CVFlowShapeBase::GetPropertyValuesByRowIndex_UI(CVFlowShapeProperty *pShapeProperty)
{
	return GetPropertyByRowIndex_UI(pShapeProperty->m_nRowIndex,pShapeProperty->m_strID,pShapeProperty->m_strValue,pShapeProperty->m_strName,pShapeProperty->m_strPath);
}

BOOL CVFlowShapeBase::GetPropertyByRowIndex_UI(const long &nRowIndex,CString &strPropertyName,CString &strPropertyValue,CString &strPropertyLabel,CString &strPropertyTip)
{
	MSVisio15::CVCell oCurCell = NULL;

	try
	{
		oCurCell = m_oShape.get_CellsSRC(MSVisio15::visSectionProp,nRowIndex,MSVisio15::visCustPropsValue);

		if (oCurCell != NULL)
		{
			strPropertyName = oCurCell.get_RowNameU();//"名称(N):"中填入的值
			strPropertyValue = oCurCell.get_FormulaU();//"值(V):"中填入的值
			strPropertyValue.Replace(_T("\""),_T(""));
		}

		oCurCell = m_oShape.get_CellsSRC(MSVisio15::visSectionProp,nRowIndex,MSVisio15::visCustPropsLabel);

		if (oCurCell != NULL)
		{
			strPropertyLabel = oCurCell.get_FormulaU();//"标签(L):"中填入的值
			strPropertyLabel.Replace(_T("\""),_T(""));
		}

		oCurCell = m_oShape.get_CellsSRC(MSVisio15::visSectionProp,nRowIndex,MSVisio15::visCustPropsPrompt);

		if (oCurCell != NULL)
		{
			strPropertyTip = oCurCell.get_FormulaU();//"提示(P):"中填入的值
			strPropertyTip.Replace(_T("\""),_T(""));
		}
	}
	catch(...)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取形状(%s)对应的属性(RowIndex=%ld)失败."),m_strName,nRowIndex);
		return FALSE;
	}

	return TRUE;
}

// BOOL CVFlowShapeBase::SetPropertyValueByRowIndex_UI(const long &nRowIndex,const CString &strPropertyValue)
// {
// 	if (m_oShape == NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前Shape节点(Name=%s;Data1=%s;)的m_oShape成员变量为空."),m_strName,m_strData1);
// 		return FALSE;
// 	}
// 
// 	MSVisio15::CVCell oCurCell = NULL;
// 
// 	try
// 	{
// 		oCurCell = m_oShape.get_CellsSRC(MSVisio15::visSectionProp,nRowIndex,MSVisio15::visCustPropsValue);
// 
// 		if (oCurCell == NULL)
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前Shape节点(Name=%s;Data1=%s;)的属性(RowIndex)不存在."),m_strName,m_strData1,nRowIndex);
// 			return FALSE;
// 		}
// 
// 		oCurCell.put_FormulaU(strPropertyValue);//"值(V):"中填入的值
// 		return TRUE;
// 
// 	}
// 	catch(...)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("设置形状(%s)对应的属性值(%ld)失败."),m_strName,nRowIndex);
// 		return FALSE;
// 	}
// }

BOOL CVFlowShapeBase::GetPropertyValueByID(const CString &strPropertyID,CString &strValue)
{
	CVFlowShapeProperty *pProperty = (CVFlowShapeProperty*)FindByID(strPropertyID);
//	strValue = _T("");

	if (pProperty == NULL)
	{
		return FALSE;
	}

	strValue = pProperty->m_strValue;
	return TRUE;
}

BOOL CVFlowShapeBase::SetPropertyValueByID(const CString &strPropertyID,const CString &strValue)
{
	CVFlowShapeProperty *pProperty = (CVFlowShapeProperty*)FindByID(strPropertyID);

	if (pProperty == NULL)
	{
		return FALSE;
	}

	pProperty->m_strValue = strValue;
	return TRUE;
}


BOOL CVFlowShapeBase::GetPropertyValueByID_UI(const CString &strPropertyID,CString &strValue)
{
	CVFlowShapeProperty *pProperty = (CVFlowShapeProperty*)FindByID(strPropertyID);

	if (pProperty == NULL)
	{
		return FALSE;
	}

	return pProperty->GetValue_UI(strValue);
}

BOOL CVFlowShapeBase::SetPropertyValueByID_UI(const CString &strPropertyID,const CString &strValue)
{
	CVFlowShapeProperty *pProperty = (CVFlowShapeProperty*)FindByID(strPropertyID);

	if (pProperty == NULL)
	{
		return FALSE;
	}

	return pProperty->SetValue_UI(strValue);
}

BOOL CVFlowShapeBase::SetPropertyDataTypeUnitByID(const CString &strPropertyID,const CString &strDataType,const CString &strUnit)
{
	CVFlowShapeProperty *pProperty = (CVFlowShapeProperty*)FindByID(strPropertyID);

	if (pProperty == NULL)
	{
		return FALSE;
	}

	pProperty->m_strDataType = strDataType;
	pProperty->m_strUnit = strUnit;
	return TRUE;
}

BOOL CVFlowShapeBase::SetPropertyValueByPath_UI(const CString &strPropertyPath,const CString &strValue)
{
	CVFlowShapeProperty *pProperty = (CVFlowShapeProperty*)FindByPath(strPropertyPath);

	if (pProperty == NULL)
	{
		return FALSE;
	}

	return pProperty->SetValue_UI(strValue);
}

BOOL CVFlowShapeBase::GetPropertyValueByPath_UI(const CString &strPropertyPath,CString &strValue)
{
	CVFlowShapeProperty *pProperty = (CVFlowShapeProperty*)FindByPath(strPropertyPath);

	if (pProperty == NULL)
	{
		return FALSE;
	}

	return pProperty->GetValue_UI(strValue);
}

BOOL CVFlowShapeBase::GetPropertyValueByPath(const CString &strPropertyPath,CString &strValue)
{
	CVFlowShapeProperty *pProperty = (CVFlowShapeProperty*)FindByPath(strPropertyPath);

	if (pProperty == NULL)
	{
		return FALSE;
	}

	strValue = pProperty->m_strValue;
	return TRUE;
}

BOOL CVFlowShapeBase::SetData3_UI(const CString &strValue)
{
	m_strData3 = strValue;

	if (!Has_VisioShapeObj())
	{
		return FALSE;
	}	

	try
	{
		m_oShape.put_Data3(strValue);
		SetPropertyValueByID_UI(VFLOW_VISIO_TAG_VALUE,strValue);
		return TRUE;
	}
	catch(...)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前Shape节点(Name=%s;Data1=%s;)设置Data3值(%s)失败."),m_strName,m_strData1,m_strData3);
		return FALSE;
	}
}

BOOL CVFlowShapeBase::GetData3_UI(CString &strValue)
{
	if (!Has_VisioShapeObj())
	{
		return FALSE;
	}	

	try
	{
		strValue = m_oShape.get_Data3();

		if (strValue != m_strData3)
		{
			SetPropertyValueByID_UI(VFLOW_VISIO_TAG_VALUE,strValue);
			m_strData3 = strValue;
		}

		return TRUE;
	}
	catch(...)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前Shape节点(Name=%s;Data1=%s;)设置Data3值(%s)失败."),m_strName,m_strData1,m_strData3);
		return FALSE;
	}
}