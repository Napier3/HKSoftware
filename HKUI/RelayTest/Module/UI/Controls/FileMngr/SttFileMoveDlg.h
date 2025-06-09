#ifndef SttFileMoveDlg_H
#define SttFileMoveDlg_H

#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QFile>

#include "SttFileViewGrid.h"
#include "../../../../../Module/XfileMngrBase/XFileMngr.h"
#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../Module/CommonCtrl_QT/QSttProgDlg.h"
#include "../../../../../Module/DataMngr/DvmData.h"

class QSttFileMoveDlg : public QDialog ,public CExBaseListGridOptrInterface
{
	Q_OBJECT
public:
	QSttFileMoveDlg(QWidget *parent=NULL );
	~QSttFileMoveDlg();
	
	void InitUI();
	void initConnections();
	void SetCurrFileMnrTypeData(CDvmData* pObj);//获取当前选中的文件
	void SetFileMngrSuffix(const CString &strSuffixText,const CString &strFormatSuffixText);//设置后缀，进行过滤
	void EnableButtons();
	void SetItemIcon();
	BOOL IsUsbFolder(const CString &strPath);

public:
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);
//	virtual BOOL OnEditCellLBDblClk(QTableWidget *pGridCtrl, int nRow, int nCol, UINT nChar);

	QVBoxLayout *m_pMain_VLayout;
 	QPushButton *m_pImport_PushButton;
 	QPushButton *m_pExport_PushButton;
	QPushButton *m_pDelete_PushButton;
	QPushButton *m_pBack_PushButton;
	QHBoxLayout *m_pFileMngrSetHLayout;
	QPushButton *m_pXFolderBtn;

	CSttFileViewGrid *m_pFileMngrGrid;
	
	CXFileMngr m_oFileMngr;
	CExBaseObject *m_pCurrSelData;//表格当前选中数据
	CDvmData *m_pFileMngrTypeData;//文件管理对象类型数据(SCD\录波\报告\模板)

public:
	QSttProgDlg *m_pSttProgDlg;
//	CExBaseObject *m_pOpenCurrData;
	CString m_strMoveFilePath;
	QStringList m_astrFileTypesPostfix;//文件过滤时使用的几种数据类型,在打开对话框时,统一进行初始化
	QStringList m_astrFormatPostfix;//CDvmData中m_strFormat对应的几种扩展类型,主要用于录波文件,文件拷贝及删除时,统一处理
	void StartProgDlg(const CString &strTitle);
#ifdef _PSX_QT_LINUX_
	pthread_t m_pSttOpenFileThread;
	static void* SttOpenFileThread(LPVOID pParam);

	pthread_t m_pSttExportFileThread;
	static void* SttExportFileThread(LPVOID pParam);
#else
	HANDLE m_pSttOpenFileThread;
	static UINT SttOpenFileThread(LPVOID pParam);

	HANDLE m_pSttExportFileThread;
	static UINT SttExportFileThread(LPVOID pParam);
#endif

protected:
	//采用读取文件后写文件的方式,linux下直接拷贝的方式在文件名包含中文字符时有问题
	BOOL CopyFile_FileMngr(const CString &strSrcFilePath,const CString &strDestFilePath);
	BOOL ImprotFile_Thread();
	BOOL ExportFile_Thread();


signals:
	void sig_UpdateImprotFile(int bRet);
	void sig_UpdateExportFile(int bRet);

public slots:
	virtual void slot_ImportClicked();
	virtual void slot_ExportClicked();
	virtual void slot_DeleteClicked();
	virtual void slot_BackClicked();
	
	void slot_UpdateImprotFile(int bRet);
	void slot_UpdateExportFile(int bRet);
	
};

extern CFont *g_pSttGlobalFont;

#endif // SttFileMoveDlg_H
