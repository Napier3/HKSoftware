#include "stdafx.h"
#include "WzdMainDlg.h"
#include "WzdDlg_IEDSel.h"
#include "WzdDlg_TestSenceSel.h"
#include "../../../iSmartTestWzd/iSmartTestWzdDlg.h"
#include "../../../../61850/Module/SclToModel/ModelWriteXml.h"
#include "../../../../61850/Module/IecfgGenMngr/IecGenTool.h"
#include "../../../AutoTest/Module/GuideBook/GuideBookDefine.h"
#include "../../../../61850/Module/IecCfgSclTool/SclToIecCfgTool.h"
#include "../../Module/MMS_STACK_CFG/MMS_STACK_CFG.h"
#include "../../Module/61850ClientConfig/61850ClientConfig.h"
#include "../../../Module/IPAddrModify/IPAddrModifyTool.h"
#include "../../Module/61850ClientConfig/61850ClientCfgMngrGlobal.h"
#include "MessageDlg.h"


IMPLEMENT_DYNAMIC(CWzdDlg_IEDSel, CDialog)

CWzdDlg_IEDSel::CWzdDlg_IEDSel(CWnd* pParent /*=NULL*/)
: CWzdDlgBase(CWzdDlg_IEDSel::IDD, pParent)
{
	C61850ClientCfgMngrXmlRWKeys::Create();
	CStNetCardInforList::Create();		//2023-5-9 luozibing ����
}	

CWzdDlg_IEDSel::~CWzdDlg_IEDSel()
{
	C61850ClientCfgMngrXmlRWKeys::Release();
	CStNetCardInforList::Release();		//2023-5-9 luozibing �ͷ�
}

void CWzdDlg_IEDSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID_IED, m_girdIED);
	DDX_Control(pDX, IDC_CMB_IP, m_cmb_ip);
	DDX_Control(pDX, IDC_CMB_CARD, m_cmb_card);
}

void CWzdDlg_IEDSel::OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	if(nRow == 0 || nCol != 1)
	{
		return;
	}

	CGridCell *pTmpCell = ((CSclIedsGrid*)pGridCtrl)->GetSelectCell(nRow);
	if(pTmpCell->dwValue != 0)
	{
		return;
	}

	PEXBASECELLDATA pVCellDataTmp = (_ExBaseCellData*)pTmpCell->lParam;
	CSclIed* pSclIed = (CSclIed*)pVCellDataTmp->pObj;
	AutoGenIecCfgDevice(pSclIed);

	//20240304 luozibing ���ѡ��IED����ʾIP
	if(!IP_Find_OK(nRow))//��ȡ��ǰѡ����
	{
		//CString strItemIP = m_girdIED.GetItemText(nRow, 3);
		//GetNewIP(strItemIP);			//�Ҳ�����������
		//GetDlgItem(IDC_TIPS)->ShowWindow(SW_SHOW);
		//CString Tmp = _T("IP������,����������IP:")+strItemIP;
		//SetDlgItemText(IDC_TIPS,Tmp);
	}
	else
	{
		//GetDlgItem(IDC_TIPS)->ShowWindow(SW_HIDE);
	}		
}

void CWzdDlg_IEDSel::OnDataEditChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	CGridCell *pTmpCell = ((CSclIedsGrid*)pGridCtrl)->GetSelectCell(nRow);//20240304luozibing �Ե�ǰ��ѡ�н����޸�ʱ����������
	PEXBASECELLDATA pVCellDataTmp = (_ExBaseCellData*)pTmpCell->lParam;
	CSclIed* pEditIed = (CSclIed*)pVCellDataTmp->pObj;
	CSclIed* pSclIed1 = GetSelectedIED();
	if(pTmpCell->dwValue != 0&&pEditIed ==pSclIed1)
	{
		IP_Find_OK(nRow);
	}
	CString strItemText = pEditIed->m_strID;//װ������
	CString strItemIP = pEditIed->m_strIP;//IP
	
	GetParentWnd()->SendMessage(WM_IEDSEL_TXT, (WPARAM)strItemIP.GetString(), (LPARAM)strItemText.GetString());
}	

