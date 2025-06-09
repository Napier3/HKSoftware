//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgGoutCh.h  CIecCfgGoutCh

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataGooseChBase.h"


class CIecCfgGoutCh : public CIecCfgDataGooseChBase
{
public:
	CIecCfgGoutCh();
	virtual ~CIecCfgGoutCh();

	CString m_strAddrExternal;
	CString m_strDescExternal;
	CString m_strDefaultValue;
	long    m_nIndexExternal;

//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGGOUTCH;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgGoutChKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual void InitAfterRead();


//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
// 	virtual void GetChFlagHcn(long &nFlag, long &nHcn);
	BYTE Get_hbo();
	BOOL IsDefaultValue();
	void CheckDefautValue();//zhouhj 20210912 ���ڼ������ȱʡֵ,���䲻�����Ӧ��������Ҫ��,�����Ϊ����Ҫ����ַ���

// 	virtual DWORD CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset)
// 	{
// 		pArtAmpDigData->m_nProtocalFlag = PROTOCOL_61850_TYPE_GOOSEOUT;
// 		return 0;
// 	}

protected:
	void CheckDefautValue_ChTypeSingle();
	void CheckDefautValue_ChTypeDouble();
	void CheckDefautValue_ChTypeQuality();
	void CheckDefautValue_ChTypeFloat();
	void CheckDefautValue_ChTypeString();
	void CheckDefautValue_ChTypeInteger();
	void CheckDefautValue_ChTypeUInteger();
};

