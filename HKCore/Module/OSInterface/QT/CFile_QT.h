#ifndef _CFile_QT_qt_h__
#define _CFile_QT_qt_h__

#include <qfile.h>

class CString;

class CFile : public QFile
{
public:
    // Flag values
        enum OpenFlags {
//             modeRead =         (int) 0x00000,
//             modeWrite =        (int) 0x00001,
//             modeReadWrite =    (int) 0x00002,
//             shareCompat =      (int) 0x00000,
//             shareExclusive =   (int) 0x00010,
//             shareDenyWrite =   (int) 0x00020,
//             shareDenyRead =    (int) 0x00030,
//             shareDenyNone =    (int) 0x00040,
//             modeNoInherit =    (int) 0x00080,
//             modeCreate =       (int) 0x01000,
//             modeNoTruncate =   (int) 0x02000,
//             typeText =         (int) 0x04000, // typeText and typeBinary are
//             typeBinary =       (int) 0x08000, // used in derived classes only
//             osNoBuffer =       (int) 0x10000,
//             osWriteThrough =   (int) 0x20000,
//             osRandomAccess =   (int) 0x40000,
//             osSequentialScan = (int) 0x80000,

			modeRead =         QIODevice::ReadOnly,
			modeWrite =        QIODevice::WriteOnly,
			modeReadWrite =    QIODevice::ReadWrite,
			shareCompat =      (int) 0x00000,
			shareExclusive =   (int) 0x00000,
			shareDenyWrite =   (int) 0x00000,
			shareDenyRead =    (int) 0x00000,
			shareDenyNone =    (int) 0x00000,
			modeNoInherit =    (int) 0x00000,
			modeCreate =       (int) 0x00000,
			modeNoTruncate =   QIODevice::Append,
			typeText =         QIODevice::Text, // typeText and typeBinary are
			typeBinary =       (int) 0x00000, // used in derived classes only
			osNoBuffer =       (int) 0x00020,
			osWriteThrough =   (int) 0x00000,
			osRandomAccess =   (int) 0x00000,
			osSequentialScan = (int) 0x00000,
			modeTruncate =		QIODevice::Truncate,
            };

        enum Attribute {
            normal =    0x00,
            readOnly =  0x01,
            hidden =    0x02,
            system =    0x04,
            volume =    0x08,
            directory = 0x10,
            archive =   0x20
            };

        enum SeekPosition { begin = 0x0, current = 0x1, end = 0x2 };
public:
    CFile()
    {

    }
    virtual ~CFile()
    {
    }

    virtual BOOL Open(const CString &strFileName, UINT nOpenFlags);
    virtual UINT Read(void* lpBuf, unsigned int nCount);
    virtual void Write(const void* lpBuf, unsigned int nCount);
    virtual void Close();
	virtual BOOL Flush();

    long SeekToEnd();
    void SeekToBegin();
    int GetLength();
    CString GetFileName();

// public:
//     CString m_strFileName;
};


bool CopyFileW(const CString &strExistingFileName,const CString &strNewFileName,BOOL bFailIfExists);
bool DeleteFileW(const CString &strFileName);
#ifdef _PSX_QT_LINUX_
#include <QTextCodec>

//在对文件进行读写操作时,根据文件路径设置本地编码(U盘目录下位gbk,机器内部位utf8),参数2获取设置前,编码方式
void InitLocalCodec_BeforeReadWrite(const CString &strPath,QTextCodec **ppOldTextCodec);
#endif

#endif   //_CFile_QT_qt_h__
