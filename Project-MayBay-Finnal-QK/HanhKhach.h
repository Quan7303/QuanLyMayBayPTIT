#pragma once

struct HanhKhach
{
    char CCCD[14];
    char Ho[20];
    char Ten[10];
    int Phai;
};

struct Node
{
    HanhKhach Data;
    Node *Left;
    Node *Right;
};

typedef Node *Tree;

int TrangHienTaiHK = 1;
int TongSoTrangHK = 0;
int nPassenger;

void CreateTree(Tree &root)
{
    root = NULL;
    nPassenger = 0;
}

Tree NewNodeHK(HanhKhach &hk)
{
    Tree temp = new Node();
    temp->Data = hk;
    temp->Left = NULL;
    temp->Right = NULL;
    return temp;
}

void AddPassenger(Tree &root, HanhKhach hk)
{
    if (root == NULL)
    {
        root = NewNodeHK(hk);
    }
    if (strcmp(hk.CCCD, root->Data.CCCD) < 0)
    {
        AddPassenger(root->Left, hk);
    }
    else if (strcmp(hk.CCCD, root->Data.CCCD) > 0)
    {
        AddPassenger(root->Right, hk);
    }
}

Tree FindPassenger(Tree root, const char *CMNDcantim)
{
    Tree p;
    p = root;
    while (p != NULL && strcmp(CMNDcantim, p->Data.CCCD) != 0)
    {
        if (strcmp(CMNDcantim, p->Data.CCCD) < 0)
            p = p->Left;
        else
            p = p->Right;
    }
    return p;
}

void GiaiPhong(Tree &root)
{
    if (root == NULL)
        return;
    GiaiPhong(root->Left);
    GiaiPhong(root->Right);
    delete root;
    root = NULL;
}
