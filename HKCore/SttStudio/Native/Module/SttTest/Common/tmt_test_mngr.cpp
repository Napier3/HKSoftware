#include "stdafx.h"
#include "tmt_test_mngr.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../XLangResource_Native.h"                              
#endif
#include "../../../../AutoTest/Module/XLanguageResourceAts.h"



#define  TMT_TEST_MNGR_COUNT_EXPAND   10

void stt_test_mngr_set_max_count(PTMT_PARAS_MNGR pMngr, long nMaxCount)
{
// 	if (pMngr->m_nMaxCount >= nMaxCount)
// 	{
// 		return;
// 	}
// 
// 	unsigned long *pNew = new unsigned long[nMaxCount];
// 	memset(pNew, 0, sizeof(unsigned long) * nMaxCount);
// 	memcpy(pNew, pMngr->m_pParasBuffer, sizeof(unsigned long) * pMngr->m_nCount);
// 	delete pMngr->m_pParasBuffer;
// 	pMngr->m_pParasBuffer = pNew;
// 	pMngr->m_nMaxCount = nMaxCount;
}

void stt_test_mngr_expand(PTMT_PARAS_MNGR pMngr, long nCount)
{
// 	stt_test_mngr_set_max_count(pMngr, pMngr->m_nMaxCount + nCount);
}


void stt_test_mngr_make_sure(PTMT_PARAS_MNGR pMngr, long nSizeAdd)
{
// 	if (pMngr->m_nCount + nSizeAdd <= pMngr->m_nMaxCount)
// 	{
// 		return;
// 	}
// 
// 	if (nSizeAdd > TMT_TEST_MNGR_COUNT_EXPAND)
// 	{
// 		stt_test_mngr_expand(pMngr, nSizeAdd);
// 	}
// 	else
// 	{
// 		stt_test_mngr_expand(pMngr, TMT_TEST_MNGR_COUNT_EXPAND);
// 	}
}

long stt_test_mngr_find_index(PTMT_PARAS_MNGR pMngr, PTMT_PARAS_HEAD pPara)
{
	long k = 0, nFind = -1;

	for (k=0; k<pMngr->m_nCount; k++)
	{
		if (pMngr->m_pParasBuffer[k] == pPara)
		{
			nFind = k;
			break;
		}
	}

	return nFind;
}

PTMT_PARAS_HEAD stt_test_mngr_get_at(PTMT_PARAS_MNGR pMngr, long nPos)
{
	if (pMngr->m_nCount == 0)
	{
		return NULL;
	}

	if (nPos < 0 || nPos >= pMngr->m_nCount)
	{
		return NULL;
	}

	return pMngr->m_pParasBuffer[nPos];
}

void stt_test_mngr_add(PTMT_PARAS_MNGR pMngr, PTMT_PARAS_HEAD pPara)
{
	stt_test_mngr_make_sure(pMngr, 1);
	pMngr->m_pParasBuffer[pMngr->m_nCount] = pPara;
	pMngr->m_nCount++;
}

void stt_test_mngr_insert_at(PTMT_PARAS_MNGR pMngr, PTMT_PARAS_HEAD pPara, long nIndex)
{
	if (pMngr->m_nCount <= nIndex)
	{
		stt_test_mngr_add(pMngr, pPara);
		return;
	}

	stt_test_mngr_make_sure(pMngr, 1);
	long k = 0;

	for (k=pMngr->m_nCount; k>nIndex; k--)
	{
		pMngr->m_pParasBuffer[k] = pMngr->m_pParasBuffer[k-1];
	}

	pMngr->m_pParasBuffer[nIndex] = pPara;
	pMngr->m_nCount++;
}

void stt_test_mngr_set_at(PTMT_PARAS_MNGR pMngr, PTMT_PARAS_HEAD pPara, long nIndex)
{
	if (pMngr->m_nCount <= nIndex)
	{
		stt_test_mngr_add(pMngr, pPara);
		return;
	}

	pMngr->m_pParasBuffer[nIndex] = pPara;
}

void stt_test_mngr_insert_before(PTMT_PARAS_MNGR pMngr, PTMT_PARAS_HEAD pPara, long nIndex)
{
	stt_test_mngr_insert_at(pMngr, pPara, nIndex);
}

void stt_test_mngr_insert_after(PTMT_PARAS_MNGR pMngr, PTMT_PARAS_HEAD pPara, long nIndex)
{
	stt_test_mngr_insert_at(pMngr, pPara, nIndex+1);
}

BOOL stt_test_mngr_delete(PTMT_PARAS_MNGR pMngr, PTMT_PARAS_HEAD pPara)
{
	long nPos = stt_test_mngr_find_index(pMngr, pPara);

	if (nPos >= 0)
	{
		return stt_test_mngr_delete_at(pMngr, nPos);
	}
	else
	{
		return FALSE;
	}
}

BOOL stt_test_mngr_delete_at(PTMT_PARAS_MNGR pMngr, long nIndex)
{
	if (nIndex < 0 || pMngr->m_nCount <= nIndex)
	{
		return FALSE;
	}

	delete pMngr->m_pParasBuffer[nIndex];
	long k = 0;

	for (k=nIndex; k<pMngr->m_nCount; k++)
	{
		pMngr->m_pParasBuffer[k] = pMngr->m_pParasBuffer[k+1];
	}

	pMngr->m_pParasBuffer[pMngr->m_nCount-1] = 0;
	pMngr->m_nCount--;

	return TRUE;
}


