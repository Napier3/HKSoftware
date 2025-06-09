#include "stdafx.h"
#include "GuideBookDefine.h"
#include "../XLanguageResourceAts.h"

#ifndef _PSX_QT_LINUX_
#include "..\..\..\Module\XFileMngrBase\DlgXFileMngr.h"
#endif
#include "../../../Module/System/TickCount32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//����ж��������ϸ񡢲��ϸ���ı�
CString g_strResultDescValueCorrect			= _T("�ϸ�");
CString g_strResultDescValueIncorrect		= _T("���ϸ�");

//shaolei 2023-8-15�����Թ����У���Ҫ��̬��ģ��������ӵ���Ŀ��ʹ�ú�ע��RemoveAll
CExBaseList g_oListItemsInsertToTree;

void Gb_AddResultJudgeKey(CValues *pValues,long nResult)
{
	if (pValues == NULL)
	{
		return;
	}

	CValue *pJdg = (CValue*)pValues->FindByID(g_strTestResultJudgeKey);
	CValue *pDsc = (CValue*)pValues->FindByID(g_strTestResultDescriptKey);
	CValue *pTime = (CValue*)pValues->FindByID(g_strTestResultTimeKey);

	if (pJdg == NULL)
	{
		pJdg = (CValue*)pValues->AddNew(g_strTestResultJudgeKey, g_strTestResultJudgeNameKey, _T(""));
		//pJdg->PutID(g_strTestResultJudgeKey);
		//pJdg->PutName(g_strTestResultJudgeNameKey);
	}

	if (pDsc == NULL)
	{
		pDsc = (CValue*)pValues->AddNew(g_strTestResultDescriptKey, g_strTestResultDescriptNameKey, _T(""));
		//pDsc->PutID(g_strTestResultDescriptKey);
		//pDsc->PutName(g_strTestResultDescriptNameKey);
	}

	if (pTime == NULL)
	{
		pTime = (CValue*)pValues->AddNew(g_strTestResultTimeKey, g_strTestResultTimeNameKey, _T(""));
		//pTime->PutID(g_strTestResultTimeKey);
		//pTime->PutName(g_strTestResultTimeNameKey);
	}

	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	pTime->m_strValue.Format(_T("%d.%d.%d"), tm.wYear, tm.wMonth, tm.wDay);

	pJdg->m_strValue.Format(_T("%d"), nResult);

	if (nResult == 0)
	{
		pDsc->PutValue(g_sLangTxt_Unqualified/*g_strResultDescValueIncorrect*/);
	}
	else
	{
		pDsc->PutValue(g_sLangTxt_Qualified/*g_strResultDescValueCorrect*/);
	}
}

void Gb_AddResultJudgeKey(CShortDatas  *pDatas,long nResult)
{
	if (pDatas == NULL)
	{
		return;
	}

	CShortData  *pJdg = (CShortData*)pDatas->FindByID(g_strTestResultJudgeKey);
	CShortData  *pDsc = (CShortData*)pDatas->FindByID(g_strTestResultDescriptKey);
	CShortData  *pTime = (CShortData*)pDatas->FindByID(g_strTestResultTimeKey);

	if (pJdg == NULL)
	{
		pJdg = (CShortData*)pDatas->AddNew();
		pJdg->PutID(g_strTestResultJudgeKey);
		pJdg->PutName(g_strTestResultJudgeNameKey);
	}

	if (pDsc == NULL)
	{
		pDsc = (CShortData*)pDatas->AddNew();
		pDsc->PutID(g_strTestResultDescriptKey);
		pDsc->PutName(g_strTestResultDescriptNameKey);
	}

	if (pTime == NULL)
	{
		pTime = (CShortData*)pDatas->AddNew();
		pTime->PutID(g_strTestResultTimeKey);
		pTime->PutName(g_strTestResultTimeNameKey);
	}

	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	pTime->m_strValue.Format(_T("%d.%d.%d"), tm.wYear, tm.wMonth, tm.wDay);

	CString strVal;
	strVal.Format(_T("%d"), nResult);
	pJdg->PutValue(strVal);

	if (nResult == 0)
	{
		pDsc->PutValue(g_sLangTxt_Unqualified/*g_strResultDescValueIncorrect*/);
	}
	else
	{
		pDsc->PutValue(g_sLangTxt_Qualified/*g_strResultDescValueCorrect*/);
	}
}

void Gb_GetItemBaseObjects(CExBaseList *pSrcList, CExBaseList *pDestList)
{
	POS pos = pSrcList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pSrcList->GetNext(pos);

		if (Gb_IsItemBaseClassID(p->GetClassID()))
		{
			pDestList->AddTail(p);
		}
	}
}

