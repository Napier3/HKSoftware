#pragma  once
#include "../SttCmdDefineGlobal.h"
#include "../../../Module/DataMngr/DvmDataset.h"
#include "../../../Module/DataMngr/DataGroup.h"

class CSttTestGlobalDatasMngr : public CExBaseList
{
public:
	CSttTestGlobalDatasMngr();
	virtual ~CSttTestGlobalDatasMngr();


public:
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()																		{		return STTGBXMLCLASSID_TESTGLOBALDATASMNGR;				}
	virtual BSTR GetXmlElementKey()													{      return CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strTestGlobalDatasMngrKey;     }
	
	virtual void InitAfterRead();
	virtual CBaseObject* Clone();

public:
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

