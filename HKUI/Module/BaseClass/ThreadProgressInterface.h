
#pragma once

#include "../OSInterface/OSInterface.h"

class CThreadProgressInterface
{
protected:
	long m_nMaxRange;
	long m_nOneStepCount;
	long m_nOneStepIndex;


public:
	CThreadProgressInterface();
	virtual ~CThreadProgressInterface();
	virtual void InitThreadProgress(long nMaxRange, long nOneStepCount);
	virtual void Step();
	
//重载实现的接口部分
public:
        virtual void SetTitle(const CString &strTitle)
        {
#ifdef _PSX_IDE_QT_
        (void)strTitle;
#endif
        };
	virtual void SetMaxRange(long nMaxRange) = 0;
	virtual void ResetProcess() = 0;
	virtual void StepIt() = 0;
	virtual void ShowMsg(const CString &strMsg) = 0;
	virtual void StartTimer(long nTimerLong) = 0;
        virtual void SetPos(long nPos)
        {
#ifdef _PSX_IDE_QT_
        (void)nPos;
#endif
        }	//2024-3-26  lijunqing

        virtual void Finish(DWORD dwParam=0)
        {
#ifdef _PSX_IDE_QT_
        (void)dwParam;
#endif
        }

        virtual void StepPos(long nPos)
        {
#ifdef _PSX_IDE_QT_
        (void)nPos;
#endif
        };

	virtual void Exit(){}

};
