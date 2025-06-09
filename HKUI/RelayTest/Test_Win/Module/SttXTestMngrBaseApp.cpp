#include "stdafx.h"
#include "SttXTestMngrBaseApp.h"
#include "../../Module/LiveUpdate/SttLiveUpdateShell.h"
#include "../../Module/SttTest/Common/tmt_adjust_sys_parameter.h"
#include "../../Module/SttSystemConfig/SttSystemConfig.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../Module/SttDevice/Module/PowerCtrl/SttPowerCtrlCom.h"
#include "Define.h"
#include "TestWinFrame/RsltWidget/RsltExprMngr.h"
#include "../../../Module/xml/PugiXML/pugixml.hpp"
#include <QCoreApplication>
#include <Windows.h>

//2021-9-16 lijunqing 后面再考虑动作、未动作的颜色状态
unsigned long  _CHARACTER_TEST_POINT_COLOR_Initial         =  RGB(255, 0, 0);                //初始状态颜色  红色
unsigned long  _CHARACTER_TEST_POINT_COLOR_Selected     =  RGB(0, 255, 255);              //选中状态颜色 青色
unsigned long  _CHARACTER_TEST_POINT_COLOR_EndOfTest  =  RGB(255, 0, 255);              //试验结束颜色 紫色
unsigned long  _CHARACTER_TEST_POINT_COLOR_TestLine     =  RGB(0, 255, 0);              //当前测试点直线颜色

CSttXTestMngrBaseApp* g_theSttXTestMngrBaseApp = NULL;

CSttXTestMngrBaseApp::CSttXTestMngrBaseApp()
{
	g_theSttXTestMngrBaseApp = this;
	m_bIECParasChanged = true;
	m_bGooseFlag = false;
	m_bFt3Flag=false;
	m_bViewTestStarted = false;

//2021-9-6  lijunqing 公共部分，后面在考虑集成到基类，避免错误
/*	InitXmlKeys();
	g_oSttTestAppCfg.SttOpen(g_oSttTestAppCfg.GetOldCfgFile());
	g_oSttTestResourceMngr.LoadDefaultIec61850Config();//放入QGooseParaWidget::initGooseTable()中加载
	g_oSttSystemConfig.OpenSystemConfig();
//	g_oSttSystemConfig.SaveSystemConfig();
	InitDefaultSystemParas();//在initData已去除初始化参数,故单独调用初始化函数

	//2021-5-30  lijunqing
	m_oTmtTestMngr.init();
*/
	m_pCharElementBase = NULL;
	m_pCharacteristics = NULL;
	m_bTmtParaChanged = FALSE;
	m_pCharacteristics = new CCharacteristics();
}

CSttXTestMngrBaseApp::~CSttXTestMngrBaseApp()
{
//	g_oSttTestAppCfg.SttSave(g_oSttTestAppCfg.GetOldCfgFile());//zhouhj 20211005 在关闭时,应该是保存,不是打开,并且此时,在修改IP地址后直接保存,关闭程序时无需再保存

	FreeXClientEngine();

	ReleaseXmlKeys();

	if (m_pSttTestResource != NULL)
	{
		delete m_pSttTestResource;
		m_pSttTestResource = NULL;
	}

	delete m_pCharacteristics;
}

long Global_GetModulePowerValue(CDataGroup *pModuleAttrs)
{
	CDvmData* pData = (CDvmData*)pModuleAttrs->FindByID(_T("ModulePower"));

	if (pData == NULL)
	{
		return -1;
	}

	return CString_To_long(pData->m_strValue);
}

void CSttXTestMngrBaseApp::initLocalSysPara()
{
	g_oSttTestResourceMngr.InitLocalSysPara();
}

void CSttXTestMngrBaseApp::GenerateTestCmdFromIEC(CSttParas &oSttParas)
{
	CIecCfgDatasMngr* pDatasMngr = &g_oSttTestResourceMngr.m_oIecDatasMngr;
	//oSttParas.AddNewChild(pDatasMngr);
	oSttParas.AddTail(pDatasMngr);//dingxy 20240508 解决iec探测闪退问题
}

void CSttXTestMngrBaseApp::GenerateTestCmdFromDefaultOutput(CSttTestCmd &oSttTestCmd)
{
	oSttTestCmd.m_strID = STT_CMD_TYPE_TEST_StartTest;
	oSttTestCmd.m_strTestor = STT_SOFT_ID_TEST;

	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->m_strID = MACROID_SttSystemDefaultOutput;

	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase* pMacroParas = oSttXmlSerializeTool.GetMacroParas();

	//序列化参数
	stt_xml_serialize(&g_oDefaultOutputPara, pMacroParas);

	//根据pDoc生成对象
	oSttTestCmd.DeleteAll();
	oSttXmlSerializeTool.SttXmlSerializeRead(&oSttTestCmd);
}

void CSttXTestMngrBaseApp::InitTestResource()
{
	if (m_pSttTestResource == NULL)
	{
		CreateTestResource();
		ASSERT(m_pSttTestResource);
		g_oSttTestResourceMngr.m_pTestResouce = m_pSttTestResource;
	}

	g_oSttTestResourceMngr.CreateChMaps();//打开本地通道映射文件
	initLocalSysPara();//在创建通道映射文件后,再初始化系统参数,如果当前缺省选择的输出模式有问题,如果选择了数字输出,但测试仪不支持数字输出,需要在初始化系统参数时,将对应设置取消
	g_oSttTestResourceMngr.ValidHardRsChMaps();//验证通道映射文件中硬件信息是否在Device中存在，删除不存在的硬件信息，如果不存在，则根据Device信息，创建缺省
	g_oSttTestResourceMngr.CreateSoftRsCh();
	g_oSttTestResourceMngr.CreateRtDataMngr();
	long nMergeCurrCoef = 1;

	if (g_oSttTestResourceMngr.GetAnalogCurrentMergeCoef(nMergeCurrCoef))
	{
		g_oLocalSysPara.m_fAC_CurMax *= nMergeCurrCoef;
		g_oLocalSysPara.m_fAC_CurMin *= nMergeCurrCoef;
		g_oLocalSysPara.m_fDC_CurMax *= nMergeCurrCoef;
		g_oLocalSysPara.m_fDC_CurMin *= nMergeCurrCoef;
	}
}

