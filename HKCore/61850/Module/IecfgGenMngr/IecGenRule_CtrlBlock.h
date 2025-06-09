//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecGenRule_CtrlBlock.h  CIecGenRule_CtrlBlock

#pragma once

#include "IecfgGenMngrGlobal.h"
#include "../CfgDataMngr/IecCfgSMVDatas.h"
#include "../CfgDataMngr/IecCfgGoutDatas.h"
#include "../CfgDataMngr/IecCfgGinDatas.h"


#include "IecGenCfgKeys.h"
#include "IecGenCfgKey.h"
#include "IecGenRule_CtrlCh.h"

class CIecGenRule_CtrlBlock : public CExBaseList
{
public:
	CIecGenRule_CtrlBlock();
	virtual ~CIecGenRule_CtrlBlock();

#ifdef IECFG_USE_KEYDB
	void InitMatchList(CXKeyDB *pKeyDB);
	CXMatchList *m_pChMatchList;
#endif


	long  m_nFiberIndex;
	long  m_nMatchRatio;
//���غ���
public:
	virtual UINT GetClassID() {    return GENRATECLASSID_CIECGENRULE_CTRLBLOCK;   }
	virtual BSTR GetXmlElementKey()  {      return CIecfgGenMngrXmlRWKeys::CIecGenRule_CtrlBlockKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIecfgGenMngrXmlRWKeys::CIecGenRule_CtrlBlockKey();     }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:


//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
// 	BOOL GenerateIecCfgDatas(CIecCfgDatasSMV *pSmvMngr);
// 	BOOL GenerateIecCfgDatas(CIecCfgGinDatas* pGinMngr);
// 	BOOL GenerateIecCfgDatas(CIecCfgGoutDatas* pGoutMngr);
//	CIecCfgDataBase* FindIecCfgData(CIecCfgDatasBase *pIecCfgDatasBase,const CStringArray &astrDesc);

protected:
// 	BOOL GenerateIecCfgData_Bin(CIecCfgGinData *pIecCfgGinData);
// 	BOOL GenerateIecCfgData_Bout(CIecCfgGoutData *pIecCfgGoutData);
};

