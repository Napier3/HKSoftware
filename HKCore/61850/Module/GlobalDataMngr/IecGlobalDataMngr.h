//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecGlobalDataMngr.h  CIecGlobalDataMngr

#pragma once

#include "../../../Module/FilterText/FilterTextMngr.h"

#include "IecSmvChDataType.h"
#include "IecGooseChDataTypeMngr.h"
#include "IecFiberConfig.h"

class CIecGlobalDataMngr : public CExBaseList
{
private:
	CIecGlobalDataMngr();
	virtual ~CIecGlobalDataMngr();

public:
	static CIecGlobalDataMngr* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CIecGlobalDataMngr *g_pGlobal;

private:
	//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes
	CIecFiberConfig *m_pSTPortsConfig;
	CIecFiberConfig *m_pFt3PortsConfig;
	CFilterTextMngr *m_pSclFilterText;
	CFilterTextMngr *m_pStCfgFileFilterText;
	CIecGooseChDataTypeMngr *m_pGooseDataTypeMngr;  
	CIecSmvChDataType* m_pSmvChDataType;        //SMVͨ����������
	CDataType* m_pAnalogChDataType;        //SMVͨ����������
	CDataType* m_pAnalogChType;        //SMVͨ����������
	CDataTypes *m_pCfgQulityDataTypes;    //Ʒ�ʲ�����������
	CDataType *m_pCfgChTypeDataType;	//ͨ��������������
	CDataType *m_pBOutChDataType;	//����ͨ��������������
	CDataTypes *m_pCommonDataTypes;    //ͨ����������
	CDataType *m_p6044SpeedDataType;	//6044�����ٶ�


	CString GetConfigFilePath(const CString &strFileName);
	//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()
	void InitSTPortsConfig();
	void InitFt3PortsConfig();
	void InitSclFilterText();
	void InitStCfgFileFilterText();
	void InitGooseDataTypeMngr();
	void InitSmvDataType();
	void InitAnalogDataType();
	void InitAnalogChType();
	void InitQulityDataTypes();
	void InitCfgChTypeDataType();
	void InitBOutChDataType();
	void Init6044SpeedDataType();
	void InitCommonDataTypeMngr();

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}
	static CIecFiberConfig* GetSTPortsConfig()	{	return g_pGlobal->m_pSTPortsConfig;	}
	static CIecFiberConfig* GetFt3PortsConfig()	{	return g_pGlobal->m_pFt3PortsConfig;	}
	static CFilterTextMngr*  GetSclFilterTextMngr()		{	return g_pGlobal->m_pSclFilterText;		}
	static CFilterTextMngr*  GetCfgFileFilterTextMngr()	{	return g_pGlobal->m_pStCfgFileFilterText;	}
	static CIecGooseChDataTypeMngr* GetGooseDataTypeMngr()	{	return g_pGlobal->m_pGooseDataTypeMngr;	}
	static CIecSmvChDataType* GetSmvDataType()				{	return g_pGlobal->m_pSmvChDataType;			}
	static CDataType* GetAnalogDataType()					{	return g_pGlobal->m_pAnalogChDataType;			}
	static CDataType* GetAnalogChType()					{	return g_pGlobal->m_pAnalogChType;			}
	static CDataTypes* GetCfgQulityDataTypes()			{	return g_pGlobal->m_pCfgQulityDataTypes;			}
	static CDataType* GetCfgChTypeDataType()				{	return g_pGlobal->m_pCfgChTypeDataType;			}
	static CDataType* GetBOutChDataType()					{	return g_pGlobal->m_pBOutChDataType;			}
	static CDataTypes* GetCommonDataTypes()			{	return g_pGlobal->m_pCommonDataTypes;			}
	static CDataType* Get6044SpeedDataType()				{	return g_pGlobal->m_p6044SpeedDataType;			}
//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};

#define ANALOGCHTYPE_T      0x00
#define ANALOGCHTYPE_U      0x01
#define ANALOGCHTYPE_I      0x02
#define ANALOGCHTYPE_NONE   0x0F
#define ANALOGCHTYPE_ALL    0xFF

inline BOOL iecfg_IsTimeCh(CString strID)
{
	strID.MakeUpper();

	if (strID.Find(_T("��ʱ")) >= 0 || strID.Find(_T("�ӳ�")) >= 0 || strID.Find(_T("TRTG")) >= 0)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL GetSmvChTypeAndPhase(const CString &strName,const CString &strID,CString &strChType,CString &strPhase);
