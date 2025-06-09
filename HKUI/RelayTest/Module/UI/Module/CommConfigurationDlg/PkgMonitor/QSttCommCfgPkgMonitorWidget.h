#ifndef  QSttCommCfgPkgMonitorWIDGET_H
#define  QSttCommCfgPkgMonitorWIDGET_H
 
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
#include <QTimerEvent>
#include <QLineEdit>
#include "SttCommCfgPkgMonitorLeftGrid.h"
#include "SttCommCfgPkgMonitorRightGrid.h"

#include "../../../../SmartTestInterface/QT/PpSttIotEngineClientWidgetMain.h"
#include "../DevComm/QSttCommCfgDeviceWidget.h"

class QSttCommCfgPkgMonitorWidget : public QWidget
{
	Q_OBJECT

public:
	QSttCommCfgPkgMonitorWidget(QWidget *parent = 0);
	~QSttCommCfgPkgMonitorWidget();

	//初始化界面和数据
	void initUI();
	void ReleaseUI();
	void InitDatas();
	//释放当前创建的 DeviceWidget
	void DeleteCommCfgDeviceWidget();
	void SetPkgMonitorFont(); //设置字体

	public slots:
		void slot_StartMonitorClicked(); //开始监听槽函数
		void slot_StopMonitorClicked();  //终止监听槽函数
		void slot_ClearListrClicked();   //清空列表槽函数
		void slot_ExportClicked();    //导出槽函数
// 		void slot_CancelClicked();
// 		void slot_OKClicked();
		//定时刷新
		void slot_TimerOut();
		//选择列表项 左侧显示具体的解析信息
		void slot_TabSelectRowChange(QTableWidgetItem *item);

private:
	QSttCommCfgDeviceWidget*  m_pCommCfgDeviceWidget;		//连接界面
	SttCCommCfgPkgMonitorLeftGrid* m_pLeftPkgMonitorGrid;   	  //报文监听左侧表格
	SttCCommCfgPkgMonitorRightGrid* m_pRightPkgMonitorGrid;	  //报文监听右侧表格
	QPushButton *m_pStartMonitor_PushButton;	  //开始监听
	QPushButton *m_pStopMonitor_PushButton;	      //终止监听
	QPushButton *m_pClearList_PushButton;	      //清空列表
	QPushButton *m_pExportMonitor_PushButton;	  //导出
	//QPushButton *m_pOK_PushButton;

	QTimer * m_pRecvPkgTimer;                      //接收报文的定时器
	BOOL	 m_bIsClearPkg;									//是否在清理报文列表
	BOOL     m_bIsCreateWidget;								//接受报文的界面 是否是当前创建的
	//QList<QByteArray> m_oPkgsRecvList;					//报文数据存储

};

#endif 
