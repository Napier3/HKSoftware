//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttSafetyMsgCfgs.h  CSttSafetyMsgCfgs

#pragma once

#include "SttSafetyMsgCfgGlobal.h"


#include "SttSafetyMsgCfg.h"

class CSttSafetyMsgCfgs : public CExBaseList
{
public:
	CSttSafetyMsgCfgs();
	virtual ~CSttSafetyMsgCfgs();


//���غ���
public:
	virtual UINT GetClassID() {    return SSMCFGCLASSID_CSTTSAFETYMSGCFGS;   }
	virtual BSTR GetXmlElementKey()  {      return CSttSafetyMsgCfgXmlRWKeys::CSttSafetyMsgCfgsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

