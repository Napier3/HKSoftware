#include "SttFileMngrTree.h"

#include <QDirIterator>
#include <QHeaderView>
#include <QStyleFactory>
#include <QIcon>
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../../../../Module/API/StringConvert/String_Utf8_To_Gbk.h"
#include "../../../XLangResource_Native.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/XLanguage/XLanguageResource.h"
//#include "../../SttTestCntrFrameBase.h"
#include <QApplication>
#include <QTextCodec>


QSttFileMngrTree::QSttFileMngrTree(QWidget *parent):QScrollTreeWidget(parent)
{
	m_oFileMngr.SetOnllySearchMainTypeFile(FALSE);//可支持多个类型搜索
//	m_bUseCodeConversion = FALSE;
	InitUI();

// 	m_bRunning = FALSE;
// 	installEventFilter(this);
}

QSttFileMngrTree::~QSttFileMngrTree()
{

}


void QSttFileMngrTree::InitUI()
{
	QStringList astrHeadList;
	CString strName, strType, strSize;
	//strName = _T("名称");
	//strType = _T("类型");
	//strSize = _T("大小");
	astrHeadList<<g_sLangTxt_Name<<g_sLangTxt_Native_Type<<g_sLangTxt_Size2 ;
	setHeaderLabels(astrHeadList);

	if (g_pSttGlobalFont != NULL)
	{
		setFont(*g_pSttGlobalFont);//20221026 设置字体
	}

	setColumnCount(3);
	setColumnWidth(0,500);
	setStyleSheet("QTreeWidget::item{height:50px}");
//	setStyle(QStyleFactory::create("windows"));
	header()->setSortIndicator(0,Qt::AscendingOrder);//第0列设置排序指示符为升序
	setItemsExpandable(true);
}

BOOL QSttFileMngrTree::IsUsbFolder(const CString &strPath)
{
#ifdef _PSX_QT_LINUX_
	if (strPath.Find(_T("/Usb/sda")) >0)
	{
        return TRUE;
	}
#endif

	return FALSE;
}

void QSttFileMngrTree::InitShowFolderViewTree(const CString &strRootFolderPath)
{
	disconnect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)),this,SLOT(slot_OnFileTreeViewDoubleClick(QTreeWidgetItem*, int)));
	m_oFileMngr.DeleteAll();
	clear();

// #ifdef _PSX_QT_LINUX_
// 	m_oFileMngr.SetUseUtf8TextCodec(!IsUsbFolder(strRootFolderPath));
// #endif

	m_oFileMngr.SetLibraryPath(strRootFolderPath,TRUE,TRUE,FALSE);
	//	 DeleteAllItems();
	CExBaseObject *pCurObj = NULL;
	POS pos = m_oFileMngr.GetHeadPosition();

	while(pos)
	{
		pCurObj = m_oFileMngr.GetNext(pos);
		InsertItemToTreeCtrl(pCurObj,NULL);
	}

	connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)), SLOT(slot_OnFileTreeViewDoubleClick(QTreeWidgetItem*, int)));
}

void QSttFileMngrTree::InsertItemToTreeCtrl(CExBaseObject* pObj,QExBaseTreeWidgetItem *pItemParent)
{
	QExBaseTreeWidgetItem *pTreeItem = NULL;

	pTreeItem = InsertItem(pItemParent,pObj);
	pObj->m_dwItemData = (DWORD)pTreeItem;
	pTreeItem->m_pItemData = pObj;

	if(xfile_IsFolder(pObj->GetClassID()))
	{
		InsertItemChildrenToTreeCtrl(pObj,pTreeItem);
	}
}

void QSttFileMngrTree::InsertItemChildrenToTreeCtrl(CExBaseObject* pObj,QExBaseTreeWidgetItem *pItemParent)
{
	CExBaseObject* pObjChild = NULL;

	if( xfile_IsFolder(pObj->GetClassID()) )
	{
		CExBaseList* pList = (CExBaseList*)pObj;
		POS pos = pList->GetHeadPosition();

		while(pos != NULL)
		{
			pObjChild = (CExBaseObject*)pList->GetNext(pos);
			InsertItemToTreeCtrl(pObjChild,pItemParent);
		}
	}
}

