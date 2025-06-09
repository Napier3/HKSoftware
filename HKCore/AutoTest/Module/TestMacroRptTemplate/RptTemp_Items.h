//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptTemp_Items.h  CRptTemp_Items

#pragma once

#include "TestMacroRptTemplateGlobal.h"


#include "RptTemp_MacroCharItems.h"
#include "RptTemp_MacroTest.h"
#include "RptTemp_ReportTemplate.h"

class CRptTemp_Items : public CExBaseList
{
public:
	CRptTemp_Items();
	virtual ~CRptTemp_Items();


	long  m_nRpt_Title;
	long  m_ntitle_level;

private:
	//�Ƿ��Ѿ����ɡ����rpt-mode=items�ġ�
	BOOL m_bHasGen;  
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_ITEMS;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_ItemsKey();     }
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
	long GetMacroTestCount();
	CRptTemp_MacroTest* GetMacroTestByIndex(long nIndex);

	BOOL IsHasGen()	{	return m_bHasGen;	}
	void SetHasGen(BOOL bHasGen)	{	m_bHasGen = bHasGen;	}
};

