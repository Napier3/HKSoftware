#pragma once

#include "../../../Module/DataMngr/DataGroup.h"
#include "GbItemsGen.h"
#include "../GuideBook/GuideBook.h"
#include "../../../SttStudio/Module/UI/Config/MacroTestUI/SttMacroTestUI_TestMacroUIDB.h"
#include "../../../SttStudio/Module/SttCmd/SttChMaps.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"
#include "../../../SttStudio/Module/SttCmd/SttMacro.h"
#include "../../../SttStudio/Module/SttCmd/GuideBook/SttContents.h"
#include "../GuideBook/ItemRsltExprRun.h"
#include "../../../SttStudio/Module/SttSystemConfig/SttSystemConfig.h"
#include "../../../Module/Expression/XExprCal.h"

//���Թ��ܲ����������ͣ�0-ԭ��̬���棻1-��ҳ����
#define TESTMACRO_UI_TYPE_ORIGINAL   0
#define TESTMACRO_UI_TYPE_WEB        1 
#define TESTMACRO_UI_TYPE_ERROR      2   //���ɹ����ļ��ͽ���HTML�ļ�û�г������ã���Ϊ���ó���

#define TEST_CLASS_AIN           _T("YC")//_T("���Ȳ���")
#define TEST_CLASS_RELAY         _T("Relay")//_T("�������ܲ���")
#define TEST_CLASS_INFO_Relay    _T("Info-Relay")//_T("��Ϣ�淶������-��������")
#define TEST_CLASS_YK            _T("YK")//_T("��Ϣ�淶������-Զ������")
#define TEST_CLASS_YX            _T("YX")//_T("ң�Ų���")

//����ģ������ģʽ��0-��ͨģʽ��1-��ʼ����ʱ����ģ��
#define TEMPLATE_GEN_MODE_NORMAL     0   //��ͨģʽ����Ҫ�������ɲ���ǰ׼����Ŀ��ϵͳ���á�Ӳ��ͨ�����á�IEC����
#define TEMPLATE_GEN_MODE_STARTTEST  1   //��ʼ����ʱ����ģʽ�����������ɲ���ǰ׼����Ŀ������ǰ׼����Ŀ�Ĳ������������������ù��ģ������������ɸ��ǣ�
#define TEMPLATE_GEN_MODE_SAVE       2   //����ģ��ʱ������Ĭ��ֵ�Ĳ�����������ɾ��

#define FILENAME_STTIECCONCFIG	 "SttIecConfig.ixml"
#define FILENAME_STTSYSTEMPARAS	 "SystemParas.sysxml"
#define FILENAME_COMMCMDWZDCFG   "commcmd-wzd-cfg.xml"
#define FILENAME_STTCOMMCMDCFG   "SttCommCmdCfg.xml"
#define FILENAME_STTSYSTEMCONFIG	 "SystemConfig.xml"

//����ж��߼�
#define ERROR_LOGIC_ABS    0   //�������
#define ERROR_LOGIC_REL    1   //������
#define ERROR_LOGIC_OR     2   //�������  ��  ������
#define ERROR_LOGIC_AND    3   //�������  ��  ������
#define ERROR_LOGIC_COMB   4   //������   ��׼ֵ * rel% + abs

//�ݱ����
//1���ݱ�����
#define Gradient_VaryMode_Act      0    //����ֵ
#define Gradient_VaryMode_Return   1    //����ϵ��
#define Gradient_VaryMode_Angle    2    //���������
//2����������
#define Gradient_VarType_Val     0    //��ֵ�ݱ�
#define Gradient_VarType_Ph      1    //��λ�ݱ�
#define Gradient_VarType_Freq    2    //Ƶ�ʵݱ�
//3����ʱ��ֵ������λ�ݱ�ʱ����Ҫ�����ǵ�ѹ�ݱ仹�ǵ����ݱ�
#define Gradient_VarIndexType_I     0    //�����ݱ�
#define Gradient_VarIndexType_U     1    //��ѹ�ݱ�
#define Gradient_VarIndexType_F     2    //Ƶ�ʵݱ�

