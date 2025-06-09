#pragma once
#include "afxwin.h"

#include "..\..\Module\Xlanguage\Xlanguagetextwnd.h"
#include "..\..\Module\XLanguage\XLanguageButton.h"
#include "..\..\GuideBook\GuideBookInterface.h"

//////////////////////////////////////////////////////////////////////////

class CCommCmdEditGrid : public CGridCtrl
{
public:
	CCommCmdEditGrid();
	virtual ~CCommCmdEditGrid();

public:
	virtual void InitGrid(CCommCmd* pCommCmd);

protected:
	CCommCmd *m_pCommCmd;
	CExBaseList *m_pCpuDataList;

	virtual void ShowColumnTitle();
	//�༭����
	virtual BOOL EndEditCell(int nRow, int nCol, DWORD dwItemData=0);
	BOOL EndEditCell_Value(int nRow, DWORD dwItemData=0);
	virtual void InitData();
	virtual void InsertValuetoItem(CExBaseObject *pData,int &nRowIndex);

protected:
};


// CCommCmdParaEditDlg �Ի���

class CCommCmdParaEditDlg : public CDynDialogEx
{
protected:
	CCommCmdEditGrid m_gridPara;

public:
	CCommCmdParaEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCommCmdParaEditDlg();
	CCommCmd *m_pCommCmd;
	void xlang_InitAndAdjust();

// �Ի�������
	//enum { IDD = IDD_EDIT_COMMCMD_PARA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CXLanguageButton m_btnCommcmdOk;
	CXLanguageButton m_btnCommcmdCancel;
	CEdit m_edtCmdInfor;
};
