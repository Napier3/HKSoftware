#include "SttDeviceAT02D.h"
#include "../../Engine/SttServerTestCtrlCntr.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>	//SIGIO
#include<sys/syscall.h>
#include <sys/types.h>
#include <sys/mman.h>

CSttDeviceAT02D *CSttDeviceAT02D::g_pSttDeviceAT02D=NULL;
long CSttDeviceAT02D::g_nSttDeviceRef = 0;


CSttDeviceAT02D::CSttDeviceAT02D()
{

}

void CSttDeviceAT02D::Create()
{
	g_nSttDeviceRef++;

	if (g_nSttDeviceRef == 1)
	{
		g_pSttDeviceAT02D=new CSttDeviceAT02D;
		g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDeviceAT02D;
	}
}

void CSttDeviceAT02D::Release()
{
	g_nSttDeviceRef--;

	if (g_nSttDeviceRef == 0)
	{
		delete g_pSttDeviceAT02D;
		g_pSttDeviceAT02D = NULL;
	}
}

int CSttDeviceAT02D::InitDevice(BOOL bHasAdjFile)
{
	m_nCommfd=open("/dev/SttDriver_PN466",O_RDWR);

	g_theSystemConfig->m_nHasAnalog=0;
	g_theSystemConfig->m_nFiberType=STT_FiberType_2G6M;
	g_theDeviceSystemParameter->m_nModuleCount=1;
	g_theDeviceSystemParameter->m_nModuleCount_D=1;
	g_theDeviceSystemParameter->m_nModuleCount_U=0;
	g_theDeviceSystemParameter->m_nModuleCount_I=0;
	g_theDeviceSystemParameter->m_nModuleCount_S=0;

	g_theDeviceSystemParameter->m_oModules[0].m_oModuleAttr.m_nModuleType = STT_MODULE_TYPE_DIGITAL_2G6M;
	g_theDeviceSystemParameter->m_oModules[0].m_oModuleAttr.m_nModuleIndex=4;
	g_theDeviceSystemParameter->m_oModules_D[0]=&g_theDeviceSystemParameter->m_oModules[0];

	InitDApara(m_nCommfd,TRUE);

	ioctl(m_nCommfd,0x7000003c,1);//1588
	return m_nCommfd;
}

void CSttDeviceAT02D::SetStep6U6IStart()
{
	ioctl(m_nCommfd, 0x110, 1);
	ioctl(m_nCommfd,0xA00,1);
	ioctl(m_nCommfd, 0x100, 1);
	Sleep(50);
	ioctl(m_nCommfd, 0x131, 6);
	ioctl(m_nCommfd, 0x103, 1);
}

void CSttDeviceAT02D::SetStep6U6IStop()
{
	ioctl(m_nCommfd,0xA00,0);
	ioctl(m_nCommfd, 0x103, 0);
	ioctl(m_nCommfd, 0x131, 0);
	ioctl(m_nCommfd, 0x100, 0);
	ioctl(m_nCommfd, 0x110, 0);
}
