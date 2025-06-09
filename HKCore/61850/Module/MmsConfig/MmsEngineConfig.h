//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
	long m_nAutoGenModelDatas;//�Զ�����ģ���еĹ̶����ݣ�����װ��ʶ���롢װ�ó���汾��Ϣ��PROT�����װ�ò������ݼ���

//���غ���
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

//˽�г�Ա����
private:
	CString GetMmsEngineConfigFile();

//˽�г�Ա�������ʷ���
public:
	BOOL IsDatasetUse(const CString &strDsName);
	BOOL IsDatasetUse(const char *pDsName);

	void ReadMmsEngineConfig();
	void SaveMmsEngineConfig();
	CMmsEngineDatasets* GetMmsDatasetsCfg();

	char* mms_GetDatasetKey(const CString &strDatasetID);
};

