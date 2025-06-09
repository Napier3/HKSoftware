#pragma once
#include "Dict.h"
using std::string;

class CSegment
{
public:
	CSegment(void);
	~CSegment(void);

	void SegKeyAndFind (CDict&, string) const;
	void MMChSegment (CDict&, string) const;
	bool IsDigOrAlph(unsigned char ch) const;
	bool IsGBWord(unsigned char *strSource) const;
};

