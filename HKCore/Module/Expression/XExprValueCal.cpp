//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XExprValueCal.cpp  CXExprValueCal


#include "stdafx.h"
#include "XExprValueCal.h"
#include <math.h>

CXExprValueCal::CXExprValueCal()
{
	//��ʼ������

	//��ʼ����Ա����
	m_pValue1 = NULL;
	m_pValue2 = NULL;
	m_pValueCalRslt = NULL;
	m_pValueStd = NULL;
	m_pError = NULL;
	m_pValueRslt = NULL;
	m_pValueErrorRslt = NULL;
}

CXExprValueCal::~CXExprValueCal()
{
}

long CXExprValueCal::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strModeKey, oNode, m_strMode);
	xml_GetAttibuteValue(pXmlKeys->m_strOptrKey, oNode, m_strOptr);
	xml_GetAttibuteValue(pXmlKeys->m_strCalOptrKey, oNode, m_strCalOptr);
	return 0;
}

long CXExprValueCal::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(pXmlKeys->m_strModeKey, oElement, m_strMode);
	xml_SetAttributeValue(pXmlKeys->m_strOptrKey, oElement, m_strOptr);
	xml_SetAttributeValue(pXmlKeys->m_strCalOptrKey, oElement, m_strCalOptr);
	return 0;
}

long CXExprValueCal::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CXExprBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMode);
		BinarySerializeCalLen(oBinaryBuffer, m_strOptr);
		BinarySerializeCalLen(oBinaryBuffer, m_strCalOptr);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMode);
		BinarySerializeRead(oBinaryBuffer, m_strOptr);
		BinarySerializeRead(oBinaryBuffer, m_strCalOptr);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMode);
		BinarySerializeWrite(oBinaryBuffer, m_strOptr);
		BinarySerializeWrite(oBinaryBuffer, m_strCalOptr);
	}
	return 0;
}

void CXExprValueCal::InitAfterRead()
{
	CXExprBase::InitAfterRead();

	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == XEXPRCLASSID_CXEXPRVALUE1)
		{
			m_pValue1 = (CXExprValue1*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUE2)
		{
			m_pValue2 = (CXExprValue2*)p;
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
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUECALRSLT)
		{
			m_pValueCalRslt = (CXExprValueCalRslt*)p;
		}
	}

	//�����½���ȫ��Ϊ��
	if (m_pValue1 == NULL)
	{
		m_pValue1 = (CXExprValue1*)AddNewChild(new CXExprValue1());
	}

	if (m_pValue2 == NULL)
	{
		m_pValue2 = (CXExprValue2*)AddNewChild(new CXExprValue2());
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

	if (m_pValueCalRslt == NULL)
	{
		m_pValueCalRslt = (CXExprValueCalRslt *)AddNewChild(new CXExprValueCalRslt());
	}
}

BOOL CXExprValueCal::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXExprBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXExprValueCal *p = (CXExprValueCal*)pObj;

	if(m_strMode != p->m_strMode)
	{
		return FALSE;
	}

	if(m_strOptr != p->m_strOptr)
	{
		return FALSE;
	}

	if(m_strCalOptr != p->m_strCalOptr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXExprValueCal::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXExprBase::CopyOwn(pDest);
	CXExprValueCal *p = (CXExprValueCal*)pDest;

	p->m_strMode = m_strMode;
	p->m_strOptr = m_strOptr;
	p->m_strCalOptr = m_strCalOptr;
	return TRUE;
}

CBaseObject* CXExprValueCal::Clone()
{
	CXExprValueCal *p = new CXExprValueCal();
	Copy(p);
	return p;
}

CBaseObject* CXExprValueCal::CloneEx(BOOL bCopyOwn, BOOL bCopyChildren)
{
	CXExprValueCal *p = new CXExprValueCal();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CXExprValueCal::CanPaste(UINT nClassID)
{
	if (nClassID == XEXPRCLASSID_CXEXPRVALUE1)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUE2)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUECALRSLT)
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

CExBaseObject* CXExprValueCal::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
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

	if (strClassID == CXExprXmlRWKeys::CXExprValue1Key())
	{
		m_pValue1 = new CXExprValue1();
		return m_pValue1;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprValue2Key())
	{
		m_pValue2 = new CXExprValue2();
		return m_pValue2;
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

	if (strClassID == CXExprXmlRWKeys::CXExprValueCalRsltKey())
	{
		m_pValueCalRslt = new CXExprValueCalRslt();
		return m_pValueCalRslt;
	}

	return pNew;
}

