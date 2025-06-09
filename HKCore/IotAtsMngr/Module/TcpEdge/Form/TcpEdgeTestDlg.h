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
	CDvmDatasetGroup m_oErrCfg; //测试错误提示

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


	//lmy,20230910添加判断下发命令参数格式容错判断------Head部分
	void UpdateDatasetNode_FmtHead(CDvmData* pData, QString& strMessage, QString& strRootNodeID);
	//添加判断下发命令参数格式容错判断------判断字符串是否为数字,并且是否在范围内
	void JudgeNumAndRange(CDvmData* pData, QString& strMessage, double dLevel, double dUp, CString strRootNodeId);
	//添加判断下发命令参数格式容错判断------Data部分
	void UpdateDatasetNode_FmtData(CDvmData* pData, QString& strMessage, QString& strRootNodeID);
	BOOL UpdateDatasetNode_FmtDataComBo(CDvmData* pData, QString& strMessage, QString& strRootNodeID);
	void UpdateDatasetNode_FmtDataOther(CDvmData* pData, QString& strMessage, QString& strRootNodeID);
	//lmy,20230913,添加对数字类型进行处理
	BOOL UpdateDatasetNode_FmtDataNumType(CDvmData* pData, QString& strMessage, QString& strRootNodeID);
	//添加判断是否包含中文的判断
	BOOL HasChineseChar(CString strData);

	//lmy,20230914添加,用于判断单个节点的容错测试
	void UpdateDataNode(CDvmDataset* pObj, QString& strMessage);
	//用于对字符串数组进行容错测试
	BOOL UpdateDataset_StringArray(CDvmDataset* pObj, QString& strMessage);
	BOOL UpdateData_StringArray(CDvmDataset* pObj, QString& strMessage, DWORD dwItemData, CString strRootNodeID);

};

#endif