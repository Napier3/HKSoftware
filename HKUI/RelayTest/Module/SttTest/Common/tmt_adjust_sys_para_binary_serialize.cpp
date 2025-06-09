#include "stdafx.h"
#include "tmt_adjust_sys_para_binary_serialize.h"
#include "../../../../Module/BaseClass/BinarySerialBuffer.h"
/*
 * lijunqing 2020-12-28
	之后版本兼容的问题，参见头文件的说明:

//2020-12-27  LIJUNQING  后续如果结构体增加数据，则递增版本号
//g_dwSttAdjSysParaCurrVersion表示当前最新的版本号
//二进制文件向老版本兼容，所以必须得增加版本控制
//老版本软件兼容新版本文件的方法：
//    新增加的数据，永远都在之前版本的后面写入，这样就能够保证老版本程序读取新版本的文件不出错

*/

//CBinarySerialBuffer
void stt_binary_serialize_AdjItem(PSTT_ADJUST_ITEM pPara,  CBinarySerialBuffer &oBinaryBuffer)
{
	if (oBinaryBuffer.IsCalSizeMode())
    {
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_fCoef);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_fZero);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_fAngle);
    }
	else if (oBinaryBuffer.IsWriteMode())
    {
		BinarySerializeWrite(oBinaryBuffer,pPara->m_fCoef);
		BinarySerializeWrite(oBinaryBuffer,pPara->m_fZero);
		BinarySerializeWrite(oBinaryBuffer,pPara->m_fAngle);
    }
	else if (oBinaryBuffer.IsReadMode())
    {
        BinarySerializeRead(oBinaryBuffer, pPara->m_fCoef);
        BinarySerializeRead(oBinaryBuffer, pPara->m_fZero);
        BinarySerializeRead(oBinaryBuffer, pPara->m_fAngle);
    }
    else
    {
    }
}

void stt_binary_serialize(PSTT_ADJUST_ITEM pPara,  CBinarySerialBuffer &oBinaryBuffer)
{
    stt_binary_serialize_AdjItem(pPara, oBinaryBuffer);
}

void stt_binary_serialize(PSTT_CHANNEL_GEAR_ADJUST pPara,  long nIndex, CBinarySerialBuffer &oBinaryBuffer)
{
	if (oBinaryBuffer.IsCalSizeMode())
    {
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_fGearValue);
    }
	else if (oBinaryBuffer.IsWriteMode())
    {
		BinarySerializeWrite(oBinaryBuffer,pPara->m_fGearValue);
    }
	else if (oBinaryBuffer.IsReadMode())
    {
        BinarySerializeRead(oBinaryBuffer, pPara->m_fGearValue);
    }
    else
    {
    }

    stt_binary_serialize(&pPara->m_oAdjItem, oBinaryBuffer);
}

void stt_binary_serialize(PSTT_CHANNEL_WAVE_ADJUST pPara,  CBinarySerialBuffer &oBinaryBuffer)
{
	if (oBinaryBuffer.IsCalSizeMode())
    {
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nGearCount);
    }
	else if (oBinaryBuffer.IsWriteMode())
    {
		BinarySerializeWrite(oBinaryBuffer,pPara->m_nGearCount);
    }
	else if (oBinaryBuffer.IsReadMode())
    {
        BinarySerializeRead(oBinaryBuffer, pPara->m_nGearCount);
    }
    else
    {
    }

    long nIndex = 0;

	for (nIndex=0; nIndex<pPara->m_nGearCount; nIndex++)
    {
        stt_binary_serialize(&pPara->m_oChGearAdj[nIndex], nIndex, oBinaryBuffer);
    }
}

