//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprNode.cpp  CXExprNode


#include "stdafx.h"
#include "XExprNode.h"

CXExprNode::CXExprNode()
{
	//初始化属性
	m_pValueRslt = NULL;
	m_strLogic = _T("and");
	//初始化成员变量
}

CXExprNode::~CXExprNode()
{
}

long CXExprNode::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strLogicKey, oNode, m_strLogic);
	return 0;
}

long CXExprNode::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(pXmlKeys->m_strLogicKey, oElement, m_strLogic);
	return 0;
}

long CXExprNode::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CXExprBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strLogic);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strLogic);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strLogic);
	}
	return 0;
}

void CXExprNode::InitAfterRead()
{
	CXExprBase::InitAfterRead();

	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
		{
			m_pValueRslt = (CXExprValueRslt*)p;
		}
	}
}

BOOL CXExprNode::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXExprBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXExprNode *p = (CXExprNode*)pObj;

	if(m_strLogic != p->m_strLogic)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXExprNode::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXExprBase::CopyOwn(pDest);
	CXExprNode *p = (CXExprNode*)pDest;

	p->m_strLogic = m_strLogic;
	return TRUE;
}

CBaseObject* CXExprNode::Clone()
{
	CXExprNode *p = new CXExprNode();
	Copy(p);
	return p;
}

CBaseObject* CXExprNode::CloneEx(BOOL bCopyOwn, BOOL bCopyChildren)
{
	CXExprNode *p = new CXExprNode();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CXExprNode::CanPaste(UINT nClassID)
{
	if (nClassID == XEXPRCLASSID_CXEXPRCMP)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRERROR)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRERROREX)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRERROREX_I)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRERRORCOMBINED)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRERRORCOMBINED_I)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRRANGE)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRRANGEEX)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRNODE)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUECAL)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUECALEX)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXExprNode::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	if (strClassID == pXmlKeys->m_strCXExprCmpKey)
	{
		pNew = new CXExprCmp();
	}
	else if (strClassID == pXmlKeys->m_strCXExprErrorKey)
	{
		pNew = new CXExprError();
	}
	else if (strClassID == pXmlKeys->m_strCXExprErrorExKey)
	{
		pNew = new CXExprErrorEx();
	}
	else if (strClassID == pXmlKeys->m_strCXExprErrorCombinedKey)
	{
		pNew = new CXExprErrorCombined();
	}
	else if (strClassID == pXmlKeys->m_strCXExprErrorEx_IKey)
	{
		pNew = new CXExprErrorEx_I();
	}
	else if (strClassID == pXmlKeys->m_strCXExprErrorCombined_IKey)
	{
		pNew = new CXExprErrorCombined_I();
	}
	else if (strClassID == pXmlKeys->m_strCXExprRangeKey)
	{
		pNew = new CXExprRange();
	}
	else if (strClassID == pXmlKeys->m_strCXExprRangeExKey)
	{
		pNew = new CXExprRangeEx();
	}
	else if (strClassID == pXmlKeys->m_strCXExprNodeKey)
	{
		pNew = new CXExprNode();
	}
	else if (strClassID == pXmlKeys->m_strValueRsltKey)
	{
		pNew = new CXExprValueRslt();
	}
	else if (strClassID == pXmlKeys->m_strCXExprValueCalKey)
	{
		pNew = new CXExprValueCal();
	}
	else if (strClassID == pXmlKeys->m_strCXExprValueCalExKey)
	{
		pNew = new CXExprValueCalEx();
	}
	else if (strClassID == pXmlKeys->m_strCXExprCalKey)
	{
		pNew = new CXExprCal();
	}

	return pNew;
}

CExBaseObject* CXExprNode::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == XEXPRCLASSID_CXEXPRCMP)
	{
		pNew = new CXExprCmp();
	}
	else if (nClassID == XEXPRCLASSID_CXEXPRERROR)
	{
		pNew = new CXExprError();
	}
	else if (nClassID == XEXPRCLASSID_CXEXPRERROREX)
	{
		pNew = new CXExprErrorEx();
	}
	else if (nClassID == XEXPRCLASSID_CXEXPRERRORCOMBINED)
	{
		pNew = new CXExprErrorCombined();
	}
	else if (nClassID == XEXPRCLASSID_CXEXPRERROREX_I)
	{
		pNew = new CXExprErrorEx_I();
	}
	else if (nClassID == XEXPRCLASSID_CXEXPRERRORCOMBINED_I)
	{
		pNew = new CXExprErrorCombined_I();
	}
	else if (nClassID == XEXPRCLASSID_CXEXPRRANGE)
	{
		pNew = new CXExprRange();
	}
	else if (nClassID == XEXPRCLASSID_CXEXPRRANGEEX)
	{
		pNew = new CXExprRangeEx();
	}
	else if (nClassID == XEXPRCLASSID_CXEXPRNODE)
	{
		pNew = new CXExprNode();
	}
	else if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
	{
		pNew = new CXExprValueRslt();
	}
	else if (nClassID == XEXPRCLASSID_CXEXPRVALUECAL)
	{
		pNew = new CXExprValueCal();
	}
	else if (nClassID == XEXPRCLASSID_CXEXPRVALUECALEX)
	{
		pNew = new CXExprValueCalEx();
	}
	else if (nClassID == XEXPRCLASSID_CXEXPRCAL)
	{
		pNew = new CXExprCal();
	}

	return pNew;
}

