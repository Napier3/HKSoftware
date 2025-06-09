#include "stdafx.h"
#include "WzdMainDlg.h"
#include "WzdDlg_TestSenceSel.h"
#include "WzdDlg_ConnectTip.h"
#include "WzdDlg_IEDSel.h"
#include "WzdDlg_DvmRead.h"
#include "WzdDlg_DvmMap.h"
#include "WzdDlg_ImpSet.h"
#include "WzdDlg_IECCfg.h"
//#include "WzdDlg_AutoTest.h"
#include "../../../iSmartTestWzd/iSmartTestWzdDlg.h"
#include "../../../AutoTest/Module/TCtrlCntrDefine.h"
#include "../../../AutoTest/Module/XSttAtsTestClientImp.h"
#include "../../../../SttStudio/Module/SttCmd/GuideBook/SttCmdGuideBookTransTool.h"
//#include "../DataMngr/DataMngrTrans.h"
#include "../../../../Module/DataMngr/DataMngrTrans.h"
#include "MessageDlg.h"
CWzdMainDlg* g_pWzdMainDlg = NULL;
CThreadProgressInterface *g_theThreadPrgsDlg = NULL;

IMPLEMENT_DYNAMIC(CWzdMainDlg, CDialog)

CWzdMainDlg::CWzdMainDlg(CWnd* pParent /*=NULL*/)
: CWzdDlgBase(CWzdMainDlg::IDD, pParent)
{
	g_pWzdMainDlg = this;

	m_pDataCfg = NULL;
	m_pStepList = NULL;

	m_pCurIecCfgFile = NULL;
	m_pSmartTestClient = NULL;

	m_pThreadPrgsDlg = NULL;
}

CWzdMainDlg::~CWzdMainDlg()
{
	m_oStepsMngr.DeleteAll();
	if(m_pDataCfg)
	{
		delete m_pDataCfg;
		m_pDataCfg = NULL;
	}
	if(m_pStepList)
	{
		delete m_pStepList;
		m_pStepList = NULL;
	}

	if(m_pSmartTestClient)
	{
		delete m_pSmartTestClient;
		m_pSmartTestClient = NULL;
	}

	if(m_pThreadPrgsDlg)
	{
		delete m_pThreadPrgsDlg;
		m_pThreadPrgsDlg = NULL;
		g_theThreadPrgsDlg = NULL;
	}
}

void CWzdMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
 	DDX_Control(pDX, IDC_STATIC_TITLE, m_txtTitle);
 	DDX_Control(pDX, IDC_ICON_MAIN, m_btnIcon);
 	DDX_Control(pDX, IDC_BTN_PREV, m_btnPrev);
 	DDX_Control(pDX, IDC_BTN_NEXT, m_btnNext);
 	DDX_Control(pDX, IDC_LIST_STEP, m_listStep);
	DDX_Control(pDX, IDD_STEP_DIALOG, m_dlgStep);
	DDX_Control(pDX, IDC_MAIN_BORDER, m_grpBorder);
	DDX_Control(pDX, IDC_MAIN_BOTTOM, m_btnBottom);

}

void CWzdMainDlg::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
 	XUI_AddWnd(&m_txtTitle, 0, 0, 1, 0);
 	XUI_AddWnd(&m_btnIcon, 0, 0, 0, 0);
	XUI_AddWnd(&m_btnBottom, 0, 1, 1, 0);
 	XUI_AddWnd(&m_btnPrev, 0.5, 1, 0.1, 0);
 	XUI_AddWnd(&m_btnNext, 0.5, 1, 0.1, 0);
 	XUI_AddWnd(&m_listStep, 0, 0, 0, 1);
	XUI_AddWnd(&m_dlgStep, 0, 0, 1, 1);
	XUI_AddWnd(&m_grpBorder, 0, 0, 1, 1);
	CXUIAdjItem_Area::XUI_OnSize();
}

void CWzdMainDlg::InitDlgs()
{
	CRect rc = GetDlgRect();
	CWzdDlg_TestSenceSel* pTestSenceSel = new CWzdDlg_TestSenceSel;
	pTestSenceSel->Create(CWzdDlg_TestSenceSel::IDD, this);
	pTestSenceSel->OnInitialUpdate();
	pTestSenceSel->MoveWindow(rc);
	pTestSenceSel->ShowWindow(SW_SHOW);
	m_oStepsMngr.AddNewChild(pTestSenceSel, DLG_STEP_SenceSel);

	//��ģ���ڴ�ռ������ 13MB->334MB
 	CWzdDlg_DvmRead* pDvmRead = new CWzdDlg_DvmRead;
 	pDvmRead->Create(CWzdDlg_DvmRead::IDD, this);
 	pDvmRead->OnInitialUpdate();
 	pDvmRead->MoveWindow(rc);
 	pDvmRead->ShowWindow(SW_HIDE);
 	m_oStepsMngr.AddNewChild(pDvmRead, DLG_STEP_DvmRead);

	CWzdDlg_IEDSel* pIEDSel = new CWzdDlg_IEDSel;
	pIEDSel->Create(CWzdDlg_IEDSel::IDD, this);
	pIEDSel->OnInitialUpdate();
	pIEDSel->MoveWindow(rc);
	pIEDSel->ShowWindow(SW_HIDE);
	m_oStepsMngr.AddNewChild(pIEDSel, DLG_STEP_IEDSel);

	CWzdDlg_DvmMap* pDvmMap = new CWzdDlg_DvmMap;
	pDvmMap->Create(CWzdDlg_DvmMap::IDD, this);
	pDvmMap->OnInitialUpdate();
	pDvmMap->MoveWindow(rc);
	pDvmMap->ShowWindow(SW_HIDE);
	m_oStepsMngr.AddNewChild(pDvmMap, DLG_STEP_DvmMap);

	CWzdDlg_ImpSet* pImpSet = new CWzdDlg_ImpSet;
	pImpSet->Create(CWzdDlg_ImpSet::IDD, this);
	pImpSet->OnInitialUpdate();
	pImpSet->MoveWindow(rc);
	pImpSet->ShowWindow(SW_HIDE);
	m_oStepsMngr.AddNewChild(pImpSet, DLG_STEP_ImpSet);

	CWzdDlg_IECCfg* pIECCfg = new CWzdDlg_IECCfg;
	pIECCfg->Create(CWzdDlg_IECCfg::IDD, this);
	pIECCfg->OnInitialUpdate();
	pIECCfg->MoveWindow(rc);
	pIECCfg->ShowWindow(SW_HIDE);
	m_oStepsMngr.AddNewChild(pIECCfg, DLG_STEP_IECCfg);

	//��ʼ���� ���� yuanting
	//CWzdDlg_AutoTest* pAutoTest = new CWzdDlg_AutoTest;
	m_pAutoTest = new CWzdDlg_AutoTest;
	m_pAutoTest->Create(CWzdDlg_AutoTest::IDD, this);
	//��������
	//CExBaseList* pGlobalData = (CExBaseList*)m_oGuideBook.FindChildByID("GlobalDatas");
	//��ҵָ���� ��Device�ڵ�����
	//CExBaseList* pDevice = (CExBaseList*)m_oGuideBook.FindChildByID("Device");
	//pAutoTest->setDataInfo(m_oGuideBook.GetGlobalDatas(),m_oGuideBook.GetDevice());

	m_pAutoTest->OnInitialUpdate();
	m_pAutoTest->MoveWindow(rc);
	m_pAutoTest->ShowWindow(SW_HIDE);
	m_oStepsMngr.AddNewChild(m_pAutoTest, DLG_STEP_AutoTest);
	

// 	CWzdDlg_ConnectTip* pConnectTip = new CWzdDlg_ConnectTip;
// 	pConnectTip->Create(CWzdDlg_ConnectTip::IDD, this);
// 	pConnectTip->OnInitialUpdate();
// 	pConnectTip->MoveWindow(rc);
// 	pConnectTip->ShowWindow(SW_HIDE);
// 	m_oStepsMngr.AddNewChild(pConnectTip, DLG_STEP_ConnectTip);

	m_oStepsMngr.SetActiveDlg(pTestSenceSel);

	CString strFilePath = _P_GetConfigPath();
	strFilePath += "/";
	strFilePath += "SafetyComboDataType.xml";
	m_oDataTypes.OpenXmlFile(strFilePath, CDataMngrXmlRWKeys::g_pXmlKeys);
}

