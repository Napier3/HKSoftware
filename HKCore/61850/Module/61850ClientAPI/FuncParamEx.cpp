#include "StdAfx.h"
#include "FuncParamEx.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CFuncParam* CFuncParams::AddFuncPara(ST_INT nDeviceIndex, ST_INT nLDIndex, const CString &strJournalName
						, ST_INT bStart, ST_INT nStartType, CTime &tmStart, long long int nStartEntry
						, ST_INT bEnd, ST_INT nEndType, CTime &tmEnd, ST_INT nEntryNum,   //zhow Ð´ÈÕÖ¾ÓÃ
						ST_INT nFuncID, ST_INT nDsIndex, /*HWND hWnd, */UINT nMsg)
{
	CFuncParam *pNew = new CFuncParam();
	pNew->set_DevIndex(nDeviceIndex);
	pNew->set_LDvIndex(nLDIndex);

	MMS_BTOD btod;
	convert_timet_to_btod(tmStart, btod);
	pNew->set_start_time(btod);
	convert_timet_to_btod(tmEnd, btod);
	pNew->set_end_time(btod);

	pNew->set_range_start_pres(bStart);
	pNew->set_start_tag(nStartType);
	pNew->set_start_entry(nStartEntry);

	pNew->set_range_stop_pres(bEnd);
	pNew->set_stop_tag(nEndType);
	pNew->set_num_of_entries(nEntryNum);

	pNew->set_vmd_spec(strJournalName);
	pNew->set_FuncID(FuncID_ReadJournal);

//	pNew->set_hNotifyWnd(hWnd);
	pNew->set_DSID(nDsIndex);
	pNew->set_FuncID(nFuncID);
	AddTail(pNew);
	return pNew;
}

//////////////////////////////////////////////////////////////////////////
//
void CFuncParamEx::SetTitle(const CString &strTitle)
{
	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->SetTitle(strTitle);
	}
}

void CFuncParamEx::SetMaxRange(long nMaxRange)
{
	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->SetMaxRange(nMaxRange);
	}
}

void CFuncParamEx::ResetProcess()
{
	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->ResetProcess();
	}
}

void CFuncParamEx::StepIt()
{
	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->StepIt();
	}
}

void CFuncParamEx::ShowMsg(const CString &strMsg)
{
	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->ShowMsg(strMsg);
	}
}

void CFuncParamEx::StartTimer(long nTimerLong)
{
	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->StartTimer(nTimerLong);
	}
}

void CFuncParamEx::Finish(DWORD dwParam)
{
	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->Finish(dwParam);
	}
}

void CFuncParamEx::StepPos(long nPos)
{
	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->StepPos(nPos);
	}
}

void CFuncParamEx::Exit()
{
	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->Exit();
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL convert_timet_to_btod(CTime &tmStart, MMS_BTOD &btod)
{
	MMS_BTIME6 btime6;
	btod.form = MMS_BTOD6;

	time_t tm;
	tm = tmStart.GetTime();

	asn1_convert_timet_to_btime6(tm, &btime6);
	btod.day = btime6.day;
	btod.ms  = btime6.ms;

	return TRUE;
}
