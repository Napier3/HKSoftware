#include "SttDriverOper.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>	//SIGIO
#include<sys/syscall.h>
#include <sys/types.h>
#include <sys/mman.h>

CSttDriverOper *CSttDriverOper::g_pSttDriverOper=NULL;
long CSttDriverOper::g_nSttDriverOperRef = 0;

//global variable definition: start with "g_"
int g_fd;
unsigned int *g_start;
int g_nmaplen;

int m_nAnalogSync = 0;
unsigned long m_nModuleSet = 0;


CSttDriverOper::CSttDriverOper(QObject *parent) : QObject(parent)
{

}

void CSttDriverOper::Create(int nfd)
{
	g_nSttDriverOperRef++;

	if (g_nSttDriverOperRef == 1)
	{
		g_pSttDriverOper=new CSttDriverOper;
		g_pSttDriverOper->InitDriver(nfd);
	}
}

void CSttDriverOper::Release()
{
	g_nSttDriverOperRef--;

	if (g_nSttDriverOperRef == 0)
	{
		delete g_pSttDriverOper;
		g_pSttDriverOper = NULL;
	}
}

void CSttDriverOper::InitDriver(int nfd)
{
	g_fd=nfd;
    g_nmaplen = 7782528;
    g_start = (unsigned int *)mmap(NULL, g_nmaplen, PROT_WRITE, MAP_SHARED, g_fd, 0);
	m_nAnalogSync=0;
	m_nModuleSet=1;
}

void CSttDriverOper::StartIecDetect()
{
	ioctl(g_fd, 0x130, 1);
}

void CSttDriverOper::StopIecDetect()
{
	ioctl(g_fd, 0x130, 0);
}

int CSttDriverOper::readIecDetectResult(char* pBuff)
{
	return read(g_fd,pBuff,0x260);
}

void CSttDriverOper::StartRecord()
{
	ioctl(g_fd, 0x131, 5);
}

void CSttDriverOper::StopRecord()
{
	ioctl(g_fd, 0x131, 0);
}

void CSttDriverOper::Start(int nValue)
{
	//nValue  ÷∂Ø1£¨◊¥Ã¨–Ú¡–2£¨≤Ó∂Ø3
	ioctl(g_fd, 0x103, nValue);
}

void CSttDriverOper::Stop()
{
	ioctl(g_fd, 0x103, 0);
}

long CSttDriverOper::getTemprature()
{
	unsigned int *buffer;
	unsigned int nRet = 0;
	buffer = (unsigned int *)malloc(sizeof(unsigned int));
	nRet = *buffer;
	free(buffer);
	return 0;
}

void CSttDriverOper::WriteData(char* pBuff,unsigned long nLen)
{
#ifdef _PSX_QT_LINUX_
	write(g_fd,pBuff,nLen);
#endif
}
void* CSttDriverOper::getMmapBuffer()
{
    return g_start;
}
bool CSttDriverOper::getLtReplayBufferAFlag()
{
    return ioctl(g_fd, 0x504, 0)&0x02;
}
bool CSttDriverOper::getLtReplayBufferBFlag()
{
    return ioctl(g_fd, 0x504, 0)&0x04;
}
void CSttDriverOper::setLtReplayBufferAFlag()
{
    unsigned int temp = ioctl(g_fd, 0x504, 0);
    temp |= 0x02;
    ioctl(g_fd, 0x134, temp);

}
void CSttDriverOper::setLtReplayBufferBFlag()
{
    unsigned int temp = ioctl(g_fd, 0x504, 0);
    temp |= 0x04;
    ioctl(g_fd, 0x134, temp);
}

void CSttDriverOper::setLtReplayBufferLoopFlag()
{
    unsigned int temp = ioctl(g_fd, 0x504, 0);
    temp |= 0x01;
    ioctl(g_fd, 0x134, temp);
}

void CSttDriverOper::WriteRegister(unsigned long nAddr,unsigned long data)
{
	unsigned int *buffer;
	buffer = (unsigned int *)malloc(sizeof(unsigned int));
	buffer[0] = data;

	ioctl(g_fd,nAddr,data);
	free(buffer);
}

void CSttDriverOper::WriteAnalogSync()
{
	if(m_nAnalogSync == 0){
		m_nAnalogSync = 1;
	}
	else{
		m_nAnalogSync = 0;
	}
	unsigned int *buffer;
	buffer = (unsigned int *)malloc(sizeof(unsigned long));
	buffer[0] = m_nAnalogSync;

	ioctl(g_fd,0x70000018,m_nAnalogSync);
	free(buffer);
}

void CSttDriverOper::WriteFPGAData(unsigned long nAddr,unsigned long data)
{
	ioctl(g_fd,nAddr,data);
}

