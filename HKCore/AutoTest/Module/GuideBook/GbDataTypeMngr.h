#pragma once

#include "../../../Module/DataMngr/DataTypes.h"
#include "../../../Module/TestMacro/MtDataTypeMngr.h"

static const CString g_strGbDataTypeNumberName				= _T("数值");
static const CString g_strGbDataTypeStringName				= _T("字符串");
static const CString g_strGbDataTypeComboboxName			= _T("组合框");
static const CString g_strGbDataTypeMulticomboboxName	= _T("多重组合框");
static const CString g_strGbDataTypeDatetimeName			= _T("时间");
static const CString g_strGbDataTypePasswordName			= _T("密码");
static const CString g_strGbDataTypeMacAddrName			= _T("MAC地址");
static const CString g_strGbDataTypeIPAddrName			= _T("IP地址");
static const CString g_strGbDataTypeDvmDatasetName		= _T("设备模型-数据集");
static const CString g_strGbDataTypeImageFileName		= _T("图像文件");
static const CString g_strGbDataTypeComtradeFileName		= _T("波形文件");

static const CString g_strGbDataTypeNumber				= _T("number");
static const CString g_strGbDataTypeString				= _T("string");
static const CString g_strGbDataTypeCombobox			= _T("combobox");
static const CString g_strGbDataTypeMulticombobox	= _T("multicombobox");
static const CString g_strGbDataTypeDatetime			= _T("datetime");
static const CString g_strGbDataTypePassword			= _T("password");
static const CString g_strGbDataTypeSet				    = _T("set");
static const CString g_strGbDataTypeExpression		    = _T("expression");
static const CString g_strGbDataTypeMacAddr		    = _T("mac-addr");
static const CString g_strGbDataTypeIPAddr		    = _T("ip-addr");
static const CString g_strGbDataTypeDvmDataset		    = _T("dvm-dataset");
static const CString g_strGbDataTypeImageFile	    = _T("image-file");
static const CString g_strGbDataTypeComtradeFile	    = _T("comtrade-file");


static const CString g_strGbtDataObjTypeName_Script			= _T("数据集映射对象");
static const CString g_strGbtDataObjTypeID_Script			= _T("dataset");
static const CString g_strGbtDataObjTypeName_Batch			= _T("批量处理参数对象");
static const CString g_strGbtDataObjTypeID_Batch			= _T("batch");

static const CString g_strDataFillModeTypeName_Cell			= _T("单一数据填写模式");
static const CString g_strDataFillModeTypeID_Cell			= _T("cell");
static const CString g_strDataFillModeTypeName_Row			= _T("表格行填写模式");
static const CString g_strDataFillModeTypeID_Row			= _T("row");
static const CString g_strDataFillModeTypeName_Col 			= _T("表格列填写模式");
static const CString g_strDataFillModeTypeID_Col			= _T("col");



class CGbDataTypeMngr
{
private:
	CGbDataTypeMngr(void);
	virtual ~CGbDataTypeMngr(void);

	BOOL m_bCall_In_e_Report;
public:
	static long g_nGbDataTypeMngrRef;
	static CGbDataTypeMngr *g_pGbDataTypeMngr;

	static const CString g_strGbSafetyComboDataTypeFile;	//安全措施组合框的数据类型定义文件
	static const CString g_strGbSetsDataTypeFile;				//定值数据类型定义文件
	static const CString g_strGbDateTimeFormatFile;			//日期时间格式数据类型文件
// 	static const CString g_strGbMacroTestDataTyeFile ;			//测试功能参数数据类型文件 //lijq 20200228  all data types are defined in test-macro-file, 

	static CGbDataTypeMngr* Create(BOOL bCall_In_e_Report=TRUE);
	static void Release();
	
public:
	static CDataTypes* GetSafetyDataTypes()				{		return &(g_pGbDataTypeMngr->m_oSafetyDataTypes);		}
	static CDataTypes* GetSafetyComboDataTypes()	{		return &(g_pGbDataTypeMngr->m_oSafetyComboDataTypes);		}
	static CDataTypes* GetDateTimeFormat()				{		return &(g_pGbDataTypeMngr->m_oDateTimeFormat);		}
	
	//lijq 20200228  all data types are defined in test-macro-file, 
	//static CDataTypes* GetMacroTestDataTypes()	;//		{		return &(g_pGbDataTypeMngr->m_oMacroTestDataTypes);		}
	//static CDataType* GetMacroTestDataType(const CString &strID);
	static CDataType* GetGbtDataObjDataType()			{		return &g_pGbDataTypeMngr->m_oGbtDataObjDataType;	}
	static CDataType* GetDataFillModeDataType()			{		return &g_pGbDataTypeMngr->m_oDataFillModeDataType;	}

	void FindDataTypeNameByID(CString strID,CString& strName);
	void FindDataTypeIDByName(CString& strID,CString strName);
	void FindComboDataTypeNameByID(CString strID,CString& strName);
	void FindComboDataTypeIDByName(CString& strID,CString strName);
	void FindComboDataTypeValueNameByID(CString strDataType,CString strID,CString& strName);
	void FindComboDataTypeValueIDByName(CString strDataType,CString& strID,CString strName);
// 	CDataTypeValue* FindComboDataTypeValueByID(const CString &strDataType,const CString &strID);
// 	CDataTypeValue* FindComboDataTypeValueByName(const CString &strDataType,const CString &strName);

private:
	CDataTypes m_oSafetyDataTypes;
	CDataTypes m_oSafetyComboDataTypes;
	CDataTypes m_oDateTimeFormat;
	//CDataTypes m_oMacroTestDataTypes;
	CDataType  m_oGbtDataObjDataType;
	CDataType  m_oDataFillModeDataType;

	void InitGbDataTypeMngr();
	void InitSafetyDataTypes();
	void InitDateTimeFormat();
	//void InitMacroTestDataTypes();//lijq 20200228  all data types are defined in test-macro-file, 
	void InitGbtDataObjDataType();
	void InitDataFillModeDataType();

	static CString GetConfigPath();
//////////////////////////////////////////////////////////////////////////
private:
	//数据类型文件对象管理
	CExBaseList m_listDataTypes;


public:
	static CDataTypes* GetDataTypes(const CString &strDataTypeFile);
};

void InsertDataTypesToComboBox(CDataTypes *pDataTypes, CComboBox *pBox);
void InsertDataTypeToComboBox(CDataType *pDataType, CComboBox *pBox);

BOOL IsComboMacroTestDataType(const CString &bstrDataTypeID);
BOOL GetDataTypeNameByValue(CDataTypes *pDataTypes, const CString &bstrDataTypeID, const CString &bstrValue, CString &strName);
BOOL GetDataTypeValueByName(CDataTypes *pDataTypes, const CString &bstrDataTypeID, CString &bstrValue, const CString &strName);
