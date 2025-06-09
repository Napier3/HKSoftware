#pragma once

#include "GbWzdXItemBase.h"

class CGbWzdItemEdit : public CGbWzdXItemBase
{
public:
	CGbWzdItemEdit(void);
	virtual ~CGbWzdItemEdit(void);

	CString m_strItemsID_Old;  //��¼�ı༭ǰ����Ŀ��ID
	long m_nRepeatTimes;  //�ظ�����
	//shaolei 2023-6-21  �Ƿ���Ϊ���⡢����ȼ�
	long m_nRptTitle;
	long m_nTitleLevel;

public:
	virtual UINT GetClassID() {    return DVMCLASSID_GBWZDITEMEDIT;   }
	virtual BSTR GetXmlElementKey()  {      return CGbSmartGenWzdXmlRWKeys::CGbWzdItemEditKey();     }
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
