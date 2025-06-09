//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DmDataTemplate.h  CDmDataTemplate

#pragma once

#include "DmDataTemplateGlobal.h"


#include "DmdtNodeDatas.h"

class CDmDataTemplate : public CExBaseList
{
public:
	CDmDataTemplate();
	virtual ~CDmDataTemplate();


//���غ���
public:
	virtual UINT GetClassID() {    return DMDTCLASSID_CDMDATATEMPLATE;   }
	virtual BSTR GetXmlElementKey()  {      return CDmDataTemplateXmlRWKeys::CDmDataTemplateKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void OpenDmDataTemplateFile();

private:
	void GetDmDataTemplateFile(CString &strFile);
};

