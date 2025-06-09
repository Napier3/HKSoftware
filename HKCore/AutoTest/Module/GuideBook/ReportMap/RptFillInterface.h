#pragma once
/*
   ���洦��ģ��Ľӿ�
   ���ű��洦���ȫ���������
*/

#include "../../GuideBook/GuideBook.h"
#include "../../../../Module/BaseClass/ThreadProgressInterface.h"

class CRptFillInterface
{
public:
	CRptFillInterface(void);
	virtual ~CRptFillInterface(void);

	void SetCommCmdCpusIndex(long nIndex)	{	m_nCommCmdCpusIndex = nIndex;	}

	void SetFillReport(BOOL bFillReport)	{	m_bFillReport = bFillReport;	}
	BOOL CanFillReport()	{	return m_bFillReport;	}
	BOOL IsReportFill_System()		{	return GetReportFillClassID() == REPORTFILL_PROGID_SYSTEM;	}
	void SetGuideBook(CGuideBook* pGuideBook)	{ m_pGuideBook = pGuideBook;}
	CString GetReportFile()	{	return m_strReportFile;	}

	//������Ա����
	CWnd*	m_pParentWnd;
	HWND	m_hParentWnd;

	CGuideBook* m_pGuideBook;	//��Ӧ��GuideBook

	CString m_strName;

	static BOOL g_bClearBeforeFillRpt;  //��䱨�����ݵ�ʱ�����������ǩλ�õ�����

protected:
	//����ӳ���ϵ�ļ�
	CString m_strReportMapFile;

	//����ģ���ļ�
	CString m_strReportTemplFile;

	//�����ļ�
	CString m_strReportFile;

	long m_nCommCmdCpusIndex; //ͨѶ����������豸��ţ���д������ʱʹ��

	CString m_strMgrpIndex;

	BOOL m_bFillReport;

public:
	//��������
	//��ȡ���鱨�洦������������
	//���ڵ������鱨����������������Ĳ���
	void SetParentWnd(CWnd* pParentWnd);
	CWnd* GetReportMainWnd();

	HWND FindRptDocWindow(const CString &strDoc);
	HWND FindRptDocWindow();
	CWnd* FindRptDocWindowEx();

	void FreeReportMap();
	CGbItemBase* GetParentGbItem(CReport *pReport);
	long InitFillReport(CGbItemBase* pItemBase);
	long InitFillReport(CReport* pReport);

	long UpdateReport(CReport* pReport);
	void ChopValueString(CRptData *pData, CString &strValue);

	CValue* FindValue(CValues *pValues, const CString &strID);

	CString GetReportString(CRptData *pData, CRptBkmk *pBkmk, CReport *pReport);
	BOOL GetReportString_CommCmd(CCommCmd *pCommCmd, CRptBkmk *pBkmk, CReport *pReport, CRptData *pData, CString &strValue);
	BOOL GetReportString_SysParaEdit(CSysParaEdit *pSysParaEdit, CRptBkmk *pBkmk, CReport *pReport, CRptData *pData, CString &strValue);
	BOOL GetReportString_MacroTest(CMacroTest *pMacroTest, CRptBkmk *pBkmk, CReport *pReport, CRptData *pData, CString &strValue, CString &strDataID);
	BOOL GetReportString_Safety(CSafety *pSafety, CRptBkmk *pBkmk, CReport *pReport, CRptData *pData, CString &strValue);

public:
	virtual CString GetReportFillClassID() = 0;

	virtual long New(CString strReportMapFile, CString strReportTemplFile, CString strReportFile, BOOL bFirst) = 0;
	virtual long Open(const CString  &strReportFile, BOOL bFirst) = 0;
	virtual long Save() = 0;
	virtual long SaveAs(CString  strRptFile)= 0;
	virtual long Close(long nSave) = 0;
	virtual void CloseDoc(DWORD dwFlag=0)	{	}

	virtual void SetSysRptShowMaxCount(long nSysRptShowMaxCount)=0;

	//���ݿ���ʾ��ͼ�Ĵ�С����������ͼ��С
	virtual void AdjustReportWindowOnSize() = 0;

	//�Ƿ������Ҫ��д�ı������ݵ�λ��
	virtual long HasReportNeedFill(const CGbItemBase* pItem) = 0;

	//���ñ������ݣ���д����
	virtual long FillReport(CReport* pReport, long nRepeatIndex, long nInsertDataLinkWhenEligible) = 0;
	//shaolei 20220507
	virtual void FillReport(CRptData *pData, CReport *pReport){}
	
	//�ڱ����ж�λ
	virtual long LocateReport(CGbItemBase* pItemBase) = 0;

	//��������
	virtual long AdjustReport(CThreadProgressInterface *pProgress=NULL) = 0;
	virtual long AdjustReport_FillEmpty() = 0;

	virtual BOOL ActiveWindow(const CString &strTitle) = 0;
	virtual BOOL AddNewReport(const CString &strRptTmplFile)=0;
	virtual void PrintReport() = 0;
	virtual void ZoomReport(long nPercentage) = 0;
	virtual long GetZoomReport() = 0;
	virtual void EmptyReportText() = 0;

	virtual void CmbmMgrpt(CRptFillInterface *pRptFill, long nMgbrpIndex)=0;
};

inline void rpt_InitRptTypeCombBox(CComboBox *pComboBox, long nReportControl)
{
	long nIndex = 0;
	nIndex = pComboBox->AddString(REPORTFILL_PROGID_WORD);
	pComboBox->SetItemData(nIndex, REPORTFILL_INDEX_WORD);

	nIndex = pComboBox->AddString(REPORTFILL_PROGID_WPS);
	pComboBox->SetItemData(nIndex, REPORTFILL_INDEX_WPS);

	nIndex = pComboBox->AddString(REPORTFILL_PROGID_SYSTEM);
	pComboBox->SetItemData(nIndex, REPORTFILL_INDEX_SYSTEM);

	nIndex = pComboBox->AddString(REPORTFILL_PROGID_NONE);
	pComboBox->SetItemData(nIndex, REPORTFILL_INDEX_NONE);

	for (nIndex=0; nIndex<4; nIndex++)
	{
		if (nReportControl == pComboBox->GetItemData(nIndex))
		{
			pComboBox->SetCurSel(nIndex);
			break;
		}
	}
}


inline DWORD rpt_GetRptTypeCombBox(CComboBox *pComboBox)
{
	long nSel = pComboBox->GetCurSel();

	if (nSel == CB_ERR)
	{
		return REPORTFILL_INDEX_NONE;
	}

	return pComboBox->GetItemData(nSel);
}

