//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SclFiles.h  CSclFiles

#pragma once

#include "IecCfgToolGlobal.h"


#include "SclFile.h"

class CSclFiles : public CExBaseList
{
public:
	CSclFiles();
	virtual ~CSclFiles();


//���غ���
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

//˽�г�Ա����
private:
	CSclFile *m_pCurrOpenSclFile;


//˽�г�Ա�������ʷ���
public:
	CSclFile* Open();
	CSclFile* Open(const CString &strSclFile);
	CSclFile* GetCurrOpenSclFile()	{	return m_pCurrOpenSclFile;	}
	BOOL FreeSclFileRead(CSclFile *pSclFile);

};

