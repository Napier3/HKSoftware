#include "SttDevicePIK100.h"
#include "../../Engine/SttServerTestCtrlCntr.h"
#include "../../Engine/SttTestServerBase.h"
#include "../../SttTest/Common/Adjust/SttAdjust_ModuleOutput.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>	//SIGIO
#include<sys/syscall.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "qthread.h"
#include "../../SttTest/Common/tmt_common_def.h"

CSttDevicePIK100 *CSttDevicePIK100::g_pSttDevicePIK100=NULL;
long CSttDevicePIK100::g_nSttDeviceRef = 0;
DCpbufferdata DCbuffer;
ACpbufferdata ACbuffer;
StructModePara StrModePara;
unsigned int SttStateStart=0;
unsigned int SttStateReadyFlag;
unsigned int nStopTestAfterCheck = 1;
quint32 temp_KR[13];
quint32 temp_KC[13];
int KC1_42State[42];
int StateFlagReady = 0;
int CountCtrlFlag = 0;
int CountNO;
quint32 TemptoFpga[16];
quint32 FPGA0x100;//[95:64]
quint32 FPGA0x101;//[63:32]
quint32 FPGA0x102;//[31:0]
quint32 FPGA0x103;//[95:64]
quint32 FPGA0x104;//[63:32]
quint32 FPGA0x105;//[31:0]
quint32 FPGA0x106;//[95:64]
quint32 FPGA0x107;//[63:32]
quint32 FPGA0x108;//[31:0]
quint32 FPGA0x109;//[95:64]
quint32 FPGA0x10a;//[63:32]
quint32 FPGA0x10b;//[31:0]
quint32 FPGA0x10c;//[12:0]
PSTT_MODULE pModule=NULL;
long nDelayTime = 0;
tmt_Pik100Test *pTmt = NULL;

CSttDevicePIK100::CSttDevicePIK100()
{

}

void CSttDevicePIK100::Create()
{
    g_nSttDeviceRef++;

    if (g_nSttDeviceRef == 1)
    {
        g_pSttDevicePIK100=new CSttDevicePIK100;
        g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDevicePIK100;
    }
}

void CSttDevicePIK100::Release()
{
    g_nSttDeviceRef--;

    if (g_nSttDeviceRef == 0)
    {
        delete g_pSttDevicePIK100;
        g_pSttDevicePIK100 = NULL;
    }
}

int CSttDevicePIK100::InitDevice(BOOL bHasAdjFile)
{
    for(int i=0;i<g_theDeviceSystemParameter->m_nModuleCount;i++)
    {
        if(g_theDeviceSystemParameter->m_oModules[i].m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_DCVOLT)
        {
            pModule = &g_theDeviceSystemParameter->m_oModules[i];
            break;
        }
    }

    m_nCommfd=open("/dev/pav5000",O_RDWR);

    //	qDebug()<<"m_nCommfd="<<QString::number(m_nCommfd);
    //	ioctl(m_nCommfd, 0x103, 1);//Start DMA
    //	SENDAtoFPGA(1,0x103);
    return m_nCommfd;
}
void CSttDevicePIK100::tmt_to_drv_systemdefaultoutput(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pTmt)
{
    if(pTmt->m_bUseSysOutput)
    {
        int Uauxtemp;
        float Uaux;
        float Uauxtemp1;
        float fcoef = 1;
        if(pModule != NULL)
        {
            STT_ADJUST_ITEM oAdjItem = pModule->m_oModuleAdjust.m_oTempAdjust[0].m_oChUdcAdj.m_oChGearAdj[0].m_oAdjItem;
            fcoef = oAdjItem.m_fCoef;
        }

        Uaux = pTmt->m_uiVOL[0].Harm[1].fAmp*fcoef;

        Uauxtemp1 = (Uaux*1000/144/2.5)*100;
        Uauxtemp = Uauxtemp1;//PWM  High Time 设置PWM高电平时间（单位10ns）
        //		qDebug()<<"PWM  High Time="<<QString::number(Uauxtemp);
        SENDAtoFPGA(Uauxtemp,0x10d);
        Uauxtemp1 = (100000-Uauxtemp1);
        Uauxtemp = Uauxtemp1;//PWM  Low Time 设置PWM低电平时间（单位10ns）
        //		qDebug()<<"PWM  Low Time ="<<QString::number(Uauxtemp);
        if(Uauxtemp < 0)
            Uauxtemp = 0;
        SENDAtoFPGA(Uauxtemp,0x10e);
        SENDAtoFPGA(1,0x010f);
    }
    else
    {
        int Uauxtemp;
        float Uaux;
        float Uauxtemp1;
        Uaux = pTmt->m_uiVOL[0].Harm[1].fAmp;
        Uauxtemp1 = (Uaux*1000/144/2.5)*100;
        Uauxtemp = Uauxtemp1;//PWM  High Time 设置PWM高电平时间（单位10ns）
        SENDAtoFPGA(Uauxtemp,0x10d);
        Uauxtemp1 = (100000-Uauxtemp1);
        Uauxtemp = Uauxtemp1;//PWM  Low Time 设置PWM低电平时间（单位10ns）
        SENDAtoFPGA(Uauxtemp,0x10e);
        SENDAtoFPGA(0,0x010f);
    }
}

