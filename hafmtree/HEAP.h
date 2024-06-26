#pragma once
template <typename E, typename Comp>class heap {
private:
	E * Heap;
	int maxsize;
	int n;
	void siftdown(int pos) {
		while (!isLeaf(pos)) {
			int j = leftchild(pos);
			int rc = rightchild(pos);
			if ((rc < n) && Comp::prior(Heap[rc], Heap[j]))
				j = rc;
			if (Comp::prior(Heap[pos], Heap[j]))return;
			swap(Heap, pos, j);
			pos = j;
		}
	}
public:
	heap(E* h, int num, int max) {
		Heap = h; n = num; maxsize = max; buildHeap();
	}
	int size()const { return n; }
	bool isLeaf(int pos)const
	{
		return (pos >= n / 2) && (pos < n);
	}
	int leftchild(int pos)const {
		return 2 * pos + 1;
	}
	int rightchild(int pos)const {
		return 2 * pos + 2;
	}
	int parent(int pos)const {
		return (pos - 1) / 2;
	}
	void buildHeap() {
		for (int i = n / 2 - 1; i >= 0; i--)siftdown(i);
	}
	void insert(const E& it) {
		int curr = n++;
		Heap[curr] = it;
		while ((curr != 0) &&
			(Comp::prior(Heap[curr], Heap[parent(curr)]))) {
			swap(Heap, curr, parent(curr));
			curr = parent(curr);
		}
	}
	E removefirst() {
		swap(Heap, 0, --n);
		if (n != 0)siftdown(0);
		return Heap[n];
	}
	E remove(int pos) {
		if (pos == (n - 1))n--;
		else {
			swap(Heap, pos, --n);
			while ((pos != 0) &&
				(Comp::prior(Heap[pos], Heap[parent(pos)]))) {
				swap(Heap, pos, parent(pos));
				pos = parent(pos);
			}
			if (n != 0)siftdown(pos);
		}
		return Heap[n];
	}
	void swap(E* H, int m, int n) {
		E temp;
		temp = H[m];
		H[m] = H[n];
		H[n] = temp;
	}
};