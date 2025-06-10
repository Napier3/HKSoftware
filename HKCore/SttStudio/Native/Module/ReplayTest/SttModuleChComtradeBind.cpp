//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttParas.cpp  CSttParas


#include "stdafx.h"
#include "SttModuleChComtradeBind.h"
#include "math.h"
#include "ComtradePlayConfig.h"
#include "../SttTestResourceMngr/SttTestResourceMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttModuleChComtradeBind::CSttModuleChComtradeBind()
{
	//��ʼ������
	m_pReplayBuf = NULL;
	m_pHdChRef = NULL;  //������У׼�����Ӳ��ͨ������
	m_fMaxAbs = 0;	//������ֵ
// 	m_nComtradeChID_A = 0;
// 	m_nComtradeChID_B = -1;
	m_dCoefA = 1;
	m_dCoefB = 1;
	m_dK = 1;
	m_nChA_Index = 0;
	m_nChB_Index = 0;
	m_nChSelected = 1;

	m_pCh_A = NULL;
	m_pCh_B = NULL;
	m_dCoefValue = 1;
	m_dZeroValue = 0;
	m_fMomentaryVal = 0.0f;

	m_pReplayBuf = new CComplexMemBuffer_Float();
}

CSttModuleChComtradeBind::~CSttModuleChComtradeBind()
{
	if (m_pReplayBuf != NULL)
	{
		delete m_pReplayBuf;
		m_pReplayBuf = NULL;
	}
}

double CSttModuleChComtradeBind::CalcChannelMaxValue()
{
	if (m_pReplayBuf == NULL)
	{
		return 0;
	}

	float* pCurr = m_pReplayBuf->GetBuffer_float();
	float* pEnd = pCurr + m_pReplayBuf->GetDataLength();

	double fMax = 0;
	double fVal = 0;

	while (pCurr < pEnd)
	{
		fVal = fabs(*pCurr);

		if (fMax < fVal)
		{
			fMax = fVal;
		}

		pCurr++;
	}

	m_fMaxAbs = fMax;
	return m_fMaxAbs;
}

BOOL CSttModuleChComtradeBind::IsChannelSelected()
{
	return m_nChSelected > 0;
}

void CSttModuleChComtradeBind::InitChReplayBuf(long nMaxPoints)
{
	ASSERT (m_pReplayBuf != NULL);

	m_pReplayBuf->SetBufferLength(nMaxPoints);
}

void CSttModuleChComtradeBind::InitCh_A(CComtradeAnalogData *pAnalogData)
{
	if (pAnalogData == NULL)
	{
		m_nChA_Index = 0;
//		m_nComtradeChID_A = 0;
		m_strComtradeChID_A = _T("");
		m_pCh_A = NULL;
		return;
	}

	m_nChA_Index = pAnalogData->GetChCurrVolIndex();
	m_strComtradeChID_A = pAnalogData->m_strName;
	m_pCh_A = pAnalogData;
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("CSttModuleChComtradeBind::InitCh_A(m_nComtradeChID_A=%ld)(m_dK=%f)"),m_nComtradeChID_A,m_dK);
}

void CSttModuleChComtradeBind::InitCh_B(CComtradeAnalogData *pAnalogData)
{
	if (pAnalogData == NULL)
	{
		m_nChB_Index = 0;
//		m_nComtradeChID_B = 0;
		m_strComtradeChID_B = _T("");
		m_pCh_B = NULL;
		return;
	}

// 	m_nChA_Index = pAnalogData->GetChCurrVolIndex();
	m_nChB_Index = pAnalogData->GetChCurrVolIndex();

//	m_nComtradeChID_B = pAnalogData->m_nChannelIndex;
	m_strComtradeChID_B = pAnalogData->m_strName;
	m_pCh_B = pAnalogData;
}

void CSttModuleChComtradeBind::ResetChReplayBuf()
{
	if (m_pReplayBuf != NULL)
	{
		m_pReplayBuf->Init();
	}
}