void CSttDriverOper::WriteFPGAAnalog(char* buff,unsigned long nLen)
{
	unsigned long* p = (unsigned long*)buff;
	memcpy(g_start+4, buff, nLen);
	for(int i=0;i<16;i++)
	{
		ioctl(g_fd,0x70004010+i*4,p[i]);
	}
	WriteAnalogSync();
}

int CSttDriverOper::IoCtrl(unsigned long ncmd,unsigned long nValue)
{
	return ioctl(g_fd,ncmd,nValue);
}

int CSttDriverOper::readRampResult(char* pBuff)
{
#ifdef _PSX_QT_LINUX_
	return read(g_fd,pBuff,0x207/*sizeof(structRampResult)*100*/);
#else
	return 0;
#endif
}

int CSttDriverOper::readStateResult(char* pBuff)
{
#ifdef _PSX_QT_LINUX_
	return read(g_fd,pBuff,0x203/*sizeof(structResultItem)*/);
#else
	return 0;
#endif
}

int CSttDriverOper::readRecordResult(char* pBuff)
{
#ifdef _PSX_QT_LINUX_
	return read(g_fd,pBuff,0x261);
#else
	return 0;
#endif
}

int CSttDriverOper::readDeviceInnerPara(char* pBuff)
{
#ifdef _PSX_QT_LINUX_
	return read(g_fd,pBuff,0x204);
#else
	return 0;
#endif
}

int CSttDriverOper::readDisBinStatePara()
{
	return ioctl(g_fd,0x208,0);
}

int CSttDriverOper::readDisResult(char* pBuff)
{
#ifdef _PSX_QT_LINUX_
	return read(g_fd,pBuff,0x207/*sizeof(distripResult)*/);
#else
	return 0;
#endif
}

void CSttDriverOper::SetisStopIfBiChanged(int nValue)
{
	ioctl(g_fd,0x104,nValue);
}

void CSttDriverOper::SetStopDelayTime(int nTime)
{
	ioctl(g_fd,0x105,nTime);
}

void CSttDriverOper::SetBinaryOut(int nState)
{
	ioctl(g_fd,0x107,nState);
}

void CSttDriverOper::SetBinaryOutTurnOnVaule(int nState)
{
	ioctl(g_fd,0x137,nState);
}

void CSttDriverOper::SetBinaryInLogic(int nLogic)
{
	ioctl(g_fd,0x10D,nLogic);
}

void CSttDriverOper::setManualAcAnalogPara(char* pBuff,int nLen)
{
	ioctl(g_fd,0x300,0);
#ifdef _PSX_QT_LINUX_
	write(g_fd,pBuff,nLen);
#endif

}

void CSttDriverOper::setManualBISetting(char* pBuff,int nLen)
{
	ioctl(g_fd,0x302,0);
#ifdef _PSX_QT_LINUX_
	write(g_fd,pBuff,nLen);
#endif
}

void CSttDriverOper::setStatePara(char* pBuff,int nLen)
{
	ioctl(g_fd,0x301,0);
#ifdef _PSX_QT_LINUX_
	write(g_fd,pBuff,nLen);
#endif
}

void CSttDriverOper::setStatePara(char* pBuff,int nLen,int nType)
{
#ifdef _PSX_QT_LINUX_
	ioctl(g_fd,0x301,nType);
	write(g_fd,pBuff,nLen);
#endif
}

void CSttDriverOper::SetModuleInfo(char* pBuff,int nLen)
{
#ifdef _PSX_QT_LINUX_
	ioctl(g_fd, 0x331, 0);
	write(g_fd, pBuff, nLen);
#endif
}

void CSttDriverOper::setDiffAcAnalogPara(char* pBuff,int nLen,int Statue)
{
	ioctl(g_fd,0x303,Statue);
#ifdef _PSX_QT_LINUX_
	write(g_fd,pBuff,nLen);
#endif
}

void CSttDriverOper::setSearchAcAnalogPara(char* pBuff,int nLen,int Statue)
{
	ioctl(g_fd,0x307,Statue);
#ifdef _PSX_QT_LINUX_
	write(g_fd,pBuff,nLen);
#endif
}

void CSttDriverOper::setDisAcAnalogPara(char* pBuff, int nLen, int State)
{
	ioctl(g_fd,0x305,State);
#ifdef _PSX_QT_LINUX_
	write(g_fd,pBuff,nLen);
#endif
}

void  CSttDriverOper::setStateTrigerManual()
{
	ioctl(g_fd,0x400,0);
}

