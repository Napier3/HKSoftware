//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SclFile.h  CSclFile

#pragma once

#include "IecCfgToolGlobal.h"


class CSclFile : public CExBaseObject
{
public:
	CString m_strtscdName;
	CSclFile();
	virtual ~CSclFile();

//重载函数
public:
	virtual UINT GetClassID() {    return IFTCLASSID_CSCLFILE;   }
	virtual BSTR GetXmlElementKey()  {      return CIecCfgToolXmlRWKeys::CSclFileKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:
#ifndef _PSX_IDE_QT_
	CFrameWnd *m_pRefFrameWnd;
#endif

//私有成员变量访问方法
public:
#ifndef _PSX_IDE_QT_
	void SetRefFrameWnd(CFrameWnd *pRefRameWnd)	{	m_pRefFrameWnd = pRefRameWnd;	}
	CFrameWnd* GetRefFrameWnd()					{	return m_pRefFrameWnd;			}
#endif

	BOOL Open(const CString &strFile);
	void FreeSclFileRead();
};