CString CSttXTestMngrBaseApp::getSystemParasFilePath()
{
	CString strFilePath = _P_GetConfigPath();
	strFilePath += FILE_SYSTEMPARA;

	return strFilePath;
}

CString CSttXTestMngrBaseApp::getSoeParasFilePath()
{
	CString strFilePath = _P_GetConfigPath();
	strFilePath += FILE_SOETESTPARA;

	return strFilePath;
}

long CSttXTestMngrBaseApp::OpenSoeParasFile(const CString& strSoeFile)
{
	long nRet = 0;
	CString strFile;

	if (strSoeFile.IsEmpty() || !IsFileExist(strSoeFile) || ParseFilePostfix(strSoeFile) != Postfix_SoeTest)
	{
		strFile = getSoeParasFilePath();
	}
	else
	{
		strFile = strSoeFile;
	}

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Soe测试参数文件【%s】不存在"),strFile.GetString());
		return FALSE;
	}

	CSttTestCmd oSttCmd;
	CSttMacro *pSttMacro = oSttCmd.GetSttMacro(TRUE,TRUE);

	CSttXmlSerializeTool oSttXmlSerializeTool;
	if (oSttXmlSerializeTool.CreateXmlSerializeRead(pSttMacro, strFile) == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("解析Soe测试参数文件失败【%s】"),strFile.GetString());
		return FALSE;
	}

	pSttMacro->SetCreateMacroChild(TRUE);
	oSttXmlSerializeTool.SttXmlSerializeRead(pSttMacro);

	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetParas();
	stt_xml_serialize(&m_oSoeParas, pMacroParas);

	return TRUE;
}

