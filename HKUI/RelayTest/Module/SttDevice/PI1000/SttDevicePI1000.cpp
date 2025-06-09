#include "SttDevicePI1000.h"

CSttDevicePI1000 *CSttDevicePI1000::g_pSttDevicePI1000=NULL;
long CSttDevicePI1000::g_nSttDeviceRef = 0;

CSttDevicePI1000::CSttDevicePI1000()
{

}

CSttDevicePI1000::~CSttDevicePI1000()
{
	FreeAsyncManu();
	FreeAsyncState();
}

void CSttDevicePI1000::Create()
{
	g_nSttDeviceRef++;

	if (g_nSttDeviceRef == 1)
	{
		g_pSttDevicePI1000=new CSttDevicePI1000;
		g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDevicePI1000;
	}
}

void CSttDevicePI1000::Release()
{
	g_nSttDeviceRef--;

	if (g_nSttDeviceRef == 0)
	{
		delete g_pSttDevicePI1000;
		g_pSttDevicePI1000 = NULL;
	}
}

int CSttDevicePI1000::InitDevice(BOOL bHasAdjFile)
{
	m_nCommfd=open("/dev/SttDriver_Pi1000",O_RDWR);
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	g_nStateCount = read(m_nCommfd,NULL,0x201);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	g_theDeviceSystemParameter->m_oDeviceAttrs.m_nStateCount = g_nStateCount;
	InitBuff();
	m_pMMapBuf = (Drv_MMapBuf *)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, m_nCommfd, 0);
#ifdef _PSX_QT_LINUX_
	qDebug()<<"Driver Mmap = "<<m_pMMapBuf;
#endif

	InitDApara(m_nCommfd,bHasAdjFile);
	InitAsyncManu();
	InitAsyncState();

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

void CSttDevicePI1000::SetSystemLocalTime(CString strTime_t)
{
	if(m_nSetSysTmCnt > 0)
		return;

	unsigned int nTime_t = strTime_t.toUInt();
	short nYear,nMon,nDay,nHour,nMin,nSec;
	TransTimer_t(nTime_t,nYear,nMon,nDay,nHour,nMin,nSec);

	int nSize = 0;
	int nFlag = -1;
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	Drv_SysUtc oSysUtc;
	nSize = read(m_nCommfd, (char *)&oSysUtc, 0x205);
	nFlag = oSysUtc.tmFlag;
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	if(nSize == sizeof(Drv_SysUtc))
	{
		if(nFlag == 0)
		{
			setBCodeTime(nYear, nMon, nDay, nHour, nMin, nSec);//传入的是0时区时间
			m_nSetSysTmCnt++;
		}
	}
}

void CSttDevicePI1000::GetVoltCurRtData()
{
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
	if(pSttTestBase == NULL)
		return;

    CSttDeviceComm::GetRtData();
}
