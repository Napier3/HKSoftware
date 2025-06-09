#pragma once
#include "../../../../Module/BaseClass/ExBaseObject.h"
#include "../DeviceModel/DeviceClassIDDefine.h"
#include "DeviceTypePathXmlKeys.h"

class CDeviceType :	public CExBaseObject
{
public:
	CDeviceType(void);
	virtual ~CDeviceType(void);

public:
//	virtual UINT GetClassID(){return PDCLASSID_DEVICE;};
	virtual BSTR GetXmlElementKey()  {      return CDeviceTypePathXmlKeys::g_pXmlRWKeys->m_strDevice;     }


	//´®ÐÐ»¯
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent);
public:
	CString m_strDeviceModelFile;
	CString m_strTemplateFile;
};
