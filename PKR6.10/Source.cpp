#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

struct Node
{
    Node* left;
    Node* right;
    int info;
};

void Create(char* fname);
void Read(char* fname, Node*& root);
void Print(Node* root, int level);
void �ount(Node* root, int& r);
void Scaning(Node* root, int& rootinfo);
int Height(Node* root);
int BFactor(Node* root);
Node* Delete(Node* p, int value);
Node* Insert(Node* p, int value);
Node* RightRotation(Node* r);
Node* LeftRotation(Node* r);
Node* BalanceHeight(Node* r);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char fname[61];
    int choice;
    int r = 0;
    int rootinfo = 0;
    Node* root = NULL;

    do
    {
        cout << " [0] - ��������� ������" << endl;
        cout << " [1] - �������� ����" << endl;
        cout << " [2] - ������� ���������� � �����" << endl;
        cout << " [3] - ����������� ������ " << endl;
        cout << " [4] - �������� �����, �������� ���� � ������� �������" << endl << endl;
        cout << "������ ��������: "; cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            cin.get();
            cin.sync();
            cout << "������ ��� �����: "; cin.getline(fname, 61);
            Create(fname);
            break;
        case 2:
            cin.get();
            cin.sync();
            cout << "������ ��� �����: "; cin.getline(fname, 61);
            Read(fname, root);
            break;
        case 3:
            Print(root, 0);
            cout << endl;
            break;
        case 4:
            �ount(root, r);
            for (int i = 0; i < r; i++)
            {
                Scaning(root, rootinfo);
                root = Delete(root, rootinfo);
            }
            break;
        case 0:
            break;
        default:
            cout << "�� ����� ��������� ��������! "
                "��� ������ ����� - ����� ��������� ������ ����" << endl;
        }
    } while (choice != 0);

    return 0;
}

void Create(char* fname)
{
    ofstream fout(fname, ios::binary);// ������� ���� ��� ������
    if (!fout)
    {
        cerr << "�������!" << fname << "'" << endl;
        return;
    }
    int value, N;
    cout << "������ ������� �����: "; cin >> N;
    for (int i = 0; i < N; i++)
    {
        cout << "������ �������� ��� �����: "; cin >> value;
        fout.write((char*)&value, sizeof(value));
    }
    cout << endl;
}

void Read(char* fname, Node*& root)
{
    ifstream fin(fname, ios::binary);// ������� ���� ��� ����������
    if (!fin)
    {
        cerr << "�� ���� ����� " << fname << "'" << endl;
        return;
    }
    int value;
    while (fin.read((char*)&value, sizeof(value)))// ���� ����� ��������� ������
    {
        root = Insert(root, value);
    }
}

void Print(Node* root, int level)
{
    if (root != NULL)
    {
        Print(root->right, level + 1);
        for (int i = 1; i <= level; i++)
            cout << "   ";
        cout << root->info << endl;
        Print(root->left, level + 1);
    }
}

void �ount(Node* root, int& r)
{
    if (root != NULL)
    {
        �ount(root->right, r);
        if (!(root->info%2))
            r++;
        �ount(root->left, r);
    }
}

void Scaning(Node* root, int& rootinfo)
{
    if (root != NULL)
    {
        Scaning(root->right, rootinfo);
        if (!(root->info%2))
            rootinfo = root->info;
        Scaning(root->left, rootinfo);
    }
}

int Height(Node* root)
{
    if (root == NULL)
        return 0;

    int hL = Height(root->left);
    int hR = Height(root->right);

    return (hL > hR ? hL : hR) + 1;
}

int BFactor(Node* root)
{
    return Height(root->right) - Height(root->left);
}

Node* FindMin(Node* root)
{
    if (root->left != NULL)
        return FindMin(root->left);
    else
        return root;
}

Node* RightRotation(Node* p)
{
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    return q;
}

Node* LeftRotation(Node* q)
{
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    return p;
}

Node* BalanceHeight(Node* p)
{
    if (BFactor(p) == 2)
    {
        if (BFactor(p->right) < 0)
            p->right = RightRotation(p->right);
        return LeftRotation(p);
    }
    if (BFactor(p) == -2)
    {
        if (BFactor(p->left) > 0)
            p->left = LeftRotation(p->left);
        return RightRotation(p);
    }
    return p;
}

Node* Insert(Node* p, int value)
{
    if (!p)
    {
        p = new Node;
        p->info = value;
        p->left = NULL;
        p->right = NULL;
        return p;
    }
    if (value < p->info)
        p->left = Insert(p->left, value);
    else
        if (value > p->info)
            p->right = Insert(p->right, value);
    return BalanceHeight(p);
}

Node* Delete(Node* root, int value)
{
    if (NULL == root) return NULL;                          // �� ������� �����      

    if (root->info == value)                                // ������� �����  
    {
        if (NULL == root->left && NULL == root->right)      // �������� �����
        {
            delete root;
            return NULL;
        }

        if (NULL == root->right && root->left != NULL)      // ����� � ����� (����) ��������
        {                                                   
            Node* temp = root->left;
            delete root;
            return temp;
        }

        if (NULL == root->left && root->right != NULL)      // ����� � ����� (������) ��������
        {                                                   
            Node* temp = root->right;
            delete root;
            return temp;
        }
                                                           
        root->info = FindMin(root->left)->info;             // ����� � ����� ��������� 
        root->left = Delete(root->left, root->info);
        return root;
    }

    if (value < root->info)                                 // ����� � ����� �������
    {
        root->left = Delete(root->left, value);
        return root;
    }

    if (value > root->info)                                 // ����� � ������� �������
    {
        root->right = Delete(root->right, value);
        return root;
    }

    return root;
}