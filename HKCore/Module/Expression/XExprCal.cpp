//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XExprCal.cpp  CXExprCal


#include "stdafx.h"
#include "XExprCal.h"
#include "../../AutoTest/Module/GuideBook/GbItemBase.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
CXExprQueryMax::CXExprQueryMax()
{
	//��ʼ������
	//��ʼ����Ա����
}

CXExprQueryMax::~CXExprQueryMax()
{
}

long CXExprQueryMax::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValueSrcIDKey, oNode, m_strValueSrcID);
	return 0;
}

long CXExprQueryMax::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	xml_SetAttributeValue(pXmlKeys->m_strValueSrcIDKey, oElement, m_strValueSrcID);

	return 0;
}

long CXExprQueryMax::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strValueSrcID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strValueSrcID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strValueSrcID);
	}
	return 0;
}

BOOL CXExprQueryMax::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXExprQueryMax *p = (CXExprQueryMax*)pObj;

	if(m_strValueSrcID != p->m_strValueSrcID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXExprQueryMax::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXExprQueryMax *p = (CXExprQueryMax*)pDest;

	p->m_strValueSrcID = m_strValueSrcID;

	return TRUE;
}

CBaseObject* CXExprQueryMax::Clone()
{
	CXExprQueryMax *p = new CXExprQueryMax();
	Copy(p);
	return p;
}

BOOL CXExprQueryMax::CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes, double &dValRet)
{
	CExBaseList oReportsForCal;
	pCalInterface->ExprCal_GetReportsForCal(&oReportsForCal, nCurrTestTimes, nRepeatTimes, pExprParent);
	BOOL bRet = pCalInterface->ExprCal_Max(&oReportsForCal, m_strValueSrcID, dValRet);
	oReportsForCal.RemoveAll();
	return bRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
CXExprQueryMin::CXExprQueryMin()
{
	//��ʼ������
	//��ʼ����Ա����
}

CXExprQueryMin::~CXExprQueryMin()
{
}

long CXExprQueryMin::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValueSrcIDKey, oNode, m_strValueSrcID);
	return 0;
}

long CXExprQueryMin::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	xml_SetAttributeValue(pXmlKeys->m_strValueSrcIDKey, oElement, m_strValueSrcID);

	return 0;
}

long CXExprQueryMin::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strValueSrcID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strValueSrcID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strValueSrcID);
	}
	return 0;
}

BOOL CXExprQueryMin::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXExprQueryMin *p = (CXExprQueryMin*)pObj;

	if(m_strValueSrcID != p->m_strValueSrcID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXExprQueryMin::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXExprQueryMin *p = (CXExprQueryMin*)pDest;

	p->m_strValueSrcID = m_strValueSrcID;

	return TRUE;
}

CBaseObject* CXExprQueryMin::Clone()
{
	CXExprQueryMin *p = new CXExprQueryMin();
	Copy(p);
	return p;
}

BOOL CXExprQueryMin::CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes, double &dValRet)
{
	CExBaseList oReportsForCal;
	pCalInterface->ExprCal_GetReportsForCal(&oReportsForCal, nCurrTestTimes, nRepeatTimes, pExprParent);
	
	BOOL bRet = pCalInterface->ExprCal_Min(&oReportsForCal, m_strValueSrcID, dValRet);
	oReportsForCal.RemoveAll();
	return bRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
CXExprCal::CXExprCal()
{
	//��ʼ������
	m_pQueryMin = NULL;
	m_pQueryMax = NULL;
	//��ʼ����Ա����
}

CXExprCal::~CXExprCal()
{
}

long CXExprCal::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValueDstIDKey, oNode, m_strValueDstID);
	xml_GetAttibuteValue(pXmlKeys->m_strValueNameKey, oNode, m_strValueName);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	
	return 0;
}

long CXExprCal::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	xml_SetAttributeValue(pXmlKeys->m_strValueDstIDKey, oElement, m_strValueDstID);
	xml_SetAttributeValue(pXmlKeys->m_strValueNameKey, oElement, m_strValueName);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	
	return 0;
}

long CXExprCal::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strValueDstID);
		BinarySerializeCalLen(oBinaryBuffer, m_strValueName);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strValueDstID);
		BinarySerializeRead(oBinaryBuffer, m_strValueName);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strValueDstID);
		BinarySerializeWrite(oBinaryBuffer, m_strValueName);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
	}
	return 0;
}

void CXExprCal::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == XEXPRCLASSID_CXEXPRQUERYMIN)
		{
			m_pQueryMin = (CXExprQueryMin*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRQUERYMAX)
		{
			m_pQueryMax = (CXExprQueryMax*)p;
		}
	}
}

BOOL CXExprCal::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXExprCal *p = (CXExprCal*)pObj;

	if(m_strValueDstID != p->m_strValueDstID)
	{
		return FALSE;
	}

	if(m_strValueName != p->m_strValueName)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXExprCal::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXExprCal *p = (CXExprCal*)pDest;

	p->m_strValueDstID = m_strValueDstID;
	p->m_strValueName = m_strValueName;
	p->m_strValue = m_strValue;
	return TRUE;
}