BOOL CSttXTestMngrBaseApp::SaveSoeParasFile(const CString& strSoeFile)
{
	CString strFile;

	CSttTestCmd oSttCmd;
	GenerateTestCmdFromSoeParas(oSttCmd);

	CSttMacro *pMacro = oSttCmd.GetSttMacro();
	CSttParas *pParas = pMacro->GetParas();
	ASSERT(pParas != NULL);

	if (strSoeFile.IsEmpty() || ParseFilePostfix(strSoeFile) != Postfix_SoeTest)
	{
		strFile = getSoeParasFilePath();
	}
	else
	{
		strFile = strSoeFile;
	}

	return pMacro->SaveXmlFile(strFile,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void CSttXTestMngrBaseApp::GenerateTestCmdFromSoeParas(CSttTestCmd &oSttTestCmd)
{
	oSttTestCmd.m_strID = STT_CMD_TYPE_TEST_StartTest;
	oSttTestCmd.m_strTestor = STT_SOFT_ID_TEST;

	CSttMacro *pMacro = oSttTestCmd.GetSttMacro(TRUE,TRUE);
	pMacro->m_strID = MACROID_SOETEST;

	CSttXmlSerializeTool oSttXmlSerializeTool;
	oSttXmlSerializeTool.CreateXmlSerializeWrite(pMacro);
	CSttXmlSerializeBase* pMacroParas = oSttXmlSerializeTool.GetParas();

	//序列化参数
	stt_xml_serialize(&m_oSoeParas, pMacroParas);

	//根据pDoc生成对象
	oSttTestCmd.GetSttMacro()->DeleteAll();
	oSttTestCmd.GetSttMacro()->SetCreateMacroChild(true);
	oSttXmlSerializeTool.SttXmlSerializeRead(oSttTestCmd.GetSttMacro());
}

// mym 评估 2012-07-21 系统参数数据 dataset；
void CSttXTestMngrBaseApp::GetSystemParaDataGroup()
{
	g_pTmt_SystemParaRef->DeleteAll();

	CSttDataGroupSerializeRegister oRegister(g_pTmt_SystemParaRef);
	stt_xml_serialize_ErrorValues(&g_oSystemParas, &oRegister);
}

void CSttXTestMngrBaseApp::OnTestInitialize(CEventResult *pEventInfo,CDataGroup *pParas)
{
	ASSERT(pParas != NULL);

	CDataGroup *pEventBinGroup = (CDataGroup*)pParas->FindByID(SYS_STATE_XEVENT_EVENTID_BIN);
	CDataGroup *pEventBoutGroup = (CDataGroup*)pParas->FindByID(SYS_STATE_XEVENT_EVENTID_BOUT);

	int i=0;
	char strName[10];
	if (pEventBinGroup)
	{
		for (i=1; i<=MAX_BINARYIN_COUNT; i++)
		{
			sprintf(strName,"Bin%03d",i);
			stt_GetDataValueByID(pEventBinGroup, strName, pEventInfo->m_BinIn[i-1]);
		}

		for (i=1; i<=MAX_ExBINARY_COUNT; i++)
		{
			sprintf(strName,"BinEx%03d",i);
			stt_GetDataValueByID(pEventBinGroup, strName, pEventInfo->m_BinInEx[i-1]);
		}
	}

	if (pEventBoutGroup)
	{
		for (i=1; i<=MAX_BINARYOUT_COUNT; i++)
		{
			sprintf(strName,"Bout%03d",i);
			stt_GetDataValueByID(pEventBoutGroup, strName, pEventInfo->m_BinOut[i-1]);
		}

		for (i=1; i<=MAX_ExBINARY_COUNT; i++)
		{
			sprintf(strName,"BoutEx%03d",i);
			stt_GetDataValueByID(pEventBoutGroup, strName, pEventInfo->m_BinOutEx[i-1]);
		}
	}
}

void CSttXTestMngrBaseApp::EndBinStateOnStarting()
{
	//初始化开入
	for (int i=0;i<g_nBinCount/*g_nBinCount*/;i++)
		m_oCurrEventResult.m_BinIn[i] = 0;

	//初始化扩展开出
	for (int i=0;i<g_nBinExCount;i++)
		m_oCurrEventResult.m_BinInEx[i] = 0;

	//初始化开出
	for (int i=0;i<g_nBoutCount/*g_nBoutCount*/;i++)
		m_oCurrEventResult.m_BinOut[i] = 0;

	//初始化扩展开出
	for (int i=0;i<g_nBoutExCount;i++)
		m_oCurrEventResult.m_BinOutEx[i] = 0;

	//UpdateToolButtons();//????????????????????????
}
//////////////////////////////////////////////////////////////////////////
//
BOOL CSttXTestMngrBaseApp::HasNextNeedTest()
{
	return GetNextItemNeedTest() >= 0 ;
}

long CSttXTestMngrBaseApp::GetNextItemNeedTest()
{
	if (m_oTmtTestMngr.m_nCount == 0)
	{
		return -1;
	}

	long nCurrIndex = 0;
	nCurrIndex  = m_nCurrTestIndex + 1;

	for (; nCurrIndex < m_oTmtTestMngr.m_nCount; nCurrIndex++)
	{
		if (m_oTmtTestMngr.m_pParasBuffer[nCurrIndex]->m_nSelected != 0)
		{
			break;
		}
	}

	if (nCurrIndex < m_oTmtTestMngr.m_nCount)
	{
		return nCurrIndex;
	}
	else
	{
		return -1;
	}
}

BOOL CSttXTestMngrBaseApp::TestCurrTestPoint()
{
	PTMT_PARAS_HEAD pCurr = NULL; //2021-9-16  lijunqing 当前测试点
	pCurr = m_oTmtTestMngr.m_pParasBuffer[m_nCurrTestIndex];

	if (pCurr != NULL)
	{
		if (pCurr->m_pDrawRef != NULL)
		{
			((CXDrawBase*)pCurr->m_pDrawRef)->m_crForeColor = _CHARACTER_TEST_POINT_COLOR_Selected;
			//当前测试点改为使用青色
		}
	}

	SendStartCmd();

	return TRUE;
}

void CSttXTestMngrBaseApp::FinishTestPoint( int nIndex)
{
	PTMT_PARAS_HEAD pCurr = NULL; //2021-9-16  lijunqing 当前测试点
	pCurr = m_oTmtTestMngr.m_pParasBuffer[nIndex];

	if (pCurr != NULL)
	{
		if (pCurr->m_pDrawRef != NULL)
		{
			((CXDrawBase*)pCurr->m_pDrawRef)->m_crForeColor = _CHARACTER_TEST_POINT_COLOR_EndOfTest;
		}
	}
}

void CSttXTestMngrBaseApp::GenerateTestCmdFromParas(CSttTestCmd &oSttTestCmd,bool bSel)
{
	InitTestCmdFromParas(oSttTestCmd, STT_CMD_TYPE_TEST_StartTest, bSel);
}

void CSttXTestMngrBaseApp::UpdateTestCmdFromParas(CSttTestCmd &oSttTestCmd,bool bSel)
{
	InitTestCmdFromParas(oSttTestCmd, STT_CMD_TYPE_TEST_UpdateParameter, bSel);
}

void CSttXTestMngrBaseApp::InitTestCmdFromParas(CSttTestCmd &oSttTestCmd, const CString &strCmdID, bool bSel)
{
	PTMT_PARAS_HEAD p = Test_GetAt(m_nCurrTestIndex);
	oSttTestCmd.m_strID = strCmdID;
	oSttTestCmd.m_strTestor = STT_SOFT_ID_TEST;

	CSttMacro *pMacro = oSttTestCmd.GetSttMacro(FALSE,FALSE);
	pMacro->m_strID = p->m_pszMacroID;

	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttXmlSerializeBase* pMacroSerializeBase = oSttXmlSerializeTool.CreateXmlSerializeWrite(pMacro);

	//序列化参数
	ASSERT(m_pSttTestResource);
	SerializeTestParas(pMacroSerializeBase, p,m_pSttTestResource->GetVolRsNum(),m_pSttTestResource->GetVCurRsNum(),
		g_nBinExCount,g_nBoutExCount,g_oSystemParas.m_nHasDigital);

	pMacro->SetCreateMacroChild(true);
	oSttXmlSerializeTool.SttXmlSerializeRead(pMacro);
}

void CSttXTestMngrBaseApp::ClearTestMngr()
{
//	m_nCurrTestIndex = 0;

	long nIndex = 0;
	PTMT_PARAS_HEAD p = NULL;

	for (nIndex=0; nIndex<m_oTmtTestMngr.m_nCount; nIndex++)
	{
		p = Test_GetAt(nIndex);
		if (p->m_nSelected != 0)    //20210923 sf 未勾选的不取消结果
		{
			p->m_nTestState = 0;
			ClearResult(p);
		}
	}
}

//2021-9-15  lijunqing 清除测试图形对象的状态
void CSttXTestMngrBaseApp::ClearResult(PTMT_PARAS_HEAD pHead)
{
	CXDrawBase *pDraw = (CXDrawBase*)pHead->m_pDrawRef;

	if (pDraw == NULL)
	{
		return;
	}

	pDraw->m_crForeColor = _CHARACTER_TEST_POINT_COLOR_Initial; //测试点标识为红色，代表初始状态 
}

long CSttXTestMngrBaseApp::OnUpdateSyncTime(CDataGroup *pRtSyncTime)
{
	return 0;
// 	long nSecond = 0,nNSecend = 0,nSyn = 0;
// 	stt_GetDataValueByID(pRtSyncTime, _T("Sync"), nSyn);
// 	stt_GetDataValueByID(pRtSyncTime, _T("Utc_s"), nSecond);
// 	stt_GetDataValueByID(pRtSyncTime, _T("Utc_ns"), nNSecend);
// 	OnUpdateGpsTime(nSyn,nSecond,nNSecend);
}


void CSttXTestMngrBaseApp::ChangeCurrTestPoint( int nIndex )
{
	PTMT_PARAS_HEAD pCurr = NULL;
	for (int i = 0; i < m_oTmtTestMngr.m_nCount; i++)
	{
		pCurr = m_oTmtTestMngr.m_pParasBuffer[i];
		if (i != nIndex)	//不是当前选中的点
		{
			if (pCurr->m_nTestState == 0)	//未测试
			{
				if (pCurr->m_pDrawRef != NULL)
				{
					((CXDrawBase*)pCurr->m_pDrawRef)->m_crForeColor = _CHARACTER_TEST_POINT_COLOR_Initial;		//初始状态
				}
			}
			else
			{
				if (pCurr->m_pDrawRef != NULL)
				{
					((CXDrawBase*)pCurr->m_pDrawRef)->m_crForeColor = _CHARACTER_TEST_POINT_COLOR_EndOfTest;	//测试结束
				}
			}
		}
		else
		{
			if (pCurr->m_pDrawRef != NULL)
			{
				((CXDrawBase*)pCurr->m_pDrawRef)->m_crForeColor = _CHARACTER_TEST_POINT_COLOR_Selected;		//选中
			}
		}
	}
}

void CSttXTestMngrBaseApp::DeleteAllDrawPoints()
{
//	CAutoSimpleLock oLock(m_oCriticSectionCharDrawList);
	POS pos = m_oCharDrawList.GetHeadPosition();
	CXDrawBase *p = NULL;
	POS posPrev = NULL;

	while(pos != NULL)
	{
		posPrev = pos;
		p = (CXDrawBase *)m_oCharDrawList.GetNext(pos);

		if (p->GetClassID() == DWCLASSID_CXDRAWPOINT_EX)
		{
			m_oCharDrawList.DeleteAt(posPrev);
		}
	}
}

PTMT_PARAS_HEAD CSttXTestMngrBaseApp::CreateTestParas(PTMT_PARAS_HEAD pCurr)
{
	return CreateTestParas(pCurr->m_pszMacroID);
}

void CSttXTestMngrBaseApp::Test_Add(PTMT_PARAS_HEAD pParas)
{
	stt_test_mngr_add(&m_oTmtTestMngr, pParas);
}

PTMT_PARAS_HEAD CSttXTestMngrBaseApp::Test_GetAt(long nIndex)
{
	return stt_test_mngr_get_at(&m_oTmtTestMngr, nIndex);
}

void CSttXTestMngrBaseApp::Test_InsertAt(PTMT_PARAS_HEAD pParas, long nIndex)
{
	stt_test_mngr_insert_at(&m_oTmtTestMngr, pParas, nIndex);
}

void CSttXTestMngrBaseApp::Test_SetAt(PTMT_PARAS_HEAD pParas, long nIndex)
{
	stt_test_mngr_set_at(&m_oTmtTestMngr, pParas, nIndex);
}

void CSttXTestMngrBaseApp::Test_DeleteAt(long nIndex)
{
	//2021-9-7  lijunqing
	PTMT_PARAS_HEAD pPara = m_oTmtTestMngr.m_pParasBuffer[nIndex];

	if (pPara != NULL)
	{
//		CAutoSimpleLock oLock(m_oCriticSectionCharDrawList);
		m_oCharDrawList.Delete((CExBaseObject*)pPara->m_pDrawRef);
	}

	stt_test_mngr_delete_at(&m_oTmtTestMngr, nIndex);
}

CString CSttXTestMngrBaseApp::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _P_GetMoudleFileName();
	strFile += _T(".");
	strFile += m_oTmtTestMngr.m_pszParaFilePostfix;

	return strFile;
}

CString CSttXTestMngrBaseApp::ReadXmlTplID( const CString & strSrcXmlFile )
{
	CString strTplID = _T("");
	//获取id
	pugi::xml_document srcXmlDoc;
	pugi::xml_parse_result srcXmlResult = srcXmlDoc.load_file(strSrcXmlFile.toLocal8Bit());
	if (srcXmlResult) 
	{
		pugi::xml_node srcXmlNode = srcXmlDoc.child(PUGIXML_TEXT("macros"));
		if (srcXmlNode) 
		{
			strTplID = 	CString(srcXmlNode.attribute(PUGIXML_TEXT("tpl_id")).value()).GetString();
		}
	}
	return strTplID;
}

CString CSttXTestMngrBaseApp::GetTplID()
{
	QString strExeName = QCoreApplication::applicationName();
	if(!strExeName.isEmpty())
	{
		return strExeName;
	}
	return _T("");
}

BOOL CSttXTestMngrBaseApp::IsCurrModuleTplID( const CString &strTplID )
{
	//获取系统exe名称
	CString strExeName = QCoreApplication::applicationName();
	if(strExeName == strTplID )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CSttXTestMngrBaseApp::OpenTestTestMngrFile(const CString& strParasFile)
{

	m_pCharElementBase = NULL;

	CString strFile;

	if (!IsValidTestParasFile(strParasFile))
	{
		//2024-01-07 wuxinyi 修改传参之后会打开默认模板文件
		if(IsValidTestParasFile(m_strDefaultParaFile))
		{
			strFile = m_strDefaultParaFile;
		}
		else
		{
		strFile = GetDefaultParaFile();
	}
	}
	else
	{
		strFile = strParasFile;
	}

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("功能测试参数文件【%s】不存在"),strFile.GetString());
		return FALSE;
	}


	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttXmlSerializeBase *pRootParas = NULL, *pParas = NULL;
	pRootParas = oSttXmlSerializeTool.CreateXmlSerializeRead(stt_TestMacrosKey(), strFile);


	if (pRootParas == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("解析功能测试参数文件【%s】失败"),strFile.GetString());
		return FALSE;
	}

	CString strTplID = ReadXmlTplID(strParasFile);
	if(!strTplID.IsEmpty())
	{
		if(!IsCurrModuleTplID(strTplID))
		{
			UpdateTestModule(strParasFile, strTplID);
			return FALSE;
		}
	}
