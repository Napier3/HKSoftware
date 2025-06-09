#include "qsttselsclfilewidget.h"
#include "../../../../Module/API/StringApi.h"
#include "../../../../Module/API/StringConvertApi.h"
#include "../../../../61850/Module/SCL/SclFileMngr/XSclFileMngr.h"
#include "../Module/PopupDialog/SttPopupOpenDialog.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../../../61850/Module/SCL_Qt/QScdFileRWDlg.h"
#include "../../../../61850/Module/SCL/CcdFileRead.h"
#include "../../../../Module/System/TickCount32.h"
#include "../Module/PopupDialog/SttFileMngrTool.h"
#include"../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "QSttSelSclIedWidget.h"
#include <QFileDialog>
#include <QFile>
#ifdef _PSX_QT_LINUX_
#include <sys/sysinfo.h>
#include <stdint.h>
#include <malloc.h>
#endif
#include"../../XLangResource_Native.h"

// #ifndef _PSX_QT_LINUX_
// #include "../../../../61850/Module/SCL/SclFileRead.h"
// // #include "../src/gui/dialogs/qfiledialog.h"
// #endif

QSttSelSclFileWidget *g_pSttSelSclFileWidget = NULL;

QSttSelSclFileWidget::QSttSelSclFileWidget(QWidget *parent)
	: QWidget(parent)
{
	m_pBtns_HBoxLayout = NULL;
	m_pMainVLayout = NULL;
	m_pClearAll_Btn = NULL;
	m_pDelCurr_Btn = NULL;
	m_pAddScl_Btn = NULL;
	m_pSclIedSelect_Btn= NULL;
	m_pSttSelSclFileGrid = NULL;
}

QSttSelSclFileWidget::~QSttSelSclFileWidget()
{

}

void QSttSelSclFileWidget::InitUI()
{
	m_pMainVLayout = new QVBoxLayout;
	m_pBtns_HBoxLayout = new QHBoxLayout;
	m_pSttSelSclFileGrid = new CSttSelSclFileGrid(this);
	m_pSttSelSclFileGrid->SetTableFont(this->font());
	m_pSttSelSclFileGrid->InitGrid();
	CString strText;
	//strText = _T("新增SCL");
	xlang_GetLangStrByFile(g_sLangTxt_IEC_AddSCL,"IEC_AddSCL");
	m_pAddScl_Btn = new QPushButton(g_sLangTxt_IEC_AddSCL,this);
	//strText = _T("删除当前");
	xlang_GetLangStrByFile(g_sLangID_IEC_DeleteNow,"IEC_DeleteNow");
	m_pDelCurr_Btn = new QPushButton(g_sLangID_IEC_DeleteNow,this);
	//strText = _T("清空全部");
	xlang_GetLangStrByFile(g_sLangID_IEC_Emptyout,"IEC_Emptyout");
	m_pClearAll_Btn = new QPushButton(g_sLangID_IEC_Emptyout,this);
	//strText = _T("IED选择");
	xlang_GetLangStrByFile(g_sLangTxt_IEC_IEDselect,"IEC_IEDselect");
	m_pSclIedSelect_Btn = new QPushButton(g_sLangTxt_IEC_IEDselect,this);
	m_pSclIedSelect_Btn->setVisible(false);
	m_pBtns_HBoxLayout->addWidget(m_pAddScl_Btn);
	m_pBtns_HBoxLayout->addWidget(m_pDelCurr_Btn);
	m_pBtns_HBoxLayout->addWidget(m_pClearAll_Btn);
	m_pBtns_HBoxLayout->addWidget(m_pSclIedSelect_Btn);
	m_pBtns_HBoxLayout->addStretch();
	m_pMainVLayout->addWidget(m_pSttSelSclFileGrid);
	m_pMainVLayout->addLayout(m_pBtns_HBoxLayout);
	setLayout(m_pMainVLayout);
	InitDatas();
	m_pSttSelSclFileGrid->AttachDataViewOptrInterface(this);
	EnableButtons();

	QFontMetrics fontMetrics = QFontMetrics(font());
	QRect recContent_drugName = fontMetrics.boundingRect(g_sLangID_IEC_DeleteNow);
	int nDrugNameWidth = recContent_drugName.width();
	nDrugNameWidth *= 1.2;

	m_pAddScl_Btn->setFixedWidth(nDrugNameWidth);
	m_pDelCurr_Btn->setFixedWidth(nDrugNameWidth);
	m_pClearAll_Btn->setFixedWidth(nDrugNameWidth);
	m_pSclIedSelect_Btn->setFixedWidth(nDrugNameWidth);

	connect(m_pAddScl_Btn, SIGNAL(clicked()), this, SLOT(slot_AddScl_Clicked()));
	connect(m_pDelCurr_Btn, SIGNAL(clicked()), this, SLOT(slot_DelCurr_Clicked()));
	connect(m_pClearAll_Btn, SIGNAL(clicked()), this, SLOT(slot_ClearAll_Clicked()));
	connect(m_pSclIedSelect_Btn, SIGNAL(clicked()), this, SLOT(slot_SclIedSelect_Clicked()));
}