void CWzdDlg_IEDSel::OnInitialUpdate()
{
	XUI_InitAdjust();

	m_girdIED.InitGrid();
	m_girdIED.AttachDataViewOptrInterface(this);

	CStNetCardInforList::InsertToComboBox(&m_cmb_card);//2023-5-9 luozibing ��ʾ������Ϣ
	int index = m_cmb_card.GetCurSel();
	if(index > 0||index == 0)
	{
		CStNetCardInfor *pCard = (CStNetCardInfor *)m_cmb_card.GetItemData(index);
		CStNetCardInforList::InsertToComboBox_IP(pCard,&m_cmb_ip);//2023-5-9 luozibing ��ʾѡ������IP��Ϣ
	}
}

void CWzdDlg_IEDSel::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
	XUI_AddWnd(&m_girdIED, 0, 0, 1, 1);

	CXUIAdjItem_Area::XUI_OnSize();
}

void CWzdDlg_IEDSel::OpenSclFile(const CString& strFile)
{
	m_girdIED.m_nCurSelect = 0;	//20240311 huangliang ��ѡ��SCDʱ�����ѡ����
	g_pWzdMainDlg->m_oSclStation.DeleteAll();
	m_oSclFileRead.ReadSclFile(strFile, this, &g_pWzdMainDlg->m_oSclStation);
}

CSclStation* CWzdDlg_IEDSel::GetSclStation()
{
	return m_oSclFileRead.GetSclStation();
}

CSclIed* CWzdDlg_IEDSel::GetSelectedIED()
{
	return (CSclIed*)m_girdIED.GetCurrSelIED();  //���ص��Ǵ򹳵������������ѡ�е�����
	/*
	POS pos = g_pWzdMainDlg->m_oSclStation.GetHeadPosition();
	CExBaseObject *pCurObj = NULL;
	CSclIed *pSclIed = NULL;

	while(pos)
	{
		pCurObj = g_pWzdMainDlg->m_oSclStation.GetNext(pos);

		if (pCurObj->GetClassID() != SCLIECCLASSID_IED)
		{
			continue;
		}

		pSclIed = (CSclIed *)pCurObj;
		
		if (pSclIed == (CSclIed *)m_girdIED.GetCurrSelData())
		{
			return pSclIed;
		}
	}
	return NULL;
	*/
}

void CWzdDlg_IEDSel::OnFileNewDevice(CIecCfgDevice *pIecfgDevice,CSclIed *pSclIed)
{
	CSclToIecCfgTool oSclToIecCfgTool;
	CIecCfgDatasMngr *pIecfgDatasMngr = (CIecCfgDatasMngr*)pIecfgDevice->FindByClassID(CFGCLASSID_CIECCFGDATASMNGR);
	pIecfgDevice->SetSclIed(pSclIed);

	if (pIecfgDatasMngr == NULL)
	{
		pIecfgDatasMngr = pIecfgDevice->CreateIecCfgDatasMngr();
	}

	pIecfgDevice->SetCurrDatasMngr(pIecfgDatasMngr); 
	oSclToIecCfgTool.AttacthSclFileRead(&g_pWzdMainDlg->m_oSclStation);
	oSclToIecCfgTool.AddToIecCfg(pSclIed, pIecfgDatasMngr);
	oSclToIecCfgTool.AddGinEx(pIecfgDatasMngr, pSclIed, &g_pWzdMainDlg->m_oSclStation);
	pIecfgDevice->m_strIcdFile = g_pWzdMainDlg->m_oSclStation.GetScdFile();
	pIecfgDevice->InitAfterRead();
}

void CWzdDlg_IEDSel::ModifyIP_PpMmsEngine(const CString &strIP,const CString &strDevName)
{
	CMMS_STACK_CFG oMMS_STACK_CFG;
	oMMS_STACK_CFG.Open_MMS_STACK_CFG_Outer();
	CStkCfg_RemoteAddressList *pRemoteAddressList = oMMS_STACK_CFG.GetRemoteAddressList();
	long nIndex = 0;
	pRemoteAddressList->SetCount(1);
	CStkCfg_RemoteAddress *pAddress = (CStkCfg_RemoteAddress *)pRemoteAddressList->GetAtIndex(0);
	pAddress->SetIP(strIP);
	pAddress->m_strModel = strDevName;

	oMMS_STACK_CFG.Save_MMS_STACK_CFG_Outer();
	oMMS_STACK_CFG.WriteIpToVMDFile();
}

