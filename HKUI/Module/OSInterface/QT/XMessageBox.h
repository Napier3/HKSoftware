#ifndef CXMESSAGEBOX_H
#define CXMESSAGEBOX_H

#include <QMessageBox>

class CXMessageBox : public QMessageBox
{
public:
	static int information(QWidget *parent, const QString &title,
		const QString &text, StandardButtons buttons = Ok,
		StandardButton defaultButton = NoButton)
	{
#ifdef _PSX_IDE_QT_
            (void)defaultButton;
#endif

		QMessageBox messageBox(NoIcon, title, text, buttons, parent);
//		messageBox.setFixedWidth(80);
		messageBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
		return messageBox.exec();
	}
};

#endif//!CXMESSAGEBOX_H
