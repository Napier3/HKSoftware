#pragma once

#include "GuideBookDefine.h"
#include "DataSet.h"
class CDevice;

class CItemsRsltExpr : public CExBaseObject
{
public:
	CItemsRsltExpr();
	virtual ~CItemsRsltExpr();

//属性
public:
	CString m_strStandID; //输出的标准值
	CString m_strAbsErrorCalExpr; //绝对误差计算公式
	CString m_strDvmDataID;    //数据ID
	CString m_strRelErrorCalExpr;   //相对误差
	CString m_strDvmDataAbsErrID;
	CString m_strDvmDataRelErrID;
	CString m_strVarAbsErr;   //绝对误差限
	CString m_strVarRelErr;   //相对误差限
	CString m_strRsltVarAbsErr;   //绝对误差记录变量
	CString m_strRsltVarRelErr;   //相对误差记录变量

	double m_dStandValue;
	double m_dDvmValue;
	double m_dAbsErrorCal;
	double m_dRelErrorCal;
	double m_dAbsError;
	double m_dRelError;
	DWORD   m_dwRsltJdg;

//公共接口
public:

//重写父类方法
public:
	virtual UINT GetClassID()		{			return GBCLASSID_ITEMSRSLTEXPR;			}
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()		{		return CGbXMLKeys::g_pGbXMLKeys->m_strRsltExprKey;			}

	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

	long RunRsltExprScript(CDevice *pDevice, CValues *pRptValues, CValues *pAllValues);

protected:
	void CalAbsError(CDevice *pDevice, CValues *pRptValues, CValues *pAllValues, double &dStand, double &dDvmVal, double &dAbsErrorCal);
	void CalRelError(CDevice *pDevice, CValues *pRptValues, CValues *pAllValues, double &dStand, double &dAbsErrorCal, double &dRelErrorCal);
	BOOL GetStandVal(CDevice *pDevice, CValues *pAllValues, double &dStandVal);
	BOOL GetDvmVal(CDevice *pDevice, CValues *pAllValues, double &dDvmVal);
};



class CItemsRsltExprScript : public CExBaseList
{
public:
	CItemsRsltExprScript();
	virtual ~CItemsRsltExprScript();

//属性
public:
	CString m_strTestMacroID;    //测试功能ID
	CString m_strDatasetID;        //测试数据集对象
	CString m_strTimeGapRead;   //读数据时间间隔
	CString m_strTimeIgnore;   //忽略报文的时间长度
	long m_nMaxReadTimes;       //最大读数据次数
	long m_nIsRef;                    //是否为引用数据

//公共接口
public:

//重写父类方法
public:
	virtual UINT GetClassID()		{			return GBCLASSID_ITEMSRSLTEXPRSCRIPT;			}
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()		{		return CGbXMLKeys::g_pGbXMLKeys->m_strRsltExprScriptKey;			}

	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL UpdateOwn(CBaseObject* pDest);

	CExBaseObject* GetParentGbItem();
	CExBaseObject* GetItemsGlobalRsltScriptMngr();
	CItemsRsltExprScript* GetRefItemsGlobalRsltScript();

	CItemsRsltExpr* AddNew(BOOL bClone);
	void SelectAllDatas(CExBaseList &listDatas, CDataSet *pDataset);  //选取相关联的全部数据对象
	void SelectAllDatas(CExBaseList &listDatas, CDvmDataset *pDataset);  //选取相关联的全部数据对象
	BOOL Validate();

	void GetItemsRsltExprScriptTime(long &nTimeLong, long &nTimeIgnore);
	long RunRsltExprScript(CDevice *pDevice, CValues *pRptValues, CValues *pMacroTestValues);

protected:
	CDataObj* SelectDataInDs(const CString &strPath, CDataSet *pDataset);
	BOOL AddDataObj(const CString &strPath, CExBaseList &listDatas, CDataSet *pDataset);

	CDvmData* SelectDataInDs(const CString &strPath, CDvmDataset *pDataset);
	BOOL AddDataObj(const CString &strPath, CExBaseList &listDatas, CDvmDataset *pDataset);
};

class CItemsRsltExprScriptMngr : public CExBaseList
{
public:
	CItemsRsltExprScriptMngr();
	virtual ~CItemsRsltExprScriptMngr();

	CString m_strScriptMngrFile;

private:
	BOOL m_bModifiedFlag;

public:
	virtual UINT GetClassID()		{			return GBCLASSID_ITEMSRSLTEXPRSCRIPTMNGR;			}
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()		{		return CGbXMLKeys::g_pGbXMLKeys->m_strRsltExprScriptMngrKey;			}

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	CItemsRsltExprScript* AddNewItemsGlobalRsltScript(const CString &strID);

	virtual BOOL OpenScriptMngrFile(const CString &strFile);
	virtual BOOL SaveScriptMngrFile(const CString &strFile);

	BOOL GetModifiedFlag()							{	return m_bModifiedFlag;		}
	void SetModifiedFlag(BOOL b = TRUE)	{	m_bModifiedFlag = b;		}

public:
	void Import(CItemsRsltExprScriptMngr *pSrc);
};


class CItemsRsltExprScriptMngrGlobalPool : public CExBaseList
{
private:
	CItemsRsltExprScriptMngrGlobalPool();
	virtual ~CItemsRsltExprScriptMngrGlobalPool();

public:
	static CItemsRsltExprScriptMngrGlobalPool *g_pItemsGlobalRsltScriptMngrGlobalPool;
	static long g_nItemsGlobalRsltScriptMngrGlobalPool;

	static CItemsRsltExprScriptMngr* CreateItemsGlobalRsltScriptMngr(const CString &strFile);

	static void Create();
	static void Release();

};