#include "RsltExprMngr.h"

long QRsltExprMngr::g_nRsltExprMngr = 0;
QRsltExprMngr* QRsltExprMngr::g_pRsltExprMngr = NULL;

QRsltExprMngr::QRsltExprMngr()
{
	m_pRoot = NULL;
}

QRsltExprMngr::~QRsltExprMngr()
{
}

QRsltExprMngr* QRsltExprMngr::Create( )
{
	g_nRsltExprMngr++;

	if (g_nRsltExprMngr == 1)
	{
		g_pRsltExprMngr = new QRsltExprMngr();
	}
	return g_pRsltExprMngr;
}

QRsltExprMngr* QRsltExprMngr::GetRsltExprMngr()
{
	return g_pRsltExprMngr;
}

void QRsltExprMngr::SetExprFileName(CString strFileName)
{
	if (m_pRoot == NULL)
	{
		m_pRoot = new CDataGroup();
	}

	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	BOOL bRet = m_pRoot->OpenXmlFile(strFileName, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

void QRsltExprMngr::Release()
{
	g_nRsltExprMngr--;

	if (g_nRsltExprMngr == 0)
	{
		delete g_pRsltExprMngr;
		g_pRsltExprMngr = NULL;
	}
}

long   QRsltExprMngr::GetExprCount()
{
	if (g_pRsltExprMngr->m_pDataGroup_Curr==NULL)
		return 0;
	else 
	{
		return g_pRsltExprMngr->m_pDataGroup_Curr->GetCount();
	}
}

// 根据传入的评估项的ID，索引号，获取表达式内容;
CString   QRsltExprMngr::GetExprContent(CString strID, int nIndex)
{
	CDataGroup * pDataGroup = FindDataGroupByID(strID);

	if (pDataGroup != NULL)
	{
		CDvmData * pDvmData = (CDvmData*)pDataGroup->GetAtIndex(nIndex);;

		if (pDvmData != NULL)
		{
			return pDvmData->m_strValue;
		}
	}

	return CString (_T(""));
}

CDataGroup *  QRsltExprMngr::FindDataGroupByID(const CString &strIDPath)
{
	if (g_pRsltExprMngr->m_pDataGroup_Curr==NULL)
		return NULL;

	return  (CDataGroup*)g_pRsltExprMngr->m_pDataGroup_Curr->FindByID(strIDPath);
}

void  QRsltExprMngr::InitDataGroupByID(const CString &strIDPath)
{
	if (g_pRsltExprMngr->m_pRoot==NULL)
		return ;

	g_pRsltExprMngr->m_pDataGroup_Curr =  (CDataGroup*)g_pRsltExprMngr->m_pRoot->FindByID(strIDPath);

	if (g_pRsltExprMngr->m_pDataGroup_Curr == NULL)
	{
		g_pRsltExprMngr->m_pDataGroup_Curr = (CDataGroup*)g_pRsltExprMngr->m_pRoot->GetHead();
	}
}


//////////////////////////////////////////////////////////////////////////
CSttTmtRsltExprDefine::CSttTmtRsltExprDefine()
{

}

CSttTmtRsltExprDefine::~CSttTmtRsltExprDefine()
{

}


void CSttTmtRsltExprDefine::InitRsltExprDefine(CDataGroup *pRsltExprDefine)
{
	if (pRsltExprDefine ==  NULL)
	{
		m_pExprDatasDef = NULL;
		m_pExprViewDatasDef = NULL;
	}
	else
	{
		//<group name="ExprDatasDef" id="ExprDatasDef" data-type="ExprDatasDef" value="ExprDatasDef">
		m_pExprDatasDef  =  dvm_FindDataGroupByValue(*pRsltExprDefine, "ExprDatasDef");// mym 2021-7-21 zhuxiao  dvm_FindDataGroupByValue(*this, "ExprDatasDef");

		//<group name="ExprViewDatasDef" id="ExprViewDatasDef" data-type="ExprViewDatasDef" value="ExprViewDatasDef">
		m_pExprViewDatasDef  = dvm_FindDataGroupByValue(*pRsltExprDefine, "ExprViewDatasDef");// mym 2021-7-21 zhuxiao
	}
}


//////////////////////////////////////////////////////////////////////////
CSttTmtRsltExprDefineMngr g_oSttTmtRsltExprDefineMngr;

CSttTmtRsltExprDefineMngr::CSttTmtRsltExprDefineMngr()
{
	m_pDataGroup = NULL;
}

CSttTmtRsltExprDefineMngr::~CSttTmtRsltExprDefineMngr()
{
	if (m_pDataGroup)
	{
		delete m_pDataGroup;
		m_pDataGroup = NULL;
	}
}

void CSttTmtRsltExprDefineMngr::InitRsltExprDefineMngr(const CString &strFile)
{
	if (m_pDataGroup == NULL)
	{
		m_pDataGroup = new CDataGroup();
	}

 	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
 	BOOL bRet = m_pDataGroup->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
 	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

//<group name="SttTmtRsltExprDefine" id="SttTmtRsltExprDefine" data-type="" value="Distance">
//根据Group的Value查找
//strTmtID为测试功能的ID，例如“Distance”，即tmt_paras_head 的 m_pszMacroID
/*
typedef struct tmt_paras_head
{
public:
	char m_pszMacroID[TMT_PARAS_HEAD_MACROID_LEN];  //测试供能ID;
}
*/
CSttTmtRsltExprDefine* CSttTmtRsltExprDefineMngr::FindRsltExprDefine(const CString &strTmtID)
{
	//CDataGroup *pFind = dvm_FindDataGroupByValue(*this, strTmtID);
	CDataGroup *pFind = dvm_FindDataGroupByValue(*m_pDataGroup,  strTmtID);

	m_oRsltExprDefine.InitRsltExprDefine(pFind);

	return &m_oRsltExprDefine;
}


//////////////////////////////////////////////////////////////////////////
void stt_init_rslt_expr_mngr(const CString &strExprFile, const CString &strExprDataFile)
{
	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += strExprFile;

	QRsltExprMngr *pExprMngr = QRsltExprMngr::Create();
	pExprMngr->SetExprFileName(strPath);


	strPath = _P_GetConfigPath();
	strPath += strExprDataFile;
	g_oSttTmtRsltExprDefineMngr.InitRsltExprDefineMngr(strPath);
}


void stt_free_rslt_expr_mngr()
{
	QRsltExprMngr::Release();
}

