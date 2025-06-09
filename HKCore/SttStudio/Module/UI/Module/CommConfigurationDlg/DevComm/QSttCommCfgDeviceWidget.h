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
	//2024-01-20 yuanting  ͨ������ ��������ʹ�� ������Ӹı� ��Լ�͵���ļ� IP���˿ڵ�
	bool SetCurrentCommInfo(CPpSttCommConfig &oCommConfig);
	//2014-01-22 yuanting �Ͽ�����
	bool CloseCurrentConnect();
	BOOL IsRemoteCtrlRunProcedure(const QString &strID);

	virtual BOOL OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj);
	virtual void OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);

	virtual void SaveDatasToLocalDvm(CPpSttIotDeviceClient *pIoTDevice);
	virtual void OnCommCommandMsg(CPpSttIotDeviceClient *pIotDevice, WPARAM wParam,LPARAM lParam);//zhouhj 2024.1.22

	QSttLineEdit *m_pEditZoneNum; //��ֵ��Ediy��
	QPushButton *m_pBtnWriteZone; //��ֵ����༭��
	QPushButton *m_pBtnCmCfg;     //ͨѶ���ð�ť
	QLabel *m_pLabelZoneNum;      //��ֵ��Label
//	QSttCommCfgDeviceWidget *m_pParentDlg;

	SttCDevCommTeleMeasureGrid *m_pDvmTeleMeasureGrid;   //ң���Ӧ�� װ��ͨѶ��
	SttCDevCommParaCommGrid *m_pDvmTeleParaCommGrid;     //����������Ӧ��  װ��ͨѶ��
	BOOL m_bCrtDasetIsTeleMeasure; //�Ƿ���ң��ı�־

	//����������ս���
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
