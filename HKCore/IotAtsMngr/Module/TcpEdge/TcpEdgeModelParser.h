/**
 *@file
 *\brief �豸ģ�ͷ�������
 */
#ifndef TCPEDGEMODELPARSER_H
#define TCPEDGEMODELPARSER_H

#include "Pkg/TcpEdgePkgData_DataSpont.h"
#include "../../../Module/DataMngr/DvmDatasetGroup.h"

//��ģ���ļ��������ݵõ�һ��datasetgroup��xml
class CTcpEdgeDevice;
class CTcpEdgeModelParser
{
public:
	/** ���̰󶨵��豸 **/
	CTcpEdgeDevice* m_pDevice;
	/** �豸��ģ������ӳ�仺�� **/
	CDvmDatasetGroup m_oDataMapping;
	/** �豸��ģ�ͻ��� **/
	CDvmDatasetGroup m_oGroup;
	/** �豸��ģ�ʹ��� **/
	QString m_strErrorInfo;
	/** �������������� **/
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
	 *@brief ͨ�����Ľ�����ģ���ļ��б�
	 *@param[in] pDataSpont ��������
	 */ 
	void ParsePkg(CTcpEdgePkgData_DataSpont* pDataSpont);
	/**
	 *@brief ͨ��ģ���ļ�������ģ��
	 *@param[in] strFile ģ���ļ�
	 */ 
	void ParseFile(const CString strFile);
};

#endif