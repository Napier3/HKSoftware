#pragma once
#include <QProgressDialog>
#include "../../../Module/OSInterface/OSInterface.h"
#include "../../../Module/BaseClass/ThreadProgressInterface.h"

#define SCDFILE_RW_TIME     0X00002005
#define SCDFILE_RW_PROGCTRL     0X00002006



class CScdFileRWDlg : public QProgressDialog, public CThreadProgressInterface
{
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
	

//	virtual BOOL OnInitDialog();	
};