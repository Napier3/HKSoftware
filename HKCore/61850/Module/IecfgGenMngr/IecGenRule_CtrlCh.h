//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecGenRule_CtrlCh.h  CIecGenRule_CtrlCh

#pragma once

#include "IecfgGenMngrGlobal.h"


#include "IecGenCfgKeys.h"

class CIecGenRule_CtrlCh : public CExBaseList
{
public:
	CIecGenRule_CtrlCh();
	virtual ~CIecGenRule_CtrlCh();


	CString  m_strAppCh;
	CString  m_strChType;
	long  m_nMatchRatio;
	CString m_strPhsID;  //phsA, phsB, phsC
//���غ���
public:
	virtual UINT GetClassID() {    return GENRATECLASSID_CIECGENRULE_CTRLCH;   }
	virtual BSTR GetXmlElementKey()  {      return CIecfgGenMngrXmlRWKeys::CIecGenRule_CtrlChKey();     }
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

