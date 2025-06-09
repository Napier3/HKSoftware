//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XExprError.cpp  CXExprError


#include "stdafx.h"
#include "XExprError.h"
#include <math.h>

CXExprError::CXExprError()
{
	//��ʼ������

	//��ʼ����Ա����
	m_pValue = NULL;
	m_pValueStd = NULL;
	m_pError = NULL;
	m_pValueRslt = NULL;
	m_pValueErrorRslt = NULL;
}

CXExprError::~CXExprError()
{
}

long CXExprError::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strModeKey, oNode, m_strMode);
	xml_GetAttibuteValue(pXmlKeys->m_strOptrKey, oNode, m_strOptr);
	return 0;
}

long CXExprError::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(pXmlKeys->m_strModeKey, oElement, m_strMode);
	xml_SetAttributeValue(pXmlKeys->m_strOptrKey, oElement, m_strOptr);
	return 0;
}

long CXExprError::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CXExprBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMode);
		BinarySerializeCalLen(oBinaryBuffer, m_strOptr);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMode);
		BinarySerializeRead(oBinaryBuffer, m_strOptr);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMode);
		BinarySerializeWrite(oBinaryBuffer, m_strOptr);
	}
	return 0;
}

void CXExprError::InitAfterRead()
{
	CXExprBase::InitAfterRead();

	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == XEXPRCLASSID_CXEXPRVALUE)
		{
			m_pValue = (CXExprValue*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUESTD)
		{
			m_pValueStd = (CXExprValueStd*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
		{
			m_pValueRslt = (CXExprValueRslt*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUEERROR)
		{
			m_pError = (CXExprValueError*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORRSLT)
		{
			m_pValueErrorRslt = (CXExprValueErrorRslt*)p;
		}
	}

	//�����½���ȫ��Ϊ��
	if (m_pValue == NULL)
	{
		m_pValue = (CXExprValue*)AddNewChild(new CXExprValue());
	}

	if (m_pValueStd == NULL)
	{
		m_pValueStd = (CXExprValueStd*)AddNewChild(new CXExprValueStd());
	}

	if (m_pError == NULL)
	{
		m_pError = (CXExprValueError*)AddNewChild(new CXExprValueError());
	}

	if (m_pValueErrorRslt == NULL)
	{
		m_pValueErrorRslt = (CXExprValueErrorRslt *)AddNewChild(new CXExprValueErrorRslt());
	}
}

BOOL CXExprError::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXExprBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXExprError *p = (CXExprError*)pObj;

	if(m_strMode != p->m_strMode)
	{
		return FALSE;
	}

	if(m_strOptr != p->m_strOptr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXExprError::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXExprBase::CopyOwn(pDest);
	CXExprError *p = (CXExprError*)pDest;

	p->m_strMode = m_strMode;
	p->m_strOptr = m_strOptr;
	return TRUE;
}

CBaseObject* CXExprError::Clone()
{
	CXExprError *p = new CXExprError();
	Copy(p);
	return p;
}

CBaseObject* CXExprError::CloneEx(BOOL bCopyOwn, BOOL bCopyChildren)
{
	CXExprError *p = new CXExprError();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CXExprError::CanPaste(UINT nClassID)
{
	if (nClassID == XEXPRCLASSID_CXEXPRVALUE)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUESTD)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERROR)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORRSLT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXExprError::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;


	if (strClassID == CXExprXmlRWKeys::CXExprValueStdKey())
	{
		m_pValueStd = new CXExprValueStd();
		return m_pValueStd;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprValueErrorKey())
	{
		m_pError = new CXExprValueError();
		return m_pError;
	}

	if (strClassID == CXExprXmlRWKeys::ValueKey())
	{
		m_pValue = new CXExprValue();
		return m_pValue;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprValueRsltKey())
	{
		m_pValueRslt = new CXExprValueRslt();
		return m_pValueRslt;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprValueErrorRsltKey())
	{
		m_pValueErrorRslt = new CXExprValueErrorRslt();
		return m_pValueErrorRslt;
	}


	return pNew;
}

CExBaseObject* CXExprError::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == XEXPRCLASSID_CXEXPRVALUE)
	{
		m_pValue = new CXExprValue();
		return m_pValue;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERROR)
	{
		m_pError = new CXExprValueError();
		return m_pError;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUESTD)
	{
		m_pValueStd = new CXExprValueStd();
		return m_pValueStd;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
	{
		m_pValueRslt = new CXExprValueRslt();
		return m_pValueRslt;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORRSLT)
	{
		m_pValueErrorRslt = new CXExprValueErrorRslt();
		return m_pValueErrorRslt;
	}

	return pNew;
}

// long CXExprError::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	m_pValueStd->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprValueStdKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValue->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::ValueKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pError->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprErrorKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValueRslt->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::ValueRsltKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 
// 	return 0;
// }

long CXExprError::Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	double dValStd = 0;
	double dValue = 0;
	double dError = 0;
	double dCal = 0;
	m_nResult = 0;
	CString strValStd, strValue, strError;

	if (! m_pValueStd->Calc(pExprParent, pCalInterface, dValStd, strValStd))
	{
		return 0;
	}

	if (! m_pValue->Calc(pExprParent, pCalInterface, dValue, strValue))
	{
		return 0;
	}

	if (! m_pError->Calc(pExprParent, pCalInterface, dError, strError))
	{
		return 0;
	}

	CString strValueErrorCal;

	if (m_strMode == _T("abs"))
	{
		dCal = dValue - dValStd;

		if (m_strOptr == _T("<="))
		{
			//m_nResult = (dValStd - dError <= dValue) && (dValue <= dValStd + dError);
			//m_nResult = (fabs(dCal) <= dError);
			m_nResult = ( (fabs(dCal)) <= (0.0001 + dError) );
		}
		else if (m_strOptr == _T("<"))
		{
			//m_nResult = (dValStd - dError < dValue) && (dValue < dValStd + dError);
			//m_nResult = (fabs(dCal) < dError);
			m_nResult = ( (fabs(dCal)) < (0.0001 + dError) );
		}

		//strValueErrorCal.Format(_T("%.3f"), dCal);
	}
	else
	{
		dError = dError / 100.0;
		if (dValue == 0)
		{
			m_nResult = 0;
			dCal = 100.0;
		}
		else
		{
			if (dValStd == 0.0)
			{
				dCal = -100.0;
				m_nResult = 0;
			}
			else
			{
				dCal = (dValue - dValStd) / dValStd/* * 100*/;
				double dCalEx = fabs(dCal);

				if (m_strOptr == _T("<="))
				{
					m_nResult = (dCalEx <= dError); 
				}
				else if (m_strOptr == _T("<"))
				{
					m_nResult = (dCalEx < dError);
				}

				dCal = dCal * 100.0;
			}
		}

		//strValueErrorCal.Format(_T("%.6f"), dCal);
	}
	
	//���������������������ݶ���
	CXExprValueErrorRslt *pValueErrorRslt = GetExprValueErrorRslt();

	if (pValueErrorRslt->IsValueUint_ms() && m_strMode == _T("abs"))
	{
		dCal *= 1000;
	}

	if (strValue == _T("δ����"))
	{
		dCal = -100.0;
		m_nResult = 0;
	}

	if (dValStd == 0.0 || strValue == _T("δ����"))
	{
		pValueErrorRslt->m_strValue = _T("--");
	}
	else
	{
		pValueErrorRslt->m_strValue.Format(_T("%.3f"), dCal);
	}

	//��������󣬽�����󶨻ض�Ӧ�Ĳ���
	CXExprValueRslt* pRslt = GetExprValueRslt();
	pRslt->m_strValue.Format(_T("%d"), m_nResult);
	pRslt->ExprRsltBind(pExprParent, pCalInterface);

// 	if (m_strMode == _T("real"))
// 	{
// 		pValueErrorRslt->SetRelCalVal(TRUE);
// 	}
// 	else
// 	{
// 		pValueErrorRslt->SetRelCalVal(FALSE);
// 	}

	pValueErrorRslt->ExprRsltBind(pExprParent, pCalInterface);

	//��׼ֵ��Ҳ��Ҫ�����Ϊ��׼ֵ���ܴӽ��������
	if (m_pValueStd != NULL)
	{
		m_pValueStd->ExprRsltBind(pExprParent, pCalInterface);
	}

	//�������ݣ���Լ��Ҳ��Ҫ�ذ�  2023-8-29
	//���ڶ���ʱ����ԣ��ײ����͵�������sΪ��λ�����뵽word��������msΪ��λ��
	//�˴����ܽ�����Լ��ذ󣬷������뵽word�е����ݽ���ʧ�档2023-8-31
// 	if (m_pValue != NULL)
// 	{
// 		m_pValue->ExprRsltBind(pExprParent, pCalInterface);
// 	}

	return m_nResult;
}

