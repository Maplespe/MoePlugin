// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>
#include <string>

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "resource.h"
#include "MoeAPI.h"

extern HWND MoeHwnd; //�Ȼ�����
extern std::string datas; //����װ���ı���Ϣ
extern std::string Indexes;//�������ֵ
extern HMODULE hModules;//��ǰģ����
extern MoeAPI Moe;//�Ȼ���ӿ���