BOOL CSttModuleChComtradeBind::IsModuleType_U()
{	
	if (m_pHdChRef != NULL)
	{
		return stt_adj_HdChDef_Is_Voltage(m_pHdChRef);
	}

	if((m_strName.Find(_T("U")) == 0) || (m_strID.Find(_T("U")) == 0))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CSttModuleChComtradeBind::IsModuleType_I()
{	
	if (m_pHdChRef != NULL)
	{
		return stt_adj_HdChDef_Is_Current(m_pHdChRef);
	}

	if((m_strName.Find(_T("I")) == 0) || (m_strID.Find(_T("I")) == 0))
	{
		return TRUE;
	}

	return FALSE;
}
//////////////////////////////////////////////////////////////////////////
//CSttModuleComtradeBind
CSttModuleComtradeBind::CSttModuleComtradeBind()
{
	m_nModulePos = -1;
	m_pReplayBufBinary1 = NULL;
	m_pReplayBufBinary2 = NULL;

	m_nWeekChTypeChg = 0;

	m_fPTRatio[0] = 1.0f;
	m_fPTRatio[1] = 1.0f;

	m_fCTRatio[0] = 1.0f;
	m_fCTRatio[1] = 1.0f;

}

CSttModuleComtradeBind::~CSttModuleComtradeBind()
{
	if (m_pReplayBufBinary1 != NULL)
	{
		delete m_pReplayBufBinary1;
		m_pReplayBufBinary1 = NULL;
	}
	if (m_pReplayBufBinary2 != NULL)
	{
		delete m_pReplayBufBinary2;
		m_pReplayBufBinary2 = NULL;
	}
}

BOOL CSttModuleComtradeBind::IsModuleSelected()
{
	POS pos = GetHeadPosition();
	CSttModuleChComtradeBind *pCh = NULL;
	CSttModuleBinaryChComtradeBind *pBinaryCh = NULL;

	//2024-03-29 wuxinyi �ж���������չģ���Ƿ�ѡ��
	if(IsBinaryTypeModule())
	{
		while (pos != NULL)
		{
		pBinaryCh = (CSttModuleBinaryChComtradeBind *)GetNext(pos);

		if (pBinaryCh->m_nBinaryCh_Index >0)
		{
			return TRUE;
		}
	}

	}
	else
	{
	while(pos != NULL)
	{
		pCh = (CSttModuleChComtradeBind *)GetNext(pos);

		if (pCh->IsChannelSelected())
		{
			return TRUE;
		}
	}
	}

	return FALSE;
}

double CSttModuleComtradeBind::CalcChMaxValueByIndex(long nChIndex)
{
	CSttModuleChComtradeBind *pCh = NULL;
	double fMax = 0;
	double fVal = 0;

	if (nChIndex < 0)
	{//����ͨ�����¼���
		POS pos = GetHeadPosition();

		while(pos != NULL)
		{
			pCh = (CSttModuleChComtradeBind *)GetNext(pos);

			if (pCh->IsChannelSelected())
			{
				fVal = pCh->CalcChannelMaxValue();
				if (fVal > fMax)
				{
					fMax = fVal;
				}
			}
		}
	}
	else
	{
		pCh = (CSttModuleChComtradeBind *)GetAt(nChIndex);
		if (pCh->IsChannelSelected())
		{
			fMax = pCh->CalcChannelMaxValue();
		}
	}

	return fMax;
}

double CSttModuleComtradeBind::GetModuleMaxValue_U()
{
	CSttModuleChComtradeBind *pCh = NULL;
	double fMax = 0;
	POS pos = GetHeadPosition();

	while(pos != NULL)
	{
		pCh = (CSttModuleChComtradeBind *)GetNext(pos);

		if (!pCh->IsChannelSelected())
		{
			continue;
		}

		if (!pCh->IsModuleType_U())
		{
			continue;
		}

		if (pCh->m_fMaxAbs > fMax)
		{
			fMax = pCh->m_fMaxAbs;
		}
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("MaxValue_U=%f"),fMax);
	return fMax;
}

double CSttModuleComtradeBind::GetModuleMaxValue_I()
{
	CSttModuleChComtradeBind *pCh = NULL;
	double fMax = 0;
	POS pos = GetHeadPosition();

	while(pos != NULL)
	{
		pCh = (CSttModuleChComtradeBind *)GetNext(pos);

		if (!pCh->IsChannelSelected())
		{
			continue;
		}

		if (!pCh->IsModuleType_I())
		{
			continue;
		}
			
		if (pCh->m_fMaxAbs > fMax)
		{
			fMax = pCh->m_fMaxAbs;
		}
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("MaxValue_I=%f"),fMax);
	return fMax;
}
void CSttModuleComtradeBind::ScalingModuleMaxValue(float fK)
{
	CSttModuleChComtradeBind *pCh = NULL;
	POS pos = GetHeadPosition();

	while(pos != NULL)
	{
		pCh = (CSttModuleChComtradeBind *)GetNext(pos);

		if (pCh->IsChannelSelected())
		{
			pCh->m_fMaxAbs *= fK;
		}
	}
}

void CSttModuleComtradeBind::InitModuleReplayBuf(long nMaxPoints)
{
	CSttModuleChComtradeBind *pCh = NULL;
	POS pos = GetHeadPosition();

	while(pos != NULL)
	{
		pCh = (CSttModuleChComtradeBind *)GetNext(pos);
		pCh->InitChReplayBuf(nMaxPoints);
	}
}

void CSttModuleComtradeBind::ResetModuleReplayBuf()
{
	CSttModuleChComtradeBind *pCh = NULL;
	POS pos = GetHeadPosition();

	while(pos != NULL)
	{
		pCh = (CSttModuleChComtradeBind *)GetNext(pos);
		pCh->ResetChReplayBuf();
	}
}

long CSttModuleComtradeBind::GetCount_U()
{
	CSttModuleChComtradeBind *pCh = NULL;
	POS pos = GetHeadPosition();
	long nCount = 0;

	while(pos != NULL)
	{
		pCh = (CSttModuleChComtradeBind *)GetNext(pos);
		
		if (pCh->IsModuleType_U())
		{
			nCount++;
		}
	}

	return nCount;
}

long CSttModuleComtradeBind::GetCount_I()
{
	CSttModuleChComtradeBind *pCh = NULL;
	POS pos = GetHeadPosition();
	long nCount = 0;

	while(pos != NULL)
	{
		pCh = (CSttModuleChComtradeBind *)GetNext(pos);

		if (pCh->IsModuleType_I())
		{
			nCount++;
		}
	}

	return nCount;
}

long CSttModuleComtradeBind::GetCount_B()
{
	return 0;
}

void CSttModuleComtradeBind::InitReplayBufBinary(long nLength)
{
	if(m_pReplayBufBinary1 == NULL || m_pReplayBufBinary2 == NULL)
	{
		m_pReplayBufBinary1 = new CComplexMemBuffer_Float;
		m_pReplayBufBinary2 = new CComplexMemBuffer_Float;
	}
	long nBinaryBuf1 = m_pReplayBufBinary1->GetBufferLength();
	long nBinaryBuf2 = m_pReplayBufBinary2->GetBufferLength();
	long nRealLength = nLength + 5;

	if(nBinaryBuf1 < nLength)
	{
		m_pReplayBufBinary1->SetBufferLength(nRealLength);
	}
	if(nBinaryBuf2 < nLength)
	{
		m_pReplayBufBinary2->SetBufferLength(nRealLength);
	}	
}

BOOL CSttModuleComtradeBind::IsBinaryTypeModule()
{	
	if(m_strModuleID.IsEmpty())
	{
		return FALSE;
	}
	return m_strModuleID.Find(_T("Binary")) != -1;
}	

void CSttModuleComtradeBind::ResetReplayBufBinaryBuf(/* long nLength */)
{
	if(m_pReplayBufBinary1 == NULL || m_pReplayBufBinary2 == NULL)
	{
		return;
	}	
	m_pReplayBufBinary1->Init();
	m_pReplayBufBinary2->Init();

}

BOOL CSttModuleComtradeBind::IsDigitalTypeModule()
{
	if(m_strModuleID.IsEmpty())
	{
		return FALSE;
	}
	return m_strModuleID.Find(_T("Digital")) != -1;
}

BOOL CSttModuleComtradeBind::IsAnalogTypeModule()
{
	if(IsBinaryTypeModule())
	{
		return FALSE;
	}
	else if(IsDigitalTypeModule())
	{
		return FALSE;
	}
	else if(IsWeekTypeModule())
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CSttModuleComtradeBind::IsWeekTypeModule()
{
	if(m_strModuleID.IsEmpty())
	{
		return FALSE;
	}
	return m_strModuleID.Find(_T("Week")) != -1;
}

BOOL CSttModuleComtradeBind::IsWeekChTypeChg()
{
	return m_nWeekChTypeChg;
}

void CSttModuleComtradeBind::SetWeekChTypeChg( long nWeekChTypeChg )
{
	m_nWeekChTypeChg = nWeekChTypeChg;
}


long CSttModuleChComtradeBind::GetMaxPoints()
{
	if (m_pReplayBuf == NULL)
	{
		return 0;
	}

	return m_pReplayBuf->GetBufferLength();
}

// long CSttModuleChComtradeBind::GetValue_DataA()
// {
// 	return m_nComtradeChID_A;
// }
// 
// long CSttModuleChComtradeBind::GetValue_DataB()
// {
// 	return m_nComtradeChID_B;
// }

double CSttModuleChComtradeBind::GetValue_DataK()
{
	return m_dK;
}

CString CSttModuleChComtradeBind::GetUnit()
{
	if (m_pCh_A != NULL)
	{
		return m_pCh_A->m_strUnit;
	}

	if (m_pCh_B != NULL)
	{
		return m_pCh_B->m_strUnit;
	}

	return _T("");
}

CString CSttModuleChComtradeBind::GetModuleChPhase()
{
	if (m_pParent == NULL)
	{
		return _T("A");
	}

	CSttModuleComtradeBind *pModule = (CSttModuleComtradeBind*)m_pParent;
	CSttModuleChComtradeBind *pCh = NULL;
	POS pos = pModule->GetHeadPosition();
	long nCount = 0;
	BOOL bIsModuleType_I = IsModuleType_I();

	while(pos != NULL)
	{
		pCh = (CSttModuleChComtradeBind *)pModule->GetNext(pos);

		if (pCh == this)
		{
			break;
		}

		if (bIsModuleType_I == pCh->IsModuleType_I())
		{
			nCount++;
		}
	}

	if (nCount%4 == 1)
	{
		return _T("B");
	}
	else if (nCount%4 == 2)
	{
		return _T("C");
	}
	else if(nCount%4 == 3)
	{
		return _T("N");
	}
	else
		return _T("A");
}

int CSttModuleChComtradeBind::GetIndexByID( CString ChStrID )
{
	if (m_pParent == NULL)
	{
		return -1;
	}

	CSttModuleComtradeBind *pModule = (CSttModuleComtradeBind*)m_pParent;
	CSttModuleChComtradeBind *pCh = NULL;
	POS pos = pModule->GetHeadPosition();
	long nCount = 0;

	while(pos != NULL)
	{
		pCh = (CSttModuleChComtradeBind *)pModule->GetNext(pos);
		if(pCh->m_strID == ChStrID)
		{
			return nCount;
		}
		nCount++;
	}

	return -1;

}

int CSttModuleChComtradeBind::GetEleTypeIndex()
{
	CDvmData *pChData = (CDvmData *)m_pHdChRef->FindByID(_T("EeType"));
	if(!pChData)
	{
		return -1;
	}

	CString strEeType = pChData->m_strValue;

	int nEleType = (strEeType == STT_REPLAY_WEEK_MODULE_CH_EeType_VOL) ?REPLAY_WEEK_CH_ELETYPE_VOL : REPLAY_WEEK_CH_ELETYPE_CURR;

	return nEleType;
}

CString CSttModuleChComtradeBind::GetEleTypeString()
{
	CDvmData *pChData = (CDvmData *)m_pHdChRef->FindByID(_T("EeType"));
	if(!pChData)
	{
		return _T("");
	}

	CString strEeType = pChData->m_strValue;

	return strEeType;
}

void CSttModuleChComtradeBind::SetEleType(int nEleType)
{
	if(!m_pHdChRef)
	{
		return;
	}

	CString strValue = (nEleType == REPLAY_WEEK_CH_ELETYPE_VOL) ? 
			STT_REPLAY_WEEK_MODULE_CH_EeType_VOL : STT_REPLAY_WEEK_MODULE_CH_EeType_Curr;

	m_pHdChRef->SetDataValue(_T("EeType"),strValue);
}

float CSttModuleChComtradeBind::GetChDCMaxValue()
{
	if(!m_pHdChRef)
    {
        return 0.0f;
    }

    CDvmData *pChData = static_cast<CDvmData *>(m_pHdChRef->FindByID(_T("ChDCMaxValue")));
    if(!pChData)
    {
        return 0.0f;
    }

	float fValue = CString_To_double(pChData->m_strValue);
    return fValue;
}


//////////////////////////////////////////////////////////////////////////
//CSttModulesComtradeBind
CSttModulesComtradeBind::CSttModulesComtradeBind()
{
	m_pSttAdjDevice = NULL;
	m_nChMaxPoints = 0;
	m_pBinaryModuleComtradeBind = NULL;

	m_nAnalogModuleCount = 0;
	m_nDigitalModuleCount = 0;
	m_nWeekModuleCount = 0;

	m_nUseBinaryModule = FALSE;
	m_nUseBinaryModuleWidget = FALSE;
}

CSttModulesComtradeBind::~CSttModulesComtradeBind()
{
	
}

BOOL CSttModulesComtradeBind::IsBinaryModuleSelected()
{
	CSttModuleComtradeBind *pBinModule = GetBinaryModule();

	if(!pBinModule)
	{
		return FALSE;
	}

	CSttModuleBinaryChComtradeBind *pBinaryCh = NULL;
	POS pos = pBinModule->GetHeadPosition();

	//2024-03-29 wuxinyi �ж���������չģ���Ƿ�ѡ��
	while (pos != NULL)
	{
		pBinaryCh = (CSttModuleBinaryChComtradeBind *)pBinModule->GetNext(pos);

		if (pBinaryCh->m_nBinaryCh_Index >0)
		{
			m_nUseBinaryModule = TRUE;
			return TRUE;
		}
	}
	m_nUseBinaryModule = FALSE;
	return FALSE;

}

void CSttModulesComtradeBind::InitModuleReplayBuf(long nChMaxPoints)
{
	m_nChMaxPoints = nChMaxPoints;
	POS pos = GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)GetNext(pos);

		if(!pModule->IsBinaryTypeModule())
		{
			pModule->InitModuleReplayBuf(nChMaxPoints);
		}
		else
		{
			pModule->InitReplayBufBinary(nChMaxPoints);
		}
	}

	if(m_pBinaryModuleComtradeBind)
	{
	m_pBinaryModuleComtradeBind->InitReplayBufBinary(nChMaxPoints);
	}

}

