//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgDataSmvChBase.h  CIecCfgDataSmvChBase

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataChBase.h"
#include <math.h>


class CIecCfgDataSmvChBase : public CIecCfgDataChBase
{
public:
	CIecCfgDataSmvChBase();
	virtual ~CIecCfgDataSmvChBase();


	CString  m_strChType;
	float  m_fCoef;
	long   m_nUseException;

//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGDATASMVCHBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDataSmvChBaseKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual void InitAfterRead();
	virtual long GetPhID(UINT nDefault=UI_CH_INDEX_A);
	virtual void InitCh();

protected:
	CString InitForSclRead_AppID(long &nUChIndex, long &nIChIndex);
	CString InitForSclRead_ChType();
	CString InitForSclRead_ChType(const CString &strName);

//˽�г�Ա����
private:
	CString InitForSclRead_AppID_Ph();
	CString InitForSclRead_AppID_UI();
	CString InitForSclRead_AppID_Index(BOOL bIsUCh, long &nUChIndex, long &nIChIndex, CString &strPhase);

//˽�г�Ա�������ʷ���
public:
// 	virtual BYTE GetChFlagHcn(long &nFlag, long &nHcn);
	virtual WORD GetAppChIndex();
// 	virtual DWORD InitArtAmpDigdata(CArtAmpDigdata *pData);
	virtual CString GetChTypeID()	{	return m_strID;	}
	virtual void SetChTypeID(const CString &strLnClass)	{};
	virtual void OnChTypeIDChanged(const CString &strChTypeID)	{};
	virtual void SetAppChIndex(long nIndex);
	virtual void InitChTypeID_Name(const CString &strName=_T(""));

public:
	//2023/10/24 wjs setֱ����ѹ������
	void SetDcAppCh(BOOL bSetU, BOOL bSetI, CStringArray &astrUChs, const CStringArray &astrIChs, BOOL bIntelligent=TRUE);

	void SetAppCh(BOOL bSetU, BOOL bSetI, CStringArray &astrUChs, const CStringArray &astrIChs, BOOL bIntelligent=TRUE);
	void SetAppCh_U(const CStringArray &astrUChs, long &nChIndex, long nMaxChs=3, BOOL bIntelligent=TRUE);
	void SetAppCh_I(const CStringArray &astrIChs, long &nChIndex, long nMaxChs=3, BOOL bIntelligent=TRUE);
	void SetAppCh_0(BOOL bSetU, BOOL bSetI);

	//��0��ʼ��ʶ,0�����һ��
	void SwitchChMap(long nGroupIndex,BOOL bSetU, BOOL bSetI,BOOL bDC_FT3);//�л�ͨ��ӳ�� zhouhj 2023.12.27

protected:
	void SetAppCh(const CStringArray &astrChs);
};

