//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EdgeParas.h  CEdgeParas

#pragma once

#include "EdgeCmdMngrGlobal.h"

#include "EdgeGroup.h"


//#include "EdgeData.h"
#include "EdgeDev.h"
#include "EdgeDisk.h"
#include "EdgeDiskLmt.h"
#include "EdgeFile.h"
#include "EdgeLinks.h"
#include "EdgeMem.h"
#include "EdgeMemLmt.h"
#include "EdgeOS.h"
#include "EdgeSign.h"
#include "EdgeCpu.h"
#include "EdgeCpuLmt.h"
#include "EdgeMemUsed.h"
#include "EdgeLinkState.h"
#include "EdgeTemperature.h"
#include "EdgeRepPeriod.h"
#include "EdgeDeviceInfos.h"

class CEdgeParas : public CEdgeGroup
{
public:
	CEdgeParas();
	virtual ~CEdgeParas();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CEDGEPARAS;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeParasKey();     }
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

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