long CSttModulesComtradeBind::GetDataLength()
{
	CSttModuleComtradeBind *pModule = (CSttModuleComtradeBind*)GetHead();

	if (pModule == NULL)
	{
		return 0;
	}

	if(!pModule->IsBinaryTypeModule())
	{
		CSttModuleChComtradeBind *pCh = (CSttModuleChComtradeBind*)pModule->GetHead();

		if (pCh == NULL)
		{
			return 0;
		}

		return pCh->m_pReplayBuf->GetDataLength();
}
	else
	{
		return pModule->m_pReplayBufBinary1->GetDataLength();
	}

}

void CSttModulesComtradeBind::InitBySttAdjDevice(CSttAdjDevice *pAdjDevice)
{
	//��ʼ������
	DeleteAll();//20220513 zhouhj ɾ��֮ǰ�Ĳ��,���²���������³�ʼ��
	InitAllMoudleCount(); 

	CExBaseList oCurModuleListRef;
	pAdjDevice->GetAllModules(&oCurModuleListRef);//��ȡȫ����ѹģ��

	POS pos = oCurModuleListRef.GetHeadPosition();
	CDataGroup *pModule = NULL,*pModuleAttrs = NULL,*pDeviceAttrs = NULL;
	CDataGroup *pHdChDef = NULL;
	CDataGroup *pHdCh = NULL;
	CDvmData *pDvmData = NULL;
	long nModuleIndex = 1;
	CSttAdjModule oModule;
	long nChNum = 0;
	CSttModuleComtradeBind *pModuleBind = NULL;
	CSttModuleChComtradeBind *pChBind = NULL;
	CSttModuleBinaryChComtradeBind *pBinaryChBind = NULL;
	CString strModuleType;
	CString strName,strTmp;
	CString strModuleDesc = _T("ģ��"),strVolDesc = _T("(��ѹ)"),strCurDesc = _T("(����)"),strVolCurDesc = _T("(��ѹ����)"),strBinaryOutEx
		,strDigitalDesc/* = _T("(������)")*/,strWeekDesc/* = _T("(���ź�)")*/;
	strName = strModuleDesc;
	strName.AppendFormat(_T("%d"),nModuleIndex);

	//2024/1/29 wangjunsheng ��ӿ�������չ
	int nBoutIndex = 1;
	int nDigitaiModuleIndex = 0;

	long nCurrSelectChNum = 0;
//	strName.Format(_T("%s%d"),strModuleDesc.GetString(), nModuleIndex);

	pDeviceAttrs = (CDataGroup *)pAdjDevice->m_pSttAdjRef->FindByID(_T("DeviceAttrs"));
	if(pDeviceAttrs)
	{
		CDvmData *pBoutReplay = (CDvmData *)pDeviceAttrs->FindByID(_T("BoutReplay"));
		if(pBoutReplay)
		{
			m_nUseBinaryModuleWidget = CString_To_long(pBoutReplay->m_strValue);
		}
	}

	while (pos != NULL)//�ڸ�ѭ�������õ�ѹģ�����ֵ,��Сֵ
	{
		pModule = (CDataGroup *)oCurModuleListRef.GetNext(pos);
		oModule.AttatchAdjRef(pModule);
		
		if (!oModule.GetModuleType(strModuleType))
		{
			continue;
		}

		if (strModuleType == STT_MODULE_TYPE_VOLT_ID && g_oSystemParas.m_nHasAnalog)
		{
			strName += strVolDesc;
			m_nAnalogModuleCount++;
		}
		else if (strModuleType == STT_MODULE_TYPE_CURRENT_ID  && g_oSystemParas.m_nHasAnalog)
		{
			strName += strCurDesc;
			m_nAnalogModuleCount++;
		}
		else if (strModuleType == STT_MODULE_TYPE_VOLT_CURRENT_ID  && g_oSystemParas.m_nHasAnalog)
		{
			strName += strVolCurDesc;
			m_nAnalogModuleCount++;
		}
		else if(strModuleType == STT_MODULE_TYPE_SWITCH_ID)
		{
			strBinaryOutEx.Format(_T("����������չ��%d ����"), nBoutIndex);
		}
		else if((strModuleType == STT_MODULE_TYPE_DIGITAL_0G8M_ID ||strModuleType == STT_MODULE_TYPE_DIGITAL_2G6M_ID ||strModuleType == STT_MODULE_TYPE_DIGITAL_4G4M_ID)
			  && g_oSystemParas.m_nHasDigital)
		{
 			strDigitalDesc = _T("������ģ��");
			m_nDigitalModuleCount++;
		}
		else if((strModuleType == STT_MODULE_TYPE_WEEK_EX_ID || strModuleType == STT_MODULE_TYPE_ADMU_ID)
		  && g_oSystemParas.m_nHasWeek)
		{
			strWeekDesc.Format( _T("���ź�ģ��%d"),m_nWeekModuleCount+1);
			m_nWeekModuleCount++;
		}
		else
		{
			continue;
		}

		pHdChDef = oModule.GetHdChDefine();

		if (pHdChDef == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("���(%s)(%s)GetHdChDefineʧ��."),strName.GetString(),strModuleType.GetString());
			continue;
		}

		if(strModuleType == STT_MODULE_TYPE_SWITCH_ID) //2024/1/30 wangjunsheng ����BINARRY������ģ��
		{
			//2024-03-26 wuxinyi �޸Ŀ�����չͨ����������
// 			nChNum = g_nBoutExCount;	
			strTmp.Format(_T("%s%d"), strModuleType.GetString(), nBoutIndex); 
			pModuleBind = (CSttModuleComtradeBind*)FindByID(strTmp);

			if (pModuleBind == NULL)
			{
				pModuleBind = new CSttModuleComtradeBind();
				pModuleBind->m_strName = strBinaryOutEx;
				pModuleBind->m_strModuleID.Format(_T("BinaryModuleEx%ld"),nBoutIndex-1);
				pModuleBind->m_strID.Format(_T("%s%d"), strModuleType.GetString(), nBoutIndex);
				pModuleBind->m_pReplayBufBinary1 = new CComplexMemBuffer_Float();
				pModuleBind->m_pReplayBufBinary2 = new CComplexMemBuffer_Float();
				AddNewChild(pModuleBind);
			}
		}
		else if(strModuleType == STT_MODULE_TYPE_VOLT_CURRENT_ID || strModuleType == STT_MODULE_TYPE_VOLT_ID || strModuleType == STT_MODULE_TYPE_CURRENT_ID)
		{
			nChNum = stt_adj_HdChDef_GetNum(pHdChDef);
			strTmp.Format(_T("%s%d"), strModuleType.GetString(), nModuleIndex); 
			pModuleBind = (CSttModuleComtradeBind*)FindByID(strTmp);

			if (pModuleBind == NULL)
			{
				pModuleBind = new CSttModuleComtradeBind();
				pModuleBind->m_strName = strName;
				pModuleBind->m_strModuleID.Format(_T("Module%ld"),nModuleIndex-1);
				pModuleBind->m_strID.Format(_T("%s%d"), strModuleType.GetString(), nModuleIndex);
				AddNewChild(pModuleBind);
			}
		}
		else if((strModuleType == STT_MODULE_TYPE_DIGITAL_0G8M_ID ||strModuleType == STT_MODULE_TYPE_DIGITAL_2G6M_ID ||strModuleType == STT_MODULE_TYPE_DIGITAL_4G4M_ID)
			&& (m_nDigitalModuleCount == 1))
		{
			strTmp.Format(_T("%s%d"), strModuleType.GetString(), nDigitaiModuleIndex); 
			pModuleBind = (CSttModuleComtradeBind*)FindByID(strTmp);

			if (pModuleBind == NULL)
			{
				pModuleBind = new CSttModuleComtradeBind();
				pModuleBind->m_strName = strDigitalDesc;
				pModuleBind->m_strModuleID.Format(_T("DigitalModule%ld"),nDigitaiModuleIndex);
				pModuleBind->m_strID = strTmp;
				AddNewChild(pModuleBind);
			}
// 			continue;
		}
		else if(strModuleType == STT_MODULE_TYPE_WEEK_EX_ID || strModuleType == STT_MODULE_TYPE_ADMU_ID)
		{
			nChNum = stt_adj_HdChDef_GetNum(pHdChDef);
			strTmp.Format(_T("%s%d"), strModuleType.GetString(), m_nWeekModuleCount); 
			pModuleBind = (CSttModuleComtradeBind*)FindByID(strTmp);

			if (pModuleBind == NULL)
			{
				pModuleBind = new CSttModuleComtradeBind();
				pModuleBind->m_strName = strWeekDesc;
				pModuleBind->m_strModuleID.Format(_T("WeekModule%ld"),m_nWeekModuleCount);
				pModuleBind->m_strID = strTmp;
				AddNewChild(pModuleBind);
			}

		}

		pModuleAttrs = (CDataGroup*)pModule->FindByID(_T("ModuleAttrs"));

		if (pModuleAttrs != NULL)
		{
			//pModuleBind->m_nModulePos = Global_GetModulePos(pModuleAttrs);
			pModuleBind->m_nModulePos = -1;

			//ģ��λ��
			CDvmData* pData = (CDvmData*)pModuleAttrs->FindByID(_T("ModulePos"));

			if (pData != NULL)
			{
				pModuleBind->m_nModulePos = CString_To_long(pData->m_strValue);
			}

			//ͨ���������Ϳɱ�(1:�ɱ�,0:���ɱ�)--���ź�ʹ��
			pData = (CDvmData*)pModuleAttrs->FindByID(_T("ChTypeChg"));
			if (pData != NULL)
			{
				long nValue = CString_To_long(pData->m_strValue);
				
				pModuleBind->SetWeekChTypeChg(nValue);
// 				pModuleBind->SetWeekChTypeChg(1);
			}

		}


		if(strModuleType == STT_MODULE_TYPE_VOLT_CURRENT_ID || strModuleType == STT_MODULE_TYPE_VOLT_ID || strModuleType == STT_MODULE_TYPE_CURRENT_ID)
		{
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("InitBySttAdjDevice(nModuleIndex=%d,Pos=%ld)"),nModuleIndex,pModuleBind->m_nModulePos);
			for (int nChIndex = 0;nChIndex < nChNum;nChIndex++)
			{
				pHdCh = pHdChDef->FindByDataType(STT_ADJ_DATA_TYPE_HdCh, nChIndex);

				if (pHdCh == NULL)
				{
					break;
				}

				pHdCh->GetDataValue(_T("ID"), strTmp);
				pChBind = (CSttModuleChComtradeBind*)pModuleBind->FindByName(strTmp);

				if (pChBind == NULL)
				{
					pChBind = new CSttModuleChComtradeBind();
					pChBind->m_strName = strTmp;
					pChBind->m_strID = pChBind->m_strName;
					pModuleBind->AddNewChild(pChBind);

					if (nCurrSelectChNum<BIG_COMTRADE_REPLAY_CH_MAX_NUM)
					{
						pChBind->m_nChSelected = 1;
						nCurrSelectChNum++;
					} 
					else
					{
						pChBind->m_nChSelected = 0;
					}
				}

				pChBind->m_pHdChRef = (CDataGroup *)pHdCh->Clone();
		}

			nModuleIndex++;
			strName = strModuleDesc;
			strName.AppendFormat(_T("%d"),nModuleIndex);

		}
		else if(strModuleType == STT_MODULE_TYPE_SWITCH_ID)
		{
			nChNum = 0;
			for(int nIndex = 0; nIndex < 8; nIndex++)
			{
				CString strName;
				strName.AppendFormat(_T("SwitchIn_%d"),nIndex);
				CDvmData* pData = (CDvmData*)pModuleAttrs->FindByID(strName);
				if(pData)
				{
				int nValue = CString_To_long(pData->m_strValue);//pData->m_strValue.toInt();
				if(nValue == 0)
				{
					nChNum += 8;
				}
			}
				
			}

			CString strID;
			for (int nChIndex = 0;nChIndex < nChNum;nChIndex++)
			{
				strTmp.Format(_T("����ͨ��%d"), nChIndex); 
				strID.Format(_T("BinaryExCh%d"), nChIndex);
				pBinaryChBind = new CSttModuleBinaryChComtradeBind();
				pBinaryChBind->m_strName = strTmp;
				pBinaryChBind->m_strID = strID;
				pModuleBind->AddNewChild(pBinaryChBind);
			}
		}
		else if((strModuleType == STT_MODULE_TYPE_DIGITAL_0G8M_ID ||strModuleType == STT_MODULE_TYPE_DIGITAL_2G6M_ID ||strModuleType == STT_MODULE_TYPE_DIGITAL_4G4M_ID)
			&& (m_nDigitalModuleCount == 1))
		{
			CString strID;
			char strChIDName[3] = {'a','b','c'};
			int nGroupNum = 1;
// 			CSttModuleChComtradeBind *pDigitalModuleChComtradeBind;
			for(int nChIndex = 0; nChIndex < REPLAY_DIGITAL_MODULE_CH_NUM; nChIndex++)
			{
				pChBind = new CSttModuleChComtradeBind();
				//��һ��
				if(nChIndex <6)
				{
					if(nChIndex < 3)
					{
						strTmp.Format(_T("U%c%d"), strChIDName[nChIndex%3] ,nGroupNum);
					}
					else
					{
						strTmp.Format(_T("I%c%d"), strChIDName[nChIndex%3] ,nGroupNum);
					}
				}
				else if(nChIndex >= 6 && nChIndex <12)//�ڶ���
				{
					if(nChIndex < 9)
					{
						strTmp.Format(_T("U%c%d"), strChIDName[nChIndex%3] ,nGroupNum+1);
					}
					else
					{
						strTmp.Format(_T("I%c%d"), strChIDName[nChIndex%3] ,nGroupNum+1);
					}
				}

				strID.Format(_T("DigitalCh%d"), nChIndex);

				pChBind->m_strName = strTmp;
				pChBind->m_strID = strID;
				pChBind->m_nChSelected = 1;
				pModuleBind->AddNewChild(pChBind);
			}
		}
		else if(strModuleType == STT_MODULE_TYPE_WEEK_EX_ID || strModuleType == STT_MODULE_TYPE_ADMU_ID)
		{
			CString strWeekEeType = _T("");

			for (int nChIndex = 0;nChIndex < nChNum;nChIndex++)
			{
				pHdCh = pHdChDef->FindByDataType(STT_ADJ_DATA_TYPE_HdCh, nChIndex);

				if (pHdCh == NULL)
				{
					break;
				}

				pHdCh->GetDataValue(_T("ID"), strTmp);
				pHdCh->GetDataValue(_T("EeType"), strWeekEeType);

				pChBind = (CSttModuleChComtradeBind*)pModuleBind->FindByName(strTmp);

				if (pChBind == NULL)
				{
					pChBind = new CSttModuleChComtradeBind();
					pChBind->m_strName = strTmp;
					pChBind->m_strID = pChBind->m_strName;

					pModuleBind->AddNewChild(pChBind);

					if (nCurrSelectChNum<BIG_COMTRADE_REPLAY_CH_MAX_NUM)
					{
						pChBind->m_nChSelected = 1;
						nCurrSelectChNum++;
					} 
					else
					{
						pChBind->m_nChSelected = 0;
					}
				}

				pChBind->m_pHdChRef = (CDataGroup *)pHdCh->Clone();
			}

// 			nModuleIndex++;
// 			strName = strModuleDesc;
// 			strName.AppendFormat(_T("%d"),nModuleIndex);

		}
	}
	
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("enter initAllCh"));
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("ģ����ģ��������:%d"),m_nAnalogModuleCount);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("������ģ��������:%d"),m_nDigitalModuleCount);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("���ź�ģ��������:%d"),m_nWeekModuleCount);


	oCurModuleListRef.RemoveAll();
}

