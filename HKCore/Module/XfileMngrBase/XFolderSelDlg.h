#pragma once

#include "XFileDlgDefine.h"
#include "XFileMngr.h"
#include "XFolderTreeCtrl.h"

// CXFolderSelDlg �Ի���

class CXFolderSelDlg : public CDynDialogEx
{
	//DECLARE_DYNAMIC(CXFolderSelDlg)

public:
	CXFolderSelDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CXFolderSelDlg();
	
	CXFileMngr *m_pXFileMngr;
	CXFolder *m_pSrcFolder;
	void EnableOkButton();

// �Ի�������

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CButton m_btnOK;
	CButton m_btnCancel;
	CXFolderTreeCtrl m_treeFolder;
	CImageList *m_pImgFolder;//�ܺ�� 20200228 �����������οؼ����ļ���ͼ��

	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	afx_msg LRESULT OnXFileMngrSelChanged(WPARAM wParam, LPARAM lParam);

};
