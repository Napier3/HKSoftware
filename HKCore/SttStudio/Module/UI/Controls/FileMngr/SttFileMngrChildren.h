#ifndef SttFileMngrChildren_H
#define SttFileMngrChildren_H

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

class QSttFileMngrChildren : public QDialog,public CExBaseListGridOptrInterface
{
	Q_OBJECT
public:
	QSttFileMngrChildren(QWidget *parent=NULL );
	~QSttFileMngrChildren();
	
	void InitUI();
	void initConnections();
	BOOL SetCurrFileMnrTypeData(CDvmData* pObj);//��ȡ��ǰѡ�е��ļ�
	void GetFileChildrenItem();
	void ShowXFolder();
	void OnClickXFolderBtn(CXFolder *pFolder);
	void ExportFolder(CString strFilePath,CExBaseObject *pData);
	void SetFileMngrSuffix(CExBaseObject* pObj);//���ú�׺�����й���
	void EnableButtons();
	void SetItemIcon();
	BOOL IsUsbFolder(const CString &strPath);

public:
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);
	virtual BOOL OnEditCellLBDblClk(QTableWidget *pGridCtrl, int nRow, int nCol, UINT nChar);

public:

	QVBoxLayout *m_pMain_VLayout;
 	QPushButton *m_pImport_PushButton;
 	QPushButton *m_pExport_PushButton;
	QPushButton *m_pDelete_PushButton;
	QPushButton *m_pBack_PushButton;
	QHBoxLayout *m_pFileMngrSetHLayout;

	QHBoxLayout *m_pPathHLayout;
	QHBoxLayout *m_pBtnHLayout;
	QList<QPushButton *> m_pListPathBtn;
	QPushButton *m_pXFolderBtn;

	CSttFileViewGrid *m_pFileMngrGrid;
	
	CXFileMngr m_oFileMngr;
	CXFolder *m_pCurrFolder;
	CExBaseObject *m_pCurrSelData;//���ǰѡ������

	CDvmData *m_pFileMngrTypeData;//�ļ����������������(SCD\¼��\����\ģ��)

public:
	QSttProgDlg *m_pSttProgDlg;
//	CExBaseObject *m_pOpenCurrData;
	CString m_strMoveFilePath;
	CString m_strTemp;
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
	//���ö�ȡ�ļ���д�ļ��ķ�ʽ,linux��ֱ�ӿ����ķ�ʽ���ļ������������ַ�ʱ������
	BOOL CopyFile_FileMngr(const CString &strSrcFilePath,const CString &strDestFilePath);
	BOOL ImprotFile_Thread();
	BOOL ExportFile_Thread();


signals:
	void sig_ShowXFolder();
	void sig_UpdateImprotFile(int bRet);
	void sig_UpdateExportFile(int bRet);

public slots:
	virtual void slot_ImportClicked();
	virtual void slot_ExportClicked();
	virtual void slot_DeleteClicked();
	virtual void slot_BackClicked();
	
	void slot_ShowXFolder();
	void slot_UpdateImprotFile(int bRet);
	void slot_UpdateExportFile(int bRet);
	
};

extern QFont *g_pSttGlobalFont;

#endif // SttFileMngrChildren_H
