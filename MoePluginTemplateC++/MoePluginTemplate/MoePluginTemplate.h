// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MOEPLUGINTEMPLATE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MYDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef MOEPLUGINTEMPLATE_EXPORTS
#define MOEDLL_API __declspec(dllexport)
#else
#define MOEDLL_API __declspec(dllimport)
#endif

#include <string>

using std::string;

extern "C" MOEDLL_API const char* GetPluginName(HWND);

extern "C" MOEDLL_API const char* GetPluginInfo(void);

extern "C" MOEDLL_API const char* OpenSetMenu(int, int);

extern "C" MOEDLL_API const char* GetIndexes(int);

extern "C" MOEDLL_API const char* MoeCreateComplete(void);

extern "C" MOEDLL_API const char* MoeBoxEvent(HWND, int);