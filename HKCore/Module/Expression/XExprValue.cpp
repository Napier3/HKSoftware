//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XExprValue.cpp  CXExprValue


#include "stdafx.h"
#include "XExprValue.h"

CXExprValue::CXExprValue()
{
	//��ʼ������
	m_bRelCalVal = FALSE;
	//��ʼ����Ա����
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

	//����ʱ����Ĳ����������msΪ��λ������ʱͳһת����s�����м��㣬����ʱ�����»����ms
	//�����ڴ˴����е�λת������Ϊ�ڼ���ʱ��������������Լ������Լ��ת�����ᵼ�¾��ȶ�ʧ  2023-8-8
// 	if (strUnit == _T("ms"))
// 	{
// 		double dValue = CString_To_double(m_strValue);
// 		dValue = dValue*1000;
// 		m_strValue.Format(_T("%.3f"), dValue);
// 	}

	//�ڼ���ʱ����*100%
// 	if (m_bRelCalVal)
// 	{
// 		//������ļ�������*100%��
// 		double dValue = CString_To_double(m_strValue);
// 		dValue = dValue * 100;
// 		m_strValue.Format(_T("%.3f"), dValue);
// 	}	
	
	if (! m_strType.IsEmpty())
	{
		pCalInterface->ExprRsltBind(pExprParent, m_strType, m_strValueID, m_strValueName, m_strItemPath, m_strValue);
	}
}

//2023-11-8 �����β� CString &strValRet�����ڷ����ַ�����������硰δ������
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
			//��������ֵ������Ϊreport������Ϊ��Ҫ���
			//��ˣ��Ҳ��������������CValue�������ֱ��ȡֵ
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

	if (m_strValueType == _T("utc_time")
		|| m_strValueType == _T("sys_time")
		|| m_strValueType == _T("$t"))
	{
		//UTC_TIME����������Լ
		m_strValue.Format(_T("%.0f"), dValRet);  //������ַ���ֵ������Լ
	}

	//����ʱ����Ĳ����������msΪ��λ����ͳһת����s�����м���
	//�˴���Ҫע����ǣ����ڴ�datasetȡ������ֵ���Ѿ����ݶ�ֵ�ĵ�λ�����й�s->ms��ת�������m_strValueUnitǧ������ms
	if (strUnit == _T("ms"))
	{
		dValRet = dValRet/1000;
	}

	//���ص�double���ܱ�����λ��Ч���֡����ڶ���ʱ����ԣ�����ֵ�Ͷ���ֵ����s�������ms��������ֵ������λ��Ч���֣��ᵼ�����ʧ��
	double dTemp = dValRet;
	dTemp = ((int)(dTemp*1000+0.5))/1000.0;  //double������λС��
	m_strValue.Format(_T("%.3f"), dTemp);  //������ַ���ֵ������Լ
	//dValRet = CString_To_double(m_strValue);
	//CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("%f"), dValRet);

	return bRet;
}

#include "../DataMngr/DvmValue.h"
//�˴����ݽ�����pReportValues��ֻ�����pExprParent�����Ŀ��
//��ˣ���CXExprValue�����·����Ϊ��ʱ�����ܴ�pReportValues���ҽ��
void CXExprValue::GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues)
{
	if (! m_strItemPath.IsEmpty())
	{
		//�����Ŀ·���Ľ�����������⴦��
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
		//ͬһ�����Ƶģ�ֻ���һ�������Ҫ��֤��������Ĳ��ֺ�TestMacro�еĲ������Ʋ��ظ�
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
			//�����ظ����ԣ�����ж��м�¼��m_strValue�������һ������ġ�
			//��ˣ��˴�������ô����.2023-8-29
			//if (pValue->m_strValue.IsEmpty())
			{
				pValue->m_strValue = pRsltValue->m_strValue;
			}
		}
	}
	//pValue->m_strID = ?  ��ʱ�������ID����Ҫʱ������
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