QExBaseTreeWidgetItem* QSttFileMngrTree::InsertItem(QExBaseTreeWidgetItem *parent, CExBaseObject* pObj)
{
	QExBaseTreeWidgetItem *pNew = NewItem(parent, pObj);
	CString strXFileName;

// 	if (m_bUseCodeConversion)
// 	{
// 		utf8_to_gbk(pObj->m_strName,strXFileName);	
// 	} 
// 	else
		strXFileName = pObj->m_strName;

//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("QSttFileMngrTree::InsertItem[%s]"),pObj->m_strName.GetString());
	pNew->setText(0, strXFileName);
	CString strPicPath;
	strPicPath = _P_GetResourcePath();
	CString strType;

	if (pObj->GetClassID() == CLASSID_XFOLDER)
	{
		CXFolder *pXFolder = (CXFolder*)pObj;
		//strType = _T("文件夹");
//		xlang_GetLangStrByFile(g_sLangTxt_File ,"File");
		pNew->setText(1,g_sLangTxt_Folder);
		pNew->setText(2, _T(""));
#ifdef _PSX_QT_WINDOWS_
		strPicPath.AppendFormat(_T("folder.png"));
#else
		strPicPath = ":/ctrls/images/folder.png";
#endif
		pNew->setIcon(0,QIcon(strPicPath));
	}
	else if (pObj->GetClassID() == CLASSID_XFILE)
	{
		CXFile *pXFile = (CXFile*)pObj;
// #ifdef _PSX_QT_LINUX_
// 		CString strFilePath;
// 		strFilePath = pXFile->GetTotalFileName();
// 		//在U盘内使用GBK，否则使用utf8
// 		long nFileSize = pXFile->GetFileSize(strFilePath.Find(_T("/Usb/sda")) == -1);
// #else
		long nFileSize = pXFile->GetFileSize();
//#endif
		//strType = _T("文件");
		pNew->setText(1,g_sLangTxt_File);
		long nKB_Size = nFileSize / 1024;
		long nM = nKB_Size / 1000;
		long nK = nKB_Size - nM * 1000;
		CString strSize;
			
		if (nM > 0)
		{
			strSize.Format(_T("%d,%03d KB"), nM, nK);
		} 
		else if (nK > 0)
		{
			strSize.Format(_T("%d KB"), nK);
		}
		else
		{
			strSize.Format(_T("%d B"), nFileSize);
		}

		pNew->setText(2, strSize);
#ifdef _PSX_QT_WINDOWS_
		strPicPath.AppendFormat(_T("file.png"));
#else
		strPicPath = ":/ctrls/images/file.png";
#endif
		pNew->setIcon(0,QIcon(strPicPath));
	}

	return pNew;
}

QExBaseTreeWidgetItem* QSttFileMngrTree::NewItem(QExBaseTreeWidgetItem *parent, CExBaseObject *pData)
{
	if (parent == NULL)
	{
		return new QExBaseTreeWidgetItem(this, pData);
	}
	else
	{
		return new QExBaseTreeWidgetItem(parent, pData);
	}
}

void QSttFileMngrTree::slot_OnFileTreeViewDoubleClick(QTreeWidgetItem* pTreeWidgetItem, int nIndex)
{
	QExBaseTreeWidgetItem *ExBaseTreeWidgetItem = (QExBaseTreeWidgetItem*)pTreeWidgetItem;

	if (ExBaseTreeWidgetItem->m_pItemData == NULL)
	{
		return;
	}

	if (IsScrollMoving())
	{
		return;
	}

	long nClassID = ExBaseTreeWidgetItem->m_pItemData->GetClassID();

	if (nClassID != CLASSID_XFOLDER)
	{
		return;
	}

	CXFolder *pFolder = (CXFolder*)ExBaseTreeWidgetItem->m_pItemData;

	if (pFolder->HasSearched())
	{
		pTreeWidgetItem->setExpanded(!pTreeWidgetItem->isExpanded());
		return;
	}

	disconnect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)),this, SLOT(slot_OnFileTreeViewDoubleClick(QTreeWidgetItem*, int)));

#ifdef _PSX_QT_LINUX_
	CString strFolderPath;
	strFolderPath = pFolder->GetFolderPath();

	QTextCodec *pOldTextCodec = NULL;
	InitLocalCodec_BeforeReadWrite(strFolderPath,&pOldTextCodec);
#endif

	pFolder->Search(m_oFileMngr.GEtFilePostfixList(),TRUE,TRUE,FALSE);

