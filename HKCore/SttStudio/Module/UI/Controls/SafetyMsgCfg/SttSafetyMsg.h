//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttSafetyMsg.h  CSttSafetyMsg

#pragma once

#include "SttSafetyMsgCfgGlobal.h"



class CSttSafetyMsg : public CExBaseObject
{
public:
	CSttSafetyMsg();
	virtual ~CSttSafetyMsg();


	CString  m_strMsg;
//���غ���
public:
	virtual UINT GetClassID() {    return SSMCFGCLASSID_CSTTSAFETYMSG;   }
	virtual BSTR GetXmlElementKey()  {      return CSttSafetyMsgCfgXmlRWKeys::CSttSafetyMsgKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

