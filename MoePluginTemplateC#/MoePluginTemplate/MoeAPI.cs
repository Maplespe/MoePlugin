using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using Microsoft.Win32;
using System.IO;
using System.Reflection;

namespace MoePluginTemplate
{
    /// <summary>
    /// 萌化箱接口类
    /// </summary>
    unsafe public class MoeAPI
    {
        //注册表常量
        public const long HKEY_CLASSES_ROOT                 =  2147483648;
        public const long HEKY_CURRENT_CONFIG               = -2147483643;
        public const long HEKY_CURRENT_USER                 = -2147483647;
        public const long HEKY_DYN_DATA                     = -2147483642;
        public const long HKEY_LOCAL_MACHINE                = -2147483646;
        public const long HKEY_PERFORMANCE_DATA             = -2147483644;
        public const long HKEY_USERS                        = -2147483645;
        //组件常量
        public const int Moe_Box_Button                     = 1011;//Moe_按钮
        public const int Moe_Box_Lable                      = 1012;//Moe_标签
        public const int Moe_Box_Picture                    = 1013;//Moe_图片框
        public const int Moe_Box_Edit                       = 1014;//Moe_编辑框
        public const int Moe_Box_Check                      = 1015;//Moe_选择框
        public const int Moe_Event_MouseMove                = 1;//鼠标移动
        public const int Moe_Event_MouseEnter               = 2;//鼠标进入
        public const int Moe_Event_MouseLeave               = 3;//鼠标离开
        public const int Moe_Event_LeftClick                = 4;//鼠标左键按下
        public const int Moe_Event_LeftUp                   = 5;//鼠标左键弹起
        public const int Moe_Event_LeftDobleClick           = 6;//鼠标左键双击
        public const int Moe_Event_RightClick               = 7;//鼠标右键按下
        public const int Moe_Event_RightUp                  = 8;//鼠标右键弹起
        public const int Moe_Event_RightDobleClick          = 9;//鼠标右键双击
        public const int Moe_Event_Rolling                  = 10;//鼠标滚轮滚动
        public const int Moe_Event_Input                    = 11;//字符输入
        public const int Moe_Event_Edit                     = 12;//编辑框内容被改变
        public const int Moe_Event_FocusChange              = 13;//组件焦点改变
        public const int Moe_Event_Close                    = 14;//窗口即将被销毁
        public const int Moe_Event_Move                     = 15;//窗口位置被移动
        public const int Moe_Event_Position                 = 16;//窗口尺寸被改变
        public const int Moe_BoxType_Left                   = 1101;//组件左边位置 (返回值转int)
        public const int Moe_BoxType_Top                    = 1102;//组件顶边位置 (返回值转int)
        public const int Moe_BoxType_Width                  = 1103;//组件宽度 (返回值转int)
        public const int Moe_BoxType_Height                 = 1104;//组件高度 (返回值转int)
        public const int Moe_BoxType_Value                  = 1105;//组件标题或编辑框内容 (返回值string无需修改)
        public const int Moe_BoxType_Visble                 = 1106;//组件可视状态 (返回值转int 1=可视2=不可视)
        public const int Moe_BoxType_InputMode              = 1107;//编辑框输入状态 输入方式 (0=普通状态1=禁止输入2=密码输入)
        public const int Moe_BoxType_PasswordStr            = 1108;//编辑框用于遮掩密码的字符 (仅对编辑框输入状态=2才有效 默认 *)
        public const int Moe_BoxType_MultiLine              = 1109;//编辑框是否多行 (1=多行2=单行 默认多行)
        public const int Moe_BoxType_Check                  = 1110;//选择框是否选中 (1=选中2=非选中)
        public const int Moe_BoxType_Image                  = 1111;//图片框的图片 请使用MoeSetRes来设置资源 (注 此为只写 无法用于获取)
        public const int Moe_BoxType_WindowBackGround       = 1112;//窗口的底图 请使用MoeSetRes来设置资源 (注 此为只写 无法用于获取)
        public const int Moe_BoxType_Font                   = 1113;//组件的字体 (注 此为只写 无法用于获取)
        public const int Moe_BoxType_PicStyle               = 1114;//图片框样式 (1=带背景边框2=不带背景边框 默认 带背景边框)
        public const int Moe_BoxType_BarMAX                 = 1115;//进度条最大位置 (返回值转int)

