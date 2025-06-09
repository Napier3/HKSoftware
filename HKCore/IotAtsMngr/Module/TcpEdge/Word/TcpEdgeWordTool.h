/**
 *@file
 *\brief 使用Qt接口操作word文档来生成报告
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
	CExBaseList m_oBuffer;//用于缓存需要保存的报告
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
	 *@brief 初始化工具
	 *@param[in] strFilePath 生成word文档的路径
	 */ 
	void InitWordTool(QString strFilePath);
	/**
	 *@brief 根据数据集填充报告
	 *@param[in] pDvmDataset 测试数据集
	 *@return 返回1完成
	 */ 
	BOOL FillTestReport(CDvmDataset* pDvmDataset);
	/**
	 *@brief 初始化后创建word文件
	 *@return 返回1完成
	 */ 
	BOOL CreateNewWord();
	/**
	 *@brief 获取生成的word文件路径
	 *@return 返回文件路径
	 */ 
	CString GetFilePath();
};

#endif