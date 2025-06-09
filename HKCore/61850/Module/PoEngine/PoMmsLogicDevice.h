
#pragma once

#include "PoMmsDataSet.h"
// CPoMmsLogicDevice ����Ŀ��

class CPoMmsLogicDevice
{
public:
	ACSI_NODE *m_pACSI_NODE;  //�豸��ָ��
	LD_NODE *m_pLD_NODE;      //�߼��豸��ָ�룬�����ڴ�ͳ��CPU
	//	DWORD m_dwNodeType;       //�ڵ������
	//���ݵ�����
	tagDA *m_pTagDA;
	DWORD m_dw_tagDA_Type;    

	static CPoMmsLogicDevice* _New_CDeviceNode_LD(ACSI_NODE *pACSI_NODE, LD_NODE *pLD_NODE)
	{
		ASSERT (pLD_NODE != NULL && pACSI_NODE != NULL);
		CPoMmsLogicDevice *pLDevice = new CPoMmsLogicDevice();
		pLDevice->m_pACSI_NODE = pACSI_NODE;  //�豸��ָ��
		pLDevice->m_pLD_NODE = pLD_NODE;      //�߼��豸��ָ�룬�����ڴ�ͳ��CPU
		return pLDevice;
	}

public:
	CPoMmsLogicDevice();
	virtual ~CPoMmsLogicDevice();

	virtual void OnFinalRelease();

public:
	virtual CPoMmsDataSet* GetItem(long nIndex);
	virtual CPoMmsDataSet* FindDataSet(const CString &strDataSetPath);

	CString GetName(void);
	void SetName(const CString &newVal);
	CString GetID(void);
	void SetID(const CString &newVal);
	long GetCount(void);
	CPoMmsData* FindData(const CString &strPath);
	CString GetXmlData(void);
	long SetXmlData(const CString &strXmlData);
};