CWzdDlgButton* CWzdMainDlg::InitListItem(const CString& strText, BOOL bImg, void* pItemData)
{
	CString strImg = _P_GetResourcePath();
	strImg += "step/";
	CWzdDlgButton* pBtn = m_pStepList->AddNewItem(strText);
	pBtn->SetImgMode(bImg);
	pBtn->SetItemData(pItemData);
	pBtn->SetReadOnly(TRUE);
	return pBtn;
}

void CWzdMainDlg::InitList()
{
	CRect rc = GetListRect();
	CString strImg = _P_GetResourcePath();
	strImg += "iSmartTestWzd/step/";
	m_pStepList = new CWzdDlgList;
	m_pStepList->Create(CWzdDlgList::IDD, this);
	m_pStepList->MoveWindow(rc);

	CWzdDlgButton* pBtn = InitListItem(/*"����1:Ӧ�ó�������"*/"", TRUE, (CWzdDlgBase*)m_oStepsMngr.FindByID(DLG_STEP_SenceSel));
	pBtn->LoadImage(strImg + "step1_n.png", strImg + "step1_y.png", NULL, strImg + "step1_d.png");
	pBtn->m_strID = DLG_STEP_SenceSel;

	pBtn = InitListItem(/*"����2:ģ�Ͷ�ȡ"*/"", TRUE, (CWzdDlgBase*)m_oStepsMngr.FindByID(DLG_STEP_DvmRead));
	pBtn->LoadImage(strImg + "step2dvm_n.png", strImg + "step2dvm_y.png", NULL, strImg + "step2dvm_d.png");
	pBtn->m_strID = DLG_STEP_DvmRead;

	pBtn = InitListItem(/*"����2:IEDװ��ѡ��"*/"", TRUE, (CWzdDlgBase*)m_oStepsMngr.FindByID(DLG_STEP_IEDSel));
	pBtn->LoadImage(strImg + "step2ied_n.png", strImg + "step2ied_y.png", NULL, strImg + "step2ied_d.png");
	pBtn->m_strID = DLG_STEP_IEDSel;

	pBtn = InitListItem(/*"����3:վ�ز���Ϣ����"*/"", TRUE, (CWzdDlgBase*)m_oStepsMngr.FindByID(DLG_STEP_DvmMap));
	pBtn->LoadImage(strImg + "step3_n.png", strImg + "step3_y.png", NULL, strImg + "step3_d.png");
	pBtn->m_strID = DLG_STEP_DvmMap;

	pBtn = InitListItem(/*"����4:��ֵ���˶�"*/"", TRUE, (CWzdDlgBase*)m_oStepsMngr.FindByID(DLG_STEP_ImpSet));
	pBtn->LoadImage(strImg + "step4_n.png", strImg + "step4_y.png", NULL, strImg + "step4_d.png");
	pBtn->m_strID = DLG_STEP_ImpSet;

	pBtn = InitListItem(/*"����5:���̲�����"*/"", TRUE, (CWzdDlgBase*)m_oStepsMngr.FindByID(DLG_STEP_IECCfg));
	pBtn->LoadImage(strImg + "step5_n.png", strImg + "step5_y.png", NULL, strImg + "step5_d.png");
	pBtn->m_strID = DLG_STEP_IECCfg;

 	pBtn = InitListItem(/*"����6:�Զ�����"*/"", TRUE, (CWzdDlgBase*)m_oStepsMngr.FindByID(DLG_STEP_AutoTest));
 	pBtn->LoadImage(strImg + "step7_n.png", strImg + "step7_y.png", NULL, strImg + "step7_d.png");
 	pBtn->m_strID = DLG_STEP_AutoTest;


// 	pBtn = InitListItem(/*"����6:������ʾ����"*/"", TRUE, (CWzdDlgBase*)m_oStepsMngr.FindByID(DLG_STEP_ConnectTip));
// 	pBtn->LoadImage(strImg + "step6_n.png", strImg + "step6_y.png", NULL, strImg + "step6_d.png");
// 	pBtn->m_strID = DLG_STEP_ConnectTip;

// 	pBtn = InitListItem(/*"����7:��������"*/"", TRUE, NULL);
// 	pBtn->LoadImage(strImg + "step7_n.png", strImg + "step7_y.png", NULL, strImg + "step7_d.png");

	m_pStepList->SetCurSel((long)0);
	m_pStepList->CalItemsRect();
	m_pStepList->ShowWindow(SW_SHOW);
}

void CWzdMainDlg::InitBtns()
{
	CString strIcon = _P_GetResourcePath();
	strIcon += "iSmartTestWzd/";
 	m_btnIcon.LoadImage(strIcon + "title.jpg", strIcon + "title.jpg", strIcon + "title.jpg", strIcon + "title.jpg");
 	m_btnIcon.SetImgMode(TRUE);

	m_txtTitle.LoadImage(strIcon + "title2.png", strIcon + "title2.png", strIcon + "title2.png", strIcon + "title2.png");
	m_txtTitle.SetImgMode(TRUE);

	m_btnBottom.LoadImage(strIcon + "bk.png", strIcon + "bk.png", strIcon + "bk.png", strIcon + "bk.png");
	m_btnBottom.SetImgMode(TRUE);
}

void CWzdMainDlg::OnInitialUpdate()
{
	XUI_InitAdjust();

	//��������list
	InitList();

	//����������DLG
	InitDlgs();

	InitBtns();

	//20230619 huangliang ʹ���µĽ���������
	//m_pThreadPrgsDlg = new CThreadPrgsDlg();
	//m_pThreadPrgsDlg->Create(IDD_THREAD_PRGS_DLG, this);
	m_pThreadPrgsDlg = new CWzdDlgSendState();
	m_pThreadPrgsDlg->Create(IDD_DIALOG_SHOWSEND, this);
	m_pThreadPrgsDlg->CenterWindow();
	m_pThreadPrgsDlg->ShowWindow(SW_HIDE);
	g_theThreadPrgsDlg = m_pThreadPrgsDlg;
}

void CWzdMainDlg::JumpToPrevDlg()
{
	CWzdDlgBase* pDlg = (CWzdDlgBase*)m_oStepsMngr.GetActiveDlg();
	long nIndex = m_oStepsMngr.FindIndexByID(pDlg->m_strID);
	CWzdDlgBase* pTempDlg = pDlg;
	switch(nIndex)
	{
	case 0:
		//��ǰ�����ǲ���һ,����˵�������
		g_pISmartTestWzdDlg->SetActiveDlg(DLG_STEP_EntrySel);
		SetActiveDlg(DLG_STEP_SenceSel);
		return;
	default:
		pDlg = (CWzdDlgBase*)m_oStepsMngr.GetAt(nIndex - 1);
		while(!pDlg->IsEnabled())
		{
			//����һ�Ľ����������Ҳ����Ч��,���Կ���ʹ��while��ǰ����
			nIndex--;
			pDlg = (CWzdDlgBase*)m_oStepsMngr.GetAt(nIndex - 1);
		}
		break;
	}

	pTempDlg->DoPrev();
	SetActiveDlg(pDlg->m_strID);
	m_pStepList->SetCurSel((long)nIndex - 1);
}

