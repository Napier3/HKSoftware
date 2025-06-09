//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XFileTypes.h  CXFileTypes

#pragma once


#include "XFileType.h"


class CXFileTypes : public CExBaseList
{
public:
	CXFileTypes();
	virtual ~CXFileTypes();

//重载函数
public:
	virtual UINT GetClassID() {    return CLASSID_XFILE_TYPES;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDataTypesKey();     }
// 	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
// 	virtual void InitAfterRead();
// 	virtual BOOL IsEqualOwn(CBaseObject* pObj);
// 	virtual BOOL CopyOwn(CBaseObject* pDest);
// 	virtual CBaseObject* Clone();
// 	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
// 	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	CXFileType* AddFileType(const CString &strName, const CString &strID, const CString &strExe, const CString &strRunMode);
	void InitXFilePostfix(CExBaseList &oList, BOOL bOnllySearchMainTypeFile);
	void GetXFileDlgString(CString &strXFileFilter, CString &strXFilePostFix);
	BOOL ValidateFilePostfix(const CString &strFilePostfix);

	CXFileType* FindFileType(CXFile *pSrcFile);
	CXFileType* FindFileType(const CString &strFilePostfix);

	void GetAllFilePostfix(CExBaseList &list);

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual BOOL XCopyFile(CXFile *pSrcFile, CXFolder *pFolder, BOOL bFailIfExists);
	virtual BOOL XCopyFile(CXFile *pSrcFile, const CString &strFolder, BOOL bFailIfExists);
	virtual BOOL XImportFile(const CString &strFile, CXFolder *pFolder, BOOL bFailIfExists);
	virtual BOOL XOpenXFile(CXFile *pFile);
	virtual BOOL XDeleteXFile(CXFile *pFile);
	virtual BOOL XEditXFile(CXFile *pFile, const CString &strDestName);
};

