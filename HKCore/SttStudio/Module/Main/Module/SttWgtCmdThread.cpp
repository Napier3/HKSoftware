#include "SttWgtCmdThread.h"
#include <QProcess>
#include "../../../../Module/API/FileApi.h"
#include "../../../../Module/API/GlobalConfigApi.h"

QSttWgtCmdThread::QSttWgtCmdThread()
{

}

QSttWgtCmdThread::~QSttWgtCmdThread()
{

}

//一体式：void QProcess::start(const QString & program, const QStringList & arguments, OpenMode mode = ReadWrite)
//外部程序启动后。将随主程序的退出而退出。
void QSttWgtCmdThread::start_exe(const CString &strExe, const CString &strArguments)
{
	QStringList strList;
	strList << strArguments;

	QProcess process;
	process.start(strExe, strList);
}

//分离式：void QProcess::startDetached(const QString & program, const QStringList & arguments, const QString & workingDirectory = QString(), qint64 * pid = 0)
//外部程序启动后，当主程序退出时并不退出。而是继续执行。
void QSttWgtCmdThread::startDetached_exe(const CString &strExe, const CString &strArguments)
{
	QStringList strList;
	strList << strArguments;

	QProcess process;
	bool bRet = process.startDetached(strExe, strList);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("调用程序(%s)失败(strArguments=%s).")
			,strExe.GetString(),strArguments.GetString());
	}
}

void QSttWgtCmdThread::run()
{
	QProcess process;
	QString strCmd = m_strPath;
	strCmd += m_strExe;

	if (!IsFileExist(strCmd))
	{
		CString strRootPah;
		strRootPah = _P_GetInstallPath();
		strCmd = strRootPah;
		strCmd += _T("Stt/Bin/");
		strCmd += m_strExe;

		if (!IsFileExist(strCmd))
		{
			strCmd = strRootPah;
			strCmd += _T("Test_Win/Bin/");
			strCmd += m_strExe;

			if (!IsFileExist(strCmd))
			{
				strCmd = strRootPah;
				strCmd += _T("SttStudio/Test_Win/Bin/");
				strCmd += m_strExe;
			}
		}
	}
#ifdef _PSX_OS_CENTOS_
    m_listCmd.prepend(strCmd);
    process.execute("sudo", m_listCmd);
#else
	process.execute(strCmd, m_listCmd);
#endif
}
