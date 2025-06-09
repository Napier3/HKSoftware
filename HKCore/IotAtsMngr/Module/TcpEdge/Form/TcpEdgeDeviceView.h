#ifndef _TCPEDGEDEVICEVIEW_H_
#define _TCPEDGEDEVICEVIEW_H_

#include "../TcpEdgeDevice.h"
#include "../TcpEdgeSavePkgThread.h"
#include "../Word/TcpEdgeWordTool.h"
#include <QWidget>
#include <QTreeWidgetItem>
#include <QTableWidgetItem>
#include <QStyledItemDelegate>
#include <QTextEdit>
#include <QMutex>

namespace Ui {
	class CTcpEdgeDeviceView;
}

struct tagDeviceTimer
{
	QString m_strPkg;
	long m_nType;
};

class CTcpEdgeDeviceView : public QWidget
{
	Q_OBJECT
private:
	Ui::CTcpEdgeDeviceView *ui;

	CTcpEdgeDevice* m_pDevice;
	CDvmDevice m_oDvmDevice;
	CDvmDatasetGroup m_treeGroup;

	QStringList m_oLogBuffer;

	bool m_bPkgIsSaving;
	CTcpEdgeSavePkgThread* m_pSavePkgThread;
	QVector<CString> m_tempPkgBuffer; //临时报告缓存,存放1000条,减少写入次数

	CTcpEdgeWordTool m_oRptWordTool;

	QTimer m_timer;
	QVector<tagDeviceTimer> m_vecTimer;
	QMutex m_oTimerLocker;

private:
	void InitUI();
	void InitTree(QTreeWidgetItem* pParent, CExBaseList* pData, CDvmLogicDevice* pDevice);
	QTreeWidgetItem* FindTreeNode(QTreeWidgetItem* pNode, QString strFuncName);
	void StartSavePkgThread();
	void ExitSaving();

	void ChangeRowColor(long nRow, QColor clr);

public:
	explicit CTcpEdgeDeviceView(QWidget *parent = NULL);
	~CTcpEdgeDeviceView();

	void SetDevice(CTcpEdgeDevice* pDevice, QString strSetupTime);
	CTcpEdgeDevice* GetDevice();
	void UpdatePkg(QString strPkg, long nType);
	void UpdateDataset();
	void JumpToFuncGrid(QString strFuncName);

protected slots:
	void slot_gridLButtonDblClk(QTableWidgetItem* pItem);
	void slot_currentItemChanged(QTreeWidgetItem* pCur, QTreeWidgetItem* pPrev);
	void slot_timeout();
};

#endif