//20230920 huangliang �����ƶ����ϴ���ȫ������
void CWzdMainDlg::SetDataInGlobal(CDvmDataset *dataG)
{
	dataG->Copy(&m_Recv0x92Data);
}
void CWzdMainDlg::SetRecv0x92DataInGlobal()	//20231025 luozibing ����0x92���������� 
{
	CDvmDataset *pGlobalDatas = m_oGuideBook.m_pGlobalDatas;
	if(pGlobalDatas == NULL)
		return;

	CDvmData *pValue = NULL;
	CDvmData *pFindV = NULL;
	POS pos = m_Recv0x92Data.GetHeadPosition();
	while(pos)
	{
		pValue = (CDvmData*)m_Recv0x92Data.GetNext(pos);

		pFindV = (CDvmData*)pGlobalDatas->FindByID(pValue->m_strID);
		if (pFindV != NULL)
		{
			pFindV->m_strValue = pValue->m_strValue;
			pFindV->m_strDataType = pValue->m_strDataType;
		}
		else
		{
			pGlobalDatas->AddNewChild((CDvmData *)pValue->Clone());
		}
	}
}
void CWzdMainDlg::ClearBlueData()
{
	//20230920 huangliang  ����������Ϊ��ֵ
	COrderInfo0x92 orderInfo;
	CDvmDataset *dataG = orderInfo.CreateDataGroup();
	SetDataInGlobal(dataG);

	dataG->DeleteAll();
	delete dataG;
}

