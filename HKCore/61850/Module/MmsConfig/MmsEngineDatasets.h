//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MmsEngineConfig.h  CMmsEngineDatasets

#pragma once

#include "MmsEngineConfigGlobal.h"


#include "MmsEngineDsCfg.h"

class CMmsEngineDatasets : public CExBaseList
{
public:
	CMmsEngineDatasets();
	virtual ~CMmsEngineDatasets();

//���غ���
public:
	virtual UINT GetClassID() {    return MSCFGCLASSID_CMMSENGINEDATASETS;   }
	virtual BSTR GetXmlElementKey()  {      return CMmsEngineConfigXmlRWKeys::CMmsDatasetsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	BOOL IsDatasetUse(const CString &strDsName);
	BOOL IsDatasetUse(const char *pDsName);

	char* mms_GetDatasetKey(const CString &strDatasetID);
};

