#include <iostream>

struct Node
{
    int value;
    Node *next;
};

Node *createNode(int num, Node *next){
	Node *nd = static_cast<Node *>(std::malloc(sizeof(Node)));
	nd->value = num;
	nd->next = next;
	return nd;
}

void  deleteNode(Node *nd){
	std::free(nd);
}

using List = Node *;

List cons(int i, List list){
	List nd = createNode(i, list);
	return nd;
}

List prepend(Node *node, List list){
	node->next = list;
	return node;
}

struct ListUncons
{
    Node *head;
    List tail;
};

ListUncons uncons(List lst){
	return {lst, lst->next};
}

void destroyList(List lst){
	if(lst != nullptr){
		ListUncons unc = uncons(lst);
		destroyList(unc.tail);
		deleteNode(unc.head);
	}
}

struct IntConstRange
{
    int const *begin;
    int const *  end;
};

List createList(IntConstRange range){
	Node *nd = createNode(range.end[-1], nullptr);
	for(int i = 0; i < range.end - range.begin - 1; i++){
		nd = cons(range.end[-2-i], nd);
	}
	return nd;
}

unsigned int listLength(List lst){
	unsigned int len = 0;
	for(Node *nd = lst; nd != nullptr; nd = nd->next){
		len++;
	}
	return len;
}

Node *listNth(List lst, unsigned int n){
	Node *nd = lst;
	for(unsigned int i = 0; i < n; i++){
		if(nd == nullptr)
			return nullptr;
		nd = nd->next;
	}
	return nd;
}

List reverseList(List lst){
	List rev = nullptr;
	for(Node *nd = lst; nd != nullptr;){
		ListUncons unc = uncons(nd);
		rev = prepend(unc.head, rev);
		nd = unc.tail;
	}
	return rev;
}

/*
List mergeList(List lst1, List lst2){
	List res = nullptr;
	
	Node *nd1 = lst1;
	Node *nd2 = lst2;

	while(nd1 != nullptr || nd2 != nullptr){
		if(nd1->value > nd2->value || nd1 == nullptr){
			ListUncons unc = uncons(nd2);
			res = prepend(unc.head, res);
			nd2 = unc.tail;
		}else{
			ListUncons unc = uncons(nd1);
			res = prepend(unc.head, res);
			nd1 = unc.tail;
		}
	}

	return res;
}*/

List mergeList(List lst1, List lst2){
	if(lst1 == nullptr){
		return lst2;
	}else if(lst2 == nullptr){
		return lst1;
	}else if(lst1->value < lst2->value){
		return prepend(lst1, mergeList(lst1->next, lst2));
	}else{
		return prepend(lst2, mergeList(lst2->next, lst1));
	}
}

List concatList(List left, List right){
	if(left == nullptr){
		return right;
	}

	List last = left;
	while(last->next != nullptr){
		last = last->next;
	}
	last->next = right;
	return left;
}

struct ListIterator
{
    Node *node;

    ListIterator &operator++(   ) {                  node = node->next; return *this;}
    ListIterator  operator++(int) {Node *tmp = node; node = node->next; return {tmp};}
    bool operator!=(ListIterator const &other) const {return node != other.node;}
    bool operator==(ListIterator const &other) const {return node == other.node;}
    int &operator* () const {return  node->value;}
    int *operator->() const {return &node->value;}
};

ListIterator begin(List lst){
	return {lst};
}

ListIterator   end(List){
	return {nullptr};
}

ListIterator next(ListIterator it, int n = 1){
	for(int i = 0; i < n; i++){
		it++;
	}
	return it;
}

int distance(ListIterator first, ListIterator last){
	int len = 0;
	while(first != last){
		first++;
		len++;
	}
	return len;
}

void iter_swap(ListIterator it1, ListIterator it2){
	int tmp = it1.node->value;
	it1.node->value = it2.node->value;
	it2.node->value = tmp;
}

ListIterator find(ListIterator first, ListIterator last, int n){
	List nd = first.node;
	while(nd != last.node){
		if(nd->value == n){
			return {nd};
		}
		nd = nd->next;
	}
	return {nd};
}

ListIterator min_element(ListIterator first, ListIterator last){
	List nd = first.node;
	List mn = first.node;

	while(nd != last.node){
		if(nd->value < mn->value){
			mn = nd;
		}
		nd = nd->next;
	}
	return {mn};
}

void selection_sort(ListIterator first, ListIterator last){
	for(List nd = first.node; nd != last.node; nd = nd->next){
		iter_swap({nd}, min_element({nd}, last));
	}
}

struct ListPair
{
    List first;
    List second;
};

bool less(int x, int y) {return x < y;}

bool neg(int x) {return x < 0;}

ListPair partition(List lst, auto unaryPredicate){
	List left = nullptr;
	List right = nullptr;
	List nd = lst;

	while(nd != nullptr){
		ListUncons unc = uncons(nd);
		if(unaryPredicate(nd->value)){
			left = prepend(unc.head, left);
//			std::cout << unc.head->value << " ";
		}else{
			right = prepend(unc.head, right);
//			std::cout << right->value << " ";
		}
		nd = unc.tail;
	}
	return {left, right};
}

List quicksort(List lst, auto compare){
	if(lst == nullptr){
		return lst;
	}
	auto pred = [y = lst->value, &compare](int x){return compare(x, y);};
	ListUncons unc = uncons(lst);
	ListPair pair = partition(unc.tail, pred);
	return concatList(quicksort(pair.first, compare), prepend(unc.head, quicksort(pair.second, compare)));
}

int main(){
	
	int rng1[] = {0, -3, -1, 4, -7, 0, -1, -7, 4, 7};

	List lst = createList({rng1, rng1 + 10});
	lst = quicksort(lst, less);
	
//	ListPair pair = partition(lst, neg);
//	List lst1 = pair.first;
//	List lst2 = pair.second;

	for(Node *node = lst; node != nullptr; node = node->next)
	    std::cout << node->value << ' ';
	std::cout << std::endl;
//	for(Node *node = lst2; node != nullptr; node = node->next)
//	    std::cout << node->value << ' ';
//	destroyList(lst1);
//	destroyList(lst2);
//	std::cout << listNth(lst, 4)->value << std::endl;
}
