//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttMacroUIMngr.h  SttMacroUIMngr

#pragma once

#include "SttTestMacroUIMngrGlobal.h"


#include "UIGroup.h"

class CSttMacroUIMngr : public CExBaseList
{
public:
	CSttMacroUIMngr();
	virtual ~CSttMacroUIMngr();


//���غ���
public:
	virtual UINT GetClassID() {    return UIMNGRCLASSID_STTMACROUIMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestMacroUIMngrXmlRWKeys::SttMacroUIMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	BOOL OpenMacroUIMngrFile();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