void CSttDevicePIK100::Print_Para(tmt_pik100_DA da)
{
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("StateStart=%d"),da.StateStart);

    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K1=%d"),da.K1);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K2=%d"),da.K2);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K3=%d"),da.K3);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K4=%d"),da.K4);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K5=%d"),da.K5);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K6=%d"),da.K6);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K7=%d"),da.K7);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K8=%d"),da.K8);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K9=%d"),da.K9);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K10=%d"),da.K10);

    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K11=%d"),da.K11);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K12=%d"),da.K12);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K13=%d"),da.K13);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K14=%d"),da.K14);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K15=%d"),da.K15);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K16=%d"),da.K16);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K17=%d"),da.K17);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K18=%d"),da.K18);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K19=%d"),da.K19);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K20=%d"),da.K20);

    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K21=%d"),da.K21);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K22=%d"),da.K22);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K23=%d"),da.K23);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K24=%d"),da.K24);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K25=%d"),da.K25);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K26=%d"),da.K26);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K27=%d"),da.K27);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K28=%d"),da.K28);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K29=%d"),da.K29);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K30=%d"),da.K30);

    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K31=%d"),da.K31);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K32=%d"),da.K32);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K33=%d"),da.K33);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K34=%d"),da.K34);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K35=%d"),da.K35);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K36=%d"),da.K36);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K37=%d"),da.K37);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K38=%d"),da.K38);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K39=%d"),da.K39);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K40=%d"),da.K40);

    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K41=%d"),da.K41);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("K42=%d"),da.K42);

    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("Addr010c=%d"),da.Addr010c);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("VsenseFlag=%d"),da.VsenseFlag);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("V24VIsenseFlag=%d"),da.V24VIsenseFlag);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("V220VIsenseFlag=%d"),da.V220VIsenseFlag);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("StateReadyFlag=%d"),da.StateReadyFlag);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("CountFlag=%d"),da.CountFlag);
}

void CSttDevicePIK100::Print_KCKR()
{
    CString strKC,strKR,strDiff;
    strKC=QString("%1").arg(temp_KC[0],8,16,QChar('0'));
    strKR=QString("%1").arg(temp_KR[0],8,16,QChar('0'));
    if(strKC.compare(strKR) == 0)
    {
        strDiff = "";
    }
    else
    {
        strDiff = "#########";
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("temp_KC[0]=%s,temp_KR[0]=%s %s"),strKC.GetString(),strKR.GetString(),strDiff.GetString());

    strKC=QString("%1").arg(temp_KC[1],8,16,QChar('0'));
    strKR=QString("%1").arg(temp_KR[1],8,16,QChar('0'));
    if(strKC.compare(strKR) == 0)
    {
        strDiff = "";
    }
    else
    {
        strDiff = "#########";
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("temp_KC[1]=%s,temp_KR[1]=%s %s"),strKC.GetString(),strKR.GetString(),strDiff.GetString());

    strKC=QString("%1").arg(temp_KC[2],8,16,QChar('0'));
    strKR=QString("%1").arg(temp_KR[2],8,16,QChar('0'));
    if(strKC.compare(strKR) == 0)
    {
        strDiff = "";
    }
    else
    {
        strDiff = "#########";
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("temp_KC[2]=%s,temp_KR[2]=%s %s"),strKC.GetString(),strKR.GetString(),strDiff.GetString());

    strKC=QString("%1").arg(temp_KC[3],8,16,QChar('0'));
    strKR=QString("%1").arg(temp_KR[3],8,16,QChar('0'));
    if(strKC.compare(strKR) == 0)
    {
        strDiff = "";
    }
    else
    {
        strDiff = "#########";
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("temp_KC[3]=%s,temp_KR[3]=%s %s"),strKC.GetString(),strKR.GetString(),strDiff.GetString());

    strKC=QString("%1").arg(temp_KC[4],8,16,QChar('0'));
    strKR=QString("%1").arg(temp_KR[4],8,16,QChar('0'));
    if(strKC.compare(strKR) == 0)
    {
        strDiff = "";
    }
    else
    {
        strDiff = "#########";
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("temp_KC[4]=%s,temp_KR[4]=%s %s"),strKC.GetString(),strKR.GetString(),strDiff.GetString());

    strKC=QString("%1").arg(temp_KC[5],8,16,QChar('0'));
    strKR=QString("%1").arg(temp_KR[5],8,16,QChar('0'));
    if(strKC.compare(strKR) == 0)
    {
        strDiff = "";
    }
    else
    {
        strDiff = "#########";
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("temp_KC[5]=%s,temp_KR[5]=%s %s"),strKC.GetString(),strKR.GetString(),strDiff.GetString());

    strKC=QString("%1").arg(temp_KC[6],8,16,QChar('0'));
    strKR=QString("%1").arg(temp_KR[6],8,16,QChar('0'));
    if(strKC.compare(strKR) == 0)
    {
        strDiff = "";
    }
    else
    {
        strDiff = "#########";
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("temp_KC[6]=%s,temp_KR[6]=%s %s"),strKC.GetString(),strKR.GetString(),strDiff.GetString());

    strKC=QString("%1").arg(temp_KC[7],8,16,QChar('0'));
    strKR=QString("%1").arg(temp_KR[7],8,16,QChar('0'));
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("temp_KC[7]=%s,temp_KR[7]=%s %s"),strKC.GetString(),strKR.GetString(),strDiff.GetString());

    strKC=QString("%1").arg(temp_KC[8],8,16,QChar('0'));
    strKR=QString("%1").arg(temp_KR[8],8,16,QChar('0'));
    if(strKC.compare(strKR) == 0)
    {
        strDiff = "";
    }
    else
    {
        strDiff = "#########";
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("temp_KC[8]=%s,temp_KR[8]=%s %s"),strKC.GetString(),strKR.GetString(),strDiff.GetString());

    strKC=QString("%1").arg(temp_KC[9],8,16,QChar('0'));
    strKR=QString("%1").arg(temp_KR[9],8,16,QChar('0'));
    if(strKC.compare(strKR) == 0)
    {
        strDiff = "";
    }
    else
    {
        strDiff = "#########";
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("temp_KC[9]=%s,temp_KR[9]=%s %s"),strKC.GetString(),strKR.GetString(),strDiff.GetString());

    strKC=QString("%1").arg(temp_KC[10],8,16,QChar('0'));
    strKR=QString("%1").arg(temp_KR[10],8,16,QChar('0'));
    if(strKC.compare(strKR) == 0)
    {
        strDiff = "";
    }
    else
    {
        strDiff = "#########";
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("temp_KC[10]=%s,temp_KR[10]=%s %s"),strKC.GetString(),strKR.GetString(),strDiff.GetString());

    strKC=QString("%1").arg(temp_KC[11],8,16,QChar('0'));
    strKR=QString("%1").arg(temp_KR[11],8,16,QChar('0'));
    if(strKC.compare(strKR) == 0)
    {
        strDiff = "";
    }
    else
    {
        strDiff = "#########";
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("temp_KC[11]=%s,temp_KR[11]=%s %s"),strKC.GetString(),strKR.GetString(),strDiff.GetString());
}

