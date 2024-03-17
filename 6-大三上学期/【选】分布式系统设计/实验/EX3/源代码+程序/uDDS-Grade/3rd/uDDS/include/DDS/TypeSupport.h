/************************************************************
** 文件名：TypeSupport.h
** Copyright (c) 2011-2021 南京磐优信息科技有限公司
** 创建人：Nephalem<250610346@qq.com>
** 日  期：2011-01-15
** 修改人：无
** 日  期：无
** 描  述：TypeSupport头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_TYPESUPPORT_H_INCLUDED_
#define _DDS_TYPESUPPORT_H_INCLUDED_

//#include <string>
//class DomainParticipant;

class DDS_DLL TypeSupport 
{
public:
    TypeSupport() {};
    virtual ~TypeSupport () {};

    ////注册用户定义的数据类型
    //static ReturnCode_t Register_Type(DomainParticipant* pDomainParticipant, char* typeName);

    ////获取TypeSupport代表的数据类型名
    //static string Get_Type_Name();

};

#endif
