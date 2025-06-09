#pragma once
//#include "SclToModelTool.h"

// #include "..\..\Module\Interface\XML2Interface.h"

#include "../../../Module/BaseClass/ExBaseList.h"

extern "C"
{
#include "glbtypes.h"
#include "mvl_acse.h"
#include "mvl_defs.h"
#include "sx_arb.h"
#include "scl.h"
#include "smpval.h"
#include "mem_chk.h"
#include "slog.h"
};

typedef struct
{
	CString da_name;
	CString type;
	CString btype;
	UINT nCount;
} SCL_DA_BDA;

#ifndef _PSX_IDE_QT_
bool UTF8ToMultiByte_Char(char *srcStr);
bool UTF8ToMultiByte_Char(CString &srcStr);
#endif

void Utf8_to_gbk(char *pszUtf8, CString &strGbk);
BSTR GetElementKey(const CString &strElement);
BOOL check_decimal_format(const CString &strDecimal);
void My_PareVarUnite(int nValue, CString &strText);

void scl_get_ln_name_model(SCL_LN  *scl_ln, ST_CHAR *lnName);
long model_XmlWrite(const CString &strFile, SCL_IED*  scl_ied,SCL_INFO *pSclInfo,BOOL bAnalCtrlData = TRUE,BOOL bDLT860Model = FALSE);//bAnalCtrlData是否解析控制类数据即dsDout数据集,nDLT860Model是否为860模式
long model_XmlWrite(SCL_IED* scl_ied,CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oElement,SCL_INFO *pSclInfo,BOOL bAnalCtrlData = TRUE,BOOL bDLT860Model = FALSE);
long model_XmlWrite(const CString &strIedName,SCL_LD* scl_ld, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oElement,SCL_INFO *pSclInfo,BOOL bAnalCtrlData = TRUE,BOOL bDLT860Model = FALSE);
long model_XmlWrite(const CString &strElement,const CString &strLDName ,SCL_DATASET *scl_dataset,SCL_LN *scl_ln0,SCL_LD *scl_ld ,CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oElement,SCL_INFO *pSclInfo,BOOL bDLT860);
long model_XmlWrite_ctrltype(const CString &strLNodeTypeID,SCL_LN	*scl_ln, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oElement,SCL_INFO *pSclInfo);
long model_XmlWrite_ctrltype_data(SCL_DO *scl_do,SCL_LN	*scl_ln, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent,SCL_INFO *pSclInfo);
void model_XmlWrite_brcb(const CString &strLDName,const CString &strDataSetName, SCL_LN *scl_ln0, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent,SCL_INFO *pSclInfo,BOOL bDLT860);
void model_XmlWriteJournalCtrls(const CString &strElement,const CString &strLDName ,SCL_LN *scl_ln0, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent/*,SCL_INFO *pSclInfo*/);
long model_XmlWrite(const CString &strElement,SCL_FCDA* scl_fcda,SCL_LD *scl_ld,CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oElement,SCL_INFO *pSclInfo);
long model_XmlWrite_SubDA(const CString &strModelName , const CString &strDoFcPath,SCL_DA_BDA *pScl_da_bda,CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent,SCL_DATYPE *pDaTypeHead);
long model_XmlWrite_ARRAY(const CString &strDoFcPath,SCL_DA_BDA *pScl_da_bda,CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent,SCL_DATYPE *pDaTypeHead,int nCount);
void model_format(CString &strDataType);
void get_all_ctrltype_lnodetype(SCL_INFO *pSclInfo);
void get_array_dataNUM(SCL_DA_BDA *pScl_da_bda,SCL_DATYPE *pDaTypeHead,long &nNum);

BOOL strcmp_fc(char *pSrc,char *pDes);
BOOL check_ModelValuePath_end(const CString &strModelValuePath,SCL_DOTYPE *doType,SCL_INFO *pSclInfo,CString &strDataType);
BOOL check_ModelValuePath_DO_SD_end(CString &strName,CString &strPath,SCL_DOTYPE *doType,SCL_INFO *pSclInfo,CString &strDataType);
BOOL check_ModelValuePath_DA_end(CString &strName,CString &strPath,CString &strType,SCL_INFO *pSclInfo,CString &strDataType);