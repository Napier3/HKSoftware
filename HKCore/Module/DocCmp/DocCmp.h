//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DocCmp.h  CDocCmp

#pragma once

#include "DocCmpGlobal.h"


#include "DocFile.h"
#include "../../Module/BaseClass/ThreadProgressInterface.h"

class CDocXReadInterface;

class CDocCmp : public CExBaseList
{
private:
	static CDataGroup *m_pDocCmpConfig;

public:
	static void InitDocCmpConfig();
	static void FreeDocCmpConfig();
	static CDataGroup* GetDocCmpConfig();
	
public:
	CDocCmp();
	virtual ~CDocCmp();

	CThreadProgressInterface *m_pProgress;
	CDocXReadInterface *m_pDocXReadInterface;

//重载函数
public:
	virtual UINT GetClassID() {    return DOCMPCLASSID_CDOCCMP;   }
	virtual BSTR GetXmlElementKey()  {      return CDocCmpXmlRWKeys::CDocCmpKey();     }
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
	void OpenDocCmpConfig();


//私有成员变量访问方法
public:
	void DocCmp(int argc, TCHAR* argv[]);
	void DocCmpXml(const CString &strFile1, const CString &strFile2, const CString &strCmpFile);

protected:
	void DocCmp();
	void SaveDocCmpFile(const CString &strFile);
};

extern 	long g_nDocmp_DebugGroup;
extern  long g_nDocToXmlFormat;

void doctoxml_change_file_postfix(CString &strFile);

