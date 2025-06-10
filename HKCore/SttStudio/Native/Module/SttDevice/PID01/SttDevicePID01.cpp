#include "SttDevicePID01.h"
#include "../../SttTest/PID01/tmt_pid01_test.h"

CSttDevicePID01 *CSttDevicePID01::g_pSttDevicePID01=NULL;
long CSttDevicePID01::g_nSttDeviceRef = 0;

CSttDevicePID01::CSttDevicePID01()
{

}

CSttDevicePID01::~CSttDevicePID01()
{

}

void CSttDevicePID01::Create()
{
	g_nSttDeviceRef++;

	if (g_nSttDeviceRef == 1)
	{
		g_pSttDevicePID01=new CSttDevicePID01;
		g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDevicePID01;
	}
}

void CSttDevicePID01::Release()
{
	g_nSttDeviceRef--;

	if (g_nSttDeviceRef == 0)
	{
		delete g_pSttDevicePID01;
		g_pSttDevicePID01 = NULL;
	}
}

#define DIO_0x100  0x00000100
#define DIO_0x101  0x00000101
#define DIO_0x102  0x00000102
#define DIO_0x103  0x00000103
#define DIO_0x104  0x00000104
#define DIO_0x105  0x00000105
#define DIO_0x106  0x00000106
#define DIO_0x107  0x00000107
#define KC_0x10B   0x0000010B
unsigned char pszDMA[1024];
unsigned char pszDIO[90];
unsigned int pszKC[33];
unsigned int nCtrlData_KC = 0xffffffff;
unsigned int nCtrlData_DIO_0x100 = 0xff;
unsigned int nCtrlData_DIO_0x101 = 0xff;
unsigned int nCtrlData_DIO_0x102 = 0xff;
unsigned int nCtrlData_DIO_0x103 = 0xff;
unsigned int nCtrlData_DIO_0x104 = 0xff;
unsigned int nCtrlData_DIO_0x105 = 0xff;
unsigned int nCtrlData_DIO_0x106 = 0xff;
unsigned int nCtrlData_DIO_0x107 = 0xff;
int nDmafd;

//资源
//0x0000010B   KC_32 -- KC_1
//0x00000100   (DIO) 53,04,52,03,51,02,50,01
//0x00000101   (DIO) 56,07,57,08,58,09,59,10
//0x00000102   (DIO) 61,12,62,13,63,14,64,15
//0x00000103   (DIO) 66,17,67,18,68,19,69,20
//0x00000104   (DIO) 71,22,72,23,73,24,74,25
//0x00000105   (DIO) 76,27,77,28,78,29,79,30
//0x00000106   (DIO) 81,32,82,33,83,34,84,35
//0x00000107   (DIO) 86,37,87,38,88,39,89,40

int CSttDevicePID01::InitDevice(BOOL bHasAdjFile)
{
	memset(pszDMA,0,1024);
	for(int i=1;i<33;i++)
	{
		pszKC[i]=1<<(i-1);
	}

	pszDIO[1]=1;
	pszDIO[2]=1<<2;
	pszDIO[3]=1<<4;
	pszDIO[4]=1<<6;

	for(int i = 7;i<=37;i=i+5)
	{
		pszDIO[i]=1<<6;
		pszDIO[i+1]=1<<4;
		pszDIO[i+2]=1<<2;
		pszDIO[i+3]=1;
	}

	pszDIO[50]=1<<1;
	pszDIO[51]=1<<3;
	pszDIO[52]=1<<5;
	pszDIO[53]=1<<7;

	for(int i = 56;i<=86;i=i+5)
	{
		pszDIO[i]=1<<7;
		pszDIO[i+1]=1<<5;
		pszDIO[i+2]=1<<3;
		pszDIO[i+3]=1<<1;
	}

    m_nCommfd=open("/dev/pav5000",O_RDWR);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("m_nCommfd=%d"),
							   m_nCommfd);
	ioctl(m_nCommfd,0x103,1);
	nDmafd = open("/dev/dma_dev",O_RDWR);

	unsigned int nData=10;
	write(m_nCommfd,&nData,0x10C);
	return m_nCommfd;
}

void CSttDevicePID01::ProPid01DrvResult()
{
	ioctl(m_nCommfd,0x110,0);
}

