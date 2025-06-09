//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Keys.h  CKeys

#pragma once

#include "IecfgGenMngrGlobal.h"
#include "../CfgDataMngr/IecCfgDatasBase.h"

#include "Key.h"

class CKeys : public CExBaseList
{
public:
	CKeys();
	virtual ~CKeys();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CKEYS;   }
	virtual BSTR GetXmlElementKey()  {      return CIecfgGenMngrXmlRWKeys::CKeysKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIecfgGenMngrXmlRWKeys::CKeysKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIecfgGenMngrXmlRWKeys::CKeyKey();     }
	virtual CExBaseObject* DB_CreateNewChild();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	void GetKeys(CStringArray &astrDesc);
	CIecCfgDataBase* FindIecCfgData(CIecCfgDatasBase *pIecCfgDatasBase);
	BOOL IsMatchSuccess(const CString &strName);
};

