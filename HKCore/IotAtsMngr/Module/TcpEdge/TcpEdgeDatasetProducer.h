/**
 *@file
 *\brief 测试数据集生成器
 */

#ifndef TCPEDGEDATASETPRODUCER_H
#define TCPEDGEDATASETPRODUCER_H
#include "Pkg/TcpEdgePkgData.h"
#include "Pkg/TcpEdgePkgHead.h"

class CTcpEdgeDatasetProducer
{
private:
	CTcpEdgePkgHead* m_pHead;
	CTcpEdgePkgData* m_pData;
	CDvmDataset* m_pDataset;
	void CopyItemData(CExBaseList* pDest, CExBaseList* pSrc);
	
public:
	CTcpEdgeDatasetProducer();
	virtual ~CTcpEdgeDatasetProducer();

public:
	/**
	 *@brief 生成用户修改的数据集
	 *@param[in] strPrcdrID 测试流程ID
	 *@return 返回指定数据集
	 */ 
	CDvmDataset* Produce(const CString& strPrcdrID);
	/**
	 *@brief 获取进行测试的数据集，是用户数据集的副本
	 *@return 返回指定数据集
	 */ 
	CDvmDataset* GetDataset();
};

#endif