        //------------------------------------------------------//
        [DllImport("user32.dll", EntryPoint = "SendMessageA")]
        public static extern int SendMessage(IntPtr hwnd, int wMsg, IntPtr wParam, IntPtr lParam);


        //如果你需要取编辑框的返回值 且文本很长很长 请调整这里的字节长度 默认1024字节
        unsafe static char* State = (char*)Marshal.AllocHGlobal(1024);
        static string msgA;

        /// <summary>
        /// 等待萌化箱返回值
        /// </summary>
        string SetState()
        {
            while (Marshal.PtrToStringAnsi((IntPtr)State) == "-1")
            {
                System.Threading.Thread.Sleep(100);
            }
            string num = Marshal.PtrToStringAnsi((IntPtr)State);

            //MessageBox.Show(Marshal.PtrToStringAnsi((IntPtr)State),"返回值",MessageBoxButtons.OK,MessageBoxIcon.Asterisk);

            //发送消息给萌化箱要求初始化返回值为-1
            msgA = "type:return&ptr:" + ((int)State).ToString() + "&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return num;
        }

        /// <summary>
        /// Moe信息框-萌化箱信息框
        /// <para>返回值 int 1=确定 2=取消</para>
        /// </summary>
        /// <param name="title">信息框的标题</param>
        /// <param name="msg">信息框提示内容 (不能超过120个中文字符)</param>
        /// <param name="btn">信息框按钮类型 (1为是否钮 2为确认取消钮 3为只有确认按钮)</param>
        /// <param name="icon">信息框显示的图标 (1为信息图标 2为错误图标)</param>
        public int MoeMessageBox(string title, string msg, int btn, int icon)
        {
            msgA = "type:msgbox&msg:" + msg + "&title:" + title + "&btn:" + btn.ToString() + "&icon:" + icon.ToString() + "&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return int.Parse(SetState());
        }

        /// <summary>
        /// 切换主题
        /// <para>返回值 int 固定为 1 该函数直到主题应用完成才会返回.</para>
        /// </summary>
        /// <param name="Path">主题文件(.theme)的绝对路径</param>
        public int MoeChangeTheme(string Path)
        {
            msgA = "type:changetheme&path:" + Path + "&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return int.Parse(SetState());
        }

        /// <summary>
        /// 写入注册表值 字符串型 C#建议使用(Registry类)
        /// </summary>
        /// <param name="Key">键根目录 (常量 HKEY_XXX)</param>
        /// <param name="Path"></param>
        /// <param name="KeyName"></param>
        /// <param name="Value"></param>
        /// <param name="Type"></param>
        /// <param name="Create"></param>
        public int MoeRegisterString(long Key, string Path, string KeyName, string Value, int Type, int Create)
        {
            msgA = "type;regstr&key:" + Key.ToString() + "&path:" + Path + "&keyname:" + KeyName + "&value:" + Value + "&type:" + Type.ToString() + "&create:" + Create.ToString() + "&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return int.Parse(SetState());
        }

        /// <summary>
        /// 写入注册表值 整数型 C#建议使用(Registry类)
        /// </summary>
        /// <param name="Key">键根目录 (常量 HKEY_XXX)</param>
        /// <param name="Path"></param>
        /// <param name="KeyName"></param>
        /// <param name="Value"></param>
        /// <param name="Type"></param>
        /// <param name="Create"></param>
        public int MoeRegisterInt(long Key, string Path, string KeyName, int Value, int Type, int Create)
        {
            msgA = "type;regint&key:" + Key.ToString() + "&path:" + Path + "&keyname:" + KeyName + "&value:" + Value.ToString() + "&type:" + Type.ToString() + "&create:" + Create.ToString() + "&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return int.Parse(SetState());
        }

        /// <summary>
        /// 设置AeroGlass状态
        /// <para>注：只有安装AeroGlass此项才会有效</para>
        /// </summary>
        /// <param name="state">状态("start"-开启,"reload"-重启,"close"-关闭)</param>
        public int MoeSetAeroGlass(string state)
        {
            msgA = "type:setaero&state:" + state + "&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return int.Parse(SetState());
        }

        /// <summary>
        /// 设置AeroGlass状态
        /// <para>返回值 int 1=未安装 2=已安装</para>
        /// </summary>
        public int MoeGetAGState()
        {
            msgA = "type:getaero&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return int.Parse(SetState());
        }

