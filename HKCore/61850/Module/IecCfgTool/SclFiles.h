//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SclFiles.h  CSclFiles

#pragma once

#include "IecCfgToolGlobal.h"


#include "SclFile.h"

class CSclFiles : public CExBaseList
{
public:
	CSclFiles();
	virtual ~CSclFiles();


//重载函数
public:
	virtual UINT GetClassID() {    return IFTCLASSID_CSCLFILES;   }
	virtual BSTR GetXmlElementKey()  {      return CIecCfgToolXmlRWKeys::CSclFilesKey();     }
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
	CSclFile *m_pCurrOpenSclFile;


//私有成员变量访问方法
public:
	CSclFile* Open();
	CSclFile* Open(const CString &strSclFile);
	CSclFile* GetCurrOpenSclFile()	{	return m_pCurrOpenSclFile;	}
	BOOL FreeSclFileRead(CSclFile *pSclFile);

};