void QSttSelSclFileWidget::InitDatas()
{
	m_pSttSelSclFileGrid->ShowDatas(&g_oXSclFileMngr);

	if (g_oXSclFileMngr.GetCount()>0)
	{
		m_pSttSelSclFileGrid->SelectRow(1);
	}
}

void QSttSelSclFileWidget::slot_AddScl_Clicked()
{
	CString strFilePath,strFolderPath;

	strFolderPath = g_oFileMngrTool.GetFolderPath_STD(STT_FILE_MNGR_SCD);

	long nSize = 0;
#ifdef _PSX_QT_LINUX_
	QStringList astrPostfix;

    astrPostfix<<"*.scd"<<"*.icd"<<"*.cid"<<"*.tscd"<<"*.ccd";
	QSttPopupOpenDialog oOpenDlg(strFolderPath,astrPostfix,this);
	oOpenDlg.setFont(font());
	oOpenDlg.InitUI();

	if (oOpenDlg.exec() != QDialog::Accepted)
		return;

	if (!oOpenDlg.GetFilePath(strFilePath))
	{
		return;
	}

	nSize = oOpenDlg.GetFileSize();
 #else
	CString strText = g_sLangTxt_Native_SCLPath;
 	QFileDialog dlg(this, strText);
 	dlg.setFileMode(QFileDialog::AnyFile);
 	//strText = _T("SCD文件(*.scd);;ICD文件(*.icd);;CID文件(*.cid)");
	strText =g_sLangTxt_Native_SCLFilter;
 	dlg.setNameFilter(strText);
 
 	dlg.setViewMode(QFileDialog::Detail);
 	dlg.setAcceptMode(QFileDialog::AcceptOpen);
 
 	dlg.setDirectory(strFolderPath);
	//strText = _T("文件路径");
	dlg.setLabelText(QFileDialog::LookIn, g_sLangTxt_FilePath);
	//strText = _T("文件名");
	dlg.setLabelText(QFileDialog::FileName,g_sLangTxt_FileName);
	//strText = _T("文件类型");
	dlg.setLabelText(QFileDialog::FileType,g_sLangTxt_Native_FileType);
 	dlg.setAcceptMode(QFileDialog::AcceptOpen);
	//strText = _T("打开");
	dlg.setLabelText(QFileDialog::Accept,g_sLangTxt_Open);
 
	//strText = _T("取消");
	dlg.setLabelText(QFileDialog::Reject,g_sLangTxt_Cancel);
 
 
 	if (dlg.exec() != QFileDialog::Accepted)
 	{
 		return;
 	}
 
 	QStringList fileNames;
 	fileNames = dlg.selectedFiles();
 	strFilePath = fileNames.at(0);
 
 	QFile oFile(strFilePath);
 
 	if (oFile.open(QFile::ReadOnly | QIODevice::Text))
 	{
 		nSize = oFile.size();
 		oFile.close();
 	}
 #endif

#ifdef _PSX_QT_LINUX_
    struct sysinfo s_info;
    sysinfo(&s_info);
    uint32_t ufreeram;
    ufreeram = s_info.freeram;
    CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前系统剩余内存大小%lu B."), ufreeram);
     if (nSize * STT_IECCONFIG_FILE_SCALE >= ufreeram)
     {
         CString strTip = _T("提示");
         CString strText = _T("当前系统剩余内存不足");
         int result =  CXMessageBox::information(this,strTip,strText ,QMessageBox::Ok);
         if (result == QMessageBox::Ok)
         {
             return;
         }
     }
#endif

	CXSclFileObj *pXSclFileObj = (CXSclFileObj*)g_oXSclFileMngr.FindByID(strFilePath);

	if (pXSclFileObj != NULL)
	{
		if (pXSclFileObj->m_nUse == 0)
		{
			pXSclFileObj->m_nUse = 1;
			g_oXSclFileMngr.ValidSetSelectState(pXSclFileObj);
			m_pSttSelSclFileGrid->slot_UpdateSelectState();
			g_oXSclFileMngr.SaveSclFileMngrCfg();
		} 

		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_currentfile.GetString(),strFilePath.GetString());
//		m_pSttSelSclFileGrid->setBackgroundRole();
		return;
	}

	if (!AddScl_ReNameFile(strFilePath))//同名文件处理
	{
	pXSclFileObj = new CXSclFileObj;
	g_oXSclFileMngr.AddNewChild(pXSclFileObj);
	pXSclFileObj->m_nSize = nSize;
	pXSclFileObj->m_strName = GetFileNameFromFilePath(strFilePath);
	pXSclFileObj->m_strID = g_oXSclFileMngr.GenerateSclFileObjID();;
	pXSclFileObj->m_strSclPath = strFilePath;
	pXSclFileObj->m_nUse = 1;

//#ifdef _PSX_QT_LINUX_
	pXSclFileObj->m_strSsclPath = Global_ParseSclFileSaveSclCfgs(strFilePath,&m_oSclStation,this,pXSclFileObj->m_strID);
// #else
// 	pXSclFileObj->m_strSsclPath = Global_ParseSclFileSaveSclCfgs_EX(strFilePath,&m_oSclStation,this);
// #endif

	if (!IsFileExist(pXSclFileObj->m_strSsclPath))
	{
		g_oXSclFileMngr.Delete(pXSclFileObj);
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_parsefile.GetString(),
			pXSclFileObj->m_strSsclPath.GetString());
		return;
	}

	m_pSttSelSclFileGrid->InsertData(pXSclFileObj);

	if (!g_oXSclFileMngr.ValidSetSelectState(pXSclFileObj))
	{
		m_pSttSelSclFileGrid->slot_UpdateSelectState();
	} 

	m_pSttSelSclFileGrid->SelectRow(g_oXSclFileMngr.GetCount());
	EnableButtons();
	g_oXSclFileMngr.SaveSclFileMngrCfg();
}
}
bool QSttSelSclFileWidget::AddScl_ReNameFile(CString strFilePath)
{
	CString strCompareFileName;
	strCompareFileName = GetFileNameFromFilePath(strFilePath);

	//20240104 gongyiping 防止同名文件重复导入
	if (g_oXSclFileMngr.GetCount()>0)//首先判断文件数目大于0时进行检测同名文件
	{
		CXSclFileObj *pXSclFileObjNodes=NULL;
		CString strSclFileName;

		POS pos = g_oXSclFileMngr.GetHeadPosition();
		while(pos)
		{
			pXSclFileObjNodes =(CXSclFileObj*)g_oXSclFileMngr.GetNext(pos);
			strSclFileName=pXSclFileObjNodes->m_strName;
			if (strCompareFileName==strSclFileName)//新加入的文件的路径与存在的文件路径比较
			{
				CString strMsg;
				strMsg ="当前存在同名SCD文件，是否继续？"; 
				int result = CXMessageBox::information(this,g_sLangTxt_Message, strMsg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

				if (result  == QMessageBox::Yes)
				{	
					//删除旧的SCD文件
					CString strFolderPath;
					strFolderPath = GetPathFromFilePathName(pXSclFileObjNodes->m_strSsclPath);
					DeleteAllDirectorys(strFolderPath);
					m_pSttSelSclFileGrid->DeleteDataRow(pXSclFileObjNodes);

					return false;//添加新的SCD文件
				}
				else if (result == QMessageBox::No)//不添加新的SCD文件,保留原来的同名的SCD文件
				{
					return true;//同名文件已处理
				}		
			} 
		}
		//还有一种情况是未找到同名文件，直接添加新的SCD文件
		return false;
	}
	else
	{
		return false;//添加新的SCD文件
	}
}
void QSttSelSclFileWidget::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	m_pSttSelSclFileGrid->UpdateSelectState(nRow);
	EnableButtons();
}

