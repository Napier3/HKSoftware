#pragma once
#include "CapDeviceSmvCh.h"
class CCapDeviceRcdCh : public CCapDeviceSmvCh
{
public:
	CCapDeviceRcdCh();
	virtual ~CCapDeviceRcdCh();
	CString GetModuleName();

	long m_nEType;//��¼���� 0-��Ч��1-��ѹ��2-������3-��Դ��������4-��Դ������
	float m_fSwitchVolt;//��Դ��������ת��ֵ
	long m_nMeasGear;//�ɼ���λ
	float m_dClampRate;//��ǯ����
//	CString m_strRcdChName;  //ͨ����¼���ļ�ʹ�õ�����
	double m_dPrimValue; //һ�β�ֵ
	double m_dSecondValue; //���β�ֵ

	DWORD m_dwComtradeChData;  //2024.9.23 zhangyq Comtrade�ļ���Ӧָ��

	virtual UINT GetClassID(){ return CPDCLASSID_RCDCH; };
};

