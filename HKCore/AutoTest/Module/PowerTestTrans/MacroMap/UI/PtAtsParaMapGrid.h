#pragma once

#include "..\..\Module\GridBase\ExBaseListGrid.h"

//#define WM_OPEN_PARAVALUEMAPDLG  (WM_USER + 2116)
#define WM_SHOW_VALUEMAP  (WM_USER + 2117)
#define WM_DELETE_PARAMAP  (WM_USER + 2118)
#define GRID_PARAMAP_DELETE             0X089202
class CPtAtsParaMapGrid : public CExBaseListGrid
{
public:
	CPtAtsParaMapGrid();
	virtual ~CPtAtsParaMapGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	void AttachMsgRcvWnd(CWnd *pWnd)			{	m_pMsgRcvWnd = pWnd;	}

protected:
	CWnd *m_pMsgRcvWnd;

	//���غ���
public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual BOOL UpdateData(CExBaseObject *pData);
	virtual void SetMidifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);    //�������ѡ�б���У��Ի�ȡPt���������в���ӳ��
	//afx_msg void OnRButtonDown(UINT nFlags, CPoint point);    //�Ҽ�����ѡ�б���У������Ի��򣬽���ֵ��ӳ��
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint point);
	afx_msg void OnDeleteParaMap();


	DECLARE_MESSAGE_MAP()

};