void CSttDevicePIK100::tmt_to_drv_pik100(void *pVoidTmt)
{
    StateFlagReady = 0;
    pTmt=(tmt_Pik100Test *)pVoidTmt;
    Print_Para(pTmt->m_oPik100Para.m_oDA);
    SttStateStart = pTmt->m_oPik100Para.m_oDA.StateStart;
    nStopTestAfterCheck = pTmt->m_oPik100Para.m_oDA.nStopTestAfterCheck;
    SttStateReadyFlag = 0;
    if(SttStateStart ==1)
    {
        KC1_42State[0] = pTmt->m_oPik100Para.m_oDA.K1;
        KC1_42State[1] = pTmt->m_oPik100Para.m_oDA.K2;
        KC1_42State[2] = pTmt->m_oPik100Para.m_oDA.K3;
        KC1_42State[3] = pTmt->m_oPik100Para.m_oDA.K4;
        KC1_42State[4] = pTmt->m_oPik100Para.m_oDA.K5;
        KC1_42State[5] = pTmt->m_oPik100Para.m_oDA.K6;
        KC1_42State[6] = pTmt->m_oPik100Para.m_oDA.K7;
        KC1_42State[7] = pTmt->m_oPik100Para.m_oDA.K8;
        KC1_42State[8] = pTmt->m_oPik100Para.m_oDA.K9;
        KC1_42State[9] = pTmt->m_oPik100Para.m_oDA.K10;
        KC1_42State[10] = pTmt->m_oPik100Para.m_oDA.K11;
        KC1_42State[11] = pTmt->m_oPik100Para.m_oDA.K12;
        KC1_42State[12] = pTmt->m_oPik100Para.m_oDA.K13;
        KC1_42State[13] = pTmt->m_oPik100Para.m_oDA.K14;
        KC1_42State[14] = pTmt->m_oPik100Para.m_oDA.K15;
        KC1_42State[15] = pTmt->m_oPik100Para.m_oDA.K16;
        KC1_42State[16] = pTmt->m_oPik100Para.m_oDA.K17;
        KC1_42State[17] = pTmt->m_oPik100Para.m_oDA.K18;
        KC1_42State[18] = pTmt->m_oPik100Para.m_oDA.K19;
        KC1_42State[19] = pTmt->m_oPik100Para.m_oDA.K20;
        KC1_42State[20] = pTmt->m_oPik100Para.m_oDA.K21;
        KC1_42State[21] = pTmt->m_oPik100Para.m_oDA.K22;
        KC1_42State[22] = pTmt->m_oPik100Para.m_oDA.K23;
        KC1_42State[23] = pTmt->m_oPik100Para.m_oDA.K24;
        KC1_42State[24] = pTmt->m_oPik100Para.m_oDA.K25;
        KC1_42State[25] = pTmt->m_oPik100Para.m_oDA.K26;
        KC1_42State[26] = pTmt->m_oPik100Para.m_oDA.K27;
        KC1_42State[27] = pTmt->m_oPik100Para.m_oDA.K28;
        KC1_42State[28] = pTmt->m_oPik100Para.m_oDA.K29;
        KC1_42State[29] = pTmt->m_oPik100Para.m_oDA.K30;
        KC1_42State[30] = pTmt->m_oPik100Para.m_oDA.K31;
        KC1_42State[31] = pTmt->m_oPik100Para.m_oDA.K32;
        KC1_42State[32] = pTmt->m_oPik100Para.m_oDA.K33;
        KC1_42State[33] = pTmt->m_oPik100Para.m_oDA.K34;
        KC1_42State[34] = pTmt->m_oPik100Para.m_oDA.K35;
        KC1_42State[35] = pTmt->m_oPik100Para.m_oDA.K36;
        KC1_42State[36] = pTmt->m_oPik100Para.m_oDA.K37;
        KC1_42State[37] = pTmt->m_oPik100Para.m_oDA.K38;
        KC1_42State[38] = pTmt->m_oPik100Para.m_oDA.K39;
        KC1_42State[39] = pTmt->m_oPik100Para.m_oDA.K40;
        KC1_42State[40] = pTmt->m_oPik100Para.m_oDA.K41;
        KC1_42State[41] = pTmt->m_oPik100Para.m_oDA.K42;

        FPGA0x10c = pTmt->m_oPik100Para.m_oDA.Addr010c;
        CountCtrlFlag = pTmt->m_oPik100Para.m_oDA.CountFlag;
        nDelayTime = pTmt->m_oPik100Para.m_oDA.nDelayTime;
        CountNO =0;
        /* 24V;24VGND;   48V;48VGND;   220V;220VGND;   500V;500VGND
        1A;1AGND   Vsense；VsenseGND     Isense；IsenseGND     KR；KRGND
    quint32 FPGA0x100;//[95:64]
    quint32 FPGA0x101;//[63:32]
    quint32 FPGA0x102;//[31:0]

    quint32 FPGA0x103;//[95:64]
    quint32 FPGA0x104;//[63:32]
    quint32 FPGA0x105;//[31:0]

    quint32 FPGA0x106;//[95:64]
    quint32 FPGA0x107;//[63:32]
    quint32 FPGA0x108;//[31:0]

    quint32 FPGA0x109;//[95:64]
    quint32 FPGA0x10a;//[63:32]
    quint32 FPGA0x10b;//[31:0]
    quint32 FPGA0x10c;//[12:0]*/
        for(int i =0;i<42;i++)
        {
            switch (KC1_42State[i]) {
            case 0: //close all
                if(i<32)
                {
                    FPGA0x10b &= ~(BIT0<<(i));
                    FPGA0x108 &= ~(BIT0<<(i));
                    FPGA0x105 &= ~(BIT0<<(i));
                    FPGA0x102 &= ~(BIT0<<(i));
                }
                else
                {
                    FPGA0x10a &= ~(BIT0<<(i-32));
                    FPGA0x107 &= ~(BIT0<<(i-32));
                    FPGA0x104 &= ~(BIT0<<(i-32));
                    FPGA0x101 &= ~(BIT0<<(i-32));
                }
                if(i<16)
                {
                    FPGA0x10a &= ~(BIT16<<(i));
                    FPGA0x107 &= ~(BIT16<<(i));
                    FPGA0x104 &= ~(BIT16<<(i));
                    FPGA0x101 &= ~(BIT16<<(i));
                }
                else
                {
                    FPGA0x109 &= ~(BIT0<<(i-16));
                    FPGA0x106 &= ~(BIT0<<(i-16));
                    FPGA0x103 &= ~(BIT0<<(i-16));
                    FPGA0x100 &= ~(BIT0<<(i-16));
                }

                //				FPGA0x100 = 0;//[95:64]
                //				FPGA0x101 = 0;//[63:32]
                //				FPGA0x102 = 0;//[31:0]
                //				FPGA0x103 = 0;//[95:64]
                //				FPGA0x104 = 0;//[63:32]
                //				FPGA0x105 = 0;//[31:0]
                //				FPGA0x106 = 0;//[95:64]
                //				FPGA0x107 = 0;//[63:32]
                //				FPGA0x108 = 0;//[31:0]
                //				FPGA0x109 = 0;//[95:64]
                //				FPGA0x10a = 0;//[63:32]
                //				FPGA0x10b = 0;//[31:0]
                //				FPGA0x10c = 0;//[12:0]
                break;
            case 1: //24V
                if(i<32)
                {
                    FPGA0x109 |= BIT29;
                    FPGA0x10b |= (BIT0<<(i));
                }
                else
                {
                    FPGA0x109 |= BIT29;
                    FPGA0x10a |= (BIT0<<(i-32));
                }

                break;
            case 2:  //24VGND
                if(i<16)
                {
                    FPGA0x109 |= BIT29;
                    FPGA0x10a |= (BIT16<<(i));
                }
                else
                {
                    FPGA0x109 |= BIT29;
                    FPGA0x109 |= (BIT0<<(i-16));
                }

                break;
            case 3:// 48V
                if(i<32)
                {
                    FPGA0x109 |= BIT29 + BIT30;
                    FPGA0x10b |= (BIT0<<(i));
                }
                else
                {
                    FPGA0x109 |= BIT29 + BIT30;
                    FPGA0x10a |= (BIT0<<(i-32));
                }
                break;
            case 4:   //48VGND
                if(i<16)
                {
                    FPGA0x109 |= BIT29 + BIT30;
                    FPGA0x10a |= (BIT16<<(i));
                }
                else
                {
                    FPGA0x109 |= BIT29 + BIT30;
                    FPGA0x109 |= (BIT0<<(i-16));
                }
                break;
            case 5:  //220V
                if(i<32)
                {
                    FPGA0x106 |= BIT29;
                    FPGA0x108 |= (BIT0<<(i));
                }
                else
                {
                    FPGA0x106 |= BIT29;
                    FPGA0x107 |= (BIT0<<(i-32));
                }
                break;
            case 6:  //220VGND
                if(i<16)
                {
                    FPGA0x106 |= BIT29;
                    FPGA0x107 |= (BIT16<<(i));
                }
                else
                {
                    FPGA0x106 |= BIT29;
                    FPGA0x106 |= (BIT0<<(i-16));
                }
                break;
            case 7:  //500V
                if(i<32)
                {
                    FPGA0x106 |= BIT29 + BIT30;
                    FPGA0x108 |= (BIT0<<(i));
                }
                else
                {
                    FPGA0x106 |= BIT29 + BIT30;
                    FPGA0x107 |= (BIT0<<(i-32));
                }
                break;
            case 8:  //500VGND
                if(i<16)
                {
                    FPGA0x106 |= BIT29 + BIT30;
                    FPGA0x107 |= (BIT16<<(i));
                }
                else
                {
                    FPGA0x106 |= BIT29 + BIT30;
                    FPGA0x106 |= (BIT0<<(i-16));
                }
                break;
            case 9: //1A
                if(i<32)
                {
                    FPGA0x103 |= BIT29;
                    FPGA0x105 |= (BIT0<<(i));
                }
                else
                {
                    FPGA0x103 |= BIT29;
                    FPGA0x104 |= (BIT0<<(i-32));
                }
                break;
            case 10:// 1AGND
                if(i<16)
                {
                    FPGA0x103 |= BIT29;
                    FPGA0x104 |= (BIT16<<(i));
                }
                else
                {
                    FPGA0x103 |= BIT29;
                    FPGA0x103 |= (BIT0<<(i-16));
                }
                break;
            case 11: //KR1；
                if(i<32)
                {
                    FPGA0x100 |= BIT26;
                    FPGA0x102 |= (BIT0<<(i));
                }
                else
                {
                    FPGA0x100 |= BIT26;
                    FPGA0x101 |= (BIT0<<(i-32));
                }
                break;
            case 12:  //KR1GND
                if(i<16)
                {
                    FPGA0x100 |= BIT26;
                    FPGA0x101 |= (BIT16<<(i));
                }
                else
                {
                    FPGA0x100 |= BIT26;
                    FPGA0x100 |= (BIT0<<(i-16));
                }
                break;
            case 13: //KR2；
                if(i<32)
                {
                    FPGA0x103 |= BIT26;
                    FPGA0x105 |= (BIT0<<(i));
                }
                else
                {
                    FPGA0x103 |= BIT26;
                    FPGA0x104 |= (BIT0<<(i-32));
                }
                break;
            case 14:   //KR2GND
                if(i<16)
                {
                    FPGA0x103 |= BIT26;
                    FPGA0x104 |= (BIT16<<(i));
                }
                else
                {
                    FPGA0x103 |= BIT26;
                    FPGA0x103 |= (BIT0<<(i-16));
                }
                break;
            case 15:  //KR3；
                if(i<32)
                {
                    FPGA0x106 |= BIT26;
                    FPGA0x108 |= (BIT0<<(i));
                }
                else
                {
                    FPGA0x106 |= BIT26;
                    FPGA0x107 |= (BIT0<<(i-32));
                }
                break;
            case 16:   //KR3GND
                if(i<16)
                {
                    FPGA0x106 |= BIT26;
                    FPGA0x107 |= (BIT16<<(i));
                }
                else
                {
                    FPGA0x106 |= BIT26;
                    FPGA0x106 |= (BIT0<<(i-16));
                }
                break;
            case 17:  //KR4；
                if(i<32)
                {
                    FPGA0x109 |= BIT26;
                    FPGA0x10b |= (BIT0<<(i));
                }
                else
                {
                    FPGA0x109 |= BIT26;
                    FPGA0x10a |= (BIT0<<(i-32));
                }
                break;
            case 18:   //KR4GND
                if(i<16)
                {
                    FPGA0x109 |= BIT26;
                    FPGA0x10a |= (BIT16<<(i));
                }
                else
                {
                    FPGA0x109 |= BIT26;
                    FPGA0x109 |= (BIT0<<(i-16));
                }
                break;
            default:
                break;
            }
        }
        if(pTmt->m_oPik100Para.m_oDA.VsenseFlag)
        {
            //Vsense；
            FPGA0x103 |= BIT27;
        }
        else
        {
            FPGA0x103 &= ~BIT27;
        }
        if(pTmt->m_oPik100Para.m_oDA.V24VIsenseFlag==1)//0:close;1:24V;2:220V
        {
            //24VIsense；
            FPGA0x109 |= BIT28;
            FPGA0x106 &= ~BIT28;
        }
        else if(pTmt->m_oPik100Para.m_oDA.V24VIsenseFlag==2)
        {

            //220VIsense；
            FPGA0x106 |= BIT28;
            FPGA0x109 &= ~BIT28;
        }
        else
        {
            FPGA0x109 &= ~BIT28;
            FPGA0x106 &= ~BIT28;
        }
        FPGA0x100  |= BIT31;
        FPGA0x101 |= BIT10+BIT11+BIT12+BIT13+BIT14+BIT15;
        FPGA0x103  |= BIT31;
        FPGA0x104 |= BIT10+BIT11+BIT12+BIT13+BIT14+BIT15;
        FPGA0x106  |= BIT31;
        FPGA0x107 |= BIT10+BIT11+BIT12+BIT13+BIT14+BIT15;
        FPGA0x109  |= BIT31;
        FPGA0x10a |= BIT10+BIT11+BIT12+BIT13+BIT14+BIT15;
        //		qDebug()<<"FPGA0x100="<<QString::number(FPGA0x100,16);
        temp_KC[0] = FPGA0x100;
        SENDAtoFPGA(FPGA0x100,0x100);
        //		qDebug()<<"FPGA0x101="<<QString::number(FPGA0x101,16);
        temp_KC[1] = FPGA0x101;
        SENDAtoFPGA(FPGA0x101,0x101);
        //		qDebug()<<"FPGA0x102="<<QString::number(FPGA0x102,16);
        temp_KC[2] = FPGA0x102;
        SENDAtoFPGA(FPGA0x102,0x102);
        //		qDebug()<<"FPGA0x103="<<QString::number(FPGA0x103,16);
        temp_KC[3] = FPGA0x103;
        SENDAtoFPGA(FPGA0x103,0x103);
        //		qDebug()<<"FPGA0x104="<<QString::number(FPGA0x104,16);
        temp_KC[4] = FPGA0x104;
        SENDAtoFPGA(FPGA0x104,0x104);
        //		qDebug()<<"FPGA0x105="<<QString::number(FPGA0x105,16);
        temp_KC[5] = FPGA0x105;
        SENDAtoFPGA(FPGA0x105,0x105);
        //		qDebug()<<"FPGA0x106="<<QString::number(FPGA0x106,16);
        temp_KC[6] = FPGA0x106;
        SENDAtoFPGA(FPGA0x106,0x106);
        //		qDebug()<<"FPGA0x107="<<QString::number(FPGA0x107,16);
        temp_KC[7] = FPGA0x107;
        SENDAtoFPGA(FPGA0x107,0x107);
        //		qDebug()<<"FPGA0x108="<<QString::number(FPGA0x108,16);
        temp_KC[8] = FPGA0x108;
        SENDAtoFPGA(FPGA0x108,0x108);
        //		qDebug()<<"FPGA0x109="<<QString::number(FPGA0x109,16);
        temp_KC[9] = FPGA0x109;
        SENDAtoFPGA(FPGA0x109,0x109);
        //		qDebug()<<"FPGA0x10a="<<QString::number(FPGA0x10a,16);
        temp_KC[10] = FPGA0x10a;
        SENDAtoFPGA(FPGA0x10a,0x10a);
        //		qDebug()<<"FPGA0x10b="<<QString::number(FPGA0x10b,16);
        temp_KC[11] = FPGA0x10b;
        SENDAtoFPGA(FPGA0x10b,0x10b);
        //		qDebug()<<"FPGA0x10c="<<QString::number(FPGA0x10c,16);
        temp_KC[12] = FPGA0x10c;
        SENDAtoFPGA(FPGA0x10c,0x10c);

    }

    //利用m_nCommfd给驱动下发参数,write(m_nCommfd,,)
}

