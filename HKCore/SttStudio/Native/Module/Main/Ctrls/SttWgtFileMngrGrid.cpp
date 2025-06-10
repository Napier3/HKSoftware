#include <QDir>
#include "SttWgtFileMngrGrid.h"
#include "../SttXuiData/SttXuiDataFileMngrGrid.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../XLangResource_Native.h"
#include <QHeaderView>
#include "../../../../61850/Module/XLanguageResourcePp_Mms.h"



QSttWgtFileMngrGrid::QSttWgtFileMngrGrid(QWidget* pParent)
{
	m_pParent = pParent;
	setParent(pParent);
}

QSttWgtFileMngrGrid::~QSttWgtFileMngrGrid()
{

}

void ListFiles(const char * dir)
{
	
}

void QSttWgtFileMngrGrid::InitUI()
{
	setRowCount(0);
	setColumnCount(4);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setSelectionMode(QAbstractItemView::SingleSelection);
	QStringList listHeader;

	listHeader << /*"名称"*/ g_sLangTxt_Name<< /*"格式"*/g_sLangTxt_Format <</* "大小(KB)"*/g_sLangTxt_Size << /*"日期"*/g_sLangTxt_Dates; 

	setHorizontalHeaderLabels(listHeader);
	setColumnWidth(0, 300);
	setColumnWidth(1, 200);
	setColumnWidth(2, 200);
	setColumnWidth(3, 200);
#ifndef _USE_IN_IED_QT5
	horizontalHeader()->setClickable(false);
#endif

	setCornerButtonEnabled(false);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void QSttWgtFileMngrGrid::Clear()
{
	long nCount = rowCount();
	for (int i = nCount - 1; i >= 0; i--)
	{
		removeRow(i);
	}
}

void QSttWgtFileMngrGrid::LoadFiles(const CString& strPath, const CString& strStyle)
{
	CString strFilePath = strPath;
	if(strPath.Find(":") == -1)
	{
		strFilePath = _P_GetBinPath() + strFilePath;
	}

	QDir dir(strFilePath);
	if(!dir.exists())
	{
		return ;
	}

	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);//实现对文件的过滤
	dir.setSorting(QDir::Size | QDir::Reversed);//实现对文件输出的排序

	QFileInfoList list = dir.entryInfoList();
	for (int i = 0; i < list.size(); ++i)
	{
		QFileInfo fileInfo = list.at(i);
		QString suffix = fileInfo.suffix();
		if(QString::compare(suffix, strStyle, Qt::CaseInsensitive) ==  0)//通过QFileInfo来实现对文件类型的过滤
		{
			QString absolute_file_path = fileInfo.absoluteFilePath();
			long nIndex = this->rowCount();
			insertRow(nIndex);

			QString strName = fileInfo.baseName();
#ifdef _PSX_QT_LINUX_	
			strName = strName.toLocal8Bit();
			strName = QString::fromUtf8(strName.toStdString().c_str());
#endif
			setItem(nIndex, 0, new QTableWidgetItem(strName));
			setItem(nIndex, 1, new QTableWidgetItem(fileInfo.completeSuffix()));
			setItem(nIndex, 2, new QTableWidgetItem(QString::number(fileInfo.size() / 1024)));
			setItem(nIndex, 3, new QTableWidgetItem(fileInfo.created().toString("yyyy-MM-dd hh:mm:ss")));
		}
	}
}

void QSttWgtFileMngrGrid::InitUIOwn(CExBaseObject *pSttXuiData)
{
	setRowCount(0);
	setColumnCount(4);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setSelectionMode(QAbstractItemView::SingleSelection);
	QStringList listHeader;
	listHeader <<g_sLangTxt_Name <</* "格式" */g_sLangTxt_Format<< /*"大小(KB)"*/g_sLangTxt_Size << /*"日期"*/g_sLangTxt_Dates; 

	setHorizontalHeaderLabels(listHeader);
#ifndef _USE_IN_IED_QT5
	horizontalHeader()->setClickable(false);
#endif
	setCornerButtonEnabled(false);
	if(pSttXuiData)
	{
		CSttXuiDataFileMngrGrid* pData = (CSttXuiDataFileMngrGrid*)pSttXuiData;
		setObjectName(pData->m_strID);
		setGeometry(pData->m_nX*g_dUIShowCoef, pData->m_nY*g_dUIShowCoef, pData->m_nCx*g_dUIShowCoef, pData->m_nCy*g_dUIShowCoef);
		long nWidth = this->width();
		setColumnWidth(0, nWidth / 3);
		setColumnWidth(1, nWidth / 8);
		setColumnWidth(2, nWidth / 8);
		setColumnWidth(3, nWidth / 4);
		//加载指定types的文件
		CSttXuiDataFileTypes* pTypes = (CSttXuiDataFileTypes*)pData->FindByClassID(MNGRCLASSID_CSTTXUIDATAFILETYPES);
		if(pTypes)
		{
			POS pos = pTypes->GetHeadPosition();
			while (pos)
			{
				CSttXuiDataFileType* pType = (CSttXuiDataFileType*)pTypes->GetNext(pos);
				LoadFiles(pType->m_strRoot, pType->m_strType);
			}
		}
	}
}
