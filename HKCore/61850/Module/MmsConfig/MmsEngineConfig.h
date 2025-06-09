//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MmsEngineConfig.h  CMmsEngineConfig

#pragma once

#include "MmsEngineConfigGlobal.h"


#include "MmsEngineDatasets.h"
// #include "MmsEngineLocalIPs.h"

class CMmsEngineConfig : public CExBaseList
{
public:
	CMmsEngineConfig();
	virtual ~CMmsEngineConfig();

	long m_nDebugMode;
	long m_nEnumLDAfterReadXml;
	long m_nMmsEnumLogCtrl;
	long m_nExitAppForException;
	long m_nUseDvmMapFile;
	long m_nSwitchSGWait;
	long m_bMultDevModel;
	long m_nExportModelAuto;
	long m_nUseDsDout;
	long m_nAutoGenModelDatas;//自动生成模型中的固定数据，包括装置识别码、装置程序版本信息到PROT下面的装置参数数据集中

//重载函数
public:
	virtual UINT GetClassID() {    return MSCFGCLASSID_CMMSENGINECONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CMmsEngineConfigXmlRWKeys::CMmsEngineConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CString GetMmsEngineConfigFile();

//私有成员变量访问方法
public:
	BOOL IsDatasetUse(const CString &strDsName);
	BOOL IsDatasetUse(const char *pDsName);

	void ReadMmsEngineConfig();
	void SaveMmsEngineConfig();
	CMmsEngineDatasets* GetMmsDatasetsCfg();

	char* mms_GetDatasetKey(const CString &strDatasetID);
};