CExBaseObject* CXExprValueCal::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == XEXPRCLASSID_CXEXPRVALUE1)
	{
		m_pValue1 = new CXExprValue1();
		return m_pValue1;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUE2)
	{
		m_pValue2 = new CXExprValue2();
		return m_pValue2;
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

	if (nClassID == XEXPRCLASSID_CXEXPRVALUECALRSLT)
	{
		m_pValueCalRslt = new CXExprValueCalRslt();
		return m_pValueCalRslt;
	}

	return pNew;
}

// long CXExprValueCal::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	m_pValueStd->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprValueStdKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValue->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::ValueKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pError->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprErrorKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValueRslt->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::ValueRsltKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 
// 	return 0;
// }

long CXExprValueCal::Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	double dValStd = 0;
	double dValue1 = 0;
	double dValue2 = 0;
	double dValueCal = 0;
	double dError = 0;
	double dErrorCal = 0;
	m_nResult = 0;
	CString strValStd, strValue1, strVale2, strError;

	if (! m_pValueStd->Calc(pExprParent, pCalInterface, dValStd, strValStd))
	{
		return 0;
	}

	if (! m_pValue1->Calc(pExprParent, pCalInterface, dValue1, strValue1))
	{
		return 0;
	}

	if (! m_pValue2->Calc(pExprParent, pCalInterface, dValue2, strVale2))
	{
		return 0;
	}

	if (! m_pError->Calc(pExprParent, pCalInterface, dError, strError))
	{
		return 0;
	}

	if (m_strCalOptr == _T("+"))
	{
		dValueCal = dValue1 + dValue2;
	}
	else if (m_strCalOptr == _T("-"))
	{
		dValueCal = dValue1 - dValue2;
	}
	else if (m_strCalOptr == _T("*"))
	{
		dValueCal = dValue1 * dValue2;
	}
	else if (m_strCalOptr == _T("/"))
	{
		dValueCal = dValue1 / dValue2;
	}

	//������1������2������������������������
	CXExprValueCalRslt *pValueCalRslt = GetExprValueCalRslt();
	pValueCalRslt->m_strValue.Format(_T("%.3f"), dValueCal);

	if (m_strMode == _T("abs"))
	{
		dErrorCal = dValueCal - dValStd;

		if (m_strOptr == _T("<="))
		{
			//m_nResult = (dValStd - dError <= dValue) && (dValue <= dValStd + dError);
			//m_nResult = (fabs(dErrorCal) <= dError);
			m_nResult = ( (fabs(dErrorCal)) <= ( 0.0001 + dError) );
		}
		else if (m_strOptr == _T("<"))
		{
			//m_nResult = (dValStd - dError < dValue) && (dValue < dValStd + dError);
			//m_nResult = (fabs(dErrorCal) < dError);
			m_nResult = ( (fabs(dErrorCal)) < ( 0.0001 + dError) );
		}

		//strValueErrorCal.Format(_T("%.3f"), dErrorCal);
	}
	else
	{
		dError = dError / 100.0;
		//2024-1-3��Ϊɶ����Ϊ0���в��ϸ�ע�͵�
// 		if (dValueCal == 0)
// 		{
// 			m_nResult = 0;
// 			dErrorCal = 100.0;
// 		}
// 		else
		{
			if (dValStd == 0.0)
			{
				dErrorCal = -100.0;
				m_nResult = 0;
			}
			else
			{
				//�ٷֱ����
				dErrorCal = dValueCal / dValStd/* * 100*/;
				double dErrorCalEx = fabs(dErrorCal);

				if (m_strOptr == _T("<="))
				{
					m_nResult = (dErrorCalEx <= dError);  
				}
				else if (m_strOptr == _T("<"))
				{
					m_nResult = (dErrorCalEx < dError);
				}

				dErrorCal = dErrorCal * 100.0; 
			}
		}

		//strValueErrorCal.Format(_T("%.6f"), dErrorCal);
	}

	//���������������������ݶ���
	CXExprValueErrorRslt *pValueErrorRslt = GetExprValueErrorRslt();

	if (pValueErrorRslt->IsValueUint_ms() && m_strMode == _T("abs"))
	{
		dErrorCal *= 1000;
	}

	if (strValue1 == _T("δ����") || strVale2 == _T("δ����"))
	{
		dErrorCal = -100.0;
		m_nResult = 0;
	}

	if (dValStd == 0.0 || strValue1 == _T("δ����") || strVale2 == _T("δ����"))
	{
		pValueErrorRslt->m_strValue = _T("--");
	}
	else
	{
		pValueErrorRslt->m_strValue.Format(_T("%.3f"), dErrorCal);;
	}

	//��������󣬽�����󶨻ض�Ӧ�Ĳ���
	CXExprValueRslt* pRslt = GetExprValueRslt();
	pRslt->m_strValue.Format(_T("%d"), m_nResult);
	pRslt->ExprRsltBind(pExprParent, pCalInterface);

	pValueErrorRslt->ExprRsltBind(pExprParent, pCalInterface);
	pValueCalRslt->ExprRsltBind(pExprParent, pCalInterface);

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