void CSttDriverOper::setDcPowerValue (char *pChar)
{
	/*****
	float fXS = CSttDevice::g_pSttDevice->getUaxuDcXS();
	float fzero = CSttDevice::g_pSttDevice->getUaxuDcZero();
	int fVlot = CSttDevice::g_pSttDevice->getUdcMaxNum();
	float fUDC = atof(pChar);

	fUDC += fzero;
	fUDC = fUDC*fXS;
	float fTmp = fUDC/fVlot*0.75;
	float fValue = qPow(2,31)*fTmp;
	long nValue = fValue;
	nValue = nValue&0xFFFFFFF0;
	unsigned short model = CSttDevice::g_pSttDevice->getModuleNum(VOLT,0); //zhangsen 20180822
	nValue += model;

	ioctl(g_fd,0x10f,nValue);
	*****/
}

int CSttDriverOper::setDeviceDaPara(char* pBuff,int nLen)
{
	ioctl(g_fd,0x304,0);
#ifdef _PSX_QT_LINUX_
	return write(g_fd,pBuff,nLen);
#else
	return 0;
#endif
}

int CSttDriverOper::setFlashData(char* pbuff,int nLen,int nMode)
{
	ioctl(g_fd,0x306,nMode);
#ifdef _PSX_QT_LINUX_
	return write(g_fd,pbuff,nLen);
#else
	return 0;
#endif
}

int CSttDriverOper::readFlashData(char* pbuff,int nMode,int nCmd)
{
#ifdef _PSX_QT_LINUX_
	if(nMode == 0)
	{
		return read(g_fd,pbuff,0x209);
	}
	else
	{
		return read(g_fd,pbuff,nCmd);
	}
#else
	return 0;
#endif
}

int CSttDriverOper::setFlashReadCmd(int module)
{
	return ioctl(g_fd, 0x123, module);
}

int CSttDriverOper::readFlashDataState(char* pbuff)
{
#ifdef _PSX_QT_LINUX_
	return read(g_fd, pbuff, 0x208);
#else
	return 0;
#endif
}

int CSttDriverOper::setRelayData(char* pBuff,int nLen)
{
	ioctl(g_fd,0x308,1);
#ifdef _PSX_QT_LINUX_
	return write(g_fd,pBuff,nLen);
#else
	return 0;
#endif
}

int CSttDriverOper::setRelayConfData(char* pBuff,int nLen)
{
	ioctl(g_fd,0x308,0);
#ifdef _PSX_QT_LINUX_
	return write(g_fd,pBuff,nLen);
#else
	return 0;
#endif
}
int CSttDriverOper::setLtRelayConfData(char* pBuff,int nLen)
{
    ioctl(g_fd,0x352,0);
#ifdef _PSX_QT_LINUX_
    return write(g_fd,pBuff,nLen);
#else
    return 0;
#endif
}
int CSttDriverOper::readReplayIrp()
{
	return ioctl(g_fd, 0x501, 0);
}

int CSttDriverOper::setRampPara(char* pBuff,int nLen)
{
	ioctl(g_fd, 0x309, 0);
#ifdef _PSX_QT_LINUX_
	return write(g_fd, pBuff, nLen);
#else
	return 0;
#endif
}

void CSttDriverOper::set_optical_port(char *pbuff,int nLen,int nFlag)
{
	ioctl(g_fd, 0x321, nFlag)	;	//	flag = 0:π‚ø⁄≈‰÷√	1£∫SMV∑¢ÀÕ≈‰÷√2£∫GOOSE∑¢ÀÕ≈‰÷√3£∫FT3∑¢ÀÕ≈‰÷√
#ifdef _PSX_QT_LINUX_
	write(g_fd, pbuff, nLen);
#endif
}

void CSttDriverOper::setConfigIECCoderData(char * pBuff,int nLen)
{
	ioctl(g_fd,  0x320, 0);
#ifdef _PSX_QT_LINUX_
	write(g_fd, pBuff, nLen);
#endif
}

void CSttDriverOper::setGooseChangedCoderData(char * pBuff,int nLen)
{
	ioctl(g_fd, 0x30B, 1);
#ifdef _PSX_QT_LINUX_
	write(g_fd, pBuff, nLen);
#endif
}

void CSttDriverOper::setGooseTestMode(char * pBuff,int nLen)//÷√ºÏ–ﬁ
{
	ioctl(g_fd, 0x30D, 1);
#ifdef _PSX_QT_LINUX_
	write(g_fd, pBuff, nLen);
#endif
}

void CSttDriverOper::setGooseSubData(char * pBuff,int nLen)
{
	ioctl(g_fd, 0x30C, 1);
#ifdef _PSX_QT_LINUX_
	write(g_fd, pBuff, nLen);
#endif
}

void CSttDriverOper::setFT3SubData(char* pBuff,int nLen)
{
	ioctl(g_fd, 0x310, 1);
#ifdef _PSX_QT_LINUX_
	write(g_fd, pBuff, nLen);
#endif
}

