//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecGenCfgDataMngrRule.h  CIecGenCfgDataMngrRule

#pragma once

#include "IecfgGenMngrGlobal.h"
#include "../CfgDataMngr/IecCfgDatasMngr.h"


#include "IecGenCfgDataMngrRule_SMV.h"
#include "IecGenCfgDataMngrRule_Gin.h"
#include "IecGenCfgDataMngrRule_Gout.h"

class CIecGenCfgDataMngrRule : public CExBaseList
{
public:
	CIecGenCfgDataMngrRule();
	virtual ~CIecGenCfgDataMngrRule();


	CString  m_strGinChFileName;
//���غ���
public:
	virtual UINT GetClassID() {    return GENRATECLASSID_CIECGENCFGDATAMNGRRULE;   }
	virtual BSTR GetXmlElementKey()  {      return CIecfgGenMngrXmlRWKeys::CIecGenCfgDataMngrRuleKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIecfgGenMngrXmlRWKeys::CIecGenCfgDataMngrRuleKey();     }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:
	CIecGenCfgDataMngrRule_SMV* m_pSmvRule;
	CIecGenCfgDataMngrRule_Gin* m_pGinRule;
	CIecGenCfgDataMngrRule_Gout* m_pGoutRule;

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	CIecGenCfgDataMngrRule_SMV* GetSmvRule();
	CIecGenCfgDataMngrRule_Gin* GetGinRule();
	CIecGenCfgDataMngrRule_Gout* GetGoutRule();
};