void CXExprError::ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	if (m_pValueRslt != NULL)
	{
		m_pValueRslt->ExprRsltBind(pExprParent, pCalInterface);
	}

	//��׼ֵ��Ҳ��Ҫ�����Ϊ��׼ֵ���ܴӽ��������
	if (m_pValueStd != NULL)
	{
		m_pValueStd->ExprRsltBind(pExprParent, pCalInterface);
	}

	//�������ݣ���Լ��Ҳ��Ҫ�ذ�  2023-8-29
	//���ڶ���ʱ����ԣ��ײ����͵�������sΪ��λ�����뵽word��������msΪ��λ��
	//�˴����ܽ�����Լ��ذ󣬷������뵽word�е����ݽ���ʧ�档2023-8-31
// 	if (m_pValue != NULL)
// 	{
// 		m_pValue->ExprRsltBind(pExprParent, pCalInterface);
// 	}

	if (m_pValueErrorRslt != NULL)
	{
// 		if (m_strMode == _T("real"))
// 		{
// 			m_pValueErrorRslt->SetRelCalVal(TRUE);
// 		}
// 		else
// 		{
// 			m_pValueErrorRslt->SetRelCalVal(FALSE);
// 		}

		m_pValueErrorRslt->ExprRsltBind(pExprParent, pCalInterface);
	}
}

