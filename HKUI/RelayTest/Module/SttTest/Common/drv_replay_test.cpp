#include "drv_replay_test.h"
#include"../../SttDevice/SttDriverOper.h"
#include "../../SttDevice/SttDeviceBase.h"

void GetVolReplayCoef(int nChannel,int nModuleUIndex, drv_LtReplayCoefItem *item, int nHarm = 0)
{
    float fAmp = 0;
    if(g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]==NULL)
        return ;

    float fChMax=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]->m_oModuleAttr.m_fChMax;
    fAmp=fChMax;

    float fVoltMax=stt_adj_get_ac_max(fAmp,nModuleUIndex,STT_MODULE_TYPE_VOLT);

    if(fVoltMax<0.001)
    {
        return ;
    }

    float fTemperature=0;//getTemperature();
    PSTT_ADJUST_ITEM pAdjItem=stt_adj_get_ac_u(fAmp,nModuleUIndex,nChannel,fTemperature,nHarm);
    item->fCoef = pAdjItem->m_fCoef;//幅值系数
    item->fZero = pAdjItem->m_fZero;//交流零漂
    item->fMaxValue = fVoltMax*1.414;
    item->fReverse = 1.0;
}

void  GetCurReplayCoef(int nChannel,int nModuleIIndex, drv_LtReplayCoefItem *item, int nHarm = 0)
{
    float fAmp = 0;
    if(g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex]==NULL)
        return ;

    float fChMax=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex]->m_oModuleAttr.m_fChMax;
    fAmp = fChMax;

    float fCurrentMax = stt_adj_get_ac_max(fAmp,nModuleIIndex,STT_MODULE_TYPE_CURRENT);

    if(fCurrentMax<0.001)
    {
        return ;
    }

    float fTemperature=0;//getTemperature();
    PSTT_ADJUST_ITEM pAdjItem=stt_adj_get_ac_i(fAmp,nModuleIIndex,nChannel,fTemperature,nHarm);
    item->fCoef = pAdjItem->m_fCoef;//幅值系数
    item->fZero = pAdjItem->m_fZero;//交流零漂
    item->fMaxValue = fCurrentMax*1.414;
    item->fReverse = -1.0;
}
void tmt_to_drv(tmt_ReplayTest *pReplayPara, drv_structLtReplayParam *pDrvPara, drv_LtReplayCoef *Coef)
{
   memset(pDrvPara, 0, sizeof(drv_structLtReplayParam));
   pDrvPara->freq = 1000;
   pDrvPara->startType = 0;
   switch(pReplayPara->m_nTripType)
   {
   case 0: // 无触发
       pDrvPara->degressType = 0; //设置无触发
       pDrvPara->tripLoopCount = pReplayPara->m_nStartCycleNum; //设置触发计数器
       break;
   case 1: // 手动触发
       pDrvPara->degressType = 0x80000000; //设置触发
       pDrvPara->tripLoopCount = 0;
       pDrvPara->tripType = 1; // 手动
       pDrvPara->modeAfterTrip = pReplayPara->m_nTrigAfterMode;
       break;
   case 2: // GPS触发
       pDrvPara->degressType = 0x80000000; //设置触发
       pDrvPara->tripLoopCount = 0;
       pDrvPara->tripType = 3; // GPS触发
       pDrvPara->tripgpsnSec = pReplayPara->m_nTrigTimeNS;
       pDrvPara->tripgpsSec = pReplayPara->m_nTrigTimeS;
       pDrvPara->modeAfterTrip = pReplayPara->m_nTrigAfterMode;
       break;
   case 3: // bi(开入)
       {
           pDrvPara->degressType = 0x80000000; //设置触发
           pDrvPara->tripLoopCount = 0;
           pDrvPara->tripType = 2; // bi(开入)
           pDrvPara->stBITrip.nBiLogic = pReplayPara->m_nBinLogic;
           int i = 0;
           pDrvPara->stBITrip.oValid.nModuleCount = 1;
           pDrvPara->stBITrip.oValid.item[0].nModule = 0x8000;
           for(i = 0; i < MAX_BINARYIN_COUNT; i++)
           {
               if(pReplayPara->m_binIn[i].nSelect)
               {
                   pDrvPara->stBITrip.nBiRef = pReplayPara->m_binIn[i].nTrigMode;
                   pDrvPara->stBITrip.oValid.item[0].nVal1 |= (0x01<<i);
               }
           }
           pDrvPara->modeAfterTrip = pReplayPara->m_nTrigAfterMode;
       }
       break;
   }
   pDrvPara->moduleCount = pReplayPara->GetModuleSelCount();
   for (int i=0; i<pReplayPara->m_nModuleCount; i++)
   {
       if (pReplayPara->m_oModule[i].m_nSel != 0)
       {
           pDrvPara->module |= (1<<pReplayPara->m_oModule[i].m_nIndex);
       }
   }
   int nModuleUIndex = 0;
   int nModuleIIndex = 0;
   for (int i=0; i<pReplayPara->m_nModuleCount; i++)
   {
       int nModuleIndex = pReplayPara->m_oModule[i].m_nIndex;
       for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount; i++)
       {
           if(g_theDeviceSystemParameter->m_oModules[i].m_oModuleAttr.m_nModuleIndex == (nModuleIndex + 1))
           {
               if(g_theDeviceSystemParameter->m_oModules[i].m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_VOLT) // 电压
               {
                   for(int k=0; k<CHANNEL_MAX ; k++)
                   {
                       Coef->Item[nModuleIndex][k].nCh = g_theDeviceSystemParameter->m_oModules_U[0]->m_nChDrvPos[k];
                       GetVolReplayCoef(k,nModuleUIndex, &Coef->Item[nModuleIndex][k]);
                   }
                   nModuleUIndex++;
               } else if (g_theDeviceSystemParameter->m_oModules[i].m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_CURRENT) // 电流
               {
                   for(int k=0; k<CHANNEL_MAX ; k++)
                   {
                       Coef->Item[nModuleIndex][k].nCh = g_theDeviceSystemParameter->m_oModules_I[0]->m_nChDrvPos[k];
                       GetCurReplayCoef(k,nModuleIIndex, &Coef->Item[nModuleIndex][k]);
                   }
                   nModuleIIndex++;
               }
           }
       }
   }
//   for(int i = 0; i < MAX_MODULE_COUNT; i++)
//   {
//       for(int j = 0; j < CHANNEL_MAX; j++)
//         CLogPrint::g_pLogPrint->LogFormatString(XLOGLEVEL_INFOR, "[%d][%d]coef = %f , fZero = %f, nCh = %d, Max= %f ,dir = %f", i , j, Coef->Item[i][j].fCoef\
//                                                 , Coef->Item[i][j].fZero, Coef->Item[i][j].nCh , Coef->Item[i][j].fMaxValue, Coef->Item[i][j].fReverse);
//   }

}
