//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CtrlBlock.h  CCtrlBlock

#pragma once

#include "IecfgGenMngrGlobal.h"
#include "../CfgDataMngr/IecCfgSMVDatas.h"
#include "../CfgDataMngr/IecCfgGoutDatas.h"
#include "../CfgDataMngr/IecCfgGinDatas.h"


#include "Keys.h"
#include "Analogs.h"
#include "Bin.h"
#include "Bout.h"

class CCtrlBlock : public CExBaseList
{
public:
	CCtrlBlock();
	virtual ~CCtrlBlock();


	long  m_nFiberIndex;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CCTRLBLOCK;   }
	virtual BSTR GetXmlElementKey()  {      return CIecfgGenMngrXmlRWKeys::CCtrlBlockKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIecfgGenMngrXmlRWKeys::CCtrlBlockKey();     }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL GenerateIecCfgDatas(CIecCfgDatasSMV *pSmvMngr);
	BOOL GenerateIecCfgDatas(CIecCfgGinDatas* pGinMngr);
	BOOL GenerateIecCfgDatas(CIecCfgGoutDatas* pGoutMngr);
//	CIecCfgDataBase* FindIecCfgData(CIecCfgDatasBase *pIecCfgDatasBase,const CStringArray &astrDesc);

protected:
	BOOL GenerateIecCfgData_Bin(CIecCfgGinData *pIecCfgGinData);
	BOOL GenerateIecCfgData_Bout(CIecCfgGoutData *pIecCfgGoutData);
};