// 	else
// 	{
// 		if(m_strLastFolderPath.isEmpty())
// 		{
// 			strFile = GetDefaultParaFile();
// 		}
// 		else
// 		{
// 			strFile = m_strFilePath;
// 		}
// 	}
	stt_xml_serialize(&m_oTmtTestMngr, pRootParas);


	long nIndex = 0;
	PTMT_PARAS_HEAD p = NULL;

	char szMacroID[TMT_PARAS_HEAD_MACROID_LEN];  //测试供能ID;
	memset(szMacroID,0,TMT_PARAS_HEAD_MACROID_LEN);

	for (nIndex=0; nIndex<m_oTmtTestMngr.m_nCount; nIndex++)
	{
		pParas = pRootParas->xml_serialize(stt_TestMacroKey(), nIndex, _T(""), _T(""), "macro");//zhouhj 20210712 创建Macro节点的时候,不再传递name和id

		if (pParas == NULL)
		{
			break;
		}

		stt_xml_serialize_ReadMacroID(pParas,szMacroID);
		p = CreateTestParas(szMacroID);
		stt_test_mngr_set_at(&m_oTmtTestMngr, p, nIndex);
		stt_xml_serialize(p, pParas);

		//2022.5.17 caoxc 
		p->m_nTestState = 0;

		SerializeTestParas(pParas, p,m_pSttTestResource->GetVolRsNum(),m_pSttTestResource->GetVCurRsNum(),
			g_nBinExCount,g_nBoutExCount,g_oSystemParas.m_nHasDigital);
//		delete p;
		ClearTestResult(p);
	}

	//2021-9-13  lijunqing  串行化特性曲线
	CXmlRWElementBase *pElement = pRootParas->GetElement();
	CXmlRWDocBase *pDoc = pRootParas->GetRWDoc();
	CXmlRWElementBase *pCharsElement = (CXmlRWElementBase*)pElement->GetChildNode(CCharacteristicXmlRWKeys::CCharacteristicsKey());

	if (pCharsElement != NULL)
	{
		if (m_pCharacteristics != NULL)
		{
			m_pCharacteristics->DeleteAll();
		}
		else
		{
			m_pCharacteristics = new CCharacteristics();
		}

		m_pCharacteristics->XmlRead(*pCharsElement, CCharacteristicXmlRWKeys::g_pXmlKeys);
	}

	//2024-4-16 wuxinyi 保存IEC配置相关参数
