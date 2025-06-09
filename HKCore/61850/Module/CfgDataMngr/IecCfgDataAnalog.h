//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgDataAnalog.h  CIecCfgDataAnalog

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataBase.h"

#include "IecCfgChsAnalog.h"

class CIecCfgDataAnalog : public CIecCfgDataBase
{
public:
	CIecCfgDataAnalog();
	virtual ~CIecCfgDataAnalog();

//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGANALOGDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDataAnalogKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CExBaseObject* pObj);
	virtual BOOL CopyOwn(CExBaseObject* pDest);
	virtual CExBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual CString GetCfgDefaultConfigFile()	{	return _T("CfgAnalog.xml");	}

//˽�г�Ա����
private:
	long m_nDataUse;

//˽�г�Ա�������ʷ���
public:
	virtual CString GetCfgDataName(long nIndex)
	{
		return _T("С�ź�");
	}
	virtual CString GetCfgDataShortName(long nIndex)
	{
		return GetCfgDataName(nIndex);
	}
	long GetDataUse()
	{
		return m_nDataUse;
	}
	void SetDataUse(long nDataUse)
	{
		m_nDataUse = nDataUse;
	}

// 	virtual void CalArtAmpDigdatas(CArtAmpDigdatas *pArtAmpDigdatas, long &nHdCnIndex);

};

