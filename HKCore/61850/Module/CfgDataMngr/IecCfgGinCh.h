//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgGinCh.h  CIecCfgGinCh

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataGooseChBase.h"


class CIecCfgGinCh : public CIecCfgDataGooseChBase
{
public:
	CIecCfgGinCh();
	virtual ~CIecCfgGinCh();

	int m_nColIndex;	//����
	int m_nPos;			//λ
	CString  m_strAppChIDText;
	CString m_strDefaultValue;//��ֵ�����ӳ�ʼֵ
	CString m_strExternAddr;

//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGGINCH;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgGinChKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	DWORD   GetGinAppID();
	void    SetGinAppID(DWORD dwAppID);
	void InitAppIDText();
	virtual void InitAfterRead();

	void   SetBinString(const CString &strBinID);
	void   AddBinString(const CString &strBinID);
	void   RemoveBinString(const CString &strBinID);
	int GetChPos();
	void CopyToGoutCh(CIecCfgDataGooseChBase *pGoutCh);//2023.6.2 zhouhj �Ѷ��Ŀ��ƿ����ݿ���������
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
// 	virtual void GetChFlagHcn(long &nFlag, long &nHcn);
	//virtual void SetDataTypeByName(const CString &strName);
	virtual void InitDataTypeName(BOOL bInitBin=FALSE);
	BOOL IsDefaultValue();
	void CheckDefautValue();//zhouhj 20210912 ���ڼ������ȱʡֵ,���䲻�����Ӧ��������Ҫ��,�����Ϊ����Ҫ����ַ���
// 	virtual DWORD CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset)
// 	{
// 		pArtAmpDigData->m_nProtocalFlag = PROTOCOL_61850_TYPE_GOOSEIN;
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

