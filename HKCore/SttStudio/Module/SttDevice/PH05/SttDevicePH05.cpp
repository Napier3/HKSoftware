#include "SttDevicePH05.h"

CSttDevicePH05 *CSttDevicePH05::g_pSttDevicePH05 = NULL;
long CSttDevicePH05::g_nSttDeviceRef = 0;

CSttDevicePH05::CSttDevicePH05()
{

}

CSttDevicePH05::~CSttDevicePH05()
{

}

void CSttDevicePH05::Create()
{
	g_nSttDeviceRef++;

	if (g_nSttDeviceRef == 1)
	{
        g_pSttDevicePH05 = new CSttDevicePH05;
        g_pSttDeviceBase = (CSttDeviceBase*)g_pSttDevicePH05;
	}
}

void CSttDevicePH05::Release()
{
	g_nSttDeviceRef--;

	if (g_nSttDeviceRef == 0)
	{
        delete g_pSttDevicePH05;
        g_pSttDevicePH05 = NULL;
	}
}

int CSttDevicePH05::InitDevice(BOOL bHasAdjFile)
{
	m_nCommfd=open("/dev/SttDriver_Pi1000",O_RDWR);
	m_pDegressMsg = (Drv_DegressMsg *)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, m_nCommfd, 0);
#ifdef _PSX_QT_LINUX_
	qDebug()<<"Driver Mmap = "<<m_pDegressMsg;
#endif

	InitDApara(m_nCommfd,bHasAdjFile);

	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_U[nIndex];
		if(pModule==NULL)
			continue;

		CSttPowerCtrlBase *pCSttPowerCtrlBase=pModule->m_oModuleAttr.m_pPowerCtrlBase;
		if(pCSttPowerCtrlBase==NULL)
		{
			pModule->m_oModuleAttr.m_pPowerCtrlBase=(CSttPowerCtrlBase*)(new CSttPowerCtrlV300_PI);
		}
	}
	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nIndex];
		if(pModule==NULL)
			continue;

		CSttPowerCtrlBase *pCSttPowerCtrlBase=pModule->m_oModuleAttr.m_pPowerCtrlBase;
		if(pCSttPowerCtrlBase==NULL)
			pModule->m_oModuleAttr.m_pPowerCtrlBase=(CSttPowerCtrlBase*)(new CSttPowerCtrlC20);
	}

	return m_nCommfd;
}

void CSttDevicePH05::AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack,int nModulePos,int nModuleType)
{
    CSttDeviceBase::AnalysisDrvSysInfo(oDrv_FeedBack,nModulePos,nModuleType);
	//466插件暂不考虑以下指标
	int nItemIndex=0;
	for(unsigned int i=0;i<g_theSttDeviceStatus->m_nAnalogCount;i++)
	{
		if(g_theSttDeviceStatus->m_oModule[i].m_nModulePos==nModulePos)
		{
			nItemIndex=i;
			break;
		}
	}
	STT_MODULE_STATUS &oModuleStatus=g_theSttDeviceStatus->m_oModule[nItemIndex];

	oModuleStatus.m_nIsVoltHot = 0;//电压过热
	oModuleStatus.m_nIsDCHot = 0;//直流过热
	oModuleStatus.m_nIsVoltWarining = 0;//电压告警
	oModuleStatus.m_nIsMissWarining = 0;//失地告警
}

