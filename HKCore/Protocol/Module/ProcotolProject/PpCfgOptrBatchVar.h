//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PpCfgOptrBatchVar.h  CPpCfgOptrBatchVar

#pragma once

#include "ClassProcotolProjectGlobal.h"



class CPpCfgOptrBatchVar : public CExBaseObject
{
public:
	CPpCfgOptrBatchVar();
	virtual ~CPpCfgOptrBatchVar();


	float  m_fStepVal;
	long  m_nStepCount;
//���غ���
public:
	virtual UINT GetClassID() {    return POCLASSID_CPPCFGOPTRBATCHVAR;   }
	virtual BSTR GetXmlElementKey()  {      return CClassProcotolProjectXmlRWKeys::CPpCfgOptrBatchVarKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

