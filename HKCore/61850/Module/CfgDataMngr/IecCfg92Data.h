//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgData92.h  CIecCfgData92

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgSmvDataBase.h"

#include "IecCfg92Chs.h"
#include "IecCfg92ChQuality.h"

#include "../../../Module/DataMngr/DvmDataset.h"

typedef CTLinkListEx<CIecCfg92ChQuality>  CIecCfg92ChQualityList;


class CIecCfg92Data : public CIecCfgSmvDataBase
{
public:
	CIecCfg92Data();
	virtual ~CIecCfg92Data();


	CString  m_strDestAddress;
	CString  m_strSrcAddress;
	DWORD  m_dwAppID;
	long  m_nPriority;
	//DWORD  m_dwSVID;
	CString m_strSVID;
	DWORD  m_dwVID;
	DWORD  m_dwVersion;
	//DWORD  m_dwDataSet;
	CString m_strDataSet;
	long  m_nCTBit;
	long  m_nPTBit;
	long  m_nDelay;
	long  m_nUseSampRate;
	long  m_nUseDataSet;
	long  m_nUseSampleTime;
	long  m_nUseRefreshTime;
	long  m_nUseEncrupt;
	long  m_nVoltateRate;
	long  m_nCurrRate;


	//2020-6-29 lijunqing 增加点长度，有字符串转换的时候避免内存溢出
	BYTE m_byteDestAddress[10];
	BYTE m_byteSrcAddresss[10];

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG92DATA;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgData92Key();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();

	virtual CString GetCfgDefaultConfigFile()	{	return _T("Cfg92.xml");	}
	virtual DWORD GetAppID() {return m_dwAppID;}
	virtual BOOL OpenCfgDefaultConfigFile();

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual void GetQualityList(CIecCfg92ChQualityList *pList);

	BOOL IsAllChSetTest();//判断是否所有的通道都置检修了
	void SetChsQualityValue(DWORD dwQulity);
	void SetTestState(BOOL bTest);

	virtual CString GetCfgDataName(long nIndex)
	{
		CString strName;
        strName.Format(_T("9-2(%d): %s"), nIndex, m_strDestAddress.GetString());
		return strName;
	}
	virtual CString GetCfgDataShortName(long nIndex)
	{
		CString strName;
		strName.Format(_T("9-2第%d组"), nIndex+1);
		return strName;
	}

#ifdef _USE_IN_AT02D_MODE_
	virtual void SetAT02D_ChannelID(CExBaseList *pSVList,long &nCBIndex);//周宏军 20200616  增加AT02配置
	virtual void AddAT02D_Dataset(CDvmDataset *pCurDataset,BOOL bHasHarm,BOOL bhasMUTestParas = FALSE);
	virtual void AT02D_MapChannelID(CIecCfg92Data *pIecCfg92Data);
	virtual BOOL HasCurAndVolChannelType();
#endif

#ifdef _PSX_IDE_QT_
	virtual BOOL SetCfgDataValue(long nDataID, unsigned long long &vValuee);
	virtual BOOL GetCfgDataValue(long nDataID, unsigned long long &vValue);
	virtual BOOL IsEqualCfgDataValue(long nDataID, unsigned long long &vValue);
#else
	virtual BOOL SetCfgDataValue(long nDataID, VARIANT &vValuee);
	virtual BOOL GetCfgDataValue(long nDataID, VARIANT &vValue);
	virtual BOOL IsEqualCfgDataValue(long nDataID, VARIANT &vValue);
#endif
};

