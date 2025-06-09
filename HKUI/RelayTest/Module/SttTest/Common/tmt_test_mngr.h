#pragma once
//2021-5-30   lijunqing 
#include "tmt_test_paras_head.h"

//���1024�����Ե㣬�򵥻�����
#define TMT_TEST_MNGR_MAX_COUNT			1024
#define TMT_TEST_MNGR_MAX_GROUP_COUNT	100 //dxy 20240326 ״̬������20������Խ��

#define MAX_GROUPMACROID_NAME			64

typedef struct tmt_paras_mngr
{
public:
	char m_pszParaFilePostfix[16];
	long m_nMaxCount;	//����Ƶ�����䣬�������η��䣺�̶���С������������չ
	long m_nCount;		//���Ե�����
	char m_pszMacroID[MAX_GROUPMACROID_NAME]; //�մ���ʾȫ�����Ե�ṹ�壬�����ʾ���鹦��ID�����ݹ������ͺ��������������
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
	long m_nGroupCount;  //������
	PTMT_PARAS_MNGR m_pTestMngr[TMT_TEST_MNGR_MAX_GROUP_COUNT]; //����

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

		return -1;//20220715 δ���ҵ�,�򷵻�-1
	}

	tmt_paras_mngr_group(){	init();}
} TMT_PARAS_MNGR_GROUP, *PTMT_PARAS_MNGR_GROUP;


//��Ϊ�̶���С����Щ����������
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


//���ʽ����ģ��
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
	CString GetExprScriptText(const CString &strScript);  //��ȡ���ʽ���ı�
	bool  CalParaExpression(const CString &strExpress, double &dValue);

	void CalTestItemRslt(PTMT_PARAS_HEAD pItem);
};

extern		CTmtTestRsltExprImp		g_oTmtTestRsltExprImp;
