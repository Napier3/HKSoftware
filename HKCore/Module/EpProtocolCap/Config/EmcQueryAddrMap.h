//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EmcQueryAddrMap.h  CEmcQueryAddrMap

#pragma once

#include "MonitorCapConfigGlobal.h"



class CEmcQueryAddrMap : public CExBaseObject
{
public:
	CEmcQueryAddrMap();
	virtual ~CEmcQueryAddrMap();


	CString  m_strSrc;
	CString  m_strDest;
//���غ���
public:
	virtual UINT GetClassID() {    return EMCCLASSID_CEMCQUERYADDRMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CMonitorCapConfigXmlRWKeys::CEmcQueryAddrMapKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	static long InitListCtrlColumnsFunc(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	virtual PFuc_InitListCtrlColumns* GetInitListCtrlColumnsFunc()	{	return InitListCtrlColumnsFunc;	}

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

