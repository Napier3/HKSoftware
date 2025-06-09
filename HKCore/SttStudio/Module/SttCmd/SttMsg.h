//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttMsg.h  CSttMsg

#pragma once

#include "SttCmdDefineGlobal.h"



class CSttMsg : public CExBaseObject
{
public:
	CSttMsg();
	virtual ~CSttMsg();

	CString  m_strMsg;
	CString m_strTime;
	long m_nLevel;
	long m_nType;
//���غ���
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTMSG;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttMsgKey();     }
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
	CString GetMsg()	{	return m_strMsg;	}
	void SetMsg(CString strMsg)	{	m_strMsg = strMsg;	}
};