CBaseObject* CXExprCal::Clone()
{
	CXExprCal *p = new CXExprCal();
	Copy(p);
	return p;
}

CBaseObject* CXExprCal::CloneEx(BOOL bCopyOwn, BOOL bCopyChildren)
{
	CXExprCal *p = new CXExprCal();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CXExprCal::CanPaste(UINT nClassID)
{
	if (nClassID == XEXPRCLASSID_CXEXPRQUERYMIN)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRQUERYMAX)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXExprCal::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	if (strClassID == CXExprXmlRWKeys::CXExprQueryMaxKey())
	{
		m_pQueryMax = new CXExprQueryMax();
		return m_pQueryMax;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprQueryMinKey())
	{
		m_pQueryMin = new CXExprQueryMin();
		return m_pQueryMin;
	}

	return pNew;
}

CExBaseObject* CXExprCal::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == XEXPRCLASSID_CXEXPRQUERYMAX)
	{
		m_pQueryMax = new CXExprQueryMax();
		return m_pQueryMax;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRQUERYMIN)
	{
		m_pQueryMin = new CXExprQueryMin();
		return m_pQueryMin;
	}

	return pNew;
}

void CXExprCal::ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	pCalInterface->ExprRsltBind(pExprParent, _T("report"), m_strValueDstID, m_strValueName, _T(""), m_strValue);
}

BOOL CXExprCal::CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes)
{
	if (nCurrTestTimes < nRepeatTimes)
	{
		//�ظ����Եģ�û��ȫ�����꣬�����н�����㡣
		//������һ�β��ԡ����㱨�档���н������
		return TRUE;
	}

	//Ŀǰֻ֧������ģʽ�������ֵ������Сֵ��
	//������ģʽ������ͬʱ֧��
	BOOL bRet = FALSE;
	double dValRet = 0.0;

	if (m_pQueryMax != NULL)
	{
		bRet = m_pQueryMax->CalcEx(pExprParent, pCalInterface, nCurrTestTimes, nRepeatTimes, dValRet);
	}

	if (m_pQueryMin != NULL)
	{
		bRet = m_pQueryMin->CalcEx(pExprParent, pCalInterface, nCurrTestTimes, nRepeatTimes, dValRet);
	}

	if (bRet)
	{
		m_strValue.Format(_T("%.3f"), dValRet);
	}
	else
	{
		m_strValue = _T("--");
	}

	return bRet;
}

void CXExprCal::GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues)
{
	if (pRsltExprValues->FindByName(m_strValueName) != NULL)
	{
		//ͬһ�����Ƶģ�ֻ���һ�������Ҫ��֤��������Ĳ��ֺ�TestMacro�еĲ������Ʋ��ظ�
		return;
	}

	CDvmValue *pRsltValue = (CDvmValue *)pReportValues->FindByID(m_strValueDstID);

	if (pRsltValue == NULL)
	{
		//�Ҳ�����˵��������û��������ֵ����Сֵ
		//˵���������鲻�����һ�����飬��û�н��м���
		return;
	}

	CDvmValue *pValue = new CDvmValue;
	pRsltExprValues->AddNewChild(pValue);
	pValue->m_strValue = pRsltValue->m_strValue;

	//pValue->m_strID = ?  ��ʱ�������ID����Ҫʱ������
	pValue->m_strName = m_strValueName;
}

BOOL CXExprCal::GetValueName(const CString &strID, CString &strName)
{
	if (m_strValueDstID == strID)
	{
		strName = m_strValueName;
		return TRUE;
	}

	return FALSE;
}

void CXExprCal::AddQueryMax(const CString &strValueSrcID)
{
	if (m_pQueryMax == NULL)
	{
		m_pQueryMax = new CXExprQueryMax();
		AddNewChild(m_pQueryMax);
	}

	m_pQueryMax->m_strValueSrcID = strValueSrcID;
}

void CXExprCal::AddQueryMin(const CString &strValueSrcID)
{
	if (m_pQueryMin == NULL)
	{
		m_pQueryMin = new CXExprQueryMin();
		AddNewChild(m_pQueryMin);
	}

	m_pQueryMin->m_strValueSrcID = strValueSrcID;
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////
CXExprCalSRpt::CXExprCalSRpt()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXExprCalSRpt::~CXExprCalSRpt()
{
}

long CXExprCalSRpt::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValueDstIDKey, oNode, m_strValueDstID);
	xml_GetAttibuteValue(pXmlKeys->m_strValueNameKey, oNode, m_strValueName);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strValueSrcIDHasKey, oNode, m_strValueSrcIdHas);
	xml_GetAttibuteValue(pXmlKeys->m_strCalModeKey, oNode, m_strCalMode);
	return 0;
}