// 	CXmlRWElementBase *pIEcElement = pRootParas->GetElement();
// 	CXmlRWDocBase *pIecDoc = pRootParas->GetRWDoc();
// 	CXmlRWElementBase *pIECElementBase = (CXmlRWElementBase*)pIEcElement->GetChildNode(CCfgDataMngrXmlRWKeys::CIecCfgDatasMngrKey());
// 
// 	if (pIECElementBase != NULL)
// 	{
// 		g_oSttTestResourceMngr.m_oIecDatasMngr.DeleteAll();
// 		g_oSttTestResourceMngr.m_oIecDatasMngr.InitDatasMngr();
// 		g_oSttTestResourceMngr.m_oIecDatasMngr.XmlRead(*pIECElementBase, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
// 	}

	return TRUE;
}

BOOL CSttXTestMngrBaseApp::SaveTestMngrFile(const CString& strParasFile)
{
	m_bTmtParaChanged = FALSE;  //2021-9-13  lijunqing  参数编辑保存部分
	CString strFile;

	if (!IsValidTestParasFile(strParasFile,FALSE))
	{
		strFile = GetDefaultParaFile();
	}
	else
	{
		strFile = strParasFile;
	}

	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttXmlSerializeBase *pRootParas = NULL, *pParas = NULL;
	pRootParas = oSttXmlSerializeTool.CreateXmlSerializeRegister(stt_TestMacrosKey());

	if (pRootParas == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("解析功能测试参数文件【%s】失败"),strFile.GetString());
		return FALSE;
	}

	CString strTplID = GetTplID();//获取tpl_id

	CXmlRWDocBase* pRootDoc = pRootParas->GetRWDoc();
	CXmlRWElementBase *pDocElement = pRootDoc->GetDocElement();
	CXmlRWElementBase *pMacrosDoc =  (CXmlRWElementBase *)pDocElement->GetChildNode(stt_TestMacrosKey());
	pMacrosDoc->xml_SetAttributeValue(L"tpl_id",strTplID);

	stt_xml_serialize(&m_oTmtTestMngr, pRootParas);

	//2024-4-16 wuxinyi 增加iec配置参数
// 	CXmlRWElementBase *pIEcElement = pRootParas->GetElement();
// 	CXmlRWDocBase *pIecDoc = pRootParas->GetRWDoc();
// 	g_oSttTestResourceMngr.m_oIecDatasMngr.XmlWrite(*pIecDoc, *pIEcElement, CCfgDataMngrXmlRWKeys::g_pXmlKeys);

	long nIndex = 0;
	PTMT_PARAS_HEAD p = NULL;

	for (nIndex=0; nIndex<m_oTmtTestMngr.m_nCount; nIndex++)
	{
		p = stt_test_mngr_get_at(&m_oTmtTestMngr, nIndex);

		if (p == NULL)
		{
			break;
		}

		pParas = pRootParas->xml_serialize(stt_TestMacroKey(), nIndex, p->m_pszMacroID, p->m_pszMacroID, "macro");

		if (pParas == NULL)
		{
			break;
		}

		stt_xml_serialize(p, pParas);
		SerializeTestParas(pParas, p,m_pSttTestResource->GetVolRsNum(),m_pSttTestResource->GetVCurRsNum(),
			g_nBinExCount,g_nBoutExCount,g_oSystemParas.m_nHasDigital);
	}

	//2021-9-13  lijunqing  串行化特性曲线
	CXmlRWElementBase *pElement = pRootParas->GetElement();
	CXmlRWDocBase *pDoc = pRootParas->GetRWDoc();

	if (m_pCharacteristics != NULL)
	{
		m_pCharacteristics->XmlWrite(*pDoc, *pElement, CCharacteristicXmlRWKeys::g_pXmlKeys);
	}

	return oSttXmlSerializeTool.Stt_WriteFile(strFile);
}

