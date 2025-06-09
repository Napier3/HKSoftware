/**
 *@file
 *\brief ʹ��Qt�ӿڲ���word�ĵ������ɱ���
 */

#ifndef TCPEDGEWORDTOOL_H
#define TCPEDGEWORDTOOL_H
#include "../../../../Module/DataMngr/DvmDataset.h"
#include "ActiveQt/QAxObject"
#include <QReadWriteLock>

class CTcpEdgeWordTool
{
private:
	QString m_strFilePath;
	QReadWriteLock m_oWordToolLocker;

public:
	CExBaseList m_oBuffer;//���ڻ�����Ҫ����ı���
	CTcpEdgeWordTool();
	virtual ~CTcpEdgeWordTool();

private:
	void CreateWord(QAxObject* pApp);
	void AddText(QAxObject* pApp, const QString& strText);
	void AddIcon(QAxObject* pApp, const QString& strFullFileName);
	QAxObject* AddTable(QAxObject* pApp, long nRows, long nCols);
	void SetCellText(QAxObject* pTable, long nRow, long nCol, const QString& strText);
	void JumpToTheEnd(QAxObject* pApp);
	void SaveWord(QAxObject* pApp);
	void SaveAsWord(QAxObject* pApp, const QString& strFullFileName);
	void CloseWord(QAxObject* pApp);
	QAxObject* OpenWord(QAxObject* pApp, const QString& strFullFileName);

public:
	/**
	 *@brief ��ʼ������
	 *@param[in] strFilePath ����word�ĵ���·��
	 */ 
	void InitWordTool(QString strFilePath);
	/**
	 *@brief �������ݼ���䱨��
	 *@param[in] pDvmDataset �������ݼ�
	 *@return ����1���
	 */ 
	BOOL FillTestReport(CDvmDataset* pDvmDataset);
	/**
	 *@brief ��ʼ���󴴽�word�ļ�
	 *@return ����1���
	 */ 
	BOOL CreateNewWord();
	/**
	 *@brief ��ȡ���ɵ�word�ļ�·��
	 *@return �����ļ�·��
	 */ 
	CString GetFilePath();
};

#endif