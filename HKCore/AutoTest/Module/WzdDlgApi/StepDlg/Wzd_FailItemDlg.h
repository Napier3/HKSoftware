#pragma once
#include "WzdDlgBase.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../../../Module/GuideBook/Items.h"
#include "ListCtrlEx.h"
#include "afxwin.h"

// CWzd_FailItemDlg �Ի���

#define  WM_FAIL_ITEM_FING_CHANG WM_USER+1001

class CWzd_FailItemDlg : public CWzdDlgBase
{
	DECLARE_DYNAMIC(CWzd_FailItemDlg)

public:
	CWzd_FailItemDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWzd_FailItemDlg();

// �Ի�������
	enum { IDD = IDD_FAIL_ITEM_DIALOG };
	virtual void XUI_InitAdjust();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
	
public:
	//��ʼ�� �б��ֵ
	void InitFailItemInfo();
	//�������У����²���ֵ ���Ե�״̬ͼ��
	void UpdateFailItemInfo(CGbItemBase* pTestItem);

	//ɾ������ ���ͨ���Ĳ�����
	void DeleteFailItemItem(CGbItemBase* pTestItem);

	int FindRow(CGbItemBase* pTestItem);

protected:
	//��Ϣ��Ӧ����
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMRClickFailItemList(NMHDR *pNMHDR, LRESULT *pResult);
	//�Ҽ��˵�
	afx_msg void OnFindFailItem();
	afx_msg void OnFailItemAdvise();

private:
	// ���ϸ�����Ŀ��Ϣ
	CListCtrlEx m_ctrlFailItemList;
	int			m_nInitWidth;
	// ��ʾ
	CStatic m_Static1;
	CImageList m_ImageList;

};
