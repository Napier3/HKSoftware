#ifndef CSTTDEVICEL336D_2_H
#define CSTTDEVICEL336D_2_H

#include "../Module/Driver466/SttDeviceComm.h"
#include "../L336D/SttDeviceL336D.h"
#include "stdafx.h"

class CSttDeviceL336D_2 : public CSttDeviceL336D
{
public:
	CSttDeviceL336D_2();
	~CSttDeviceL336D_2();
private:
	static long g_nSttDeviceRef;

public:
    static void Create();
    static void Release();
	static CSttDeviceL336D_2 *g_pSttDeviceL336D_2;
};

#endif // CSTTDEVICEL336D_2_H
