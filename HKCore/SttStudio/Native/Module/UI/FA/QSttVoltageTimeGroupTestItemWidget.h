#ifndef QSTTVOLTAGETIMEGROUPTESTITEMWIDGET_H
#define QSTTVOLTAGETIMEGROUPTESTITEMWIDGET_H

#include <QWidget>
#include "../Controls/SttCheckBox.h"
#include <QTableWidget>
#include <QPushButton>
#include "../../../Module/DataMngr/DataGroup.h"
#include "../../SttTest/Common/tmt_result_def.h"

class QSttVoltageTimeGroupTestItemWidget : public QWidget
{
	Q_OBJECT

public:
	QSttVoltageTimeGroupTestItemWidget(QWidget *parent = NULL);
	virtual ~QSttVoltageTimeGroupTestItemWidget();

private:
	CDataGroup *m_pVolTimeTypeSecDataGroup;
	QList<QSttCheckBox*> m_pSelcetCheckItemList; // 存储复选框的列表
	QTableWidget* m_pVolTimeTypeTestItemTableWidget;//测试项目表格
	QPushButton *m_pCheckSelBtn;//全选/清空
	QSttCheckBox *m_pRemoteMonitorCheckBox;//遥信变位监视
	CString m_strItemID;//当前测试的节点路径
	long m_nBinIn[MAX_BINARYIN_COUNT];//存储上一次开入量

public:
	void InitUI();
	void InitTable();
	void InitConnections();
	void InitData(CDataGroup *pParas);
	void StartInit();
	void StopInit();
	void UpdateData(CDataGroup *pParas);
	void UpdateStateTable();//更新状态序列设置表格
	void UpdateResultState( CString strID,const CString &strState );//更新测试项目表格的状态一列
	void ClearResultState();
	void UpdateEventMsg(CEventResult *pCurrEventResult);
	CString FindBinInChange(long *pnNewArr, int size);//判断是否变位

private slots:
	void slot_CheckSelBtnClicked();
	void slot_RemoteMonitorClicked(bool checked);
	void slot_TableWidgetClicked(int row,int col);
	void slot_CheckBoxClicked(bool checked);

};

#endif