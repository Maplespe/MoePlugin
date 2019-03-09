// MoeAPI �����Ȼ�����ù��ܽӿ�
#include "stdafx.h"
#include "MoeAPI.h"
#include "MoePluginTemplate.h"

using  namespace std;

string State = (char*)malloc(1024); //�������Ҫȡ�༭��ķ���ֵ ���ı��ܳ��ܳ� �����������ֽڳ���
string msgA;

//�ȴ��Ȼ��䷵��ֵ
extern string SetState(void);


string SetState() {
	while (State == "-1") { 
		Sleep(100); 
	}
	string num = State.data();
	//MessageBoxA(MoeHwnd, (LPCSTR)State.data(), (LPCSTR)"����ֵ", MB_ICONASTERISK);
	State = "-1";
	return num;
}

/*Moe��Ϣ��-�Ȼ�����Ϣ��
title - ��Ϣ��ı���
msg - ��Ϣ����ʾ���� (���ܳ���120�������ַ�)
btn - ��Ϣ��ť���� (1Ϊ�Ƿ�ť 2Ϊȷ��ȡ��ť 3Ϊֻ��ȷ�ϰ�ť)
icon - ��Ϣ����ʾ��ͼ�� (1Ϊ��Ϣͼ�� 2Ϊ����ͼ��)

����ֵ int 1=ȷ�� 2=ȡ��
*/
int MoeAPI::MoeMessageBox(string title,string msg,int btn,int icon) {
	msgA = "type:msgbox&msg:" + msg + "&title:" + title + "&btn:" + to_string(btn) + "&icon:" + to_string(icon)+"&";
	::SendMessageA(MoeHwnd, 23232,(WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*�л�����
Path - �����ļ�(.theme)�ľ���·��

����ֵ int �̶�Ϊ 1 �ú���ֱ������Ӧ����ɲŻ᷵��.
*/
int MoeAPI::MoeChangeTheme(string Path) {
	msgA = "type:changetheme&path:" + Path +"&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*д��ע���ֵ �ַ�����
Key - ����Ŀ¼ (���� HKEY_XXX)
Path - ע��·�� (���������� �� "SOFTWARE\Microsoft\Windows")
KeyName - ������
Value - Ҫд����ַ���ֵ
Type - ���� (���� REG_XXX)
Create - ���Ҫд���ֵ������ ָ���Ƿ��Զ����� (1�Զ�����2������)
*/
int MoeAPI::MoeRegisterString(int Key, string Path, string KeyName, string Value, int Type, int Create) {
	msgA = "type;regstr&key:" + to_string(Key) + "&path:" + Path + "&keyname:" + KeyName + "&value:" + Value + "&type:" + to_string(Type) + "&create:" + to_string(Create) + "&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*д��ע���ֵ ������
Key - ����Ŀ¼ (���� HKEY_XXX)
Path - ע��·�� (���������� �� "SOFTWARE\Microsoft\Windows")
KeyName - ������
Value - Ҫд����ַ���ֵ
Type - ���� (���� REG_XXX)
Create - ���Ҫд���ֵ������ ָ���Ƿ��Զ����� (1�Զ�����2������)
*/
int MoeAPI::MoeRegisterInt(int Key, string Path, string KeyName, int Value, int Type, int Create) {
	msgA = "type;regint&key:" + to_string(Key) + "&path:" + Path + "&keyname:" + KeyName + "&value:" + to_string(Value) + "&type:" + to_string(Type) + "&create:" + to_string(Create) + "&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*����AeroGlass״̬
state - ״̬("start"-����,"reload"-����,"close"-�ر�)

ע��ֻ�а�װAeroGlass����Ż���Ч
*/
int MoeAPI::MoeSetAeroGlass(string state) {
	msgA = "type:setaero&state:" + state + "&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*ȡAeroGlass��װ״̬

����ֵ int 1=δ��װ 2=�Ѱ�װ
*/
int MoeAPI::MoeGetAGState(void) {
	msgA = "type:getaero";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*��ӵ������
text - Ҫ���������

д��һ����Ϣ���Ȼ�����Դ��� ���Ȼ��俪������״̬��Ч
*/
int MoeAPI::MoeCout(string text) {
	msgA = "type:cout&msg:" + text+ "&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*����һ������
Parent - �����ھ��(Ϊ0���ø�)
Style - ���ڷ��(1=��ɫ���ߴ���(��ɫ)2=�Ȼ���ͼƬ��񴰿�(ͼƬ))
Title - ���ڱ���
Left - �������λ��
Top - ���ڶ���λ��
width - ���ڿ��
height - ���ڸ߶�
MaxBtn - �Ƿ�������󻯰�ť

ע�����ڴ�����Ͻ�����ú���MoeCreatesComplete
��ͬ�����ڲ��ᴴ��

����ֵ HWND - ���ش����Ĵ��ھ��
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

/*����һ��ָ�����
Type - �������(���� Mox_XXX_Box)
Parent - �����ھ��(��MoeCreateWindow�����õ��ľ�� ���ñ����������õ��ľ��)
Title - ����ı�������ݻ�ͼƬ
Left - ������λ��
Top - �������λ��
Width - ������
Height - ����߶�
Visible - �Ƿ�ɼ�
Relation - ��������ľ�� ��������д0
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

 /*���������
 Type - �������(���� Mox_Box_XXX ��������1)
 SetType - Ҫ���õ���������(���� Moe_BoxType_XXX)
 Value - Ҫ���õ�ֵ
 Hwnd - ������
 */
int MoeAPI::MoeSetBoxAttribute(int Type, int SetType,string Value, HWND hwnd) {
	 msgA = "indexes:" + Indexes + "&type:setbox&types:" + to_string(Type) + "&settype:" + to_string(SetType) + "&value:" + Value + "&hwnd:" + to_string((int)hwnd) + "&";
	 ::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	 return atoi(SetState().data());
 }

 /*ȡ�������
 Type - �������(���� Mox_Box_XXX ��������1)
 GetType - Ҫȡ����������(���� Moe_BoxType_XXX)
 Hwnd - ������

 ����ֵ string - ���ص�ֵ ��ο�������ע�ͽ����ʵ�ת��
 */
 string MoeAPI::MoeGetBoxAttribute(int Type, int GetType, HWND hwnd) {
	 msgA = "indexes:" + Indexes + "&type:getbox&types:" + to_string(Type) + "&gettype:" + to_string(GetType) + "&hwnd:" + to_string((int)hwnd) + "&";
	 ::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	 return SetState();
 }

 /*��Ƕ����Դ
 ResName - ��Դ�������� (��ʹ��TEXT("")����ת���ַ���)
 ResID - ��ԴID (MoePluginTemplate.rc���ļ�����ԴID)

 ����ֵ - string (���ݵ�ָ��ʹ�С-ֱ��ʹ��MoeSetBoxAttribute����ͼƬ���� Ҳ�������Ȼ��������ӿ������ṩ)
 */
string MoeAPI::MoeSetResource(wstring ResName, unsigned long ResID) {
	 HINSTANCE hDll = hModules;
	 HRSRC hRes = FindResource (hDll, MAKEINTRESOURCE(ResID),ResName.c_str());
	 HGLOBAL hgRes = LoadResource(hDll, hRes);
	 DWORD nResSize = SizeofResource(hDll, hRes);
	 BYTE* pRes = (BYTE*)LockResource(hgRes);

	 return "pres:" + to_string((int)pRes) + "#psize:" + to_string((int)nResSize) + "#";
 }

 /*������Ϣ����
 Msg - Ҫ��������Ϣ���� ���Ի��� �粻���л��Զ�����
 */
int MoeAPI::MoeMessageBubble(string Msg) {
	 msgA = "&type:msgbubble&msg:" + Msg + "&";
	 ::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	 return atoi(SetState().data());
 }

/*�������� (ֻ֧��WAV��MID��ʽ)
Resource - ������Դ ��ʹ��MoeSetResource��ת��
Loop - �Ƿ�ѭ������
*/
int MoeAPI::MoePlaySound(string Resource,bool Loop) {
	string lp = "1";
	if (Loop) { lp = "2"; }
	msgA = "&type:playsound&res:" + Resource + "&loop:" + lp + "&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*ֹͣ��������
ֹͣ��MoePlaySound���ŵ�����
*/
int MoeAPI::MoeStopSound(void) {
	msgA = "&type:stopsound&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*��������㼶
Hwnd - ������
Level - �㼶 (���Ը���)

ע������MoeCreateBox��������Ĳ㼶
*/
int MoeAPI::MoeSetBoxLevel(HWND hwnd, int Level) {
	msgA = "&type:setboxlevel&hwnd:" + to_string((int)hwnd) + "&level:" + to_string(Level) + "&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*��ȡ����㼶
Hwnd - ������

����ֵ int ��������㼶
*/
int MoeAPI::MoeGetBoxLevel(HWND hwnd) {
	msgA = "&type:getboxlevel&hwnd:" + to_string((int)hwnd) + "&";
	::SendMessageA(MoeHwnd, 23232, (WPARAM)State.data(), (LPARAM)msgA.data());
	return atoi(SetState().data());
}

/*����������Դ
FontName - ��������
FontSize - �����С
FontEffect - ����Ч��(1=��ͨ��2=������)

����ֵ - string (�÷���MoeSetResource��ͬ)
*/
string MoeAPI::MoeSetFontResource(string FontName, int FontSize, int FontEffect) {
	return "moeset:font#fname:" + FontName + "#fsize:" + to_string(FontSize) + "#feffect:" + to_string(FontEffect) + "#";
}