void CSttXTestMngrBaseApp::OnReport_ReadDevice(const CString &strMacroID, CDataGroup *pParas)
{
	CDataGroup *pReadGroup = (CDataGroup*)pParas->FindByID(_T("Device"));
	ASSERT(pReadGroup);
	CSttAdjDevice oReadDevice;
	CSttAdjDevice *pCurDevice = &g_oSttTestResourceMngr.m_oCurrDevice;
	oReadDevice.AttatchAdjRef(pReadGroup);
	oReadDevice.GetAttrs();
	pCurDevice->GetAttrs();

	if (pCurDevice->m_pSttAdjRef == NULL)
	{
		pCurDevice->m_pSttAdjRef = new CDataGroup();
		pCurDevice->m_pSttAdjRef->SetParent(pCurDevice);
	}

	pCurDevice->m_pSttAdjRef->DeleteAll();
	pReadGroup->Copy(pCurDevice->m_pSttAdjRef);

	g_oSttSystemConfig.OpenSystemConfig();
	
	//如果信号或者装置SN不匹配，则需要重新读取Device信息
	if ((oReadDevice.m_strModel != pCurDevice->m_strModel)||(oReadDevice.m_strSN != pCurDevice->m_strSN)
		||(g_oSttSystemConfig.GetLockMaps() == 0))///wangtao 20240510 此处增加锁定映射判断
	{
		pCurDevice->GetAttrs();
		pCurDevice->SortModules();
		g_oSttTestResourceMngr.SetCurSelDevice(pCurDevice->m_strModel,pCurDevice->m_strSN);
		g_oSttTestResourceMngr.SaveCurDeviceFile();
		g_oSttTestResourceMngr.GetAllModuleTags();

		if (g_oSttSystemConfig.GetLockMaps() == 0)
		{
			CSttChMaps oSttChMaps;
			oSttChMaps.DeleteAll();
			g_oSttTestResourceMngr.m_oChMaps.Copy(&oSttChMaps);

			if (!g_oSttTestResourceMngr.CreateDefaultChMapsByDevice(&oSttChMaps,g_oSystemParas.m_nIecFormat,g_oSystemParas.m_nHasDigital))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_MissingDefaultMappings.GetString()); //缺少硬件资源文件,无法创建缺省通道映射 
				g_oSttSystemConfig.SaveSystemConfig();
				return;
			}
			oSttChMaps.Copy(&g_oSttTestResourceMngr.m_oChMaps);
			g_oSttTestResourceMngr.SaveCurChMapsFile();
		}

	}
	else//需要将读取出来的模块的电流档位等信息更新到系统参数中去??????????????????????????????????????????????????????????
	{
		pCurDevice->GetAttrs();
		pCurDevice->SortModules();
		g_oSttTestResourceMngr.SaveCurDeviceFile();
	}
    g_oSttSystemConfig.SaveSystemConfig();
	oReadDevice.AttatchAdjRef(NULL);
}

void CSttXTestMngrBaseApp::initDefaultSoeParaFile()
{
	m_oSoeParas.init();
}

int CSttXTestMngrBaseApp::GetTestItemTableRow(PTMT_PARAS_HEAD pCurr)
{
	for (int i=0;i<m_oTmtTestMngr.m_nCount;i++)
	{
		if(m_oTmtTestMngr.m_pParasBuffer[i] == pCurr)
		{
			return i;
		}
	}

	return -1;
}

BOOL CSttXTestMngrBaseApp::IsValidTestParasFile(const CString& strParasFile,BOOL bOpen)
{
	CString strPostfix = ParseFilePostfix(strParasFile);
	if (strParasFile.IsEmpty())
	{
		return FALSE;
	}

	if(strPostfix != m_oTmtTestMngr.m_pszParaFilePostfix && strPostfix != STT_UPDATE_TEST_XML_POSTFIX)
	{
		return FALSE;
	}

	if(bOpen && !IsFileExist(strParasFile))
	{
		return FALSE;
	}

	return TRUE;
}

// 评估 添加测试项的时候; 2021-7-23
//如果是新建测试点，需要根据m_strExprValueID中定义的数据，初始化测试点的各表达式
//pszExprGroupPath="Common",  "Gnd1"
//<group name="通用" id="Common" data-type="" value="">
//例如:<group name="接地距离一段" id="Gnd1" data-type="" value="">
/*
<group name="通用" id="Common" data-type="" value="">
	<group name="跳A" id="TtripA" data-type="" value="">
		<data name="表达式" id="exp1" data-type="" value="TtripA &gt; 0"/>
		<data name="表达式" id="exp1" data-type="" value="TtripA &lt;= 0"/>
		<data name="表达式" id="exp2" data-type="" value="(TtripA &gt; 0) &amp;&amp;  (TtripA &lt; TSet2)"/>
		<data name="表达式" id="exp3" data-type="" value="(TtripA &gt; 0) &amp;&amp; (TtripA &lt; g_TerrAbs)"/>
	</group>
	<group name="跳B" id="TtripB" data-type="" value="">

*/
void CSttXTestMngrBaseApp::InitTestParaExpr(PTMT_PARAS_HEAD pItemPara, char *pszExprGroupPath, bool bInit )
{
	long nIndex = 0;

	QRsltExprMngr::InitDataGroupByID(pszExprGroupPath);
	//pFind = <group name="通用" id="Common" data-type="" value="">
	CDataGroup *pFind =  NULL;//QRsltExprMngr::GetRsltExprMngr()->FindDataGroupByID(pszExprGroupPath);

	//从第XML文件DataDef中读取评估项的定义,比如有几个跳A,跳B,跳C 和几个结果数据的定义；
	CSttTmtRsltExprDefine*  pSttTmtRsltExprDefine  = g_oSttTmtRsltExprDefineMngr.FindRsltExprDefine(pItemPara->m_pszMacroID);
	
	if (pSttTmtRsltExprDefine->m_pExprDatasDef == NULL&&pSttTmtRsltExprDefine->m_pExprViewDatasDef==NULL)
		return;

	TMT_PARAS_RSLT_EXPR_MNGR *pExprMngr  =  &pItemPara->m_oRsltExprMngr;
	
	if (bInit)//当是TRUE的时候 说明SAVE文件中已经有了表达式的存储；当不相等的时候才往下执行，给结构体中赋初值，保存的时候把结构体保存到XML文件中。
	{
		// 当相等的时候 直接返回，说明SAVE文件中已经有了表达式的存储；当不相等的时候才往下执行，给结构体中赋初值，保存的时候把结构体保存到XML文件中。
		if (pSttTmtRsltExprDefine->m_pExprDatasDef->GetCount() == pExprMngr->m_nCount)
			return;
	}

	pExprMngr->m_nCount  =  pSttTmtRsltExprDefine->m_pExprDatasDef->GetCount(); //获取有几个跳A,跳B,跳C 这样的表达式的数量；
	strcpy(pExprMngr->m_pszExprGroupID, pszExprGroupPath);                                        //从外面传进来的ExprGroup 存入m_pszExprGroupID中；
	
	TMT_PARAS_RSLT_EXPR Expr  ;
	CDataGroup *pDataExprGroup = NULL;
	CDvmData *pData = NULL;

	for (nIndex  =  0; nIndex  <  pExprMngr->m_nCount; nIndex++)
	{
		//<data name="跳A" id="TtripA" data-type="" value=""/>
		pData = (CDvmData*)pSttTmtRsltExprDefine->m_pExprDatasDef->GetAtIndex(nIndex);
		
		//<group name="跳A" id="TtripA" data-type="" value="">
		pDataExprGroup  =  (CDataGroup *)QRsltExprMngr::FindDataGroupByID(pData->m_strID);

		//<data name="表达式" id="exp1" data-type="" value="TtripA &gt; 0"/>
		//初始化为第一个表达式是有问题的，可以初始化为空
		pData = (CDvmData*)pDataExprGroup->GetHead();  
		
		//新建数据表达式，并初始化
		//pExpr = new TMT_PARAS_RSLT_EXPR;

		//初始化为第一个表达式是有问题的，可以初始化为空
		//CString_to_char(pData->m_strValue,  pExpr->m_pRsltExpr);
		//Expr.m_pRsltExpr[0] = pData->m_strValue.GetString();//0;
		CString_to_char(pData->m_strID, Expr.m_pszExprDataID);

		//这里我又改成了初始化为第一个表达式，mym 2021-7-26;
		CString_to_char(pData->m_strValue, Expr.m_pRsltExpr);

		pExprMngr->m_RsltExprs[nIndex] = Expr;
	}

	AdjustTestParaExpr(pItemPara);
}

