#ifndef SttMUTestRecordCbWidget_H
#define SttMUTestRecordCbWidget_H

#include <QDialog>
#include <QFont>
#include "../SttIecCbGrid.h"
#include "../../../../../Module/OSInterface/XWndInterface.h"
#include "../../../../../Module/DataMngr/DataTypes.h"
#include "../SttIecRcdFuncInterface.h"
#include "../../../../../Module/CriticalSection/SynCriticalSection.h"
#include "../../../UI/Module/ScrollCtrl/ScrollComboBox.h"
#include "SttIecRecordCbInterface.h"
#include "../SttIecSmvWaveWidget.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QLabel>
#include <QTabWidget>
#include "FirstCircleWave/SttMUTestFirstCwWidget.h"

class QSttMUTestRecordCbWidget : public QDialog, public CSttIecRecordCbInterface
{
    Q_OBJECT

public:
    explicit QSttMUTestRecordCbWidget(QFont font,long nPkgDetectType,QWidget *parent = 0);
    virtual ~QSttMUTestRecordCbWidget();

//CSttWndAssistInterface
public:
	void InitUI();
	void InitConnects();
	void ShowDelayTimeUI(bool bShow,bool bIsADMUTest = false);//是否显示延时相关界面
	//查找窗口，保留用 找到返回窗口,      否则返回NULL
	//具体对象必须重载此函数，因为如果直接返回窗口指针，然后强制转换为CSttWndAssistInterface，会出错
	virtual CSttWndAssistInterface* ast_FindWnd(const CString &strWndID);

	//功能执行接口
	virtual bool ast_ExecCmd(const CString &strCmdID,const CString &strParas);
	virtual bool ast_ExecCmd_Data(const CString &strCmdID, const CString &strDataID);
	virtual bool ast_ExecCmd_DataFile(const CString &strCmdID, const CString &strDataFile);

	//更新首周波测试特性图
	virtual void UpdateFirstCirclePlot(long nChSetModifyType);

public:
	virtual void UpdateCapDevice(CCapDeviceBase *pCapDevice);
	void SetCapDevice(CCapDeviceBase *pCapDevice);
	virtual void SetSelectedCbs(CExBaseList *pSelectedCbs);
	virtual void Ats_IecRecord(BOOL bIsFromIecfgFile);
    void Ats_IecRecord_Stop();

	virtual void InitIecRecordCb(const CString &strIecFunc);
	void IecRcdFuncUpdate_MUDelayTimes(CCapDeviceBase *pCapDevice);//更新合并单元延时
	

	virtual void BtnBack();//返回按钮功能
//	virtual void Connect_UpdateMUTimeAccurRlt(BOOL bCoonect);
	virtual bool IsTabUI_Mode(){return true;}//返回当前控制块界面显示方式是否为tab显示方式
	virtual void Update_IecRcdTimer();
	
	void SetIecRecordCbFont(); //2022-10-17
	void HideDelayErrUI();//隐藏延时误差等界面显示


	QTabWidget *m_pSttRecordCBTabWidget;
	QVBoxLayout *m_pMainVLayout;
	QHBoxLayout *m_pBottomBtnHLayout;
	QSpacerItem *m_pBottomHSpacer1;
	QPushButton *m_pPrevPageBtn;
	QPushButton *m_pNextPageBtn;
	QSpacerItem *m_pBottomHSpacer2;
	QPushButton *m_pSysSetBtn;
	QSttIecSmvWaveWidget *m_pSttIecSmvWaveWidget;
	QSttMUTestFirstCwWidget *m_pSttFirstCwWidget;

	QLabel *m_pDelayChValue_Label;
	QLineEdit *m_pDelayChValue_Edit;
	QLabel *m_pRealDelayValue_Label;
	QLineEdit *m_pRealDelayValue_Edit;
	QLabel *m_pDelayValueError_Label;
	QLineEdit *m_pDelayValueError_Edit;

	QLabel *m_pSampFreqLabel;
	QLabel *m_pOutputRateLabel;
	QLineEdit *m_pSampFreqEdit; //采样频率
	QLineEdit *m_pOutputRateEdit; //输出速率

public:
	CString m_strIecRcdFuncID;
	CCapDeviceBase *m_pCurrCapDevice;
	
	CSttIecRcdFuncInterface *m_pSttIecRcdFuncInterface;
	
	void RecordCapDevice(CCapDeviceBase *pCapDevice);
	void RecordCapDevice();
	void ExecIecFunc(const CString &strIecfFunc);
	virtual void ExecIecFunc();//执行当前测试功能
	void ExecIecFunc_SetCapAnalysisConfig();//设置报文分析配置
	virtual void UpdateSVDatasetsPowerVector();
	void UpdateSampFreOutputRateData(CCapDeviceBase *pCapDevice);//刷新采样频率/输出速率

private:
	CDataTypes m_oIecRcdDataTypes;
	CDataType *m_pDataType_SttIecRcdMUFuncs;

	QTimer m_oTimerIecRcdUpdate;

	//2022-4-25  lijunqing 功能能之间的互斥处理
	//例如：上页下页等导致绘图元素变化
	//例如：切换选择功能导致与定时器的冲突等
	CAutoCriticSection m_oFuncCriticSection;
	bool m_bInSetCapDevice;

	void OnCurrFuncChanged(long nIndex);

signals:
//	void sig_UpdateMUTimeAccurRlt(CDvmData *pSVDelayData);
	void sig_UpdateSVDatasetsPowerVector();//更新向量、功率等

private slots:
	void slot_currentChangedTabWidget(int nCurrIndex);
	void slot_SysSetBtnClicked();
	void slot_PrevPageBtnClicked();
	void slot_NextPageBtnClicked();

	void slot_Timer_IecRcdUpdate();
	void slot_UpdateSVDatasetsPowerVector();//更新向量、功率等
};

#endif // SttMUTestRecordCbWidget_H
