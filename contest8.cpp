#include <iostream>
#include <ostream>
#include <string>

struct Node
{
    int value;
    Node *left;
    Node *right;
};
using Tree = Node *;

namespace list
{

struct ListNode
{
    Tree value;
    ListNode *next;
};

using List = ListNode *;

inline List cons(Tree const value, List const next)
{
    ListNode * const node = static_cast<ListNode *>(std::malloc(sizeof(ListNode)));
    node->value = value;
    node->next = next;
    return node;
}
inline List prepend(ListNode * const head, List const tail)
{
    head->next = tail;
    return head;
}

struct ListUncons
{
    ListNode *head;
    List tail;
};
inline ListUncons uncons(List const list)
{
    return {list, list->next};
}

inline void destroy(List const list)
{
    if(list != nullptr)
    {
        auto const [x, xs] = uncons(list);
        std::free(x);
        destroy(xs);
    }
}

inline unsigned int length(List const list)
{
    return list == nullptr
        ? 0u
        : 1u + length(list->next);
}
inline List reverse(List list)
{
    List accum = nullptr;
    while(list != nullptr)
    {
        auto const [x, xs] = uncons(list);
        accum = prepend(x, accum);
        list = xs;
    }
    return accum;
}
inline List concat(List const left, List const right)
{
    if(left == nullptr)
        return right;

    ListNode *last = left;
    while(last->next != nullptr)
        last = last->next;
    last->next = right;
    return left;
}

struct Iterator
{
    ListNode *node;

    Iterator &operator++(   ) {                      node = node->next; return *this;}
    Iterator  operator++(int) {ListNode *tmp = node; node = node->next; return {tmp};}

    bool operator!=(Iterator const &other) const {return node != other.node;}
    bool operator==(Iterator const &other) const {return node == other.node;}

    Tree &operator* () const {return  node->value;}
    Tree *operator->() const {return &node->value;}
};

inline Iterator begin(List const list) {return {   list};}
inline Iterator   end(List           ) {return {nullptr};}

} // namespace list

Tree cons(Tree left, int value, Tree right){
	Tree nd = static_cast<Tree>(std::malloc(sizeof(Node)));
	nd -> value = value;
	nd -> left = left;
	nd -> right = right;
	return nd;
}

std::ostream &printTree(std::ostream &out, Tree const tree, bool right, std::string const &prefix)
{
    if(tree != nullptr)
    {
        out << prefix << (right ? "└──" : "├──" ) << tree->value << std::endl;
        printTree(out, tree->left, false, prefix + (right ? "    " : "│   "));
        printTree(out, tree->right, true, prefix + (right ? "    " : "│   "));
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, Tree const tree)
{
    return printTree(out, tree, true, "");
}

void destroyTree(Tree tree){
	if(tree != nullptr){
		destroyTree(tree->left);
		destroyTree(tree->right);
		std::free(tree);
	}
}

Tree createTree(int const *begin, int const *end){
	if(end == begin){
		return nullptr;
	}else if(end - begin == 1){
		return cons(nullptr, *begin, nullptr);
	}else{
		int const * const mid = begin + (end - begin) / 2;
		return cons(createTree(begin, mid), *mid, createTree(mid+1, end));
	}
}

unsigned int treeSize(Tree tree){
	if(tree == nullptr){
		return 0;
	}
	return 1 + treeSize(tree->left) + treeSize(tree->right);
}

unsigned int treeDepth(Tree tree){
	if(tree == nullptr){
		return 0;
	}
	int lnleft = treeDepth(tree->left);
	int lnright = treeDepth(tree->right);
	if(lnleft > lnright){
		return 1 + lnleft;
	}else{
		return 1 + lnright;
	}
}

list::List preorder(Tree tree){
	if(tree == nullptr){
		return nullptr;
	}
	return list::cons(tree, list::concat(preorder(tree->left), preorder(tree->right)));
}

list::List  inorder(Tree tree){
	if(tree == nullptr){
		return nullptr;
	}
	return list::concat(inorder(tree->left), cons(tree, inorder(tree->right)));
}

int min(Tree tree){
	if(tree->left == nullptr){
		return tree->value;
	}
	return min(tree->left);
}

int max(Tree tree){
	if(tree->right == nullptr){
		return tree->value;
	}
	return max(tree->right);
}

Node const *find(int n, Tree tree){
	if(tree == nullptr){
		return nullptr;
	}
	if(tree->value == n){
		return tree;
	}
	if(n > tree->value){
		return find(n, tree->right);
	}else{
		return find(n, tree->left);
	}
}

Tree insert(int n, Tree tree){
	if(tree == nullptr){
		return cons(nullptr, n, nullptr);
	}
	if(n == tree->value){
	}else if(n > tree->value){
		tree->right = insert(n, tree->right);
	}else{
		tree->left = insert(n, tree->left);
	}
	return tree;
}

Tree insert(Node *nd, Tree tree){
	if(tree == nullptr){
		nd->left = nullptr;
		nd->right = nullptr;
		return nd;
	}
	if(nd->value == tree->value){
		std::free(nd);
	}else if(nd->value > tree->value){
		tree->right = insert(nd, tree->right);
	}else{
		tree->left = insert(nd, tree->left);
	}
	return tree;
}

Tree merge(Tree left, Tree right){
	list::List lst = preorder(right);
	for(list::ListNode *nd = lst; nd != nullptr; nd = nd->next){
		left = insert(nd->value, left);
	}
	list::destroy(lst);
	return left;
}

int main(){
	int rng1[] = {0, 2, 3, 4, 6, 8, 10};
	int rng2[] = {1, 5, 7, 8, 10};

	Tree left = createTree(rng1, rng1+7);
	Tree right = createTree(rng2, rng2+5);

	std::cout << left << std::endl;
	std::cout << right << std::endl;

	Tree tree = merge(left, right);

	std::cout << tree << std::endl;

	list::List ls = inorder(tree);
	for(list::ListNode *nd = ls; nd != nullptr; nd = nd->next){
		std::cout << nd->value->value << " ";
	}
	std::cout << std::endl;
	destroyTree(tree);
//	destroyTree(left);
//	destroyTree(right);
	list::destroy(ls);
}