void CWzdMainDlg::CreateNewTest()
{
	if (m_strGbXmlFile.IsEmpty())
	{
		return;
	}

	CString strGbrptFile,strIecfgFile,strXmlFile,SrcstrWzdxmlFile,strWzdxmlFile, strSrcJsonFile, strJsonFile;
	SYSTEMTIME tmSys;
	::GetLocalTime(&tmSys);	//20231017 huangliang ʱ���Ƶ��������ֱ�ע�͵�

	//֮ǰ�ĸ�ֵ�������ã����¸�ֵһ�� shaolei  20220309
	//m_oGuideBook.m_strIecfgFile = m_strIecfgFile;
	//m_oGuideBook.m_strDeviceModelFile = m_strSCDDvmFile;
	//m_oGuideBook.m_strDvmFile = m_strSCDDvmFile;

	//�����޸ı�ǣ����ڱ�����Լ�¼�ļ�
	Gb_SetGbModifiedFlag(&m_oGuideBook);
//	SaveTaskInfoToGlobalDatas();

	////���Լ�¼�ļ�	
	//strGbrptFile = _P_GetWorkspacePath() + GetFileTitleFromFilePath(m_strGbXmlFile);
	//strGbrptFile.AppendFormat(_T("(%d%d%d%d%d).%s"), tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, g_strGuideBookBinaryPostfix);
	
	//HL���¹���������������
	CString strPathTemp = _P_GetWorkspacePath();
	strPathTemp.AppendFormat(_T("%s\\%s��ѹ�ȼ�\\%s\\%s\\"), m_strUser, m_strFileVolt, m_strFileType, m_strSCDFile);
	CreateAllDirectories(strPathTemp);

	strPathTemp.AppendFormat(_T("%s_%s_���Ա���_"), m_strIedDesc, m_strIedModel);
	strPathTemp.AppendFormat(_T("%04d-%02d-%02d %02d$%02d$%02d"), tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
	//strPathTemp.AppendFormat(_T("%04d-%02d-%02d %02d:%02d:%02d"), tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);

	//HL����gbrpt�ļ���
	strGbrptFile = strPathTemp;
	strGbrptFile.AppendFormat(_T(".%s"), g_strGuideBookBinaryPostfix);

	//2023-6-6  lijunqing ����ͨ���������  
	if (m_strComm == _T("CMS"))
	{
		m_oGuideBook.m_strPpEngineProgID = g_strPpEngineProgIDDlt;
	}

	//20230606 luozibing ����iecfg��wzdxml��xml�ļ�
	//long nIndex = m_oGuideBook.m_strIecfgFile.ReverseFind('.');
	//SrcstrWzdxmlFile =m_oGuideBook.m_strIecfgFile.Left(nIndex);//��ȡWzdxmlԭ·��
	//SrcstrWzdxmlFile = SrcstrWzdxmlFile +".wzdxml";
	SrcstrWzdxmlFile = ChangeFilePostfix(m_oGuideBook.m_strIecfgFile, "wzdxml");
	strWzdxmlFile = strPathTemp+".wzdxml";
	X_CopyFile(SrcstrWzdxmlFile, strWzdxmlFile, FALSE);//����Wzdxml�ļ�

	strIecfgFile = strPathTemp;
	strIecfgFile.AppendFormat(_T("%s"), g_strIecfgFilePostfix);
	X_CopyFile(m_oGuideBook.m_strIecfgFile, strIecfgFile, FALSE);//����iecfg�ļ�
	m_oGuideBook.m_strIecfgFile = strIecfgFile;

	strXmlFile = strPathTemp;
	strXmlFile.AppendFormat(_T("_ģ��%s"), g_strXmlPostfix);
	X_CopyFile(m_oGuideBook.m_strDeviceModelFile, strXmlFile, FALSE);//����xml�ļ�
	m_oGuideBook.m_strDeviceModelFile = strXmlFile;

	//20230901 huangliang �����ΪJson��ʽ
	strSrcJsonFile = ChangeFilePostfix(m_strGbXmlFile, g_strJsonFilePostfix);
	strJsonFile = strPathTemp;
	strJsonFile.AppendFormat(_T(".%s"), g_strJsonFilePostfix);
	X_CopyFile(strSrcJsonFile, strJsonFile, FALSE);//����Json�ļ�

	//����ģ���ļ�
	CString strRptFile = m_strGbXmlFile;
	CString strDestRptFile = strGbrptFile;
	strRptFile = ChangeFilePostfix(strRptFile, g_strDocFilePostfix);
	strDestRptFile = ChangeFilePostfix(strDestRptFile, g_strDocFilePostfix);
	long nRes = X_CopyFile(strRptFile, strDestRptFile, FALSE);
	m_strReportFile = strDestRptFile;

	//������չ���沿��  //��չ������Ҫ�ֶ���������ɱ��桱���Զ����ɱ��棬��˴˴����ÿ�����WorkSpace·����
	CDvmDataset *pExpandRpts = m_oGuideBook.GetExtendRptTemplateDef(FALSE);

	if(pExpandRpts != NULL)
	{
		CDvmData *pRptEx = (CDvmData *)pExpandRpts->GetHead();

		if (pRptEx != NULL)
		{
			CString strRptFormat = pRptEx->m_strFormat;
			CString strExRptFile;
			long nPos = strGbrptFile.ReverseFind('.');

			if (nPos > 0)
			{
				strExRptFile = strGbrptFile.Left(nPos);
			}

			strExRptFile.AppendFormat(_T("%s.doc"), strRptFormat);
			m_strExRptFile = strExRptFile;
		}
	}
	m_oGuideBook.SaveBinaryFile(strGbrptFile, 0);
	m_strGbRptFile = strGbrptFile;			//����gbrpt�ļ�

	CString strTestDate;  //��������
	strTestDate.Format(_T("%04d��%02d��%02d��"), tmSys.wYear, tmSys.wMonth, tmSys.wDay);
	CDvmDataset *pGlobalDatas = m_oGuideBook.GetGlobalDatas(FALSE);

	if (pGlobalDatas != NULL)
	{
		CDvmData* pjyrqData = (CDvmData*)pGlobalDatas->FindByID("jyrq");
		if(pjyrqData)  pjyrqData->m_strValue = strTestDate;
	}

	//20231101 huangliang ���ڽ���֤����ʹ��
	CString strTemp = _P_GetTemplatePath();
	strTemp += _T("TempGBXml");
	strTemp += g_strGbFilePostfix;
	m_oGuideBook.SaveXMLFile(strTemp);

	OpenGbRptFile(m_strGbRptFile);
}
//2023-5-6 huangliang  �����ѯ�������
void CWzdMainDlg::OpenGbRptForQue(const CString &strFilePath)
{
	OpenGbRptFile(strFilePath); 
	
	//AfxGetMainWnd()->SetTimer(TIMER_ID_CLOSE_WZD, 500, NULL);
	//2024-03-08 yuanting
	//ȥ��ԭ���� �Զ����ԵĽ��� 
	//AfxGetMainWnd()->ShowWindow(SW_SHOWMINIMIZED);
	m_oGuideBook.OpenBinaryFile(strFilePath,0);

	//if(pDlg->m_strID == DLG_STEP_AutoTest)
	{
		if(MessageDlg::MessageBox("��ʾ", "ȷ�����ò�����������?", MessageDlg::YESANDNO) == IDOK)
		{
			if(m_strFileCfg == "����")
			{
				SaveWzdXmlFile();
				//Ŀǰ��ͳ��Լû�еط�����,�����
				CWzdDlg_IECCfg* pIecDlg = (CWzdDlg_IECCfg*)m_oStepsMngr.FindByID(DLG_STEP_IECCfg);
				pIecDlg->SaveXmlFile();
			}

			//ȥ���½�����
			//CreateNewTest();
		
			SetActiveDlg(DLG_STEP_AutoTest);
			long nIndex = m_oStepsMngr.FindIndexByID(DLG_STEP_AutoTest);
			m_pStepList->SetCurSel((long)nIndex);

			m_pAutoTest->setDataInfo(m_oGuideBook.GetGlobalDatas(),m_oGuideBook.GetDevice());
			CRect rcStepList;
			m_listStep.GetWindowRect(rcStepList);
			ScreenToClient(rcStepList);
			m_pStepList->ShowWindow(SW_HIDE);

			CRect rcTest;
			rcTest = GetDlgRect();
			rcTest.left = rcStepList.left;
			m_pAutoTest->MoveWindow(rcTest);
		}
		else
		{
			return;
		}
	}


}
void CWzdMainDlg::OpenGbRptFile(const CString &strFilePath)
{
 	if (m_pSmartTestClient == NULL)
 	{
 		m_pSmartTestClient = new CXSttAtsTestClientImp();
 	}

	((CXSttAtsTestClientImp*)m_pSmartTestClient)->m_pXSmartTestEventInterface = this;
 
 	BOOL bRet = m_pSmartTestClient->InitXSmartTestClient("127.0.0.1");
 
 	if (bRet)
 	{
 		m_pSmartTestClient->OpenGbrptFile(strFilePath, SmartTest_Run_Mode_Server);
 	}
	else
	{
		MessageDlg::MessageBox("��ʾ", "δ�ܼ�⵽�Զ����Գ���,��ȷ���Զ������ѿ���������", MessageDlg::YES);
	}
}

void CWzdMainDlg::SaveWzdXmlFile()
{
	CWzdDlg_IECCfg* pIecDlg = (CWzdDlg_IECCfg*)m_oStepsMngr.FindByID(DLG_STEP_IECCfg);
	CIecCfgDevice* pIecFileDevice = pIecDlg->GetIecCfgFileDevice()->GetIecCfgDevice();

	CString strFile;
	strFile.Format("%s.iecfg", pIecFileDevice->m_pSclIed->m_strID);
	strFile = _P_GetTemplatePath() + strFile;
	pIecFileDevice->SaveAsIecCfgFile(strFile);

	CDataGroup* pRoot = new CDataGroup;
	CDataGroup* pDevice = pRoot->AddNewGroup("�����豸��Ϣ","DeviceInfor","");
	pDevice->m_strValue = "1";
	CDvmData* pDeviceData = pDevice->AddNewData("Factory", m_strFactory);
	pDeviceData->m_strName = "��������";
	pDeviceData = pDevice->AddNewData("IP", m_strIP);
	pDeviceData->m_strName = "IP��ַ";
	pDeviceData = pDevice->AddNewData("FileCfg", m_strFileCfg);
	pDeviceData->m_strName = "���վ��Ϣ����";

	//��ֵ��
	CDataGroup* pSetInfor = pRoot->AddNewGroup("��ֵ����Ϣ","SetInfor","");
	if(!m_strParameterMd5.GetLength())
	{
		pSetInfor->m_strValue = "0";
	}
	else
	{
		pSetInfor->m_strValue = "1";
		pSetInfor->AddNewData("�豸������ϣֵ", "ParameterMd5", "", m_strParameterMd5);
		pSetInfor->AddNewData("����ѹ���ϣֵ", "RelayEnaMd5", "", m_strEnaMd5);
		pSetInfor->AddNewData("�豸������ϣֵ", "SettingMd5", "", m_strSettingMd5);
	}

	strFile.Format("%s.wzdxml", pIecFileDevice->m_pSclIed->m_strID);
	strFile = _P_GetTemplatePath() + strFile;
	pRoot->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	pRoot->DeleteAll();
}

void CWzdMainDlg::JumpToNextDlg()
{
	CWzdDlgBase* pDlg = (CWzdDlgBase*)m_oStepsMngr.GetActiveDlg();
	long nIndex = m_oStepsMngr.FindIndexByID(pDlg->m_strID);
	CWzdDlgBase* pTempDlg = pDlg;
	pDlg = (CWzdDlgBase*)m_oStepsMngr.GetAt(nIndex + 1);

	if(pDlg)
	{
		while (pDlg && !pDlg->IsEnabled())
		{
			nIndex++;
			pDlg = (CWzdDlgBase*)m_oStepsMngr.GetAt(nIndex + 1);
		}

		if(pDlg)
		{
			long nRes = pTempDlg->DoNext();
			if(nRes)
			{
				if(pDlg->m_strID == DLG_STEP_AutoTest)
				{
					if(MessageDlg::MessageBox("��ʾ", "ȷ�����ò�����������?", MessageDlg::YESANDNO) == IDOK)
					{
						if(m_strFileCfg == "����")
						{
							SaveWzdXmlFile();
							//Ŀǰ��ͳ��Լû�еط�����,�����
							CWzdDlg_IECCfg* pIecDlg = (CWzdDlg_IECCfg*)m_oStepsMngr.FindByID(DLG_STEP_IECCfg);
							pIecDlg->SaveXmlFile();
						}

						CreateNewTest();
						//AfxGetMainWnd()->SetTimer(TIMER_ID_CLOSE_WZD, 500, NULL);
						//AfxGetMainWnd()->ShowWindow(SW_SHOWMINIMIZED);

						//CWzdDlg_AutoTest* pAutoTest = (CWzdDlg_AutoTest*)pDlg;
						SetActiveDlg(pDlg->m_strID);
						m_pStepList->SetCurSel((long)nIndex + 1);

						m_pAutoTest->setDataInfo(m_oGuideBook.GetGlobalDatas(),m_oGuideBook.GetDevice());
						CRect rcStepList;
						m_listStep.GetWindowRect(rcStepList);
						ScreenToClient(rcStepList);
						m_pStepList->ShowWindow(SW_HIDE);

						CRect rcTest;
						rcTest = GetDlgRect();
						rcTest.left = rcStepList.left;
					//	rcTest.right = rcTest.right + rcStepList.Width()/2;
						m_pAutoTest->MoveWindow(rcTest);
						//m_pAutoTest->StarTimer();
					}
					else
					{
						return;
					}
				}
				else
				{
					SetActiveDlg(pDlg->m_strID);
					m_pStepList->SetCurSel((long)nIndex + 1);
				}
				
			}
			return;
		}
	}

// 	if(nIndex == m_oStepsMngr.GetCount() - 1)
// 	{
// 		pDlg = (CWzdDlgBase*)m_oStepsMngr.GetAt(nIndex);
// 		pDlg->DoNext();
// 	}
}

void CWzdMainDlg::SetActiveDlg(const CString& strID)
{
	CWnd* pWnd = m_oStepsMngr.GetActiveWnd();
	pWnd->ShowWindow(SW_HIDE);
	m_oStepsMngr.SetActiveDlg(strID);
	pWnd = m_oStepsMngr.GetActiveWnd();
	pWnd->ShowWindow(SW_SHOW);
	CRect rc = GetDlgRect();
	pWnd->MoveWindow(rc);
}

CRect CWzdMainDlg::GetDlgRect()
{
	m_dlgStep.ShowWindow(SW_SHOW);
	CRect rc;
	m_dlgStep.GetWindowRect(rc);
	ScreenToClient(rc);
	m_dlgStep.ShowWindow(SW_HIDE);
	return rc;
}

CRect CWzdMainDlg::GetListRect()
{
	m_listStep.ShowWindow(SW_SHOW);
	CRect rc;
	m_listStep.GetWindowRect(rc);
	ScreenToClient(rc);
	m_listStep.ShowWindow(SW_HIDE);
	return rc;
}

BOOL CWzdMainDlg::InitUI(CDataGroup* pDataGroup)
{
	m_pDataCfg = pDataGroup;

	m_pStepList->SetItemVisible(DLG_STEP_DvmMap, FALSE);
	m_pStepList->EnableItem(DLG_STEP_ImpSet, FALSE);
	m_pStepList->EnableItem(DLG_STEP_IECCfg, FALSE);

	POS pos = m_oStepsMngr.GetHeadPosition();
	BOOL bRes = TRUE;
	while (pos)
	{
		CWzdDlgBase* pDlg = (CWzdDlgBase*)m_oStepsMngr.GetNext(pos);
		CDataGroup* pGroup = (CDataGroup*)pDataGroup->FindByID(pDlg->m_strID);
		if(pDlg->InitUI(pGroup) == FALSE)
		{
			bRes = FALSE;
			m_strErrorLog += pDlg->GetErrorLog();
		}
	}

	m_pStepList->CalItemsRect();

	return bRes;
}

void CWzdMainDlg::LoadUI()
{

}

void CWzdMainDlg::ClearCfgXml()
{
	m_pDataCfg->DeleteAll();
	m_pDataCfg = NULL;
}

BEGIN_MESSAGE_MAP(CWzdMainDlg, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_PREV, &CWzdMainDlg::OnBnClickedBtnPrev)
	ON_BN_CLICKED(IDC_BTN_NEXT, &CWzdMainDlg::OnBnClickedBtnNext)
	ON_MESSAGE(WM_SENCESEL_CHANGE, &CWzdMainDlg::OnSenSelChanged)
	ON_MESSAGE(WM_USER_CHANGE, &CWzdMainDlg::OnSenSelUser)
	ON_MESSAGE(WM_SENCESEL_CFG, &CWzdMainDlg::OnSenSelCfg)
	ON_MESSAGE(WM_SENCESEL_COMM, &CWzdMainDlg::OnSenSelComm)
	ON_MESSAGE(WM_SENCESEL_TEST, &CWzdMainDlg::OnSenSelTestChanged)
	ON_MESSAGE(WM_SENSESEL_FILE, &CWzdMainDlg::OnSenSelFile)
	ON_MESSAGE(WM_OPEN_SCL_FILE, &CWzdMainDlg::OnOpenSclFile)
	ON_MESSAGE(WM_IEDSEL_SELECT, &CWzdMainDlg::OnIEDSelSelect)
	ON_MESSAGE(WM_IEDSEL_TXT, &CWzdMainDlg::OnIEDSelText)
	ON_MESSAGE(WM_DVMMAP_DONEXT, &CWzdMainDlg::OnDvmMapDoNext)
	ON_MESSAGE(WM_STEPLIST_CHANGE, &CWzdMainDlg::OnStepListChanged)
	ON_MESSAGE(WM_MAIN_ENABLE_NEXT, &CWzdMainDlg::OnEnableNext)
	ON_MESSAGE(WM_MAIN_ENABLE_PREV, &CWzdMainDlg::OnEnablePrev)
	ON_MESSAGE(WM_MAIN_ENABLE_RETURN, &CWzdMainDlg::OnEnableReturn)
	ON_MESSAGE(WM_CONNECT_UPDATE, &CWzdMainDlg::OnUpdateConnect)
	ON_MESSAGE(WM_IMPSET_UPDATE, &CWzdMainDlg::OnImpSetUpdateMd5)
END_MESSAGE_MAP()

void CWzdMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
	CRect rc;
	CWnd* pWnd = m_oStepsMngr.GetActiveWnd();
	if(pWnd)
	{
		rc = GetDlgRect();
		pWnd->MoveWindow(rc);
	}

	if(m_pStepList)
	{
		rc = GetListRect();
		m_pStepList->MoveWindow(rc);
		m_pStepList->CalItemsRect();
	}
}

