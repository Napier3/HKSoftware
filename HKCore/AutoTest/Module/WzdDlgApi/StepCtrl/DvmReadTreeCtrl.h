#pragma once


class CDvmReadTreeCtrl : public CTreeCtrl
{
	// ����
public:
	CDvmReadTreeCtrl();

	void ClearLDNodeTree()
	{
		DeleteAllItems();
	}

	virtual void InitDeviceNodeList(long nDeviceIndex);
	virtual void UpdateDeviceState(long nDeviceIndex);
	virtual void UpdateDeviceState(ACSI_NODE *pDevice);
	virtual void UpdateDatasetState(long nDeviceIndex, long nLDIndex, long nDsIndex);
	virtual void UpdateDatasetState(LD_DATASET_INFO *pLD_INFO);

	virtual void UpdateDeviceIP_Desc(long nDeviceIndex);//zhouhj20190923 ����IP��ַ�󣬸������νڵ���IP������
	virtual long FindDevIndexByIP(const CString &strIP);//zhouhj 20200208 
	BOOL SelDeviceNode(long nNodeType,long nDevIndex,long nLogicDevIndex,long nDatasetIndex);//�����ڵ��"���ļ�"��"����־"�Ȱ�ťʱ,�Զ�����ѡ���Ӧ�ڵ�

	virtual void InitRootObject();
	virtual void InsertDevice(long nDeviceIndex, HTREEITEM hParent);
private:
	virtual void InsertLDevice(long nDeviceIndex, long nLDIndex, HTREEITEM hParent);
	virtual void OnMmsSelchanged(HTREEITEM hItem);

protected:
	ST_UCHAR * m_pStartAddr_ACSI_CTRL;
	ST_UCHAR * m_pStartAddrDEVICE_NODE;
	ST_UCHAR * m_pStartAddrACSI_NODE;
	ST_UCHAR * m_pStartAddr_SOERPT;
	ST_UCHAR * m_pStartAddr_RLYSOERPT;

	// ��д
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	HTREEITEM m_hCurrSelItem;

	// ʵ��
public:
	virtual ~CDvmReadTreeCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};
