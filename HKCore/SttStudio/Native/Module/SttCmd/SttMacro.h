//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttMacro.h  CSttMacro

#pragma once

#include "SttCmdDefineGlobal.h"
#include "SttParas.h"

class CSttMacro : public CExBaseList//CTestMacro
{
public:
	CSttMacro();
	virtual ~CSttMacro();

    CString  m_strVersion;
    CString  m_strType;
    CString  m_strRemark;

//���غ���
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTMACRO;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttMacroKey();     }
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

    virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
    virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

    //ReadXml
    virtual long XmlReadChildren(CXmlRWNodeListBase &oNodes, CXmlRWKeys *pXmlRWKeys);

    //WriteXml
    //virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:
	CSttParas *m_pParas;
	CSttResults *m_pResults;
	CSttSearchResults *m_pSearchResults;//zhouhj 20210925 ������������
	bool m_bCreateMacroChild;

//˽�г�Ա�������ʷ���
public:
	CSttParas* GetParas();
	CSttResults* GetResults();
	CSttSearchResults* GetSearchResults();//zhouhj 20210925 ������������
	void SetCreateMacroChild(bool bCreateMacroChild)	{	m_bCreateMacroChild = bCreateMacroChild;	}
	void SetParameter(const CString &strMacroID, CDataGroup *pParas);

//���Ա������ʷ���
public:
};

