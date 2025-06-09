#pragma once

#include "GbWzdXItemBase.h"

//单独添加的电气量项目，例如：硬件通道映射、系统参数配置、IEC61850Config
class CGbWzdMacroTestAdd : public CGbWzdXItemBase
{
public:
	CGbWzdMacroTestAdd(void);
	virtual ~CGbWzdMacroTestAdd(void);

	CString m_strTestMacroUI;

public:
	virtual UINT GetClassID() {    return DVMCLASSID_GBWZDMACROTESTADD;   }
	virtual BSTR GetXmlElementKey()  {      return CGbSmartGenWzdXmlRWKeys::CGbWzdMacroTestAddKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:

};
