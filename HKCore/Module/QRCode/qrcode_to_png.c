
#include <stdlib.h>
#include "qrencode.h"
#include <string.h>
#include <stdio.h>
#include "..\PNG\png.h"
#include "getopt.h"

#include "qrcode_to_png.h"


#define INCHES_PER_METER (100.0/2.54)

static int casesensitive = 1;
static int eightbit = 0;
static int version = 0;
static int size = 3;
static int margin = -1;
static int dpi = 72;
static int structured = 0;
static int micro = 0;
static QRecLevel level = QR_ECLEVEL_L;
static QRencodeMode hint = QR_MODE_8;

static const struct option options[] = {
	{"help"         , no_argument      , NULL, 'h'},
	{"output"       , required_argument, NULL, 'o'},
	{"level"        , required_argument, NULL, 'l'},
	{"size"         , required_argument, NULL, 's'},
	{"symversion"   , required_argument, NULL, 'v'},
	{"margin"       , required_argument, NULL, 'm'},
	{"dpi"          , required_argument, NULL, 'd'},
	{"structured"   , no_argument      , NULL, 'S'},
	{"kanji"        , no_argument      , NULL, 'k'},
	{"casesensitive", no_argument      , NULL, 'c'},
	{"ignorecase"   , no_argument      , NULL, 'i'},
	{"8bit"         , no_argument      , NULL, '8'},
	{"micro"        , no_argument      , NULL, 'M'},
	{"version"      , no_argument      , NULL, 'V'},
	{NULL, 0, NULL, 0}
};

static char *optstring = "ho:l:s:v:m:d:Skci8MV";

static void usage(int help, int longopt)
{
	if(help) {
		if(longopt) {
			fprintf(stderr,
				"Usage: view_qrcode [OPTION]... [STRING]\n"
				"Encode input data in a QR Code and display.\n\n"
				"  -h, --help   display the help message. -h displays only the help of short\n"
				"               options.\n\n"
				"  -s NUMBER, --size=NUMBER\n"
				"               specify module size in dots (pixels). (default=3)\n\n"
				"  -l {LMQH}, --level={LMQH}\n"
				"               specify error correction level from L (lowest) to H (highest).\n"
				"               (default=L)\n\n"
				"  -v NUMBER, --symversion=NUMBER\n"
				"               specify the version of the symbol. (default=auto)\n\n"
				"  -m NUMBER, --margin=NUMBER\n"
				"               specify the width of the margins. (default=4)\n\n"
				"  -S, --structured\n"
				"               make structured symbols. Version must be specified.\n\n"
				"  -k, --kanji  assume that the input text contains kanji (shift-jis).\n\n"
				"  -c, --casesensitive\n"
				"               encode lower-case alphabet characters in 8-bit mode. (default)\n\n"
				"  -i, --ignorecase\n"
				"               ignore case distinctions and use only upper-case characters.\n\n"
				"  -8, --8bit   encode entire data in 8-bit mode. -k, -c and -i will be ignored.\n\n"
				"  -M, --micro  encode in a Micro QR Code. (experimental)\n\n"
				"  -V, --version\n"
				"               display the version number and copyrights of the qrencode.\n\n"
				"  [STRING]     input data. If it is not specified, data will be taken from\n"
				"               standard input.\n"
				);
		} else {
			fprintf(stderr,
				"Usage: view_qrcode [OPTION]... [STRING]\n"
				"Encode input data in a QR Code and display.\n\n"
				"  -h           display this message.\n"
				"  --help       display the usage of long options.\n"
				"  -s NUMBER    specify module size in dots (pixels). (default=3)\n"
				"  -l {LMQH}    specify error correction level from L (lowest) to H (highest).\n"
				"               (default=L)\n"
				"  -v NUMBER    specify the version of the symbol. (default=auto)\n"
				"  -m NUMBER    specify the width of the margins. (default=4)\n"
				"  -S           make structured symbols. Version must be specified.\n"
				"  -k           assume that the input text contains kanji (shift-jis).\n"
				"  -c           encode lower-case alphabet characters in 8-bit mode. (default)\n"
				"  -i           ignore case distinctions and use only upper-case characters.\n"
				"  -8           encode entire data in 8-bit mode. -k, -c and -i will be ignored.\n"
				"  -M           encode in a Micro QR Code.\n"
				"  -V           display the version number and copyrights of the qrencode.\n"
				"  [STRING]     input data. If it is not specified, data will be taken from\n"
				"               standard input.\n"
				);
		}
	}
}

