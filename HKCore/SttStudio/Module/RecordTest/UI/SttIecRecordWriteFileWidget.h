#ifndef SttIecRecordWriteFileWidget_H
#define SttIecRecordWriteFileWidget_H

#include <QDialog>
#include <QFont>
// #include <QTimer>
#include "../../UI/Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "SttIecRcdFuncInterface.h"
#include <QHBoxLayout>

/////////////////////////////////////���ƿ���Ϣ��////////////////////////////////////////////
class QSttIecRecordWriteFileGrid : public QExBaseListGridBase
{
	Q_OBJECT

public:
	QSttIecRecordWriteFileGrid(QWidget* parent = 0);
	virtual ~QSttIecRecordWriteFileGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public:
	virtual void Show_61850Type(CExBaseObject *pStData, const int& nRow, const int& nCol, UINT nType);//����
	virtual void Show_Fiber(CExBaseObject *pStData, const int& nRow, const int& nCol, UINT nFiberIndex);//���
	void Show_FileSize(CExBaseObject *pStData, const int& nRow, const int& nCol);//�ļ���С
	void Show_TotalPackets(CExBaseObject *pStData, const int& nRow, const int& nCol, PSTT_AT02_PKT_HEAD_STC pHeadStc);//��������

};

//////////////////////////////////////////////////////////////////////////
// namespace Ui {
// class QSttIecRecordWriteFileWidget;
// }

class QSttIecRecordWriteFileWidget : public QDialog, public CSttIecRcdFuncInterface
{

	Q_OBJECT

public://CSttIecRcdFuncInterface
	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Release();
	virtual BOOL NeedConfig(){return TRUE;}
	virtual void Config();//ֹͣд�ļ�

	BOOL HasSaveAsWriteFile();

	//2023/11/24 wangjunsheng ���¼��״̬�л��ź�
	BOOL m_bIsStartRecord;
	void StartRecord();

public:
    explicit QSttIecRecordWriteFileWidget(QWidget *parent = 0);
    virtual ~QSttIecRecordWriteFileWidget();

	void SetSelectedCbs(CExBaseList *pSelectedCbs);
	QSttIecRecordWriteFileGrid *m_pRecordWriteFileGrid;
//	CString m_strWriteFilePath;

private:
//    Ui::QSttIecRecordWriteFileWidget *ui;
//	QTimer m_oTimerRcdtimer;//����¼��ʱ�䶨ʱ��
//	long m_nRecordtime;//����¼��ʱ��
	QHBoxLayout *m_mainLayout;
	CTickCount32 m_oWriteFileTickCount;

public slots:
//	void timerUpdate();//����ʱ��

signals:
//	void sig_SendFileSize(long nM, long nK);
//	void sig_SendRecordTime(int nTime);
	
};

extern QFont *g_pSttGlobalFont; 

#endif // SttIecRecordWriteFileWidget_H