void QSttSelSclFileWidget::EnableButtons()
{
	if (m_pSttSelSclFileGrid->GetCurrSelData())
	{
		m_pDelCurr_Btn->setEnabled(true);
		m_pSclIedSelect_Btn->setEnabled(true);
	}
	else
	{
		m_pDelCurr_Btn->setEnabled(false);
		m_pSclIedSelect_Btn->setEnabled(false);
	}

	if (g_oXSclFileMngr.GetCount()>0)
	{
		m_pClearAll_Btn->setEnabled(true);
	} 
	else
	{
		m_pClearAll_Btn->setEnabled(false);
	}
}

void QSttSelSclFileWidget::slot_DelCurr_Clicked()
{
	//m_pSttSelSclFileGrid->DelSelectData();

	CXSclFileObj *pXSclFileObj = (CXSclFileObj*)m_pSttSelSclFileGrid->GetCurrSelData();

	if (pXSclFileObj == NULL)
	{
		return;
	}

	CString strFolderPath;
	strFolderPath = GetPathFromFilePathName(pXSclFileObj->m_strSsclPath);
	DeleteAllDirectorys(strFolderPath);
	m_pSttSelSclFileGrid->DeleteDataRow(pXSclFileObj);
	g_oXSclFileMngr.SaveSclFileMngrCfg();
}

