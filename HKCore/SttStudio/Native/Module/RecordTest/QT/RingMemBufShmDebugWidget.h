#ifndef RingMemBufShmDebugWIDGET_H
#define RingMemBufShmDebugWIDGET_H

#include <QDialog>
#include <QFont>
#include "../../../../Module/API/StringApi.h"

#define  MAX_CAP_SEND_BUFFER   102400

namespace Ui {
class QRingMemBufShmDebugWidget;
}

class QRingMemBufShmDebugWidget : public QDialog
{
    Q_OBJECT

public:
    explicit QRingMemBufShmDebugWidget(QWidget *parent = 0);
    virtual ~QRingMemBufShmDebugWidget();
	void InitLanguage();
	bool m_bOpenCapFile;
	CFile m_oCapFile;
	BYTE m_pBuffer[MAX_CAP_SEND_BUFFER+1024];
	BYTE m_pBufferHead[MAX_CAP_SEND_BUFFER+1024];
	BYTE m_pBufferHeadSend[MAX_CAP_SEND_BUFFER]; 
	long m_nSendLength;
	BYTE m_pBufferLeft[32];  //计算头，剩下的部分
	long m_nLeftBufferLen;

	long m_nSendBufSize;
	long m_nSendBufSizeTotal;

	QTimer m_oTimerWrite;
	long m_nAutoWritePkg;

	void GetSendLength();
	void DebugWriteRcvPkg(BYTE *pBuffer, long nLen);
	void DebugWriteRcvPkgHead(BYTE *pBuffer, long nLen);

	void SetRingMemBufShmFont();//2022-10-24 sy 设置字体

signals:

private slots:
    void on_m_Btn_WriteDetectPkg_clicked();
    void on_m_Btn_WriteRcvPkg_clicked();
    void on_m_btnAutoWrite_clicked();
	void slot_Timer_AutoWrite();

private:
    Ui::QRingMemBufShmDebugWidget *ui;
};

extern QFont *g_pSttGlobalFont;

#endif // RingMemBufShmDebugWIDGET_H
