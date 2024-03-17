#ifndef _DDS_DLL_FILE_H_
#define _DDS_DLL_FILE_H_

#if (defined( ULINX_WIN) ||  defined(_WIN32)) 
# pragma warning (disable:4819)

#ifdef _DDS_DLL_FILE
#define DDS_DLL _declspec(dllexport)
#else
#define DDS_DLL _declspec(dllimport)
#endif
#else
#define DDS_DLL
#endif

#endif