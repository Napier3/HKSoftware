#pragma once
#include "../../../../module/baseclass/exbaselist.h"
#include "DeviceTypePathXmlKeys.h"
#include "DeviceType.h"

class CDeviceTypePath :	public CExBaseList
{
public:
	CDeviceTypePath(void);
	virtual ~CDeviceTypePath(void);

//	virtual UINT GetClassID(){return PDCLASSID_PATH;};
	virtual BSTR GetXmlElementKey()  {      return CDeviceTypePathXmlKeys::g_pXmlRWKeys->m_strPath;     }


	//串行化
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	//创建子对象
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail);

	CString m_strPath;
};