void CXExprError::GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues)
{
	if (m_pValue != NULL)
	{
		m_pValue->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueStd != NULL)
	{
		m_pValueStd->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pError != NULL)
	{
		m_pError->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueRslt != NULL)
	{
		m_pValueRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueErrorRslt != NULL)
	{
		m_pValueErrorRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	GetRsltExprValues_ExprMode(m_strMode, pRsltExprValues);
}

BOOL CXExprError::GetValueName(const CString &strID, CString &strName)
{
	if (m_pValue != NULL)
	{
		if (m_pValue->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	if (m_pValueStd != NULL)
	{
		if (m_pValueStd->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	if (m_pError != NULL)
	{
		if (m_pError->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	if (m_pValueRslt != NULL)
	{
		if (m_pValueRslt->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	if (m_pValueErrorRslt != NULL)
	{
		if (m_pValueErrorRslt->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	return FALSE;
}

//��ȡ�������
CXExprValue* CXExprError::GetExprValue()
{
	if (m_pValue == NULL)
	{
		m_pValue = new CXExprValue();
		AddNewChild(m_pValue);
	}

	return m_pValue;
}

//��ȡ��׼����
CXExprValueStd* CXExprError::GetExprValueStd()
{
	if (m_pValueStd == NULL)
	{
		m_pValueStd = new CXExprValueStd();
		AddNewChild(m_pValueStd);
	}

	return m_pValueStd;
}

//��ȡ�����
CXExprValueError* CXExprError::GetExprValueError()
{
	if (m_pError == NULL)
	{
		m_pError = new CXExprValueError();
		AddNewChild(m_pError);
	}

	return m_pError;
}

//��ȡ���ʽ���������ϸ� or ���ϸ�
CXExprValueRslt* CXExprError::GetExprValueRslt()
{
	if (m_pValueRslt == NULL)
	{
		m_pValueRslt = new CXExprValueRslt();
		AddNewChild(m_pValueRslt);
	}

	return m_pValueRslt;
}

//��ȡ���ֵ������������
CXExprValueErrorRslt* CXExprError::GetExprValueErrorRslt()
{
	if (m_pValueErrorRslt == NULL)
	{
		m_pValueErrorRslt = new CXExprValueErrorRslt();
		AddNewChild(m_pValueErrorRslt);
	}

	return m_pValueErrorRslt;
}