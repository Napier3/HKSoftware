//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgGooseDataBase.h  CIecCfgGooseDataBase

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataBase.h"
#define  STGOOSE_CHANNEL_NUM  8

class CIecCfgGooseDataBase : public CIecCfgDataBase
{
public:
	CIecCfgGooseDataBase();
	virtual ~CIecCfgGooseDataBase();


	CString  m_strDestAddress;
	CString  m_strSrcAddress;
	DWORD  m_dwAppID;
	long  m_dwVLandPriority;
	DWORD  m_dwVLandID;
	DWORD  m_dwVersion;
	CString  m_strGooseId;
	CString  m_strDataSet;
	CString  m_strDataSetDesc;
	CString  m_strgocbRef;
	CString  m_strgocbIED;
	long  m_bTest;
	long  m_nT0;		//�ȶ��������ش�ʱ��
	long  m_nT1;		//��̴���ʱ��
	long  m_nT2;		//��������Ե�һ��GOOSE������ʱ
	long  m_nT3;
	long  m_nTGroup;
	CString  m_strTQuality;		//ʱ��Ʒ��
	long  m_bNdsCom;
	long  m_nLiveTime;

	//2020-6-29 lijunqing ���ӵ㳤�ȣ����ַ���ת����ʱ������ڴ����
	BYTE m_byteDestAddress[10];
	BYTE m_byteSrcAddresss[10];

//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGGOOSEDATABASE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgGooseDataBaseKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual void InitAfterRead();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	long GetIndex();
	virtual DWORD GetAppID() {return m_dwAppID;}
	virtual void SetAT02D_ChannelID(CExBaseList *pGinList,long &nCBIndex);//�ܺ�� 20200616  ����AT02����
	virtual BOOL OpenCfgDefaultConfigFile();

#ifdef _PSX_IDE_QT_
	virtual BOOL SetCfgDataValue(long nDataID, unsigned long long &vValue);
	virtual BOOL GetCfgDataValue(long nDataID, unsigned long long &vValue);
	virtual BOOL IsEqualCfgDataValue(long nDataID, unsigned long long &vValue);
#else
	virtual BOOL SetCfgDataValue(long nDataID, VARIANT &vValue);
	virtual BOOL GetCfgDataValue(long nDataID, VARIANT &vValue);
	virtual BOOL IsEqualCfgDataValue(long nDataID, VARIANT &vValue);
#endif
};