long CXExprCalSRpt::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	xml_SetAttributeValue(pXmlKeys->m_strValueDstIDKey, oElement, m_strValueDstID);
	xml_SetAttributeValue(pXmlKeys->m_strValueNameKey, oElement, m_strValueName);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strValueSrcIDHasKey, oElement, m_strValueSrcIdHas);
	xml_SetAttributeValue(pXmlKeys->m_strCalModeKey, oElement, m_strCalMode);
	return 0;
}

long CXExprCalSRpt::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strValueDstID);
		BinarySerializeCalLen(oBinaryBuffer, m_strValueName);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strValueSrcIdHas);
		BinarySerializeCalLen(oBinaryBuffer, m_strCalMode);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strValueDstID);
		BinarySerializeRead(oBinaryBuffer, m_strValueName);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strValueSrcIdHas);
		BinarySerializeRead(oBinaryBuffer, m_strCalMode);	
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strValueDstID);
		BinarySerializeWrite(oBinaryBuffer, m_strValueName);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strValueSrcIdHas);
		BinarySerializeWrite(oBinaryBuffer, m_strCalMode);
	}
	return 0;
}

void CXExprCalSRpt::InitAfterRead()
{

}

BOOL CXExprCalSRpt::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXExprCalSRpt *p = (CXExprCalSRpt*)pObj;

	if(m_strValueDstID != p->m_strValueDstID)
	{
		return FALSE;
	}

	if(m_strValueName != p->m_strValueName)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_strValueSrcIdHas != p->m_strValueSrcIdHas)
	{
		return FALSE;
	}

	if(m_strCalMode != p->m_strCalMode)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXExprCalSRpt::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXExprCalSRpt *p = (CXExprCalSRpt*)pDest;

	p->m_strValueDstID = m_strValueDstID;
	p->m_strValueName = m_strValueName;
	p->m_strValueSrcIdHas = m_strValueSrcIdHas;
	p->m_strValueName = m_strValueName;
	p->m_strCalMode = m_strCalMode;	
	return TRUE;
}

CBaseObject* CXExprCalSRpt::Clone()
{
	CXExprCalSRpt *p = new CXExprCalSRpt();
	Copy(p);
	return p;
}

CBaseObject* CXExprCalSRpt::CloneEx(BOOL bCopyOwn, BOOL bCopyChildren)
{
	CXExprCalSRpt *p = new CXExprCalSRpt();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CXExprCalSRpt::CanPaste(UINT nClassID)
{
	return CXExprNode::CanPaste(nClassID);
}

CExBaseObject* CXExprCalSRpt::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return CXExprNode::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}

CExBaseObject* CXExprCalSRpt::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return CXExprNode::CreateNewChild(nClassID);
}

//���ڼ��㵥�α����У�ָ���������ݵ�min��max��avgֵ
//������CXExprCalSRpt������CXExprCalSRpt�ڵ�Ľ������н���������ڵ㲻����������
long CXExprCalSRpt::Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	double dRet = 0;
	BOOL bRet = pCalInterface->ExprCal_SRpt(pExprParent, m_strValueSrcIdHas, m_strCalMode, dRet);
	
	if (!bRet)
	{
		return 0;
	}

	//����ɹ��󣬻��������棻
	m_strValue.Format(_T("%.3f"), dRet);
	ExprRsltBind(pExprParent, pCalInterface);
	return CXExprNode::Calc(pExprParent, pCalInterface);
}

void CXExprCalSRpt::ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	pCalInterface->ExprRsltBind(pExprParent, _T("report"), m_strValueDstID, m_strValueName, _T(""), m_strValue);
	CXExprNode::ExprRsltBind(pExprParent, pCalInterface);
}

void CXExprCalSRpt::GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues)
{
	if (pRsltExprValues->FindByName(m_strValueName) != NULL)
	{
		//ͬһ�����Ƶģ�ֻ���һ�������Ҫ��֤��������Ĳ��ֺ�TestMacro�еĲ������Ʋ��ظ�
		return;
	}

	CDvmValue *pRsltValue = (CDvmValue *)pReportValues->FindByID(m_strValueDstID);

	if (pRsltValue == NULL)
	{
		//�Ҳ�����˵��������û��������ֵ����Сֵ
		//˵���������鲻�����һ�����飬��û�н��м���
		return;
	}

	CDvmValue *pValue = new CDvmValue;
	pRsltExprValues->AddNewChild(pValue);
	pValue->m_strValue = pRsltValue->m_strValue;

	//pValue->m_strID = ?  ��ʱ�������ID����Ҫʱ������
	pValue->m_strName = m_strValueName;

	CXExprNode::GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
}

BOOL CXExprCalSRpt::GetValueName(const CString &strID, CString &strName)
{
	if (m_strValueDstID == strID)
	{
		strName = m_strValueName;
		return TRUE;
	}

	return CXExprNode::GetValueName(strID, strName);
}