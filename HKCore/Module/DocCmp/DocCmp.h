//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
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

//˽�г�Ա����
private:
	void OpenDocCmpConfig();


//˽�г�Ա�������ʷ���
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

