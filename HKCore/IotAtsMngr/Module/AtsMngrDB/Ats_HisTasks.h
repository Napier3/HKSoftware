//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Ats_HisTasks.h  CAts_HisTasks

#pragma once

#include "ATSMNGRGlobal.h"


#include "Ats_HisTask.h"

class CAts_HisTasks : public CExBaseList
{
public:
	CAts_HisTasks();
	virtual ~CAts_HisTasks();


//���غ���
public:
	virtual UINT GetClassID() {    return ATSCLASSID_CATS_HISTASKS;   }
	virtual BSTR GetXmlElementKey()  {      return CATSMNGRXmlRWKeys::CAts_HisTasksKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CATSMNGRXmlRWKeys::CAts_HisTaskKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CATSMNGRXmlRWKeys::CAts_HisTaskKey();     }
	virtual CExBaseObject* DB_CreateNewChild();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