//г�����
#define Harm_VarIndexType_I     0    //�����ݱ�
#define Harm_VarIndexType_U     1    //��ѹ�ݱ�

//ͨ���������
#define Manual_VaryMode_Act      0    //����ֵ
#define Manual_VaryMode_Return   1    //����ϵ��

//��������
#define SequenceManu_VaryMode_Act      0    //����ֵ
#define SequenceManu_VaryMode_Return   1    //����ϵ��

//�ݱ�-�����
#define SequenceGradient_VarIndexType_I     0    //�����ݱ�
#define SequenceGradient_VarIndexType_U     1    //��ѹ�ݱ�

//ͨ������-�ߵ�ѹ
#define LineVoltManual_VarIndexType_I     0    //�����ݱ�
#define LineVoltManual_VarIndexType_U     1    //��ѹ�ݱ�

//�ݱ�-�ߵ�ѹ
#define LineVolGradient_VarIndexType_I     0    //�����ݱ�
#define LineVolGradient_VarIndexType_U     1    //��ѹ�ݱ�

//��������Ŀ���ظ�����ʱ��������㷽ʽ
#define MACROTEST_RPTCALMODE_AVERAGE    0
#define MACROTEST_RPTCALMODE_MAX        1
#define MACROTEST_RPTCALMODE_MIN        2

class CGbItemsGenTool
{
public:
	CGbItemsGenTool(void);
	virtual ~CGbItemsGenTool(void);

	//2022-3-29  lijunqing  ��ʹ��SmartTest.exe��ʱ��ϵͳ·��Ӧ����STT
	void InitGbGenSysPath(const CString &strSysPath);
	CString GetDBPath()		{	return m_strDbPath;		}
	CString GetConfigPath()	{	return m_strConfigPath;	}
	void AfterInitSysPath();
	CString GetDeviceModel();
	CString GetDevice_RelPath();  //��ȡ����װ���ͺ��£�����ļ������·����

private:
	CString m_strDbPath;
	CString m_strConfigPath;

public:
	CDataGroup *m_pUIParasGroup;   //�������
	CDataGroup m_oUiParas_SortIdPath;  //���ݽ���������漰��groupǶ�׵ģ���ȡ������·��  //shaolei 2025-4-2
	CDataGroup *m_pCommCmd;        //ͨѶ�����
	CItemsGenInterface *m_pCurrInstInterface;  //��ǰClass����Define��Interface

	CGbItemsGen *m_pGbItemsGen;   //ģ�����ɹ����ļ�
	CSttChMaps *m_pChMaps;   //Ĭ�ϵ�Ӳ��ͨ������
	CTestMacros *m_pTestMacros;  //���ݹ����ļ���������Ӧ�Ĳ��Թ����ļ�
	CIecCfgDatasMngr *m_pIecDatasMngr;   //IEC����
	CSttMacro *m_pSysParameter;   //ϵͳ��������
	CCharacteristics *m_pCharacteristics;   //��������
    long m_bHasDigital;
    long m_nGenWithDebug;
	long m_nLoopTest;