void CSttDevicePID01::tmt_to_drv_pid01(void *pVoidTmt)
{
	nCtrlData_KC = 0xffffffff;
	nCtrlData_DIO_0x100 = 0xff;
	nCtrlData_DIO_0x101 = 0xff;
	nCtrlData_DIO_0x102 = 0xff;
	nCtrlData_DIO_0x103 = 0xff;
	nCtrlData_DIO_0x104 = 0xff;
	nCtrlData_DIO_0x105 = 0xff;
	nCtrlData_DIO_0x106 = 0xff;
	nCtrlData_DIO_0x107 = 0xff;
	tmt_Pid01Test *pTmt=(tmt_Pid01Test *)pVoidTmt;

	//主板开关量
	//开出1 DIO_1
	if(pTmt->m_oPid01Para.m_binOut[0].nState == 0)
	{
		nCtrlData_DIO_0x100 |= pszDIO[1];
	}
	else
	{
		nCtrlData_DIO_0x100 &= ~pszDIO[1];
	}
	//开出2 DIO_50
	if(pTmt->m_oPid01Para.m_binOut[1].nState == 0)
	{
		nCtrlData_DIO_0x100 |= pszDIO[50];
	}
	else
	{
		nCtrlData_DIO_0x100 &= ~pszDIO[50];
	}
	//开出3 DIO_2
	if(pTmt->m_oPid01Para.m_binOut[2].nState == 0)
	{
		nCtrlData_DIO_0x100 |= pszDIO[2];
	}
	else
	{
		nCtrlData_DIO_0x100 &= ~pszDIO[2];
	}
	//开出4 DIO_51
	if(pTmt->m_oPid01Para.m_binOut[3].nState == 0)
	{
		nCtrlData_DIO_0x100 |= pszDIO[51];
	}
	else
	{
		nCtrlData_DIO_0x100 &= ~pszDIO[51];
	}
	//开出5 DIO_3
	if(pTmt->m_oPid01Para.m_binOut[4].nState == 0)
	{
		nCtrlData_DIO_0x100 |= pszDIO[3];
	}
	else
	{
		nCtrlData_DIO_0x100 &= ~pszDIO[3];
	}
	//开出6 DIO_52
	if(pTmt->m_oPid01Para.m_binOut[5].nState == 0)
	{
		nCtrlData_DIO_0x100 |= pszDIO[52];
	}
	else
	{
		nCtrlData_DIO_0x100 &= ~pszDIO[52];
	}
	//开出7 DIO_4
	if(pTmt->m_oPid01Para.m_binOut[6].nState == 0)
	{
		nCtrlData_DIO_0x100 |= pszDIO[4];
	}
	else
	{
		nCtrlData_DIO_0x100 &= ~pszDIO[4];
	}
	//开出8 DIO_53
	if(pTmt->m_oPid01Para.m_binOut[7].nState == 0)
	{
		nCtrlData_DIO_0x100 |= pszDIO[53];
	}
	else
	{
		nCtrlData_DIO_0x100 &= ~pszDIO[53];
	}

	switch(pTmt->m_oPid01Para.m_oPik08Para[1].m_nU2Power)
	{
	case U2Power_U2M:
	{
		//DIO_18
		nCtrlData_DIO_0x103 &= ~pszDIO[18];
	}
		break;
	case U2Power_U2S:
	{
		//DIO_67
		nCtrlData_DIO_0x103 &= ~pszDIO[67];
	}
		break;
	case U2Power_U2MS:
	{
		nCtrlData_DIO_0x103 &= ~pszDIO[18];
		nCtrlData_DIO_0x103 &= ~pszDIO[67];
	}
		break;
	}

	switch(pTmt->m_oPid01Para.m_oPik08Para[1].m_nVoltMode)
	{
	case Mode_4Ch:
	{
		//DIO_10
		nCtrlData_DIO_0x101 &= ~pszDIO[10];
	}
		break;
	case Mode_aH:
	{
		//DIO_59
		nCtrlData_DIO_0x101 &= ~pszDIO[59];
	}
		break;
	case Mode_bH:
	{
		//DIO_9
		nCtrlData_DIO_0x101 &= ~pszDIO[9];
	}
		break;
	case Mode_cH:
	{
		//DIO_58
		nCtrlData_DIO_0x101 &= ~pszDIO[58];
	}
		break;
	case Mode_0H:
	{
		//DIO_8
		nCtrlData_DIO_0x101 &= ~pszDIO[8];
	}
		break;
	}

	switch(pTmt->m_oPid01Para.m_oPik08Para[1].m_nCurrMode)
	{
	case Mode_4Ch:
	{
		//DIO_57
		nCtrlData_DIO_0x101 &= ~pszDIO[57];
	}
		break;
	case Mode_aH:
	{
		//DIO_7
		nCtrlData_DIO_0x101 &= ~pszDIO[7];
	}
		break;
	case Mode_bH:
	{
		//DIO_56
		nCtrlData_DIO_0x101 &= ~pszDIO[56];
	}
		break;
	case Mode_cH:
	{
		//DIO_15
		nCtrlData_DIO_0x102 &= ~pszDIO[15];
	}
		break;
	case Mode_0H:
	{
		//DIO_64
		nCtrlData_DIO_0x102 &= ~pszDIO[64];
	}
		break;
	}

	switch(pTmt->m_oPid01Para.m_oPik08Para[1].m_nVoltBoardSel)
	{
	case Board_S1:
	{
		//DIO_19
		nCtrlData_DIO_0x103 &= ~pszDIO[19];
	}
		break;
	case Board_S2:
	{
		//DIO_68
		nCtrlData_DIO_0x103 &= ~pszDIO[68];
	}
		break;
	}

	switch(pTmt->m_oPid01Para.m_oPik08Para[1].m_nCurrBoardSel)
	{
	case Board_S1:
	{
		//DIO_14
		nCtrlData_DIO_0x102 &= ~pszDIO[14];
	}
		break;
	case Board_S2:
	{
		//DIO_63
		nCtrlData_DIO_0x102 &= ~pszDIO[63];
	}
		break;
	case Board_S3:
	{
		//DIO_13
		nCtrlData_DIO_0x102 &= ~pszDIO[13];
	}
		break;
	case Board_S4:
	{
		//DIO_62
		nCtrlData_DIO_0x102 &= ~pszDIO[62];
	}
		break;
	case Board_S5:
	{
		//DIO_12
		nCtrlData_DIO_0x102 &= ~pszDIO[12];
	}
		break;
	case Board_S6:
	{
		//DIO_61
		nCtrlData_DIO_0x102 &= ~pszDIO[61];
	}
		break;
	case Board_S7:
	{
		//DIO_20
		nCtrlData_DIO_0x103 &= ~pszDIO[20];
	}
		break;
	case Board_S8:
	{
		//DIO_69
		nCtrlData_DIO_0x103 &= ~pszDIO[69];
	}
		break;
	}

	write(m_nCommfd,&nCtrlData_DIO_0x100,DIO_0x100);
	write(m_nCommfd,&nCtrlData_DIO_0x101,DIO_0x101);
	write(m_nCommfd,&nCtrlData_DIO_0x102,DIO_0x102);
	write(m_nCommfd,&nCtrlData_DIO_0x103,DIO_0x103);
	write(m_nCommfd,&nCtrlData_DIO_0x104,DIO_0x104);
	write(m_nCommfd,&nCtrlData_DIO_0x105,DIO_0x105);
	write(m_nCommfd,&nCtrlData_DIO_0x106,DIO_0x106);
	write(m_nCommfd,&nCtrlData_DIO_0x107,DIO_0x107);

	write(nDmafd,&pszDMA,1024);

	//KC
	switch(pTmt->m_oPid01Para.m_oPik08Para[0].m_nU2Power)
	{
	case U2Power_U2M:
	{
		//KC_21
		nCtrlData_KC &= ~pszKC[21];
	}
		break;
	case U2Power_U2S:
	{
		//KC_22
		nCtrlData_KC &= ~pszKC[22];
	}
		break;
	case U2Power_U2MS:
	{
		nCtrlData_KC &= ~pszKC[21];
		nCtrlData_KC &= ~pszKC[22];
	}
		break;
	}

	switch(pTmt->m_oPid01Para.m_oPik08Para[0].m_nVoltMode)
	{
	case Mode_4Ch:
	{
		//KC_1
		nCtrlData_KC &= ~pszKC[1];
	}
		break;
	case Mode_aH:
	{
		//KC_2
		nCtrlData_KC &= ~pszKC[2];
	}
		break;
	case Mode_bH:
	{
		//KC_3
		nCtrlData_KC &= ~pszKC[3];
	}
		break;
	case Mode_cH:
	{
		//KC_4
		nCtrlData_KC &= ~pszKC[4];
	}
		break;
	case Mode_0H:
	{
		//KC_5
		nCtrlData_KC &= ~pszKC[5];
	}
		break;
	}

	switch(pTmt->m_oPid01Para.m_oPik08Para[0].m_nCurrMode)
	{
	case Mode_4Ch:
	{
		//KC_6
		nCtrlData_KC &= ~pszKC[6];
	}
		break;
	case Mode_aH:
	{
		//KC_7
		nCtrlData_KC &= ~pszKC[7];
	}
		break;
	case Mode_bH:
	{
		//KC_8
		nCtrlData_KC &= ~pszKC[8];
	}
		break;
	case Mode_cH:
	{
		//KC_9
		nCtrlData_KC &= ~pszKC[9];
	}
		break;
	case Mode_0H:
	{
		//KC_10
		nCtrlData_KC &= ~pszKC[10];
	}
		break;
	}

	switch(pTmt->m_oPid01Para.m_oPik08Para[0].m_nVoltBoardSel)
	{
	case Board_S1:
	{
		//KC_19
		nCtrlData_KC &= ~pszKC[19];
	}
		break;
	case Board_S2:
	{
		//KC_20
		nCtrlData_KC &= ~pszKC[20];
	}
		break;
	}

	switch(pTmt->m_oPid01Para.m_oPik08Para[0].m_nCurrBoardSel)
	{
	case Board_S1:
	{
		//KC_11
		nCtrlData_KC &= ~pszKC[11];
	}
		break;
	case Board_S2:
	{
		//KC_12
		nCtrlData_KC &= ~pszKC[12];
	}
		break;
	case Board_S3:
	{
		//KC_13
		nCtrlData_KC &= ~pszKC[13];
	}
		break;
	case Board_S4:
	{
		//KC_14
		nCtrlData_KC &= ~pszKC[14];
	}
		break;
	case Board_S5:
	{
		//KC_15
		nCtrlData_KC &= ~pszKC[15];
	}
		break;
	case Board_S6:
	{
		//KC_16
		nCtrlData_KC &= ~pszKC[16];
	}
		break;
	case Board_S7:
	{
		//KC_17
		nCtrlData_KC &= ~pszKC[17];
	}
		break;
	case Board_S8:
	{
		//KC_18
		nCtrlData_KC &= ~pszKC[18];
	}
		break;
	}

	write(m_nCommfd,&nCtrlData_KC,KC_0x10B);

	if(pTmt->m_oPid01Para.m_fOutputTime > 1.0 && pTmt->m_oPid01Para.m_fOutputTime < 5.1)
	{
		Sleep((long)pTmt->m_oPid01Para.m_fOutputTime*1000);
	}
	else
	{
		Sleep(1000);
	}

	CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
	pSttTestBase->ReturnRealTimeEvent();
	pSttTestBase->ReturnTestStateEvent_TestFinish(0,0,FALSE);
}

