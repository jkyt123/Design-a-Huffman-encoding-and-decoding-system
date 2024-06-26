#include "HUFF.h"//哈夫曼树类的头文件
#include "CODE.h"//哈夫曼树的编码存储类
#include<fstream>
#include<iostream>
using namespace std;
int main()
{	
	void menu();
	menu();

	CODE<char>* code = nullptr;//用于存储树的编码
	HuffTree<char>* HT = nullptr;//用于存储哈夫曼树
	int num = 0;//元素个数
	char key;//选择菜单
	cin >> key;
	while (key != 'Q'&&key!='q') {
		switch (key) {
		case 'I'://初始化与存储
		case'i':
		{
			ofstream outfile("hfmTree.dat", ios::out | ios::trunc);//存储哈夫曼树
			if (!outfile) {
				cout << "hfmTree.dat文件打不开" << endl;
				break;
			}
			num = 0;
			int i = 0;
			char key2;//字符
			int weight;//权值
			int count;//用于计数
			int n;//存储元素长度
			string saveT;//用于存储元素
			while (num < 3) {//哈夫曼树元素>=3个
				cout << "输入字符集大小x:(x>=3)" << endl;
				cin >> num;
			}
			saveT = to_string(num)+ " ";//存储元素个数。“ ”区分单个元素
			count = num;
			cout << "输入字符和权值:" << endl;
			HuffTree<char> **HFT=new HuffTree<char>*[num];
			for (i = 0; i<num; i++)
				HFT[i] = new HuffTree<char>();
			                         //建数Tree组用于建哈夫曼树的buildHuff（）函数
			while (count > 0) {//循环对数Tree组赋值。count计数
				cin >> key2;
				cin >> weight;
				HuffTree<char> T(key2, weight);//初始化数Tree
				saveT = saveT + key2 +" "+ to_string(weight) + " ";
				**(HFT+num-count) = T;//组赋值
				count--;
			}
			n = saveT.length();
			for (i = 0; i < n; i++)
				outfile.put(saveT[i]);//循环写入文件
			outfile.close();
			HT=buildHuff(HFT, num);//建哈夫曼树赋值到HT
			code = new CODE<char>[num];
			int j = 0;
			ECode(HT->root(), code, j);//树编码
		break; }
		case 'E'://编码
		case 'e':
		{
			if (HT == nullptr)cout << "当前没有哈夫曼树" << endl;
			else {
				char ch;//读文件字符
				string s="";//存文件字符串
				int i;//循环计数
				ifstream infile("ToBeTran.dat", ios::in );
				                              //读待编码文件
				if (!infile) { 
					cout << "ToBeTran.dat文件打不开" << endl;
					break;
				}
				ofstream outfile("CodeFile.dat", ios::out| ios::trunc);
				                              //存储编码后文件
				if (!outfile) {
					cout << "CodeFile.dat文件打不开" << endl;
					break;
				}
				while (infile.get(ch))//读字符
					for (i = 0; i < num; i++) //循环与树的字符进行比较
						if (ch == code[i].getVa())
							s = s + code[i].getCo() + " ";
				                            //若字符存在对文件进行编码
				int n = s.length();
				for (i = 0; i < n; i++)
					outfile.put(s[i]);//存储编码文件
				infile.close();
				outfile.close();
			}
			break; }
		case 'D'://译码
		case 'd':
		{
			if (HT == nullptr)cout << "当前没有哈夫曼树" << endl;
			else {
				int i;//循环计数
				char ch;//读文件字符
				string temp = "";//用于编码判断
				ifstream infile("CodeFile.dat", ios::in );
				                                       //读待译码文件
				if (!infile) {
					cout << "CodeFile.dat文件打不开" << endl;
					break;
				}
				ofstream outfile("TextFile.dat", ios::out | ios::trunc);
				if (!outfile) {
					cout << "TextFile.dat文件打不开" << endl;
					break;
				}
				while (infile.get(ch)) {
					if (ch != ' ')
						temp += ch;
					else {
						for (i = 0; i < num; i++)
							if (temp == code[i].getCo())//编码比较
								outfile.put(code[i].getVa());//是-》存储
						temp = "";
					}
				}
				infile.close();
				outfile.close();
			}
			break; }
		case 'P'://打印代码文件
		case 'p':
		{
			if (HT == nullptr)cout << "当前没有哈夫曼树" << endl;
			else {
				int i = 0;
				char ch;
				string temp = "";
				ifstream infile("CodeFile.dat", ios::in );
				if (!infile) {
					cout << "CodeFile.dat文件打不开" << endl;
					break;
				}
				ofstream outfile("CodePrint.dat", ios::out | ios::trunc);
				if (!outfile) {
					cout << "CodePrint.dat文件打不开" << endl;
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
		case 'T'://打印哈夫曼树
		case 't':
		{
			if (HT == nullptr)cout << "当前没有哈夫曼树" << endl;
			else {
				ofstream outfile("TreePrint.dat", ios::out | ios::trunc);
				if (!outfile) {
					cout << "TreePrint.dat文件打不开" << endl;
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
		case 'S'://载入哈夫曼
		case 's':
		{
			if (HT != nullptr)cout << "当前已初始化哈夫曼树" << endl;
			else {
				char ch;//读文件字符
				char key3;//字符
				int weight;//权重
				int i;//循环计数
				string N;//权重
				int count = 0;
				int ct2 = 0;
				HuffTree<char> **HFT = nullptr;
				ifstream infile("hfmTree.dat", ios::in );
				if (!infile) {
					cout << "hfmTree.dat文件打不开" << endl;
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
	cout << "                 哈夫曼码的编/译码系统菜单                " << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "I.初始化哈夫曼树" << endl;
	cout << "E.对文件进行编码" << endl;
	cout << "D.对文件进行译码" << endl;
	cout << "P.打印代码文件" << endl;
	cout << "T.打印哈夫曼树" << endl;
	cout << "S.载入哈夫曼树" << endl;
	cout << "Q.退出" << endl;
}
