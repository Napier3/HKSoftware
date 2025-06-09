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
	g_nmaplen = 0x70005074 - 0x70004010;
	g_start = (unsigned int *)mmap(NULL, g_nmaplen, PROT_WRITE, MAP_SHARED, g_fd, 0);
	m_nAnalogSync=0;
	m_nModuleSet=1;
	Init();
}

long CSttDriverOper::getTemprature()
{
	unsigned int *buffer;
	unsigned int nRet = 0;
	buffer = (unsigned int *)malloc(sizeof(unsigned int));

#ifdef CURLINUX
	nRet = *buffer;
#endif

	free(buffer);
	return nRet;
}

long CSttDriverOper::getStartTime()
{
	unsigned int *buffer;
	unsigned int nRet = 0;
	buffer = (unsigned int *)malloc(sizeof(unsigned int));

#ifdef CURLINUX
	nRet = *buffer;
#endif

	free(buffer);
	return nRet;
}

void CSttDriverOper::Start(int nValue)
{
	//nValue 手动1，状态序列2，差动3
#ifdef CURLINUX
	//    qDebug()<<"0x103---------------"<<nValue;
	ioctl(g_fd, 0x103, nValue);
#endif
}

void CSttDriverOper::Stop()
{
	//   qDebug()<<"Driver stop";
#ifdef CURLINUX
	ioctl(g_fd, 0x103, 0);
#endif
}


void CSttDriverOper::keepStop()
{
	//   qDebug()<<"Driver stop";
#ifdef CURLINUX
	ioctl(g_fd, 0x113, 0);
	ioctl(g_fd, 0x103, 0);
#endif
}

void CSttDriverOper::setStartTime(unsigned long nSecond,unsigned long nNaSecond)
{

}

void CSttDriverOper::WriteRegister(unsigned long nAddr,unsigned long data)
{
	unsigned int *buffer;
	buffer = (unsigned int *)malloc(sizeof(unsigned int));
	buffer[0] = data;

	//m_mutex.lock();
#ifdef CURLINUX
	ioctl(g_fd,nAddr,data);
#endif
	free(buffer);
}

void CSttDriverOper::WriteAnalogSync()
{
	if(m_nAnalogSync == 0)
	{
		m_nAnalogSync = 1;
	}
	else
	{
		m_nAnalogSync = 0;
	}
	unsigned int *buffer;
	buffer = (unsigned int *)malloc(sizeof(unsigned long));
	buffer[0] = m_nAnalogSync;

	//m_mutex.lock();
#ifdef CURLINUX
	ioctl(g_fd,0x70000018,m_nAnalogSync);
	//     qDebug()<<"0x70000018"<<m_nAnalogSync;
#endif
	free(buffer);
}

void CSttDriverOper::WriteFPGAData(unsigned long nAddr,unsigned long data)
{
#ifdef CURLINUX
	ioctl(g_fd,nAddr,data);
#endif
}

void CSttDriverOper::WriteFPGAAnalog(char* buff,unsigned long nLen)
{
	unsigned long bufLen;

	unsigned long* p = (unsigned long*)buff;

	memcpy(g_start+4, buff, nLen);

	for(int i=0;i<16;i++){
		ioctl(g_fd,0x70004010+i*4,p[i]);
	}
	WriteAnalogSync();
}

void CSttDriverOper::IoCtrl(unsigned long ncmd,unsigned long nValue)
{
#ifdef CURLINUX
	ioctl(g_fd,ncmd,nValue);
#endif
}

int CSttDriverOper::readManualResult(char* buff,int nSize)
{
#ifdef CURLINUX
	int nLen = read(g_fd,buff,0x01);
	//   qDebug()<<"*******************************************nLen is:"<<nLen;
	return nLen;
#endif
}

int CSttDriverOper::readDeviceInnerPara(char* pbuff)
{
	if(readFlashData(pbuff,4,DAPARAADDR,1)<=0)
	{
		return -1;
	}
	if(readFlashData(pbuff+4,4,DAPARAADDR,2)<=0)
	{
		return -1;
	}

	return 1;
}

int CSttDriverOper::readDisBinStatePara()
{
#ifdef CURLINUX
	int nLen = ioctl(g_fd,0x208,0);
	return nLen;
#endif

}

void CSttDriverOper::SetisStopIfBiChanged(int nValue)
{
#ifdef CURLINUX
	ioctl(g_fd,0x104,nValue);
#endif
}

void CSttDriverOper::SetStopDelayTime(int nTime)
{
#ifdef CURLINUX
	ioctl(g_fd,0x105,nTime);
#endif

}

void CSttDriverOper::SetBinaryOut(int nState)
{
#ifdef CURLINUX
	ioctl(g_fd,0x107,nState);
#endif
}

void CSttDriverOper::SetBinaryInLogic(int nLogic)
{
#ifdef CURLINUX
	ioctl(g_fd,0x10D,nLogic);
#endif
}

