#pragma  once

#include "DataSetGroup.h"

class CTestGlobalDatasMngr : public CExBaseList
{
public:
	CTestGlobalDatasMngr();
	virtual ~CTestGlobalDatasMngr();

	CDataSet *m_pTestApp;
	CDataSet *m_pDeviceAttr;

public:
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()																		{		return GBCLASSID_TESTGLOBALDATASMNGR;				}
	virtual BSTR GetXmlElementKey()													{      return CGbXMLKeys::g_pGbXMLKeys->m_strTestGlobalDatasMngrKey;     }
	
	virtual void InitAfterRead();
	virtual CBaseObject* Clone();

public:
	void SetTestGlobaoDatasMngrs(CDataSet *pDataset);
	void SetTestGlobaoDatas_DeviceAttr(CDataSet *pDataset);
	void SetTestGlobaoDatas_TestApp(CDataSet *pDataset);

	void SetCommConfig_DvmFile(const CString &strDvmFile);
	void SetCommConfig(CDataGroup *pCommConfig);
	void SetCommConfigs(CDataGroup *pCommConfigs);
	CDataGroup* GetCommConfig(BOOL bCreateNew);
	CDataGroup* GetCommConfigs(BOOL bCreateNew);

	//2023-6-17  lijunqing ≤‚ ‘“«∂®“Â
	void SetTestApps(CDvmDataset *pTestApps);
	void SetTestApps(CDataGroup *pTestApps);
	CDataGroup* GetTestApps(BOOL bCreateNew);
	void UpdateTestApps(CDataGroup *pTestApps);
	CDataGroup* FindTestApps(CDataGroup *pTestApps);
	void AddTestAppInfo(const CString &strID, const CString&strValue);

};