        /// <summary>
        /// 添加调试输出
        /// <para>写入一条消息到萌化箱调试窗口 仅萌化箱开启调试状态有效</para>
        /// </summary>
        /// <param name="text">要输出的内容</param>
        public int MoeCout(string text)
        {
            msgA = "type:cout&msg:" + text + "&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return int.Parse(SetState());
        }

        /// <summary>
        /// 创建一个窗口
        /// <para>注：窗口创建完毕将会调用函数MoeCreatesComplete 且同名窗口不会创建</para>
        /// <para>返回值 IntPtr - 返回创建的窗口句柄</para>
        /// </summary>
        /// <param name="Parent">父窗口句柄(为IntPtr.Zero则不置父)</param>
        /// <param name="Style">窗口风格(1=蓝色边线窗口(纯色)2=萌化箱图片风格窗口(图片))</param>
        /// <param name="Title">窗口标题</param>
        /// <param name="Left">窗口左边位置</param>
        /// <param name="Top">窗口顶边位置</param>
        /// <param name="width">窗口宽度</param>
        /// <param name="height">窗口高度</param>
        /// <param name="MaxBtn">是否启用最大化按钮</param>
        public IntPtr MoeCreateWindow(IntPtr Parent, int Style, string Title, int Left, int Top, int width, int height, bool MaxBtn)
        {
            string max = "1";
            if (MaxBtn) { max = "2"; }
            msgA = "indexes:" + Moev.Indexes + "&type:createwindows&parent:" + ((int)Parent).ToString() + "&style:" + Style.ToString() + "&title:" + Title
                + "&left:" + Left.ToString() + "&top:" + Top.ToString() + "&width:" + width.ToString() + "&height:" + height.ToString()
                + "&maxbtn:" + max + "&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return (IntPtr)int.Parse(SetState());
        }

        /// <summary>
        /// 创建一个指定组件
        /// </summary>
        /// <param name="Type">组件类型(常量 Mox_XXX_Box)</param>
        /// <param name="Parent">父窗口句柄(用MoeCreateWindow创建得到的句柄 或用本命令创建组件得到的句柄)</param>
        /// <param name="Title">组件的标题或内容或图片</param>
        /// <param name="Left">组件左边位置</param>
        /// <param name="Top">组件左边位置</param>
        /// <param name="Width">组件宽度</param>
        /// <param name="Height">组件高度</param>
        /// <param name="Visble">是否可见</param>
        /// <param name="Relation">关联组件的句柄 不关联填写IntPtr.Zero</param>
        public IntPtr MoeCreateBox(int Type, IntPtr Parent, string Title, int Left, int Top, int Width, int Height, bool Visble, IntPtr Relation)
        {
            string vsb = "1";
            if (Visble) { vsb = "2"; }
            msgA = "indexes:" + Moev.Indexes + "&type:createbox&types:" + Type.ToString() + "&parent:" + ((int)Parent).ToString() + "&title:" + Title
                + "&left:" + Left.ToString() + "&top:" + Top.ToString() + "&width:" + Width.ToString() + "&height:" + Height.ToString()
                + "&visble:" + vsb + "&relation:" + ((int)Relation).ToString() + "&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return (IntPtr)int.Parse(SetState());
        }

        /// <summary>
        /// 置组件属性
        /// </summary>
        /// <param name="Type">组件类型(常量 Mox_Box_XXX 窗口请填1)</param>
        /// <param name="SetType">要设置的属性类型(常量 Moe_BoxType_XXX)</param>
        /// <param name="Value">要设置的值</param>
        /// <param name="hwnd">组件句柄</param>
        public int MoeSetBoxAttribute(int Type, int SetType, string Value, IntPtr hwnd)
        {
            msgA = "indexes:" + Moev.Indexes + "&type:setbox&types:" + Type.ToString() + "&settype:" + SetType.ToString() + "&value:" + Value + "&hwnd:" + ((int)hwnd).ToString() + "&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return int.Parse(SetState());
        }

