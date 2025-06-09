#pragma once
//2021-5-30   lijunqing 
#include "../../SttTestBase/SttXmlSerialize.h"

#define TMT_PARAS_HEAD_MACROID_LEN  32	//2021-8-2 yyj空间加大，MacroID超过16会异常
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
<group name="通用" id="Common" data-type="" value="">
	<group name="跳A" id="TtripA" data-type="" value="">
		<data name="表达式" id="exp1" data-type="" value="TtripA &gt; 0"/>
		<data name="表达式" id="exp1" data-type="" value="TtripA &lt;= 0"/>
		<data name="表达式" id="exp2" data-type="" value="(TtripA &gt; 0) &amp;&amp;  (TtripA &lt; TSet2)"/>
		<data name="表达式" id="exp3" data-type="" value="(TtripA &gt; 0) &amp;&amp; (TtripA &lt; g_TerrAbs)"/>
	</group>
*/
typedef struct tmt_data_rslt_expr
{
	////数据的ID，例如“TtripA”
	char m_pszExprDataID[32];    

	 //数据当前使用的表达式，例如"TtripA &gt; 0"
	char  m_pRsltExpr[PARAS_RSLT_EXPR_LEN];   

}TMT_PARAS_RSLT_EXPR,   *PTMT_PARAS_RSLT_EXPR;

//2021-7-7 add mym
typedef struct tmt_paras_rslt_expr_mngr  //测试点测试结果判断表达式的个数，可是一个点一个，也可以是一个数据一个 
{
	long  m_nCount;  

	//下拉框中表达式选择项：由m_pszExprGroupID和m_pszExprDataID共同决定
	//表达式数据组ID   ，例如“Common”
	char m_pszExprGroupID[ExprGroupID_MaxLen];		

	TMT_PARAS_RSLT_EXPR   m_RsltExprs[EXPR_MAX_COUNT];

}TMT_PARAS_RSLT_EXPR_MNGR,  *PTMT_PARAS_RSLT_EXPR_MNGR;

typedef struct tmt_paras_head
{
public:
	char m_pszMacroID[TMT_PARAS_HEAD_MACROID_LEN];  //测试供能ID;
	long m_nVersionRead;  //测试功能参数结构体的版本号：读取模式下记录的源数据版本号
	long m_nVersion;  //测试功能参数结构体的版本号
	long m_nTestState; //测试状态  0=未测试； 1=测试完成，合格；2=测试完成，不合格
	long m_nSelected;//测试项是否被选择  zhouhj 20210712 

	//2021-9-7  lijunqing
	void *m_pDrawRef;   //绘图对象的引用，如果没有绘图对象，则为NULL

	virtual ~tmt_paras_head(){}//zhouhj 20210623 不加该函数,delete数组中对象时,报错

	TMT_PARAS_RSLT_EXPR_MNGR m_oRsltExprMngr;               //2021-7-7 add mym

	void init_head()
	{
			m_pszMacroID[0] = 0;  //测试供能ID;
			m_nVersionRead = 0;  //测试功能参数结构体的版本号：读取模式下记录的源数据版本号
			m_nVersion = 0;  //测试功能参数结构体的版本号
			m_nTestState = 0; //测试状态  0=未测试； 1=测试完成，合格；2=测试完成，不合格
			m_nSelected = 1;//测试项是否被选择  zhouhj 20210712 
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

CString stt_get_test_item_name(PTMT_PARAS_HEAD pParas);	//2021-7-15  lijunqing 获取测试点的名字

void stt_clone_expr_mngr(TMT_PARAS_RSLT_EXPR_MNGR pSrc, TMT_PARAS_RSLT_EXPR_MNGR pDest);//2021-7-21  lijunqing  克隆表达式
void stt_clone_expr_mngr(PTMT_PARAS_HEAD pSrc, PTMT_PARAS_HEAD pDest);

//2022-1-8  lijunqing zhoulei zhouhongjun shefu
//测试功能参数结构体用到了如下两个数据，LINUX TestCtrl不需要引入太多的和Device相关的内容
//因此将此两个变量改为全局变量。读完硬件信息，初始化此两个变量
extern int g_nBinExCount;//=MAX_ExBINARY_COUNT;
extern int g_nBoutExCount;//=MAX_ExBINARY_COUNT;

extern int g_nBinCount;//MAX_BINARYIN_COUNT
extern int g_nBoutCount;//MAX_BINARYOUT_COUNT
extern int g_nStateCount;//=20;
#endif //NOT_USE_TMT_TEST_PARAS_HEAD
