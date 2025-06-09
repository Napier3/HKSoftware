#include "sttdebuglogwidget.h"
#include "ui_sttdebuglogwidget.h"
#include "../../../Module/API/GlobalApi.h"

sttdebuglogwidget *g_pLogWidget = 0;

sttdebuglogwidget::sttdebuglogwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sttdebuglogwidget)
{
    ui->setupUi(this);
    CLogPrint::Create(this);
    CLogPrint::CreateLogFile();
    connect(this,SIGNAL(sig_LogString(QString)),this,SLOT(slot_LogString(QString)), Qt::QueuedConnection);

    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    g_pLogWidget = this;
}

sttdebuglogwidget::~sttdebuglogwidget()
{
    CLogPrint::SetLog(NULL);
    CLogPrint::Release();

    delete ui;
}

#include "../../../Module/API/GlobalConfigApi.h"
#include <QFile>
#include <QTextStream>
void sttdebuglogwidget::SaveLogFile()
{
    CString strFile;
    strFile = _P_GetBinPath();
   
	QDateTime tm = QDateTime::currentDateTime();
	QDate date = tm.date();
	QTime t = tm.time();

    if (m_strMacroID.GetLength() > 0)
    {
        strFile.AppendFormat("%d_%d_%d_%d_%d_%s.txt"
                             , date.month(), date.day(),t.hour() , t.minute(), t.second()
                             , m_strMacroID.GetString());
    }
    else
    {
        strFile.AppendFormat("%d_%d_%d_%d_%d.txt"
                             , date.month(), date.day(),t.hour() , t.minute(), t.second() );
    }

	QFile file(strFile);  

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {  
		return;  
	}  

	QTextStream out(&file);  
	out << ui->logEdit->toPlainText();  
	file.close();
}

void sttdebuglogwidget::LogString(long nLevel, const CString &strMsg)
{
    emit sig_LogString(strMsg);
}

void sttdebuglogwidget::LogString(long nLevel, const char *strMsg)
{
    emit sig_LogString(strMsg);
}

void sttdebuglogwidget::slot_LogString(QString strMsg)
{
    CString strTime;
   GetCurrSystemtimeString(strTime);
    ui->logEdit->append(strTime + ": " + strMsg);
}

