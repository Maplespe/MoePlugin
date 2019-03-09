//MoeAPI.h �Ȼ���API�ӿ�����
#pragma once
#include <string>
using namespace std;

const int Moe_Box_Button					= 1011;//Moe_��ť
const int Moe_Box_Lable						= 1012;//Moe_��ǩ
const int Moe_Box_Picture					= 1013;//Moe_ͼƬ��
const int Moe_Box_Edit						= 1014;//Moe_�༭��
const int Moe_Box_Check 					= 1015;//Moe_ѡ���
const int Moe_Event_MouseMove				= 1;//����ƶ�
const int Moe_Event_MouseEnter				= 2;//������
const int Moe_Event_MouseLeave				= 3;//����뿪
const int Moe_Event_LeftClick				= 4;//����������
const int Moe_Event_LeftUp					= 5;//����������
const int Moe_Event_LeftDobleClick			= 6;//������˫��
const int Moe_Event_RightClick				= 7;//����Ҽ�����
const int Moe_Event_RightUp					= 8;//����Ҽ�����
const int Moe_Event_RightDobleClick			= 9;//����Ҽ�˫��
const int Moe_Event_Rolling					= 10;//�����ֹ���
const int Moe_Event_Input					= 11;//�ַ�����
const int Moe_Event_Edit					= 12;//�༭�����ݱ��ı�
const int Moe_Event_FocusChange				= 13;//�������ı�
const int Moe_Event_Close					= 14;//���ڼ���������
const int Moe_Event_Move					= 15;//����λ�ñ��ƶ�
const int Moe_Event_Position				= 16;//���ڳߴ类�ı�
const int Moe_BoxType_Left					= 1101;//������λ�� (����ֵתint)
const int Moe_BoxType_Top					= 1102;//�������λ�� (����ֵתint)
const int Moe_BoxType_Width					= 1103;//������ (����ֵתint)
const int Moe_BoxType_Height				= 1104;//����߶� (����ֵתint)
const int Moe_BoxType_Value					= 1105;//��������༭������ (����ֵstring�����޸�)
const int Moe_BoxType_Visble				= 1106;//�������״̬ (����ֵתint 1=����2=������)
const int Moe_BoxType_InputMode				= 1107;//�༭������״̬ ���뷽ʽ (0=��ͨ״̬1=��ֹ����2=��������)
const int Moe_BoxType_PasswordStr			= 1108;//�༭����������������ַ� (���Ա༭������״̬=2����Ч Ĭ�� *)
const int Moe_BoxType_MultiLine				= 1109;//�༭���Ƿ���� (1=����2=���� Ĭ�϶���)
const int Moe_BoxType_Check					= 1110;//ѡ����Ƿ�ѡ�� (1=ѡ��2=��ѡ��)
const int Moe_BoxType_Image					= 1111;//ͼƬ���ͼƬ ��ʹ��MoeSetRes��������Դ (ע ��Ϊֻд �޷����ڻ�ȡ)
const int Moe_BoxType_WindowBackGround		= 1112;//���ڵĵ�ͼ ��ʹ��MoeSetRes��������Դ (ע ��Ϊֻд �޷����ڻ�ȡ)
const int Moe_BoxType_Font					= 1113;//��������� (ע ��Ϊֻд �޷����ڻ�ȡ)

class MoeAPI {
public:

	/*Moe��Ϣ��-�Ȼ�����Ϣ��
	title - ��Ϣ��ı���
	msg - ��Ϣ����ʾ���� (���ܳ���120�������ַ�)
	btn - ��Ϣ��ť���� (1Ϊ�Ƿ�ť 2Ϊȷ��ȡ��ť 3Ϊֻ��ȷ�ϰ�ť)
	icon - ��Ϣ����ʾ��ͼ�� (1Ϊ��Ϣͼ�� 2Ϊ����ͼ��)

	����ֵ int 1=ȷ�� 2=ȡ��
	*/
	int MoeMessageBox(string, string, int, int);

	/*�л�����
	Path - �����ļ�(.theme)�ľ���·��

	����ֵ int �̶�Ϊ 1 �ú���ֱ������Ӧ����ɲŻ᷵��.
	*/
	int MoeChangeTheme(string);

	/*д��ע���ֵ �ַ�����
	Key - ����Ŀ¼ (���� HKEY_XXX)
	Path - ע��·�� (���������� �� "SOFTWARE\Microsoft\Windows")
	KeyName - ������
	Value - Ҫд����ַ���ֵ
	Type - ���� (���� REG_XXX)
	Create - ���Ҫд���ֵ������ ָ���Ƿ��Զ����� (1�Զ�����2������)
	*/
	int MoeRegisterString(int, string, string, string, int, int);