/*
// 本函数专门用来初始化用的；就是当XML文件中没有表达式的时候
void CSttXTestMngrBaseApp::InitTestParaExpr_Ex(PTMT_PARAS_HEAD pItemPara, char *pszExprGroupPath)
{
	long nIndex = 0;

	QRsltExprMngr::InitDataGroupByID(pszExprGroupPath);

	//pFind = <group name="通用" id="Common" data-type="" value="">
	CDataGroup *pFind =  NULL;//QRsltExprMngr::GetRsltExprMngr()->FindDataGroupByID(pszExprGroupPath);

	//从第XML文件DataDef中读取评估项的定义,比如有几个跳A,跳B,跳C 和几个结果数据的定义；
	CSttTmtRsltExprDefine*  pSttTmtRsltExprDefine  = g_oSttTmtRsltExprDefineMngr.FindRsltExprDefine(pItemPara->m_pszMacroID);
		
	if (pSttTmtRsltExprDefine->m_pExprDatasDef == NULL&&pSttTmtRsltExprDefine->m_pExprViewDatasDef==NULL)
		return;

	TMT_PARAS_RSLT_EXPR_MNGR *pExprMngr  =  &pItemPara->m_oRsltExprMngr;

	// 当相等的时候 直接返回，说明SAVE文件中已经有了表达式的存储；当不相等的时候才往下执行，给结构体中赋初值，保存的时候把结构体保存到XML文件中。
	if (pSttTmtRsltExprDefine->m_pExprDatasDef->GetCount() == pExprMngr->m_nCount)
		return;

	pExprMngr->m_nCount  =  pSttTmtRsltExprDefine->m_pExprDatasDef->GetCount(); //获取有几个跳A,跳B,跳C 这样的表达式的数量；
	strcpy(pExprMngr->m_pszExprGroupID, pszExprGroupPath);                                        //从外面传进来的ExprGroup 存入m_pszExprGroupID中；

	TMT_PARAS_RSLT_EXPR Expr  ;
	CDataGroup  *  pDataExprGroup = NULL;
	CDvmData  * pData = NULL;

	for (nIndex  =  0; nIndex  <  pExprMngr->m_nCount; nIndex++)
	{
		//<data name="跳A" id="TtripA" data-type="" value=""/>
		pData = (CDvmData*)pSttTmtRsltExprDefine->m_pExprDatasDef->GetAtIndex(nIndex);

		//<group name="跳A" id="TtripA" data-type="" value="">
		pDataExprGroup  =  (CDataGroup *)QRsltExprMngr::FindDataGroupByID(pData->m_strID);

		//<data name="表达式" id="exp1" data-type="" value="TtripA &gt; 0"/>
		//初始化为第一个表达式是有问题的，可以初始化为空
		pData = (CDvmData*)pDataExprGroup->GetHead();  

		//新建数据表达式，并初始化
		//pExpr = new TMT_PARAS_RSLT_EXPR;

		//初始化为第一个表达式是有问题的，可以初始化为空
		//CString_to_char(pData->m_strValue,  pExpr->m_pRsltExpr);
		//Expr.m_pRsltExpr[0] = pData->m_strValue.GetString();//0;
		CString_to_char(pData->m_strID, Expr.m_pszExprDataID);

		//这里我又改成了初始化为第一个表达式，mym 2021-7-26;
		CString_to_char(pData->m_strValue, Expr.m_pRsltExpr);

		pExprMngr->m_RsltExprs[nIndex] = Expr;
	}

	AdjustTestParaExpr(pItemPara);
}
*/

BOOL CSttXTestMngrBaseApp::IsTestAppExist(const CString &strIP)
{
	char pszIP[20];
	CString_to_char(strIP,pszIP);
	return xping(pszIP);
}

void CSttXTestMngrBaseApp::InitGoosePubDataGroups()
{
	m_listGoosePub.clear();
	CIecCfgGoutDatas *pSourceGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr();
	CIecCfgGoutDatas *pIecCfgGoutDatas = NULL;

	for (int i=0;i<m_oTmtTestMngr.m_nCount;i++)
	{
		pIecCfgGoutDatas = (CIecCfgGoutDatas*)pSourceGoutDatas->Clone();
		m_listGoosePub.append(pIecCfgGoutDatas);
	}
}

void CSttXTestMngrBaseApp::InitGooseGinPubDataGroups()
{
	m_listGooseGinPub.clear();
	CIecCfgGinDatas *pSourceGinDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGinMngr();
	CIecCfgGinDatas *pIecCfgGinDatas = NULL;

	for (int i=0;i<m_oTmtTestMngr.m_nCount;i++)
	{
		pIecCfgGinDatas = (CIecCfgGinDatas*)pSourceGinDatas->Clone();
		m_listGooseGinPub.append(pIecCfgGinDatas);
	}
}

