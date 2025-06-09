#pragma once
//2021-5-30   lijunqing 
#include "tmt_test_paras_head.h"

//最多1024个测试点，简单化处理
#define TMT_TEST_MNGR_MAX_COUNT			1024
#define TMT_TEST_MNGR_MAX_GROUP_COUNT	100 //dxy 20240326 状态数大于20，数组越界

#define MAX_GROUPMACROID_NAME			64

typedef struct tmt_paras_mngr
{
public:
	char m_pszParaFilePostfix[16];
	long m_nMaxCount;	//避免频繁分配，采用批次分配：固定大小，保留将来扩展
	long m_nCount;		//测试点数量
	char m_pszMacroID[MAX_GROUPMACROID_NAME]; //空串表示全部测试点结构体，否则表示分组功能ID（根据故障类型和区段组合命名）
	PTMT_PARAS_HEAD m_pParasBuffer[TMT_TEST_MNGR_MAX_COUNT];

	void init()
	{
		m_nMaxCount = TMT_TEST_MNGR_MAX_COUNT;
		m_nCount = 0;
		memset(m_pParasBuffer, 0, sizeof(PTMT_PARAS_HEAD) * TMT_TEST_MNGR_MAX_COUNT);
	}

	long GetIndex(TMT_PARAS_HEAD *pCurParasHead)
	{
		if (pCurParasHead == NULL)
		{
			return -1;
		}

		for (int nIndex = 0;nIndex<TMT_TEST_MNGR_MAX_COUNT;nIndex++)
		{
			if (m_pParasBuffer[nIndex] == pCurParasHead)
			{
				return nIndex;
			}
		}

		return -1;
	}

//2023.9.18 zhouhj
	bool IsValidItem(TMT_PARAS_HEAD *pCurParasHead)
	{
		if (pCurParasHead == NULL)
		{
			return false;
		}

		for (int nIndex = 0;nIndex<m_nCount;nIndex++)
		{
			if (m_pParasBuffer[nIndex] == pCurParasHead)
			{
				return true;
			}
		}

		return false;
	}

	tmt_paras_mngr(){  init(); }
}TMT_PARAS_MNGR, *PTMT_PARAS_MNGR;

typedef struct tmt_paras_mngr_group{
	long m_nGroupCount;  //分组数
	PTMT_PARAS_MNGR m_pTestMngr[TMT_TEST_MNGR_MAX_GROUP_COUNT]; //分组

	void init()
	{
		m_nGroupCount = 0;
		memset(m_pTestMngr, 0, sizeof(PTMT_PARAS_MNGR) * TMT_TEST_MNGR_MAX_GROUP_COUNT);
	}

	int GetGroupIndex(char* pszGroupMacroID)
	{
		if(strlen(pszGroupMacroID) == 0)
		{
			return -1;
		}

		for (int i=0;i<m_nGroupCount;i++)
		{
			if(strcmp(m_pTestMngr[i]->m_pszMacroID,pszGroupMacroID)==0)
				return i;
		}

		return -1;//20220715 未查找到,则返回-1
	}

	tmt_paras_mngr_group(){	init();}
} TMT_PARAS_MNGR_GROUP, *PTMT_PARAS_MNGR_GROUP;


//因为固定大小，这些函数保留用
void stt_test_mngr_set_max_count(PTMT_PARAS_MNGR pMngr, long nMaxCount);
void stt_test_mngr_expand(PTMT_PARAS_MNGR pMngr, long nCount);

long stt_test_mngr_find_index(PTMT_PARAS_MNGR pMngr, PTMT_PARAS_HEAD pPara);
PTMT_PARAS_HEAD stt_test_mngr_get_at(PTMT_PARAS_MNGR pMngr, long nPos);

void stt_test_mngr_add(PTMT_PARAS_MNGR pMngr, PTMT_PARAS_HEAD pPara);
void stt_test_mngr_insert_at(PTMT_PARAS_MNGR pMngr, PTMT_PARAS_HEAD pPara, long nIndex);
void stt_test_mngr_set_at(PTMT_PARAS_MNGR pMngr, PTMT_PARAS_HEAD pPara, long nIndex);
void stt_test_mngr_insert_before(PTMT_PARAS_MNGR pMngr, PTMT_PARAS_HEAD pPara, long nIndex);
void stt_test_mngr_insert_after(PTMT_PARAS_MNGR pMngr, PTMT_PARAS_HEAD pPara, long nIndex);
BOOL stt_test_mngr_delete(PTMT_PARAS_MNGR pMngr, PTMT_PARAS_HEAD pPara);
BOOL stt_test_mngr_delete_at(PTMT_PARAS_MNGR pMngr, long nIndex);
void stt_test_mngr_delete_all(PTMT_PARAS_MNGR pMngr, BOOL b);
void stt_test_mngr_remove_all(PTMT_PARAS_MNGR pMngr);

void stt_xml_serialize(PTMT_PARAS_MNGR pParas, CSttXmlSerializeBase *pXmlSierialize);


//表达式计算模块
//#include "../../../../Module/Expression/ExprParse.h"

#include "../../../../Module/Expression/ExprParse.h"

extern CDataGroup *g_pTmt_TestItemResultRef;
extern CDataGroup *g_pTmt_SystemParaRef;
extern CDataGroup *g_pTmt_SetsRef;

class CTmtTestRsltExprImp : public CExprVariableFind
{
public:
	CTmtTestRsltExprImp();
	virtual ~CTmtTestRsltExprImp();

public:
	virtual CExBaseObject* FindVariableByID(const CString &strID);
	virtual CExBaseObject* FindVariableByName(const CString &strName);
	virtual void OnExprScriptChanged(const CString &strExprScript);

	CExprTextUnitList m_oExprTextUnitList;

public:
	CDataGroup m_oTestItemResultRef;
	CDataGroup m_oSystemParaRef;
	CDataGroup m_oSetsRef;

public:
	CString GetExprScriptText(const CString &strScript);  //获取表达式的文本
	bool  CalParaExpression(const CString &strExpress, double &dValue);

	void CalTestItemRslt(PTMT_PARAS_HEAD pItem);
};

extern		CTmtTestRsltExprImp		g_oTmtTestRsltExprImp;