void CWzdDlg_IEDSel::ModifyIP_DltEngine(const CString &strIP,const CString &strDevName)
{
	CString strPath;
	strPath = _P_GetInstallPath();
	strPath += _T("DltEngine\\Config\\");
	strPath += _T("860ClientConfig.xml");

	if (g_o61850ClientConfig.OpenClientConfg(strPath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�����ļ�(%s)�򿪳ɹ�."),strPath);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����ļ�(%s)��ʧ��."),strPath);
		return;
	}

	CRemoteDev *pRemoteDev = g_o61850ClientConfig.GetRemoteDev(0);
	pRemoteDev->m_strIP = strIP;
	pRemoteDev->m_strName = strDevName;
	g_o61850ClientConfig.SaveClientConfg();
}

void CWzdDlg_IEDSel::CreateLocalIP_EngineIP(const CString &strDriverDesc,const CString &strIP,const CString &strDevName)
{
	if ((strIP.IsEmpty()||(strIP.Find(_T(".")) <=0)))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ�豸IP��ַ(%s)Ϊ��,����IP��ַ��ʽ����ȷ."),strIP.GetString());
		return;
	}

	CIPAddrModifyTool oIPAddrModifyTool;
	oIPAddrModifyTool.InitGetAdapterInfo();

	if (oIPAddrModifyTool.NeedAddNetworkSegmentIP(strDriverDesc,strIP))//zhouhj 20220429 ��������pingͨ��ӦIP��ַ,����������ӱ���IP
	{
		if(oIPAddrModifyTool.AddIPForLocalNet_SameSegment(strIP,strDriverDesc))		//202305024 luozibing ��IP��ӵ���Ӧ����
		{
																					//20230601 luozibing ����ӳɹ���IP�����������[���޸Ĳ���ʹ��]
// 			int index = m_cmb_card.GetCurSel();
// 			if(index > 0||index == 0)
// 			{
// 				CStNetCardInfor *pCard = (CStNetCardInfor *)m_cmb_card.GetItemData(index);
// 				pCard->m_vecIP.push_back(strIP);
// 				CStNetCardInforList::InsertToComboBox_IP(pCard,&m_cmb_ip);
// 			}
		}
	}
	ModifyIP_PpMmsEngine(strIP,strDevName);
	ModifyIP_DltEngine(strIP,strDevName);
}
BOOL CWzdDlg_IEDSel::DoPrev()			//20230619luo �����һ����ѡ���-1��
{
	m_girdIED.ClearSelect();
	m_girdIED.SelectRow(-1);
	g_pWzdMainDlg->InitIECFileChoose();
	return TRUE;
}
BOOL CWzdDlg_IEDSel::DoNext()
{
	CExBaseObject* pData = GetSelectedIED();//20240311 huangliang ͳһʹ�õ�ǰѡ��ѡ��
	if(!pData)
	{
		MessageDlg::MessageBox("����", "û��ѡ��һ����Ч��IED!", MessageDlg::ERRYES);
		return FALSE;
	}

	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 0);
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_PREV, 0, 0);
	g_pWzdMainDlg->CWzdDlg_IEDSel_DoNext(this);

	return TRUE;
}

