//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptTemp_TextDef.h  CRptTemp_TextDef

#pragma once

#include "TestMacroRptTemplateGlobal.h"
#include "RptTemp_Enable.h"
#include "../../../Module/DataMngr/DataGroup.h"



class CRptTemp_TextDef : public CExBaseList
{
public:
	CRptTemp_TextDef();
	virtual ~CRptTemp_TextDef();


	CString  m_strFont;   //����
	float     m_fSize;     //�ֺ�
	long     m_nBold;     //�Ƿ�Ӵ�
	CString  m_strText;
	CString  m_strData1_Id;
	CString  m_strData2_Id;
	CString  m_strData3_Id;
	CString  m_strData4_Id;
	CString  m_strData5_Id;
	CString  m_strData6_Id;
	CString  m_strHAlignType; //�ı�ˮƽ���뷽ʽ AlignLeft�Ϳ�ֵ:����� AlignRight���Ҷ��� AlignCenter��ˮƽ���� //ftt 2024.12.10

//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_TEXTDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_TextDefKey();     }
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
	CRptTemp_Enable *m_pEnable;

//˽�г�Ա�������ʷ���
public:
	CRptTemp_Enable* GetEnable()	{	return m_pEnable;	}

//���Ա������ʷ���
public:
	BOOL IsEnable(CExBaseList *pParas);
	CDataGroup* GetItemsTec();
};