void CXExprValueCal::ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
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

	if (m_pValueCalRslt != NULL)
	{
		m_pValueCalRslt->ExprRsltBind(pExprParent, pCalInterface);
	}
}

void CXExprValueCal::GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues)
{
	if (m_pValue1 != NULL)
	{
		m_pValue1->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValue2 != NULL)
	{
		m_pValue2->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueCalRslt != NULL)
	{
		m_pValueCalRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
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

BOOL CXExprValueCal::GetValueName(const CString &strID, CString &strName)
{
	if (m_pValue1 != NULL)
	{
		if (m_pValue1->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	if (m_pValue2 != NULL)
	{
		if (m_pValue2->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	if (m_pValueCalRslt != NULL)
	{
		if (m_pValueCalRslt->GetValueName(strID, strName))
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

void CXExprValueCal::GetRsltExprValues_ExprMode(const CString &strMode, CExBaseList *pRsltExprValues)
{
	if (! ExprModeValid(strMode))
	{
		return;
	}

	CDvmValue *pValue = new CDvmValue;
	pValue->m_strID = _T("ErrorLogic");
	pValue->m_strName = _T("����ж��߼�");
	pRsltExprValues->AddNewChild(pValue, TRUE);

	if (strMode == _T("abs"))
	{
		pValue->m_strValue = _T("�������");
	}
	else if (strMode == _T("real"))
	{
		pValue->m_strValue = _T("�ٷֱ����");
	}
	else if (strMode == _T("or"))
	{
		pValue->m_strValue = _T("������� or �ٷֱ����");
	}
	else if (strMode == _T("and"))
	{
		pValue->m_strValue = _T("������� & �ٷֱ����");
	}
	else if (strMode == _T("combined"))
	{
		pValue->m_strValue = _T("������");
	}
}

//��ȡ�������1
CXExprValue1* CXExprValueCal::GetExprValue1()
{
	if (m_pValue1 == NULL)
	{
		m_pValue1 = new CXExprValue1();
		AddNewChild(m_pValue1);
	}

	return m_pValue1;
}

//��ȡ�������2
CXExprValue2* CXExprValueCal::GetExprValue2()
{
	if (m_pValue2 == NULL)
	{
		m_pValue2 = new CXExprValue2();
		AddNewChild(m_pValue2);
	}

	return m_pValue2;
}

//��ȡ�������1��������2������������
CXExprValueCalRslt* CXExprValueCal::GetExprValueCalRslt()
{
	if (m_pValueCalRslt == NULL)
	{
		m_pValueCalRslt = new CXExprValueCalRslt();
		AddNewChild(m_pValueCalRslt);
	}

	return m_pValueCalRslt;
}

//��ȡ��׼����
CXExprValueStd* CXExprValueCal::GetExprValueStd()
{
	if (m_pValueStd == NULL)
	{
		m_pValueStd = new CXExprValueStd();
		AddNewChild(m_pValueStd);
	}

	return m_pValueStd;
}

//��ȡ�����
CXExprValueError* CXExprValueCal::GetExprValueError()
{
	if (m_pError == NULL)
	{
		m_pError = new CXExprValueError();
		AddNewChild(m_pError);
	}

	return m_pError;
}

//��ȡ���ʽ���������ϸ� or ���ϸ�
CXExprValueRslt* CXExprValueCal::GetExprValueRslt()
{
	if (m_pValueRslt == NULL)
	{
		m_pValueRslt = new CXExprValueRslt();
		AddNewChild(m_pValueRslt);
	}

	return m_pValueRslt;
}

//��ȡ���ֵ������������
CXExprValueErrorRslt* CXExprValueCal::GetExprValueErrorRslt()
{
	if (m_pValueErrorRslt == NULL)
	{
		m_pValueErrorRslt = new CXExprValueErrorRslt();
		AddNewChild(m_pValueErrorRslt);
	}

	return m_pValueErrorRslt;
}