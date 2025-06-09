#ifndef	 QSTTANTISHAKETIMEDINEVENTGROUPGRID
#define  QSTTANTISHAKETIMEDINEVENTGROUPGRID

#include "../../../Module/UI/SttTestCntrCmdDefine.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include <QTableWidget>
#include "../../Module/ScrollCtrl/ScrollTableWidget.h"
#include "../../Module/CommonCtrl_QT/CommonCtrlInterface.h"
#include "../../../../Module/DataMngr/DvmDataset.h"

#ifdef _PSX_QT_LINUX_
class QSttAntiShakeTimeDinEventGroupGrid:public QScrollTableWidget, public CCommonCtrlInterface
#else
class QSttAntiShakeTimeDinEventGroupGrid:public QTableWidget, public CCommonCtrlInterface
#endif
{
	Q_OBJECT

public:
	QSttAntiShakeTimeDinEventGroupGrid(QWidget *parent = NULL);
     ~QSttAntiShakeTimeDinEventGroupGrid();

	void InitUI();
	void InitTable();
	virtual void UpdateText(const QString &strText);
	void AddShowReports(CDvmDataset *pSoeRptDataset);
	CString GetAttrValue(CDvmData *pCurrData,const CString &strSearchID);


public:	
	BOOL m_bRunning;
	int m_nRowHeight;
	int m_nHeaderViewHeight;
	QTableWidgetItem *m_pCurrKeyboardItem;//弹键盘时使用的表格单元格

};


#endif