void QSttSelSclFileWidget::slot_ClearAll_Clicked()
{
//	CString strMsg;
//	strMsg = "请确认,是否清空全部SCL文件？";
//	xlang_GetLangStrByFile(g_sLangTxt_confirmfiles,"confirmfiles");
// 	int result = CXMessageBox::information(this,g_sLangTxt_Message,g_sLangTxt_confirmfiles  , QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

	//2024-5-22 wuxinyi 弹窗yes改成是
	CXMessageBox messageBox;
	messageBox.setWindowTitle(g_sLangTxt_Message);
	messageBox.setText(g_sLangTxt_confirmfiles);
	QPushButton *yesButton = messageBox.addButton(tr("是"), QMessageBox::YesRole);
	QPushButton *noButton = messageBox.addButton(tr("否"), QMessageBox::NoRole);
	messageBox.setDefaultButton(yesButton);
	messageBox.setIcon(QMessageBox::NoIcon); // 设置图标为空
	messageBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	int result = messageBox.exec();

	if (result == 1)
	{
		return;
	}

	g_oXSclFileMngr.ClearAll_WithFolderFiles();
	m_pSttSelSclFileGrid->ShowDatas(&g_oXSclFileMngr);
	g_oXSclFileMngr.SaveSclFileMngrCfg();
	EnableButtons();
}

