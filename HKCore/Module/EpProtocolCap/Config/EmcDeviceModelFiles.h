//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EmcDeviceModelFiles.h  CEmcDeviceModelFiles

#pragma once

#include "MonitorCapConfigGlobal.h"


#include "EmcDeviceModelFile.h"

class CEmcDeviceModelFiles : public CExBaseList
{
public:
	CEmcDeviceModelFiles();
	virtual ~CEmcDeviceModelFiles();


//���غ���
public:
	virtual UINT GetClassID() {    return EMCCLASSID_CEMCDEVICEMODELFILES;   }
	virtual BSTR GetXmlElementKey()  {      return CMonitorCapConfigXmlRWKeys::CEmcDeviceModelFilesKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual PFuc_InitListCtrlColumns* GetInitListCtrlColumnsFunc()	{	return CEmcDeviceModelFile::InitListCtrlColumnsFunc;	}

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