void CWzdMainDlg::OnBnClickedBtnPrev()
{
	JumpToPrevDlg();
}

void CWzdMainDlg::OnBnClickedBtnNext()
{
	CString strText;
	m_btnNext.GetWindowText(strText);
	if(strText == "����")
	{
		CString strDlg = DLG_STEP_ConnectTip;
		SendMessage(WM_CONNECT_UPDATE, 0 ,0);
		SendMessage(WM_MAIN_ENABLE_RETURN, (WPARAM)strDlg.GetString(), 0);
	}
	else
	{
		JumpToNextDlg();
	}
}

LRESULT CWzdMainDlg::OnSenSelChanged(WPARAM wParam, LPARAM lParam)
{
	//������վ-0 ���ܱ��վ-1
	if(!wParam)
	{
		m_oStepsMngr.EnableDlg(DLG_STEP_DvmRead);
		m_oStepsMngr.DisableDlg(DLG_STEP_IEDSel);
		m_oStepsMngr.DisableDlg(DLG_STEP_IECCfg);

		m_pStepList->SetItemVisible(DLG_STEP_IECCfg, FALSE);
		//���վ��Ϣ����ѡ�񣺡�������վ�����ߡ�������������վ��
		//�·���SCD�ļ���Ϊ����ѡ��
		//����2��Ϊװ��ģ�Ͷ�ȡ
		//���Ҳ���5���̲����ò����ò���ʾ��
		m_pStepList->EnableItem(DLG_STEP_DvmRead, TRUE);
		m_pStepList->SetItemVisible(DLG_STEP_DvmRead, TRUE);
		m_pStepList->EnableItem(DLG_STEP_IEDSel, FALSE);
		m_pStepList->SetItemVisible(DLG_STEP_IEDSel, FALSE);
		m_pStepList->EnableItem(DLG_STEP_IECCfg, FALSE);

		m_strFileCfg = _T("����");
	}
	else
	{
		m_oStepsMngr.DisableDlg(DLG_STEP_DvmRead);
		m_oStepsMngr.EnableDlg(DLG_STEP_IEDSel);
		m_oStepsMngr.EnableDlg(DLG_STEP_IECCfg);

		m_pStepList->SetItemVisible(DLG_STEP_IECCfg, TRUE);
		m_pStepList->SetItemVisible(DLG_STEP_DvmMap, TRUE);
		//���վ��Ϣ����ѡ�񣺡����ܱ��վ�����ߡ����������ܱ��վ��
		//�·���SCD�ļ���Ϊ��ѡ��
		//����2��ΪIEDװ��ѡ��
		m_pStepList->EnableItem(DLG_STEP_DvmRead, FALSE);
		m_pStepList->SetItemVisible(DLG_STEP_DvmRead, FALSE);
		m_pStepList->EnableItem(DLG_STEP_IEDSel, TRUE);
		m_pStepList->SetItemVisible(DLG_STEP_IEDSel, TRUE);
		m_pStepList->EnableItem(DLG_STEP_IECCfg, TRUE);

		m_strFileCfg = _T("����");
	}

	GenerateFileName();

	if(lParam)
	{
		m_oStepsMngr.EnableDlg(DLG_STEP_ImpSet);
		m_pStepList->EnableItem(DLG_STEP_ImpSet, TRUE);
	}
	else
	{
		m_oStepsMngr.DisableDlg(DLG_STEP_ImpSet);
		m_pStepList->EnableItem(DLG_STEP_ImpSet, FALSE);
	}

	m_pStepList->CalItemsRect();

	return 0;
}

