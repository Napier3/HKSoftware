//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgDataChBase.h  CIecCfgDataChBase

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "../GlobalDataMngr/IecGlobalDataMngr.h"

class CIecCfgDataChBase : public CExBaseObject
{
public:
	CIecCfgDataChBase();
	virtual ~CIecCfgDataChBase();


	long  m_nUseFlag;
	long  m_nIndex;
	CString  m_strAppChID;
	CString  m_strDevChID;
	CString  m_strMapDataID;

	CExBaseObject *m_pScdObjRef; //������SCD���ݶ���

	CExBaseObject* GetAncestorIecCfgData();
	
//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGDATACHBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDataChBaseKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual void InitCh();


//˽�г�Ա����
private:
// 	CArtAmpDigdata *m_pArtAmpDigdata;

//˽�г�Ա�������ʷ���
public:
// 	virtual BYTE GetChFlagHcn(long &nFlag, long &nHcn)	{	nFlag = 1;	nHcn = 0x7F;	return 0xFF;	}
	virtual BOOL IsChUse();
	virtual BOOL IsTimeCh();
	virtual BOOL IsZeroCh();
	virtual BOOL IsAppCh();
	virtual BOOL IsUCh();
	virtual BOOL IsICh();
	virtual BOOL IsTCh();

// 	virtual void SetArtAmpDigdata(CArtAmpDigdata *pArtAmpDigdata)	{	m_pArtAmpDigdata = pArtAmpDigdata;	}
// 	virtual DWORD InitArtAmpDigdata(CArtAmpDigdata *pArtAmpDigdata);
// 	virtual DWORD CalMagAndOffset(CArtAmpDigdata *pArtAmpDigdata);
// 	virtual DWORD GetMagAndOffset(float &dwMag, float &dwOffset);

	virtual void InitForSclRead(long &nUChIndex, long &nIChIndex);

private:
//	virtual DWORD CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset);
//	virtual DWORD CalMagAndOffset(float &dwMag, float &dwOffset);

};

