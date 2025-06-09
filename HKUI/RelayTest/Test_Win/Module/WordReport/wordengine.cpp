#include "wordengine.h"

#ifdef _DEBUG
#pragma comment(lib,"QAxContainerd.lib" ) 
#else
#pragma comment(lib,"QAxContainer.lib")
#endif

WordEngine::WordEngine(QObject *parent)
	: QObject(parent)
{
	m_bOpened = false;
	word = NULL;
	documents = NULL;
	document = NULL;
}

WordEngine::~WordEngine()
{

}

bool WordEngine::openword(QString templatePath,bool bVisable)
{
	word=new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
	bool bFlag = word->setControl( "word.Application" );    
	if(!bFlag)    
	{        
		// 用wps打开        
		bFlag = word->setControl( "kwps.Application" );        
		if(!bFlag)        
		{           
			return false;       
		}    
	}    
	word->setProperty("Visible", bVisable);    

	// 获取所有的工作文档
	documents = word->querySubObject("Documents");
	// 以文件template.doc为模版新建一个文档
	
	documents->dynamicCall("Add(QString)",templatePath);

	// 获取当前激活的文档
	document=word->querySubObject("ActiveDocument");

	m_bOpened = true;    
	return true;
}

bool WordEngine::close()
{
	if (m_bOpened)    
	{        
		if(documents)           
			documents->dynamicCall("Close (bool)", true);
		//关闭文本窗口        
		if(word)            
			word->dynamicCall("Quit()");
		//退出word        
		if(documents)            
			delete documents;        
		if(document)            
			delete document;        
		m_bOpened = false;    
	}     
	return m_bOpened;
}

void WordEngine::inserText(QString text)
{
    QAxObject* selection  = word->querySubObject("Selection");
    if(NULL== selection)
    {
        return;
    }
    selection->dynamicCall("TypeText(const QString&)",text);
	inserEnter();
}

void WordEngine::setFontSize(int fontsize)
{
    QAxObject* selection = word->querySubObject("Selection");
    if(NULL== selection)
    {
        return;
    }
    selection->querySubObject("Font")->setProperty("Size",fontsize);
}

void WordEngine::setFontBold(bool flag)
{
    QAxObject* selection = word->querySubObject("Selection");
    if(NULL== selection)
    {
        return;
    }
    selection->querySubObject("Font")->setProperty("Bold",flag);
}

void WordEngine::setParagraphAlignment(int flag)
{
    QAxObject* selection = word->querySubObject("Selection");
    if(NULL== selection)
    {
        return;
    }
    if(flag == 0)
    {
        selection->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphCenter");
    }else if(flag == 1)
    {
        selection->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphJustify");
    }else if(flag == 2)
    {
        selection->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphRight");
    }
}

void WordEngine::inserEnter()
{
    QAxObject* selection  = word->querySubObject("Selection");
    if(!selection)
    {
        return;
    }
    selection->dynamicCall("TypeParagraph(void)");
}

void WordEngine::inserTitle(QString text)
{
    setFontSize(25);
    setFontBold(true);
    setParagraphAlignment(0);
    inserText(text);
	setFontSize(10);
	setFontBold(false);
	inserEnter();
}

void WordEngine::inserHeading1(QString text)
{
    setFontSize(14);
    setFontBold(true);
    setParagraphAlignment(1);
    inserText(text);
	setFontSize(10);
	setFontBold(false);
	inserEnter();
}

void WordEngine::inserHeading2(QString text)
{
	setFontSize(12);
	setFontBold(true);
	setParagraphAlignment(1);
	inserText(text);
	setFontSize(10);
	setFontBold(false);
	inserEnter();
}

void WordEngine::insertPic(QString picPath)
{
    QAxObject* selection  = word->querySubObject("Selection");
    if(NULL== selection)
    {
        return;
    }
    QAxObject *Inlineshapes = selection->querySubObject("InlineShapes");
    Inlineshapes->dynamicCall("AddPicture(const QString&)",picPath);
    delete Inlineshapes;
	inserEnter();
}

QAxObject* WordEngine::insertTable(int row,int column,bool gridflag,int flag)
{
    QAxObject* selection  = word->querySubObject("Selection");
    if(NULL== selection)
    {
        return NULL;
    }
    selection->dynamicCall("InsertAfter(QString&)", "\r\n");
    QAxObject *range = selection->querySubObject("Range");
	if (NULL == range)
	{
		return NULL;
	}
    QAxObject *tables = document->querySubObject("Tables");
	if(NULL== tables)
	{
		return NULL;
	}
    QAxObject *table = tables->querySubObject("Add(QVariant,int,int)",range->asVariant(),row,column);
	if(NULL== table)
	{
		return NULL;
	}
    //table->setProperty("Style",tr("网格型"));

    //表格自动拉伸列 0固定  1根据内容调整  2 根据窗口调整
	if (flag == 0)
	{
		table->dynamicCall("AutoFitBehavior(WdAutoFitBehavior)", 0);
	}
	else if (flag == 1)
	{
		table->dynamicCall("AutoFitBehavior(WdAutoFitBehavior)", 1);
	}
	else
	{
		table->dynamicCall("AutoFitBehavior(WdAutoFitBehavior)", 2);
	}
    
    if(gridflag)
    {
        for(int i=1;i<=6;i++)
        {
            QString str = QString("Borders(-%1)").arg(i);
            QAxObject *borders = table->querySubObject(str.toLocal8Bit().constData());
            borders->dynamicCall("SetLineStyle(int)",1);
        }
    }

    return table;
}

