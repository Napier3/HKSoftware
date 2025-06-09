//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
	long  m_nT0;		//稳定条件下重传时间
	long  m_nT1;		//最短传输时间
	long  m_nT2;		//其他组相对第一组GOOSE发送延时
	long  m_nT3;
	long  m_nTGroup;
	CString  m_strTQuality;		//时间品质
	long  m_bNdsCom;
	long  m_nLiveTime;

	//2020-6-29 lijunqing 增加点长度，有字符串转换的时候避免内存溢出
	BYTE m_byteDestAddress[10];
	BYTE m_byteSrcAddresss[10];

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGGOOSEDATABASE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgGooseDataBaseKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual void InitAfterRead();

//私有成员变量
private:

//私有成员变量访问方法
public:
	long GetIndex();
	virtual DWORD GetAppID() {return m_dwAppID;}
	virtual void SetAT02D_ChannelID(CExBaseList *pGinList,long &nCBIndex);//周宏军 20200616  增加AT02配置
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

