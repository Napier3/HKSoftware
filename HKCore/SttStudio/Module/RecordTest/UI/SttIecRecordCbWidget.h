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
	//查找窗口，保留用 找到返回窗口,      否则返回NULL
	//具体对象必须重载此函数，因为如果直接返回窗口指针，然后强制转换为CSttWndAssistInterface，会出错
	virtual CSttWndAssistInterface* ast_FindWnd(const CString &strWndID);

	//功能执行接口
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
	

	virtual void BtnBack();//返回按钮功能
//	virtual void Connect_UpdateMUTimeAccurRlt(BOOL bCoonect);
	virtual void SetEnable_BtnBack(bool bEnable);
	
	void SetIecRecordCbFont(); //2022-10-17
	virtual void UpdateWriteFileTimeAndFileSize(long nTimeMs,long nFileSize);


public:
	CString m_strIecRcdFuncID;
	CCapDeviceBase *m_pCurrCapDevice;
	//zhouhj 2023.10.22 放入基类
//	CExBaseList *m_pSelectedCbs;
	
	CSttIecRcdFuncInterface *m_pSttIecRcdFuncInterface;
	QSttIecRecordWriteFileWidget *m_pSttRcdWriteFileWidget;//220231020 wxy 写文件窗口
	CSttIecSmvWidget_Harm *m_pSttIecSmvWidget_Harm;
	
	void RecordCapDevice(CCapDeviceBase *pCapDevice);
	void RecordCapDevice();
	void ExecIecFunc(const CString &strIecfFunc);
	virtual void ExecIecFunc();
	void ExecIecFunc_Create();
	virtual void UpdateSVDatasetsPowerVector();
	void UpdateWriteFileCtrls(bool bShow);//20231020 wxy 设置写文件窗口控件
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

	//2022-4-25  lijunqing 功能能之间的互斥处理
	//例如：上页下页等导致绘图元素变化
	//例如：切换选择功能导致与定时器的冲突等
	CAutoCriticSection m_oFuncCriticSection;
	QScrollComboBox* m_cmbFunc;
	QScrollComboBox* m_cmbCb;
	bool m_bInSetCapDevice;
	QScrollComboBox* m_cmbHarmDisplay; //cl20231016 谐波显示
	QScrollComboBox* CombHarmDisplayType();

	BOOL InitFuncTypeComboBox(CCapDeviceBase *pCapDevice);
	void OnCurrFuncChanged(long nIndex);

	void HarmFuncType();
	//long m_nHarmDisplayIndex;//谐波显示下拉框的Index值

public slots:

signals:
//	void sig_UpdateMUTimeAccurRlt(CDvmData *pSVDelayData);
	void sig_UpdateSVDatasetsPowerVector();//更新向量、功率等

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

	void slot_UpdateSVDatasetsPowerVector();//更新向量、功率等
//	void slot_ReciveFileSize(long nM, long nK);//接受写文件窗口录波文件大小
//	void slot_ReciveRecordTime(int nTime);//接受写文件窗口录波时间

private:
    Ui::QSttIecRecordCbWidget *ui;
};

#endif // SttIecRecordCbWidget_H
