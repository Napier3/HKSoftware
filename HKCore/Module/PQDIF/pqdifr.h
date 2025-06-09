
#ifndef _PQDIFR_H_
#define _PQDIFR_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


//  Definitions
// #define BOOL    short
// #define DWORD   unsigned long
// #define TRUE    1
// #define FALSE   0

#define PQDIF_min(a,b)  (((a) < (b)) ? (a) : (b))

//  Headers for this app
#include "pqdif_ph.h"
#include "pqdif_lg.h"
#include "pqdif_id.h"

//  Example "proprietary" structures
#define _PQDIF_R_
#include "pqdexamp.h"

//  Tag and ID names
#include "names.h"

//  Logical structure validation
#include "validate.h"

//  Reads into examples structures
#include "pqread.h"


#endif // _PQDIFR_H_