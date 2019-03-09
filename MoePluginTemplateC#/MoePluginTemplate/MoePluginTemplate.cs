using MoePluginTemplate;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

public class Moev //变量
{
    public static string datas;//存放数据
    public static string Indexes;//插件索引
    public static IntPtr MoeHwnd;//萌化箱句柄
    public static string Name;//插件名
}

namespace 插件模板 //注意 发布之前请更改此命名空间的名字！ 只需更改此空间即可 否则和别的插件一样就无法使用咯
{

    [ClassInterface(ClassInterfaceType.None)]
    public class Class : MoePluginTemplate.IClass
    {
        public string GetIndexes(int Index) { Moev.Indexes = Index.ToString(); return Moev.datas; }

        MoeAPI Moe = new MoeAPI();

        /// <summary>
        /// 萌化箱加载插件列表将会调用此项,也是插件初始化的地方，请尽快返回 否则影响萌化箱启动
        /// </summary>
        /// <param name="hwnd">萌化箱主窗口句柄</param>
        public string GetPluginName(int hwnd)
        {
            Moev.MoeHwnd = (IntPtr)hwnd;//萌化箱句柄
            //这里设置插件名
            Moev.Name = "C#测试插件模板";
            //这里加入初始化代码


            return Moev.Name;
        }

        /// <summary>
        /// 萌化箱插件列表被选中后会调用此项
        /// </summary>
        public string GetPluginInfo()
        {
            //这里是作者名
            string Names = "Maple";
            //这里是插件版本
            string Ver = "1.0";
            //插件描述信息 可以换行
            string Info = "萌化箱插件模板\r\n这是一个插件描述";
            //插件按钮 这里设置按钮的标题 设置为 "null" 则不显示按钮 按钮被按下会触发下面的OpenSetMenu事件
            string btn = "插件设置菜单";

            //请不要修改返回数据
            Moev.datas = "&1" + Names + "&2" + Ver + "&3" + Info + "&4" + btn + "&";
            return Moev.datas;
        }

        IntPtr[] test = new IntPtr[5];//用于储存测试界面的句柄 可以删除

        /// <summary>
        /// 萌化箱插件设置按钮被按下后会调用此项
        /// </summary>
        /// <param name="x">鼠标x坐标位置</param>
        /// <param name="y">鼠标y坐标位置</param>
        public string OpenSetMenu(int x, int y)
        {
            //加入代码

            //----测试代码 一个简单的界面 可以删除
            IntPtr main = Moe.MoeCreateWindow(IntPtr.Zero, 2, "测试窗口", 100, 100, 800, 500, true);
            test[0] = Moe.MoeCreateBox(MoeAPI.Moe_Box_Edit, main, "hello word", 1, 27 + 32, 392, 30, true, IntPtr.Zero);
            test[1] = Moe.MoeCreateBox(MoeAPI.Moe_Box_Lable, main, "请输入一段文字~", 0, 32, 100, 25, true, IntPtr.Zero);
            test[2] = Moe.MoeCreateBox(MoeAPI.Moe_Box_Button, main, "点我试试", 400, 27 + 32, 80, 30, true, IntPtr.Zero);
            test[3] = Moe.MoeCreateBox(MoeAPI.Moe_Box_Picture, main, Moe.MoeSetResource("MoePluginTemplate.IMG_2508.JPG"), 0, 60 + 32, 220, 300, true, IntPtr.Zero);
            test[4] = Moe.MoeCreateBox(MoeAPI.Moe_Box_Check, main, "这是选择框", 228, 60 + 32, 100, 30, true, IntPtr.Zero);
            //----测试代码结束

            return Moev.datas;
        }

        /// <summary>
        /// 使用MoeCreateWindow创建窗口完毕后会触发此事件
        /// </summary>
        public string MoeCreateComplete()
        {
            //加入代码

            return Moev.datas;
        }

        /// <summary>
        /// 使用MoeCreateBox创建组件之后的回调
        /// </summary>
        /// <param name="hwnd">触发事件的组件的句柄</param>
        /// <param name="events">事件ID (常量 Moe_Event_XXX)</param>
        public string MoeBoxEvent(int hwnd,int events)
        {
            //加入判断代码

            //---------------------------测试代码 可以删除
            /*测试代码 上面的测试代码创建了一个简单的界面 这里处理事件*/
            if ((IntPtr)hwnd == test[2] && events == MoeAPI.Moe_Event_LeftClick) {//按钮被按下
            Moe.MoeMessageBubble("你输入了：" + Moe.MoeGetBoxAttribute(MoeAPI.Moe_Box_Edit, MoeAPI.Moe_BoxType_Value, test[0]));
        }
	    if ((IntPtr)hwnd == test[4] && events == MoeAPI.Moe_Event_LeftClick) {//选择框被按下
            if (Moe.MoeGetBoxAttribute(MoeAPI.Moe_Box_Check, MoeAPI.Moe_BoxType_Check, test[4]) == "2")
            {
                    //选择框是选中状态
                    Moe.MoeSetBoxAttribute(MoeAPI.Moe_Box_Lable, MoeAPI.Moe_BoxType_Font, Moe.MoeSetFontResource("微软雅黑", 12, 2), test[1]);
                }
            else
            {
                    //选择框未选中
                    Moe.MoeSetBoxAttribute(MoeAPI.Moe_Box_Lable, MoeAPI.Moe_BoxType_Font, Moe.MoeSetFontResource("微软雅黑", 12, 1), test[1]);
                }
        }
            //---------------------------测试代码结束
            return Moev.datas;
        }
    }
}
