#ifndef SttIecRecordWriteFileWidget_H
#define SttIecRecordWriteFileWidget_H

#include <QDialog>
#include <QFont>
// #include <QTimer>
#include "../../UI/Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "SttIecRcdFuncInterface.h"
#include <QHBoxLayout>

/////////////////////////////////////控制块信息表////////////////////////////////////////////
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
	virtual void Show_61850Type(CExBaseObject *pStData, const int& nRow, const int& nCol, UINT nType);//类型
	virtual void Show_Fiber(CExBaseObject *pStData, const int& nRow, const int& nCol, UINT nFiberIndex);//光口
	void Show_FileSize(CExBaseObject *pStData, const int& nRow, const int& nCol);//文件大小
	void Show_TotalPackets(CExBaseObject *pStData, const int& nRow, const int& nCol, PSTT_AT02_PKT_HEAD_STC pHeadStc);//报文总数

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
	virtual void Config();//停止写文件

	BOOL HasSaveAsWriteFile();

	//2023/11/24 wangjunsheng 添加录波状态切换信号
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
//	QTimer m_oTimerRcdtimer;//更新录波时间定时器
//	long m_nRecordtime;//计入录波时间
	QHBoxLayout *m_mainLayout;
	CTickCount32 m_oWriteFileTickCount;

public slots:
//	void timerUpdate();//更新时间

signals:
//	void sig_SendFileSize(long nM, long nK);
//	void sig_SendRecordTime(int nTime);
	
};

extern CFont *g_pSttGlobalFont; 

#endif // SttIecRecordWriteFileWidget_H