void QSttSelSclFileWidget::slot_SclIedSelect_Clicked()
{
	QSttSelSclIedWidget oSttSelSclIedWidget(this);
	oSttSelSclIedWidget.InitUI();
	oSttSelSclIedWidget.InitDatas(&m_oSclStation);
	oSttSelSclIedWidget.exec();
}

UINT SttSclFIleSaveThread(LPVOID pPara)
{
	SttSCLFileSaveParas *pSttSCLFileSaveParas = (SttSCLFileSaveParas*)pPara;
	pSttSCLFileSaveParas->m_strResult = Global_SaveSclCfgs(pSttSCLFileSaveParas->m_strSclFilePath,
		pSttSCLFileSaveParas->m_pSclStation,
		pSttSCLFileSaveParas->m_strFileID,pSttSCLFileSaveParas->m_bIsTscd);
	pSttSCLFileSaveParas->m_bHasFinished = TRUE;
	return 0;
}

CString Global_ParseSclFileSaveSclCfgs(const CString &strSclFilePath,CSclStation *pSclStation,QWidget *pParent,const CString &strFileID)
{
// 	if (pSclStation->GetScdFile() == strSclFilePath) //如果是相同的scd文件不再重复解析
// 	{
// 		return Global_SaveSclCfgs(strSclFilePath, pSclStation);
// 	}

	long nPos = strSclFilePath.ReverseFind('.');
    BOOL bIsTscd;
	if (nPos<=0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前文件(%s)没有扩展名不是SCL文件."),strSclFilePath.GetString());
		return "";
	}

	pSclStation->DeleteAll();
	CScdFileRWDlg oScdFileRWDlg(pParent);
	CTickCount32 oWait; 
	CString strUIText; 
	strUIText = "SCL解析";
	oScdFileRWDlg.setWindowTitle(strUIText);
	strUIText = "正在加载SCL文件...";
	oScdFileRWDlg.setLabelText(strUIText);
	oScdFileRWDlg.show();
	oWait.DoEvents(100);

	CString strPostfix;
	strPostfix = strSclFilePath.Mid(nPos+1);
	strPostfix.MakeLower();
	if (strPostfix == _T("ccd"))
	{
		CcdFileRead oCcdFileRead;
		oCcdFileRead.SetProgressInterface(&oScdFileRWDlg);
		oCcdFileRead.ReadSclFile(strSclFilePath,pSclStation);

		while(oCcdFileRead.IsInReadState())	
		{
			oWait.DoEvents(100);
		}
		oWait.Enter();
		oCcdFileRead.FreeThreadAndDatas();
	}
	else
	{
	QSclFileRead  oSclFileRead;
        bIsTscd = oSclFileRead.IsTscdSclFile(strSclFilePath);
	oSclFileRead.SetProgressInterface(&oScdFileRWDlg);
	oSclFileRead.ReadSclFile(strSclFilePath,pSclStation);

	while(oSclFileRead.IsInReadState())	
	{
		oWait.DoEvents(100);
	}
	oWait.Enter();
	oSclFileRead.FreeThreadAndDatas();//zhouhj 2023.12.24 单独释放
	}	

//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("Time1(%ld)."),oWait.GetTickCountLong());
	
#ifdef _PSX_QT_LINUX_
	strUIText = "SCL解析";
	oScdFileRWDlg.setWindowTitle(strUIText);
	strUIText = "正在保存SCL配置...";
	oScdFileRWDlg.setValue(50);
	oScdFileRWDlg.setLabelText(strUIText);
	oScdFileRWDlg.show();
	SttSCLFileSaveParas oSttSCLFileSaveParas;
    oSttSCLFileSaveParas.InitParas(strSclFilePath, pSclStation,strFileID,bIsTscd);

	CWinThread *pThread = new CWinThread(SttSclFIleSaveThread, &oSttSCLFileSaveParas);
	pThread->m_bAutoDelete = FALSE;
	pThread->ResumeThread();

	while(!oSttSCLFileSaveParas.m_bHasFinished)	
	{
		oWait.DoEvents(100);
	}

	pThread->PostThreadMessage(WM_QUIT, 0, 0);
	pThread->wait();
	pThread = NULL;
	CString str = oSttSCLFileSaveParas.m_strResult;

	//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("Time2(%ld)."),oWait.GetTickCountLong());
	malloc_trim(0);//yzj 2024.1.2 确保linux系统下scd使用完成后释放的内存可以立即执行
#else
	CString str = Global_SaveSclCfgs(strSclFilePath, pSclStation,strFileID,bIsTscd);
#endif
	return str;
}

