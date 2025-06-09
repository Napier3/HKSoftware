#include "stdafx.h"
#include "TcpEdgeWordTool.h"
#include <QFileInfo>
#include <QDir>

CTcpEdgeWordTool::CTcpEdgeWordTool()
{

}

CTcpEdgeWordTool::~CTcpEdgeWordTool()
{

}

void CTcpEdgeWordTool::CreateWord(QAxObject* pApp)
{
	QAxObject *docs = pApp->querySubObject("Documents");
	docs->dynamicCall("Add()");
}

void CTcpEdgeWordTool::AddText(QAxObject* pApp, const QString& strText)
{
	QAxObject* selection = pApp->querySubObject("Selection");
	QAxObject* range = selection->querySubObject("Range");
	range->dynamicCall("InsertAfter(const QString&)", strText);
	JumpToTheEnd(pApp);
}

void CTcpEdgeWordTool::AddIcon(QAxObject* pApp, const QString& strFullFileName)
{
	QAxObject* selection = pApp->querySubObject("Selection");
	QAxObject* inlineShapes = selection->querySubObject("InlineShapes");
	inlineShapes->dynamicCall("AddPicture(const QString&)", strFullFileName);
	JumpToTheEnd(pApp);
}

QAxObject* CTcpEdgeWordTool::AddTable(QAxObject* pApp, long nRows, long nCols)
{
	QAxObject* selection = pApp->querySubObject("Selection");
	QAxObject* range = selection->querySubObject("Range");
	QAxObject* tables = selection->querySubObject("Tables");

	QVariantList params;
	params.append(range->asVariant());
	params.append(nRows);
	params.append(nCols);
	tables->querySubObject("Add(QAxObject*, int, int, QVariant&, QVariant&)", params);
	QAxObject* table = selection->querySubObject("Tables(int)", 1);
	table->setProperty("Style", "网格型");

	QAxObject* borders = table->querySubObject("Borders");
	borders->setProperty("InsideLineStyle", 1);
	borders->setProperty("OutsideLineStyle", 1);

	JumpToTheEnd(pApp);

	return table;
}

void CTcpEdgeWordTool::SetCellText(QAxObject* pTable, long nRow, long nCol, const QString& strText)
{
	QAxObject* range = pTable->querySubObject("Cell(int,int)", nRow, nCol)->querySubObject("Range");
	range->dynamicCall("SetText(const QString&)", strText);
}

void CTcpEdgeWordTool::JumpToTheEnd(QAxObject* pApp)
{
	QAxObject* selection = pApp->querySubObject("Selection");
	QVariantList params;
	params.append(6);
	params.append(0);
	selection->dynamicCall("EndOf(QVariant&, QVariant&)", params).toInt();
}

void CTcpEdgeWordTool::SaveWord(QAxObject* pApp)
{
	QAxObject* activeDocument = pApp->querySubObject("ActiveDocument");
	activeDocument->dynamicCall("Save()");
}

void CTcpEdgeWordTool::SaveAsWord(QAxObject* pApp, const QString& strFullFileName)
{
	QAxObject* activeDocument = pApp->querySubObject("ActiveDocument");
	activeDocument->dynamicCall("SaveAs (const QString&, const QVariant&)", strFullFileName, 16);
}

void CTcpEdgeWordTool::CloseWord(QAxObject* pApp)
{
	QAxObject* activeDocument = pApp->querySubObject("ActiveDocument");
	activeDocument->dynamicCall("Close (boolean)", true);
}

QAxObject* CTcpEdgeWordTool::OpenWord(QAxObject* pApp, const QString& strFullFileName)
{
	QAxObject* docs = pApp->querySubObject("Documents");
	QAxObject* doc = pApp->querySubObject("Open(QString)", strFullFileName);
	return doc;
}

void CTcpEdgeWordTool::InitWordTool(QString strFilePath)
{
	m_strFilePath = strFilePath;

	long nPathIndex = m_strFilePath.lastIndexOf("\\");
	if(nPathIndex == -1)
	{
		nPathIndex = m_strFilePath.lastIndexOf("/");
	}

	QString strFullPath = m_strFilePath.left(nPathIndex);
	QDir dir(strFullPath);
	if (!dir.exists())
	{
		dir.mkpath(strFullPath);
	}
}

BOOL CTcpEdgeWordTool::CreateNewWord()
{
	QReadLocker lock(&m_oWordToolLocker);

	QAxObject* app = new QAxObject();

	BOOL bRet = app->setControl("Word.Application");
	if (!bRet)
	{
		bRet = app->setControl("kwps.Application");//尝试用wps打开
		if(!bRet)
		{
			return FALSE;
		}
	}
	
	app->setProperty("Visible", FALSE);

	QFileInfo file(m_strFilePath);
	if(file.exists())
	{
		OpenWord(app, m_strFilePath);
	}
	else
	{
		CreateWord(app);
		AddText(app, "配电边缘网关测试平台测试报告\n\n");
	}

	POS pos = m_oBuffer.GetHeadPosition();
	while (pos)
	{
		CExBaseList* pDvmDataset = (CExBaseList*)m_oBuffer.GetNext(pos);
		AddText(app, pDvmDataset->m_strName);
		QAxObject* table = AddTable(app, pDvmDataset->GetCount(), 4);
		POS posChild = pDvmDataset->GetHeadPosition();
		long nIndex = 1;
		while (posChild)
		{
			CDvmData* pData = (CDvmData*)pDvmDataset->GetNext(posChild);
			CDvmValue* pValue = (CDvmValue*)pData->GetTail();
			
			SetCellText(table, nIndex, 1, pData->m_strName);
			SetCellText(table, nIndex, 2, pData->m_strID);

			if(pValue)
			{
				SetCellText(table, nIndex, 3, pValue->m_strValue);
				SetCellText(table, nIndex, 4, pValue->m_strDataType);
			}

			nIndex++;
		}
		AddText(app, "\n");
	}

	SaveAsWord(app, m_strFilePath);
	CloseWord(app);
	app->dynamicCall("Quit(void)");
	delete app;

	return TRUE;
}

BOOL CTcpEdgeWordTool::FillTestReport(CDvmDataset* pDvmDataset)
{
	QWriteLocker lock(&m_oWordToolLocker);

	long nCount = pDvmDataset->GetCount();
	if(nCount)
	{
		if(m_oBuffer.FindByID(pDvmDataset->m_strID))
		{
			m_oBuffer.DeleteByID(pDvmDataset->m_strID);
		}
		m_oBuffer.AddNewChild((CExBaseList*)pDvmDataset->CloneEx(TRUE, TRUE));
	}

	return TRUE;
}

CString CTcpEdgeWordTool::GetFilePath()
{
	return m_strFilePath;
}