void CSttXTestMngrBaseApp::InitFT3PubDataGroups()
{
	m_listFT3Pub.clear();
	CIecCfgDatasSMV *pSourceDatasSMV = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr();
	CIecCfgDatasSMV *pIecCfgDatasSMV = NULL;

	for (int i=0;i<m_oTmtTestMngr.m_nCount;i++)
	{
		pIecCfgDatasSMV = (CIecCfgDatasSMV*)pSourceDatasSMV->Clone();
		m_listFT3Pub.append(pIecCfgDatasSMV);
	}
}

void CSttXTestMngrBaseApp::SerializeGoosePubs(CSttXmlSerializeBase *pXmlGoosePubsParent,CIecCfgGoutDatas *pGoutDatas)
{
	if (pXmlGoosePubsParent == NULL)
	{
		return;
	}

	CSttXmlSerializeBase *pXmlGouts = pXmlGoosePubsParent->xml_serialize("GOOSEPubs", "GOOSEPubs", "GOOSEPubs", stt_ParaGroupKey());

	if ((pXmlGouts != NULL)&&g_oSystemParas.m_nHasDigital)
	{
		long nRet = 0;
		CXmlRWElementBase *pElementNode = pXmlGouts->GetElement();
		CDataGroup oGoutGroup;

		if (stt_xml_serialize_is_read(pXmlGouts))
		{
			CXmlRWNodeListBase *pChildNodeList = pElementNode->GetChildNodes();
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
			oGoutGroup.XmlReadChildren(*pChildNodeList, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
			pGoutDatas->ReadGouts_GroupDatas(&oGoutGroup);
		}
		else if (stt_xml_serialize_is_write(pXmlGouts)||stt_xml_serialize_is_register(pXmlGouts))
		{
			CXmlRWDocBase *pRootNode = pXmlGouts->GetRWDoc();
			pGoutDatas->GenerateGouts_GroupDatas(&oGoutGroup);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
			oGoutGroup.XmlWriteChildren(*pRootNode,*pElementNode, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
		}			
	}
}
void CSttXTestMngrBaseApp::SerializeGooseGinPubs(CSttXmlSerializeBase *pXmlGoosePubsParent,CIecCfgGinDatas *pGinDatas)
{
	if (pXmlGoosePubsParent == NULL)
	{
		return;
	}

	CSttXmlSerializeBase *pXmlGins = pXmlGoosePubsParent->xml_serialize("GOOSEGinPubs", "GOOSEGinPubs", "GOOSEGinPubs", stt_ParaGroupKey());

	if ((pXmlGins != NULL)&&g_oSystemParas.m_nHasDigital)
	{
		long nRet = 0;
		CXmlRWElementBase *pElementNode = pXmlGins->GetElement();
		CDataGroup oGoutGroup;

		if (stt_xml_serialize_is_read(pXmlGins))
		{
			CXmlRWNodeListBase *pChildNodeList = pElementNode->GetChildNodes();
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
			oGoutGroup.XmlReadChildren(*pChildNodeList, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
			pGinDatas->ReadGins_GroupDatas(&oGoutGroup);
		}
		else if (stt_xml_serialize_is_write(pXmlGins)||stt_xml_serialize_is_register(pXmlGins))
		{
			CXmlRWDocBase *pRootNode = pXmlGins->GetRWDoc();
			pGinDatas->GenerateGins_GroupDatas(&oGoutGroup);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
			oGoutGroup.XmlWriteChildren(*pRootNode,*pElementNode, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
		}			
	}
}
//chenling
void CSttXTestMngrBaseApp::SerializeFT3Pubs(CSttXmlSerializeBase *pXmlFT3PubsParent,CIecCfgDatasSMV *pIecCfgDatasSMV)
{
	if (pXmlFT3PubsParent == NULL)
	{
		return;
	}
 	CSttXmlSerializeBase *pXmlFT3=pXmlFT3PubsParent->xml_serialize("FT3Pubs", "FT3Pubs", "FT3Pubs", stt_ParaGroupKey());
 	
	if (pXmlFT3 != NULL&&g_oSystemParas.m_nHasDigital)
	{
		long nRet = 0;
		CXmlRWElementBase *pElementNode = pXmlFT3->GetElement();
		CDataGroup oGoutGroup;

		if (stt_xml_serialize_is_read(pXmlFT3))
		{
			CXmlRWNodeListBase *pChildNodeList = pElementNode->GetChildNodes();
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
			oGoutGroup.XmlReadChildren(*pChildNodeList, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
			pIecCfgDatasSMV->ReadSmv_GroupDatas(&oGoutGroup);
		}
		else if (stt_xml_serialize_is_write(pXmlFT3)||stt_xml_serialize_is_register(pXmlFT3))
		{
			CXmlRWDocBase *pRootNode = pXmlFT3->GetRWDoc();
			pIecCfgDatasSMV->GenerateSmv_GroupDatas(&oGoutGroup);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
			oGoutGroup.XmlWriteChildren(*pRootNode,*pElementNode, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
		}			
	}
}

void CSttXTestMngrBaseApp::GetSMVDataAppIDs(QList<int> &listAppIDs)
{
	listAppIDs.clear();
	CIecCfgDatasSMV *pIecCfgDatasSMV = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr();
	CIecCfgSmvDataBase *pIecCfgSmvData = NULL;

	for (int i=0;i<pIecCfgDatasSMV->GetCount();i++)
	{
		pIecCfgSmvData = (CIecCfgSmvDataBase*)pIecCfgDatasSMV->GetAtIndex(i);
		if (pIecCfgSmvData->GetClassID() != CFGCLASSID_CIECCFG92DATA)
		{
			continue;
		}

		listAppIDs.append(((CIecCfg92Data*)pIecCfgSmvData)->m_dwAppID);
	}
}

BOOL CSttXTestMngrBaseApp::OpenCharacteristicsFile(const CString &strFile)
{
	if (m_pCharacteristics == NULL)
	{
		m_pCharacteristics = new CCharacteristics();
	}

	return m_pCharacteristics->OpenXmlFile(strFile, CCharacteristicXmlRWKeys::g_pXmlKeys);
}






