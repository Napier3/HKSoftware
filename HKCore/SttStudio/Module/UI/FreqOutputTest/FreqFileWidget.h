#ifndef QFREQFILEWidget_H
#define QFREQFILEWidget_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include "../Controls/SttLineEdit.h"
#include <QDialog>
#include "../../SttTest/Common/Distribution/tmt_freqoutput_test.h"
#include "../Module/CommonCtrl_QT/QSttProgDlg.h"

class QDeleteRowDialog : public QDialog
{
	Q_OBJECT

public:
	QDeleteRowDialog(int nRow , QWidget* parent = NULL);
	~QDeleteRowDialog();

private:
	void InitUI();
	QSttLineEdit *m_pStartRowEdit;
	QSttLineEdit *m_pEndRowEdit;
	int m_nMaxRow;

signals:
	void sig_DelRow(int,int);

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
	void slot_StartRowEditFinished();
	void slot_EndRowEditFinished();

};

class QFreqFileWidget : public QWidget
{
	Q_OBJECT

public:
	QFreqFileWidget(QWidget *parent = 0);
	virtual ~QFreqFileWidget();

public:
	void InitUI();
	void InitTable();
	void InitConnect();
	void SetData(tmt_FreqOutputParas *pFreqOutputParas);
	void UpdateData(int nRow);//�������
	void StartProgDlg(const CString &strTitle);
	void ParseData(CString &strFilePath);
	void CalTableRow();
	void ShowData();

protected:
	bool m_bHasInitFinished;
	virtual void showEvent(QShowEvent *event);
	tmt_FreqOutputParas *m_pFreqOutputParas;

	QPushButton *m_pNewFileBtn;//�½��ļ�
	QPushButton *m_pImportFileBtn;//�����ļ�
	QPushButton *m_pSaveFileBtn;//�����ļ�
	QPushButton *m_pDeleteRowBtn;//ɾ����
	QTableWidget *m_pFreqFileTableWidget;//��ʾ���
	QSttLineEdit *m_pInfoLineEdit;
	QSttLineEdit *m_pTotalLineEdit;
	QSttProgDlg *m_pSttProgDlg;
	CString m_strFilePath;
	QStringList m_headerLabels;
	int m_nTabPageRowN; //������������ʾ����
	long m_nDataCount;//�����ʾ��������
	QScrollBar * m_pCurScrollBar;

#ifdef _PSX_QT_LINUX_
	pthread_t m_pSttExportFileThread;
	static void* SttExportFileThread(LPVOID pParam);
#else
	HANDLE m_pSttExportFileThread;
	static UINT SttExportFileThread(LPVOID pParam);
#endif

signals:
	void sig_ExportFile();

private slots:
	void slot_NewFileBtn_Clicked();
	void slot_ImportFileBtn_Clicked();
	void slot_SaveFileBtn_Clicked();
	void slot_DeleteRowBtn_Clicked();
	void slot_OnCellChanged(int row,int col);
	void slot_DelRow(int,int);
	void slot_UpdateTable();
	void slot_ExportFile();
	void getValue(int val);
	void slot_OnSelectionChanged();
};

#endif