BOOL CWzdDlg_IEDSel::DoNextForThead()
{
	//long nIndex = m_girdIED.GetCurrSelRow();

	//ԭ�ȲŴ����˴�Ϊѡ�е���һ�У�ʵ��Ӧ���ô򹳵���һ��  shaolei 2024-2-29
// 	CString strItemText = m_girdIED.GetItemText(nIndex, 3);  //װ������
// 	CString strItemIP = m_girdIED.GetItemText(nIndex, 4);  //IP��ַ
// 	CString strZZXH = m_girdIED.GetItemText(nIndex, 5);   //�豸�ͺ�
// 	CString strNetDesc;

	CSclIed* pIed = GetSelectedIED();
	if(!pIed)
	{
		MessageDlg::MessageBox("����", "û��ѡ��һ����Ч��IED!", MessageDlg::ERRYES);
		return FALSE;
	}

	CString strIedName = pIed->m_strID;  //װ�����ơ������������ױ�
	CString strIedModel = pIed->m_strModel;  //�豸�ͺ�
	CString strItemIP = pIed->m_strIP;  //װ��IP��

// 	GetParentWnd()->SendMessage(WM_IEDSEL_TXT, (WPARAM)strItemIP.GetString(), (LPARAM)strItemText.GetString());
// 	GetParentWnd()->SendMessage(WM_IEDSEL_SELECT, (WPARAM)g_pWzdMainDlg->m_oGuideBook.m_strIecfgFile.GetString(), (LPARAM)m_strSCDDvmFile.GetString());
	g_pWzdMainDlg->OnIEDSelText((WPARAM)strIedModel.GetString(), (LPARAM)strIedName.GetString());
	g_pWzdMainDlg->CmpDeviceFile_LoadIecFile(m_strSCDDvmFile, g_pWzdMainDlg->m_oGuideBook.m_strIecfgFile);
	g_pWzdMainDlg->SetIEDInfo(strIedName, strIedModel, m_oSclFileRead.GetSelStationName(), pIed->m_strName);
	g_pWzdMainDlg->SetIedInfoToGlobal();//��װ����Ϣ�����ܵ�ģ���ȫ������

	g_pWzdMainDlg->SendMessage(WM_IEDSEL_SELECT, 0, 0);

// 	CString strNetDesc;
// 	strNetDesc = g_oIecfgGenMngr.m_strNetDesc;
// 	CSclIed* pIed = GetSelectedIED();
// 	CreateLocalIP_EngineIP(strNetDesc, pIed->m_strIP, pIed->m_strName);
	long nIndex = m_cmb_card.GetCurSel();
	if(nIndex == -1)
	{
		nIndex = 0;			//202305024 luozibing ���õ�һ������ΪĬ������
	}
	SaveFile(); 
	CStNetCardInfor *pCard = NULL;
	pCard = (CStNetCardInfor *)m_cmb_card.GetItemData(nIndex);
	CreateLocalIP_EngineIP(pCard->m_strInfor, strItemIP, strIedName);//20230601 luozibing�ڵ�ǰѡ�е����������IP

	CStNetCardInforList::g_pNetCardList->DeleteAll();
	CStNetCardInforList::g_pNetCardList->GetNetCardInfor();			// 20230601 luozibing ��ȡ����������Ϣ���ڽ����и���
	CStNetCardInforList::InsertToComboBox(&m_cmb_card);
	if(nIndex > 0||nIndex == 0)
	{
		CStNetCardInfor *pCard = (CStNetCardInfor *)m_cmb_card.GetItemData(nIndex);
		CStNetCardInforList::InsertToComboBox_IP(pCard,&m_cmb_ip);
	}
	
	g_theThreadPrgsDlg->Finish();
	
	g_pWzdMainDlg->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 1);
	g_pWzdMainDlg->SendMessage(WM_MAIN_ENABLE_PREV, 0, 1);

	return TRUE;
}
void CWzdDlg_IEDSel::AutoGenIecCfgDevice(CSclIed *pSclIed)
{
	if (pSclIed == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("����ѡ��ǰ���Ե��豸."));
		return;
	}

	//��scd�ļ�����ȡ�豸����ģ���ļ�,���洢��Library�ļ�����
	CString strModelFilePath;
	strModelFilePath = _P_GetLibraryPath();
	strModelFilePath += pSclIed->m_strID;
	strModelFilePath += _T(".xml"); 
	model_XmlWrite(strModelFilePath ,(SCL_IED*)pSclIed->m_pRefItemData,m_oSclFileRead.GetSCL_INFO(),FALSE);
	g_pWzdMainDlg->m_oGuideBook.m_strDvmFile = m_strSCDDvmFile = strModelFilePath;
	g_pWzdMainDlg->m_oGuideBook.m_strDeviceModelFile = strModelFilePath;

	CIecCfgTool::CloseIecFile(g_pWzdMainDlg->m_pCurIecCfgFile, TRUE);
	g_pWzdMainDlg->m_pCurIecCfgFile = CIecCfgTool::NewIecCfgFile(g_strDeviceIecCfgFilePostfix);
	CIecCfgFileDevice* pIecCfgFileDevice = (CIecCfgFileDevice*)g_pWzdMainDlg->m_pCurIecCfgFile;
	CIecCfgDevice *pIecfgDevice = pIecCfgFileDevice->GetIecCfgDevice();
	OnFileNewDevice(pIecfgDevice,pSclIed);
	CIecGenTool oIecGenTool;

	CString strIecfgName = g_pWzdMainDlg->m_strGuideBookIecfgFile;

	if (oIecGenTool.Generate(pIecfgDevice, strIecfgName, pSclIed))
	{
		CIecCfgDatasMngr* pCurrIecCfgDatasMngr = pIecfgDevice->GetCurrDatasMngr();

		if (pCurrIecCfgDatasMngr != NULL)
		{
			pCurrIecCfgDatasMngr->UpdateGinChMapFile();
		}
	}

	CString strIecfgFilePath;
	strIecfgFilePath = _P_GetTemplatePath();
	strIecfgFilePath += pSclIed->m_strID;
	strIecfgFilePath += g_strIecfgFilePostfix; 
	pIecCfgFileDevice->SaveAs(strIecfgFilePath);
	g_pWzdMainDlg->m_oGuideBook.m_strIecfgFile = strIecfgFilePath;
}

