#pragma once
//2021-5-30   lijunqing 
#include "../../SttTestBase/SttXmlSerialize.h"

#define TMT_PARAS_HEAD_MACROID_LEN  32	//2021-8-2 yyj�ռ�Ӵ�MacroID����16���쳣
BOOL stt_xml_serialize_ReadMacroID(CSttXmlSerializeBase *pXmlSierialize,char *pszMacroID);

#ifdef NOT_USE_TMT_TEST_PARAS_HEAD

typedef struct tmt_paras_head
{
public:
	char m_pszMacroID[TMT_PARAS_HEAD_MACROID_LEN]; 

	void init_head()
	{
		m_pszMacroID[0] = 0;
	}

	tmt_paras_head &operator = (const tmt_paras_head &paras)
	{
		return *this;
	}

	virtual void clear_result(){}

}TMT_PARAS_HEAD, *PTMT_PARAS_HEAD;

void stt_xml_serialize(PTMT_PARAS_HEAD pParas, CSttXmlSerializeBase *pXmlSierialize);

#else  //NOT_USE_TMT_TEST_PARAS_HEAD

#define PARAS_RSLT_EXPR_LEN			128
#define PARAS_RSLT_EXPR_MAX_COUNT     4
#define ExprGroupID_MaxLen            24
#define EXPR_MAX_COUNT                32


//2021-7-7 add mym
/*
<group name="ͨ��" id="Common" data-type="" value="">
	<group name="��A" id="TtripA" data-type="" value="">
		<data name="���ʽ" id="exp1" data-type="" value="TtripA &gt; 0"/>
		<data name="���ʽ" id="exp1" data-type="" value="TtripA &lt;= 0"/>
		<data name="���ʽ" id="exp2" data-type="" value="(TtripA &gt; 0) &amp;&amp;  (TtripA &lt; TSet2)"/>
		<data name="���ʽ" id="exp3" data-type="" value="(TtripA &gt; 0) &amp;&amp; (TtripA &lt; g_TerrAbs)"/>
	</group>
*/
typedef struct tmt_data_rslt_expr
{
	////���ݵ�ID�����硰TtripA��
	char m_pszExprDataID[32];    

	 //���ݵ�ǰʹ�õı��ʽ������"TtripA &gt; 0"
	char  m_pRsltExpr[PARAS_RSLT_EXPR_LEN];   

}TMT_PARAS_RSLT_EXPR,   *PTMT_PARAS_RSLT_EXPR;

//2021-7-7 add mym
typedef struct tmt_paras_rslt_expr_mngr  //���Ե���Խ���жϱ��ʽ�ĸ���������һ����һ����Ҳ������һ������һ�� 
{
	long  m_nCount;  

	//�������б��ʽѡ�����m_pszExprGroupID��m_pszExprDataID��ͬ����
	//���ʽ������ID   �����硰Common��
	char m_pszExprGroupID[ExprGroupID_MaxLen];		

	TMT_PARAS_RSLT_EXPR   m_RsltExprs[EXPR_MAX_COUNT];

}TMT_PARAS_RSLT_EXPR_MNGR,  *PTMT_PARAS_RSLT_EXPR_MNGR;

typedef struct tmt_paras_head
{
public:
	char m_pszMacroID[TMT_PARAS_HEAD_MACROID_LEN];  //���Թ���ID;
	long m_nVersionRead;  //���Թ��ܲ����ṹ��İ汾�ţ���ȡģʽ�¼�¼��Դ���ݰ汾��
	long m_nVersion;  //���Թ��ܲ����ṹ��İ汾��
	long m_nTestState; //����״̬  0=δ���ԣ� 1=������ɣ��ϸ�2=������ɣ����ϸ�
	long m_nSelected;//�������Ƿ�ѡ��  zhouhj 20210712 

	//2021-9-7  lijunqing
	void *m_pDrawRef;   //��ͼ��������ã����û�л�ͼ������ΪNULL

	virtual ~tmt_paras_head(){}//zhouhj 20210623 ���Ӹú���,delete�����ж���ʱ,����

	TMT_PARAS_RSLT_EXPR_MNGR m_oRsltExprMngr;               //2021-7-7 add mym

	void init_head()
	{
			m_pszMacroID[0] = 0;  //���Թ���ID;
			m_nVersionRead = 0;  //���Թ��ܲ����ṹ��İ汾�ţ���ȡģʽ�¼�¼��Դ���ݰ汾��
			m_nVersion = 0;  //���Թ��ܲ����ṹ��İ汾��
			m_nTestState = 0; //����״̬  0=δ���ԣ� 1=������ɣ��ϸ�2=������ɣ����ϸ�
			m_nSelected = 1;//�������Ƿ�ѡ��  zhouhj 20210712 
			m_pDrawRef = NULL;
			memset(&m_oRsltExprMngr, 0, sizeof(TMT_PARAS_RSLT_EXPR_MNGR));
			//m_oRsltExprMngr.m_nCount = 5;
	}

	tmt_paras_head &operator = (const tmt_paras_head &paras)
	{
		::memcpy(m_pszMacroID, paras.m_pszMacroID, TMT_PARAS_HEAD_MACROID_LEN);
		m_nVersionRead = paras.m_nVersionRead;
		m_nVersion = paras.m_nVersion;
		m_nSelected = paras.m_nSelected;
		m_nTestState = paras.m_nTestState;
		return *this;
	}

	virtual void clear_result(){}

}TMT_PARAS_HEAD, *PTMT_PARAS_HEAD;

void stt_xml_serialize(PTMT_PARAS_HEAD pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(PTMT_PARAS_RSLT_EXPR_MNGR	pRsltExprMngr,   CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize(PTMT_PARAS_RSLT_EXPR 	pRsltExpr, long nIndex,  CSttXmlSerializeBase *pXmlSerialize);

CString stt_get_test_item_name(PTMT_PARAS_HEAD pParas);	//2021-7-15  lijunqing ��ȡ���Ե������

void stt_clone_expr_mngr(TMT_PARAS_RSLT_EXPR_MNGR pSrc, TMT_PARAS_RSLT_EXPR_MNGR pDest);//2021-7-21  lijunqing  ��¡���ʽ
void stt_clone_expr_mngr(PTMT_PARAS_HEAD pSrc, PTMT_PARAS_HEAD pDest);

//2022-1-8  lijunqing zhoulei zhouhongjun shefu
//���Թ��ܲ����ṹ���õ��������������ݣ�LINUX TestCtrl����Ҫ����̫��ĺ�Device��ص�����
//��˽�������������Ϊȫ�ֱ���������Ӳ����Ϣ����ʼ������������
extern int g_nBinExCount;//=MAX_ExBINARY_COUNT;
extern int g_nBoutExCount;//=MAX_ExBINARY_COUNT;

extern int g_nBinCount;//MAX_BINARYIN_COUNT
extern int g_nBoutCount;//MAX_BINARYOUT_COUNT
extern int g_nStateCount;//=20;
#endif //NOT_USE_TMT_TEST_PARAS_HEAD
