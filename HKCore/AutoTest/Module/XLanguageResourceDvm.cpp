//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLanguageResourceBase.cpp  CXLanguageResourceAtsBase


#include "stdafx.h"
#include "XLanguageResourceDvm.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
const CString  CXLanguageResourceDvmBase::g_strXLangRsDvmBaseFile = _T("RsDvmBase"); 
CXLanguageResourceDvmBase::CXLanguageResourceDvmBase()
{
	
}


CXLanguageResourceDvmBase::~CXLanguageResourceDvmBase()
{
	m_oXLangRsDvmBase.RemoveAll(); 
}

void CXLanguageResourceDvmBase::InitLangFileForDebug(const CString &strModule)
{
	m_strXLangFile = _P_GetLanguagePath();
	m_strXLangFile.AppendFormat(_T("%s.xml"), strModule);
}
CXLangItem* CXLanguageResourceDvmBase::rs_AddString(const CString &strID, CString *pstrString)
{
	CXLangItem *p = CXLanguage::AddString(strID, pstrString); 

	m_oXLangRsDvmBase.AddTail(p); 

	return p;
}

void CXLanguageResourceDvmBase::InitLangRsByFile()
{
	CXLanguageResourceBase::InitLangRsByFile(); 

	InitLangRsByFileEx(&m_oXLangRsDvmBase, g_strXLangRsDvmBaseFile); 
}


void CXLanguageResourceDvmBase::RegisterLanguageResource()
{
	CXLanguageResourceBase::RegisterLanguageResource();
	rs_AddString(g_sLangID_CanotCreatWnd, &g_sLangTxt_CanotCreatWnd);
	rs_AddString(g_sLangID_ConnetDev, &g_sLangTxt_ConnetDev);
	rs_AddString(g_sLangID_CommunError, &g_sLangTxt_CommunError);
	rs_AddString(g_sLangID_CommunTestStop, &g_sLangTxt_CommunTestStop);
	rs_AddString(g_sLangID_NoPrtc, &g_sLangTxt_NoPrtc);
	rs_AddString(g_sLangID_CreatPrtcFail, &g_sLangTxt_CreatPrtcFail);
	rs_AddString(g_sLangID_FctnDevelop, &g_sLangTxt_FctnDevelop);

	rs_AddString(g_sLangID_Find, &g_sLangTxt_Find);
	rs_AddString(g_sLangID_Ge, &g_sLangTxt_Ge);
	rs_AddString(g_sLangID_MatchingTurn, &g_sLangTxt_MatchingTurn);
	rs_AddString(g_sLangID_Correlation, &g_sLangTxt_Correlation);
	rs_AddString(g_sLangID_DelCorrelation, &g_sLangTxt_DelCorrelation);
	rs_AddString(g_sLangID_DataSel, &g_sLangTxt_DataSel);
	rs_AddString(g_sLangID_DelRstNewTest, &g_sLangTxt_DelRstNewTest);
	rs_AddString(g_sLangID_DevDataTemp, &g_sLangTxt_DevDataTemp);
	rs_AddString(g_sLangID_DevDataModelTest, &g_sLangTxt_DevDataModelTest);
	rs_AddString(g_sLangID_DevDataModelCompara, &g_sLangTxt_DevDataModelCompara);
	rs_AddString(g_sLangID_OutputInf, &g_sLangTxt_OutputInf);
	rs_AddString(g_sLangID_CopyOutput, &g_sLangTxt_CopyOutput);
	rs_AddString(g_sLangID_ClearOutput, &g_sLangTxt_ClearOutput);
	
}

