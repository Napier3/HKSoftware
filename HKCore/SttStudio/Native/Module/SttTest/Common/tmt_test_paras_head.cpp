#include "stdafx.h"
#include "tmt_test_paras_head.h"

int g_nBinExCount = 0;
int g_nBoutExCount = 0;
int g_nBinCount = 20;
int g_nBoutCount = 20;
int g_nStateCount = 20;

BOOL stt_xml_serialize_ReadMacroID(CSttXmlSerializeBase *pXmlSierialize,char *pszMacroID)
{
	if (!stt_xml_serialize_is_read(pXmlSierialize))
	{
		strcpy(pszMacroID,_T(""));
		return FALSE;
	}

	pXmlSierialize->xml_serialize("id","id","","string", pszMacroID);

	return TRUE;
}

#ifdef NOT_USE_TMT_TEST_PARAS_HEAD
void stt_xml_serialize(PTMT_PARAS_HEAD pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	if (stt_xml_serialize_is_write(pXmlSierialize))
	{
		pXmlSierialize->xml_serialize("id","id","","string", pParas->m_pszMacroID);
	}
}
#else
void stt_xml_serialize(PTMT_PARAS_HEAD pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		pXmlSierialize->xml_serialize("Version","Version","","long", pParas->m_nVersionRead);
	}
	else
	{
		pXmlSierialize->xml_serialize("id","id","","string", pParas->m_pszMacroID);
		pXmlSierialize->xml_serialize("Version","Version","","long", pParas->m_nVersion);
	}

	pXmlSierialize->xml_serialize("Selected","Selected","","long", pParas->m_nSelected);//zhouhj 20210712  保持测试模板时,记录每个测试项的选择状态
	pXmlSierialize->xml_serialize("TestState","TestState","","long", pParas->m_nTestState);

	stt_xml_serialize(&pParas->m_oRsltExprMngr,  pXmlSierialize);
}

void stt_xml_serialize(PTMT_PARAS_RSLT_EXPR_MNGR	pRsltExprMngr,   CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlExprMngr  = pXmlSerialize->xml_serialize("ExprMngr", "ExprMngr", "ExprMngr", L"ExprMngr");

	if (pXmlExprMngr == NULL)
	{
		return;
	}

	pXmlExprMngr->xml_serialize("count", "count", "", "long",  pRsltExprMngr->m_nCount);      //exp: 有几个跳A，跳B，跳C，重合，后加速等等；
	pXmlExprMngr->xml_serialize("ExprGroupID", "ExprGroupID", "", "string",  pRsltExprMngr->m_pszExprGroupID);

	int nIndex = 0;
	for (nIndex = 0;  nIndex <  pRsltExprMngr->m_nCount; nIndex++)
	{
		//pRsltExprMngr-> m_pRsltExprs[nIndex] = new TMT_PARAS_RSLT_EXPR;
		stt_xml_serialize(&pRsltExprMngr-> m_RsltExprs[nIndex], nIndex, pXmlExprMngr);
	}
}

void stt_xml_serialize(PTMT_PARAS_RSLT_EXPR	pRsltExpr, long nIndex,  CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlExpr = pXmlSerialize->xml_serialize(L"Expr", nIndex, "Expr", "Expr", "Expr");

	if (pXmlExpr == NULL)
	{
		return;
	}

	//pXmlSerialize->xml_serialize("Count", "Count", "", "long",  pRsltExpr->m_nCount);
	pXmlExpr->xml_serialize("DataID", "DataID", "",  "string",  pRsltExpr->m_pszExprDataID);
	pXmlExpr->xml_serialize("Expr",  "Expr",  "",  "string", 	pRsltExpr->m_pRsltExpr);
}

void stt_clone_expr_mngr(PTMT_PARAS_RSLT_EXPR_MNGR pSrc, PTMT_PARAS_RSLT_EXPR_MNGR pDest)
{
	pDest->m_nCount = pSrc->m_nCount;
	long k = 0;

	for (k=0; k<pSrc->m_nCount; k++)
	{
	//	pDest->m_pRsltExprs[k] = new TMT_PARAS_RSLT_EXPR;
		(pDest->m_RsltExprs[k]) = (pSrc->m_RsltExprs[k]);
	}
}

void stt_clone_expr_mngr(PTMT_PARAS_HEAD pSrc, PTMT_PARAS_HEAD pDest)
{
	stt_clone_expr_mngr(&pSrc->m_oRsltExprMngr, &pDest->m_oRsltExprMngr);
}

#endif

