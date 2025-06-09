/**
 *@file
 *\brief �������ݼ�������
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
	 *@brief �����û��޸ĵ����ݼ�
	 *@param[in] strPrcdrID ��������ID
	 *@return ����ָ�����ݼ�
	 */ 
	CDvmDataset* Produce(const CString& strPrcdrID);
	/**
	 *@brief ��ȡ���в��Ե����ݼ������û����ݼ��ĸ���
	 *@return ����ָ�����ݼ�
	 */ 
	CDvmDataset* GetDataset();
};

#endif