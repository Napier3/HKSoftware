//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RcdDir.h  CRcdDir

#pragma once

#include "MmsRcdFilesMngrGlobal.h"


#include "RcdFile.h"

class CRcdDir : public CExBaseList
{
public:
	CRcdDir();
	virtual ~CRcdDir();


	long  m_nDirSize;
	double  m_fDirTime;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRCDDIR;   }
	virtual BSTR GetXmlElementKey()  {      return CMmsRcdFilesMngrXmlRWKeys::CRcdDirKey();     }
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