LRESULT CWzdMainDlg::OnOpenSclFile(WPARAM wParam, LPARAM lParam)
{
	CString strFile = (char*)lParam;
	CWzdDlg_IEDSel* pDlg = (CWzdDlg_IEDSel*)m_oStepsMngr.FindByID(DLG_STEP_IEDSel);
	pDlg->OpenSclFile(strFile);
	CWzdDlg_IECCfg* pIecDlg = (CWzdDlg_IECCfg*)m_oStepsMngr.FindByID(DLG_STEP_IECCfg);
	pIecDlg->SetSclStation(pDlg->GetSclStation());

	//2023-5-6 huangliang  ��ȡ����,���ڼ���¼�Ĵ��·��
	m_strSCDFile = strFile;
	long nPos = m_strSCDFile.ReverseFind('\\');
	if (nPos < 0)
	{
		nPos = m_strSCDFile.ReverseFind('/');
	}
	if(nPos != -1)
	{
		m_strSCDFile = m_strSCDFile.Right(m_strSCDFile.GetLength() - nPos - 1);
	}

	int p = m_strSCDFile.ReverseFind('.');
	if(p != -1)
	{
		m_strSCDFile = m_strSCDFile.Left(p);
	}
	return 0;
}

void CWzdMainDlg::CmpDeviceFile_LoadIecFile(const CString &strFile, const CString &strIecfg)
{
	//CString strFile = (char*)lParam;
	CWzdDlg_DvmMap* pDlg = (CWzdDlg_DvmMap*)m_oStepsMngr.FindByID(DLG_STEP_DvmMap);
	pDlg->CmpDeviceFile(strFile);
	CWzdDlg_IECCfg* pIecDlg = (CWzdDlg_IECCfg*)m_oStepsMngr.FindByID(DLG_STEP_IECCfg);
	//CString strIecfg = (char*)wParam;
	pIecDlg->LoadIecfgFile(strIecfg);	//20231023 huangliang �ڴ˴����û���������Gin��Gout��ʹ�õ�һ���ַ
}
//20230619 huangliang ��ʼ��IED�ļ���ѡ��
void  CWzdMainDlg::InitIECFileChoose()
{
	CWzdDlg_IECCfg* pIecDlg = (CWzdDlg_IECCfg*)m_oStepsMngr.FindByID(DLG_STEP_IECCfg);
	pIecDlg->InitIECFileChoose();
}

LRESULT CWzdMainDlg::OnIEDSelSelect(WPARAM wParam, LPARAM lParam)
{
	CWzdDlg_IECCfg* pIecDlg = (CWzdDlg_IECCfg*)m_oStepsMngr.FindByID(DLG_STEP_IECCfg);
	pIecDlg->ShowIecfgFile();
	return 0;
}

LRESULT CWzdMainDlg::OnIEDSelText(WPARAM wParam, LPARAM lParam)
{
	m_strIP = (char*)wParam;
	CWzdDlg_ConnectTip* pConnectTip = (CWzdDlg_ConnectTip*)m_oStepsMngr.FindByID(DLG_STEP_ConnectTip);
	pConnectTip ? pConnectTip->SetAddress(m_strIP) : 0;
	CString strText = (char*)lParam;
	CWzdDlg_DvmMap* pDvmMap = (CWzdDlg_DvmMap*)m_oStepsMngr.FindByID(DLG_STEP_DvmMap);
	pDvmMap->UpdateDvmTitle(strText);
	return 0;
}

//���/�������ơ������ױ�װ�����ƣ������վ���ơ�װ���ͺ�
void CWzdMainDlg::SetIEDInfo(const CString &strIedName, const CString &strIedModel
							 , const CString &strStationName, const CString &strIedDesc)
{
	m_strIedName = strIedName;
	m_strIedModel = strIedModel;
	m_strStationName = strStationName;
	m_strIedDesc = strIedDesc;
}

void CWzdMainDlg::SetIedInfoToGlobal()
{
	CDvmDataset *pGlobalDatas = m_oGuideBook.GetGlobalDatas(FALSE);

	if (pGlobalDatas == NULL)
	{
		return;
	}

	if (g_pISmartTestWzdDlg->GetWzdMode() != Wzd_Mode_CreateTest)
	{
		//�˴�ֻ�����½�����ģʽ�¡�����ģʽ�Ѿ�����������
		return;
	}

	CDvmData* pbdzData = (CDvmData*)pGlobalDatas->FindByID("bdz");
	if(pbdzData)  pbdzData->m_strValue = m_strStationName;

	CDvmData* psbmcData = (CDvmData*)pGlobalDatas->FindByID("sbmc");
	if(psbmcData)  psbmcData->m_strValue = m_strIedDesc;

	CDvmData* psbxhData = (CDvmData*)pGlobalDatas->FindByID("sbxh");
	if(psbxhData)  psbxhData->m_strValue = m_strIedModel;

	CDvmData* piedinfoData = (CDvmData*)pGlobalDatas->FindByID("iedinfo");
	if(piedinfoData) piedinfoData->m_strValue = m_strIedName;
}

void CWzdMainDlg::GenerateFileName()
{
	CString strName;
	strName.Format("%s_%s_%s_%s_����ģ��.xml", m_strFileCfg, m_strFileVolt, m_strFileType/*, m_strComm*/, m_strFileTest);

	CString strFile = _P_GetLibraryPath();
	strFile += strName;

	m_strGbXmlFile = _P_GetTemplatePath();
	strName.Format("%s_%s_%s_%s_����ģ��.gbxml", m_strFileCfg, m_strFileVolt, m_strFileType/*, m_strComm*/, m_strFileTest);
	m_strGbXmlFile += strName;

	CWzdDlg_DvmMap* pDlg = (CWzdDlg_DvmMap*)m_oStepsMngr.FindByID(DLG_STEP_DvmMap);
	pDlg->UpdateStandFile(strFile);
	CWzdDlg_TestSenceSel* pSenceDlg = (CWzdDlg_TestSenceSel*)m_oStepsMngr.FindByID(DLG_STEP_SenceSel);
	pSenceDlg->SetGbFile(m_strGbXmlFile);
}