void stt_xml_serialize(PTMT_PARAS_MNGR pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("Count","Count","","long", pParas->m_nCount);

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		stt_test_mngr_set_max_count(pParas, pParas->m_nCount);
	}
}


//////////////////////////////////////////////////////////////////////////
CDataGroup *g_pTmt_TestItemResultRef = NULL;
CDataGroup *g_pTmt_SystemParaRef = NULL;
CDataGroup *g_pTmt_SetsRef = NULL;

CTmtTestRsltExprImp g_oTmtTestRsltExprImp;

CTmtTestRsltExprImp::CTmtTestRsltExprImp()
{
	g_pTmt_TestItemResultRef = &m_oTestItemResultRef;
	g_pTmt_SystemParaRef = &m_oSystemParaRef;
	g_pTmt_SetsRef = &m_oSetsRef;

	m_oExprTextUnitList.SetExprVariableFind(this);      //关联数据查找
}

CTmtTestRsltExprImp::~CTmtTestRsltExprImp()
{

}

//获取表达式的文本
CString CTmtTestRsltExprImp::GetExprScriptText(const CString &strScript)
{
	m_oExprTextUnitList.SetExprScript(strScript);         //设置表达式
	return m_oExprTextUnitList.GetExprScriptText();      //获取表达式的文本
}

bool  CTmtTestRsltExprImp::CalParaExpression(const CString &strExpress, double &dValue)
{
	CEpExpression oEpExp;

	if (strExpress.GetLength() == 0)
	{
		return FALSE;
	}

	if (oEpExp.ChangeEpExpression(strExpress) == -1)
	{
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /* _T("表达式【%s】 错误") */ g_sLangTxt_ExpressionError.GetString(), strExpress.GetString());
		return FALSE;
	}

	CString strValue;
	POS pos   =  oEpExp.GetHeadPosition();
	CEpExpVariable *pExpVar  = NULL;
	BOOL bTrue  =  TRUE;
	CDvmData *pFind  = NULL;

	while (pos != NULL)
	{
		pExpVar = oEpExp.GetNext(pos);
		pFind = (CDvmData*)FindVariableByID(pExpVar->m_strVarID);

		if (pFind != NULL)
		{
#ifdef _UNICODE
			pExpVar->m_dValue = _wtof(pFind.m_strValue);
#else
			{
				char*  ch;
				QByteArray ba = pFind->m_strValue.toLatin1(); 
				ch = ba.data();
				pExpVar->m_dValue = atof(ch);
			}
#endif
		}
		else
		{
			//if (bLogError)
			{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /* _T("表达式变量【%s】 错误") */ g_sLangTxt_ExpressionVariable.GetString(), pExpVar->m_strVarID.GetString());
				bTrue = FALSE;
			}
		}
	}

	oEpExp.Value(dValue);

	return bTrue;
}


CExBaseObject* CTmtTestRsltExprImp::FindVariableByID(const CString &strID)
{
	CExBaseObject* pExBaseObject = NULL;

	pExBaseObject  =  m_oSetsRef.FindByID(strID);
	if (pExBaseObject  !=  NULL)
		return pExBaseObject;
	else 
	{
		pExBaseObject  = m_oTestItemResultRef.FindByID(strID);

		if (pExBaseObject  != NULL)
			return pExBaseObject;
		else 
		{
			pExBaseObject  = m_oSystemParaRef.FindByID(strID);	
			if (pExBaseObject  !=  NULL)
				return pExBaseObject;
			else 
				return NULL;
		}
	}


	return NULL;
}

CExBaseObject* CTmtTestRsltExprImp::FindVariableByName(const CString &strName)
{
	CExBaseObject* pExBaseObject = NULL;

	pExBaseObject   =  m_oTestItemResultRef.FindByName(strName);
	if (pExBaseObject  !=  NULL)
		return pExBaseObject;
	else 
	{
		pExBaseObject  = m_oSystemParaRef.FindByName(strName);

		if (pExBaseObject  != NULL)
			return pExBaseObject;
		else 
		{
			pExBaseObject  = m_oSetsRef.FindByName(strName);	
			if (pExBaseObject  !=  NULL)
				return pExBaseObject;
			else 
				return NULL;
		}
	}

	return NULL;
}

void CTmtTestRsltExprImp::OnExprScriptChanged(const CString &strExprScript)
{

}


void CTmtTestRsltExprImp::CalTestItemRslt(PTMT_PARAS_HEAD pItem)
{
	TMT_PARAS_RSLT_EXPR_MNGR *pExprMngr  = &pItem->m_oRsltExprMngr;
	PTMT_PARAS_RSLT_EXPR pExpr = NULL;
	double dValue = 0;
	CString strExpr;

	for (long k = 0; k < pExprMngr->m_nCount;  k++)
	{
		strExpr = pExprMngr->m_RsltExprs[k].m_pRsltExpr;
		if(strExpr.GetLength()==0)
		{
			continue;
		}

		if(CalParaExpression(strExpr,  dValue))
		{
			if (dValue  <=  0.001)
			{
				pItem->m_nTestState  =  2;
				break;
			}
		}
		else //表达式错误的时候直接赋值2后 蹦出来 不再继续判其他表达式了;
		{
			pItem->m_nTestState  =  2;
			break;
		}
	}

	if (pItem->m_nTestState != 2)
	{
		pItem->m_nTestState = 1;
	}
}