#define MAX_DATA_SIZE (7090 * 16) /* from the specification */
static unsigned char *readStdin(int *length)
{
	unsigned char *buffer;
	int ret;

	buffer = (unsigned char *)malloc(MAX_DATA_SIZE + 1);
	if(buffer == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	ret = fread(buffer, 1, MAX_DATA_SIZE, stdin);
	if(ret == 0) {
		fprintf(stderr, "No input data.\n");
		exit(EXIT_FAILURE);
	}
	if(feof(stdin) == 0) {
		fprintf(stderr, "Input data is too large.\n");
		exit(EXIT_FAILURE);
	}

	buffer[ret] = '\0';
	*length = ret;

	return buffer;
}

static int writePNG(QRcode *qrcode, const char *outfile)
{
	static FILE *fp; // avoid clobbering by setjmp.
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned char *row, *p, *q;
	int x, y, xx, yy, bit;
	int realwidth;

	realwidth = (qrcode->width + margin * 2) * size;
	row = (unsigned char *)malloc((realwidth + 7) / 8);
	if(row == NULL) {
		fprintf(stderr, "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	if(outfile[0] == '-' && outfile[1] == '\0') {
		fp = stdout;
	} else {
		fp = fopen(outfile, "wb");
		if(fp == NULL) {
			fprintf(stderr, "Failed to create file: %s\n", outfile);
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);  //不行的
	if(png_ptr == NULL) {
		fprintf(stderr, "Failed to initialize PNG writer.\n");
		exit(EXIT_FAILURE);
	}

	info_ptr = png_create_info_struct(png_ptr);     //PNG的都不行
	if(info_ptr == NULL) {
		fprintf(stderr, "Failed to initialize PNG write.\n");
		exit(EXIT_FAILURE);
	}

	if(setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fprintf(stderr, "Failed to write PNG image.\n");
		exit(EXIT_FAILURE);
	}

	png_init_io(png_ptr, fp);
	png_set_IHDR(png_ptr, info_ptr,
		realwidth, realwidth,
		1,
		PNG_COLOR_TYPE_GRAY,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT);
	png_set_pHYs(png_ptr, info_ptr,
		dpi * INCHES_PER_METER,
		dpi * INCHES_PER_METER,
		PNG_RESOLUTION_METER);
	png_write_info(png_ptr, info_ptr);

	/* top margin */
	memset(row, 0xff, (realwidth + 7) / 8);
	for(y=0; y<margin * size; y++) {
		png_write_row(png_ptr, row);
	}

	/* data */
	p = qrcode->data;
	for(y=0; y<qrcode->width; y++) {
		bit = 7;
		memset(row, 0xff, (realwidth + 7) / 8);
		q = row;
		q += margin * size / 8;
		bit = 7 - (margin * size % 8);
		for(x=0; x<qrcode->width; x++) {
			for(xx=0; xx<size; xx++) {
				*q ^= (*p & 1) << bit;
				bit--;
				if(bit < 0) {
					q++;
					bit = 7;
				}
			}
			p++;
		}
		for(yy=0; yy<size; yy++) {
			png_write_row(png_ptr, row);
		}
	}
	/* bottom margin */
	memset(row, 0xff, (realwidth + 7) / 8);
	for(y=0; y<margin * size; y++) {
		png_write_row(png_ptr, row);
	}

	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr, &info_ptr);

	fclose(fp);
	free(row);

	return 0;
}

static QRcode *encode(const unsigned char *intext, int length)
{
	QRcode *code;

	if(micro) {
		if(eightbit) {
			code = QRcode_encodeDataMQR(length, intext, version, level);
		} else {
			code = QRcode_encodeStringMQR((char *)intext, version, level, hint, casesensitive);
		}
	} else {
		if(eightbit) {
			code = QRcode_encodeData(length, intext, version, level);
		} else {
			code = QRcode_encodeString((char *)intext, version, level, hint, casesensitive);
		}
	}

	return code;
}

static void qrencode(const unsigned char *intext, int length, const char *outfile)
{
	QRcode *qrcode;

	qrcode = encode(intext, length);
	if(qrcode == NULL) {
		perror("Failed to encode the input data");
		exit(EXIT_FAILURE);
	}
	writePNG(qrcode, outfile);
	QRcode_free(qrcode);
}

static QRcode_List *encodeStructured(const unsigned char *intext, int length)
{
	QRcode_List *list;

	if(eightbit) {
		list = QRcode_encodeDataStructured(length, intext, version, level);
	} else {
		list = QRcode_encodeStringStructured((char *)intext, version, level, hint, casesensitive);
	}

	return list;
}

static void qrencodeStructured(const unsigned char *intext, int length, const char *outfile)
{
	QRcode_List *qrlist, *p;
	char filename[FILENAME_MAX];
	char *base, *q, *suffix = NULL;
	int i = 1;

	base = strdup(outfile);
	if(base == NULL) {
		fprintf(stderr, "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}
	if(strlen(base) > 4) {
		q = base + strlen(base) - 4;
		if(stricmp(".png", q) == 0) {
			suffix = strdup(q);
			*q = '\0';
		}

	}

	qrlist = encodeStructured(intext, length);
	if(qrlist == NULL) {
		perror("Failed to encode the input data");
		exit(EXIT_FAILURE);
	}

	for(p = qrlist; p != NULL; p = p->next) {
		if(p->code == NULL) {
			fprintf(stderr, "Failed to encode the input data.\n");
			exit(EXIT_FAILURE);
		}
		if(suffix) {
			_snprintf_s(filename, FILENAME_MAX, "%s-%02d%s", base, i, suffix);
		} else {
			_snprintf_s(filename, FILENAME_MAX, "%s-%02d", base, i);
		}
		writePNG(p->code, filename);
		i++;
	}

	free(base);
	if(suffix) {
		free(suffix);
	}

	QRcode_List_free(qrlist);
}


int writeqrcodepngfile(const char* strText, const char *strPngFile)
{
	int length = 10;

	level = QR_ECLEVEL_M;
	margin = 4;
	version = 1;

	length = strlen(strText);

	qrencode(strText, length, strPngFile);
	
	return 0;
}