void CWzdMainDlg::OnWindowPosChanging()
{
	CWzdDlgBase* pWnd = (CWzdDlgBase*)m_oStepsMngr.GetActiveWnd();
	if(pWnd)
	{
		pWnd->OnWindowPosChanging();
	}
}

LRESULT CWzdMainDlg::OnSenSelUser(WPARAM wParam, LPARAM lParam)
{
	m_strUser = (char*)lParam;
	return 0;
}
LRESULT CWzdMainDlg::OnSenSelCfg(WPARAM wParam, LPARAM lParam)
{
	m_strFileVolt = (char*)wParam;
	m_strFileType = (char*)lParam;

	GenerateFileName();

	CWzdDlg_IECCfg* pIecDlg = (CWzdDlg_IECCfg*)m_oStepsMngr.FindByID(DLG_STEP_IECCfg);
	CDataGroup* pDataGroup = (CDataGroup*)m_pDataCfg->FindByID(DLG_STEP_IECCfg);
	POS pos = pDataGroup->GetHeadPosition();
	while (pos)
	{
		CDvmData* pData = (CDvmData*)pDataGroup->GetNext(pos);
		if(pData->m_strName == m_strFileType)
		{
			pData->m_strValue = "1";
			pIecDlg->SetIECCfgType(pData->m_strID);
		}
		else
		{
			pData->m_strValue = "0";
		}
	}

	return 0;
}

LRESULT CWzdMainDlg::OnSenSelTestChanged(WPARAM wParam, LPARAM lParam)
{
	m_strFileTest = (char*)lParam;
	GenerateFileName();
	return 0;
}

LRESULT CWzdMainDlg::OnSenSelComm(WPARAM wParam, LPARAM lParam)
{
	if(wParam)
	{
		m_strFactory = (char*)wParam;
		CWzdDlg_ConnectTip* pDlg = (CWzdDlg_ConnectTip*)m_oStepsMngr.FindByID(DLG_STEP_ConnectTip);
		pDlg ? pDlg->SetFactory(m_strFactory) : 0;
	}
	else
	{
		m_strComm = (char*)lParam;
		GenerateFileName();
	}
	return 0;
}

LRESULT CWzdMainDlg::OnSenSelFile(WPARAM wParam, LPARAM lParam)
{
	CString strFile = (char*)lParam;
	CWzdDlg_ImpSet* pDlg = (CWzdDlg_ImpSet*)m_oStepsMngr.FindByID(DLG_STEP_ImpSet);
	pDlg->SetFileType((BOOL)wParam);
	pDlg->SetFilePath(strFile);
	return 0;
}

LRESULT CWzdMainDlg::OnDvmMapDoNext(WPARAM wParam, LPARAM lParam)
{
	CWzdDlg_DvmMap* pDvmMapDlg = (CWzdDlg_DvmMap*)m_oStepsMngr.FindByID(DLG_STEP_DvmMap);
	CWzdDlg_ImpSet* pDlg = (CWzdDlg_ImpSet*)m_oStepsMngr.FindByID(DLG_STEP_ImpSet);
	pDlg->UpdateFileSelected();
	pDlg->GetMd5(m_strParameterMd5, m_strSettingMd5, m_strEnaMd5);
	CWzdDlg_ConnectTip* pConnect = (CWzdDlg_ConnectTip*)m_oStepsMngr.FindByID(DLG_STEP_ConnectTip);
	pConnect ? pConnect->SetMd5(m_strParameterMd5, m_strSettingMd5, m_strEnaMd5) : 0;
	return 0;
}

LRESULT CWzdMainDlg::OnImpSetUpdateMd5(WPARAM wParam, LPARAM lParam)
{
	CWzdDlg_ImpSet* pDlg = (CWzdDlg_ImpSet*)m_oStepsMngr.FindByID(DLG_STEP_ImpSet);
	pDlg->GetMd5(m_strParameterMd5, m_strSettingMd5, m_strEnaMd5);
	CWzdDlg_ConnectTip* pConnect = (CWzdDlg_ConnectTip*)m_oStepsMngr.FindByID(DLG_STEP_ConnectTip);
	pConnect ? pConnect->SetMd5(m_strParameterMd5, m_strSettingMd5, m_strEnaMd5) : 0;
	return 0;
}

LRESULT CWzdMainDlg::OnStepListChanged(WPARAM wParam, LPARAM lParam)
{
	CWzdDlgButton* pBtn = (CWzdDlgButton*)lParam;
	CWzdDlgBase* pWnd = (CWzdDlgBase*)pBtn->GetItemData();
	if(pWnd && pBtn->IsEnabled())
	{
		SetActiveDlg(pWnd->m_strID);
	}
	return 0;
}

LRESULT CWzdMainDlg::OnEnableNext(WPARAM wParam, LPARAM lParam)
{
	m_btnNext.SetEnabled(lParam);
	return 0;
}

LRESULT CWzdMainDlg::OnEnablePrev(WPARAM wParam, LPARAM lParam)
{
	m_btnPrev.SetEnabled(lParam);
	return 0;
}

LRESULT CWzdMainDlg::OnEnableReturn(WPARAM wParam, LPARAM lParam)
{
	if(lParam)
	{
		m_btnPrev.SetVisible(FALSE);
		m_btnNext.SetWindowText("����");
	}
	else
	{
		m_btnPrev.SetVisible(TRUE);
		m_btnNext.SetWindowText("��һ��");
	}
	CString strDlg = (char*)wParam;
	SetActiveDlg(strDlg);
	return 0;
}

LRESULT CWzdMainDlg::OnUpdateConnect(WPARAM wParam, LPARAM lParam)
{
	CWzdDlg_IECCfg* pIecDlg = (CWzdDlg_IECCfg*)m_oStepsMngr.FindByID(DLG_STEP_IECCfg);
	CWzdDlg_ConnectTip* pConnectDlg = (CWzdDlg_ConnectTip*)m_oStepsMngr.FindByID(DLG_STEP_ConnectTip);
	pConnectDlg ? pConnectDlg->UpdateGrid(pIecDlg->GetIecCfgFileDevice()) : 0;
	return 0;
}

static UINT CWzdDlg_IEDSel_DoNext_Thread(LPVOID pPara)
{
	CWzdDlgBase *pDlg = (CWzdDlgBase*)pPara;
	pDlg->DoNextForThead();

	return 0;
}

//2023-4-18  lijunqing
void CWzdMainDlg::CWzdDlg_IEDSel_DoNext(CWzdDlgBase *pDlg)
{
	CWinThread *pThread = AfxBeginThread(CWzdDlg_IEDSel_DoNext_Thread, pDlg);
	pThread->m_bAutoDelete = TRUE;
	pThread->ResumeThread();
}

//�Զ������¼�
long CWzdMainDlg::OnItemStateChanged(const CString& strDeviceID, long nDeviceIndex, long nReportIndex, 
								long nItemIndex, const CString& strItemID, const CString& strState, long nSelect)
{
	CGbItemBase *pItem = (CGbItemBase *)Gb_GetItem(&m_oGuideBook, strItemID);
	long nState = GB_GetTestStateByIDEx(strState);
	
	if (pItem == NULL)
	{
		return 1;
	}

	pItem->SetState(nState);
	Gb_UpdateGbItemParentTestState(pItem);  //ˢ������guidebook����Ŀ��״̬

	//m_pAutoTest->OnItemStateChanged(pItem);
	::SendMessage(m_pAutoTest->GetSafeHwnd(),WM_TEST_STATE_CHANGE,reinterpret_cast<WPARAM>((void*)(pItem)),0);
	return 0;
}

