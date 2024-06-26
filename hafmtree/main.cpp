#include "HUFF.h"//�����������ͷ�ļ�
#include "CODE.h"//���������ı���洢��
#include<fstream>
#include<iostream>
using namespace std;
int main()
{	
	void menu();
	menu();

	CODE<char>* code = nullptr;//���ڴ洢���ı���
	HuffTree<char>* HT = nullptr;//���ڴ洢��������
	int num = 0;//Ԫ�ظ���
	char key;//ѡ��˵�
	cin >> key;
	while (key != 'Q'&&key!='q') {
		switch (key) {
		case 'I'://��ʼ����洢
		case'i':
		{
			ofstream outfile("hfmTree.dat", ios::out | ios::trunc);//�洢��������
			if (!outfile) {
				cout << "hfmTree.dat�ļ��򲻿�" << endl;
				break;
			}
			num = 0;
			int i = 0;
			char key2;//�ַ�
			int weight;//Ȩֵ
			int count;//���ڼ���
			int n;//�洢Ԫ�س���
			string saveT;//���ڴ洢Ԫ��
			while (num < 3) {//��������Ԫ��>=3��
				cout << "�����ַ�����Сx:(x>=3)" << endl;
				cin >> num;
			}
			saveT = to_string(num)+ " ";//�洢Ԫ�ظ������� �����ֵ���Ԫ��
			count = num;
			cout << "�����ַ���Ȩֵ:" << endl;
			HuffTree<char> **HFT=new HuffTree<char>*[num];
			for (i = 0; i<num; i++)
				HFT[i] = new HuffTree<char>();
			                         //����Tree�����ڽ�����������buildHuff��������
			while (count > 0) {//ѭ������Tree�鸳ֵ��count����
				cin >> key2;
				cin >> weight;
				HuffTree<char> T(key2, weight);//��ʼ����Tree
				saveT = saveT + key2 +" "+ to_string(weight) + " ";
				**(HFT+num-count) = T;//�鸳ֵ
				count--;
			}
			n = saveT.length();
			for (i = 0; i < n; i++)
				outfile.put(saveT[i]);//ѭ��д���ļ�
			outfile.close();
			HT=buildHuff(HFT, num);//������������ֵ��HT
			code = new CODE<char>[num];
			int j = 0;
			ECode(HT->root(), code, j);//������
		break; }
		case 'E'://����
		case 'e':
		{
			if (HT == nullptr)cout << "��ǰû�й�������" << endl;
			else {
				char ch;//���ļ��ַ�
				string s="";//���ļ��ַ���
				int i;//ѭ������
				ifstream infile("ToBeTran.dat", ios::in );
				                              //���������ļ�
				if (!infile) { 
					cout << "ToBeTran.dat�ļ��򲻿�" << endl;
					break;
				}
				ofstream outfile("CodeFile.dat", ios::out| ios::trunc);
				                              //�洢������ļ�
				if (!outfile) {
					cout << "CodeFile.dat�ļ��򲻿�" << endl;
					break;
				}
				while (infile.get(ch))//���ַ�
					for (i = 0; i < num; i++) //ѭ���������ַ����бȽ�
						if (ch == code[i].getVa())
							s = s + code[i].getCo() + " ";
				                            //���ַ����ڶ��ļ����б���
				int n = s.length();
				for (i = 0; i < n; i++)
					outfile.put(s[i]);//�洢�����ļ�
				infile.close();
				outfile.close();
			}
			break; }
		case 'D'://����
		case 'd':
		{
			if (HT == nullptr)cout << "��ǰû�й�������" << endl;
			else {
				int i;//ѭ������
				char ch;//���ļ��ַ�
				string temp = "";//���ڱ����ж�
				ifstream infile("CodeFile.dat", ios::in );
				                                       //���������ļ�
				if (!infile) {
					cout << "CodeFile.dat�ļ��򲻿�" << endl;
					break;
				}
				ofstream outfile("TextFile.dat", ios::out | ios::trunc);
				if (!outfile) {
					cout << "TextFile.dat�ļ��򲻿�" << endl;
					break;
				}
				while (infile.get(ch)) {
					if (ch != ' ')
						temp += ch;
					else {
						for (i = 0; i < num; i++)
							if (temp == code[i].getCo())//����Ƚ�
								outfile.put(code[i].getVa());//��-���洢
						temp = "";
					}
				}
				infile.close();
				outfile.close();
			}
			break; }
		case 'P'://��ӡ�����ļ�
		case 'p':
		{
			if (HT == nullptr)cout << "��ǰû�й�������" << endl;
			else {
				int i = 0;
				char ch;
				string temp = "";
				ifstream infile("CodeFile.dat", ios::in );
				if (!infile) {
					cout << "CodeFile.dat�ļ��򲻿�" << endl;
					break;
				}
				ofstream outfile("CodePrint.dat", ios::out | ios::trunc);
				if (!outfile) {
					cout << "CodePrint.dat�ļ��򲻿�" << endl;
					break;
				}
				while (infile.get(ch)) {
					if (ch != ' ') { 
						cout << ch;
						outfile.put(ch);
						i++;
					}
					if (i % 50 == 0) {
						cout << endl;
						outfile.put('\n');
					}
				}
				cout << endl;
			}
			break; }
		case 'T'://��ӡ��������
		case 't':
		{
			if (HT == nullptr)cout << "��ǰû�й�������" << endl;
			else {
				ofstream outfile("TreePrint.dat", ios::out | ios::trunc);
				if (!outfile) {
					cout << "TreePrint.dat�ļ��򲻿�" << endl;
					break;
				}
				string ss = "";
				string sto = "";
				showT(HT->root(),ss,sto);
				int j;
				for (j = 0; j < num; j++)
				{
					cout << code[j].getVa() << ":" << code[j].getCo() << endl;
					sto = sto + code[j].getVa() + ":" + code[j].getCo() + "\n";
				}
				int n = sto.length();
				for (j = 0; j < n; j++)
					outfile.put(sto[j]);
				outfile.close();
			}
			break; }
		case 'S'://���������
		case 's':
		{
			if (HT != nullptr)cout << "��ǰ�ѳ�ʼ����������" << endl;
			else {
				char ch;//���ļ��ַ�
				char key3;//�ַ�
				int weight;//Ȩ��
				int i;//ѭ������
				string N;//Ȩ��
				int count = 0;
				int ct2 = 0;
				HuffTree<char> **HFT = nullptr;
				ifstream infile("hfmTree.dat", ios::in );
				if (!infile) {
					cout << "hfmTree.dat�ļ��򲻿�" << endl;
					break;
				}
				while (infile.get(ch)) {
					if (ch != ' ') {
						N = N + ch;
						continue;
					}
					else {
						if (count == 0) {
							num = stoi(N);
							HFT = new HuffTree<char>*[num];
							for (i = 0; i < num; i++)
								HFT[i] = new HuffTree<char>();
						}
						else if (count % 2 != 0)key3 = N[0];
						else if (count % 2 == 0) {
							weight = stoi(N);
							HuffTree<char> T(key3, weight);
							**(HFT + ct2) = T;
							ct2++;
						}
						count++;
						N = "";
					}
				}
				HT = buildHuff(HFT, num);
				code = new CODE<char>[num];
				int j = 0;
				ECode(HT->root(), code, j);
			}
			break; }
		default:break;
		}
		menu();
		cin >> key;
	}
	return 0;
}

void menu()
{
	cout << "----------------------------------------------------------" << endl;
	cout << "                 ��������ı�/����ϵͳ�˵�                " << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "I.��ʼ����������" << endl;
	cout << "E.���ļ����б���" << endl;
	cout << "D.���ļ���������" << endl;
	cout << "P.��ӡ�����ļ�" << endl;
	cout << "T.��ӡ��������" << endl;
	cout << "S.�����������" << endl;
	cout << "Q.�˳�" << endl;
}