        /// <summary>
        /// 取组件属性
        /// <para> 返回值 string - 返回的值 请参考常量的注释进行适当转换</para>
        /// </summary>
        /// <param name="Type">组件类型(常量 Mox_Box_XXX 窗口请填1)</param>
        /// <param name="GetType">要取的属性类型(常量 Moe_BoxType_XXX)</param>
        /// <param name="hwnd">组件句柄</param>
        public string MoeGetBoxAttribute(int Type, int GetType, IntPtr hwnd)
        {
            msgA = "indexes:" + Moev.Indexes + "&type:getbox&types:" + Type.ToString() + "&gettype:" + GetType.ToString() + "&hwnd:" + ((int)hwnd).ToString() + "&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return SetState();
        }

        /// <summary>
        /// 置嵌入资源
        /// <para> 返回值 - string (直接使用MoeSetBoxAttribute设置图片即可 也可用于萌化箱其他接口数据提供)</para>
        /// </summary>
        /// <param name="ResourceName">要转换的资源"项目名称.文件名称" 注意文件属性设置为嵌入的资源</param>
        public string MoeSetResource(string ResourceName)
        {
            Stream stream = Assembly.GetExecutingAssembly().GetManifestResourceStream(ResourceName);
            byte[] buffer = new byte[stream.Length];
            stream.Read(buffer, 0, (int)stream.Length);
            stream.Close();
            return "pres:" + Convert.ToBase64String(buffer) + "#psize:base64#";
        }

        /// <summary>
        /// 弹出信息气泡
        /// </summary>
        /// <param name="Msg">要弹出的信息内容 可以换行 如不换行会自动换行</param>
        public int MoeMessageBubble(string Msg)
        {
            msgA = "&type:msgbubble&msg:" + Msg + "&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return int.Parse(SetState());
        }

        /// <summary>
        /// 播放声音 (只支持WAV和MID格式)
        /// </summary>
        /// <param name="Resource">声音资源 请使用MoeSetResource来转换</param>
        /// <param name="Loop">是否循环播放</param>
        public int MoePlaySound(string Resource, bool Loop)
        {
            string lp = "1";
            if (Loop) { lp = "2"; }
            msgA = "&type:playsound&res:" + Resource + "&loop:" + lp + "&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return int.Parse(SetState());
        }

        /// <summary>
        /// 停止播放声音
        /// <para>停止用MoePlaySound播放的声音</para>
        /// </summary>
        public int MoeStopSound()
        {
            msgA = "&type:stopsound&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return int.Parse(SetState());
        }

        /// <summary>
        /// 设置组件层级
        /// <para>注：设置MoeCreateBox创建组件的层级</para>
        /// </summary>
        /// <param name="hwnd">组件句柄</param>
        /// <param name="Level">层级 (可以负数)</param>
        public int MoeSetBoxLevel(IntPtr hwnd, int Level)
        {
            msgA = "&type:setboxlevel&hwnd:" + ((int)hwnd).ToString() + "&level:" + Level.ToString() + "&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return int.Parse(SetState());
        }

        /// <summary>
        /// 取组件层级
        /// <para>返回值 int 返回组件层级</para>
        /// </summary>
        /// <param name="Hwnd">组件句柄</param>
        public int MoeGetBoxLevel(IntPtr Hwnd)
        {
            msgA = "&type:getboxlevel&hwnd:" + ((int)Hwnd).ToString() + "&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return int.Parse(SetState());
        }

        /// <summary>
        /// 设置字体资源
        /// <para>返回值 - string (用法与MoeSetResource相同)</para>
        /// </summary>
        /// <param name="FontName">字体名称</param>
        /// <param name="FontSize">字体大小</param>
        /// <param name="FontEffect">字体效果(1=普通字2=发光字)</param>
        public string MoeSetFontResource(string FontName, int FontSize, int FontEffect)
        {
            return "moeset:font#fname:" + FontName + "#fsize:" + FontSize.ToString() + "#feffect:" + FontEffect.ToString() + "#";
        }

        /// <summary>
        /// 销毁指定组件或窗口
        /// </summary>
        /// <param name="Hwnd">组件句柄</param>
        /// <returns></returns>
        public int MoeClose(IntPtr Hwnd)
        {
            msgA = "&type:close&hwnd:" + ((int)Hwnd).ToString() + "&";
            SendMessage(Moev.MoeHwnd, 23232, (IntPtr)State, (IntPtr)Marshal.StringToHGlobalAnsi(msgA).ToPointer());
            return int.Parse(SetState());
        }
    }
}