void stt_binary_serialize(PSTT_CHANNEL_ADJUSTS pPara,  long nHarmCount, CBinarySerialBuffer &oBinaryBuffer)
{
	if (oBinaryBuffer.IsCalSizeMode())
    {
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_fDcZero[0]);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_fDcZero[1]);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_fDcZero[2]);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_fLargeCurrentRatio);
    }
	else if (oBinaryBuffer.IsWriteMode())
    {
        BinarySerializeWrite(oBinaryBuffer, pPara->m_fDcZero[0]);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_fDcZero[1]);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_fDcZero[2]);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_fLargeCurrentRatio);
    }
	else if (oBinaryBuffer.IsReadMode())
    {
        BinarySerializeRead(oBinaryBuffer, pPara->m_fDcZero[0]);
        BinarySerializeRead(oBinaryBuffer, pPara->m_fDcZero[1]);
        BinarySerializeRead(oBinaryBuffer, pPara->m_fDcZero[2]);
        BinarySerializeRead(oBinaryBuffer, pPara->m_fLargeCurrentRatio);
    }
    else
    {
    }

	if (oBinaryBuffer.IsReadMode())
        {
		if(pPara->m_pChWaveAdj!=NULL)
            free(pPara->m_pChWaveAdj);

		pPara->m_pChWaveAdj = (PSTT_CHANNEL_WAVE_ADJUST)malloc((nHarmCount+1)*sizeof(STT_CHANNEL_WAVE_ADJUST));
    }

    if(nHarmCount >= 1)
    {
        stt_binary_serialize(&pPara->m_pChWaveAdj[0], oBinaryBuffer);
        stt_binary_serialize(&pPara->m_pChWaveAdj[1], oBinaryBuffer);
    }

    long nIndex = 0;

	for (nIndex=2; nIndex<= nHarmCount; nIndex++)
    {
        stt_binary_serialize(&pPara->m_pChWaveAdj[nIndex], oBinaryBuffer);
    }
}

void stt_binary_serialize(PSTT_TRANGE_ADJUST pPara, long nHarmCount, CBinarySerialBuffer &oBinaryBuffer, long nChannelNum)
{
	if (oBinaryBuffer.IsCalSizeMode())
    {
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_fTemperature);
    }
	else if (oBinaryBuffer.IsWriteMode())
    {
		BinarySerializeWrite(oBinaryBuffer,pPara->m_fTemperature);
    }
	else if (oBinaryBuffer.IsReadMode())
    {
        BinarySerializeRead(oBinaryBuffer, pPara->m_fTemperature);
    }
    else
    {
    }

    stt_binary_serialize(&pPara->m_oChIdcAdj, oBinaryBuffer);
    stt_binary_serialize(&pPara->m_oChUdcAdj, oBinaryBuffer);

    if(oBinaryBuffer.IsReadMode())
    {
        //先释放原来的pPara->nChannelNum，再申请nChannelNum
        if(pPara->m_pChsAdjust != NULL)
        {
            for(long nChannel = 0; nChannel < pPara->nChannelNum; nChannel++)
            {
                if(pPara->m_pChsAdjust[nChannel].m_pChWaveAdj != NULL)
                {
                    free(pPara->m_pChsAdjust[nChannel].m_pChWaveAdj);
                }
            }

            free(pPara->m_pChsAdjust);
            pPara->m_pChsAdjust = NULL;
        }

        pPara->m_pChsAdjust = (PSTT_CHANNEL_ADJUSTS)malloc(nChannelNum * sizeof(STT_CHANNEL_ADJUSTS));
    }

    for(long nIndex = 0; nIndex < nChannelNum; nIndex++)
    {
        if(oBinaryBuffer.IsReadMode())
        {
            pPara->m_pChsAdjust[nIndex].init();
        }

        stt_binary_serialize(&pPara->m_pChsAdjust[nIndex], nHarmCount, oBinaryBuffer);
    }
}

void stt_binary_serialize(PSTT_MODULE_ADJUST  pPara,  CBinarySerialBuffer &oBinaryBuffer, long nChannelNum, long nHarmCount)
{
	if (oBinaryBuffer.IsCalSizeMode())
    {
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nTemperatureCount);
    }
	else if (oBinaryBuffer.IsWriteMode())
    {
		BinarySerializeWrite(oBinaryBuffer,pPara->m_nTemperatureCount);
    }
	else if (oBinaryBuffer.IsReadMode())
    {
        BinarySerializeRead(oBinaryBuffer, pPara->m_nTemperatureCount);
    }
    else
    {
    }

    long nIndex = 0;

	for (nIndex=0; nIndex < pPara->m_nTemperatureCount; nIndex++)
    {
        stt_binary_serialize(&pPara->m_oTempAdjust[nIndex], nHarmCount, oBinaryBuffer, nChannelNum);
    }
}

