//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Pkg_GetTopFileResp_Files.h  CPkg_GetTopFileResp_Files

#pragma once

#include "TcpEdgePkgGlobal.h"

#include "PxPkgDataBase.h"


class CPkg_GetTopFileResp_Files : public CPxPkgDataBase
{
public:
	CPkg_GetTopFileResp_Files();
	virtual ~CPkg_GetTopFileResp_Files();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CPKG_GETTOPFILERESP_FILES;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CPkg_GetTopFileResp_FilesKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CPkg_GetTopFileResp_FilesKey();     }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

