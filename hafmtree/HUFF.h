#pragma once
#include "HEAP.h"
#include "CODE.h"
#include <iostream>
template <typename E>class HuffNode {
public:
	virtual ~HuffNode() {};
	virtual int weight() = 0;
	virtual bool isLeaf() = 0;
	virtual HuffNode<E>* left()const = 0;
	virtual HuffNode<E>* right()const = 0;
	virtual E val() = 0;
};
//Ҷ
template<typename E>
class LeafNode :public HuffNode<E> {
private:
	E it;
	int wgt;
public:
	LeafNode(const E& val, int freq) {
		it = val; wgt = freq;
	}
	int weight() { return wgt; }
	E val() {
		return it;
	}
	bool isLeaf() { return true; }
	HuffNode<E>* left()const { return nullptr; }
	HuffNode<E>* right()const { return nullptr; }
};
//�ڲ����
template<typename E>
class IntlNode :public HuffNode<E> {
private:
	HuffNode<E>* lc;
	HuffNode<E>* rc;
	int wgt;
public:
	IntlNode(HuffNode<E>* l, HuffNode<E>* r) {
		wgt = l->weight()+r->weight();
		lc = l;
		rc = r;
	}
	int weight() { return wgt; }
	bool isLeaf() { return false; }
	HuffNode<E>* left()const { return lc; }
	void setLeft(HuffNode<E>* b) {
		lc = (HuffNode<E>*)b;
	}
	HuffNode<E>* right()const { return rc; }
	void setRight(HuffNode<E>* b) {
		rc = (HuffNode<E>*)b;
	}
	E val() { return 0; }
};
//��������
template <typename E>
class HuffTree {
private:
	HuffNode<E>* Root;
public:
	HuffTree() {}
	HuffTree(E& val,int freq) {
		Root = new LeafNode<E>(val, freq);
	}
	HuffTree(HuffTree<E>* l, HuffTree<E>* r) {
		Root = new IntlNode<E>(l->root(), r->root());
	}
	~HuffTree() {}
	HuffNode<E>* root() {return Root;}
	int weight() { return Root->weight(); }
};

//�Ƚ�
template <typename E>
class minTreeComp {
public:
	static bool prior(HuffTree<E>* x, HuffTree<E>* y) { return x->weight() < y->weight(); }
};

//���������ع�������
template <typename E>HuffTree<E>*
buildHuff(HuffTree<E>** TreeArray, int count) {
	heap<HuffTree<E>*, minTreeComp<E>>* forest =
		new heap<HuffTree<E>*, minTreeComp<E>>(TreeArray, count, count);
	HuffTree<char> *temp1, *temp2, *temp3 = nullptr;
	while (forest->size() > 1) {
		temp1 = forest->removefirst();
		temp2 = forest->removefirst();
		temp3 = new HuffTree<E>(temp1, temp2);
		forest->insert(temp3);
		delete temp1;
		delete temp2;
	}
	return temp3;
}
;
//��ӡ������洢
template <typename E>
void showT(HuffNode<E>* root ,string ss,string& sto) {
	if (root == nullptr)return;
	ss += "  ";
	showT(root->left(), ss, sto);
	std::cout << ss;
	sto += ss;
	if (root->isLeaf())
	{
		std::cout << root->val() << '|';
		sto = sto + root->val() + "|";
	}
	std::cout << root->weight() << endl;
	sto = sto + to_string(root->weight()) + "\n";
	showT(root->right(), ss, sto);
}

//���룬������0��1
//root�ǹ��������ĸ���㣬C�Ǵ洢������ָ�루���飩��n��ΪC���±�
template <typename E>
void ECode(HuffNode<E>* root, CODE<E>* C,int &n) {
	if (root == nullptr)return;	
	if (root->isLeaf()) {
		C[n].setVa(root->val());
		n++;
		return;
	}
	if (root->left() != nullptr)C[n].setCo(C[n].getCo() + "0");
	ECode(root->left(), C, n);
	if (root->left()->isLeaf()) {//����ǰ��Ҷ������ǰһ��������룬ǰ�涼��ͬ
		int i = C[n - 1].length();
		int j;
		for (j = 0; j < i - 1; j++) {
			C[n].setCo(C[n].getCo() + C[n - 1].getCo()[j]);
		}
	}
	else {//����ǰ�ڽ��������������ѭ�������������ַ������ң��ϸ����ұߵķ�Ҷ��㣩
		  //��ֱ���ҵ�Ҷ��㣬�����½�������������[�������+2]ǰ�涼��ͬ
		int i = C[n - 1].length();
		int j;
		int k = getN(root->left());
		for (j = 0; j < i - k; j++) {
			C[n].setCo(C[n].getCo() + C[n - 1].getCo()[j]);
		}
	}
	if (root->right() != nullptr)C[n].setCo(C[n].getCo() + "1");
	ECode(root->right(), C, n);
}
//��ý������
template <typename E>
int getN(HuffNode<E>* root) {
	int k = 2;//����+2
	HuffNode<E>* temp=root;
	while (!temp->right()->isLeaf())
	{
		k++;
		temp = temp->right();
	}
	return k;
}