#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class node
{
protected:
    int _times = 0;
    char _value;
    node *_left = NULL;
    node *_right = NULL;

public:
    node() {}
    node(int times) : _times(times) {}
    node(int times, char value) : _times(times), _value(value) {}
    int get_times()
    {
        return _times;
    }
    char get_value()
    {
        return _value;
    }
    node *get_left()
    {
        return this->_left;
    }
    node *get_right()
    {
        return this->_right;
    }

    void set_left(node *left)
    {
        this->_left = left;
    }
    void set_right(node *right)
    {
        this->_right = right;
    }
    void set_times(int times)
    {
        this->_times = times;
    }
    void set_value(char value)
    {
        this->_value = value;
    }
    ~node() { delete this; }
};

class tree : public node
{
private:
    node *_root = NULL;
    int height = 0;

public:
    tree(node *root) : _root(root) {}
    void set_root(node *root)
    {
        this->_root = root;
    }
    node *get_root()
    {
        return this->_root;
    }
    void *combine_nodes(node *node1)
    {
        node *parent = new node(this->get_root()->get_times() + node1->get_times());
        parent->set_left(this->get_root());
        parent->set_right(node1);
        this->set_root(parent);
        return this;
    }
    void DFS_for_preorder(node *n)
    {
        if (n == NULL)
            return;
        cout << n->get_times() << " ";
        if (n->get_left() != NULL)
            this->DFS_for_preorder(n->get_left());
        if (n->get_right() != NULL)
            this->DFS_for_preorder(n->get_right());
    }
    void preorder()
    {
        node *head = this->get_root();
        this->DFS_for_preorder(head);
        cout << endl;
    }
    void DFS_for_inorder(node *n)
    {
        if (n == NULL)
            return;
        if (n->get_left() != NULL)
            this->DFS_for_preorder(n->get_left());
        cout << n->get_times() << " ";
        if (n->get_right() != NULL)
            this->DFS_for_preorder(n->get_right());
    }
    void inorder()
    {
        node *head = this->get_root();
        this->DFS_for_inorder(head);
        cout << endl;
    }
    ~tree() { delete this; }
};

int find(vector<pair<int, char>> nodes, char s)
{
    for (int i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i].second == s)
            return i;
    }
    return -1;
}

int main()
{
    vector<pair<int, char>> nodes;
    string s;
    getline(cin, s);
    for (int i = 0; i < s.size(); ++i)
    {
        int flag = find(nodes, s[i]);
        if (flag == -1)
        {
            nodes.push_back(make_pair(1, s[i]));
        }
        else
        {
            nodes[flag].first++;
        }
    }
    sort(nodes.begin(), nodes.end(), [](pair<int, char> p1, pair<int, char> p2)
         { return p1.first < p2.first; });
    vector<tree *> sub_tree;
    for (auto i : nodes)
    {
        tree *head = new tree(new node(i.first, i.second));
        sub_tree.push_back(head);
    }
    while (sub_tree.size() > 1)
    {
        sub_tree[0]->combine_nodes(sub_tree[1]->get_root());
        sub_tree.erase(sub_tree.begin() + 1);
        sort(sub_tree.begin(), sub_tree.end(), [](tree *t1, tree *t2)
             { return t1->get_times() < t2->get_times(); });
    }
    sub_tree[0]->preorder();
    sub_tree[0]->inorder();
    return 0;
}