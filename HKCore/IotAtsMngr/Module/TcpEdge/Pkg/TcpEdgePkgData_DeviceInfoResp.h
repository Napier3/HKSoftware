//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData_DeviceInfoResp.h  CTcpEdgePkgData_DeviceInfoResp

#pragma once

#include "TcpEdgePkgGlobal.h"

#include "TcpEdgePkgData.h"
#include "TcpEdgePkgDev.h"
#include "TcpEdgePkgCpu.h"
#include "TcpEdgePkgMem.h"
#include "TcpEdgePkgDisk.h"
#include "TcpEdgePkgTemperature.h"
#include "TcpEdgePkgOs.h"

class CTcpEdgePkgData_DeviceInfoResp : public CTcpEdgePkgData
{
public:
	CTcpEdgePkgData_DeviceInfoResp();
	virtual ~CTcpEdgePkgData_DeviceInfoResp();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEINFORESP;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgData_DeviceInfoRespKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgData_DeviceInfoRespKey();     }

//˽�г�Ա����
public:
	CTcpEdgePkgDev *m_pTcpEdgePkgDev;
	CTcpEdgePkgCpu *m_pTcpEdgePkgCpu;
	CTcpEdgePkgMem *m_pTcpEdgePkgMem;
	CTcpEdgePkgDisk *m_pTcpEdgePkgDisk;
	CTcpEdgePkgTemperature *m_pTcpEdgePkgTemperature;
	CTcpEdgePkgOs *m_pTcpEdgePkgOs;

protected:
	BOOL m_bObjectMustExist[5]; //�����жϽ��յ��ı����еı���Object�Ƿ����,0-5�ֱ��ʾ��Dev��Cpu��Mem��Disk��Os; False:ȱ�ٸ�object,True:������object
	CString m_strObjectName[5];  //���ڴ�ű���object���֣�˳���m_bObjectExist�ж�Ӧ

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

