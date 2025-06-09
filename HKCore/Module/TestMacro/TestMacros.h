//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TestMacros.h  CTestMacros

#pragma once

#include "TestMacroGlobal.h"


#include "TestMacro.h"
#include "../DataMngr/DataTypes.h"

//CTestMacros��m_strName��m_strID���Ա����˲��Թ����ļ���������"TestMacro.xml"

class CTestMacros : public CExBaseList
{
public:
	CTestMacros();
	virtual ~CTestMacros();

	CString m_strProgID;
	CString m_strMacroFile;
	CString m_strMacroFilePath;
	CExBaseList m_listMacrosInclude;

private:
	static CString g_strOldMacroTestDataTypeFile;
	BOOL m_bOpenFlag;  //2021-8-14  lijunqing  �����η������ļ�

//���غ���
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTESTMACROS;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTestMacrosKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	CExBaseObject *m_pMacroScriptMngr;	//���Թ�����صĽű��������
	CDataTypes    *m_pDataTypes;

//˽�г�Ա�������ʷ���
public:
	void FreeMacroScriptMngr();
	void SetMacroScriptMngr(CExBaseObject *pMacroScriptMngr);
	CExBaseObject* GetMacroScriptMngr()		{	return m_pMacroScriptMngr;		}
	void OpenDataTypeFile(const CString &strDataTypeFile);
	CDataTypes* GetDataTypes()	{	return m_pDataTypes;	}

	BOOL OpenTestMacroFile(const CString &strMacroFile, const CString &strMacroFileID);

	CTestMacro *GetCloneMacro(const CString& strID);

	//lijunqing  2021-8-15
	void InitParas_Dvm();
	CDataTypeValue* GetDataTypeValue(const CString &strMacroID, const CString &strIDPath, const CString &strValue);
};

class CTestMacrosInclude : public CTestMacros
{
public:
	CTestMacrosInclude();
	virtual ~CTestMacrosInclude();

	CString m_strIncludeFile;

	void OpenMacrosIncludeFile(const CString &strPath);

	//���غ���
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTESTMACROSINCLUDE;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTestMacrosIncludeKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

};

