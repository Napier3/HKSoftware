//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptTemp_Text.h  CRptTemp_Text

#pragma once

#include "TestMacroRptTemplateGlobal.h"



class CRptTemp_Text : public CExBaseObject
{
public:
	CRptTemp_Text();
	virtual ~CRptTemp_Text();


	CString  m_strText;
	CString  m_strFont;   //����
	float     m_fSize;     //�ֺ�
	long     m_nBold;     //�Ƿ�Ӵ�
	CString  m_strHAlignType; //�ı�ˮƽ���뷽ʽ AlignLeft�Ϳ�ֵ:����� AlignRight���Ҷ��� AlignCenter��ˮƽ���� //ftt 2024.12.10

	CString  m_strData1_Id;
	CString  m_strData2_Id;
	CString  m_strData3_Id;
	CString  m_strData4_Id;
	CString  m_strData5_Id;
	CString  m_strData6_Id;
	CString  m_strTextFormat;//���ڱ������õĹ��򣬷���ʵʱ����
	void *m_pGbItemBase;  //�󶨵Ĳ�����Ŀ��CGbItemBase����CSttItemBase��
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_TEXT;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_TextKey();     }
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
};