//2023-8-15  �ȴ���Ŀȫ��������Ŀ��
void Gb_WaitItemsInsertTree()
{
	CTickCount32 oTick;

	while (TRUE)
	{
		if (g_oListItemsInsertToTree.GetCount() == 0)
		{
			break;
		}

		oTick.DoEvents(50);
	}
}

const CString g_strDataSetID[DSID_dsMaxCount] = {_T("dsParameter"),_T("dsSetting"),_T("dsEna"),_T("dsAin")
	, _T("dsDin"),_T("dsRec"),_T("dsTripInfo"),_T("dsAlarm")
	, _T("dsWarning"),_T("dsSoe"),_T("dsSV"),_T("dsGOOSE"), _T("dsDout")
    , _T("all"), _T("dsOwnDef"), _T("none"), _T("report"), _T("log"), _T("file"), _T("dsMatrix")};
const CString g_strDataSetIDKey[DSID_dsMaxCount] = {_T("Parameter"),_T("Setting"),_T("Ena"),_T("Ain")
	, _T("Din"),_T("Rec"),_T("TripInfo"),_T("Alarm")
	, _T("Warning"),_T("Soe"),_T("SV"),_T("GOOSE"), _T("Dout")
    , _T("all"), _T("OwnDef"), _T("none"), _T("report"), _T("log"), _T("file"), _T("Matrix")};

const CString g_strDataSetName[DSID_dsMaxCount] = {_T("װ�ò���"),_T("��ֵ"),_T("ѹ��"),_T("ң��")
, _T("ң��"),_T("���ϱ���"),_T("�����¼�"),_T("�����ź�")
, _T("�澯�ź�"),_T("SOE"),_T("����ֵ"),_T("GOOSE") , _T("ң��")
, _T("all"), _T("�Զ���"), _T("none"), _T("report"), _T("log"), _T("file"), _T("����")};

//static const CString g_strDataSetName[DSID_dsMaxCount] = {g_sLangTxt_UnitPara/*_T("װ�ò���")*/,g_sLangTxt_FixedValue/*_T("��ֵ")*/,g_sLangTxt_Platen/*_T("ѹ��")*/,g_sLangTxt_Telemetering/*_T("ң��")*/
//	,g_sLangTxt_Telecommunicating/* _T("ң��")*/,g_sLangTxt_FaultReport/*_T("���ϱ���")*/,g_sLangTxt_ProtectEvent/*_T("�����¼�")*/,g_sLangTxt_FaultSignal/*_T("�����ź�")*/
//	, g_sLangTxt_AlarmSignal/*_T("�澯�ź�")*/,_T("SOE"),g_sLangTxt_SamplingValue/*_T("����ֵ")*/,_T("GOOSE") ,  g_sLangTxt_Telecontrolling/*_T("ң��")*/
//    , _T("all"), g_sLangTxt_Custom/*_T("�Զ���")*/, _T("none"), _T("report")};

const CString& Gb_GetDataSetName(const CString &strIDKey)
{
	static const  CString g_strDataSetError =g_sLangTxt_ErrorID /*_T("��������ݼ�ID")*/;
	long nIndex = 0;
	long nIndexFind = -1;

	for (nIndex=0; nIndex<DSID_dsMaxCount; nIndex++)
	{
		if (g_strDataSetID[nIndex].GetLength() == 0)
		{
			break;
		}

		if (g_strDataSetID[nIndex].Find(strIDKey) >= 0)
		{
			nIndexFind = nIndex;
			break;
		}
	}

	if (nIndexFind != -1)
	{
		return g_strDataSetName[nIndexFind];
	}
	else
	{
		return g_strDataSetError;
	}
}

const CString& Gb_GetDataSetID(const CString &strID)
{
	long nIndex = 0;
	long nIndexFind = -1;

	for (nIndex=0; nIndex<DSID_dsMaxCount; nIndex++)
	{
		if (g_strDataSetID[nIndex].GetLength() == 0)
		{
			break;
		}

		if (strID.Find(g_strDataSetID[nIndex]) >= 0)
		{
			nIndexFind = nIndex;
			break;
		}
	}

	if (nIndexFind != -1)
	{
		return g_strDataSetID[nIndexFind];
	}
	else
	{
		return g_strDataSetID[DSID_dsAll];
	}
}

static const  CString g_strDataSetIDError = _T("Err_dsID");

