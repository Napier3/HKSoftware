//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AinExpandMngr.h  CAinExpandMngr

#pragma once

#include "AinExpand.h"

class CAinExpandMngr : public CExBaseList
{
public:
	CAinExpandMngr();
	virtual ~CAinExpandMngr();

	static const CString g_strAinExpandConfigFile;

//���غ���
public:
	virtual UINT GetClassID() {    return GBCLASSID_CAINEXPANDMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CGbXMLKeys::CAinExpandMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	CString GetAinExpandConfigFile();

//˽�г�Ա�������ʷ���
public:
	void OpenAinExpandConfigFile();
};

