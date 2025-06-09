#include "SttDeviceL336D_2.h"

CSttDeviceL336D_2 *CSttDeviceL336D_2::g_pSttDeviceL336D_2 = NULL;
long CSttDeviceL336D_2::g_nSttDeviceRef = 0;


CSttDeviceL336D_2::CSttDeviceL336D_2()
{
	m_oBat485Info.bHasBat = TRUE;
}

CSttDeviceL336D_2::~CSttDeviceL336D_2()
{

}

void CSttDeviceL336D_2::Create()
{
	g_nSttDeviceRef++;

	if(g_nSttDeviceRef == 1)
	{
		g_pSttDeviceL336D_2 = new CSttDeviceL336D_2;
		g_pSttDeviceBase = (CSttDeviceBase *)g_pSttDeviceL336D_2;
	}
}

void CSttDeviceL336D_2::Release()
{
	g_nSttDeviceRef--;

	if(g_nSttDeviceRef == 0)
	{
		delete g_pSttDeviceL336D_2;
		g_pSttDeviceL336D_2 = NULL;
	}
}
