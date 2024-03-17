/************************************************************
** 文件名：cdr.h
** Copyright (c) 2011-2021 南京磐优信息科技有限公司
** 创建人：Nephalem<250610346@qq.com>
** 日  期：2011-03-16
** 修改人：Nephalem
** 日  期：2012-07-02
** 描  述：cdr头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#define DEFAULT_CDRSIZE 50
#include <stddef.h>
#include "BasicTypes.h"
#include "DDS_DLL.h"
#ifndef _CDR_HH
#define _CDR_HH

#undef MY_BYTE_SEX

#undef WORDS_BIGENDIAN

#ifdef SOLARIS_SPARC
#define WORDS_BIGENDIAN
#endif

#if defined(WIN32) || defined(FREEBSD) || defined(SOLARIS)
#define WORDS_LITTLEENDIAN
#endif


#if defined (WORDS_BIGENDIAN)
#define MY_BYTE_SEX 0
#else
#define MY_BYTE_SEX 1
#endif


#if SIZEOF_VOID_P == SIZEOF_INT
typedef unsigned long ptr_arith_t;

#elif SIZEOF_VOID_P == SIZEOF_LONG
typedef unsigned long ptr_arith_t;

#elif SIZEOF_VOID_P == SIZEOF_LONG_LONG
typedef unsigned long long ptr_arith_t;

#else
#error "Can't find a suitable type for doing pointer arithmetic."
#endif

#if defined(ULINX_VXWORKS) || defined(_DDS_LIB_FILE)
class CDR
#else
class DDS_DLL CDR
#endif
{
public:
    //下个待拷贝字节流开始处指针
    unsigned char *pNext;
    //剩余空间长度
    size_t Remaining;

    //指向字节流的指针
    unsigned char *pReal_buffer;
    //是否要释放空间
    int iDo_free;

    //指向字节流的指针
    unsigned char *pBuffer;
    //为字节流申请空间的长度
    size_t Length;

    //交换字节
    int iDo_byteswap;

    //unsigned char _is_request;
    //unsigned char _orbus_used;

    //CORBA::ORB_ptr _orb;

public:
    //取指向Buffer的指针
    inline char* GetBufferPtr() 
	{
        return (char*)pBuffer;
    }

    //取Buffer的长度
    inline size_t GetBufferLen() 
	{
        return Length;
    }

    //取已存内容的长度
    inline size_t GetContentLen() 
	{
        return (pNext - pBuffer);
    }

    //设置存放内容的剩余空间长度
    inline void SetContentLen(size_t Len) 
	{
       Remaining = Len;
    }

    //
    inline void SetByteSwap(int iSwap) 
	{
        iDo_byteswap = iSwap;
    }

    //重设Buffer参数
    inline void ResetBuffer() 
	{
        pNext = pBuffer;
        Remaining = Length;
    }

    enum 
	{
        SHORT_SIZE = 2,
        LONG_SIZE = 4,
        LONGLONG_SIZE = 8,
        LONGDOUBLE_SIZE = 16,

        MAX_ALIGNMENT = 16,

        DEFAULT_BUFSIZE = 1430
    };


    //Boolean PutAny(Any a);
    //Boolean PutTypeCode(TypeCode tc);

    unsigned char PutByte(char c);
    unsigned char PutShort(short s);
    unsigned char PutLong(long l);

    unsigned char PutLongLong(const long long &ll);
    unsigned char PutLongDouble(const long double &ld);

    unsigned char PutByteStr(unsigned char* pBuf, unsigned short len);
    unsigned char PutString(const char* pBuf);
	//unsigned char PutTypeCode (TypeCode tc);    //Added by xusen.2012-7-2

    inline unsigned char PutChar(char c) 
	{
        return PutByte((char) c);
    }
    inline unsigned char PutWChar(wchar_t wc) 
	{
        return PutShort((short)wc);
    }

    inline unsigned char PutBoolean(unsigned char b) 
	{
        char ch = (b != false) ? 0x01010101 : 0;
        return PutByte(ch);
    }

    inline unsigned char PutOctet(unsigned char o) 
	{
        return PutByte((char) o);
    }
    inline unsigned char PutUShort(unsigned short s) 
	{
        return PutShort((short) s);
    }
    inline unsigned char PutULong(unsigned long l) 
	{
        return PutLong((long) l);
    }

    inline unsigned char PutULongLong(const unsigned long long &ll) 
	{
        return PutLongLong((long long &) ll);
    }

    inline unsigned char PutFloat(float f) 
	{
#if defined ULINX_LINUX
        return PutLong(*(int *)&f);
#else
        return PutLong(*(long *)&f);
#endif
    }
    inline unsigned char PutDouble(const double &d) 
	{
        return PutLongLong(*(long long *)&d);
    }


    //static TypeCode::traverse_status Encoder (_TYPE_CODE_PTR    tc,
    //                                          const void *pData,
    //                                          const void *,
    //                                          void *context,
    //                                          Environment &env);

    //unsigned char GetAny (Any &a);
    //unsigned char GetTypeCode (TypeCode &tc);
 
    unsigned char GetByte(char &c);
    unsigned char GetShort(short &s);
    unsigned char GetLong(long &l);

    unsigned char GetLongLong(long long &ll);
    unsigned char GetLongDouble(long double &ld);

    unsigned char GetByteStr(unsigned char* pBuf, unsigned short len);
    unsigned char GetString(char* &pBuf);
	//unsigned char GetTypeCode (TypeCode &tc);    //Added by xusen.2012-7-2

    //Object* UnMarshalObject(Environment &env = default_env());
    //TypeCode::traverse_status MarshalObject(Object*);

    inline unsigned char GetChar(char &o) 
	{
        return GetByte((char &) o);
    }
    inline unsigned char GetWChar(wchar_t &wc) 
	{
        short s;
        unsigned char retval = GetShort(s);
        wc = s;
        return retval;
    }

    inline unsigned char GetBoolean(unsigned char &b) 
	{
        char c;
        unsigned char retval = GetChar(c);
        b = (c == 1);
        return retval;
    }

    inline unsigned char GetOctet(unsigned char &o) 
	{
        return GetByte((char &) o);
    }
    inline unsigned char GetUShort(unsigned short &s) 
	{
        return GetShort((short&) s);
    }
    inline unsigned char GetULong(unsigned long &l) 
	{
        return GetLong((long &) l);
    }
    inline unsigned char GetULongLong(const unsigned long long &ull) 
	{
        return GetLongLong((long long &) ull); 
    }

    inline unsigned char GetFloat(float &f) 
	{
        return GetLong((long &) f);
    }
    inline unsigned char GetDouble(double &d) 
	{
        return GetLongLong((long long &) d);
    }

    //static TypeCode::traverse_status Decoder (_TYPE_CODE_PTR tc,
    //                                          const void *pData,
    //                                          const void *,
    //                                          void *context,
    //                                          Environment &env);

    CDR(
        //CORBA::ORB_ptr orb = 0,
        unsigned char *pBuf = 0,
        unsigned      len = 0,
        int           byte_order = MY_BYTE_SEX,
        int           consume_buf = 0
        //unsigned char          system_used = 0
        );

    ~CDR ();


	
    unsigned char SkipString();
    inline unsigned char SkipBytes(unsigned nbytes) 
	{
        if (Remaining < nbytes)
            return false;

        Remaining -= nbytes;
        pNext += nbytes;

        return true;
    }

	unsigned char Skip(short size);
	
    void SetupEncapsulation(unsigned char *pBuf, unsigned len);
    unsigned char Grow(size_t newlength);

    inline size_t BytesRemaining() 
	{
        return Remaining;
    }

};

#endif