//20230608 huangliang �Զ�������
long CWzdMainDlg::OnTestFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex)
{
	g_pISmartTestWzdDlg->SetCheckOverToBlueState(CHECK_RPT_START);	
	//m_pAutoTest->OnTestFinished();
	::PostMessage(m_pAutoTest->GetSafeHwnd(),WM_TEST_STATE_FINISH,0,0);
	return 0;
}

long CWzdMainDlg::OnTestStoped(const CString& strDeviceID, long nDeviceIndex, long nReportIndex)
{
	//m_pAutoTest->OnTestStoped();
	::PostMessage(m_pAutoTest->GetSafeHwnd(),WM_TEST_STATE_STOP,0,0);
	return 0;
}

long CWzdMainDlg::OnExportRptEvent(const CString& strDeviceID, const CString &strEventID, long nDeviceIndex, long nReportIndex)
{
	return 0;
}

long CWzdMainDlg::OnExportRptEvent(CSttParas *pParas)
{
	CString strEventID = _T(""),strDocFile = _T("");
	pParas->GetDataValue(STT_CMD_PARA_EventID, strEventID);
	pParas->GetDataValue("doc-ex-file", strDocFile);

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�յ�OnExportRptEvent:%s"), strEventID);
	if(strEventID == _T("ExportFinish"))
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("���ExportRpt"));
		CTickCount32 oTick;
		oTick.DoEvents(2000);
		if(g_pISmartTestWzdDlg != NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR, _T("׼���ر��Զ�����"));
			g_pISmartTestWzdDlg->SetCheckOverToBlueState(CHECK_STATE_OVER);	
		}
	}
	return 0;
}

long CWzdMainDlg::OnTestAppEvent(const CString& strDeviceID, const CString& strEvent)
{
	m_pAutoTest->OnTestAppEvent(strEvent);
	return 0;
}

long CWzdMainDlg::OnEngineEvent(const CString& strDeviceID, long nDeviceIndex, const CString& strEvent)
{
	m_pAutoTest->OnEngineEvent(strEvent);
	return 0;
}

long CWzdMainDlg::OnTestCreated(const CString& strDeviceID)
{
	//m_pAutoTest->OnTestCreated();
	::PostMessage(m_pAutoTest->GetSafeHwnd(),WM_TEST_STATE_CREATE,0,0);
	return 0;
}

long CWzdMainDlg::OnOpenGbrptFileFailed(const CString& strDeviceID)
{
	m_pAutoTest->OnOpenGbrptFileFailed();
	return 0;
}

long CWzdMainDlg::OnTestProcess(const CString& strDeviceID, const CString& strTestID, long nTotalItems, 
						   long nCurrItem, long nTotalTime, long nRemainTime, const CString& strDeviceState)
{
	return 0;
}

long CWzdMainDlg::OnTestProcess(CExBaseList* pSttParas)
{
	m_pAutoTest->OnTestProcess(pSttParas);
	return 0;
}

long CWzdMainDlg::OnReTestFinished(CExBaseList* pSttParas)
{
	m_pAutoTest->OnReTestFinished(pSttParas);
	return 0;
}

long CWzdMainDlg::OnTestStarted(const CString& strDeviceID, long nDeviceIndex, long nReportIndex)
{
	//m_pAutoTest->OnTestStarted();
	::PostMessage(m_pAutoTest->GetSafeHwnd(),WM_TEST_STATE_STAR,0,0);
	return 0;
}

long CWzdMainDlg::OnUploadRptFile(const CString& strDeviceID, const CString &strFiles)
{
	return 0;
}

long CWzdMainDlg::OnInputData(const CString& strDatas, const CString& strMsgs)
{
	return 0;
}

long CWzdMainDlg::OnReport(CExBaseList* pSttParas)
{
	CSttParas *pParas = (CSttParas *)pSttParas;
	CString strItemID;
	pParas->GetDataValue(STT_CMD_PARA_ItemID, strItemID);

	CGbItemBase *pItem = (CGbItemBase *)Gb_GetItem(&m_oGuideBook, strItemID);
	CSttReports *pSttReports = pParas->GetSttReports(FALSE);

	if (pItem == NULL || pSttReports == NULL)
	{
		return 1;
	}

	CReports *pReports = pItem->GetReports();
	CSttCmdGuideBookTransTool oTool;
	pReports->DeleteAll();
	oTool.ReverseTrans(pReports, pSttReports);

	//m_pAutoTest->OnReport(pItem);
	::PostMessage(m_pAutoTest->GetSafeHwnd(),WM_TEST_STATE_REPORT,reinterpret_cast<WPARAM>((void*)(pItem)),0);

	return 0;
}

long CWzdMainDlg::OnInputData(CExBaseList *pSttParas, CExBaseList *pSttMsgs)
{
	//m_pAutoTest->OnInputData(pSttParas, pSttMsgs);
	::SendMessage(m_pAutoTest->GetSafeHwnd(),WM_TEST_ONINPUTDATA,reinterpret_cast<WPARAM>((void*)(pSttParas)),reinterpret_cast<LPARAM>((void*)(pSttMsgs)));
	return 0;
}

void CWzdMainDlg::CloseTestClient()
{
	if (m_pSmartTestClient == NULL)
		return ;
	m_pSmartTestClient->CloseTest(_T(""));
}

void CWzdMainDlg::TestClientStartTest()
{
	if (m_pSmartTestClient == NULL)
		return ;
	m_pSmartTestClient->BeginTest(_T(""));
}

void CWzdMainDlg::TestClientStopTest()
{
	if (m_pSmartTestClient == NULL)
		return ;
	m_pSmartTestClient->StopTest(_T(""));
}

void CWzdMainDlg::SetItemState(CString strMacroID, long nSelect)
{
	if (m_pSmartTestClient == NULL)
		return ;
	CSttParas oParas;
	oParas.AddNewData("ItemPath", strMacroID);
	oParas.AddNewData("Select", nSelect);
	oParas.AddNewData("Enable", 1);
	oParas.AddNewData("Show", 1);
	m_pSmartTestClient->SetItemState(&oParas);
}

void CWzdMainDlg::SetTestParas(const CString &strDeviceID, CString &strTestParas)
{
	if (m_pSmartTestClient == NULL)
		return ;

	m_pSmartTestClient->SetTestParas(strDeviceID, strTestParas);
}

void CWzdMainDlg::SetNetState(long nState)
{
	if (m_pAutoTest != NULL)
	{
		//m_pAutoTest->SetNetState(nState);
		::PostMessage(m_pAutoTest->GetSafeHwnd(),WM_TEST_STATE_BOOTH,nState,0);
	}
}

void CWzdMainDlg::FinishInputData(CExBaseList* pDatas)
{
	CShortDatas oDatas;
	DvmDatas_to_ShortDatas(pDatas, &oDatas);
	CString strDeviceID, strReport;
	oDatas.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strReport);

	m_pSmartTestClient->FinishInputData(strDeviceID, strReport);
}

//20231025 huangliang ���õ�������
void CWzdMainDlg::TestClientExportRpt()
{
	if (m_pSmartTestClient == NULL)
		return ;
	m_pSmartTestClient->ExportRpt(_T(""));
}

void CWzdMainDlg::TestCurrentItem(CString strPath)
{
	if(strPath.IsEmpty())
	{
		return;
	}
	m_pSmartTestClient->TestPoint(_T(""),strPath);
}

void CWzdMainDlg::TestFromItem(CString strPath)
{
	if(strPath.IsEmpty())
	{
		return;
	}
	m_pSmartTestClient->TestBelow(_T(""),strPath);
}
