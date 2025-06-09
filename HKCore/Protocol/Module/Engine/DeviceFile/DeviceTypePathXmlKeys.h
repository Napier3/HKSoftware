#pragma once

#include "../../../../Module/BaseClass/ExBaseList.h"

class CDeviceTypePathXmlKeys : public CXmlRWKeys
{
public:
	CDeviceTypePathXmlKeys(void);
	virtual ~CDeviceTypePathXmlKeys(void);

public:
	static CDeviceTypePathXmlKeys* g_pXmlRWKeys;
	static CDeviceTypePathXmlKeys* Create();
	static void Release();
	static long g_nDeviceTypathRef;

	BSTR m_strRoot;
	BSTR m_strDevice;
	BSTR m_strPath;
	BSTR m_strName;
	BSTR m_strDeviceModelFile;
	BSTR m_strTemplateFile;

};
