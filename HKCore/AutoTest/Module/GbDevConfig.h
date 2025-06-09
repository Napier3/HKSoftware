#pragma once

/*
	功能描述：自动测试配置；设置自动测试过程中相关的配置
	关联文件：TCtrlCntr.xml/TCtrlCnr.ini
*/
#include "../../Module/BaseClass/ExBaseObject.h"
#include "AutoTestXMLRWKeys.h"


class CGbDevConfig : public CExBaseObject
{
private:
	CGbDevConfig();
	virtual ~CGbDevConfig();

public:
	static CGbDevConfig* g_pGbDevConfig;
	static long g_nGbDevConfigRef;

	static CGbDevConfig* Create();
	static void Release();

public:
	long m_nWordPageOrientation;
	CString m_strWordPageOrientation;

	//其他
	CString m_strFile;


public:
	long Save();
	long Open();

public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{      return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTCtrlCntrKey;	}

protected:
	
public:
	static BOOL IsWordPageDir_Horz();
	static BOOL IsWordPageDir_Vert();
	static void SetWordPageDir_Horz();
	static void SetWordPageDir_Vert();
};