//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttTestGridDefine.h  CSttTestGridDefine

#pragma once

#include "SttTestGridDefineGlobal.h"


#include "SttGdTestMacro.h"

class CSttTestGridDefine : public CExBaseList
{
public:
	CSttTestGridDefine();
	virtual ~CSttTestGridDefine();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTTESTGRIDDEFINE;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestGridDefineXmlRWKeys::CSttTestGridDefineKey();     }
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

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	CSttGdGridInst* GetGridInst(const CString &strMacroID,const CString &strInstID);
};

