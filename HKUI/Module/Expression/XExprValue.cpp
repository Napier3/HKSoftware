//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprValue.cpp  CXExprValue


#include "stdafx.h"
#include "XExprValue.h"

CXExprValue::CXExprValue()
{
	//初始化属性
	m_bRelCalVal = FALSE;
	//初始化成员变量
}

CXExprValue::~CXExprValue()
{
}

long CXExprValue::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strValueIDKey, oNode, m_strValueID);
	xml_GetAttibuteValue(pXmlKeys->m_strValueNameKey, oNode, m_strValueName);
	xml_GetAttibuteValue(pXmlKeys->m_strValueUnitKey, oNode, m_strValueUnit);
	xml_GetAttibuteValue(pXmlKeys->m_strValueTypeKey, oNode, m_strValueType);
	xml_GetAttibuteValue(pXmlKeys->m_strItemPathKey, oNode, m_strItemPath);
	return 0;
}

long CXExprValue::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strValueIDKey, oElement, m_strValueID);
	xml_SetAttributeValue(pXmlKeys->m_strValueNameKey, oElement, m_strValueName);
	xml_SetAttributeValue(pXmlKeys->m_strValueUnitKey, oElement, m_strValueUnit);
	xml_SetAttributeValue(pXmlKeys->m_strValueTypeKey, oElement, m_strValueType);
	xml_SetAttributeValue(pXmlKeys->m_strItemPathKey, oElement, m_strItemPath);
	return 0;
}

long CXExprValue::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strValueID);
		BinarySerializeCalLen(oBinaryBuffer, m_strValueName);
		BinarySerializeCalLen(oBinaryBuffer, m_strValueUnit);
		BinarySerializeCalLen(oBinaryBuffer, m_strValueType);
		BinarySerializeCalLen(oBinaryBuffer, m_strItemPath);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strValueID);
		BinarySerializeRead(oBinaryBuffer, m_strValueName);
		BinarySerializeRead(oBinaryBuffer, m_strValueUnit);
		BinarySerializeRead(oBinaryBuffer, m_strValueType);
		BinarySerializeRead(oBinaryBuffer, m_strItemPath);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strValueID);
		BinarySerializeWrite(oBinaryBuffer, m_strValueName);
		BinarySerializeWrite(oBinaryBuffer, m_strValueUnit);
		BinarySerializeWrite(oBinaryBuffer, m_strValueType);
		BinarySerializeWrite(oBinaryBuffer, m_strItemPath);
	}
	return 0;
}

BOOL CXExprValue::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXExprValue *p = (CXExprValue*)pObj;

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_strValueID != p->m_strValueID)
	{
		return FALSE;
	}

	if(m_strValueName != p->m_strValueName)
	{
		return FALSE;
	}

	if(m_strValueUnit != p->m_strValueUnit)
	{
		return FALSE;
	}

	if(m_strValueType != p->m_strValueType)
	{
		return FALSE;
	}

	if(m_strItemPath != p->m_strItemPath)
	{
		
		return FALSE;
	}
	return TRUE;
}

BOOL CXExprValue::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXExprValue *p = (CXExprValue*)pDest;

	p->m_strType = m_strType;
	p->m_strValue = m_strValue;
	p->m_strValueID = m_strValueID;
	p->m_strValueName = m_strValueName;
	p->m_strValueUnit = m_strValueUnit;
	p->m_strValueType = m_strValueType;
	p->m_strItemPath = m_strItemPath;
	return TRUE;
}

CBaseObject* CXExprValue::Clone()
{
	CXExprValue *p = new CXExprValue();
	Copy(p);
	return p;
}

BOOL CXExprValue::IsValueUint_ms()
{
	CString strUnit = m_strValueUnit;
	strUnit.MakeLower();

	if (strUnit == _T("ms"))
	{
		return TRUE;
	}

	return FALSE;
}

void CXExprValue::ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
// 	CString strUnit = m_strValueUnit;
// 	strUnit.MakeLower();

	//对于时间类的参数，如果是ms为单位。计算时统一转换成s来进行计算，回填时，重新换算成ms
	//不能在此处进行单位转换。因为在计算时，进行了数据修约。先修约再转换，会导致精度丢失  2023-8-8
// 	if (strUnit == _T("ms"))
// 	{
// 		double dValue = CString_To_double(m_strValue);
// 		dValue = dValue*1000;
// 		m_strValue.Format(_T("%.3f"), dValue);
// 	}

	//在计算时，就*100%
