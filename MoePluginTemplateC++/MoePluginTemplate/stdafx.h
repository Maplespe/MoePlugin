// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
#include <windows.h>
#include <string>

// TODO:  在此处引用程序需要的其他头文件
#include "resource.h"
#include "MoeAPI.h"

extern HWND MoeHwnd; //萌化箱句柄
extern std::string datas; //用来装载文本消息
extern std::string Indexes;//插件索引值
extern HMODULE hModules;//当前模块句柄
extern MoeAPI Moe;//萌化箱接口类