CSttModuleComtradeBind* CSttModulesComtradeBind::FindByModuleID(const CString &strModuleID)
{
	CSttModuleComtradeBind* pCSttModuleComtradeBind = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pCSttModuleComtradeBind = (CSttModuleComtradeBind*)GetNext(pos);

		if (pCSttModuleComtradeBind->m_strModuleID == strModuleID)
		{
			return pCSttModuleComtradeBind;
		}
	}

	return NULL;
}
long CSttModulesComtradeBind::GetModuleCount()
{
// 	long nModuleCount = 0;
// 	CSttModuleComtradeBind* pCSttModuleComtradeBind = NULL;
// 	POS pos = GetHeadPosition();
// 
// 	while(pos)
// 	{
// 		pCSttModuleComtradeBind = (CSttModuleComtradeBind*)GetNext(pos);
// 
// 		if (pCSttModuleComtradeBind)
// 		{
// 			 ++nModuleCount;
// 		}
// 	}
// 
// 	return nModuleCount;

	long nModuleCount = GetCount();

	return nModuleCount;
}

void CSttModulesComtradeBind::InitBinaryModule()
{
	if(m_pBinaryModuleComtradeBind != NULL)
	{
		delete m_pBinaryModuleComtradeBind;
		m_pBinaryModuleComtradeBind = NULL;
	}

	CSttModuleBinaryChComtradeBind * pBinaryChBind = NULL;
	int nChNum = g_nBoutCount;
	if(nChNum <= 0)
	{
		return;
	}

	if(m_pBinaryModuleComtradeBind == NULL)
	{
		m_pBinaryModuleComtradeBind = new CSttModuleComtradeBind();
		m_pBinaryModuleComtradeBind->m_strName = _T("���忪����ģ��");
		m_pBinaryModuleComtradeBind->m_strModuleID = _T("BinaryModule");
		m_pBinaryModuleComtradeBind->m_strID = STT_MODULE_TYPE_SWITCH_ID;
		m_pBinaryModuleComtradeBind->m_pReplayBufBinary1 = new CComplexMemBuffer_Float();
		m_pBinaryModuleComtradeBind->m_pReplayBufBinary2 = new CComplexMemBuffer_Float();
		CString strID,strTmp;
		for (int nChIndex = 0;nChIndex < nChNum;nChIndex++)
		{
			strTmp.Format(_T("����ͨ��%d"), nChIndex); 
			strID.Format(_T("BinaryCh%d"), nChIndex);
			pBinaryChBind = new CSttModuleBinaryChComtradeBind();
			pBinaryChBind->m_strName = strTmp;
			pBinaryChBind->m_strID = strID;
			m_pBinaryModuleComtradeBind->AddNewChild(pBinaryChBind);
		}
	}
	else
	{
		m_pBinaryModuleComtradeBind->m_strName = _T("���忪����ģ��");
		m_pBinaryModuleComtradeBind->m_strModuleID = _T("BinaryModule");
		m_pBinaryModuleComtradeBind->m_strID = STT_MODULE_TYPE_SWITCH_ID;

		CString strID,strTmp;
		for (int nChIndex = 0;nChIndex < nChNum;nChIndex++)
		{
			strTmp.Format(_T("����ͨ��%d"), nChIndex); 
			strID.Format(_T("BinaryCh%d"), nChIndex);
			pBinaryChBind = (CSttModuleBinaryChComtradeBind*)m_pBinaryModuleComtradeBind->FindByID(strID);
			if (pBinaryChBind == NULL)
			{
				pBinaryChBind = new CSttModuleBinaryChComtradeBind();
				pBinaryChBind->m_strName = strTmp;
				pBinaryChBind->m_strID = strID;
				m_pBinaryModuleComtradeBind->AddNewChild(pBinaryChBind);

			}

		}
	}


}

