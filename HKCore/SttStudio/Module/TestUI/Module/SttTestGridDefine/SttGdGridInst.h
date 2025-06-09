//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttGdGridInst.h  CSttGdGridInst

#pragma once

#include "SttTestGridDefineGlobal.h"


#include "SttGdInst_Cols.h"
#include "SttGdCondition.h"

class CSttGdGridInst : public CExBaseList
{
public:
	CSttGdGridInst();
	virtual ~CSttGdGridInst();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTGDGRIDINST;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestGridDefineXmlRWKeys::CSttGdGridInstKey();     }
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
	CSttGdInst_Cols *m_pSttGdInst_Cols;

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	long GetColCount();
};

