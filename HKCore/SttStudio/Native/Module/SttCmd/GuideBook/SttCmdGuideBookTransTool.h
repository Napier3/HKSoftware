//SttCmdGuideBookTransTool.h  CSttCmdGuideBookTransTool

#pragma once

#include "SttGuideBook.h"
#include "../../../../AutoTest/Module/GuideBook/GuideBook.h"
#include "../SttMsgs.h"

/*该类作为CGuideBook与CSttGuideBook类的转换工具类
1、Trans：从CGuideBook转换到CSttGuideBook；
2、ReverseTrans：从CSttGuideBook转换到CGuideBook；
*/
class CSttCmdGuideBookTransTool
{
public:
	CSttCmdGuideBookTransTool();
	virtual ~CSttCmdGuideBookTransTool();

	static BOOL g_bOnlyItemsTree;  //只转换项目分类目录

public:
    void Trans(CGuideBook *pGuideBook, CSttGuideBook *pSttGuideBook);

public:   //2022-9-14  lijunqing
    void Trans(CDevice *pDevice, CSttDevice *pSttDevice);
	void Trans(CExBaseList *pGbList, CExBaseList *pSttParent);
    void Trans(CItems *pItems, CSttItems *pSttItems);
    void Trans(CMacroTest *pMacroTest, CSttMacroTest *pSttMacroTest);
	void TransEx(CMacroTest *pMacroTest, CSttMacroTest *pSttMacroTest);
	void Trans(CCommCmd *pCommCmd, CSttCommCmd *pSttCommCmd);
	void TransEx(CCommCmd *pCommCmd, CSttCommCmd *pSttCommCmd);
	void Trans(CCmd *pCmd, CSttCommCmdData *pSttCommCmdData);  //2022-9-14  lijunqing
	void Trans(CReportMap *pRptMap, CSttReportMap *pSttRptMap);  //2022-9-24  SHAOLEI
    void Trans(CSafety *pSafety, CSttSafety *pSttSafety);
	void Trans(CSysParaEdit *pSysParaEdit, CSttSysParaEdit *pSttSysParaEdit);
    void TransItemBase(CGbItemBase *pItemBase, CSttItemBase *pSttItemBase);
	void Trans(CReports *pReports, CSttReports *pSttReports);
	void Trans(CReport *pReport, CSttReport *pSttReport);
	void Trans(CTestMacroUiParas *pUiParas, CSttTestMacroUiParas *pSttUiParas);
	void Trans(CTestMacroCharParas *pCharParas, CSttTestMacroCharParas *pSttCharParas);
	void Trans(CMacroCharItems *pMacroCharItems, CSttMacroCharItems *pSttMacroCharItems);
	void Trans(CCharacteristic *pCharacteristic, CSttCharacteristic *pSttCharacteristic);
	void Trans(CItemRsltExprRun*pRsltExpr, CSttItemRsltExpr*pSttRsltExpr);

//2022-9-14  lijunqing
public:
	void Trans(CSttCommCmd *pSrc, CCommCmd *pDest);
	void Trans(CSttCommCmdData *pSrc, CCmd *pDest); 

//shaolei 2023-10-09
public:
	void ReverseTrans(CReports *pReports, CSttReports *pSttReports);
	void ReverseTrans(CReport *pReport, CSttReport *pSttReport);
};

//2022-06-14 shaolei
//安全措施的Msg列表，转换成CSttMsgs链表
void MsgLists_to_SttMsgs(CExBaseList *pMsgs, CExBaseList *pSttMsgs);
void stt_AtsInitSttReport_DataType(CSttReport *pSttReport, CGbItemBase *pItem, BOOL bInitName = FALSE);  //shaolei  2023-1-6  处理电气量项目报告数据的数据类型和名称
void stt_AtsInitSttReport_Name(CDvmValue *pValue, CXExprNode *pNode);  //shaolei  2023-7-15  处理电气量项目报告数据的名称
