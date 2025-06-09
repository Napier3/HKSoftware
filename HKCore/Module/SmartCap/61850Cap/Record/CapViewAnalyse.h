// CapViewAnalyse.h:
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "../../../Record/Draw/ViewAnalyse.h"
#include "CapDeviceChRecordMngr.h"

class CCapViewAnalyse : public CViewAnalyse
{
public:
	CCapViewAnalyse();
	virtual ~CCapViewAnalyse();

	void SetCapDeviceChRecordMngr(CCapDeviceChRecordMngr *p);

protected:
	CCapDeviceChRecordMngr *m_pCapDeviceChRecordMngr;

	//���ݵ�ǰ���鴴����ͼ����
// 	CDrawVariable* CreateVariable(CCapDeviceChRecord *pVariable, long &nCurrentChans, long &nAnalogChanAmount, long &nBinaryChanAmount);
// 	CDrawVariable* CreateAnalogVar(CCapDeviceSmvChRecord* pSingle,long nIndex);
// 	CDrawVariable* CreateBinaryVar(CCapDeviceGooseChRecord* pBinary,long nIndex);

public:
	void ShowAllRecordCh();
	void ShowRecordCh(CCapDeviceChRecord* pRecord);
	void HideRecordCh(CCapDeviceChRecord* pRecord);

protected:
	void InitCapViewDraw();
	void InitDrawVariableShow();
};

