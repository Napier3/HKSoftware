//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PNTplRoot.h  CPNTplRoot

#pragma once

#include "PNTplMngrGlobal.h"


#include "PNTplElement.h"
#include "PNTplEquation.h"
#include "PNTplGroup.h"
#include "PNTplText.h"

class CPNTplRoot : public CExBaseList
{
public:
	CPNTplRoot();
	virtual ~CPNTplRoot();
	

//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CPNTPLROOT;   }
	virtual BSTR GetXmlElementKey()  {      return CPNTplMngrXmlRWKeys::CPNTplRootKey();     }
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

//˽�г�Ա�������ʷ���
public:
};

