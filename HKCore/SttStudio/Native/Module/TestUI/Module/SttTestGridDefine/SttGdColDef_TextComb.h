//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttGdColDef_TextComb.h  CSttGdColDef_TextComb

#pragma once

#include "SttTestGridDefineGlobal.h"



class CSttGdColDef_TextComb : public CExBaseObject
{
public:
	CSttGdColDef_TextComb();
	virtual ~CSttGdColDef_TextComb();


	CString  m_strPrevText;
	CString  m_strAfterText;
	long  m_nWithUnit;
	CString  m_strDecimal;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTGDCOLDEF_TEXTCOMB;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestGridDefineXmlRWKeys::CSttGdColDef_TextCombKey();     }
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

