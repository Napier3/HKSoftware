//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptTemp_TitleDef.h  CRptTemp_TitleDef

#pragma once

#include "TestMacroRptTemplateGlobal.h"
class CRptTemp_Items;

class CRptTemp_TitleDef : public CExBaseObject
{
public:
	CRptTemp_TitleDef();
	virtual ~CRptTemp_TitleDef();


	long  m_nLevel;     //����������items�ڵ�ı���ȼ�
	CString  m_strText;
	CString  m_strItem_Id;
	long  m_nItem_Level;
	long  m_nItem_Level_2;
	long  m_nItem_Level_3;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_TITLEDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_TitleDefKey();     }
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
	long GetTitleLevel();
	CRptTemp_Items* GetFirstItems_UseRptTitle();
};

