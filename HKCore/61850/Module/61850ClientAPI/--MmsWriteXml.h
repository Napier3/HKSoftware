
#pragma once
//#include "DltEngine.h"

long mms_XmlWrite(const CString &strFile,ACSI_NODE *pDevice);
long mms_XmlWrite(ACSI_NODE *pDevice,CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oElement, BOOL bOblyGetLd=FALSE);
long mms_XmlWrite(LD_NODE *pLDevice, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oElement, BOOL bOblyGetLd = FALSE);
void mms_XmlWrite(const CString &strElement,RCB_NODE *pRCB, int nNum, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent);
void mms_XmlWriteJournalCtrls(const CString &strElement,LD_JOURNAL_CTRLS *pJournalCtrls, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent);
long mms_XmlWrite(const CString &strElement,LD_DATASET_INFO*pLD_INFO,CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oElement);
long mms_XmlWrite(const CString &strElement,tagDA *pDA,CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oElement);
long mms_XmlWrite_SubDA(const CString &strElement,tagDA *pDA,CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oElement);

// 2013-2-18  实现对模型文件的读取操作
BOOL mms_XmlRead(const CString &strFile, ACSI_NODE *pDevice);
long mms_XmlRead(ACSI_NODE *pDevice, CXmlRWNodeBase&pElement);
long mms_XmlRead(LD_NODE *pLDevice, CXmlRWNodeBase &pNode);
long mms_XmlReadData(LD_DATASET_INFO *pLD_INFO, CXmlRWNodeBase &pNode);
long mms_XmlReadData(RCB_NODE *pRCB, int &nRcb, CXmlRWNodeBase &pNode);
long mms_XmlReadData(LD_NODE *pLDevice, CString strID, CXmlRWNodeBase &pNode);
long mms_XmlReadData(tagDA *pDAs, int &nCount, RCB_NODE *pRCB, int &nRcb, CXmlRWNodeBase &pNode);
long mms_XmlRead(tagDA *pDA, CXmlRWNodeBase &pNode);
long mms_XmlRead_SubDA(tagDA *pDA, CXmlRWNodeBase &pNode);
long mms_XmlReadJournalCtrls(LD_JOURNAL_CTRLS *pJournalCtrls, CXmlRWNodeBase &pNode);
long mms_XmlReadJournal(LD_LOG_INFO *pJournal, CXmlRWNodeBase &pNode);

// 2013-4-16  加载 scd/cid 文件
void xml_LoadscdFile(const CString &strFile, ACSI_NODE *pDevice);
// 2013-4-16  加载连接点
void xml_LoadAccessPoint(CXmlRWNodeBase &pNode, ACSI_NODE *pDevice);
// 2013-4-16  加载逻辑设备描述
void xml_LoadLDDesc(CXmlRWNodeBase &pNode,ACSI_NODE *pDevice);
// 2013-4-16  加载数据集描述
void xml_LoadDataSetDesc(CXmlRWNodeBase &pNode, LD_NODE*pLD);
// 2013-12-24  加载数据集描述
void xml_LoadDataInfor(CXmlRWNodeBase &pNode, LD_DATASET_INFO*pDataset);

//////////////////////////////////////////////////////////////////////////
BOOL mms_GetXml(ACSI_NODE *pDevice, CString &bstrXml, BOOL bOblyGetLd=FALSE);
BOOL mms_GetXml(LD_NODE *pLDevice, CString &bstrXml);
BOOL mms_GetXml(LD_DATASET_INFO *pDataset, CString &bstrXml);

BOOL mms_SetXml(ACSI_NODE *pDevice,const  CString &bstrXml);
BOOL mms_SetXml(LD_NODE *pLDevice,const  CString &bstrXml);
BOOL mms_SetXml(LD_DATASET_INFO *pDataset,const CString &bstrXml);

void mms_InitLdAndBrcb(ACSI_NODE *pDestDevice, ACSI_NODE *pSrcDevice);

//////////////////////////////////////////////////////////////////////////
//数据建模部分
void mms_XmlWriteNode(const CString &strFile,ACSI_NODE *pDevice, BOOL bChangeFile);
void mms_XmlWriteNode(ACSI_NODE *pDevice, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent);
void mms_XmlWriteNode(LD_NODE *pLDevice, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent);
void mms_XmlWriteNode(MMS_DATA_NODE *pNode, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent);
void mms_XmlWriteNodeAttr(MMS_DATA_NODE *pNode, CXmlRWElementBase &oElement);

// void mms_XmlReadNode(const CString &strFile,ACSI_NODE *pDevice);
// void mms_XmlReadNode(LD_NODE *pLDevice, CXmlRWElementBase&pElement);
// void mms_XmlReadNode(MMS_DATA_NODE *pNode, CXmlRWElementBase&pElement);
