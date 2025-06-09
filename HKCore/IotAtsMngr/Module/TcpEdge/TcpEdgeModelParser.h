/**
 *@file
 *\brief 设备模型分析器类
 */
#ifndef TCPEDGEMODELPARSER_H
#define TCPEDGEMODELPARSER_H

#include "Pkg/TcpEdgePkgData_DataSpont.h"
#include "../../../Module/DataMngr/DvmDatasetGroup.h"

//从模型文件分析数据得到一个datasetgroup的xml
class CTcpEdgeDevice;
class CTcpEdgeModelParser
{
public:
	/** 过程绑定的设备 **/
	CTcpEdgeDevice* m_pDevice;
	/** 设备的模型数据映射缓存 **/
	CDvmDatasetGroup m_oDataMapping;
	/** 设备的模型缓存 **/
	CDvmDatasetGroup m_oGroup;
	/** 设备的模型错误 **/
	QString m_strErrorInfo;
	/** 分析器分析错误 **/
	QString m_strParseErrorInfo;

private:
	void ParseFile(CJSON* pJson, CDvmDatasetGroup* pDatasetGroup);
	void ParseDevices(CExBaseList* pNode);
	void ParseServices(CExBaseList* pNode, CExBaseList* pRecord);
	void ParseDatas(CExBaseList* pNode, CExBaseList* pRecord);

public:
	CTcpEdgeModelParser();
	virtual ~CTcpEdgeModelParser();
	/**
	 *@brief 通过报文解析出模型文件列表
	 *@param[in] pDataSpont 报文数据
	 */ 
	void ParsePkg(CTcpEdgePkgData_DataSpont* pDataSpont);
	/**
	 *@brief 通过模型文件解析出模型
	 *@param[in] strFile 模型文件
	 */ 
	void ParseFile(const CString strFile);
};

#endif