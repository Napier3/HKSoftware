#pragma once

#include "../../../../Module/DataMngr/DataGroup.h"
#include "GbSmartGenWzdGlobal.h"

class CGbWzdItemCopy : public CDataGroup
{
public:
	CGbWzdItemCopy(void);
	virtual ~CGbWzdItemCopy(void);

	CString m_strParentItemsID;
	CString m_strItemsName;
	CString m_strItemsID;
	CString m_strItemType;  //Ŀǰ��֧�֣�macrotest, commcmd, items 
	CString m_strItemPath;  //��������Ŀ��·����Ϣ

public:
	virtual UINT GetClassID() {    return DVMCLASSID_GBWZDITEMCOPY;   }
	virtual BSTR GetXmlElementKey()  {      return CGbSmartGenWzdXmlRWKeys::CGbWzdItemCopyKey();     }
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
	void GetItemCopyPath(CString &strItemPath);  //��ȡ��Ŀ·��

};
