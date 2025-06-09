#ifndef CXMD5_H
#define CXMD5_H

#pragma  once
#include <string>
#include <fstream>

/* Type define */
typedef unsigned char byte;
typedef unsigned int uint32;

using std::string;
using std::ifstream;

/* CXMD5 declaration. */
//计算中文字符串的md5值时，需要将字符串以UTF-8格式传入
class CXMD5 {
public:
    CXMD5();
    CXMD5(const void* input, size_t length);
    CXMD5(const string& str);
    CXMD5(ifstream& in);
    void update(const void* input, size_t length);
    void update(const string& str);
    void update(ifstream& in);
    const byte* digest();
    string toString();
    void reset();

private:
    void update(const byte* input, size_t length);
    void final();
    void transform(const byte block[64]);
    void encode(const uint32* input, byte* output, size_t length);
    void decode(const byte* input, uint32* output, size_t length);
    string bytesToHexString(const byte* input, size_t length);

    /* class uncopyable */
    CXMD5(const CXMD5&);
    CXMD5& operator=(const CXMD5&);

private:
    uint32 _state[4];    /* state (ABCD) */
    uint32 _count[2];    /* number of bits, modulo 2^64 (low-order word first) */
    byte _buffer[64];    /* input buffer */
    byte _digest[16];    /* message digest */
    bool _finished;        /* calculate finished ? */

    static const byte PADDING[64];    /* padding for calculate */
    static const char HEX[16];
    enum { BUFFER_SIZE = 1024 };
};

#endif /*CXMD5_H*/