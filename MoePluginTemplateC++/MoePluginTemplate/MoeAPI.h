//MoeAPI.h 萌化箱API接口声明
#pragma once
#include <string>
using namespace std;

const int Moe_Box_Button					= 1011;//Moe_按钮
const int Moe_Box_Lable						= 1012;//Moe_标签
const int Moe_Box_Picture					= 1013;//Moe_图片框
const int Moe_Box_Edit						= 1014;//Moe_编辑框
const int Moe_Box_Check 					= 1015;//Moe_选择框
const int Moe_Box_ProgressBar				= 1016;//Moe_进度条
const int Moe_Event_MouseMove				= 1;//鼠标移动
const int Moe_Event_MouseEnter				= 2;//鼠标进入
const int Moe_Event_MouseLeave				= 3;//鼠标离开
const int Moe_Event_LeftClick				= 4;//鼠标左键按下
const int Moe_Event_LeftUp					= 5;//鼠标左键弹起
const int Moe_Event_LeftDobleClick			= 6;//鼠标左键双击
const int Moe_Event_RightClick				= 7;//鼠标右键按下
const int Moe_Event_RightUp					= 8;//鼠标右键弹起
const int Moe_Event_RightDobleClick			= 9;//鼠标右键双击
const int Moe_Event_Rolling					= 10;//鼠标滚轮滚动
const int Moe_Event_Input					= 11;//字符输入
const int Moe_Event_Edit					= 12;//编辑框内容被改变
const int Moe_Event_FocusChange				= 13;//组件焦点改变
const int Moe_Event_Close					= 14;//窗口即将被销毁
const int Moe_Event_Move					= 15;//窗口位置被移动
const int Moe_Event_Position				= 16;//窗口尺寸被改变
const int Moe_BoxType_Left					= 1101;//组件左边位置 (返回值转int)
const int Moe_BoxType_Top					= 1102;//组件顶边位置 (返回值转int)
const int Moe_BoxType_Width					= 1103;//组件宽度 (返回值转int)
const int Moe_BoxType_Height				= 1104;//组件高度 (返回值转int)
const int Moe_BoxType_Value					= 1105;//组件标题或编辑框内容、进度条位置等 (返回值string 进度条转int)
const int Moe_BoxType_Visble				= 1106;//组件可视状态 (返回值转int 1=可视2=不可视)
const int Moe_BoxType_InputMode				= 1107;//编辑框输入状态 输入方式 (0=普通状态1=禁止输入2=密码输入)
const int Moe_BoxType_PasswordStr			= 1108;//编辑框用于遮掩密码的字符 (仅对编辑框输入状态=2才有效 默认 *)
const int Moe_BoxType_MultiLine				= 1109;//编辑框是否多行 (1=多行2=单行 默认多行)
const int Moe_BoxType_Check					= 1110;//选择框是否选中 (1=选中2=非选中)
const int Moe_BoxType_Image					= 1111;//图片框的图片 请使用MoeSetRes来设置资源 (注 此为只写 无法用于获取)
const int Moe_BoxType_WindowBackGround		= 1112;//窗口的底图 请使用MoeSetRes来设置资源 (注 此为只写 无法用于获取)
const int Moe_BoxType_Font					= 1113;//组件的字体 (注 此为只写 无法用于获取)
const int Moe_BoxType_PicStyle				= 1114;//图片框样式 (1=带背景边框2=不带背景边框 默认 带背景边框)
const int Moe_BoxType_BarMAX				= 1115;//进度条最大位置 (返回值转int)

class MoeAPI {
public:

	/*Moe信息框-萌化箱信息框
	title - 信息框的标题
	msg - 信息框提示内容 (不能超过120个中文字符)
	btn - 信息框按钮类型 (1为是否钮 2为确认取消钮 3为只有确认按钮)
	icon - 信息框显示的图标 (1为信息图标 2为错误图标)

	返回值 int 1=确定 2=取消
	*/
	int MoeMessageBox(string, string, int, int);

	/*切换主题
	Path - 主题文件(.theme)的绝对路径

	返回值 int 固定为 1 该函数直到主题应用完成才会返回.
	*/
	int MoeChangeTheme(string);

	/*写入注册表值 字符串型
	Key - 键根目录 (常量 HKEY_XXX)
	Path - 注册路径 (不包括键根 如 "SOFTWARE\Microsoft\Windows")
	KeyName - 键名称
	Value - 要写入的字符串值
	Type - 类型 (常量 REG_XXX)
	Create - 如果要写入的值不存在 指定是否自动创建 (1自动创建2不处理)
	*/
	int MoeRegisterString(int, string, string, string, int, int);

