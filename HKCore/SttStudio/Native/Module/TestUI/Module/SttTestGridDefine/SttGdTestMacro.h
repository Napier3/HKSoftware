//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttGdTestMacro.h  CSttGdTestMacro

#pragma once

#include "SttTestGridDefineGlobal.h"


#include "SttGdDataProcess.h"
#include "SttGdGridDefine.h"
#include "SttGdGridInsts.h"

class CSttGdTestMacro : public CExBaseList
{
public:
	CSttGdTestMacro();
	virtual ~CSttGdTestMacro();


	CString  m_strMacroID;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTGDTESTMACRO;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestGridDefineXmlRWKeys::CSttGdTestMacroKey();     }
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
};

