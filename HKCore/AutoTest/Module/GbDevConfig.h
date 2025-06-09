#pragma once

/*
	�����������Զ��������ã������Զ����Թ�������ص�����
	�����ļ���TCtrlCntr.xml/TCtrlCnr.ini
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

	//����
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