CSttModuleComtradeBind * CSttModulesComtradeBind::GetBinaryModule()
{
	return m_pBinaryModuleComtradeBind;
}

int CSttModulesComtradeBind::GetAnalogModuleCount()
{
	return m_nAnalogModuleCount;
}

int CSttModulesComtradeBind::GetDigitalModuleCount()
{
	return m_nDigitalModuleCount;
}

int CSttModulesComtradeBind::GetWeekModuleCount()
{
	return m_nWeekModuleCount;
}

void CSttModulesComtradeBind::InitAllMoudleCount()
{
	m_nAnalogModuleCount = 0;
	m_nDigitalModuleCount = 0;
	m_nWeekModuleCount = 0;
}

CSttModuleBinaryChComtradeBind::CSttModuleBinaryChComtradeBind()
{
	m_pBinaryCh = NULL;
	m_strComtradeBinaryCh = _T("");	//������ͨ��
	m_nBinaryCh_Index = 0;			//������ѡ��ͨ��
	m_nChState = 0;				//0-�Ͽ� 1-�պ� 
}

CSttModuleBinaryChComtradeBind::~CSttModuleBinaryChComtradeBind()
{

}

void CSttModuleBinaryChComtradeBind::InitBinaryCh( CComtradeBinaryData *pBinaryData )
{
	if (pBinaryData == NULL)
	{
		m_nBinaryCh_Index = 0;
		m_strComtradeBinaryCh = _T("");
		m_pBinaryCh = NULL;
		return;
	}

	m_nBinaryCh_Index = pBinaryData->GetChIndex();
	m_strComtradeBinaryCh = pBinaryData->m_strName;
	m_pBinaryCh = pBinaryData;
}
