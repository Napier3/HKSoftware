//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData_AppSetCfgFileReq.h  CTcpEdgePkgData_AppSetCfgFileReq

#pragma once

#include "TcpEdgePkgGlobal.h"

#include "TcpEdgePkgData.h"

#include "TcpEdgePkgFile.h"

class CTcpEdgePkgData_AppSetCfgFileReq : public CTcpEdgePkgData
{
public:
	CTcpEdgePkgData_AppSetCfgFileReq();
	virtual ~CTcpEdgePkgData_AppSetCfgFileReq();


	CString  m_strContainer;
	CString  m_strApp;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CTCPEDGEPKGDATA_APPSETCFGFILEREQ;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgData_AppSetCfgFileReqKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgData_AppSetCfgFileReqKey();     }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	CTcpEdgePkgFile* GetTcpEdgePkgFile(){ return m_pTcpEdgePkgFile; }


public:
	virtual CDvmDataset* ToDataset();

//˽�г�Ա����
private:
	CTcpEdgePkgFile *m_pTcpEdgePkgFile;

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

