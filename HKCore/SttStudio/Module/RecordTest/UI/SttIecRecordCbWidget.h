#ifndef SttIecRecordCbWidget_H
#define SttIecRecordCbWidget_H

#include <QDialog>
#include <QFont>
#include "SttIecCbGrid.h"
#include "../../../../Module/OSInterface/XWndInterface.h"
#include "../../../../Module/DataMngr/DataTypes.h"
#include "SttIecRcdFuncInterface.h"
#include "../../../../Module/CriticalSection/SynCriticalSection.h"
#include "../../UI/Module/ScrollCtrl/ScrollComboBox.h"
#include "MUTest/SttIecRecordCbInterface.h"
#include "SttIecRecordWriteFileWidget.h"
#include <QLabel>
#include <QLineEdit>
#include "SttIecSmvWidget_Harm.h"

namespace Ui {
class QSttIecRecordCbWidget;
}
 
class QSttIecRecordCbWidget : public QDialog, public CSttIecRecordCbInterface
{
    Q_OBJECT

public:
    explicit QSttIecRecordCbWidget(QFont font,QWidget *parent = 0);
    virtual ~QSttIecRecordCbWidget();

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
//	virtual void UpdateCapDevice(CCapDeviceBase *pCapDevice);
	void SetCapDevice(CCapDeviceBase *pCapDevice);
	virtual void SetSelectedCbs(CExBaseList *pSelectedCbs);
	virtual void Ats_IecRecord(BOOL bIsFromIecfgFile);
    void Ats_IecRecord_Stop();

	virtual void InitIecRecordCb(const CString &strIecFunc);
	

	virtual void BtnBack();//���ذ�ť����
//	virtual void Connect_UpdateMUTimeAccurRlt(BOOL bCoonect);
	virtual void SetEnable_BtnBack(bool bEnable);
	
	void SetIecRecordCbFont(); //2022-10-17
	virtual void UpdateWriteFileTimeAndFileSize(long nTimeMs,long nFileSize);


public:
	CString m_strIecRcdFuncID;
	CCapDeviceBase *m_pCurrCapDevice;
	//zhouhj 2023.10.22 �������
//	CExBaseList *m_pSelectedCbs;
	
	CSttIecRcdFuncInterface *m_pSttIecRcdFuncInterface;
	QSttIecRecordWriteFileWidget *m_pSttRcdWriteFileWidget;//220231020 wxy д�ļ�����
	CSttIecSmvWidget_Harm *m_pSttIecSmvWidget_Harm;
	
	void RecordCapDevice(CCapDeviceBase *pCapDevice);
	void RecordCapDevice();
	void ExecIecFunc(const CString &strIecfFunc);
	virtual void ExecIecFunc();
	void ExecIecFunc_Create();
	virtual void UpdateSVDatasetsPowerVector();
	void UpdateWriteFileCtrls(bool bShow);//20231020 wxy ����д�ļ����ڿؼ�
        void BtnPreNextEnabled(long nType);

private:
	CDataTypes m_oIecRcdDataTypes;
	CDataType *m_pCurrIecRcdFucsDataType;
	CDataType *m_pDataType_SttIecRcdSmvFuncs;
	CDataType *m_pDataType_SttIecRcdGooseFuncs;
	CDataType *m_pDataType_SttIecRcdMUFuncs;
	CDataType *m_pDataType_SttIecRcdFT3Funcs;

	QLabel *m_pWriteFileTime_Label;
	QLabel *m_pWriteFileSize_Label;
	QLineEdit *m_pWriteFileTime_Edit;
	QLineEdit *m_pWriteFileSize_Edit;

	QTimer m_oTimerIecRcdUpdate;

	//2022-4-25  lijunqing ������֮��Ļ��⴦��
	//���磺��ҳ��ҳ�ȵ��»�ͼԪ�ر仯
	//���磺�л�ѡ���ܵ����붨ʱ���ĳ�ͻ��
	CAutoCriticSection m_oFuncCriticSection;
	QScrollComboBox* m_cmbFunc;
	QScrollComboBox* m_cmbCb;
	bool m_bInSetCapDevice;
	QScrollComboBox* m_cmbHarmDisplay; //cl20231016 г����ʾ
	QScrollComboBox* CombHarmDisplayType();

	BOOL InitFuncTypeComboBox(CCapDeviceBase *pCapDevice);
	void OnCurrFuncChanged(long nIndex);

	void HarmFuncType();
	//long m_nHarmDisplayIndex;//г����ʾ�������Indexֵ

public slots:

signals:
//	void sig_UpdateMUTimeAccurRlt(CDvmData *pSVDelayData);
	void sig_UpdateSVDatasetsPowerVector();//�������������ʵ�

private slots:
	void slot_CbCurrentIndexChanged(int index);
	void slot_FuncCurrentIndexChanged(int index);
	void slot_CbHarmDisplayIndexChanged(int index);
	void on_m_btnBack_clicked();
	void on_m_btnSysSet_clicked();
	void slot_Timer_IecRcdUpdate();
	void on_m_btnPrevPage_clicked();
	void on_m_btnNextPage_clicked();

	void on_m_btnAddToSub_clicked();//20230602 zhouhj
	void on_m_btnAddToPub_clicked();

	void slot_UpdateSVDatasetsPowerVector();//�������������ʵ�
//	void slot_ReciveFileSize(long nM, long nK);//����д�ļ�����¼���ļ���С
//	void slot_ReciveRecordTime(int nTime);//����д�ļ�����¼��ʱ��

private:
    Ui::QSttIecRecordCbWidget *ui;
};

#endif // SttIecRecordCbWidget_H