CString CXLanguageResourceDvmBase::g_sLangID_CanotCreatWnd             = _T("sCanotCreatWnd");
CString CXLanguageResourceDvmBase::g_sLangTxt_CanotCreatWnd            = _T("δ�ܴ����������\n");
CString CXLanguageResourceDvmBase::g_sLangID_ConnetDev                 = _T("sConnetDev");
CString CXLanguageResourceDvmBase::g_sLangTxt_ConnetDev                = _T("�����豸�ɹ�");
CString CXLanguageResourceDvmBase::g_sLangID_CommunError               = _T("sCommunError");
CString CXLanguageResourceDvmBase::g_sLangTxt_CommunError              = _T("ͨѶ�����г��ִ���");
CString CXLanguageResourceDvmBase::g_sLangID_CommunTestStop            = _T("sCommunTestStop");
CString CXLanguageResourceDvmBase::g_sLangTxt_CommunTestStop           = _T("ͨѶ�����쳣��������ֹ");
CString CXLanguageResourceDvmBase::g_sLangID_NoPrtc                    = _T("sNoPrtc");
CString CXLanguageResourceDvmBase::g_sLangTxt_NoPrtc                   = _T("û��ע���Լ�������");
CString CXLanguageResourceDvmBase::g_sLangID_CreatPrtcFail             = _T("sCreatPrtcFail");
CString CXLanguageResourceDvmBase::g_sLangTxt_CreatPrtcFail            = _T("������ԼͨѶ�豸ʧ��");
CString CXLanguageResourceDvmBase::g_sLangID_FctnDevelop               = _T("sFctnDevelop");
CString CXLanguageResourceDvmBase::g_sLangTxt_FctnDevelop              = _T("������ƿ�����");

CString CXLanguageResourceDvmBase::g_sLangID_Find                      = _T("sFind");
CString CXLanguageResourceDvmBase::g_sLangTxt_Find                     = _T("����");
CString CXLanguageResourceDvmBase::g_sLangID_Ge                        = _T("sGe");
CString CXLanguageResourceDvmBase::g_sLangTxt_Ge                       = _T("��");
CString CXLanguageResourceDvmBase::g_sLangID_MatchingTurn              = _T("sMatchingTurn");
CString CXLanguageResourceDvmBase::g_sLangTxt_MatchingTurn             = _T("�Ӵ���������ƥ��");
CString CXLanguageResourceDvmBase::g_sLangID_Correlation               = _T("sCorrelation");
CString CXLanguageResourceDvmBase::g_sLangTxt_Correlation              = _T("����");
CString CXLanguageResourceDvmBase::g_sLangID_DelCorrelation            = _T("sDelCorrelation");
CString CXLanguageResourceDvmBase::g_sLangTxt_DelCorrelation           = _T("ɾ������");
CString CXLanguageResourceDvmBase::g_sLangID_DataSel                   = _T("sDataSel");
CString CXLanguageResourceDvmBase::g_sLangTxt_DataSel                  = _T("����ѡ��");
CString CXLanguageResourceDvmBase::g_sLangID_DelRstNewTest             = _T("sDelRstNewTest");
CString CXLanguageResourceDvmBase::g_sLangTxt_DelRstNewTest            = _T("Ҫɾ��֮ǰ�Ľ���������µĲ�����");
CString CXLanguageResourceDvmBase::g_sLangID_DevDataTemp               = _T("sDevDataTemp");
CString CXLanguageResourceDvmBase::g_sLangTxt_DevDataTemp              = _T("װ���豸����ģ��");
CString CXLanguageResourceDvmBase::g_sLangID_DevDataModelTest          = _T("sDevDataModelTest");
CString CXLanguageResourceDvmBase::g_sLangTxt_DevDataModelTest         = _T("�豸����ģ�Ͳ���");
CString CXLanguageResourceDvmBase::g_sLangID_DevDataModelCompara       = _T("sDevDataModelCompara");
CString CXLanguageResourceDvmBase::g_sLangTxt_DevDataModelCompara      = _T("�豸����ģ�ͱȽ�");
CString CXLanguageResourceDvmBase::g_sLangID_OutputInf                 = _T("sOutputInf");
CString CXLanguageResourceDvmBase::g_sLangTxt_OutputInf                = _T("�����Ϣ");
CString CXLanguageResourceDvmBase::g_sLangID_CopyOutput                = _T("sCopyOutput");
CString CXLanguageResourceDvmBase::g_sLangTxt_CopyOutput               = _T("�������");
CString CXLanguageResourceDvmBase::g_sLangID_ClearOutput               = _T("sClearOutput");
CString CXLanguageResourceDvmBase::g_sLangTxt_ClearOutput              = _T("������");