//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgFiles.h  CIecCfgFiles

#pragma once

#include "IecCfgToolGlobal.h"


#include "IecCfgFile.h"

class CIecCfgFiles : public CExBaseList
{
public:
	CIecCfgFiles();
	virtual ~CIecCfgFiles();

	long m_nViewOnlyUsedInChs;
	long m_nViewChsPath;//显示通道路径信息

//重载函数
public:
	virtual UINT GetClassID() {    return IFTCLASSID_CIECCFGFILES;   }
	virtual BSTR GetXmlElementKey()  {      return CIecCfgToolXmlRWKeys::CIecCfgFilesKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:

public:
	void AdjustIecCfgFile(CIecCfgFile *pIecfgFile);
	CIecCfgFile* NewIecCfgFile(const CString &strFileType=g_strIecCfgFilePostfix);
	BOOL IsIecFileOpen(const CString &strFile);
	CIecCfgFile* OpenIecFile(const CString &strFile);
	BOOL CloseIecFile(CIecCfgFile *pFile, BOOL bDelete);
	BOOL SaveIecFile(CIecCfgFile *pFile);
	BOOL SaveAsIecFile(CIecCfgFile *pFile);

	BOOL HasIecCfgFileModified(CString &strFiles);
	BOOL HasFileInFolder(const CString &strFolder);
	void SetIecCfgSmvRates(CIecCfgSmvRates *pRates, CIecCfgFile *pFile);
	void SetIecCfgSmvCommon(CIecCfgDataSmvCommon *pSmvCommon, CIecCfgFile *pFile);

};