void stt_binary_serialize(PSTT_MODULE_CH_DEF  pPara, CBinarySerialBuffer &oBinaryBuffer)
{
	if (oBinaryBuffer.IsCalSizeMode())
    {
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_pszChId);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nChIndex);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nWorkMode);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nEeType);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nChRsIndex);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_fChACMaxValue);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_fChDCMaxValue);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nChMeasPos);
    }
	else if (oBinaryBuffer.IsWriteMode())
    {
        BinarySerializeWrite(oBinaryBuffer, pPara->m_pszChId);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nChIndex);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nWorkMode);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nEeType);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nChRsIndex);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_fChACMaxValue);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_fChDCMaxValue);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nChMeasPos);
    }
	else if (oBinaryBuffer.IsReadMode())
    {
        BinarySerializeRead(oBinaryBuffer, pPara->m_pszChId);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nChIndex);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nWorkMode);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nEeType);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nChRsIndex);
        BinarySerializeRead(oBinaryBuffer, pPara->m_fChACMaxValue);
        BinarySerializeRead(oBinaryBuffer, pPara->m_fChDCMaxValue);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nChMeasPos);
    }
    else
    {
    }
}

void stt_binary_serialize(PSTT_MODULE_CH_DEFS  pPara,  CBinarySerialBuffer &oBinaryBuffer, long nChannelNum)
{
    long nIndex = 0;

	for (nIndex=0; nIndex<nChannelNum; nIndex++)
    {
        stt_binary_serialize(&pPara->m_oChDef[nIndex], oBinaryBuffer);
    }
}

void stt_binary_serialize(PSTT_CH_DRV_POS  pPara,  CBinarySerialBuffer &oBinaryBuffer, long nChannelNum)
{
    if(oBinaryBuffer.IsCalSizeMode())
    {
        for(int nIndex = 0; nIndex < nChannelNum; nIndex++)
        {
            BinarySerializeCalLen(oBinaryBuffer, pPara->m_nChDrvPos[nIndex]);
        }
    }
    else if(oBinaryBuffer.IsWriteMode())
    {
        for(int nIndex = 0; nIndex < nChannelNum; nIndex++)
        {
            BinarySerializeWrite(oBinaryBuffer, pPara->m_nChDrvPos[nIndex]);
        }
    }
    else if(oBinaryBuffer.IsReadMode())
    {
        for(int nIndex = 0; nIndex < nChannelNum; nIndex++)
        {
            BinarySerializeRead(oBinaryBuffer, pPara->m_nChDrvPos[nIndex]);
        }
    }
    else
    {
    }
}

void stt_binary_serialize(PSTT_MODULE_CH_MAP_DEF  pPara,  CBinarySerialBuffer &oBinaryBuffer, long nChannelNum)
{
    stt_binary_serialize(&pPara->m_oChDefs, oBinaryBuffer, nChannelNum);
    stt_binary_serialize(&pPara->m_oChDrvPos, oBinaryBuffer, nChannelNum);
}

