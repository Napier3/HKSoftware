//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgSysParas.h  CIecCfgSysParas

#pragma once

#include "IecCfgDataMngrGlobal.h"


#include "IecCfgPrimRates.h"
#include "IecCfgPrimRatesIn.h"
#include "IecCfgFiberParas.h"
#include "IecCfgFiberParasIn.h"



class CIecCfgSysParas : public CExBaseList
{
public:
	CIecCfgSysParas();
	virtual ~CIecCfgSysParas();


	long  m_nPkgSendType;
//	long  m_nSecSyn;
// 	long  m_nBCodeLogic;
// 	long  m_nIec1588Type;
	long  m_nPrimParas;//��������ѡ�� 0-����ֵ 1-һ��ֵ,ȱʡ���ö���ֵ(��ϵͳ�����еĸ�ֵ�����෴)
	long  m_nPrimOutput;//�������ѡ�� 0-����ֵ 1-һ��ֵ,ȱʡ����һ��ֵ(��ϵͳ�����еĸ�ֵ�����෴)
//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGSYSPARAS;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgSysParasKey();     }
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
	CIecCfgPrimRates *m_pPrimRates;
	CIecCfgPrimRatesIn *m_pPrimRatesIn;
	CIecCfgFiberParas *m_pFiberParas;
	CIecCfgFiberParasIn *m_pFiberParasIn;
//˽�г�Ա�������ʷ���
public:
	CIecCfgPrimRates* GetPrimRates();
	CIecCfgPrimRatesIn* GetPrimRatesIn();
	CIecCfgFiberParas* GetFiberParas();
	CIecCfgFiberParasIn* GetFiberParasIn();
//���Ա������ʷ���
public:
	void InitPrimRatesFiberParas(long nCT_GroupNum,long nPT_GroupNum,long nFiberLC_Num,long nFiberST_Num);//zhouhj 20210316 ��ʼ��CT��PT��ȼ����ӳ�����
};

