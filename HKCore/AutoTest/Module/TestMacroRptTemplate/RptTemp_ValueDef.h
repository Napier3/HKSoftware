//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptTemp_ValueDef.h  CRptTemp_ValueDef

#pragma once

#include "TestMacroRptTemplateGlobal.h"
#include "../../../Module/DataMngr/DataGroup.h"



class CRptTemp_ValueDef : public CExBaseObject
{
public:
	CRptTemp_ValueDef();
	virtual ~CRptTemp_ValueDef();


	CString  m_strVal;
	CString  m_strProcess;
	CString  m_strPrecision;
	long  m_nPrecision;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_VALUEDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_ValueDefKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	CDataGroup* GetItemsTec();
	BOOL UpdatePrecision();
};

