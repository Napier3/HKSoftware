//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

//重载函数
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

//私有成员变量
private:
	CSttParas *m_pParas;
	CSttResults *m_pResults;
	CSttSearchResults *m_pSearchResults;//zhouhj 20210925 增加搜索点结果
	bool m_bCreateMacroChild;

//私有成员变量访问方法
public:
	CSttParas* GetParas();
	CSttResults* GetResults();
	CSttSearchResults* GetSearchResults();//zhouhj 20210925 增加搜索点结果
	void SetCreateMacroChild(bool bCreateMacroChild)	{	m_bCreateMacroChild = bCreateMacroChild;	}
	void SetParameter(const CString &strMacroID, CDataGroup *pParas);

//属性变量访问方法
public:
};