void CSttDevicePIK100::ProPik100DrvResult()
{
    int AlarmTemp;
    int UTCtimeNowS ;
    int inter_flag =ioctl(m_nCommfd,0x110,0);
    //    if(inter_flag != 1)
    //    {qDebug()<<"----inter_flag-----"<<QString::number(inter_flag);}
    //	qDebug()<<"----inter_flag-----"<<QString::number(inter_flag);
    switch(inter_flag)
    {
    case 0 ://不使用流控制

        //        qDebug()<<QString::number(a,16);
        break;
    case 1 ://
        break;
    default:
        break;

    }
    //PIS2K实验下驱动上报中断的处理入口
    //ioctl(m_nCommfd,,0),read(m_nCommfd,,0)a

    //	long nRealTimeEventCount=0;
    //	for(int nChanIndex=0;nChanIndex<40;nChanIndex++)
    //	{
    //		int nBiValue=0;
    //		stt_add_test_event(Result_Type_Bin, -1, -1, nChanIndex+1, nBiValue, 0, 0);
    //		nRealTimeEventCount++;
    //	}
    //	if (nRealTimeEventCount > 0)
    //	{
    //		CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
    //		pSttTestBase->ReturnRealTimeEvent();
    //	}



}

BOOL CSttDevicePIK100::OnTimer(BOOL bExec)
{
    if(!bExec)
    {
        m_nDeviceOnTimerCount++;
        if(m_nDeviceOnTimerCount*m_nOnTimerMs < m_nDeviceOnTimerMs)
        {
            return FALSE;
        }
        m_nDeviceOnTimerCount=0;
    }

    if(SttStateStart ==1)
    {
        SttStateReadyFlag++;
        if(SttStateReadyFlag > 1)
        {
            temp_KR[0] = 0x202;
            READformHEX(temp_KR,22);
            qDebug()<<"-----------------------"<<QString::number(temp_KR[0],16);
            temp_KR[0]  |= BIT31;

            temp_KR[1] = 0x203;   //
            READformHEX(temp_KR+1,0x200);
            temp_KR[1] |= BIT10+BIT11+BIT12+BIT13+BIT14+BIT15;

            temp_KR[2] = 0x204;   //
            READformHEX(temp_KR+2,0x201);


            temp_KR[3] = 0x205;   //
            READformHEX(temp_KR+3,0x202);
            temp_KR[3]  |= BIT31;


            temp_KR[4] = 0x206;   //
            READformHEX(temp_KR+4,0x203);
            temp_KR[4] |= BIT10+BIT11+BIT12+BIT13+BIT14+BIT15;

            temp_KR[5] = 0x207;   //
            READformHEX(temp_KR+5,0x204);

            temp_KR[6] = 0x208;   //
            READformHEX(temp_KR+6,0x205);
            temp_KR[6]  |= BIT31;

            temp_KR[7] = 0x209;   //
            READformHEX(temp_KR+7,0x206);
            temp_KR[7]  |= BIT10+BIT11+BIT12+BIT13+BIT14+BIT15;

            temp_KR[8] = 0x20a;   //
            READformHEX(temp_KR+8,0x207);

            temp_KR[9] = 0x20b;   //
            READformHEX(temp_KR+9,0x208);
            temp_KR[9]  |= BIT31;

            temp_KR[10] = 0x20c;   //
            READformHEX(temp_KR+10,0x209);
            temp_KR[10] |= BIT10+BIT11+BIT12+BIT13+BIT14+BIT15;

            temp_KR[11] = 0x20d;   //
            READformHEX(temp_KR+11,0x20a);

            temp_KR[12] = 0x20e;   //
            READformHEX(temp_KR+12,0x20b);

            Print_KCKR();
            for(int i = 0;i<12;i++)
            {
                if(temp_KR[i]  == temp_KC[i])
                {
                    StateFlagReady++;
                }
            }

            if(StateFlagReady == 12)
            {
                if(nDelayTime < 0)
                {
                    nDelayTime = 0;
                }
                if(nDelayTime > 5)
                {
                    nDelayTime = 5;
                }
                Sleep(nDelayTime*1000);
                CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
                pSttTestBase->ReturnTestStateEvent_TestFinish(0,0,FALSE);
            }
            else
            {
                if(nStopTestAfterCheck)
                {
                    /***********************************************************************************/
                    CSttTestServerBase *pSttTestServerBase=CSttTestServerBase::GetServerEngine();
                    pSttTestServerBase->StopAutoTestEvent();
                    /***********************************************************************************/
                }
                else
                {
                    //调试模式
                    if(pTmt != NULL)
                    {
                        pTmt->m_oPik100Result.m_nResUseful = 1;
                        for(int i = 0 ;i<12;i++)
                        {
                            pTmt->m_oPik100Result.m_nKR[i] = temp_KR[i];
                            pTmt->m_oPik100Result.m_nKC[i] = temp_KC[i];
                        }

                        CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
                        pSttTestBase->ReturnTestStateEvent_TestFinish(0,0,FALSE);
                    }
                }
            }

            SttStateStart = 0;
            StateFlagReady = 0;
        }
    }

    temp_KR[12] = 0x20e;   //
    READformHEX(temp_KR+12,0x20b);
    //	qDebug()<<"temp_KR="<<12<<QString::number(temp_KR[12],16);//temp_KR[12]0x0000_020e 开入量[4:0]={插件1，插件2，插件3，插件4，暂停}
    if(CountCtrlFlag==0)
    {
        int nKIndex[5]={1,2,3,4,5};
        int nKValue[5]={0,0,0,0,0};//1闭合 0断开
        nKValue[0] = temp_KR[12] & BIT0;
        nKValue[1] = (temp_KR[12] & BIT1)>>1;
        nKValue[2] = (temp_KR[12] & BIT2)>>2;
        nKValue[3] = (temp_KR[12] & BIT3)>>3;
        nKValue[4] = (temp_KR[12] & BIT4)>>4;
        STT_TEST_EVENT obufEvent;
        obufEvent.nEventInfoCnt=5;
        obufEvent.oTime.dTime=0;
        obufEvent.oTime.dRealTime=0;
        obufEvent.oTime.dBinActTime=-1;

        for(int nEventIndex=0;nEventIndex<5;nEventIndex++)
        {
            obufEvent.oEventInfo[nEventIndex].nType=SttResult_Type_BinEx;
            obufEvent.oEventInfo[nEventIndex].nStateIndex=-1;
            obufEvent.oEventInfo[nEventIndex].nStepIndex=-1;

            obufEvent.oEventInfo[nEventIndex].nChannel=nKIndex[nEventIndex];
            obufEvent.oEventInfo[nEventIndex].nValue=nKValue[nEventIndex];
        }

        stt_add_test_event(obufEvent);
        //		stt_add_test_event(SttResult_Type_BinEx, -1, -1, nKIndex[0], nKValue[0], 0, 0);//"BinEx001"
        //		stt_add_test_event(SttResult_Type_BinEx, -1, -1, nKIndex[1], nKValue[1], 0, 0);//"BinEx002"
        //		stt_add_test_event(SttResult_Type_BinEx, -1, -1, nKIndex[2], nKValue[2], 0, 0);//"BinEx003"
        //		stt_add_test_event(SttResult_Type_BinEx, -1, -1, nKIndex[3], nKValue[3], 0, 0);//"BinEx004"
        //		stt_add_test_event(SttResult_Type_BinEx, -1, -1, nKIndex[4], nKValue[4], 0, 0);//"BinEx005"
        CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
        pSttTestBase->ReturnRealTimeEvent();
    }

    //	//系统秒定时器处理入口
    return FALSE;
}

