/**
 *@file
 *\brief ���Թ��̶���(�ļ�����ָ��)
 */

#ifndef TCPEDGEPRCDRFILE_H
#define TCPEDGEPRCDRFILE_H

#include "TcpEdgePrcdrBase.h"

class CTcpEdgePrcdr_File : public CTcpEdgePrcdrBase
{
public:
	CTcpEdgePrcdr_File();
	virtual ~CTcpEdgePrcdr_File();

private:
	BOOL m_bRecAppSetCfgFileResp;   //�����ж��Ƿ��յ���AppSetCfgFileResp����
	CString m_strFilePath; //�ļ�·��,�����ļ���
	CString m_strFileName; //�ļ���
	BOOL m_bFileFind;//�ж��ļ��Ƿ��ȡ�ɹ�

	CString m_strParaSetID;
	CString m_strJobId;
	CString m_strBase64;
	CString m_strCmdId;	//���ڼ�¼�����ķ��ͱ���ID
	CString m_strContinue; //���ڼ�¼�����ķ��ͱ����Ƿ��к���
	long m_nFileSegNo;	//���ڼ�¼�����ķ��ͱ��ĵ����
	CString m_strRecvCrc32;//���ڼ�¼���ܵ���FileGetResp�е�CRC32

	long m_nFileGetType;//�ٻ��ļ������� 0-��ͨ,1-ģ��,2-����,3-����

	long m_nMaxFileSize;
	long m_nCurFileSize;

private:
	//���͡���ȡ�ļ�����
	long GetFileSize(const CString& strFilePath);
	BOOL Base64ToFile(const CString& strFilePath, long& nFileLength);
	CString FileToBase64(const CString& strFilePath);

	BOOL ProcessFileGet(CPxPkgBase *pPkgDetail);
	BOOL ProcessFileGetResp(CPxPkgBase *pPkgDetail);
	BOOL ProduceData_FileGetResp(CPxPkgBase *pPkgDetail);
	BOOL ProduceData_FileGet();
	BOOL ProduceData_FileTransResp(const CString& strCmdId, const CString& strFileSegNo,
		CString strStatus, CString strErrorCode, CString strNote);
	BOOL ProduceData_FileTransReq();

	//BOOL ProcessFileSend(CPxPkgBase *pPkgDetail);
	//BOOL ProduceData_FileSend(SOCKET hSocket);

	CString GetValueFromDataset(const CString& strDataID);
	CString CRC32(CString strFilePath, long nFileLength);

	//������Dataset����
	void CreateDataset(CTcpEdgePkgHead* pHead);

private:
	BOOL ProcessDeviceGetLogReq(CPxPkgBase *pPkgDetail);
	BOOL ProcessContGetLogReq(CPxPkgBase *pPkgDetail);
	BOOL ProcessAppGetLogReq(CPxPkgBase *pPkgDetail);
	
	BOOL ProcessAppGetCfgFileReq(CPxPkgBase *pPkgDetail);
	//BOOL ProcessAppSetCfgFileReq(CPxPkgBase *pPkgDetail);

	BOOL ProcessDeviceUpdateStatusReq(CPxPkgBase *pPkgDetail);

	BOOL ProcessAppInstallStateReq(CPxPkgBase *pPkgDetail);

public:
	/**
	 *@brief ִֹͣ�в�������
	 *@return ���ط�0ֹͣ�ɹ�
	 */ 
	virtual BOOL RunStepNull();
	/**
	 *@brief ��ϸ������ձ�������
	 *@param[in] pPkgDetail ���Ķ���
	 *@return ���ط�0����ɹ�
	 */ 
	virtual BOOL ProcessPackageDetail(CPxPkgBase *pPkgDetail);
	/**
	 *@brief �����ļ���������
	 *@param[in] strID ��������(FileModelGet/FileTopoGet/FileMessageGet)
	 */ 
	void SetFileGetType(const QString& strID);
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