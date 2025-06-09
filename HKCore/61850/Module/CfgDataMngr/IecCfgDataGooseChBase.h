//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgDataGooseChBase.h  CIecCfgDataGooseChBase

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataChBase.h"


class CIecCfgDataGooseChBase : public CIecCfgDataChBase
{
public:
	CIecCfgDataGooseChBase();
	virtual ~CIecCfgDataGooseChBase();


	CString  m_strDataType;
	CString  m_strDataTypeName;
//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGDATAGOOSECHBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDataGooseChBaseKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	BOOL IsUseChAppID();
	void GetDataType(BYTE &byteDataType, BYTE &byteLen);
	BYTE GetDataType();
	BYTE GetDataLen();
	void GetData(BYTE &byteLen, BYTE *byteData);
// 	virtual DWORD CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset);

	virtual void SetDataTypeByName(const CString &strName);
	virtual void InitDataTypeName(BOOL bInitBin=FALSE);
	CDataTypeValue* FindGooseChTypeValue(const CString &strName);

};

void iecfg_GooseGetDataType(const CString &strDataType, BYTE &byteDataType);
void iecfg_GooseGetDataTypeLen(BYTE byteDataType, const CString &strAppChID, BYTE &byteLen);
