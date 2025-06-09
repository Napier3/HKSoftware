#pragma once
#include "BbData.h"
#include "PpScript.h"
#include "ProtocolXmlRWKeys.h"
//#include "DeviceModel/PpDeviceNode.h"

class CWBbData:	public CBbData
{
public:
	CWBbData(void);
	virtual ~CWBbData(void);

public:
	CPpScript	*m_pInitScript;
	long m_nLoopCount;
	long m_nLoopIndex;

	CString m_strLoopCount;	//��ȱXSD����Ӧ��keys����
	CString m_strLoopIndex;	
	CString m_strDataCount;	

	static const CString g_strLoopCountVariable;
	static const CString g_strLoopIndexVariable;
	CExBaseObject *m_pDeviceBindData;

	CPpScript* GetInitScript();

public:
	virtual UINT GetClassID() {        return PPCLASSID_WBBDATA;                               }
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataKey;     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();


public:
	//�ֽڿ�Ľ���		����Ľ�������������ִ�н���
	virtual DWORD Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)		{		return PpParseError();		};

	//�ֽڿ������
	virtual DWORD Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail);

private:
	//�ֽڿ������
	DWORD ProduceDeviceNode(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail, CExBaseObject *pNode);
	DWORD ProduceDeviceNodeData(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail, CExBaseObject *pNodeData);

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
	CBbVariable* GetVariable(CString &strVariableID);
	//CDvmDataset* GetDeviceNode(CString &strDataAttrID, POS &rPosition, CExBaseList *pList);
	DWORD RunOnBbPckScript(CBaseObject *pPkg, long &nAddedBlock, CExBaseList *pDetail, long &nPos);

	//���ݵİ󶨹�ϵ
	virtual CExBaseObject* QueryByBind();
	virtual CExBaseObject* BindItemIndex(long nItemIndex);

private:
	DWORD RunInitScript();
	void SetLoopIndexBind();
	void ResetBinds();

	CPpDataBind *m_pOldDataBind;
	CPpDataBind *m_pLoopIndexBind;
	long m_nBindItemIndex;
};
