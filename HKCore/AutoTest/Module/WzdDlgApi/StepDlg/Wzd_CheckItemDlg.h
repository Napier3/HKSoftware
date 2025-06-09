#pragma once
#include "WzdDlgBase.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../../../Module/GuideBook/Items.h"
#include "ListCtrlEx.h"
// CWzd_CheckItemDlg �Ի���

class CWzd_CheckItemDlg : public CWzdDlgBase
{
	DECLARE_DYNAMIC(CWzd_CheckItemDlg)

public:
	CWzd_CheckItemDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWzd_CheckItemDlg();

// �Ի�������
	enum { IDD = IDD_CHECK_ITEM__DIALOG };
	virtual void XUI_InitAdjust();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
	


public:
	//��ʼ�� �б��ֵ �����ڵ�
	void InitCheckItemInfo(CItems* pStep);
	//���ݲ���ָ����� ��ǰ�� ���¼����
	void UpdateCheckItemInfo(CItems* pStep);
	//�������У����²���ֵ ���Ե�״̬ͼ�꣬���ϸ���ʾ�ڲ��ϸ��б�
	void UpdateCheckItemState(CGbItemBase* pTestItem);
	void UpdateCheckItemState2();
	//��ȡ��ǰѡ�нڵ�
	bool GetCurrentItemInfo(CItems* &pTestItem);
	//���õ�ǰѡ����
	void SetSelectRow(CItems* pTestItem);

protected:
	//��Ϣ��Ӧ����
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMClickCheckItemList(NMHDR *pNMHDR, LRESULT *pResult);	
	//�Ҽ��˵�
	afx_msg void OnNMRClickCheckItemList(NMHDR *pNMHDR, LRESULT *pResult);
	//�˵���ť  ���Ե�ǰ��Ŀ  �ӵ�ǰ��Ŀ��ʼ����  �鿴��ϸ��Ϣ
	afx_msg void OnTestCurrentItem();
	afx_msg void OnFromTestItem();
	afx_msg void OnCheckDetailInfo();

private:
	// ������Ŀ��Ϣ
	//CListCtrl m_ctrlChectItemList;
	CListCtrlEx m_ctrlChectItemList;
	CImageList m_ImageList;

	CItems*  m_pCurrentStepItem;
	CItems*  m_pTestItem;
};
