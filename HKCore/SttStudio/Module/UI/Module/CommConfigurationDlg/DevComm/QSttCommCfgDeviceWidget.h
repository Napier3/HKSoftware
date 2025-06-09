#ifndef QSttCommCfgDeviceWidget_H   
#define QSttCommCfgDeviceWidget_H

#include <QDialog>
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
#include "../../../../../Module/SmartTestInterface/QT/PpSttIotEngineClientWidgetMain.h"
#include "SttDevCommTeleParaCommGrid.h"
#include "SttDevCommTeleMeasureGrid.h"
#include "../../../../../Module/UI/Controls/SttLineEdit.h"
#include "../../../../../Module/UI/Controls/SttDvmEdit.h"


class QSttCommCfgDeviceWidget : public QPpSttIotEngineClientWidgetMain
{
	Q_OBJECT

public:
	QSttCommCfgDeviceWidget(QWidget *parent = 0);
	virtual ~QSttCommCfgDeviceWidget();
	void setInnertState();
	void initUI();
	void SetDialogFont();
	void InitDatas(); 
	void OpenPpSttCommConfigFile();
	void ShowTelemesureTable(CExBaseObject *pSelObj);
	void SetLinuxDeviceIP(CPpSttCommConfig *pCommConfig);
	//2024-01-20 yuanting  通信配置 测试连接使用 多测连接改变 规约和点表文件 IP，端口等
	bool SetCurrentCommInfo(CPpSttCommConfig &oCommConfig);
	//2014-01-22 yuanting 断开连接
	bool CloseCurrentConnect();
	BOOL IsRemoteCtrlRunProcedure(const QString &strID);

	virtual BOOL OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj);
	virtual void OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);

	virtual void SaveDatasToLocalDvm(CPpSttIotDeviceClient *pIoTDevice);
	virtual void OnCommCommandMsg(CPpSttIotDeviceClient *pIotDevice, WPARAM wParam,LPARAM lParam);//zhouhj 2024.1.22

	QSttLineEdit *m_pEditZoneNum; //定值号Ediy框
	QPushButton *m_pBtnWriteZone; //定值区域编辑框
	QPushButton *m_pBtnCmCfg;     //通讯配置按钮
	QLabel *m_pLabelZoneNum;      //定值号Label
//	QSttCommCfgDeviceWidget *m_pParentDlg;

	SttCDevCommTeleMeasureGrid *m_pDvmTeleMeasureGrid;   //遥测对应的 装置通讯表
	SttCDevCommParaCommGrid *m_pDvmTeleParaCommGrid;     //其他参数对应的  装置通讯表
	BOOL m_bCrtDasetIsTeleMeasure; //是否是遥测的标志

	//操作结果接收界面
	QWidget *m_pRunProcedureReceiveDlg;

	virtual void EnableBtns();
	virtual void EnableBtns_Connecting_Closeing();

signals:
	void sig_FinishRunProcedure(QString strID);


public slots:
	void slot_FinishRunProcedure(QString strID);
	void slot_DevCommConfigBtnClicked();
	void slot_DevCommWriteZoneBtnClicked();
};

#endif // QSttCommCfgDeviceWidget_H