void stt_binary_serialize(PST_MODULE_ATTR  pPara,  CBinarySerialBuffer &oBinaryBuffer)
{
    if(oBinaryBuffer.IsCalSizeMode())
    {		
		BinarySerializeCalLen(oBinaryBuffer, pPara->m_dwVersion);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nModuleType);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_strModelName);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_strFactory);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_strDateProduce);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_strModuleSN);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nModuleIndex);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nFiberPortNum_LC);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nFiberPortNum_STSend);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nFiberPortNum_STRecv);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nChannelNum);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nHarmCount);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_fChMax);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_fChDcMax);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_fFreCoef);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_fDigitalDelay);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nModulePower);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nChMergeMode);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nSwitchIn[0]);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nSwitchIn[1]);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nSwitchIn[2]);
        BinarySerializeCalLen(oBinaryBuffer, pPara->m_nSwitchIn[3]);
		BinarySerializeCalLen(oBinaryBuffer, pPara->m_nChTypeChg);
		BinarySerializeCalLen(oBinaryBuffer, pPara->m_nSwitchIn[4]);
		BinarySerializeCalLen(oBinaryBuffer, pPara->m_nSwitchIn[5]);
		BinarySerializeCalLen(oBinaryBuffer, pPara->m_nSwitchIn[6]);
		BinarySerializeCalLen(oBinaryBuffer, pPara->m_nSwitchIn[7]);
		BinarySerializeCalLen(oBinaryBuffer, pPara->m_fDefChMax);
		BinarySerializeCalLen(oBinaryBuffer, pPara->m_fDefChDcMax);
		BinarySerializeCalLen(oBinaryBuffer, pPara->m_nDefChannelNum);
		BinarySerializeCalLen(oBinaryBuffer, pPara->m_nDAChanNum);
    }
	else if (oBinaryBuffer.IsWriteMode())
    {
		BinarySerializeWrite(oBinaryBuffer, pPara->m_dwVersion);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nModuleType);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_strModelName);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_strFactory);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_strDateProduce);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_strModuleSN);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nModuleIndex);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nFiberPortNum_LC);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nFiberPortNum_STSend);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nFiberPortNum_STRecv);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nChannelNum);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nHarmCount);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_fChMax);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_fChDcMax);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_fFreCoef);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_fDigitalDelay);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nModulePower);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nChMergeMode);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nSwitchIn[0]);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nSwitchIn[1]);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nSwitchIn[2]);
        BinarySerializeWrite(oBinaryBuffer, pPara->m_nSwitchIn[3]);
		BinarySerializeWrite(oBinaryBuffer, pPara->m_nChTypeChg);
		BinarySerializeWrite(oBinaryBuffer, pPara->m_nSwitchIn[4]);
		BinarySerializeWrite(oBinaryBuffer, pPara->m_nSwitchIn[5]);
		BinarySerializeWrite(oBinaryBuffer, pPara->m_nSwitchIn[6]);
		BinarySerializeWrite(oBinaryBuffer, pPara->m_nSwitchIn[7]);
		BinarySerializeWrite(oBinaryBuffer, pPara->m_fDefChMax);
		BinarySerializeWrite(oBinaryBuffer, pPara->m_fDefChDcMax);
		BinarySerializeWrite(oBinaryBuffer, pPara->m_nDefChannelNum);
		BinarySerializeWrite(oBinaryBuffer, pPara->m_nDAChanNum);
    }
	else if (oBinaryBuffer.IsReadMode())
    {
		BinarySerializeRead(oBinaryBuffer, pPara->m_dwVersion);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nModuleType);
        BinarySerializeRead(oBinaryBuffer, pPara->m_strModelName);
        BinarySerializeRead(oBinaryBuffer, pPara->m_strFactory);
        BinarySerializeRead(oBinaryBuffer, pPara->m_strDateProduce);
        BinarySerializeRead(oBinaryBuffer, pPara->m_strModuleSN);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nModuleIndex);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nFiberPortNum_LC);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nFiberPortNum_STSend);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nFiberPortNum_STRecv);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nChannelNum);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nHarmCount);
        BinarySerializeRead(oBinaryBuffer, pPara->m_fChMax);
        BinarySerializeRead(oBinaryBuffer, pPara->m_fChDcMax);
        BinarySerializeRead(oBinaryBuffer, pPara->m_fFreCoef);
        BinarySerializeRead(oBinaryBuffer, pPara->m_fDigitalDelay);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nModulePower);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nChMergeMode);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nSwitchIn[0]);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nSwitchIn[1]);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nSwitchIn[2]);
        BinarySerializeRead(oBinaryBuffer, pPara->m_nSwitchIn[3]);
		BinarySerializeRead(oBinaryBuffer, pPara->m_nChTypeChg);
		if(pPara->m_dwVersion <= STT_ADJUST_MODULE_PARA_VERSION_1)
		{
			return;
		}

		BinarySerializeRead(oBinaryBuffer, pPara->m_nSwitchIn[4]);
		BinarySerializeRead(oBinaryBuffer, pPara->m_nSwitchIn[5]);
		BinarySerializeRead(oBinaryBuffer, pPara->m_nSwitchIn[6]);
		BinarySerializeRead(oBinaryBuffer, pPara->m_nSwitchIn[7]);
		if(pPara->m_dwVersion <= STT_ADJUST_MODULE_PARA_VERSION_2)
		{
			return;
		}

		BinarySerializeRead(oBinaryBuffer, pPara->m_fDefChMax);
		BinarySerializeRead(oBinaryBuffer, pPara->m_fDefChDcMax);
		if(pPara->m_dwVersion <= STT_ADJUST_MODULE_PARA_VERSION_3)
		{
			return;
		}

		BinarySerializeRead(oBinaryBuffer, pPara->m_nDefChannelNum);
		BinarySerializeRead(oBinaryBuffer, pPara->m_nDAChanNum);
    }
    else
    {
    }
}