const CString& Gb_GetDataSetKey(const CString &strID)
{
	long nIndex = 0;
	long nIndexFind = -1;

	for (nIndex=0; nIndex<DSID_dsMaxCount; nIndex++)
	{
		if (g_strDataSetID[nIndex].GetLength() == 0)
		{
			break;
		}

		if (g_strDataSetID[nIndex].Find(strID) >= 0)
		{
			nIndexFind = nIndex;
			break;
		}
	}

	if (nIndexFind != -1)
	{
		return g_strDataSetIDKey[nIndexFind];
	}
	else
	{
		return strID;
	}
}


void Gb_GetDataSetKeyEx(const CString &strID, CStringArray &astrKeys)
{
	CString strKey = Gb_GetDataSetKey(strID);

	if (!Gb_IsDataSetIDError(strKey))
	{
		astrKeys.Add(strKey);
	}
}

long Gb_GetDataSetKey(const CString &strID, CStringArray &astrKeys)
{
	astrKeys.RemoveAll();
	CString strTempID = strID;
	long nPos = 0;
	long nLen = strTempID.GetLength();
	CString strKey;

	while (TRUE)
	{
		nPos = strTempID.Find('#');

		if (nPos > 0)
		{
			strKey = strTempID.Left(nPos);
			strTempID = strTempID.Mid(nPos+1);
			Gb_GetDataSetKeyEx(strKey, astrKeys);
		}
		else
		{
			break;
		}
	}

	Gb_GetDataSetKeyEx(strTempID, astrKeys);

	return astrKeys.GetCount();
}

BOOL Gb_IsDataSetIDError(const CString &strID)
{
	return (g_strDataSetIDError == strID);
}

#ifndef _PSX_QT_LINUX_
#include "..\GuideBookFileMngr\GuideBookFileMngr.h"

CString Gb_GetOpenGuideBookFile(const CString &strGbFileType, CWnd *pParent)
{
	CString strFileName;

	CString strFileType = strGbFileType;
	CString strDes;

	Gb_ValidateGuideBookFileType(strFileType);
	strDes = Gb_GetGuideBookFileDes(strFileType);

	CGuideBookFileMngr::InitGuideBookFileMngr(strGbFileType, TRUE);
#ifdef GB_USE_XFILEMNGRBASE
	CDlgXFileMngr dlg(0,strGbFileType,strDes,CGuideBookFileMngr::g_pGuideBookFileMngr,OPEN_FILE_MODE,pParent);
#else
	CDlgFileMngr dlg(0,strGbFileType,strDes,CGuideBookFileMngr::g_pGuideBookFileMngr,OPEN_FILE_MODE,pParent);
#endif

	if (strFileType == g_strTGbFileFilter)
	{
		dlg.InitHistory(GB_FILE_DLG_HISTORY_FILE_GBT, CString(_P_GetTemplatePath()));
	}
	else
	{
		dlg.InitHistory(GB_FILE_DLG_HISTORY_FILE, CString(_P_GetTemplatePath()));
	}

	if(dlg.DoModal() == IDOK)
	{
		strFileName = dlg.GetFileName();
	}

	return strFileName;
}
#endif


void Gb_SetGbModifiedFlag(CExBaseObject *pGbObj, BOOL bFlag)
{
	if (pGbObj == NULL)
	{
		return;
	}

	CExBaseObject *pGuideBook = (CExBaseObject *)pGbObj->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

	if (pGuideBook == NULL)
	{
		return;
	}

	pGuideBook->m_dwReserved = bFlag;
}

BOOL Gb_GetGbModifiedFlag(CExBaseObject *pGbObj)
{
	if (pGbObj == NULL)
	{
		return FALSE;
	}

	CExBaseObject *pGuideBook = (CExBaseObject *)pGbObj->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

	if (pGuideBook == NULL)
	{
		return FALSE;
	}

	return (pGuideBook->m_dwReserved > 0);
}

//////////////////////////////////////////////////////////////////////////
//ģ��༭��ص�ȫ�ֱ���
CExBaseList *g_pListRetry = NULL;
CExBaseList *g_pListRepeat = NULL;
CExBaseList *g_pListTimeLong = NULL;

class _CGbDevGlobalDefine_Init
{
public:
	_CGbDevGlobalDefine_Init()
	{
		g_pListRetry = NULL;
		g_pListRepeat = NULL;
		g_pListTimeLong = NULL;
	}

