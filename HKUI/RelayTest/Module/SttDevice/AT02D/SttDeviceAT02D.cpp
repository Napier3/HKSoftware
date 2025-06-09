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
	g_nNeedReportDevExcept = 0;
	m_nCommfd=open("/dev/SttDriver_PN466",O_RDWR);
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	g_nStateCount = read(m_nCommfd,NULL,0x201);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	g_theDeviceSystemParameter->m_oDeviceAttrs.m_nStateCount = g_nStateCount;

	g_theSystemConfig->m_nHasAnalog=0;
	g_theSystemConfig->m_nFiberType=STT_FiberType_2G6M;
	g_theDeviceSystemParameter->m_nModuleCount=1;
	g_theDeviceSystemParameter->m_nModuleCount_D=1;
	g_theDeviceSystemParameter->m_nModuleCount_U=0;
	g_theDeviceSystemParameter->m_nModuleCount_I=0;
	g_theDeviceSystemParameter->m_nModuleCount_S=0;

	g_theDeviceSystemParameter->m_oModules[0].m_oModuleAttr.m_nModuleType = STT_MODULE_TYPE_DIGITAL_2G6M;
	g_theDeviceSystemParameter->m_oModules[0].m_oModuleAttr.m_nModuleIndex = 4;
	g_theDeviceSystemParameter->m_oModules[0].m_oModuleAttr.m_nFiberPortNum_LC = 8;
	g_theDeviceSystemParameter->m_oModules[0].m_oModuleAttr.m_nFiberPortNum_STRecv = 4;
	g_theDeviceSystemParameter->m_oModules[0].m_oModuleAttr.m_nFiberPortNum_STSend = 2;
	g_theDeviceSystemParameter->m_oModules_D[0]=&g_theDeviceSystemParameter->m_oModules[0];

	InitBuff();
	m_pMMapBuf = (Drv_MMapBuf *)mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, m_nCommfd, 0);
	qDebug() << "Driver Mmap = " << m_pMMapBuf;
	InitDApara(m_nCommfd,TRUE);

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(m_nCommfd,0x7000003c,1);//1588
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	return m_nCommfd;
}

BOOL CSttDeviceAT02D::OnTimer(BOOL bExec)
{
	m_nDeviceOnTimerCount++;

	if(m_nDeviceOnTimerCount < 20)
	{
		return FALSE;
	}

	m_nDeviceOnTimerCount = 0;

	stt_init_stt_device_status();
#ifdef _PSX_QT_LINUX_
	memset(&m_oSysUtc, 0, sizeof(Drv_SysUtc));
	GetUtcInfo(&m_oSysUtc);

	if(m_oSysUtc.tmFlag != 0)
	{
		g_theSttDeviceStatus->m_nSync = m_oSysUtc.tmFlag;
	}

	g_theSttDeviceStatus->m_nUtc_s = m_oSysUtc.tm_h;
	g_theSttDeviceStatus->m_nUtc_ns = m_oSysUtc.tm_l;
	g_theSttDeviceStatus->m_nUser_s = g_theSttDeviceStatus->m_nUtc_s
									  + g_theSttDeviceStatus->m_nTimeZone * 3600;

	memset(&m_oSysInfo, 0, sizeof(Drv_SysInfo));
	GetModuleInfo(&m_oSysInfo);
	long nModulePos;
	for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_D; i++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[i];

		if(pModule == NULL)
		{
			continue;
		}

		nModulePos = pModule->m_oModuleAttr.m_nModuleIndex;
		AnalysisLightPower(m_oSysInfo.stBack[nModulePos - 1], nModulePos);
	}
#endif

	return TRUE;
}
