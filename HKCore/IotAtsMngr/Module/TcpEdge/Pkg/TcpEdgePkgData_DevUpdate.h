//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData_DevUpdate.h  CTcpEdgePkgData_DevUpdate

#pragma once

#include "TcpEdgePkgGlobal.h"

//#include "PxPkgDataBase.h"
#include "TcpEdgePkgData.h"

class CTcpEdgePkgData_DevUpdate : public CTcpEdgePkgData//public CPxPkgDataBase   //lmy�޸�
{
public:
	CTcpEdgePkgData_DevUpdate();
	virtual ~CTcpEdgePkgData_DevUpdate();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CTCPEDGEPKGDATA_DEVUPDATE;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgData_DevUpdateKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgData_DevUpdateKey();     }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	//virtual CDvmDataset* ToDataset();
};

