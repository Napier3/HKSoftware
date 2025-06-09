#ifndef QSTTBINRECORDDLG_H
#define QSTTBINRECORDDLG_H

#include <QDialog>
#include "ui_QSttBinRecordDlg.h"
#include "XGlobalDataTypes_QT.h"
#include "../../AdjustTool/SttAdjDevice.h"
#include "../../Engine/SttTestEngineClientData.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceRecord.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceMngr.h"
#include "Grid/QSttBinRecordModuleGrid.h"
#include "Grid/QSttBinRecordChsGrid.h"
//#include "Grid/QSttBinRecordChMapGrid.h"

class QSttBinRecordDlg : public QDialog
{
	Q_OBJECT

public:
	QSttBinRecordDlg(QWidget *parent = 0);
	~QSttBinRecordDlg();

	long m_nSampleRate;
	BOOL m_bLoginRecord;//�Ƿ��¼¼��
	BOOL m_bRecord;//�Ƿ�����¼��
	BOOL m_bAutoSaveComtradeFile;//�Ƿ��Զ�����¼���ļ�
	CString m_strComtradeFoldPath;//���õı���¼���ļ����ļ���·��
	CString m_strPkgZipFile;
	CString m_strPkgUnZipFile;
	CString m_strPCapFile;
	CString m_strComtradeFile;
	CDataGroup m_oBinRecordParas;//������¼���Ĳ���

	void InitUI();                                              //��ʼ������
	void InitDatas(CSttAdjDevice *pSttAdjDevice);				//��ʼ������
	void GenerateParas();										//���ɿ�����¼������
	void InitBinRecord();
	void SendBinRecordCmd();
	void ExistBinRecord();

	void UpdateBinRecordCfgByCapDevices(CCapDeviceRcdCh *pBinaryCh);//��CapDevice��ֵ���µ����ݶ�����
	void UpdateCapDevicesByBinRecordCfg(CCapDeviceRcdCh *pBinaryCh, CCapDeviceRecord *pCapDevBinaryModule);   //��ʼ������
	
	CCapDeviceMngr *m_pCapDeviceAll;							//�·�������¼������
	CCapDeviceRecord* AddCapDeviceBinary(CDataGroup *pModule);	//���ݵ��������������CapDeviceBinary
	CCapDeviceMngr m_oCapDeviceAll;
	CDataGroup m_oBinRecordCfgDataGroup;						//������¼�����ݶ���

	QSttBinRecordModuleGrid *m_pSttBinRecordModuleGrid;        //������¼��������
	QSttBinRecordChsGrid *m_pSttBinRecordChsGrid;			   //������¼�����������

public slots:
	void slot_BeginRecord();                                    //����¼���ۺ���
	void slot_StartMonitor();	                                //������Ӳۺ���
	void slot_Close();                                          //�رղۺ���
	void On_SmpRateChanged();									//���ò����ʲۺ���
	void slot_BtnAutoSaveClicked();								//�Ƿ��Զ�����¼���ļ�
	void slot_Btn_SaveCfgclicked();								//��������
	void slot_Btn_LoadCfgClicked();								//��������
	void slot_BtnBinRecordSet();								//¼�����òۺ���
	void slot_CheckBoxState(int nRow, int nState);
private:
	Ui::QSttBinRecordDlg ui;
};

#endif // QSTTBINRECORDDLG_H
extern QSttBinRecordDlg* g_pBinRecord;