void WordEngine::setTableAlignment(QAxObject *table,int flag)
{
	if (!table)
	{
		return;
	}
	int rowcount = table->querySubObject("Rows")->dynamicCall("Count").toInt();
	for(int i=1;i<=rowcount;i++)
	{
		QAxObject* Row= table->querySubObject("Rows(int)",i);
		if(NULL== Row)
		{
			return;
		}
		QAxObject* range = Row->querySubObject("Range");
		if(NULL== range)
		{
			return;
		}
		Row->querySubObject("Alinment(int)",flag);
		if(flag == 0)
		{
			range->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphCenter");
		}
		else if(flag == 1)
		{
			range->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphJustify");
		}
		else if(flag == 2)
		{
			range->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphRight");
		}
		else if(flag ==3)
		{
			range->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphLeft");
		}
	}
}

void WordEngine::setTableRowAlignment(QAxObject *table, int row,int flag)
{
    if(!table)
    {
        return;
    }
    QAxObject* Row= table->querySubObject("Rows(int)",row);
    if(NULL== Row)
    {
        return;
    }
    QAxObject* range = Row->querySubObject("Range");
    if(NULL== range)
    {
        return;
    }
    Row->querySubObject("Alinment(int)",flag);
    if(flag == 0)
    {
        range->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphCenter");
    }else if(flag == 1)
    {
        range->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphJustify");
    }else if(flag == 2)
    {
        range->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphRight");
    }else if(flag ==3)
    {
        range->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphLeft");
    }
}

void WordEngine::setTableRowFontBold(QAxObject *table,int row,bool flag)
{
	if (!table)
	{
		return;
	}
	int columncount = table->querySubObject("Columns")->dynamicCall("Count").toInt();
	for (int i=1;i<=columncount;i++)
	{
		QAxObject *cell = table->querySubObject("Cell(int,int)",row,i);
		if(!cell)
			return ;
		cell->querySubObject("Range")->dynamicCall("SetBold(int)",flag);
	}
}

void WordEngine::SetTableCellString(QAxObject *table, int row,int column,QString text)
{
	if (!table)
	{
		return;
	}
	QAxObject *cell = table->querySubObject("Cell(int,int)",row,column);
	if(!cell)
		return ;
	cell->dynamicCall("Select(void)");
	cell->querySubObject("Range")->setProperty("Text", text);
}

void WordEngine::SetTableString(QAxObject *table,QList<QStringList> list)
{
	if (!table)
	{
		return;
	}
	int rowcount = table->querySubObject("Rows")->dynamicCall("Count").toInt();
	int columncount = table->querySubObject("Columns")->dynamicCall("Count").toInt();

	for (int i = 1;i<=rowcount;i++)
	{
		for (int j = 1;j<=columncount;j++)
		{
			QAxObject *cell = table->querySubObject("Cell(int,int)",i,j);
			if(!cell)
				return ;
			cell->dynamicCall("Select(void)");
			cell->querySubObject("Range")->setProperty("Text", list.at(i-1).at(j-1));
		}
	}
}

void WordEngine::setTableColumnWidth(QAxObject *table, int column,int width)
{
	if (!table)
	{
		return;
	}
	table->querySubObject("Columns(int)", column)->setProperty("Width", width);
}

void WordEngine::moveForEnd()
{
    QAxObject* selection = word->querySubObject("Selection");
    if(NULL== selection)
    {
        return;
    }
    QVariantList params;
    params.append(6);
    params.append(0);
    selection->dynamicCall("EndOf(QVariant&, QVariant&)", params).toInt();
}

void WordEngine::MergTableCell(QAxObject *table,int startRow,int endRow,int startColumn,int endColumn)
{
	if (!table)
	{
		return;
	}
	QAxObject* StartCell =table->querySubObject("Cell(int, int)",startRow,startColumn);
	QAxObject* EndCell = table->querySubObject("Cell(int, int)",endRow,endColumn);
	if(NULL==StartCell)
	{
		return;
	}
	if(NULL== EndCell)
	{
		return;
	}
	StartCell->querySubObject("Merge(QAxObject *)",EndCell->asVariant());
}
