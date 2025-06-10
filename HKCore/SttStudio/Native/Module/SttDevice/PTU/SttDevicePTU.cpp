#include "SttDevicePTU.h"
#include "../../Engine/SttServerTestCtrlCntr.h"
#include "../../SttTest/Common/SttAdjust_ModuleOutput.h"
#include "../Module/PowerCtrl/SttPowerCtrlCom.h"


CSttDevicePTU *CSttDevicePTU::g_pSttDevicePTU=NULL;
long CSttDevicePTU::g_nSttDeviceRef = 0;

CSttDevicePTU::CSttDevicePTU()
{

}

void CSttDevicePTU::Create()
{
	g_nSttDeviceRef++;

	if (g_nSttDeviceRef == 1)
	{
		g_pSttDevicePTU=new CSttDevicePTU;
		g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDevicePTU;
	}
}

void CSttDevicePTU::Release()
{
	g_nSttDeviceRef--;

	if (g_nSttDeviceRef == 0)
	{
		delete g_pSttDevicePTU;
		g_pSttDevicePTU = NULL;
	}
}

int CSttDevicePTU::InitDevice(BOOL bHasAdjFile)
{
	m_nCommfd=open("/dev/SttDriver_PTU",O_RDWR);
	//	ioctl(m_nCommfd,0x114,0xff0000);//含小信号档位
	//	ioctl(m_nCommfd,0x104,4);//采集档位固定100
	ioctl(m_nCommfd,0x105,0x80);//电压电流档位

	g_nmaplen = 0x70005074 - 0x70004010;
	g_start = (unsigned int *)mmap(NULL, g_nmaplen, PROT_WRITE, MAP_SHARED, m_nCommfd, 0);

	InitDApara(m_nCommfd);

	CSttPowerCtrlBase *pCSttPowerCtrlBase=NULL;
	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		pCSttPowerCtrlBase=g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_oModuleAttr.m_pPowerCtrlBase;
		if(pCSttPowerCtrlBase==NULL)
		{
			g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_oModuleAttr.m_pPowerCtrlBase=(CSttPowerCtrlBase *)(new CSttPowerCtrlV264(FALSE));
		}
	}

	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		pCSttPowerCtrlBase=g_theDeviceSystemParameter->m_oModules_I[nIndex]->m_oModuleAttr.m_pPowerCtrlBase;
		if(pCSttPowerCtrlBase==NULL)
		{
			g_theDeviceSystemParameter->m_oModules_I[nIndex]->m_oModuleAttr.m_pPowerCtrlBase=(CSttPowerCtrlBase *)(new CSttPowerCtrlC20(FALSE));
		}
	}

	return m_nCommfd;
}
