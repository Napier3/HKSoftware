#pragma once

#include "CapCycleMemBuffer.h"
#include "CapSmFileDB\SmFileDBQueryDef.h"
#include "CapSmFileDB\CapSmDb.h"

#define ID_EPCAP_DATA_LISTCTRL   31358

// CEpCapDatasListCtrlEx

class CEpCapDatasListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CEpCapDatasListCtrlEx)

public:
	CEpCapDatasListCtrlEx();
	virtual ~CEpCapDatasListCtrlEx();
	BOOL CreateWatch(CRect rc, CWnd *pParent);
	void ShowResults(CEpDeviceDatas *pDeviceDatas, long nProtocol);
	void AddResults(CEpDeviceDatas *pDeviceDatas, long nProtocol);

private:
	void ShowResult(CEpY4Data *pDeviceData, long nIndex, long nDataType, long nProtocol);
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


