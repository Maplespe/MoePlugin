// MoePluginTemplate.cpp : ���� DLL Ӧ�ó���ĵ���������
// winmoes.com 2019.3.2 by Maple

#include "stdafx.h"
#include "MoePluginTemplate.h"
#include "MoeAPI.h"
#include <string>

using std::string;
string datas;//�������
string Indexes;//�������
MoeAPI Moe;//�Ȼ���API�ӿ���
extern "C" MOEDLL_API const char* GetIndexes(int Index) { Indexes = to_string(Index); return datas.data(); }

HWND MoeHwnd; //�Ȼ�����


//�����ǲ����
string Name = "���Բ��ģ��";

//�Ȼ�����ز���б�����ô���,Ҳ�ǲ����ʼ���ĵط����뾡�췵�� ����Ӱ���Ȼ�������
extern "C" MOEDLL_API const char* GetPluginName(HWND Hwnd) {
	MoeHwnd = Hwnd; //�Ȼ��������ھ��
	//��������ʼ������


	return Name.data();
}

//�Ȼ������б�ѡ�к����ô���
extern "C" MOEDLL_API const char* GetPluginInfo() {

	//������������
	string Names = "Maple";
	//�����ǲ���汾
	string Ver = "1.0";
	//���������Ϣ ���Ի���
	string Info = "�Ȼ�����ģ��\r\n����һ���������";
	//�����ť �������ð�ť�ı��� ����Ϊ "null" ����ʾ��ť ��ť�����»ᴥ�������OpenSetMenu�¼�
	string btn = "������ò˵�";
	//�벻Ҫ�޸ķ�������
	datas = "&1" + Names + "&2" + Ver + "&3" + Info + "&4" +btn + "&";
	return datas.data();
}

/* ����ǲ��Ա��� �����������洴������ľ�� ����ɾ��*/
HWND test[5];


/*�Ȼ��������ð�ť�����º����ô���
���� x ���x����λ��
���� y ���y����λ��
*/
extern "C" MOEDLL_API const char* OpenSetMenu(int x, int y) {
	//�����Զ��庯��
	//----���Դ��� һ���򵥵Ľ��� ����ɾ��
	HWND main = Moe.MoeCreateWindow(0, 2, "���Դ���", 100, 100, 800, 500, true);
	test[0] = Moe.MoeCreateBox(Moe_Box_Edit, main, "hello word", 1, 27 + 32, 392, 30, true, 0);
	test[1] = Moe.MoeCreateBox(Moe_Box_Lable, main, "������һ������~", 0, 32, 100, 25, true, 0);
	test[2] = Moe.MoeCreateBox(Moe_Box_Button, main, "��������", 400, 27 + 32, 80, 30, true, 0);
	test[3] = Moe.MoeCreateBox(Moe_Box_Picture, main, Moe.MoeSetResource(TEXT("JPG"), IDB_IMG1), 0, 60 + 32, 220,300, true, 0);
	test[4] = Moe.MoeCreateBox(Moe_Box_Check, main, "����ѡ���", 228, 60 + 32, 100, 30, true, 0);
	//----���Դ������

	return datas.data();
}

//ʹ��MoeCreateWindow����������Ϻ�ᴥ�����¼�
extern "C" MOEDLL_API const char * MoeCreateComplete() {


	return datas.data();
}

/*ʹ��MoeCreateBox�������֮��Ļص�
���� hwnd - �����¼�������ľ��
���� event - �¼�ID (���� Moe_Event_XXX)

ע�������������ʹ�ô˺���
�뽫����hwnd�ʹ�������õ��ľ�����Ա� �����ж����ĸ�������¼�
*/
extern "C" MOEDLL_API const char * MoeBoxEvent(HWND hwnd, int event) {
	//�����жϴ���

	//---------------------------���Դ��� ����ɾ��
	/*���Դ��� ����Ĳ��Դ��봴����һ���򵥵Ľ��� ���ﴦ���¼�*/
	if (hwnd == test[2] && event == Moe_Event_LeftClick) {//��ť������
		Moe.MoeMessageBubble("�������ˣ�" + Moe.MoeGetBoxAttribute(Moe_Box_Edit, Moe_BoxType_Value, test[0]));
	}
	if (hwnd == test[4] && event == Moe_Event_LeftClick) {//ѡ��򱻰���
		if (Moe.MoeGetBoxAttribute(Moe_Box_Check, Moe_BoxType_Check, test[4]) == "2") {
			//ѡ�����ѡ��״̬
			Moe.MoeSetBoxAttribute(Moe_Box_Lable, Moe_BoxType_Font, Moe.MoeSetFontResource("΢���ź�", 12, 2), test[1]);
		}
		else {
			//ѡ���δѡ��
			Moe.MoeSetBoxAttribute(Moe_Box_Lable, Moe_BoxType_Font, Moe.MoeSetFontResource("΢���ź�", 12, 1), test[1]);
		}
	}
	//---------------------------���Դ������
	return datas.data();
}