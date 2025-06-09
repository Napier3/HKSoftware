//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GenRule.h  CGenRule

#pragma once

#include "IecfgGenMngrGlobal.h"
#include "../CfgDataMngr/IecCfgDatasMngr.h"


#include "SmvRule.h"
#include "GinRule.h"
#include "GoutRule.h"

class CGenRule : public CExBaseList
{
public:
	CGenRule();
	virtual ~CGenRule();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CGENRULE;   }
	virtual BSTR GetXmlElementKey()  {      return CIecfgGenMngrXmlRWKeys::CGenRuleKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIecfgGenMngrXmlRWKeys::CGenRuleKey();     }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:
	CSmvRule* m_pSmvRule;
	CGinRule* m_pGinRule;
	CGoutRule* m_pGoutRule;

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL GenarateIecCfgDatasMngr(CIecCfgDatasMngr *pIecCfgDatasMngr);
	CSmvRule* GetSmvRule();
	CGinRule* GetGinRule();
	CGoutRule* GetGoutRule();
};

