#pragma once

#include "EthernetCapGlobalDef.h"
// CNetDeviceComboBox

class CNetDeviceComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CNetDeviceComboBox)

public:
	CNetDeviceComboBox();
	virtual ~CNetDeviceComboBox();

	void InitNetDevice(BOOL bOnllyShowDesc=FALSE);
	
private:
	CStNetCardInforList *m_pNetCardList;


protected:
	DECLARE_MESSAGE_MAP()
};


