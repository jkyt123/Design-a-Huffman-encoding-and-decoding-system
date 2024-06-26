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
//叶
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
//内部结点
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
//哈夫曼树
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

//比较
template <typename E>
class minTreeComp {
public:
	static bool prior(HuffTree<E>* x, HuffTree<E>* y) { return x->weight() < y->weight(); }
};

//建树，返回哈夫曼树
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
//打印凹入表并存储
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

//编码，遍历加0，1
//root是哈夫曼树的根结点，C是存储编码类指针（数组），n用为C的下标
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
	if (root->left()->isLeaf()) {//返回前是叶结点则除前一个的最后码，前面都相同
		int i = C[n - 1].length();
		int j;
		for (j = 0; j < i - 1; j++) {
			C[n].setCo(C[n].getCo() + C[n - 1].getCo()[j]);
		}
	}
	else {//返回前内结点向左子树走再循环向右子树（字符从左到右，上个在右边的非叶结点）
		  //走直到找到叶结点，并记下进入次数，除最后[进入次数+2]前面都相同
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
//获得进入次数
template <typename E>
int getN(HuffNode<E>* root) {
	int k = 2;//次数+2
	HuffNode<E>* temp=root;
	while (!temp->right()->isLeaf())
	{
		k++;
		temp = temp->right();
	}
	return k;
}