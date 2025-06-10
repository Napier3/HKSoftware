//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttDevice.h  CSttDevice

#pragma once

#include "../SttCmdDefineGlobal.h"

#include "SttItemBase.h"

#include "SttSysParas.h"
#include "SttItems.h"
#include "SttCommCmd.h"
#include "SttMacroTest.h"
#include "SttSafety.h"
#include "SttSysParaEdit.h"

class CSttDevice : public CSttItemBase, public CXExprCalInterface
{
public:
	CSttDevice();
	virtual ~CSttDevice();


	CString  m_strFactory;
	CString  m_strDeviceType;
	long  m_nIsTimeSetsUnit_ms;
	long  m_nDsvTextWithValue;
	long  m_nDsvTextWithUtcTime;
	CString  m_strSrcDeviceModelFile;
//���غ���
public:
	virtual UINT GetClassID() {    return STTGBXMLCLASSID_CSTTDEVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttDeviceKey();     }
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

//˽�г�Ա�������ʷ���
public:
	CSttSysParas *m_pSysPara;

//���Ա������ʷ���
public:
	CSttSysParas* GetSysPara(BOOL bCreate);
	void UpdateSysPara(CExBaseList *pSrcList, BOOL bCreateNew);
	long SelectAllRootItem(CExBaseList &oList);

	virtual long GetGbItemCount();
	virtual void GetItemsCountByItemsType(long &nTotalCount, long &nEligibleCount, long &nInlegibleCount);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//shaolei   2023-03-10  ����жϱ��ʽ
public:
	//2024-7-5 �����β� CString &strDataType�����ڴ����������ͣ����磺utc_time��
	virtual BOOL ExprCal(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, double &dValRet, CString &strValRet, const CString &strDataType) {	return TRUE;	}
	virtual BOOL ExprRsltBind(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strDataName, const CString &strParentPath, const CString &strValue);
	virtual BOOL ExprGetValueAttr(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, CString &strValueAttrRet, const CString &strAttr);
	virtual void ExprCal_GetReportsForCal(CExBaseList* pListReportsForCal, long nCurrTestTimes, long nRepeatTimes, CExBaseObject* pExprParent) {	}

	virtual BOOL ExprCal_Min(CExBaseList* pListReportsForCal, const CString &strExpression, double &dValRet){	return TRUE;	}//������Сֵ
	virtual BOOL ExprCal_Max(CExBaseList* pListReportsForCal, const CString &strExpression, double &dValRet){	return TRUE;	}//�������ֵ
	virtual BOOL ExprCal_SRpt(CExBaseObject *pExprParent, const CString &strSrcIDHas, const CString &strCalMode, double &dValRet){	return TRUE;	}//���㵥��������ָ�����ݵ�max��min��avg

private:
	BOOL ExprRsltBind_dataset(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, const CString &strValue);
	BOOL ExprRsltBind_sys_para(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strValue);
	BOOL ExprRsltBind_global_para(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strValue);
	BOOL ExprRsltBind_report(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strDataName, const CString &strParentPath, const CString &strValue);
	BOOL ExprRsltBind_script(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strValue);

	BOOL ExprGetValueAttr_dataset(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, CString &strValueAttrRet, const CString &strAttr);
	BOOL ExprGetValueAttr_sys_para(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, CString &strValueAttrRet, const CString &strAttr);
	BOOL ExprGetValueAttr_global_para(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, CString &strValueAttrRet, const CString &strAttr);
	BOOL ExprGetValueAttr_report(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, CString &strValueAttrRet, const CString &strAttr);
	BOOL ExprGetValueAttr_script(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, CString &strValueAttrRet, const CString &strAttr);

};

