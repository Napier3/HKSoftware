#pragma once
#include "GuideBookDefine.h"
#include "../../../Module/BaseClass/ExBaseList.h"
#include "GbItemBase.h"
#include "SysParas.h"
#include "Cpus.h"
#include "Items.h"

#ifndef _PSX_QT_LINUX_
#include "GbtDataInterfaces.h"
#endif

#include "../Characteristic/Characteristics.h"

//2022-9-25  lijunqing ���ʽ����
class CDevice :public CGbItemBase, public CXExprCalInterface
{
public:
	CDevice(void);
	virtual ~CDevice(void);

	static CDevice* _New(CBaseObject *pParent=NULL)
	{
		CDevice *pNew = new CDevice();
		pNew->SetParent(pParent);
		pNew->InitAfterRead();
		return pNew;
	}
	
	void InitAfterReadGb();
	void InitAfterReadGbt();
	void ReadAttr(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	void RemoveExpandDatas(CDvmDataset *pDatas);
	void ImportExpandDatas(CDvmDataset *pDatas);
	void UpdateSysPara(CExBaseList *pSrcList, BOOL bCreateNew);
	void SetSysParaValue(CExBaseList *pSrcList, BOOL bCreateNew);//2024-2-21 �����²��Բ�����value����

	void AddSrcDeviceModelFile(const CString &strFile);
	//attribute
public:
	CCpus* m_pCpus;     //�豸����ģ��
#ifndef _PSX_QT_LINUX_
    CGbtDataInterfaces* m_pGbtDataInterfaces;      //��ģ������ݽӿ�
#endif

	CString m_strFactory;
	long m_nIsTimeSetsUnit_ms;   //ʱ�䶨ֵ�ĵ�λ�Ƿ�Ϊs
	CSysParas* m_pSysParas;  //����ϵͳ����
	CSysParas* m_pTestParas; //ȥ��
	CString m_strDeviceType;						//�ͺ�
	CCharacteristics* m_pCharacteristics;   //��������
	CString m_strSrcDeviceModelFile;
	long m_nDsvTextWithValue;
	long m_nDsvTextWithUtcTime;

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()													{		return GBCLASSID_DEVICE;	}
	virtual BSTR GetXmlElementKey()								{      return CGbXMLKeys::g_pGbXMLKeys->m_strDeviceKey;     }
	virtual void InitAfterRead();

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

	//Interface Mathods
	long GetCpusList(CExBaseList &oListCpu, BOOL bAppend=FALSE);
	CCpus* GetCpus()			{		return m_pCpus;			}
	CCharacteristics* GetCharacteristics()			{		return m_pCharacteristics;			}
	CCpus* GetCpusEx(long nCpusIndex);
	CSysParas* GetSysParas()	{		return m_pSysParas;		}
	CSysParas* GetTestParas()	{		return m_pSysParas;	}
	void AddSysPara(const CString &strID, const CString &strValue);

// 	CSet* GetSetAtIndex(long nIndex);
// 	CSet* FindSetByID(const CString &strID);
// 	CSet* FindSetByName(const CString &strName);
	//2019-12-31  lijunqing
	CDataObj* SelectDataObj(const CString &strPath);
	long SelectDataObj(const CString &strPath, CExBaseList &listDatas);

	CDataObj* FindDataObjByID(const CString &strPath, long nDeviceModelIndex);
	CDataObj* FindDataObjByName(const CString &strName);
	CExBaseObject* FindDvmDataObj(const CString &strID);

	void InsertSetsToComboBox(CComboBox *pComboBox);
	void InsertSysParasToComboBox(CComboBox *pComboBox);

	BOOL GetVariableValue(const CString &strVariable, CString &strValue, BOOL bShowLog=FALSE);
	BOOL GetVariableValue(const CString &strVariable, double &dValue, BOOL bShowLog=FALSE);
	BOOL GetVariableValue2(const CString &strVariable, CString &strValue, BOOL bShowLog=FALSE);
	BOOL GetVariableValue2(const CString &strVariable, double &dValue, BOOL bShowLog=FALSE);

	CExBaseList* GetDeviceModelDatasById(const CString &strCpuID, const CString &strDeviceModelTypeID);
	long GetDataSetList(const CString &strKey, CExBaseList &oListDataSet, long nCpusIndex);
	CExBaseList* GetDeviceDodelDatas(long nCpusIndex);
	long SelectDataSetList(const CString &strIDPath, CExBaseList &oListDataSet, long nCpusIndex);
	long SelectDataSetListEx(const CString &strIDPath, CExBaseList &oListDataSet, long nCpusIndex);
	CDataSet* SelectDataSet(const CString &strIDPath, long nCpusIndex);
	CExBaseList* SelectDataSetList(const CString &strIDPath, long nCpusIndex);

	long SelectAllRootItem(CExBaseList &oList);
	CExBaseList* CreateItemsDirectories(const CString &strNamePath, const CString &strIDPath);

	//2014-12-14  full path
	CDataSet* SelectDataSetEx(const CString &strIDPath);
	long SelectDataSetEx(const CString &strIDPath, CExBaseList &oListDataSet);
protected:
	CExBaseList* CreateItemsDirectories(CExBaseList *pParent, const CString &strNamePath, const CString &strIDPath);
	BOOL GetSplit(const CString &strPath, CString &strLeft, CString &strRight);

public:
	void GbxmlToStxml(CExBaseList &listDatas);

	//�Ƿ��Ѿ����豸����ģ����
	BOOL IsDeviceHasDvm(); 
	CItems* FindFirstRootTypeItem();

//////////////////////////////////////////////////////////////////////////
//2022-9-25  lijunqing ���ʽ����
//CXExprCalInterface
public:
	//2023-11-8 �����β� CString &strValRet�����ڷ����ַ�����������硰δ������
	//2024-7-5 �����β� CString &strDataType�����ڴ����������ͣ����磺utc_time��
	virtual BOOL ExprCal(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, double &dValRet, CString &strValRet, const CString &strDataType);
	virtual BOOL ExprRsltBind(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strDataName, const CString &strParentPath, const CString &strValue);
	virtual BOOL ExprGetValueAttr(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, CString &strValueAttrRet, const CString &strAttr)	{	return TRUE;	}
	virtual void ExprCal_GetReportsForCal(CExBaseList* pListReportsForCal, long nCurrTestTimes, long nRepeatTimes, CExBaseObject* pExprParent);
	virtual BOOL ExprCal_Min(CExBaseList* pListReportsForCal, const CString &strExpression, double &dValRet);  //������Сֵ
	virtual BOOL ExprCal_Max(CExBaseList* pListReportsForCal, const CString &strExpression, double &dValRet);  //�������ֵ
	virtual BOOL ExprCal_SRpt(CExBaseObject *pExprParent, const CString &strSrcIDHas, const CString &strCalMode, double &dValRet);//���㵥��������ָ�����ݵ�max��min��avg

private:
	BOOL ExprCal_dataset(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, double &dValRet, const CString &strDataType);
	BOOL ExprCal_sys_para(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, double &dValRet, const CString &strDataType);
	BOOL ExprCal_global_para(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, double &dValRet, const CString &strDataType);
	//2023-11-8 �����β� CString &strValRet�����ڷ����ַ�����������硰δ������
	BOOL ExprCal_report(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, double &dValRet, CString &strValRet, const CString &strDataType);
	BOOL ExprCal_script(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, double &dValRet, const CString &strDataType);

	//ң�����ݣ����ݲ�����һ��ֵ���Ƕ���ֵ�����ݱ�Ȼ���ɶ���ֵ��������������
	BOOL ExprCal_dataset_Ain(const CString &strExpression, double &dValRet);
	BOOL ExprCal_dataset_Ain_I(CDataGroup *pAinRatios, double &dValRet);
	BOOL ExprCal_dataset_Ain_U(CDataGroup *pAinRatios, double &dValRet);
	BOOL ExprCal_dataset_Ain_PQ(CDataGroup *pAinRatios, double &dValRet);
	BOOL ExprCal_dataset_UTCTIME(const CString &strExpression, CExBaseList *pDataset, double &dValRet);
	BOOL ExprCal_dataset_Account(const CString &strExpression, const CString &strAcountID, CExBaseList *pDataset, double &dValRet);  //����ң�ű�λͳ�ƴ���
	BOOL ExprCal_dataset_SysTime(const CString &strExpression, CExBaseList *pDataset, double &dValRet);//����ң���������͡�
	BOOL ExprCal_dataset_$t(const CString &strExpression, CExBaseList *pDataset, double &dValRet);//����ң�Ŷ�ʱ���ܡ�

	BOOL ExprRsltBind_dataset(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strDataName, const CString &strParentPath, const CString &strValue);
	BOOL ExprRsltBind_sys_para(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strValue);
	BOOL ExprRsltBind_global_para(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strValue);
	BOOL ExprRsltBind_report(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strDataName, const CString &strParentPath, const CString &strValue);
	BOOL ExprRsltBind_script(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strValue);
};