void CSttDriverOper::setCurrentMerge(unsigned int nMerge)
{
	int nFlag = m_nModuleSet&(~0x1);
	nFlag = nFlag | nMerge;
	ioctl(g_fd, 0x110, nFlag);
}

void CSttDriverOper::setPollingsyncsecond(unsigned int nsync)
{
	ioctl(g_fd, 0x110, nsync);
}

void CSttDriverOper::setGooseBoMapData(char* pBuff,int nLen)
{
	ioctl(g_fd, 0x30E, 1);
#ifdef _PSX_QT_LINUX_
	write(g_fd, pBuff, nLen);
#endif
}

void CSttDriverOper::setSendAtStop(unsigned long nValue)
{
	ioctl(g_fd,0x121,nValue);
}

int CSttDriverOper::updateFpga(char* pbuff,int nLen,int nModule)
{
	ioctl(g_fd,0x30F,nModule);
#ifdef _PSX_QT_LINUX_
	return write(g_fd,pbuff,nLen);
#else
	return 0;
#endif
}

int CSttDriverOper::ReadupdateFpga(char* pbuff,int nType)
{
#ifdef _PSX_QT_LINUX_
	return read(g_fd,pbuff,nType);
#else
	return 0;
#endif
}

int CSttDriverOper::ReadupdateFpgaState()
{
	return ioctl(g_fd,0x502,0);
}

int CSttDriverOper::sendUpdateFpgaOver()
{
	return ioctl(g_fd,0x30F,0);
}

int CSttDriverOper::getUpdateFpgaPrecent()
{
	return ioctl(g_fd,0x505,0);
}

void CSttDriverOper::startDMA()
{
	ioctl(g_fd,0xA00,1);
}

void CSttDriverOper::stopDMA()
{
	ioctl(g_fd,0xA00,0);
}

void CSttDriverOper::setFilter(int nFilter)
{
	ioctl(g_fd, 0x402, nFilter);
}

int CSttDriverOper::readDMA(char* buffer)
{
#ifdef _PSX_QT_LINUX_
	return read(g_fd, buffer, 0x230);
#else
	return 0;
#endif
}

void CSttDriverOper::setSwingingPara(char* pBuff,int nLen)
{
	ioctl(g_fd,0x311,0);
#ifdef _PSX_QT_LINUX_
	write(g_fd,pBuff,nLen);
#endif
}

void CSttDriverOper::setabnStatePara(char* pBuff,int nLen)
{
	ioctl(g_fd,0x312,0);
#ifdef _PSX_QT_LINUX_
	write(g_fd,pBuff,nLen);
#endif
}

void CSttDriverOper::setfiberports(int nfiberport)
{
	ioctl(g_fd, 0x122, nfiberport);
}

void CSttDriverOper::SetCurrent_Multiple(int nType)
{
	ioctl(g_fd, 0x124, nType);
}

void CSttDriverOper::setDcModuleTap(int nTap)
{
	ioctl(g_fd, 0x125, nTap);
}

void CSttDriverOper::SetStopDcOutput(char *pBuff,int nLen)
{
	ioctl(g_fd, 0x330, 0);
#ifdef _PSX_QT_LINUX_
	write(g_fd,pBuff,nLen);
#endif
}

void CSttDriverOper::SetBinaryModule(char *pBuff,int nLen)
{
	ioctl(g_fd, 0x340, 0);
#ifdef _PSX_QT_LINUX_
	write(g_fd, pBuff, nLen);
#endif
}

int CSttDriverOper::ReadBinaryModule(char* pBuff)
{
#ifdef _PSX_QT_LINUX_
	return read(g_fd,pBuff,0x240);
#else
	return 0;
#endif
}

void CSttDriverOper::setModuleValied(int nModule)
{
	ioctl(g_fd, 0x126, nModule);
}

void CSttDriverOper::SetSyncPara(char *pBuff,int nLen)
{
	ioctl(g_fd, 0x350, 0);
#ifdef _PSX_QT_LINUX_
	write(g_fd, pBuff, nLen);
#endif
}

int CSttDriverOper::ReadSyncResult(char* pBuff)
{
#ifdef _PSX_QT_LINUX_
	return read(g_fd,pBuff,0x250);
#else
	return 0;
#endif
}

void CSttDriverOper::setRising(int nRising)
{
#ifdef _PSX_QT_LINUX_
	ioctl(g_fd, 0x132, nRising);
#endif
}

int CSttDriverOper::ReadPPStime(char* buff)
{
#ifdef _PSX_QT_LINUX_
	return read(g_fd,buff,0x503);
#endif
}