	/*写入注册表值 整数型
	Key - 键根目录 (常量 HKEY_XXX)
	Path - 注册路径 (不包括键根 如 "SOFTWARE\Microsoft\Windows")
	KeyName - 键名称
	Value - 要写入的字符串值
	Type - 类型 (常量 REG_XXX)
	Create - 如果要写入的值不存在 指定是否自动创建 (1自动创建2不处理)
	*/
	int MoeRegisterInt(int, string, string, int, int, int);

	/*设置AeroGlass状态
	state - 状态("start"-开启,"reload"-重启,"close"-关闭)

	注：只有安装AeroGlass此项才会有效
	*/
	int MoeSetAeroGlass(string);

	/*取AeroGlass安装状态

	返回值 int 1=未安装 2=已安装
	*/
	int MoeGetAGState(void);

	/*添加调试输出
	text - 要输出的内容

	写入一条消息到萌化箱调试窗口 仅萌化箱开启调试状态有效
	*/
	int MoeCout(string);

	/*创建一个窗口
	Parent - 父窗口句柄(为0则不置父)
	Style - 窗口风格(1=蓝色边线窗口(纯色)2=萌化箱图片风格窗口(图片))
	Title - 窗口标题
	Left - 窗口左边位置
	Top - 窗口顶边位置
	Width - 窗口宽度
	Height - 窗口高度
	MaxBtn - 是否启用最大化按钮

	注：窗口创建完毕将会调用函数MoeCreatesComplete
	且同名窗口不会创建

	返回值 HWND - 返回创建的窗口句柄
	*/
	HWND MoeCreateWindow(HWND, int, string, int, int, int, int, bool);

	/*创建一个指定组件
	Type - 组件类型(常量 Moe_XXX_Box)
	Parent - 父窗口句柄(用MoeCreateWindow创建得到的句柄 或用本命令创建组件得到的句柄)
	Title - 组件的标题或内容或图片
	Left - 组件左边位置
	Top - 组件顶边位置
	Width - 组件宽度
	Height - 组件高度
	Visible - 是否可见
	Relation - 关联组件的句柄 不关联填写0
	*/
	HWND MoeCreateBox(int, HWND, string, int, int, int, int, bool, HWND);

	/*置组件属性
	Type - 组件类型
	SetType - 要设置的属性类型(常量 Moe_BoxType_XXX 窗口请填1)
	Value - 要设置的值
	Hwnd - 组件句柄
	*/
	int MoeSetBoxAttribute(int, int, string, HWND);

	/*取组件属性
	Type - 组件类型
	GetType - 要取的属性类型(常量 Moe_BoxType_XXX 窗口请填1)
	Hwnd - 组件句柄

	返回值 string - 返回的值 请参考常量的注释进行适当转换
	*/
	string MoeGetBoxAttribute(int, int, HWND);

	/*置嵌入资源
	ResName - 资源类型名称 (请使用TEXT("")宏来转换字符串)
	ResID - 资源ID (MoePluginTemplate.rc里文件的资源ID)

	返回值 - string (数据的指针和大小-直接使用MoeSetBoxAttribute设置图片即可 也可用于萌化箱其他接口数据提供)
	*/
	string MoeSetResource(wstring, unsigned long);

	/*弹出信息气泡
	 Msg - 要弹出的信息内容 可以换行 如不换行会自动换行
	 */
	int MoeMessageBubble(string);

	/*播放声音 (只支持WAV和MID格式)
	Resource - 声音资源 请使用MoeSetResource来转换
	*/
	int MoePlaySound(string,bool);

	/*停止播放声音
	停止用MoePlaySound播放的声音
	*/
	int MoeStopSound(void);

	/*设置组件层级
	Hwnd - 组件句柄
	Level - 层级 (可以负数)

	注：设置MoeCreateBox创建组件的层次
	*/
	int MoeSetBoxLevel(HWND, int);

	/*获取组件层级
	Hwnd - 组件句柄

	返回值 int 返回组件层级
	*/
	int MoeGetBoxLevel(HWND);

	/*设置字体资源
	FontName - 字体名称
	FontSize - 字体大小
	FontEffect - 字体效果(1=普通字2=发光字)
	*/
	string MoeSetFontResource(string, int, int);

	/*销毁指定组件
	Hwnd - 组件句柄
	*/
	int MoeClose(HWND);
};