	UINT m_nUIType;
	CString m_strDvmFile;   //ģ���ļ�
	CString m_strTestClass;  //�������ͣ����Ȳ��ԡ����ܲ��ԡ���Ϣ�淶������-�������ܡ���Ϣ�淶������-Զ��������ң�Ų���
	CDataGroup m_oCommCmdWzdCfg;  //ͨѶ����-��������ӵ�����
	CDataGroup m_oSttCommCmdCfg;  //������ӵ�ͨѶ��������ݼ�����
	CDvmDevice m_oDvmDevice;
	CDataGroup *m_pAinDataMapCfg;  //��һ���·���ң��ͨ�����á������ң����Ŀʱ�����������ò�Ϊ�գ���ֱ�ӽ��в����滻��

protected:
	UINT m_nGenMode;
	CExBaseList m_oBeforeTestBk;  //����ǰ׼����Ŀ�ı��ݣ����ڴ��CItems����

private:
	CGuideBook *m_pGuideBook;
	CGbItemBase *m_pGbItemBase;  //ͨ��GenerateItems�������ɵĲ�����Ŀ
	CMacroTest *m_pMacroTest;   //ͨ��GenerateMacroTestָ��������ɵĵ�������Ŀ
	BOOL m_bMacroTestSaveParas;  //��������Ŀ���Ƿ񱣴������Linux�£�����ģ��ʱ���������
	CItems *m_pItems_SelfDef;  //ͨ����macro-selfdef-gen���ڵ㣬���ɵķ���ڵ�
	CItems *m_pDevReset; //װ�ø���̬������̬�Ķ��壺ѹ��ȫͶ��������ȫ�ˣ�������ֵȫ������Ϊ���ֵ
	CItems *m_pCmdAddGrp;  //����ǰ������ϡ���������ʱ�������ڴ�Ų���ǰ�������ڷ���Ӧ���ġ������ŵ�ģ����
	CItems *m_pItems_ImportDvm;  //����ģ�ͺ󣬸���ģ���������ɵ���Ŀ����ʱ���󣬱����ŵ�ģ���У������ڷ���Ӧ����
	CItems *m_pItems_AinCfg;  //ң��������ã��������úõ�ͨѶ�����ʱ���󣬱����ŵ�ģ���У������ڷ���Ӧ���ġ����ķ��غ󣬼�ʱɾ������
	CExBaseList m_oListAinCommCmds;  //������ӵ�ң��ͨѶ������ڱ���ԭʼ��������¡����ID��¼��Ŀ·��
	CSttSystemConfig m_oSttSystemConfig;  //ϵͳ���ã��ɻ�ȡװ���ͺ�

public:
	void FreeItems_DevReset();
	void FreeItems_ImportDvm(BOOL bDelete = TRUE);
	void FreeItems_AinCfg();
	CDvmData* SelectErrorLogic();
	long SelectErrorLimits(CExBaseList &oListError);
	long SelectDatasSets(CExBaseList &oListSets);

	CDvmDataset* GetGlobalDatas();
	CExBaseList* GetSysPara();
	void SetMacroTestSaveParas(BOOL bSave)	{	m_bMacroTestSaveParas = bSave;	}
	CGuideBook* GetGuideBook()	{	return m_pGuideBook;	}
    void SetGuideBook(CGuideBook* pGuideBook);
	CGbItemBase* GetGbItemBase()	{	return m_pGbItemBase;	}
	CGbItemBase* GetGbItems_CmdAddGrp()	{	return m_pCmdAddGrp;	}
	CGbItemBase* GetGbItems_ImportDvm()	{	return m_pItems_ImportDvm;	}
	CGbItemBase* GetGbItems_AinCfg()	{	return m_pItems_AinCfg;	}
	CGbItemBase* GetItems_BeforeTest();
	CString GetItemsPath_BeforeTest();
	CMacroTest* GetMacroTest()	{	return m_pMacroTest;	}
	CTestMacro* GetTestMacroByID(const CString &strMacroID);
	UINT GetTemplateGenMode();
	void SetTemplateGenMode(UINT nMode);
	void SetChMaps(CSttChMaps *pChMaps);
	void SetIecCfgDatasMngr(CIecCfgDatasMngr *pIecDatasMngr);
	void SetSysParameter(CSttMacro *pSysParameter);

	void Reset();
	BOOL IsUI_Original()	{	return m_nUIType == TESTMACRO_UI_TYPE_ORIGINAL;		}
	BOOL IsUI_Web()		{	return m_nUIType == TESTMACRO_UI_TYPE_WEB;		}
	BOOL IsUI_Error()	{	return m_nUIType == TESTMACRO_UI_TYPE_ERROR;	}
	BOOL IsTestClass_Ain()	{	return m_strTestClass == TEST_CLASS_AIN;	}