// #ifndef _PSX_QT_LINUX_
// CString Global_ParseSclFileSaveSclCfgs_EX(const CString &strSclFilePath,CSclStation *pSclStation,QWidget *pParent)
// {
// 	pSclStation->DeleteAll();
// 	CScdFileRWDlg oScdFileRWDlg(pParent);
// 	CSclFileRead  oSclFileRead;
// 	
// 	oSclFileRead.SetIedSaveDvm(FALSE);
// 	oSclFileRead.SetProgessInterface(&oScdFileRWDlg);
// 	oSclFileRead.ReadSclFile(strSclFilePath,NULL, pSclStation);
// 	CTickCount32 oWait;
// 
// 	while( oSclFileRead.IsInReadState() )
// 	{
// 		oWait.DoEvents(100);
// 	}
// 
// 	return Global_SaveSclCfgs(strSclFilePath, pSclStation);
// }
// #endif
// bool Global_GbkToUtf8(const CString &strGbk,CString &strUtf8)
// {
// 	unsigned char *pgbkString = NULL,*putf8String = NULL;
// 	CString strUtf8String;
// 	int nUtf8Lenth = 0;
// 	pgbkString = (unsigned char *)strGbk.GetString();
// 	gbk_to_utf8_r(pgbkString,strlen((char*)pgbkString),&putf8String,&nUtf8Lenth,0);
// 
// 	if (nUtf8Lenth<=0)
// 	{
// 		return false;
// 	} 
// 
// 	strUtf8 = (char *)putf8String;
// 	delete putf8String;
// 	return true;
// }

CString Global_SaveSclCfgs(const CString &strSclFilePath, CSclStation *pSclStation
						   ,const CString &strFileID,BOOL bIsTscd)
{
	CString strTscdPath,strFileName,strFileNameWithPostfix,strSsclPath;
	//	const char *pString = NULL;
	strTscdPath = _P_GetLibraryPath();
	strFileNameWithPostfix = GetPathFileNameFromFilePathName(strSclFilePath);
	strFileName = GetFileTitleFromFilePath(strFileNameWithPostfix);
	strTscdPath += _T("SCL/");
	
#ifdef _PSX_QT_LINUX_//在linux下防止存储文件时,文件名为中文,改用ID进行存储
	strTscdPath += strFileID;
 #else
 	strTscdPath += strFileName;
 #endif
	strTscdPath += _T("/");	

	CreateAllDirectories(strTscdPath);

#ifdef _PSX_QT_LINUX_//在linux下防止存储文件时,文件名为中文,改用ID进行存储
	strTscdPath += strFileID;
 #else
 	strTscdPath += strFileName;
 #endif

	strTscdPath += _T(".tscd");
	pSclStation->SaveXmlFile(strTscdPath,CCfgDataMngrXmlRWKeys::g_pXmlKeys);

	
	pSclStation->m_strTscdFile = strTscdPath;
	strSsclPath = ChangeFilePostfix(strTscdPath,_T("sscl"));
	pSclStation->SaveSsclFiles(strSsclPath);
	return strSsclPath;
}
