#ifndef _PdfFileToText_h__
#define _PdfFileToText_h__

#include <string>
#include "../MemBuffer/ExpandMemBuf.h"

bool PdfToTxt(const std::string &PdfFile,const std::string &TxtOutPath);
BOOL PdfToText(const std::string &PdfFile, CExpandMemBuf &oBuffer);

#endif
