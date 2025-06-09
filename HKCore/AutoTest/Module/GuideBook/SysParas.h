#pragma once

#include "GuideBookDefine.h"
// #include "Set.h"
#include "DataSet.h"

#define SYSPARASID_SYS				0
#define SYSPARASID_TEST			1
const CString g_strSysParaChild_unitTime = _T("ms"); 

class CSysParas :public CDataSet
{
public:
	CSysParas();
	virtual ~CSysParas(void);

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()												{		return GBCLASSID_DEVICE_SYSPARAS;	}
	virtual BSTR GetXmlElementKey()							{      return CGbXMLKeys::g_pGbXMLKeys->m_strSysParasKey;     }

	BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

	//Interface mathods
	CDataSet*  GetDatas()					 {		return this;		}

	BOOL FindTimeParas(CExBaseList *pTimeList);//查找系统参数中的时间参数，用于通讯命令的通讯前/后延时 添加2010-12-27

protected:

private:

};

class CTestParas : public CSysParas
{
public:
	CTestParas();
	virtual ~CTestParas(){}

public:
	virtual UINT GetClassID()								{		return GBCLASSID_DEVICE_TESTPARAS;						}
	virtual BSTR GetXmlElementKey()							{      return CGbXMLKeys::g_pGbXMLKeys->m_strTestParasKey;		}
	virtual CBaseObject* Clone();
};