	void Init()
	{
		g_pListRetry = new CExBaseList();
		g_pListRepeat = new CExBaseList();
		g_pListTimeLong = new CExBaseList();

		g_pListRetry->AddNew(_T("0"),_T("0"));
		g_pListRetry->AddNew(_T("1"),_T("1"));
		g_pListRetry->AddNew(_T("2"),_T("2"));
		g_pListRetry->AddNew(_T("3"),_T("3"));
		g_pListRetry->AddNew(_T("4"),_T("4"));
		g_pListRetry->AddNew(_T("5"),_T("5"));
		g_pListRetry->AddNew(_T("6"),_T("6"));
		g_pListRetry->AddNew(_T("7"),_T("7"));
		g_pListRetry->AddNew(/*_T("�����쳣")*/g_sLangTxt_IgnoreAbnormal,_T("-1"));

		g_pListRepeat->AddNew(_T("0"),_T("0"));
		g_pListRepeat->AddNew(_T("2"),_T("2"));
		g_pListRepeat->AddNew(_T("3"),_T("3"));
		g_pListRepeat->AddNew(_T("4"),_T("4"));
		g_pListRepeat->AddNew(_T("5"),_T("5"));
		g_pListRepeat->AddNew(_T("6"),_T("6"));
		g_pListRepeat->AddNew(_T("7"),_T("7"));
		g_pListRepeat->AddNew(_T("8"),_T("8"));
		g_pListRepeat->AddNew(_T("9"),_T("9"));
		g_pListRepeat->AddNew(_T("10"),_T("10"));
		g_pListRepeat->AddNew(_T("11"),_T("11"));
		g_pListRepeat->AddNew(_T("12"),_T("12"));
		g_pListRepeat->AddNew(_T("13"),_T("13"));
		g_pListRepeat->AddNew(_T("14"),_T("14"));
		g_pListRepeat->AddNew(_T("15"),_T("15"));
		g_pListRepeat->AddNew(_T("16"),_T("16"));
		g_pListRepeat->AddNew(_T("17"),_T("17"));
		g_pListRepeat->AddNew(_T("18"),_T("18"));
		g_pListRepeat->AddNew(_T("19"),_T("19"));
		g_pListRepeat->AddNew(_T("20"),_T("20"));
		g_pListRepeat->AddNew(_T("30"),_T("30"));
		g_pListRepeat->AddNew(_T("50"),_T("50"));
		g_pListRepeat->AddNew(_T("80"),_T("80"));
		g_pListRepeat->AddNew(_T("100"),_T("100"));
		g_pListRepeat->AddNew(_T("150"),_T("150"));

		g_pListTimeLong->AddNew(_T("0"),_T("0"));
		g_pListTimeLong->AddNew(_T("100"),_T("100"));
		g_pListTimeLong->AddNew(_T("200"),_T("200"));
		g_pListTimeLong->AddNew(_T("500"),_T("500"));
		g_pListTimeLong->AddNew(_T("1000"),_T("1000"));
		g_pListTimeLong->AddNew(_T("2000"),_T("2000"));
		g_pListTimeLong->AddNew(_T("3000"),_T("3000"));
		g_pListTimeLong->AddNew(_T("5000"),_T("5000"));
		g_pListTimeLong->AddNew(_T("8000"),_T("8000"));
		g_pListTimeLong->AddNew(_T("10000"),_T("10000"));
		g_pListTimeLong->AddNew(_T("15000"),_T("15000"));
		g_pListTimeLong->AddNew(_T("20000"),_T("20000"));
		g_pListTimeLong->AddNew(_T("30000"),_T("30000"));
		g_pListTimeLong->AddNew(_T("60000"),_T("60000"));
	}
	virtual ~_CGbDevGlobalDefine_Init()
	{
		if (g_pListRetry != NULL)
		{
			delete g_pListRetry;
			delete g_pListRepeat;
			delete g_pListTimeLong;
		}

		g_pListRetry = NULL;
		g_pListRepeat = NULL;
		g_pListTimeLong = NULL;
	}

}g_GbDevGlobalDefine_Init;

void Gb_GbDevGlobalDefine_Init()
{
	if (g_pListRetry != NULL)
	{
		return;
	}

	g_GbDevGlobalDefine_Init.Init();
}

//2019-1-28  �Ƿ�Ϊ����xml��ʽ�ı���
BOOL g_bGbExportXmlReportFile = FALSE;

//2021-1-14  �Ƿ񱣴�ģ��ṹ�����ļ�
BOOL g_bGbSaveGbStruDscFile = FALSE;

//2023-4-10  ����dscxmlʱ���Ƿ񱣴���Ŀ״̬��
BOOL g_bGbSaveItemState_WhenSavedscxml = FALSE;