	/*д��ע���ֵ ������
	Key - ����Ŀ¼ (���� HKEY_XXX)
	Path - ע��·�� (���������� �� "SOFTWARE\Microsoft\Windows")
	KeyName - ������
	Value - Ҫд����ַ���ֵ
	Type - ���� (���� REG_XXX)
	Create - ���Ҫд���ֵ������ ָ���Ƿ��Զ����� (1�Զ�����2������)
	*/
	int MoeRegisterInt(int, string, string, int, int, int);

	/*����AeroGlass״̬
	state - ״̬("start"-����,"reload"-����,"close"-�ر�)

	ע��ֻ�а�װAeroGlass����Ż���Ч
	*/
	int MoeSetAeroGlass(string);

	/*ȡAeroGlass��װ״̬

	����ֵ int 1=δ��װ 2=�Ѱ�װ
	*/
	int MoeGetAGState(void);

	/*��ӵ������
	text - Ҫ���������

	д��һ����Ϣ���Ȼ�����Դ��� ���Ȼ��俪������״̬��Ч
	*/
	int MoeCout(string);

	/*����һ������
	Parent - �����ھ��(Ϊ0���ø�)
	Style - ���ڷ��(1=��ɫ���ߴ���(��ɫ)2=�Ȼ���ͼƬ��񴰿�(ͼƬ))
	Title - ���ڱ���
	Left - �������λ��
	Top - ���ڶ���λ��
	Width - ���ڿ��
	Height - ���ڸ߶�
	MaxBtn - �Ƿ�������󻯰�ť

	ע�����ڴ�����Ͻ�����ú���MoeCreatesComplete
	��ͬ�����ڲ��ᴴ��

	����ֵ HWND - ���ش����Ĵ��ھ��
	*/
	HWND MoeCreateWindow(HWND, int, string, int, int, int, int, bool);

	/*����һ��ָ�����
	Type - �������(���� Moe_XXX_Box)
	Parent - �����ھ��(��MoeCreateWindow�����õ��ľ�� ���ñ����������õ��ľ��)
	Title - ����ı�������ݻ�ͼƬ
	Left - ������λ��
	Top - �������λ��
	Width - ������
	Height - ����߶�
	Visible - �Ƿ�ɼ�
	Relation - ��������ľ�� ��������д0
	*/
	HWND MoeCreateBox(int, HWND, string, int, int, int, int, bool, HWND);

	/*���������
	Type - �������
	SetType - Ҫ���õ���������(���� Moe_BoxType_XXX ��������1)
	Value - Ҫ���õ�ֵ
	Hwnd - ������
	*/
	int MoeSetBoxAttribute(int, int, string, HWND);

	/*ȡ�������
	Type - �������
	GetType - Ҫȡ����������(���� Moe_BoxType_XXX ��������1)
	Hwnd - ������

	����ֵ string - ���ص�ֵ ��ο�������ע�ͽ����ʵ�ת��
	*/
	string MoeGetBoxAttribute(int, int, HWND);

	/*��Ƕ����Դ
	ResName - ��Դ�������� (��ʹ��TEXT("")����ת���ַ���)
	ResID - ��ԴID (MoePluginTemplate.rc���ļ�����ԴID)

	����ֵ - string (���ݵ�ָ��ʹ�С-ֱ��ʹ��MoeSetBoxAttribute����ͼƬ���� Ҳ�������Ȼ��������ӿ������ṩ)
	*/
	string MoeSetResource(wstring, unsigned long);

	/*������Ϣ����
	 Msg - Ҫ��������Ϣ���� ���Ի��� �粻���л��Զ�����
	 */
	int MoeMessageBubble(string);

	/*�������� (ֻ֧��WAV��MID��ʽ)
	Resource - ������Դ ��ʹ��MoeSetResource��ת��
	*/
	int MoePlaySound(string,bool);

	/*ֹͣ��������
	ֹͣ��MoePlaySound���ŵ�����
	*/
	int MoeStopSound(void);

	/*��������㼶
	Hwnd - ������
	Level - �㼶 (���Ը���)

	ע������MoeCreateBox��������Ĳ��
	*/
	int MoeSetBoxLevel(HWND, int);

	/*��ȡ����㼶
	Hwnd - ������

	����ֵ int ��������㼶
	*/
	int MoeGetBoxLevel(HWND);

	/*����������Դ
	FontName - ��������
	FontSize - �����С
	FontEffect - ����Ч��(1=��ͨ��2=������)
	*/
	string MoeSetFontResource(string, int, int);
};