// MoePluginTemplate.cpp : 定义 DLL 应用程序的导出函数。
// winmoes.com 2019.3.2 by Maple

#include "stdafx.h"
#include "MoePluginTemplate.h"
#include "MoeAPI.h"
#include <string>

using std::string;
string datas;//存放数据
string Indexes;//插件索引
MoeAPI Moe;//萌化箱API接口类
extern "C" MOEDLL_API const char* GetIndexes(int Index) { Indexes = to_string(Index); return datas.data(); }

HWND MoeHwnd; //萌化箱句柄


//这里是插件名
string Name = "测试插件模板";

//萌化箱加载插件列表将会调用此项,也是插件初始化的地方，请尽快返回 否则影响萌化箱启动
extern "C" MOEDLL_API const char* GetPluginName(HWND Hwnd) {
	MoeHwnd = Hwnd; //萌化箱主窗口句柄
	//这里加入初始化代码


	return Name.data();
}

//萌化箱插件列表被选中后会调用此项
extern "C" MOEDLL_API const char* GetPluginInfo() {

	//这里是作者名
	string Names = "Maple";
	//这里是插件版本
	string Ver = "1.0";
	//插件描述信息 可以换行
	string Info = "萌化箱插件模板\r\n这是一个插件描述";
	//插件按钮 这里设置按钮的标题 设置为 "null" 则不显示按钮 按钮被按下会触发下面的OpenSetMenu事件
	string btn = "插件设置菜单";
	//请不要修改返回数据
	datas = "&1" + Names + "&2" + Ver + "&3" + Info + "&4" +btn + "&";
	return datas.data();
}

/* 这个是测试变量 用来储存下面创建组件的句柄 可以删除*/
HWND test[5];


/*萌化箱插件设置按钮被按下后会调用此项
参数 x 鼠标x坐标位置
参数 y 鼠标y坐标位置
*/
extern "C" MOEDLL_API const char* OpenSetMenu(int x, int y) {
	//加入自定义函数
	//----测试代码 一个简单的界面 可以删除
	HWND main = Moe.MoeCreateWindow(0, 2, "测试窗口", 100, 100, 800, 500, true);
	test[0] = Moe.MoeCreateBox(Moe_Box_Edit, main, "hello word", 1, 27 + 32, 392, 30, true, 0);
	test[1] = Moe.MoeCreateBox(Moe_Box_Lable, main, "请输入一段文字~", 0, 32, 100, 25, true, 0);
	test[2] = Moe.MoeCreateBox(Moe_Box_Button, main, "点我试试", 400, 27 + 32, 80, 30, true, 0);
	test[3] = Moe.MoeCreateBox(Moe_Box_Picture, main, Moe.MoeSetResource(TEXT("JPG"), IDB_IMG1), 0, 60 + 32, 220,300, true, 0);
	test[4] = Moe.MoeCreateBox(Moe_Box_Check, main, "这是选择框", 228, 60 + 32, 100, 30, true, 0);
	//----测试代码结束

	return datas.data();
}

//使用MoeCreateWindow创建窗口完毕后会触发此事件
extern "C" MOEDLL_API const char * MoeCreateComplete() {


	return datas.data();
}

/*使用MoeCreateBox创建组件之后的回调
参数 hwnd - 触发事件的组件的句柄
参数 event - 事件ID (常量 Moe_Event_XXX)

注：创建的组件均使用此函数
请将参数hwnd和创建组件得到的句柄作对比 即可判断是哪个组件的事件
*/
extern "C" MOEDLL_API const char * MoeBoxEvent(HWND hwnd, int event) {
	//加入判断代码

	//---------------------------测试代码 可以删除
	/*测试代码 上面的测试代码创建了一个简单的界面 这里处理事件*/
	if (hwnd == test[2] && event == Moe_Event_LeftClick) {//按钮被按下
		Moe.MoeMessageBubble("你输入了：" + Moe.MoeGetBoxAttribute(Moe_Box_Edit, Moe_BoxType_Value, test[0]));
	}
	if (hwnd == test[4] && event == Moe_Event_LeftClick) {//选择框被按下
		if (Moe.MoeGetBoxAttribute(Moe_Box_Check, Moe_BoxType_Check, test[4]) == "2") {
			//选择框是选中状态
			Moe.MoeSetBoxAttribute(Moe_Box_Lable, Moe_BoxType_Font, Moe.MoeSetFontResource("微软雅黑", 12, 2), test[1]);
		}
		else {
			//选择框未选中
			Moe.MoeSetBoxAttribute(Moe_Box_Lable, Moe_BoxType_Font, Moe.MoeSetFontResource("微软雅黑", 12, 1), test[1]);
		}
	}
	//---------------------------测试代码结束
	return datas.data();
}