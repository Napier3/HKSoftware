//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EmcQueryAddrDir.h  CEmcQueryAddrDir

#pragma once

#include "MonitorCapConfigGlobal.h"


#include "EmcQueryAddrMap.h"

class CEmcQueryAddrDir : public CExBaseList
{
public:
	CEmcQueryAddrDir();
	virtual ~CEmcQueryAddrDir();


//���غ���
public:
	virtual UINT GetClassID() {    return EMCCLASSID_CEMCQUERYADDRDIR;   }
	virtual BSTR GetXmlElementKey()  {      return CMonitorCapConfigXmlRWKeys::CEmcQueryAddrDirKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	static long InitListCtrlColumnsFunc(CListCtrl *pListCtrl);
	virtual PFuc_InitListCtrlColumns* GetInitListCtrlColumnsFunc()	{	return CEmcQueryAddrMap::InitListCtrlColumnsFunc;	}

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	BOOL ValidateDir();
	CString GetDeviceModelFile();
	void GetAllDvmFile(CStringArray &astrFile);
	void AddDvmFile(CStringArray &astrFile, const CString &strFile);
};