void stt_binary_serialize(PSTT_MODULE pPara, CBinarySerialBuffer &oBinaryBuffer)
{
    stt_binary_serialize(&pPara->m_oModuleAttr, oBinaryBuffer);

    if(pPara->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_VOLT
            || pPara->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_CURRENT
            || pPara->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_WEEK_EX
			|| pPara->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_VOLT_CURRENT
			|| pPara->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_ADMU)
    {
        stt_binary_serialize(&pPara->m_oModuleAttr.m_oChDefMap, oBinaryBuffer, pPara->m_oModuleAttr.m_nChannelNum);
        stt_binary_serialize(&pPara->m_oModuleAdjust, oBinaryBuffer, pPara->m_oModuleAttr.m_nChannelNum, pPara->m_oModuleAttr.m_nHarmCount);
    }
}


void stt_InitSttAdjSysParaVersion(char *pszPrefix, DWORD &dwVersion)
{
	pszPrefix[0]='S';
	pszPrefix[1]='T';
	pszPrefix[2]='T';
	pszPrefix[3]='.';
	pszPrefix[4]='A';
	pszPrefix[5]='D';
	pszPrefix[6]='J';
	pszPrefix[7]=0;
	pszPrefix[8]=0;
    dwVersion = g_dwSttAdjSysParaCurrVersion;
}

void stt_InitSttAdjSysParaVersion(CBinarySerialBuffer &oBuffer)
{
    stt_InitSttAdjSysParaVersion(oBuffer.m_chPrefix, oBuffer.m_dwVersion);
    oBuffer.SetCharSet(CHAR_SET_ASCII);
}

#include "../../RecordTest/SttRcdSocketBufferZip.h"

BOOL stt_binary_serialize_read(STT_MODULE &oPara, BYTE *pDestBuffer, long &nLength, bool bUseZip)
{
    BOOL bRet = FALSE;
    CBinarySerialBuffer oBuffer;
    stt_InitSttAdjSysParaVersion(oBuffer);
    oBuffer.ResetVersion();

    BYTE *pUnzipBuffer = NULL;

	if (bUseZip)
    {
		if (!stt_rcd_buf_zip_init())
        {
            bRet = FALSE;
        }
        else
        {
			if (stt_rcd_zip_buf_match_head(pDestBuffer))
            {
                long nSrcLen = stt_rcd_zip_buf_get_len_src(pDestBuffer);
                long nZipLen = 0;
                pUnzipBuffer = new BYTE[nSrcLen + 10];
                bRet = stt_rcd_buf_unzip(pDestBuffer, nLength, pUnzipBuffer, nZipLen);
                oBuffer.AttachBuffer((char *)pUnzipBuffer, nZipLen);
            }
            else
            {
                bRet = FALSE;
            }
        }
    }
    else
    {
        oBuffer.AttachBuffer((char *)pDestBuffer, nLength);
        bRet = TRUE;
    }

    oBuffer.SetReadMode();
    oBuffer.ReadVersion();
    BOOL bResult = FALSE;

    if(bRet)
    {
        stt_binary_serialize(&oPara, oBuffer);
        bResult = TRUE;
    }

	if (pUnzipBuffer != NULL)
    {
        delete pUnzipBuffer;
    }

    return bResult;
}

void stt_binary_serialize_write(STT_MODULE &oPara, BYTE **ppDestBuffer, long &nDestLength, bool bUseZip)
{
    CBinarySerialBuffer oBuffer;
    stt_InitSttAdjSysParaVersion(oBuffer);

    oBuffer.SetCalSizeMode();
    stt_binary_serialize(&oPara, oBuffer);
    oBuffer.WriteVersion();
    oBuffer.AllocBuffer(0);

    oBuffer.SetWriteMode();
    oBuffer.WriteVersion();
    stt_binary_serialize(&oPara, oBuffer);

    //直接返回缓冲区的指针，同时Dettach
	oBuffer.GetBuffer((char**)ppDestBuffer, &nDestLength);
    oBuffer.DettachBuffer();

	if (!bUseZip)
    {
        return;
    }

	if (!stt_rcd_buf_zip_init())
    {
        return;
    }

    long nZipLen = 0;
    BYTE *pZipBuffer = new BYTE[nDestLength + 80];//预留80字节自定义头
    memset(pZipBuffer, 0, nDestLength + 80);
    BOOL bRet = stt_rcd_buf_zip(*ppDestBuffer, nDestLength, pZipBuffer, nZipLen);

	if (bRet)
    {
        delete *ppDestBuffer;
        *ppDestBuffer = pZipBuffer;
        nDestLength = nZipLen;
    }

}