// 	if (m_bRelCalVal)
// 	{
// 		//相对误差的计算结果，*100%。
// 		double dValue = CString_To_double(m_strValue);
// 		dValue = dValue * 100;
// 		m_strValue.Format(_T("%.3f"), dValue);
// 	}	
	
	if (! m_strType.IsEmpty())
	{
		pCalInterface->ExprRsltBind(pExprParent, m_strType, m_strValueID, m_strValueName, m_strItemPath, m_strValue);
	}
}

//2023-11-8 新增形参 CString &strValRet。用于返回字符串结果，例如“未动作”
BOOL CXExprValue::Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, double &dValRet, CString &strValRet)
{
	CString strUnit = m_strValueUnit;
	strUnit.MakeLower();
	BOOL bRet = FALSE;

	if (m_strType == _T("number"))
	{
		dValRet = CString_To_double(m_strValue);
		bRet = TRUE;
	}
	else
	{
		bRet = pCalInterface->ExprCal(pExprParent, m_strType, m_strValueID, m_strItemPath, dValRet, strValRet, m_strValueType);

		if (m_strType == _T("report"))
		{
			//对于整定值，设置为report，是因为需要回填。
			//因此，找不到结果报告数据CValue，则可以直接取值
			if (! bRet)
			{
				if (! m_strValue.IsEmpty())
				{
					dValRet = CString_To_double(m_strValue);
					bRet = TRUE;
				}
			}
		}
	}

	//对于时间类的参数，如果是ms为单位。则统一转换成s来进行计算
	//此处需要注意的是，对于从dataset取回来的值，已经根据定值的单位，进行过s->ms的转换，因此m_strValueUnit千万不能填ms
	if (strUnit == _T("ms"))
	{
		dValRet = dValRet/1000;
	}

	//返回的double不能保留三位有效数字。对于动作时间测试，整定值和动作值都是s。误差是ms。若动作值保留三位有效数字，会导致误差失真
	double dTemp = dValRet;

	if (m_strValueType != _T("utc_time"))
	{
		//UTC_TIME。已经转为ms。此处再这样处理会超限
	dTemp = ((int)(dTemp*1000+0.5))/1000.0;  //double保留三位小数
	}
	
	m_strValue.Format(_T("%.3f"), dTemp);  //仅针对字符串值进行修约
	//dValRet = CString_To_double(m_strValue);
	//CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("%f"), dValRet);

	return bRet;
}

#include "../DataMngr/DvmValue.h"
//此处传递进来的pReportValues。只是针对pExprParent这个项目的
//因此，当CXExprValue的相对路径不为空时，不能从pReportValues查找结果
void CXExprValue::GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues)
{
	if (! m_strItemPath.IsEmpty())
	{
		//相对项目路径的结果参数，另外处理
		pListXExprValues->AddTail(this);
		return;
	}

	if (m_strType.IsEmpty())
	{
		return;
	}

	CString strName;

	if (m_strType != _T("number"))
	{
		if (m_strValueName.IsEmpty())
		{
			pCalInterface->ExprGetValueAttr(pExprParent, m_strType, m_strValueID, m_strItemPath, m_strValueName, _T("name"));
		}
	}
	
	strName = m_strValueName;

	if (pRsltExprValues->FindByName(strName) != NULL)
	{
		//同一个名称的，只添加一个。因此要保证界面参数的部分和TestMacro中的参数名称不重复
		return;
	}

	CDvmValue *pValue = new CDvmValue;
	pRsltExprValues->AddNewChild(pValue);
	pValue->m_strValue = m_strValue;

	if (m_strType == _T("report"))
	{
		CDvmValue *pRsltValue = (CDvmValue *)pReportValues->FindByID(m_strValueID);

		if (pRsltValue != NULL)
		{
			//对于重复测试，结果判断中记录的m_strValue，是最后一次试验的。
			//因此，此处不能这么处理.2023-8-29
			//if (pValue->m_strValue.IsEmpty())
			{
				pValue->m_strValue = pRsltValue->m_strValue;
			}
		}
	}
	//pValue->m_strID = ?  暂时不存参数ID，需要时再新增
	pValue->m_strName = strName;
}

void CXExprValue::GetRsltExprValues_RelPath(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues)
{
	CString strItemPath = m_strItemPath;
	m_strItemPath.Empty();
	GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, NULL);
	m_strItemPath = strItemPath;
}

BOOL CXExprValue::GetValueName(const CString &strID, CString &strName)
{
	if (strID == m_strValueID)
	{
		strName = m_strValueName;
		return TRUE;
	}

	return FALSE;
}