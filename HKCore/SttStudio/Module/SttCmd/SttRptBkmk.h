//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttRptBkmk.h  CSttRptBkmk

#pragma once

#include "SttCmdDefineGlobal.h"



class CSttRptBkmk : public CExBaseObject
{
public:
	CSttRptBkmk();
	virtual ~CSttRptBkmk();


	CString  m_strAttr_Id;
	CString  m_strProcess;
	CString  m_strFill_Mode;
	CString  m_strMgrp_Cmbn;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTRPTBKMK;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttRptBkmkKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

