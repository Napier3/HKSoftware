/**
 *@file
 *\brief ���Թ��̶���(��ָ��)
 */

#ifndef TCPEDGEPRCDRREAD_H
#define TCPEDGEPRCDRREAD_H

#include "TcpEdgePrcdrBase.h"

class CTcpEdgePrcdr_Read : public CTcpEdgePrcdrBase
{
public:
	CTcpEdgePrcdr_Read();
	virtual ~CTcpEdgePrcdr_Read();

public:
	/**
	 *@brief ִֹͣ�в�������
	 *@return ���ط�0ֹͣ�ɹ�
	 */ 
	virtual BOOL RunStepNull();

	//����Ӧ�����߼�
	/**
	 *@brief ��ϸ������ձ�������
	 *@param[in] pPkgDetail ���Ķ���
	 *@return ���ط�0����ɹ�
	 */ 
	virtual BOOL ProcessPackageDetail(CPxPkgBase *pPkgDetail);
	/**
	 *@brief ���´�����Ϣ
	 *@param[in] pPkgDetail ���Ķ���
	 *@param[in] strID ���ݼ�ID
	 */ 	
	void UpdateFailErrorInfo(CPxPkgBase *pPkgDetail, CString strID);
	/**
	 *@brief ���´�����Ϣ
	 *@param[in] strNecessityLack ��Ҫ����ȱʧ��Ϣ
	 *@param[in] strNecessityErr ��Ҫ����������Ϣ
	 *@param[in] strRangeOut ������Χ��Ϣ
	 *@param[in] strReturnFalse ����ֵ������Ϣ
	 *@return ���س�����Χ��Ϣ
	 */ 	
	void UpdateErrInfo(QString strNecessityLack, QString strNecessityErr, QString strRangeOut, QString strReturnFalse);
};

#endif