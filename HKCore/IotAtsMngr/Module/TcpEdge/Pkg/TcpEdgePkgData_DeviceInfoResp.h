//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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


//重载函数
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

//私有成员变量
public:
	CTcpEdgePkgDev *m_pTcpEdgePkgDev;
	CTcpEdgePkgCpu *m_pTcpEdgePkgCpu;
	CTcpEdgePkgMem *m_pTcpEdgePkgMem;
	CTcpEdgePkgDisk *m_pTcpEdgePkgDisk;
	CTcpEdgePkgTemperature *m_pTcpEdgePkgTemperature;
	CTcpEdgePkgOs *m_pTcpEdgePkgOs;

protected:
	BOOL m_bObjectMustExist[5]; //用于判断接收到的报文中的必需Object是否存在,0-5分别表示：Dev、Cpu、Mem、Disk、Os; False:缺少该object,True:包含该object
	CString m_strObjectName[5];  //用于存放必需object名字，顺序和m_bObjectExist中对应

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

