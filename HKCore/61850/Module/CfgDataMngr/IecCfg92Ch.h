//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfg92Ch.h  CIecCfg92Ch

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataSmvChBase.h"

/*
ģ��ĺϲ���Ԫ��ͨ������
	m_strName������
	m_strID����ַ
�ⲿ���õ�ͨ����������Ӧ��������ص�SVIN����ַ������Ϊ�գ���ʾ��ͨ���Ե�ǰ������˵��ʹ��
	m_strAddrExternal���ⲿ��ַ
	m_strDescExternal���ⲿ����
*/

class CIecCfg92Ch : public CIecCfgDataSmvChBase
{
public:
	CIecCfg92Ch();
	virtual ~CIecCfg92Ch();

	CString m_strAddrExternal;
	CString m_strDescExternal;
	long    m_nIndexExternal;
	DWORD   m_nQuality;
	long    m_nData;

//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG92CH;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfg92ChKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual void InitCh();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
// 	virtual void GetChFlagHcn(long &nFlag, long &nHcn);
// 	virtual DWORD CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset);
	virtual void InitForSclRead(long &nUChIndex, long &nIChIndex);

	virtual void SetChTypeID(const CString &strLnClass);
	virtual void OnChTypeIDChanged(const CString &strChTypeID);
	long GetChAngType();//20221210 zhouhj ��ȡ��ǰ��λ��� A��1/2/3/4/5/6
};

