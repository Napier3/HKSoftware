#pragma once
#include <QProgressDialog>
#include "../../../Module/OSInterface/OSInterface.h"
#include "../../../Module/BaseClass/ThreadProgressInterface.h"

#define SCDFILE_RW_TIME     0X00002005
#define SCDFILE_RW_PROGCTRL     0X00002006



class CScdFileRWDlg : public QProgressDialog, public CThreadProgressInterface
{
	Q_OBJECT
public:
	CScdFileRWDlg(QWidget* pParent = NULL);   // 标准构造函数
	virtual ~CScdFileRWDlg();
	long m_nTimeCout;
public:
	virtual void SetTitle(const CString &strTitle);
	virtual void SetMaxRange(long nMaxRange);
	virtual void ResetProcess();
	virtual void StepIt();
	virtual void ShowMsg(const CString &strMsg);
	virtual void StartTimer(long nTimerLong);
	virtual void InitThreadProgress(long nMaxRange, long nOneStepCount);
	
	////////////////////////////////////////////////////////////////
	//所有的接口，全部改为信号槽，这样可以跨线程使用。shaolei 2022-12-12
signals:
	void sig_SetTitle(const CString &strTitle);
	void sig_SetMaxRange(long nMaxRange);
	void sig_ResetProcess();
	void sig_StepIt();
	void sig_ShowMsg(const CString &strMsg);
	void sig_StartTimer(long nTimerLong);
	void sig_InitThreadProgress(long nMaxRange, long nOneStepCount);

public slots:
	void slot_SetTitle(const CString &strTitle);
	void slot_SetMaxRange(long nMaxRange);
	void slot_ResetProcess();
	void slot_StepIt();
	void slot_ShowMsg(const CString &strMsg);
	void slot_StartTimer(long nTimerLong);
	void slot_InitThreadProgress(long nMaxRange, long nOneStepCount);	
};