BEGIN_MESSAGE_MAP(CWzdDlg_IEDSel, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_MESSAGE(WM_SCLFILE_READ_FINISH, OnSclReadFinish)
	ON_CBN_SELCHANGE(IDC_CMB_CARD, &CWzdDlg_IEDSel::OnCbnSelchangeCmbCard)
END_MESSAGE_MAP()

void CWzdDlg_IEDSel::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}

LRESULT CWzdDlg_IEDSel::OnSclReadFinish(WPARAM wParam, LPARAM lParam)
{
	if (SCLFILE_READ_FINISH == lParam)
	{
	}
	else if (SCLFILE_READ_SHOW == lParam)
	{
		g_pWzdMainDlg->m_oSclStation.InitGoutCh_VirtualTerminals();
		m_girdIED.ShowDatas(&g_pWzdMainDlg->m_oSclStation);
	}
	else if (SCLFILE_READ_DELCTRLS == lParam)
	{
	}

	return 0;
}

BOOL CWzdDlg_IEDSel::IP_Find_OK(int nRow)
{
	CString str_grid_ip,str_cmb_ip,str_card,str_ip;
	
	CSclIed *pTmp = (CSclIed *)m_girdIED.GetDataRow(nRow);//20240304 luozibing ��ȡ��ǰѡ���л�ȡ��ip
	if(pTmp == NULL)
	{
		return FALSE;
	}
	CString grid_ip = pTmp->m_strIP;
	long nIndex = grid_ip.ReverseFind('.');
	str_grid_ip = grid_ip.Left(nIndex);

	int cardIndex,ipIndex;

	CStNetCardInfor *pCard = NULL;
	cardIndex = m_cmb_card.GetCurSel();
	if(cardIndex > 0||cardIndex == 0)
	{
		pCard = (CStNetCardInfor *)m_cmb_card.GetItemData(cardIndex);
	}
	if(CStNetCardInforList::FindIPByCard(pCard,str_grid_ip,cardIndex,ipIndex))//2023-5-9 luozibing �����Ƿ���ͬһ����IP
	{
		if(cardIndex >0|| cardIndex == 0)
		{
			m_cmb_card.SetCurSel(cardIndex);
			pCard = (CStNetCardInfor *)m_cmb_card.GetItemData(cardIndex);
			m_cmb_ip.ResetContent();
			CStNetCardInforList::InsertToComboBox_IP(pCard,&m_cmb_ip);
		}
		m_cmb_ip.SetCurSel(ipIndex);
		SaveFile();
		return TRUE;

	}
	
	return FALSE;
}
void CWzdDlg_IEDSel::SaveFile()		//20230531 luozibing ����xml������Ϣ
{
	CStNetCardInfor *pCard = NULL;
	int index  = m_cmb_card.GetCurSel();
	pCard = (CStNetCardInfor *)m_cmb_card.GetItemData(index);
	g_oIecfgGenMngr.m_strNetDesc = pCard->m_strInfor;
	CString m_strID = _P_GetConfigPath();
	m_strID += IECFG_GEN_MNGR_FILE_NAME_DEFAULT;
	g_oIecfgGenMngr.SaveXmlFile(m_strID,CIecfgGenMngrXmlRWKeys::g_pXmlKeys);
}
void CWzdDlg_IEDSel::OnCbnSelchangeCmbCard()
{
	m_cmb_ip.ResetContent();//���������
	int index = m_cmb_card.GetCurSel();
	if(index > 0||index == 0)
	{
		CStNetCardInfor *pCard = (CStNetCardInfor *)m_cmb_card.GetItemData(index);
		CStNetCardInforList::InsertToComboBox_IP(pCard,&m_cmb_ip);//2023-5-9 luozibing ����IP��Ϣ
	}
}
HBRUSH CWzdDlg_IEDSel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_TIPS)
	{
		CFont font;
		font.CreatePointFont(120,_T("΢���ź�"),NULL); 
		pDC->SetTextColor(RGB(0, 146, 159));
		pDC->SelectObject(&font);
	}
	return hbr;
}