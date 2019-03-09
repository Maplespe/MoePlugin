using System;

namespace MoePluginTemplate //此类用于声明 不建议修改
{
    public interface IClass
    {
        string GetIndexes(int Index);
        string GetPluginName(int hwnd);
        string GetPluginInfo();
        string OpenSetMenu(int x, int y);
        string MoeCreateComplete();
        string MoeBoxEvent(int hwnd, int events);
    }
}