	BOOL Init(const CString &strUI);
	BOOL Init(CDataGroup *pTestMacroUI);
	void Init_UIType(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	BOOL Init_GenFile(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	BOOL Init_UIParaFile(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	BOOL Init_HdRsFile(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	BOOL Init_IecCfg();
	BOOL Init_SystemParas();

	void Init_UIType(CDataGroup *pGroup);
	BOOL Init_GenFile(CDataGroup *pGroup);    //ģ�����ɹ����ļ�
	BOOL Init_UIParaFile(CDataGroup *pGroup); //��������ļ�����ȡĬ�ϲ���
	BOOL Init_HdRsFile(CDataGroup *pGroup);   //Ӳ��ͨ�������ļ�����ȡĬ��Ӳ��ͨ�����ò���

	BOOL OpenGenFile(const CString &strFileName);
	BOOL OpenUIParaFile(const CString &strFileName);
	BOOL OpenHdRsFile(const CString &strFileName);
	BOOL OpenCommCmdWzdCfgFile();    //������������ӵ�ͨѶ����
	BOOL OpenSttCommCmdCfgFile();   //���ڵ�����ӵ�ͨѶ����

	BOOL Init_DvmDevice_Ex(const CString &strDvmFile);
	void Init_DvmDevice(const CString &strDvmFile);
	void Init_DvmDevice();
	void Init_DvmDevice_GetFullPath(CString &strFullPath);  //��ȡȫ·��
	void Init_TestMacroFile();
	BOOL NeedSetRootNode(const CString &strMacroID);
	void Ats_ConfigDevice(CDataGroup *pSttParas);

	void GetXml_TestMacroCharParas(CString &strParas);
	void GetXml_TestMacroUiParas(CString &strParas, const CString &strMacroID = _T(""));
	void GetXml_TestMacroUiParas(CString &strParas, CDataGroup *pUIParas, const CString &strMacroID = _T(""));
	//���������TestMacro�е�Ĭ�ϲ����Ƚϣ�ɾ��ֵ = Ĭ��ֵ�Ĳ���
	void SortTestMacroUiParas(CDataGroup *pUiParas, const CString &strMacroID);
	void SortTestMacroUiParas_ByDefault(CDataGroup *pUiParas, CDataGroup *pFaultParas);
	//�����״̬���У�����״̬����ɾ�������״̬�Ĳ���
	void SortTestMacroUiParas_ByStateCount(CDataGroup *pUiParas);
	void SortTestMacroUiParas_RsltEvalute(CDataGroup *pUiParas);

	void GenGuideBook(const CString &strMacroName, const CString &strMacroID, const CString &strDvmFile
		, const CString &strEngineProgID, const CString &strPpxmlFile);
	BOOL GenGuideBook_Items(const CString &strMacroName, const CString &strMacroID, const CString &strParentItemPath
		, const CString &strItemsName, const CString &strItemsID, long nRepeatTimes=0, long nRptTitle=0, long nTitleLevel=1);
	//�β�bGenerateRootItems�����ڱ�ʶ�Ƿ����ɸ���CItems�ڵ㡣bGenerateBFT���Ƿ����ɲ���ǰ׼����
	void GenGuideBook_Items(const CString &strMacroName, const CString &strMacroID, CGbItemBase *pParentItem, BOOL bGenerateRootItems = TRUE, BOOL bGenerateBFT = TRUE);
	void GenGuideBook_BeforeTest(CGbItemBase *pBeforeTestItems);
	void GenGuideBook_BeforeTest(CGbItemBase *pParentItem, const CString &strUI);
	void GenGuideBook_BeforeTest_FromFile(const CString &strUI);  //����UI��ID���ӻ���ģ���ж�ȡ����׼����Ŀ
	void GenguideBook_BeforeTest_CopyFormFile(CItems *pParentItems, const CString &strFile, const CString &strUI);
	void GenGuideBook_BeforeTest_StartTestMode(CGbItemBase *pBeforeTestItems);
	void GetBaseGbxmlFile(const CString &strUI, CString &strPath);
	CMacroTest* GenGuideBook_CreateMacroTest(const CString &strName, const CString &strID);

	void GenGbItemBase_Original(const CString &strMacroName, const CString &strMacroID, CGbItemBase *pParentItem, BOOL bGenerateBFT = TRUE);
	void GenGbItemBase_Define(CGbItemBase *pParentItem, CItemsGenInst *pInst);
	void GenGbItemBase_Define(CGbItemBase *pParentItem, CItemsGenNode *pNode);
	void GenGbItemBase_Define(CGbItemBase *pParentItem, CItemsGenCharItemLine *pLine, CCharacteristic *pCharacteristic, CItemsGenInst *pInst);
	//�½�һ���̶��Ĳ��Է�����Ŀ�������ء���Ϊ��ǰ�����ļ����в�����Ŀ�ĸ��ڵ�
	CItems* GenGbItemsBase_BaseItems(CItems *pRoot, const CString &strName, const CString &strID);
	CItems* GenGbItemsBase_Root(CMacroItemsGen *pMacroItemsGen, const CString &strName, const CString &strID);
	//�½����Է��࣬�������½��Ĳ��Է��࣬��Ϊ��һ���½�������Ŀ�ĸ��ڵ�
	CGbItemBase* GenGbItemBase_Define_Items(CGbItemBase *pParentItem, CItemsGenNode *pNode); 
	//�½���������Ŀ�������ص�������Ŀ�ĸ��ڵ㣬��Ϊ��һ���½�������Ŀ�ĸ��ڵ�
	CGbItemBase* GenGbItemBase_Define_MacroTest(CGbItemBase *pParentItem, CItemsGenNode *pNode);
	void GenGbItemBase_Define_MacroTest_InitMacroPara(CMacroTest *pMacroTest, CItemsGenNode *pNode);
    void GenGbItemBase_Define_MacroTest_InitReport(CMacroTest *pMacroTest, CExBaseList *pListParasMap=NULL);  //2022-3-15 lijunqing
	void GenGbItemBase_Define_MacroTest_InitReport_SortByDefault(CReport *pReport, CExBaseList *pListParasMap);  //2023-2-27  shaolei
	void GenGbItemBase_Define_MacroTest_InitReport(CMacroCharItems *pMacroCharItems);
	void GenGbItemBase_Define_MacroTest_InitReport_Characteristic(CMacroTest *pMacroTest);
	void GenGbItemBase_Define_MacroTest_InitReport_Expression(CString &strValue, CReport *pReport, const CString &strExpress); //��ʼ�����棬��������󶨶�ֵ��ϵͳ�������ʽ


	//������ԣ���Ӷ��������
	long GenGuideBook_MacroTest_Single(const CString& strMacroID, const CString& strParentItemPath, const CString& strItemsName, const CString& strItemsID, CDataGroup* pMacroParas);

	//�������ж�
	void GenGbItemBase_MacroTest_RsltExpr(CMacroTest *pMacroTest); 
	void GenGbItemBase_MacroTest_RsltExpr_StateTest(CMacroTest *pMacroTest);  //״̬����
	void GenGbItemBase_MacroTest_RsltExpr_StateTest(long nIndex, CDataGroup *pEvaluteGrp, CXExprNode *pExprNode);  //״̬���У�ÿһ��������
	void GenGbItemBase_MacroTest_RsltExpr_GradientTest(CMacroTest *pMacroTest);  //�ݱ�����
	void GenGbItemBase_MacroTest_RsltExpr_HarmTest(CMacroTest *pMacroTest);  //г��
	void GenGbItemBase_MacroTest_RsltExpr_ManualTest(CMacroTest *pMacroTest);  //ͨ������
	void GenGbItemBase_MacroTest_RsltExpr_SequenceManuTest(CMacroTest *pMacroTest);//ͨ������-�����
	void GenGbItemBase_MacroTest_RsltExpr_SequenceGradientTest(CMacroTest *pMacroTest);//�ݱ�-�����
	void GenGbItemBase_MacroTest_RsltExpr_LineVolGradientTest(CMacroTest *pMacroTest);//�ݱ�-�ߵ�ѹ
	void GenGbItemBase_MacroTest_RsltExpr_LineVoltManualTest(CMacroTest *pMacroTest);//ͨ������-�ߵ�ѹ

	void GenGbItemBase_MacroTest_RsltExpr(CMacroCharItems *pMacroCharItems, CItemGenRsltExpr* pRsltExprGen, CExBaseList *pInterface); 

	void InitRsltExpr(CItemRsltExprRun *pRsltExprRun, CExBaseList *pInterface, CItemGenRsltExpr* pExprNode, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprNode* pExprNode, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprCmp* pExprCmp, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprError* pExprError, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprErrorEx* pExprErrorEx, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprRange* pExprRange, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprRangeEx* pExprRangeEx, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprValueCal* pExprValueCal, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprValueCalEx* pExprValueCalEx, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprErrorCombined* pExprErrorCombined, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprCal* pXExprCal, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprCalSRpt* pXExprCalSRpt, CExBaseList *pParasMap);
	void InitRsltExpr_Value(CExBaseList *pInterface, CXExprValue *pExprValue, CExBaseList *pParasMap);
	void InitRsltExpr_Value_Expression(CExBaseList *pInterface, CXExprValue *pExprValue, CExBaseList *pParasMap);   //����pExprValue->m_strValueID�Ǳ��ʽ�����

	BOOL Expr_Mode_SetByMap(CExBaseList *pInterface, CString &strMode);   //����ж��߼�������ӳ�������������
	BOOL Expr_Use_SetByMap(CXExprBase *pExprBase, CExBaseList *pInterface);   //����ж��Ƿ����ã����ҽ��������������

	//�½�ͨѶ������Ŀ��������ͨѶ������Ŀ
	CGbItemBase* GenGbItemBase_Define_CommCmd(CGbItemBase *pParentItem, CItemsGenNode *pNode);
	void InitCommCmdAttr(CItemsGenCommCmd *pGenCommCmd, CCommCmd *pCommCmd);  //��ʼ��ͨѶ���������
	void InitCommCmdParas(CItemsGenCommCmd *pGenCommCmd, CCommCmd *pCommCmd);  //��ʼ��ͨѶ�����ͨѶ����

	void GenGbItem_CharItemLine(CMacroCharItemLineDef *pItemLineDef, CItemsGenCharItemLine *pItemGenLine);

	void GenGbCommCmd_After(CGbItemBase *pParentItem);
	void GenGbCommCmd_Before(CGbItemBase *pParentItem);
	void GenGbCommCmd(CGbItemBase *pParentItem, CDataGroup *pGroup);
	CGbItemBase*  GenGbCommCmd_Ex(CGbItemBase *pParentItem, CDataGroup *pGroup);
	void GenGbCommCmd_ReadAin(CGbItemBase *pParentItem);//���ɹ̶��Ķ�ң�ŵ�ͨѶ������Ŀ
	CCommCmd* GenGbCommCmd_NewCmd(CDataGroup *pGroup);
	BOOL GetCommCmdRwOptr(const CString &strCmdID, CString &strRwOptr);
	BOOL GetCommCmdName(const CString &strCmdID, CString &strName);

	void GenGbItemBase_Class(CGbItemBase *pParentItem, CItemsGenInst *pInst);

    BOOL SetItemPara(const CString &strMacroID, const CString &strItemPath, CDataGroup *pItemsParas, CSttContents *pContents);
    BOOL SetItemPara(CMacroTest *pMacroTest, CDataGroup *pItemsParas, CSttContents *pContents);
	BOOL SetItemPara(const CString &strItemPath, CSttContents *pRsltExpr);
    BOOL SetItemPara_SystemConfig(long nHasDigital);
	void SetItemPara_IecConfig(CSttContents *pContents);
	void SetItemPara_ChMapsConfig(CSttContents *pContents);

	BOOL UpdateItem(const CString &strItemPath, const CString &strItemType, CSttContents *pContents);
	BOOL QueryItem(const CString &strItemPath, CString &strItemPara);
	long OfflineSel(const CString &strDeviceModel, const CString &strDeviceSN);
	long Init_HdRsFile_Offline(const CString &strHdRsFile, const CString &strDeviceModel, const CString &strDeviceSN);
	long Init_SystemParas_Offline(const CString &strDeviceModel, const CString &strDeviceSN);
	long Init_IecCfg_Offline(long nHasDigital);

    void UpdateUIParas(CDataGroup *pUIParas);
	void AfterInitUIParas();  //���������ʼ�������º����������·�� shaolei 2025-4-2
	void AfterInitUIParas(CDataGroup *pGrp);  
	void UpdateCommCmd(CDataGroup *pCommCmd);
	void SetCharacteristics(CSttContents *pContents);
	CCharacteristic* FindCharacterByID(const CString &strID);
	void InitCharacteristicsByFile(const CString &strFile);
	void SaveGbXmlFile(const CString &strMacroID);
#ifndef _PSX_QT_LINUX_
	void SaveDscXmlFile(const CString &strMacroID);
#endif

	//�����ض��Ĳ��Թ��ܣ��Բ��Թ���ID����������������ݱ���Ե��������������
	void GenGbItem_MacroID_Revise(CString &strMacroID, CDataGroup *pUIParas);
	//�����ض��ĵ��������ܣ��Ե�������Ŀ��Name��ID��������������ϲ���Ԫ�Զ����Թ���
	void ResetMacroNameId(CItemsGenNode *pNode, CString &strName, CString &strID);

	//2022-3-29  lijunqing
	long GenerateItemsOnly(CDataGroup *pParas);
	long GenerateItemsOnly_Create(CDataGroup *p_PARA_generate_items);
	long GenerateItemsOnly_ItemsDelete(CGbItemBase* pItemParent, const CString &strItemsID);
	long GenerateItemsOnly_Create_AddDevReset(CGbItemBase *pParentItem);
	long CreateCommCmds_Write_ByDatasets(CExBaseList *pListDatasets, UINT nType, CGbItemBase* pItemParent, BOOL bDevReset, CItems *pItems = NULL);
	CItems* CloneDevReset(BOOL bIDUseReset);
	long GenerateItemsOnly_ItemsMoveUp(CGbItemBase* pItemParent, const CString &strItemsID, CDataGroup *p_PARA_generate_items);
	long GenerateItemsOnly_ItemsMoveDown(CGbItemBase* pItemParent, const CString &strItemsID, CDataGroup *p_PARA_generate_items);
	long GenerateItemsOnly_ItemsPaste(CGbItemBase* pItemParent, CDataGroup *p_PARA_generate_items);
	long GenerateItemsOnly_SafetyAdd(CGbItemBase* pItemParent, CDataGroup *pParas);
	long GenerateItemsOnly_CmdAddGrp(CGbItemBase* pItemParent,CDataGroup *p_PARA_generate_items);
	long GenerateItemsOnly_ImportDvmFile(CDataGroup *p_PARA_generate_items);
	long GenerateItemsOnly_ImportDvmFile_DvmMap(const CString &strDvmFile);   //ʹ��ģ��ӳ��
	long GenerateItemsOnly_ImportDvmFile_HasDvm(const CString &strDvmFile);
	long GenerateItemsOnly_ImportDvmFile_HasDvm(CGbItemBase *pGbItemParent);
	long GenerateItemsOnly_ImportDvmFile_HasDvm_Ex(CGbItemBase *pGbItemParent);
	long GenerateItemsOnly_ImportDvmFile_HasDvm(CGbItemBase *pGbItemParent, CItems* pItems, CGbCommCmd *pGbCmd);
	long GenerateItemsOnly_ImportDvmFile_NoDvm(const CString &strDvmFile);
	long GenerateItemsOnly_AinDataMap(CDataGroup *pAinDataMapCfg, CDataGroup *pAinRatios);
	long GenerateItemsOnly_AinDataMap(CItems *pItems, CDataGroup *pAinDataMapCfg);
	long GenerateItemsOnly_AinDataMap(CCommCmd *pCommCmd, CDataGroup *pAinDataMapCfg);
	long GenerateItemsOnly_AinDataMap(CXExprNode* pExprNode, CDataGroup *pAinDataMapCfg, CString &strDsPath);
	long GenerateItemsOnly_AinDataMap(CXExprValue *pExprValue, CDataGroup *pAinDataMapCfg, CString &strDsPath);
	long GenerateItemsOnly_CmdWzd(CDataGroup *pGenerateItems);
	void GenerateItemsOnly_Cmd_Ex(CDataGroup *pReply, CDataGroup *pParas, const CString &strMacroName);
	void GenerateItemsOnly_Cmd_Ex_register(CDataGroup *pReply, CGbCommCmd *pCmd);
	void GenerateItemsOnly_Cmd_Ex_write(CDataGroup *pReply, CGbCommCmd *pCmd, const CString &strMacroName);
	void GenerateItemsOnly_Cmd_Ex_read(CDataGroup *pReply, CGbCommCmd *pCmd, const CString &strMacroName);
	long GenerateItemsOnly_Cmd_Add(CDataGroup *pGenerateItems, CSttContents *pContents);
	long GenerateItemsOnly_Macro_Add(CDataGroup *pGenerateItems, CSttContents *pContents);
	long GenerateItemsOnly_Macro_Add_SystemConfig(CMacroTest *pMacroTest, CSttContents *pContents);

	void SetBinaryFileName();

	void GetdsKey(CStringArray &strKeyArray, const CString &strKey);
	CDevice* InitGuideBookForGenerateItemsOnly();
	BOOL m_bGenerateItemsOnly_CmdWzd;   //GenerateItemsָ�ͨѶ���������򵼵ı�ǡ���Ϊ��ָ��������GenerateItemsָ���Ӧ��һ�£������ӱ������
	CDataGroup m_oGroupCmdWzdReply;    //ͨѶ���������򵼣�Ӧ�������group

private:
	BOOL QueryItem_MacroTest(CExBaseObject *pItem, CString &strItemPara);
	BOOL QueryItem_Items(CExBaseObject *pItem, CString &strItemPara);
	BOOL QueryItem_CommCmd(CExBaseObject *pItem, CString &strItemPara);

	BOOL UpdateItem_MacroTest(CExBaseObject *pItem, CSttContents *pContents);
	BOOL UpdateItem_Items(CExBaseObject *pItem, CSttContents *pContents);
	BOOL UpdateItem_CommCmd(CExBaseObject *pItem, CSttContents *pContents);

	BOOL IsDvmData_BOOL(CDvmData *pData);

public:
	void ErrorLogicType(CXExprErrorEx *pErrorEx,long nErrorLogic);
	void ActionValueGradient(CItemRsltExprRun *pRsltExprRun,long nVarType,long nVarIndexType, const CString &strMacroID);//����ֵ�ݱ�
	void ReturnValueGradient(CItemRsltExprRun *pRsltExprRun);	//����ϵ��
	void MaxAngleValueGradient(CItemRsltExprRun *pRsltExprRun);//���������	
	void ActionTimeValue(CItemRsltExprRun *pRsltExprRun);//����ʱ��

	//�Ƿ�����ˡ�װ�ø���̬��
	CItems* IsHasDevReset();
	BOOL IsItemDevReset(CGbItemBase *pItemBase);  //�жϵ�ǰ������ǲ�������װ�ø���̬��
	BOOL IsGuideBookHasDvm();  //GuideBook�Ƿ��Ѿ�������豸����ģ��
	long GetGbCommCmdConfigs(CExBaseList *pListCommCmds, CExBaseList *pGbCommCmdConfigs);
	long GetDatasetsByGbCommCmd(CExBaseList *pListDatasets, CGbCommCmd *pGbCmd);
	void GetParentItemPath(const CString &strItemPath, CString &strParentPath); //����Ŀ·���У���ȡ����Ŀ·������$Ϊ�ָ���
	long GetAllAinItems(CExBaseList *pDestLists);
	long GetAllAinItems(CGbItemBase *pItemBase, CExBaseList *pDestLists);
	BOOL IsAinItems(const CString &strItemsID);
};
