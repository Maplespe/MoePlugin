// MoeAPI 定义萌化箱可用功能接口
#include "stdafx.h"
#include "MoeAPI.h"
#include "MoePluginTemplate.h"

using  namespace std;

string State = (char*)malloc(1024); //如果你需要取编辑框的返回值 且文本很长很长 请调整这里的字节长度
string msgA;

//等待萌化箱返回值
extern string SetState(void);


string SetState() {
	while (State == "-1") { 
		Sleep(100); 
	}
	string num = State.data();
	//MessageBoxA(MoeHwnd, (LPCSTR)State.data(), (LPCSTR)"返回值", MB_ICONASTERISK);
	State = "-1";
	return num;
}

/*Moe信息框-萌化箱信息框
title - 信息框的标题
msg - 信息框提示内容 (不能超过120个中文字符)
btn - 信息框按钮类型 (1为是否钮 2为确认取消钮 3为只有确认按钮)
icon - 信息框显示的图标 (1为信息图标 2为错误图标)

返回值 int 1=确定 2=取消
*/
int MoeAPI::MoeMessageBox(string title,string msg,int btn,int icon) {
	msgA = "type:msgbox&msg:" + msg + "&title:" + title + "&btn:" + to_string(btn) + "&icon:" + to_string(icon)+"&";
	::SendMessageA(MoeHwnd, 23232,(WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*切换主题
Path - 主题文件(.theme)的绝对路径

返回值 int 固定为 1 该函数直到主题应用完成才会返回.
*/
int MoeAPI::MoeChangeTheme(string Path) {
	msgA = "type:changetheme&path:" + Path +"&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*写入注册表值 字符串型
Key - 键根目录 (常量 HKEY_XXX)
Path - 注册路径 (不包括键根 如 "SOFTWARE\Microsoft\Windows")
KeyName - 键名称
Value - 要写入的字符串值
Type - 类型 (常量 REG_XXX)
Create - 如果要写入的值不存在 指定是否自动创建 (1自动创建2不处理)
*/
int MoeAPI::MoeRegisterString(int Key, string Path, string KeyName, string Value, int Type, int Create) {
	msgA = "type;regstr&key:" + to_string(Key) + "&path:" + Path + "&keyname:" + KeyName + "&value:" + Value + "&type:" + to_string(Type) + "&create:" + to_string(Create) + "&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*写入注册表值 整数型
Key - 键根目录 (常量 HKEY_XXX)
Path - 注册路径 (不包括键根 如 "SOFTWARE\Microsoft\Windows")
KeyName - 键名称
Value - 要写入的字符串值
Type - 类型 (常量 REG_XXX)
Create - 如果要写入的值不存在 指定是否自动创建 (1自动创建2不处理)
*/
int MoeAPI::MoeRegisterInt(int Key, string Path, string KeyName, int Value, int Type, int Create) {
	msgA = "type;regint&key:" + to_string(Key) + "&path:" + Path + "&keyname:" + KeyName + "&value:" + to_string(Value) + "&type:" + to_string(Type) + "&create:" + to_string(Create) + "&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*设置AeroGlass状态
state - 状态("start"-开启,"reload"-重启,"close"-关闭)

注：只有安装AeroGlass此项才会有效
*/
int MoeAPI::MoeSetAeroGlass(string state) {
	msgA = "type:setaero&state:" + state + "&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*取AeroGlass安装状态

返回值 int 1=未安装 2=已安装
*/
int MoeAPI::MoeGetAGState(void) {
	msgA = "type:getaero";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*添加调试输出
text - 要输出的内容

写入一条消息到萌化箱调试窗口 仅萌化箱开启调试状态有效
*/
int MoeAPI::MoeCout(string text) {
	msgA = "type:cout&msg:" + text+ "&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*创建一个窗口
Parent - 父窗口句柄(为0则不置父)
Style - 窗口风格(1=蓝色边线窗口(纯色)2=萌化箱图片风格窗口(图片))
Title - 窗口标题
Left - 窗口左边位置
Top - 窗口顶边位置
width - 窗口宽度
height - 窗口高度
MaxBtn - 是否启用最大化按钮

注：窗口创建完毕将会调用函数MoeCreatesComplete
且同名窗口不会创建

返回值 HWND - 返回创建的窗口句柄
*/
 HWND MoeAPI::MoeCreateWindow(HWND Parent, int Style, string Title, int Left, int Top, int width, int height, bool MaxBtn) {
	string max = "1";
	if (MaxBtn) { max = "2"; }
	msgA = "indexes:"+Indexes+"&type:createwindows&parent:"+ to_string((int)Parent) +"&style:"+ to_string(Style) + "&title:" + Title
		+ "&left:" + to_string(Left) + "&top:" + to_string(Top) + "&width:" + to_string(width) + "&height:" + to_string(height)
		+ "&maxbtn:" + max + "&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return (HWND)atoi(SetState().data());
}

/*创建一个指定组件
Type - 组件类型(常量 Mox_XXX_Box)
Parent - 父窗口句柄(用MoeCreateWindow创建得到的句柄 或用本命令创建组件得到的句柄)
Title - 组件的标题或内容或图片
Left - 组件左边位置
Top - 组件顶边位置
Width - 组件宽度
Height - 组件高度
Visible - 是否可见
Relation - 关联组件的句柄 不关联填写0
*/
 HWND MoeAPI::MoeCreateBox(int Type, HWND Parent, string Title, int Left, int Top, int Width, int Height, bool Visble,HWND Relation) {
	 string vsb = "1";
	 if (Visble) { vsb = "2"; }
	 msgA = "indexes:" + Indexes + "&type:createbox&types:" + to_string(Type) + "&parent:" + to_string((int)Parent) + "&title:" + Title
		 + "&left:" + to_string(Left) + "&top:" + to_string(Top) + "&width:" + to_string(Width) + "&height:" + to_string(Height)
		 + "&visble:" + vsb + "&relation:" + to_string((int)Relation) + "&";
	 ::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	 return (HWND)atoi(SetState().data());
}

 /*置组件属性
 Type - 组件类型(常量 Mox_Box_XXX 窗口请填1)
 SetType - 要设置的属性类型(常量 Moe_BoxType_XXX)
 Value - 要设置的值
 Hwnd - 组件句柄
 */
int MoeAPI::MoeSetBoxAttribute(int Type, int SetType,string Value, HWND hwnd) {
	 msgA = "indexes:" + Indexes + "&type:setbox&types:" + to_string(Type) + "&settype:" + to_string(SetType) + "&value:" + Value + "&hwnd:" + to_string((int)hwnd) + "&";
	 ::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	 return atoi(SetState().data());
 }

 /*取组件属性
 Type - 组件类型(常量 Mox_Box_XXX 窗口请填1)
 GetType - 要取的属性类型(常量 Moe_BoxType_XXX)
 Hwnd - 组件句柄

 返回值 string - 返回的值 请参考常量的注释进行适当转换
 */
 string MoeAPI::MoeGetBoxAttribute(int Type, int GetType, HWND hwnd) {
	 msgA = "indexes:" + Indexes + "&type:getbox&types:" + to_string(Type) + "&gettype:" + to_string(GetType) + "&hwnd:" + to_string((int)hwnd) + "&";
	 ::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	 return SetState();
 }

 /*置嵌入资源
 ResName - 资源类型名称 (请使用TEXT("")宏来转换字符串)
 ResID - 资源ID (MoePluginTemplate.rc里文件的资源ID)

 返回值 - string (数据的指针和大小-直接使用MoeSetBoxAttribute设置图片即可 也可用于萌化箱其他接口数据提供)
 */
string MoeAPI::MoeSetResource(wstring ResName, unsigned long ResID) {
	 HINSTANCE hDll = hModules;
	 HRSRC hRes = FindResource (hDll, MAKEINTRESOURCE(ResID),ResName.c_str());
	 HGLOBAL hgRes = LoadResource(hDll, hRes);
	 DWORD nResSize = SizeofResource(hDll, hRes);
	 BYTE* pRes = (BYTE*)LockResource(hgRes);

	 return "pres:" + to_string((int)pRes) + "#psize:" + to_string((int)nResSize) + "#";
 }

 /*弹出信息气泡
 Msg - 要弹出的信息内容 可以换行 如不换行会自动换行
 */
int MoeAPI::MoeMessageBubble(string Msg) {
	 msgA = "&type:msgbubble&msg:" + Msg + "&";
	 ::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	 return atoi(SetState().data());
 }

/*播放声音 (只支持WAV和MID格式)
Resource - 声音资源 请使用MoeSetResource来转换
Loop - 是否循环播放
*/
int MoeAPI::MoePlaySound(string Resource,bool Loop) {
	string lp = "1";
	if (Loop) { lp = "2"; }
	msgA = "&type:playsound&res:" + Resource + "&loop:" + lp + "&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*停止播放声音
停止用MoePlaySound播放的声音
*/
int MoeAPI::MoeStopSound(void) {
	msgA = "&type:stopsound&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*设置组件层级
Hwnd - 组件句柄
Level - 层级 (可以负数)

注：设置MoeCreateBox创建组件的层级
*/
int MoeAPI::MoeSetBoxLevel(HWND hwnd, int Level) {
	msgA = "&type:setboxlevel&hwnd:" + to_string((int)hwnd) + "&level:" + to_string(Level) + "&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*获取组件层级
Hwnd - 组件句柄

返回值 int 返回组件层级
*/
int MoeAPI::MoeGetBoxLevel(HWND Hwnd) {
	msgA = "&type:getboxlevel&hwnd:" + to_string((int)Hwnd) + "&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*设置字体资源
FontName - 字体名称
FontSize - 字体大小
FontEffect - 字体效果(1=普通字2=发光字)

返回值 - string (用法与MoeSetResource相同)
*/
string MoeAPI::MoeSetFontResource(string FontName, int FontSize, int FontEffect) {
	return "moeset:font#fname:" + FontName + "#fsize:" + to_string(FontSize) + "#feffect:" + to_string(FontEffect) + "#";
}

/*销毁指定组件
Hwnd - 组件句柄
*/
int MoeAPI::MoeClose(HWND Hwnd) {
	msgA = "&type:close&hwnd:" + to_string((int)Hwnd) + "&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}
