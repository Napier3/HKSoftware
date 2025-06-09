#ifndef _TCPEDGETESTDLG_H_
#define _TCPEDGETESTDLG_H_

#include "TcpEdgeFormUI.h"
#include "TcpEdgeTestHeaderView.h"
#include "TcpEdgeTestDataView.h"
#include "../TcpEdgeDatasetProducer.h"

namespace Ui {
	class CTcpEdgeTestDlg;
}

class CTcpEdgeTestDlg : public CTcpEdgeFormUI
{
	Q_OBJECT
private:
	Ui::CTcpEdgeTestDlg *ui;
	CTcpEdgeTestHeaderView* m_viewHeader;
	CTcpEdgeTestDataView* m_viewData;
	CTcpEdgeDatasetProducer m_oProducer;
	CTcpEdgeDevice* m_pDevice;
	CDvmDatasetGroup m_oErrCfg; //���Դ�����ʾ

	void UpdateDatasetNode(CDvmDataset* pDataset, QString& strMessage);
	void InitViewData(const QString& strFunName);

public:
	CDvmDataset* m_pProducePkg;
	explicit CTcpEdgeTestDlg(QWidget *parent = NULL);
	~CTcpEdgeTestDlg();

	void InitUI();
	void AttachDevice(CTcpEdgeDevice* pDevice);
	int exec(const QString& strTitle, const QString& strFunName);
	CDvmDataset* GetDataset();
	bool UpdateDatasetNode();
	bool IsMngrChannel() { return m_viewData->m_bIsMngrCh; }
	virtual CDvmDataset* GetDefaultDataset(const QString& strFunName);

protected slots:
	void slot_adjustSize();
	void slot_ok(bool bChecked);
	void slot_clicked(bool bChecked);


	//lmy,20230910����ж��·����������ʽ�ݴ��ж�------Head����
	void UpdateDatasetNode_FmtHead(CDvmData* pData, QString& strMessage, QString& strRootNodeID);
	//����ж��·����������ʽ�ݴ��ж�------�ж��ַ����Ƿ�Ϊ����,�����Ƿ��ڷ�Χ��
	void JudgeNumAndRange(CDvmData* pData, QString& strMessage, double dLevel, double dUp, CString strRootNodeId);
	//����ж��·����������ʽ�ݴ��ж�------Data����
	void UpdateDatasetNode_FmtData(CDvmData* pData, QString& strMessage, QString& strRootNodeID);
	BOOL UpdateDatasetNode_FmtDataComBo(CDvmData* pData, QString& strMessage, QString& strRootNodeID);
	void UpdateDatasetNode_FmtDataOther(CDvmData* pData, QString& strMessage, QString& strRootNodeID);
	//lmy,20230913,��Ӷ��������ͽ��д���
	BOOL UpdateDatasetNode_FmtDataNumType(CDvmData* pData, QString& strMessage, QString& strRootNodeID);
	//����ж��Ƿ�������ĵ��ж�
	BOOL HasChineseChar(CString strData);

	//lmy,20230914���,�����жϵ����ڵ���ݴ����
	void UpdateDataNode(CDvmDataset* pObj, QString& strMessage);
	//���ڶ��ַ�����������ݴ����
	BOOL UpdateDataset_StringArray(CDvmDataset* pObj, QString& strMessage);
	BOOL UpdateData_StringArray(CDvmDataset* pObj, QString& strMessage, DWORD dwItemData, CString strRootNodeID);

};

#endif