#pragma  once

#include "../../../Module/DataMngr/DvmDevice.h"
#include "../../../Protocol/Module/Engine/DeviceModel/DeviceModelXmlKeys.h"
#include "../../../Module/API/FileApi.h"
#include "../GuideBook/GuideBookDefine.h"

class CTestGlobalDefine : public CDvmLogicDevice
{
public:
	CTestGlobalDefine();
	virtual ~CTestGlobalDefine();

	CDvmDataset *m_pExpandDatas;
	CDvmDataset *m_pExpandDatasAutoSet;
	CDvmDataset *m_pReportSNGen;
	CDvmDataset *m_pTaskReportSNGen;
	CDvmDataset *m_pDeviceAttrsDefine;
	CDvmDataset *m_pTestAppDefine;

	long m_nShowWordRpt;

// #ifndef GUIDEBOOK_DEV_MODE
// 	CDeviceCmmConfig* m_pDeviceCmmConfig;
// #endif
	
public:
	//串行化
	virtual BSTR GetXmlElementKey();

	//创建子对象
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	BOOL OpenTestDefineFile(const CString &strFile, BSTR bstrElementKey, CXmlRWKeys *pXmlRWKeys);
	BOOL SaveTestDefineFile(CXmlRWKeys *pXmlRWKeys);

private:
	CString m_strTestGlobalDefineFile;
};