int CSttDevicePIK100::SENDAtoFPGA(quint32 VALUE,int ADDR)
{
    quint32 VALUEtemp[1];
    VALUEtemp[0] = VALUE;
    write(m_nCommfd,VALUEtemp,ADDR);
    //    VALUE = chPara[0]+chPara[1]*256+chPara[2]*256*256;
    return VALUEtemp[0];
}

void CSttDevicePIK100::READformHEX(quint32 *VALUE,int ADDR)
{
    read(m_nCommfd,VALUE,ADDR);
}

void CSttDevicePIK100::SetTestStop(BOOL bIsSysDefaultOutput)
{
    if(bIsSysDefaultOutput)
    {
        //		ioctl(m_nfd, 0x136, 0);
        qDebug()<<"----EventProcessAUDCOUT-----";
    }
    else
    {
        qDebug()<<"----EventProcessAUDCSTOP~~~~~~~~~~";
        FPGA0x100=0;//[95:64]
        FPGA0x101=0;//[63:32]
        FPGA0x102=0;//[31:0]
        FPGA0x103=0;//[95:64]
        FPGA0x104=0;//[63:32]
        FPGA0x105=0;//[31:0]
        FPGA0x106=0;//[95:64]
        FPGA0x107=0;//[63:32]
        FPGA0x108=0;//[31:0]
        FPGA0x109=0;//[95:64]
        FPGA0x10a=0;//[63:32]
        FPGA0x10b=0;//[31:0]
        FPGA0x10c=0;//[12:0]
        memset(KC1_42State, 0, sizeof(KC1_42State));
        memset(temp_KC, 0, sizeof(temp_KC));
        int Statetemp=0;
        SENDAtoFPGA(Statetemp,0x100);
        SENDAtoFPGA(Statetemp,0x101);
        SENDAtoFPGA(Statetemp,0x102);
        SENDAtoFPGA(Statetemp,0x103);
        SENDAtoFPGA(Statetemp,0x104);
        SENDAtoFPGA(Statetemp,0x105);
        SENDAtoFPGA(Statetemp,0x106);
        SENDAtoFPGA(Statetemp,0x107);
        SENDAtoFPGA(Statetemp,0x108);
        SENDAtoFPGA(Statetemp,0x109);
        SENDAtoFPGA(Statetemp,0x10a);
        SENDAtoFPGA(Statetemp,0x10b);
        SENDAtoFPGA(Statetemp,0x10c);
    }
}
