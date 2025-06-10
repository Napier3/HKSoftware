#pragma once
#include "../Module/SCL/SclIecCfgDatasGrid.h"


// CAT02D_CBsDlg �Ի���

class CAT02D_CBsDlg : public CDialog
{
	DECLARE_DYNAMIC(CAT02D_CBsDlg)

public:
	CSclIecCfgCtrlGrid m_oSclIecCfgCtrlGrid;
	CExBaseList *m_pCurDatasList;

	CAT02D_CBsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAT02D_CBsDlg();

	void AttachMsgWnd(CExBaseListGridOptrInterface *pMsgWnd){m_pDataViewOptrInterface = pMsgWnd;}
	void ShowGridDatas(CExBaseList *pDatas);

// �Ի�������
	enum { IDD = IDD_AT02D_CBS_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	CExBaseListGridOptrInterface *m_pDataViewOptrInterface;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
