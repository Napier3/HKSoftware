//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DvmLogs.h  CDvmLogs

#pragma once

#include "DataMngrGlobal.h"


#include "DvmLog.h"

class CDvmLogs : public CExBaseList
{
public:
	CDvmLogs();
	virtual ~CDvmLogs();

//���غ���
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDVMLOGS;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDvmLogsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CanPaste(UINT nClassID);
	virtual void InitAfterRead();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	long ClearByReserved(DWORD dwReserved);

};
