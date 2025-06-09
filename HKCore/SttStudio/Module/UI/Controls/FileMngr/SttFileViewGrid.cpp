#include "SttFileViewGrid.h"
#include "../../../../../Module/DataMngr/ShortData.h"
#include "../../../../../Module/XfileMngrBase/XFolder.h"
#include "../../../XLangResource_Native.h"
#include <QApplication>
#include <QProcess>


CSttFileViewGrid::CSttFileViewGrid(QWidget* pParent): QExBaseListGridBase(pParent)
{
	//m_nAdjustBeginCol = 1;
	InitGrid();
	m_bRunning = FALSE;
	installEventFilter(this);
}

CSttFileViewGrid::~CSttFileViewGrid()
{

}


void CSttFileViewGrid::InitGrid()
{
	InitGridTitle();
	SetDefaultRowHeight(50);
}

void CSttFileViewGrid::InitGridTitle()
{
	CString cTempStr[4]={/*_T("名称")*/g_sLangTxt_Name,/*_T("修改日期")*/g_sLangTxt_FileMngr_Date,/*_T("类型")*/g_sLangTxt_Type,/*_T("大小")*/g_sLangTxt_Size2};
	int iWidth[4]={300, 200,100,100};

	QExBaseListGridBase::InitGridTitle(cTempStr, iWidth, 4);
}

void CSttFileViewGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{

	if (pData->GetClassID() == CLASSID_XFILE)
	{
		CXFile *pFileData = (CXFile*) pData;
		CString strFileType =/* _T("文件")*/g_sLangTxt_File;

		CString strModifyTime;
		 pFileData->GetModifyTime(strModifyTime);

// #ifdef _PSX_QT_LINUX_
// 		 CString strFilePath;
// 		 strFilePath = pFileData->GetTotalFileName();
// 		 //在U盘内使用GBK，否则使用utf8
// 		 long nSize = pFileData->GetFileSize(strFilePath.Find(_T("/Usb/sda")) == -1);
// #else
		long nSize = pFileData->GetFileSize();
//#endif

		long nKB_Size = nSize / 1024;
		long nM = nKB_Size / 1024;
		long nK = nKB_Size - nM * 1024;

		CString strFileSize;

		if (nM > 0)
		{
			strFileSize.Format(_T("%d M"), nM);
		} 
		else if (nK > 0)
		{
			strFileSize.Format(_T("%d KB"), nK);
		}
		else
		{
			strFileSize.Format(_T("%d B"), nSize);
		}
		
//		CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("CSttFileViewGrid::ShowData[%s]"),pFileData->m_strName.GetString());
		Show_StaticString(pData, nRow,0, &pFileData->m_strName);
		Show_StaticString(pData,nRow,1,&strModifyTime);
		Show_StaticString(pData, nRow,2, &strFileType);
		Show_StaticString(pData, nRow,3, &strFileSize);

		nRow++;
	}
	else 
	{
		CString strFlieType  =/* _T("文件夹")*/g_sLangTxt_Folder;
		
		CXFolder *pFolderData = (CXFolder*) pData;
		CString strFolderPath =pFolderData->GetFolderPath();
		CString strModifyTime;
		//pFolderData->GetFolderModifyTime(strModifyTime);

		QProcess oProcess;
		CString strCmd;
		strCmd.Format(_T("du -c %s"),strFolderPath.GetString());
		oProcess.start(strCmd);
		oProcess.waitForFinished();
		QByteArray bSize = oProcess.readAllStandardOutput();

		CString strSize,strTmp1,strTmp2;
		strSize = (const char *)bSize;
		long nIndex = strSize.ReverseFind('t');
		strTmp1 = strSize.Left(nIndex);
		nIndex = strTmp1.ReverseFind('\n');
		strTmp2 = strTmp1.Mid(nIndex+1);
		long totalSize = CString_To_long(strTmp2);
		long nM = totalSize / 1024;
		double nG = 0.0f;
		nG = totalSize/1024/1024;

		CString strFolderSize;

		if (nG >= 1)
		{
			strFolderSize.Format(_T("%.1f G"), nG);
		}
		else if (nM > 0)
		{
			strFolderSize.Format(_T("%d M"), nM);
		} 
		else
		{
			strFolderSize.Format(_T("%d KB"), totalSize);
		}
		
		Show_StaticString(pData, nRow,0, &pFolderData->m_strName);
		Show_StaticString(pData,nRow,1,&strModifyTime);
		Show_StaticString(pData, nRow,2, &strFlieType);
		Show_StaticString(pData,nRow,3,&strFolderSize);
		nRow++;
	}

}

bool CSttFileViewGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return  true;
	}

	return QExBaseListGridBase::eventFilter(obj,event);

}

void CSttFileViewGrid::mousePressEvent(QMouseEvent * event)
{
	if (m_bRunning)
	{
		QExBaseListGridBase::mousePressEvent(event);
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
	QApplication::postEvent(this,pEvent);
	QExBaseListGridBase::mousePressEvent(event);

}

