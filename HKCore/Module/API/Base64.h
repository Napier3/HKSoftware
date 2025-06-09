#ifndef BASE64_H
#define BASE64_H
#endif

//shaolei 20211007
const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="; 

/* Base64 ±àÂë */ 
char* base64_encode(const char* data, int data_len); 

/* Base64 ½âÂë */ 
char *base64_decode(const char* data, int data_len, int &ret_len); 