#ifdef _PSX_QT_LINUX_
	ResetLocalCodec(pOldTextCodec);
#endif

	CExBaseObject *pCurObj = NULL;
	POS pos = pFolder->GetHeadPosition();

	while(pos)
	{
		pCurObj = pFolder->GetNext(pos);
		InsertItemToTreeCtrl(pCurObj,ExBaseTreeWidgetItem);
	}

	pTreeWidgetItem->setExpanded(!pTreeWidgetItem->isExpanded());
	connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)), SLOT(slot_OnFileTreeViewDoubleClick(QTreeWidgetItem*, int)));
}

void QSttFileMngrTree::slot_TreeItemClicked(QTreeWidgetItem* pItem, int nIndex)
{
//	slot_OnFileTreeViewDoubleClick(pItem,0);
}

// void utf8_to_gbk(const CString &strUtf8, CString &strGbk)
// {
// 	unsigned char* pTmpStringGBK = NULL;
// 	char *pTmpStringUTF8 = (char *)strUtf8.GetString();
// 	int nLenth = 0;
// 	utf8_to_gbk_r((const unsigned char*)pTmpStringUTF8,strlen(pTmpStringUTF8),&pTmpStringGBK,&nLenth);
// 
// 	if (nLenth>0)
// 	{
// 		strGbk = (char*)pTmpStringGBK;
// 	} 
// 	else
// 	{
// 		strGbk = strUtf8;
// 	}
// 
// 	if (pTmpStringGBK != NULL)
// 	{
// 		delete pTmpStringGBK;
// 	}
// }

// bool QSttFileMngrTree::eventFilter(QObject *obj, QEvent *event)
// {
// 	//if (event->type() == QEvent::MouseButtonDblClick)
// 	//{
// 	//	QMouseEvent *pMouseEvent = (QMouseEvent *)event;
// 	//	m_bRunning = TRUE;
// 	//	mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
// 	//	m_bRunning = FALSE;
// 	//	return  true;
// 	//}
// 
// 	return QScrollTreeWidget::eventFilter(obj,event);
// 
// }
// 
// void QSttFileMngrTree::mouseReleaseEvent(QMouseEvent * event)
// {
// 	//if (m_bRunning)
// 	//{
// 	//	QScrollTreeWidget::mouseReleaseEvent(event);
// 	//	return;
// 	//}
// 
// 	//QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
// 	//QApplication::postEvent(this,pEvent);
// 	QScrollTreeWidget::mouseReleaseEvent(event);
// }

BOOL GetUsbRootFolderPath(CString &strUsbRootFolderPath)
{
#ifdef _PSX_QT_LINUX_
	CString strPath,strTmpFolderFileName,strTmpFolderPath;
	CString strAbsFolderPath;
#ifdef _PSX_OS_CENTOS_
	strAbsFolderPath = "/run/media/root/";
#else
	strAbsFolderPath = _P_GetSystemPath();
	strAbsFolderPath += "Usb/";
#endif
	QDir dir(strAbsFolderPath);

	//将过滤后的文件名称存入到files列表中
	QStringList astrChildFolders,atrFolderFilters,astrTmp;
	astrChildFolders = dir.entryList(atrFolderFilters, QDir::Dirs| QDir::NoDotAndDotDot);

	if(astrChildFolders.size() == 0)
	{
		return FALSE;
	}

	for (int nIndex = 0;nIndex<astrChildFolders.size();nIndex++)
	{
		strTmpFolderFileName = astrChildFolders.at(nIndex);
		strTmpFolderPath.Format(_T("%s%s/"),strAbsFolderPath.GetString(),strTmpFolderFileName.GetString());
		QDir dirTmp(strTmpFolderPath);

		astrTmp = dirTmp.entryList(atrFolderFilters, QDir::Dirs| QDir::Files| QDir::NoDotAndDotDot);

		if(astrTmp.size()>0)//取USB文件夹下,第一个不为空的文件夹
		{
			strUsbRootFolderPath = strTmpFolderPath;
			return TRUE;
		}
	}

	strTmpFolderFileName = astrChildFolders.at(0);//如果都为空,则取第一个文件夹
	strUsbRootFolderPath.Format(_T("%s%s/"),strAbsFolderPath.GetString(),strTmpFolderFileName.GetString());
	return TRUE;
#else
	return FALSE;
#endif
}

