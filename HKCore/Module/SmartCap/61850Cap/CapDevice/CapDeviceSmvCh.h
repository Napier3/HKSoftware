//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceSmvCh.h  CCapDeviceSmvCh

#pragma once

#include "CapDeviceChBase.h"

#include <math.h>

class CCapDeviceSmvCh : public CCapDeviceChBase
{
public:
	CCapDeviceSmvCh();
	virtual ~CCapDeviceSmvCh();


	//UINT m_nChType;// ��ѹ=0������=1��ʱ��=2
	UINT m_nChRateIndex;
	double m_fChRate;

	//yyj
	DWORD m_wValue;		//9-1ͨ��ԭʼֵ
	DWORD m_dwValue;	//9-2ͨ��ԭʼֵ
	DWORD m_dwQuality;	//9-2ͨ��Ʒ��

	float m_fValue;		//����ֵ
	long m_nAccurLevel;//zhouhj ׼ȷ��
	long m_nChAngType;//20221210 zhouhj ͨ�����,������ţ��Ե���ͨ��Ϊ��0-Ia1 1-Ib1 2-Ic1 3-I01 4-Ia2

//���غ���
public:
	virtual UINT GetClassID(){return CPDCLASSID_SMVCH;};
	virtual void InitChannel(CIecCfgDataChBase *pIecCfgDataCh);
	virtual void InitChannelAttrs(CDvmData *pChData);


//˽�г�Ա����
private:
	

//˽�г�Ա�������ʷ���
public:
	void SetChRateString(const CString &strRate);
	void SetChRateIndex(long nIndex);
	void UpdateChDescByChTypeChAng();//202212121 zhouhj  ����ͨ�����͡�ͨ������Զ�����ͨ������

	CString GetChType()
	{
		if (m_nChType == CAPDEVICE_CHTYPE_U)
		{
			return _T("��ѹ");
		}
		else if (m_nChType == CAPDEVICE_CHTYPE_I)
		{
			return _T("����");
		}
		else if (m_nChType == CAPDEVICE_CHTYPE_T)
		{
			return _T("ʱ��");
		}
		else if (m_nChType == CAPDEVICE_CHTYPE_B)
		{
			return _T("״ֵ̬");
		}
		else
		{
			return _T("����");
		}
	}
	void SetChType(const CString &strType)
	{
		if (strType == _T("��ѹ") || strType == _T("Vol"))
		{
			m_nChType = CAPDEVICE_CHTYPE_U;
		}
		else if (strType == _T("����") || strType == _T("Curr") || strType == _T("CurrMeasure"))
		{
			m_nChType = CAPDEVICE_CHTYPE_I;
		}
		else if (strType == _T("ʱ��") || strType == _T("UTCTime"))
		{
			m_nChType = CAPDEVICE_CHTYPE_T;
		}
		//chenling 2024.6.4 ����long m_nChType[STCAPPARSE_DATA_MAX_COUNT]�󶨲���
		else if (strType == _T("����") || strType == _T("other")) 
		{
			m_nChType = CAPDEVICE_CHTYPE_N;
		}
		else if (strType == _T("״ֵ̬") ||strType == _T("StateValue"))
		{
			m_nChType = CAPDEVICE_CHTYPE_B;
		}
		

//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("(CCapDeviceSmvCh)%s;%s;%d;%s"),m_strID.GetString(),m_strName.GetString(),m_nChType,strType.GetString());
	}

public:
	void WriteRcdFile_Comtrade(double *pdLong, long nCount, const CString &strComtradeFile);
	virtual void UpdateChTypeAndLength(WORD wChType,WORD wLength);
	virtual void InitAfterSetChType();
};

CString st_GetCapDeviceChRateString(long nIndex);
float st_GetCapDeviceChRate(long nIndex);
long st_GetCapDeviceChRateIndex(const CString &strID);
void st_AddCapDeviceChRateTo(CComboBox *pComboBox);
float st_GetCapDeviceSVRate(CExBaseObject* pSmvCh,BOOL bDCFT3 = FALSE);//zhouhj 2023.11.24 ����2����Ƿ�Ϊ��ֱFT3ģʽ

