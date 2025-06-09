#pragma once

#include "../../../Module/DataMngr/DataGroup.h"

class CGbWzdItemsNameLib : public CDataGroup
{
private:
	CGbWzdItemsNameLib(void);
	virtual ~CGbWzdItemsNameLib(void);

	CDataGroup *m_pDeviceTypeDef;

	virtual void InitAfterRead();
	void OpenLibFile();

	static long g_nGbWzdItemsNameLibRef;
	static CGbWzdItemsNameLib* g_pGbWzdItemsNameLib;

public:
	static CGbWzdItemsNameLib* Create();
	static void Release();

	static CDataGroup* GetDeviceTypeDef();
	static CDataGroup* FindDeviceTypeLib(const CString &strDeviceTypeID);

};
