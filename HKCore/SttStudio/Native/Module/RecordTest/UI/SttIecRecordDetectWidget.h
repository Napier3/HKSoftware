#ifndef SttIecRecordDetectWidget_H
#define SttIecRecordDetectWidget_H

#include <QDialog>
#include <QFont>
#include "SttIecCbGrid.h"
#include "XWndInterface.h"
#include "../Module/UI/Controls/SttCheckBox.h"
//2022-12-02  lijunqing  
#include "../../Assist/SttAssistGlobalApi.h"
#include "SttIecRecordWriteFileWidget.h"

//���屨��̽������
#define STT_IEC_DETECT_TYPE_61850                      0
#define STT_IEC_DETECT_TYPE_61850_92                   1
#define STT_IEC_DETECT_TYPE_61850_GS                   2
#define STT_IEC_DETECT_TYPE_60044                      3

namespace Ui {
class QSttIecRecordDetectWidget;
}

class QSttIecRecordDetectWidget : public QDialog, public CXWndInterface, public CExBaseListGridOptrInterface,
	public CSttWndAssistInterface  //2022-12-02 lijunqing ����������صĽӿ�
{
    Q_OBJECT

public:
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

public:
	virtual unsigned int XSetTimer(unsigned int nIDEvent, unsigned int nElapse, void* pFunc);
	virtual BOOL XKillTimer(unsigned int nIDEvent);
	virtual void XPostMessage(unsigned int nMsgID, unsigned long wParam=0, unsigned long  lParam=0);
	BOOL IsCapDeviceMngrDevice(CCapDeviceBase *pCapDeviceBase);//�����ж�ȷ��  zhouhj 2024.4.26

//CSttWndAssistInterface
public:
	//���Ҵ��ڣ������� �ҵ����ش���,      ���򷵻�NULL
	//�������������ش˺�������Ϊ���ֱ�ӷ��ش���ָ�룬Ȼ��ǿ��ת��ΪCSttWndAssistInterface�������
	virtual CSttWndAssistInterface* ast_FindWnd(const CString &strWndID);

	//����ִ�нӿ�
	virtual bool ast_ExecCmd(const CString &strCmdID,const CString &strParas);
	virtual bool ast_ExecCmd_Data(const CString &strCmdID, const CString &strDataID);
	virtual bool ast_ExecCmd_DataFile(const CString &strCmdID, const CString &strDataFile);

public:
    explicit QSttIecRecordDetectWidget(QFont font,QWidget *parent = 0);
    virtual ~QSttIecRecordDetectWidget();
	void SetIecCapWriteFile(bool b);

	void ConnectAll();
	void DisConnectAll();

	CSttIecCbGrid *m_pGridIecCb;
	BOOL m_bViewSmv;
	BOOL m_bViewGoose;
	BOOL m_bViewFT3;
	BOOL m_bIsFromIecfgFile;
	bool m_bIecCapWriteFile;
	bool m_bIsClearCBs;//zhouhj  20220902  ���ӷ�ֹ������ε�������ť
	long m_nIecType; //20240813 suyang ���ӱ���̽��ʱIEC���ͣ����ڴ����ײ�SV--1 GOOSE---2  FT3---3  ȫ��---0

public:
//	void InitSttIecRecord();
//	void FreeeSttIecRecord();
	void UpdateCbGrid();
	void UpdateDetectWidget();//���±�񼰽��水ť
	void StartDetect();//��ʼ̽��
	void ImportIecfg();
	void UpdateIecfg();
	void CloseIecCapDetect();//20220629 zhouhj �رղ��Թ��ܽ���ʱ,����ײ㻹����̽��ģʽ,�ر�̽��ͨ��
	
	void SetIecRecordFont();//2022-10-17

	BOOL AttachDeviceChMapsBySCL(CCapDeviceBase *pCapDeviceBase);//20221218 zhouhj ����SCD,����SCD�ļ��ж�Ӧ��AppID���µ�ǰ���ƿ�����
	//����FT3���ƿ����ͨ��ӳ������
	BOOL AttachDeviceFT3ChMaps(CCapDeviceBase *pCapDeviceBase);
	void ClearAll_StartDetect();//���ȫ��,���¿�ʼ̽��

	//zhouhj 2023.12.4���±���̽�����
	void UpdateDetectType(long nPkgDetectType);

public slots:

signals:
	void sig_AddNewDevice(CCapDeviceBase *pCapDevice);

private slots:
    void on_m_btnDetect_clicked();
	void on_m_btnClear_clicked();
	void on_m_btnBeginRecord_clicked();//�������
    void slot_chkUseSmvClicked();
	void slot_chkUseGooseClicked();
    void slot_chkUseFT3Clicked();
	void on_AddNewDevice(CCapDeviceBase *pCapDevice);

    void on_m_chkSmvFirstIsTime_clicked();
    void on_m_btnDetectStop_clicked();

    void on_m_btnImportIecfg_clicked();

	void slot_ck_WaveRecordStateChanged(int	nIndex);

//	void on_m_chkWaveRecord_clicked(int bState);

private:
    Ui::QSttIecRecordDetectWidget *ui;
	QSttCheckBox *m_chkWaveRecord;//¼��
	QSttIecRecordWriteFileWidget *m_pRecordWriteFileWiget;
	
};

extern QSttIecRecordDetectWidget *g_pSttIecRecordDetectWidget;

#endif // SttIecRecordDetectWidget_H
