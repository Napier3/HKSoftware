//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XFileType.h  CXFileType

#pragma once

#include "XFile.h"
#include "XFolder.h"

#include "../DataMngr/DataMngrGlobal.h"

class CXFileTypePostfix : public CExBaseObject
{
public:
	CXFileTypePostfix();
	virtual ~CXFileTypePostfix();

public:
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	virtual UINT GetClassID() {    return CLASSID_XFILE_POSTFIX;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDataTypeValueKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

};

class CXFileType : public CExBaseList
{
public:
	CXFileType();
	virtual ~CXFileType();

	CString m_strExe;
	CString m_strRunMode;

//���غ���
public:
	virtual UINT GetClassID() {    return CLASSID_XFILE_TYPE;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDataTypeKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
// 	virtual void InitAfterRead();
// 	virtual BOOL IsEqualOwn(CBaseObject* pObj);
// 	virtual BOOL CopyOwn(CBaseObject* pDest);
// 	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

public:
	CXFileTypePostfix* AddNewPostfix(const CString &strName, const CString &strID);
	void InitXFilePostfix(CExBaseList &oList, BOOL bOnllySearchMainTypeFile);
	void GetXFileDlgString(CString &strXFileFilter, CString &strXFilePostFix);
	BOOL ValidateFilePostfix(const CString &strFilePostfix);
	BOOL IsRunModeSingle()	{	return m_strRunMode == _T("single");	}
	BOOL IsRunModeMulti()	{	return m_strRunMode == _T("multi");	}

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	BOOL FindFileType(const CString &strFilePostfix);
	virtual BOOL  XCopyFile(CXFile *pSrcFile, CXFolder *pFolder, BOOL bFailIfExists);
	virtual BOOL  XCopyFile(CXFile *pSrcFile, const CString &strFolder, BOOL bFailIfExists);
	virtual BOOL XImportFile(const CString &strFile, CXFolder *pFolder, BOOL bFailIfExists);
	virtual BOOL XOpenXFile(CXFile *pFile);
	virtual BOOL XDeleteXFile(CXFile *pFile);
	virtual BOOL XEditXFile(CXFile *pFile, const CString &strDestName);

};

