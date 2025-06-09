//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfg2MData.h  CIecCfg2MData

#pragma once

#include "IecCfg6044CommonData.h"


class CIecCfg2MData : public CIecCfg6044CommonData
{
public:
	CIecCfg2MData();
	virtual ~CIecCfg2MData();

//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG2MDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgData2MKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual CString GetCfgDefaultConfigFile()	{	return _T("Cfg2M.xml");	}

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual CString GetCfgDataName(long nIndex)
	{
		CString strName;
		strName.Format(_T("2M(%d)"), nIndex);
		return strName;
	}
	virtual CString GetCfgDataShortName(long nIndex)
	{
		CString strName;
		strName.Format(_T("2M��%d��"), nIndex+1);
		return strName;
	}

	virtual void GetCommData(CIecCfgDataSmvCommon *pCommon);
	virtual void InitByCommData(CIecCfgDataSmvCommon *pCommon);

};

