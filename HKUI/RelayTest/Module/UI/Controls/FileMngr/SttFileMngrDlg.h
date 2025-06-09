#ifndef SttFileMngrDlg_H
#define SttFileMngrDlg_H

#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QDialog>

#include "SttFileTypeMngrGrid.h"
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"

//#define USE_SttFileMngrChildren

class QSttFileMngrDlg : public QDialog,public CExBaseListGridOptrInterface
{
	Q_OBJECT
public:
	QSttFileMngrDlg(QWidget *parent= NULL);
	~QSttFileMngrDlg();

public:
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);
	virtual BOOL OnEditCellLBDblClk(QTableWidget *pGridCtrl, int nRow, int nCol, UINT nChar);

public:
	void InitUI();
	void OpenFileTypeMngr();//打开xml文件
	void GetDiskInfo(); //获取磁盘信息
	char* Global_GetByteValue(char *pzfString,double &dValue);
	void SetFileMngrFont();
//	BOOL IsFolderPath(const CString &strPath,CString &strFilePath);
	BOOL GetFolderSize(const CString &strPath,CString &strFolderSize);
	BOOL FileSizeTypeChanged(double nSize,CString &strSize);
	void SetFoderIecon();


public:
	QLabel *m_pUsed_Label;
	QLabel *m_pUsedText_Label;
	QLabel *m_pAvailable_Label;
	QLabel *m_pAvailaText_Label;
	QProgressBar *m_pMemory_PgBar;
	QHBoxLayout *m_pMenoryLayout;
	QPushButton *m_pCancel_PushButton;
	QHBoxLayout *m_pOpen_CancelHLayout;
	QVBoxLayout *m_pMain_VLayout;
	CFileTypeMngrGrid *m_pFodlerGrid;

	CDataGroup m_oDataGroup;

public slots:
	virtual void slot_CloseClicked();
	
};

extern CFont *g_pSttGlobalFont;

#endif // SttFileMngrDlg_H
