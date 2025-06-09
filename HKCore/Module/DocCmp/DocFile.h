//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DocFile.h  CDocFile

#pragma once

#include "DocCmpGlobal.h"


#include "DocText.h"
#include "DocTable.h"
#include "DocGroup.h"
#include "../../Module/DataMngr/DataGroup.h"

class CDocFile : public CExBaseList
{
public:
	CDocFile();
	virtual ~CDocFile();

	CDocGroup m_oDocGroupRoot;   //���ձ�������ͽ��з��飬�ȶ�ֻ���

//���غ���
public:
	virtual UINT GetClassID() {    return DOCMPCLASSID_CDOCFILE;   }
	virtual BSTR GetXmlElementKey()  {      return CDocCmpXmlRWKeys::CDocFileKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void Group(CDataGroup *pConfig);
	void GroupNone(CDataGroup *pConfig);

	void Cmp(CDocFile *pSrcFile);
	void CmpSingle(CDocFile *pSrcFile);

	void OpenDocDataFile(const CString &strFile);
	void InitTableTxtCmpID();
};

