/**
 *@file
 *\brief ���Թ��̶���(дָ��)
 */

#ifndef TCPEDGEPRCDRWRITE_H
#define TCPEDGEPRCDRWRITE_H

#include "TcpEdgePrcdrBase.h"

class CTcpEdgePrcdr_Write : public CTcpEdgePrcdrBase
{

public:
	CTcpEdgePrcdr_Write();
	virtual ~CTcpEdgePrcdr_Write();

private:
	BOOL ProcessCtrlCmd(CPxPkgBase *pPkgDetail);
	BOOL ProduceData_CtrlCmd(CString strCtrlType,CString strDeviceID,CString strCtrlVal,CString strDataRefer);
	BOOL ProcessParaSet(CPxPkgBase *pPkgDetail);

public:
	/**
	 *@brief ִֹͣ�в�������
	 *@return ���ط�0ֹͣ�ɹ�
	 */ 
	virtual BOOL RunStepNull();
	/**
	 *@brief ִ�в���Ӧ��
	 *@param[in] pPkgDetail ���Ķ���
	 *@return ���ط�0ִ�гɹ�
	 */ 
	virtual BOOL ProcessPackageAck(CPxPkgBase *pPkgDetail);
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
	void FailErrorInfo(CPxPkgBase *pPkgDetail, CString strID);
	/**
	 *@brief ��ȡ������Ϣ
	 *@param[in] strStatus ����״̬
	 *@param[in] strErrorCode �������
	 *@param[in] strNote ������ʾ
	 *@param[in] StrPkgID ���Ĳ���ID
	 *@return ���ش�����Ϣ
	 */ 
	QString FailErrorInfo(CString strStatus, CString strErrorCode, CString strNote, CString StrPkgID);
	/**
	 *@brief ��ȡʧ����Ϣ
	 *@param[in] strStatus ����״̬
	 *@param[in] strErrorCode �������
	 *@param[in] strNote ������ʾ
	 *@param[in] StrPkgID ���Ĳ���ID
	 *@return ����ʧ����Ϣ
	 */ 
	QString ReurnFalseInfo(CString strStatus, CString strErrorCode, CString strNote, CString StrPkgID);
	/**
	 *@brief ��ȡ������Χ��Ϣ
	 *@param[in] strStatus ����״̬
	 *@param[in] strErrorCode �������
	 *@param[in] strNote ������ʾ
	 *@param[in] StrPkgID ���Ĳ���ID
	 *@return ���س�����Χ��Ϣ
	 */ 	
	QString RangeOutInfo(CString strStatus, CString strErrorCode, CString strNote, CString StrPkgID);
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