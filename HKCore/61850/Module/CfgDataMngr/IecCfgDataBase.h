//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDataBase.h  CIecCfgDataBase

#pragma once

#include "IecCfgDataMngrGlobal.h"
#include "IecCfgDataChBase.h"
#include "IecCfgChsBase.h"
// #include "ArtAmpDigdatas.h"

#ifdef IECFG_USE_KEYDB
#include "../../../Module/KeyDb/XKeyDB.h"
#include "../../../Module/KeyDb/XMatchList.h"
#endif

class CIecCfgDataBase : public CExBaseList
{
public:
	CIecCfgDataBase();
	virtual ~CIecCfgDataBase();
#ifdef IECFG_USE_KEYDB
	CXMatchList *m_pMatchList;
	void InitMatchList(CXKeyDB *pKeyDB);
#endif


	long  m_nUseFlag;
	long  m_nChannelNum;
	long  m_nFiberIndex;//从0开始编号,即0代表光口1
	long  m_nFiber2Index;//zhouhj 用于AT02D光口
	long  m_nSyn;
	CString m_strIedRefDesc;

	long  m_nCfgDataViewState;

	CIecCfgChsBase *m_pCfgChs;
	CExBaseObject  *m_pSclRef;

	CString m_strDvmDatasetID;  //2022-5-7 lijunqing 临时用于记录设备数据模型的ID

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGDATABASE;   }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDataBaseKey();     }
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);

	virtual long GetChannelNum();

	//保存为缺省配置文件
	virtual BOOL SaveCfgDefaultConfigFile();
	virtual BOOL OpenCfgDefaultConfigFile();
	virtual CString GetCfgDefaultConfigFile() = 0;
	virtual void GetCfgDefaultConfigFile(CString &strFile);

	virtual void InitForSclRead();
	virtual CString GetCfgDataName(long nIndex)=0;
	virtual CString GetCfgDataShortName(long nIndex)=0;
	virtual CString GetCfgDataName();
	virtual CString GetCfgDataShortName();

	virtual BOOL SaveCfgDataTempFile();
	virtual BOOL OpenCfgDataTempFile();
	virtual DWORD GetAppID() {return 0;}

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual void RemoveTailCh(long nCountRemove, CExBaseList &oListRemove);
	virtual BOOL SetChannelNum(long nChannelNum);
	virtual long GetChannels(CExBaseList &oListCh);
	virtual void SetAT02D_ChannelID(CExBaseList *pGinList,long &nCBIndex){}
	void InitChs(UINT nClassID);
	long GetCfgDataIndex();
// 	virtual void CalArtAmpDigdatas(CArtAmpDigdatas *pArtAmpDigdatas, long &nHdCnIndex);

	CIecCfgDataChBase* GetCfgDataCh(int nIndex);		//yyj

#ifdef _PSX_IDE_QT_
	virtual BOOL SetCfgDataValue(long nDataID, unsigned long long &vValue);
	virtual BOOL SetCfgDataValues(long nDataID, unsigned long long &vValue);
	virtual BOOL GetCfgDataValue(long nDataID, unsigned long long &vValue);
	virtual BOOL IsEqualCfgDataValue(long nDataID, unsigned long long &vValue);
#else
	virtual BOOL SetCfgDataValue(long nDataID, VARIANT &vValue);
	virtual BOOL GetCfgDataValue(long nDataID, VARIANT &vValue);
	virtual BOOL IsEqualCfgDataValue(long nDataID, VARIANT &vValue);
#endif

	virtual BOOL ValidateFiberIndex();
	virtual long GetAppFiberCount();
};

void iecfg_GetCfgDataValueMac(const CString  &strMac, BYTE *pbyteMac);

#ifdef _PSX_IDE_QT_
void iecfg_GetCfgDataValueMac(const CString  &strMac, unsigned long long &vValue);
void iecfg_SetCfgDataValueMac(CString  &strMac, unsigned long long &vValue);
#else
void iecfg_GetCfgDataValueMac(const CString  &strMac, VARIANT &vValue);
void iecfg_SetCfgDataValueMac(CString  &strMac, VARIANT &vValue);
#endif