void CSttDevicePID01::tmt_to_drv_pid16(void *pVoidTmt)
{
    nCtrlData_DIO_0x100 = 0xff;
    nCtrlData_DIO_0x101 = 0xff;
    tmt_Pid16Para *pTmt=(tmt_Pid16Para *)pVoidTmt;

    //主板开关量
    //0x00000100   (DIO) 53,04,52,03,51,02,50,01
    //0x00000101   (DIO) 56,07,57,08,58,09,59,10
    //开出1 DIO_10
    if(pTmt->m_binOut[0].nState == 0)
    {
        nCtrlData_DIO_0x101 |= pszDIO[10];
    }
    else
    {
        nCtrlData_DIO_0x101 &= ~pszDIO[10];
    }
    //开出2 DIO_9
    if(pTmt->m_binOut[1].nState == 0)
    {
        nCtrlData_DIO_0x101 |= pszDIO[9];
    }
    else
    {
        nCtrlData_DIO_0x101 &= ~pszDIO[9];
    }
    //开出3 DIO_8
    if(pTmt->m_binOut[2].nState == 0)
    {
        nCtrlData_DIO_0x101 |= pszDIO[8];
    }
    else
    {
        nCtrlData_DIO_0x101 &= ~pszDIO[8];
    }
    //开出4 DIO_7
    if(pTmt->m_binOut[3].nState == 0)
    {
        nCtrlData_DIO_0x101 |= pszDIO[7];
    }
    else
    {
        nCtrlData_DIO_0x101 &= ~pszDIO[7];
    }
    //开出5 DIO_4
    if(pTmt->m_binOut[4].nState == 0)
    {
        nCtrlData_DIO_0x100 |= pszDIO[4];
    }
    else
    {
        nCtrlData_DIO_0x100 &= ~pszDIO[4];
    }
    //开出6 DIO_3
    if(pTmt->m_binOut[5].nState == 0)
    {
        nCtrlData_DIO_0x100 |= pszDIO[3];
    }
    else
    {
        nCtrlData_DIO_0x100 &= ~pszDIO[3];
    }
    //开出7 DIO_2
    if(pTmt->m_binOut[6].nState == 0)
    {
        nCtrlData_DIO_0x100 |= pszDIO[2];
    }
    else
    {
        nCtrlData_DIO_0x100 &= ~pszDIO[2];
    }
    //开出8 DIO_1
    if(pTmt->m_binOut[7].nState == 0)
    {
        nCtrlData_DIO_0x100 |= pszDIO[1];
    }
    else
    {
        nCtrlData_DIO_0x100 &= ~pszDIO[1];
    }   
    //开出9 DIO_59
    if(pTmt->m_binOut[8].nState == 0)
    {
        nCtrlData_DIO_0x101 |= pszDIO[59];
    }
    else
    {
        nCtrlData_DIO_0x101 &= ~pszDIO[59];
    }
    //开出10 DIO_58
    if(pTmt->m_binOut[9].nState == 0)
    {
        nCtrlData_DIO_0x101 |= pszDIO[58];
    }
    else
    {
        nCtrlData_DIO_0x101 &= ~pszDIO[58];
    }
    //开出11 DIO_57
    if(pTmt->m_binOut[10].nState == 0)
    {
        nCtrlData_DIO_0x101 |= pszDIO[57];
    }
    else
    {
        nCtrlData_DIO_0x101 &= ~pszDIO[57];
    }
    //开出12 DIO_56
    if(pTmt->m_binOut[11].nState == 0)
    {
        nCtrlData_DIO_0x101 |= pszDIO[56];
    }
    else
    {
        nCtrlData_DIO_0x101 &= ~pszDIO[56];
    }
    //开出13 DIO_53
    if(pTmt->m_binOut[12].nState == 0)
    {
        nCtrlData_DIO_0x100 |= pszDIO[53];
    }
    else
    {
        nCtrlData_DIO_0x100 &= ~pszDIO[53];
    }
    //开出14 DIO_52
    if(pTmt->m_binOut[13].nState == 0)
    {
        nCtrlData_DIO_0x100 |= pszDIO[52];
    }
    else
    {
        nCtrlData_DIO_0x100 &= ~pszDIO[52];
    }
    //开出15 DIO_51
    if(pTmt->m_binOut[14].nState == 0)
    {
        nCtrlData_DIO_0x100 |= pszDIO[51];
    }
    else
    {
        nCtrlData_DIO_0x100 &= ~pszDIO[51];
    }
    //开出16 DIO_50
    if(pTmt->m_binOut[15].nState == 0)
    {
        nCtrlData_DIO_0x100 |= pszDIO[50];
    }
    else
    {
        nCtrlData_DIO_0x100 &= ~pszDIO[50];
    }    

    write(m_nCommfd,&nCtrlData_DIO_0x100,DIO_0x100);
    write(m_nCommfd,&nCtrlData_DIO_0x101,DIO_0x101);
    write(nDmafd,&pszDMA,1024);

    if(pTmt->m_fOutputTime > 1.0 && pTmt->m_fOutputTime < 5.1)
    {
        Sleep((long)pTmt->m_fOutputTime*1000);
    }
    else
    {
        Sleep(1000);
    }

    CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
    pSttTestBase->ReturnRealTimeEvent();
    pSttTestBase->ReturnTestStateEvent_TestFinish(0,0,FALSE);
}