long CXExprNode::Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	long nCount = 0/*GetCount()*/;
	POS pos = GetHeadPosition();
	CXExprBase *p = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	long nResult = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
		{
			continue;
		}

		if (nClassID == XEXPRCLASSID_CXEXPRCAL)
		{
			//这个放到最后处理。等所有的表达式计算，都计算结束后，再进行该类型的节点计算
			continue;
		}

		p = (CXExprBase *)pObj;

		if (p->m_nIsUse != 1)
		{
			//不启用的，不参与结果判断
			continue;
		}

		long nRet = p->Calc(pExprParent, pCalInterface);

		if (p->m_nCntRslt)
		{
			//启用参与结论评判
			nCount += 1;
			nResult += nRet;
		}
	}

	if (m_strLogic == _T("and"))
	{
		m_nResult = (nResult == nCount);
	}
	else
	{
		m_nResult = (nResult > 0);
	}
	
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CXExprNode::Calc::计算结果为%d"), m_nResult);

	//计算结束后，将结果绑定回对应的参数
	CXExprValueRslt* pRslt = GetValueRslt();
	pRslt->m_strValue.Format(_T("%d"), m_nResult);
	pRslt->ExprRsltBind(pExprParent, pCalInterface);

	return m_nResult;
}

long CXExprNode::CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes)
{
	long nRslt = Calc(pExprParent, pCalInterface);

	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		//shaolei 在Calc中，已经递归调用了子的node节点。此处只计算CXExprCal的部分
		if (nClassID == XEXPRCLASSID_CXEXPRNODE)
		{
			CXExprNode *pChildNode = (CXExprNode *)pObj;

			if (pChildNode->m_nIsUse == 0)
			{
				continue;
			}

			pChildNode->CalcEx_MaxMin(pExprParent, pCalInterface, nCurrTestTimes, nRepeatTimes);
		}

		if (nClassID != XEXPRCLASSID_CXEXPRCAL)
		{
			continue;
		}

		CXExprCal *p = (CXExprCal *)pObj;

		/*BOOL bRet = */p->CalcEx(pExprParent, pCalInterface, nCurrTestTimes, nRepeatTimes);

		//重复测试的，没有全部测完，不进行结果计算。也就不需要进行结果绑定
		if (/*bRet && */nCurrTestTimes >= nRepeatTimes)
		{
			p->ExprRsltBind(pExprParent, pCalInterface);
		}
	}

	if (m_nCntRslt)
	{
		return nRslt;
	}
	
	return 1;
}

long CXExprNode::CalcEx_MaxMin(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != XEXPRCLASSID_CXEXPRCAL)
		{
			continue;
		}

		CXExprCal *p = (CXExprCal *)pObj;

		BOOL bRet = p->CalcEx(pExprParent, pCalInterface, nCurrTestTimes, nRepeatTimes);

		//重复测试的，没有全部测完，不进行结果计算。也就不需要进行结果绑定
		if (bRet && nCurrTestTimes >= nRepeatTimes)
		{
			p->ExprRsltBind(pExprParent, pCalInterface);
		}
	}

	return 1;
}

//将输出参数的值，赋值给对应的绑定参数
void CXExprNode::ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	POS pos = GetHeadPosition();
	CXExprBase *p = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
		{
			CXExprValueRslt *pValueRslt = (CXExprValueRslt*)pObj;
			pValueRslt->ExprRsltBind(pExprParent, pCalInterface);
			continue;
		}

		if (nClassID == XEXPRCLASSID_CXEXPRCAL)
		{
			CXExprCal *pExprCal = (CXExprCal *)pObj;
			pExprCal->ExprRsltBind(pExprParent, pCalInterface);
			continue;
		}

		p = (CXExprBase *)pObj;

		if (p->m_nIsUse != 1)
		{
			//不启用的，不参与结果绑定
			continue;
		}

		p->ExprRsltBind(pExprParent, pCalInterface);
	}
}

CXExprValueRslt* CXExprNode::GetValueRslt()
{
	if (m_pValueRslt == NULL)
	{
		m_pValueRslt = new CXExprValueRslt();
		AddNewChild(m_pValueRslt);
	}

	return m_pValueRslt;
}

void CXExprNode::GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues)
{
	POS pos = GetHeadPosition();
	CXExprBase *p = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
		{
			CXExprValueRslt *pValueRslt = (CXExprValueRslt*)pObj;
			pValueRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
			continue;
		}

		if (nClassID == XEXPRCLASSID_CXEXPRCAL)
		{
			CXExprCal *pExprCal = (CXExprCal *)pObj;
			pExprCal->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
			continue;
		}

		p = (CXExprBase *)pObj;

		if (p->m_nIsUse != 1)
		{
			//不启用的，不参与结果判断
			continue;
		}

		p->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}
}

BOOL CXExprNode::GetValueName(const CString &strID, CString &strName)
{
	POS pos = GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	CXExprBase *p = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
		{
			CXExprValueRslt *pValueRslt = (CXExprValueRslt*)pObj;

			if (pValueRslt->GetValueName(strID, strName))
			{
				return TRUE;
			}

			continue;
		}

		if (nClassID == XEXPRCLASSID_CXEXPRCAL)
		{
			CXExprCal *pExprCal = (CXExprCal *)pObj;

			if (pExprCal->GetValueName(strID, strName))
			{
				return TRUE;
			}

			continue;
		}

		p = (CXExprBase *)pObj;

		if (p->m_nIsUse != 1)
		{
			//不启用的，不参与结果判断
			continue;
		}

		if (p->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	return FALSE;
}