void CSttDriverOper::setManualAcAnalogPara(char* pBuff,int nLen)
{
#ifdef CURLINUX
	ioctl(g_fd,0x300,0);
	write(g_fd,pBuff,nLen);
#endif
}
void CSttDriverOper::setOutPutTap(int nTap)
{
#ifdef CURLINUX
	//qDebug("tap %x",nTap);
	ioctl(g_fd,0x105,nTap);
#endif
}
void CSttDriverOper::setMeasTap(int nTap)
{
#ifdef CURLINUX
	ioctl(g_fd,0x104,nTap);
#endif
}
void CSttDriverOper::setInputShake(int nDelay)
{
#ifdef CURLINUX
	ioctl(g_fd,0x111,nDelay);
#endif
}
void CSttDriverOper::setDelayOverload(int nDelay)
{
#ifdef CURLINUX
	ioctl(g_fd,0x112,nDelay);
#endif
}
void CSttDriverOper::setOutPutStatue(int nValue)
{
#ifdef CURLINUX
	ioctl(g_fd,0x107,nValue);
#endif

}
void CSttDriverOper::setAnalogMeas(char* pBuff,int nLen)
{
#ifdef CURLINUX
	ioctl(g_fd,0x301,0);
	write(g_fd,pBuff,nLen);
#endif
}

void CSttDriverOper::setStatePara(char* pBuff,int nLen)
{
#ifdef CURLINUX
	ioctl(g_fd,0x302,0);
	write(g_fd,pBuff,nLen);
#endif
}
void CSttDriverOper::setDiffAcAnalogPara(char* pBuff,int nLen,int Statue)
{
#ifdef CURLINUX
	ioctl(g_fd,0x303,Statue);
	write(g_fd,pBuff,nLen);
#endif

}
void CSttDriverOper::setSearchAcAnalogPara(char* pBuff,int nLen,int Statue)
{
#ifdef CURLINUX
	ioctl(g_fd,0x307,0);
	write(g_fd,pBuff,nLen);
#endif

}
void CSttDriverOper::setDisAcAnalogPara(char* pBuff, int nLen, int State)
{

#ifdef CURLINUX
	ioctl(g_fd,0x305,State);
	write(g_fd,pBuff,nLen);
#endif

}

void  CSttDriverOper::setStateTrigerManual()
{
#ifdef CURLINUX
	ioctl(g_fd,0x400,0);

#endif
}

void CSttDriverOper::setDCoutput(long nValue)
{
#ifdef CURLINUX
	ioctl(g_fd,0x10f,nValue);
#endif

}

int CSttDriverOper::setDeviceDaPara(char* pbuff,int nLen)
{
#ifdef CURLINUX
	ioctl(g_fd,0x304,0);
	write(g_fd,pbuff,nLen);
#endif
}

int  CSttDriverOper::SaveDevicePara(char* pbuff,int nLen)
{
	setFlashData(pbuff,4,DAPARAADDR,1);
	setFlashData(pbuff+4,4,DAPARAADDR,2);
}

int CSttDriverOper::setFlashData(char* pbuff,int nLen,int nAddr,int nMode)
{
#ifdef CURLINUX
	ioctl(g_fd,0x306,nMode);
	lseek(g_fd, nAddr, nMode);
	write(g_fd,pbuff,nLen);
#endif
}

int CSttDriverOper::readFlashData(char* pbuff,int nLen,int nAddr,int nMode)
{
#ifdef CURLINUX
	ioctl(g_fd,0x206,nMode);
	lseek(g_fd, nAddr, nMode);
	int nret = read(g_fd,pbuff,nLen);
	return nret;
#endif
}
int CSttDriverOper::setRelayData(char* pbuff,int nLen)
{
#ifdef CURLINUX
	ioctl(g_fd,0x309,1);
	write(g_fd,pbuff,nLen);
#endif
}
int CSttDriverOper::setRelayConfData(char* pbuff,int nLen)
{
#ifdef CURLINUX
	ioctl(g_fd,0x309,0);
	write(g_fd,pbuff,nLen);
#endif
}
int CSttDriverOper::setKeepSendData(char* pBuff,int nLen)
{
#ifdef CURLINUX
	ioctl(g_fd,0x308,1);
	write(g_fd,pBuff,nLen);
	ioctl(g_fd,0x113,1);
#endif

}

int CSttDriverOper::readRelayIrp()
{
	int nRet;
#ifdef CURLINUX
	nRet = ioctl(g_fd, 0x501, 0);
#endif
	return nRet;
}
void CSttDriverOper::readMeasdata(char* pbuff,int nState)
{
#ifdef CURLINUX
	read(g_fd,pbuff,nState);
#endif

}

int CSttDriverOper::setRampPara(char* pbuff,int nLen)
{
#ifdef CURLINUX
	ioctl(g_fd, 0x30A, 0);
	write(g_fd, pbuff, nLen);
#endif
}

void CSttDriverOper::Init()
{
	setInputShake(20000);
#ifdef CURLINUX
	ioctl(g_fd, 0x110,5);
#endif
}

int CSttDriverOper::updateFpga(char* pbuff,int nLen,int nModule)
{
#ifdef CURLINUX
	ioctl(g_fd,0x30F,nModule);
	int nRet = write(g_fd,pbuff,nLen);
	return nRet;

#endif
}
int CSttDriverOper::sendUpdateFpgaOver()
{
#ifdef CURLINUX
	ioctl(g_fd,0x30F,0);
#endif
}
int CSttDriverOper::ReadupdateFpga(char* pbuff,int nType)
{
#ifdef CURLINUX
	int nLen = read(g_fd,pbuff,nType);

#endif
}
int CSttDriverOper::ReadupdateFpgaState()
{
#ifdef CURLINUX
	int nRet = ioctl(g_fd,0x502,0);
	return nRet;
#endif
}

int CSttDriverOper::SetSmallTap(int nTap)
{
#ifdef CURLINUX
	int nRet = ioctl(g_fd,0x114,nTap);
	return nRet;
#endif
}
