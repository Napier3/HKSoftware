//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfg6044Ch.h  CIecCfg6044Ch

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataSmvChBase.h"


class CIecCfg6044CommonCh : public CIecCfgDataSmvChBase
{
public:
	CIecCfg6044CommonCh();
	virtual ~CIecCfg6044CommonCh();

	long m_nChLenth;
	long m_nValue;

//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG6044COMMONCH;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfg6044CommonChKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
// 	virtual void GetChFlagHcn(long &nFlag, long &nHcn);
// 	virtual DWORD CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset);
	virtual void InitForSclRead(long &nUChIndex, long &nIChIndex);
	virtual void SetChTypeID(const CString &strLnClass);
	virtual void InitAfterRead();
	long GetChAngType();//202434 zhouhj ��ȡ��ǰ��λ��� A��1/2/3/4/5/6

};

