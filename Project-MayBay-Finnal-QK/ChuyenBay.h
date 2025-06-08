#pragma once
#include "DayTime.h"
#include "MayBay.h"
struct Ticket
{
    char CCCD[14];
    int Status; // So cho
};
// 0: hủy chuyến, 1: còn vé, 2: hết vé,3: hoàn tất;
struct ChuyenBay
{
    char MaCB[10];
    char SanBayDen[20];
    char SoHieuMB[15];
    int TrangThai;
    DayTime TimeDi;
    int SoVe;

    Ticket *TicketList;
    int TongSoDaBan;
};

struct NodeCB
{
    ChuyenBay Data;
    NodeCB *next = NULL;
};

typedef NodeCB *PTRCB;
struct ListCB
{
    PTRCB First;
    PTRCB Last;
    int SoLuongCB;
};

int TrangHienTaiCB = 1;
int TongSoTrangCB = 0;

int CurPosTicket = 1;
int CurPosPreTicket = 1;

void InitChuyenBay(ChuyenBay &cb)
{
    cb.SoVe = 0;
    cb.TongSoDaBan = 0;
    cb.TicketList = new Ticket[100]; // cap phat mang dong
    cb.TrangThai = 1;                // 0: hủy chuyến, 1: còn vé, 2: hết vé,3: hoàn tất ;
}

void InitListCB(ListCB &LCB)
{
    LCB.First = NULL;
    LCB.Last = NULL;
    LCB.SoLuongCB = 0;
}

PTRCB TaonodeCB(ChuyenBay &cb)
{
    PTRCB temp = new NodeCB;
    if (temp == NULL)
    {
        return NULL;
    }
    temp->Data = cb;
    temp->next = NULL;
    return temp;
}

void InsertEnd(ListCB &LCB, ChuyenBay cb)
{
    PTRCB tmp = TaonodeCB(cb);
    if (LCB.First == NULL)
    {
        LCB.First = LCB.Last = tmp;
    }
    else
    {
        LCB.Last->next = tmp;
        LCB.Last = tmp;
    }
    LCB.SoLuongCB++;
}

void InsertOrder(ListCB &LCB, ChuyenBay cb)
{
    PTRCB p, t, s;
    p = TaonodeCB(cb);
    for (s = LCB.First; s != NULL && strcmp(s->Data.MaCB, p->Data.MaCB) < 0; t = s, s = s->next)
        ;
    if (s == LCB.First)
    {
        p->next = LCB.First;
        LCB.First = p;
    }
    else
    {
        p->next = s;
        t->next = p;
    }
    LCB.SoLuongCB++;
}

int ViTriCB(ListCB LCB, const char *MaCB)
{
    int vt = 0;
    for (PTRCB p = LCB.First; p != NULL; p = p->next)
    {
        if (strcmp(p->Data.MaCB, MaCB) == 0)
        {
            return vt;
        }
        vt++;
    }
    return -1;
}

int ViTriSBDen(ListCB LCB, const char *SBDen)
{
    int vt = 0;
    for (PTRCB p = LCB.First; p != NULL; p = p->next)
    {
        if (strcmp(p->Data.SanBayDen, SBDen) == 0)
        {
            return vt;
        }
        vt++;
    }
    return -1;
}

PTRCB TimCB(ListCB LCB, const char *MaCB)
{
    if (LCB.First == NULL)
    {
        return NULL;
    }
    for (PTRCB p = LCB.First; p != NULL; p = p->next)
    {
        if (strcmp(p->Data.MaCB, MaCB) == 0)
        {
            return p;
        }
    }
    return NULL;
}

// Rang buoc xoa may bay khi chuyen bay da thuc hien
PTRCB TimCBTheoSHMB(ListCB LCB, const char *SHMB)
{
    for (PTRCB p = LCB.First; p != NULL; p = p->next)
    {
        if (strcmp(p->Data.SoHieuMB, SHMB) == 0)
        {
            return p;
        }
    }
    return NULL;
}

// giai phong bo nho
void CleanUpFlightList(ListCB &LCB)
{
    PTRCB p;
    while (LCB.First != NULL)
    {
        p = LCB.First;
        LCB.First = LCB.First->next;
        // delete[] p->Data.TicketList;
        delete p;
    }
    LCB.First = LCB.Last = NULL;
    LCB.SoLuongCB = 0;
}

void TuDongCapNhatTrangThai(ListCB &LCB)
{
    for (PTRCB p = LCB.First; p != NULL; p = p->next)
    {
        if (DateTimeIsValid(p->Data.TimeDi) == false && p->Data.TrangThai != 0)
            // 0: hủy chuyến, 1: còn vé, 2: hết vé,3: hoàn tất ;
            p->Data.TrangThai = 3;
    }
}

int CheckOut(ChuyenBay cb, int x)
{
    for (int i = 0; i < cb.TongSoDaBan; i++)
    {
        if (x == cb.TicketList[i].Status)
        {
            return 1;
        }
    }
    return 0;
}

void CopyListCB(ListCB &LCB, ListCB &tmp)
{
    if (tmp.First != NULL)
    {
        CleanUpFlightList(tmp);
    }
    tmp.First = tmp.Last = NULL;
    tmp.SoLuongCB = 0;

    for (PTRCB p = LCB.First; p != NULL; p = p->next)
    {
        PTRCB NodeCP = TaonodeCB(p->Data);
        if (tmp.First == NULL)
        {
            tmp.First = tmp.Last = NodeCP;
        }
        else
        {
            tmp.Last->next = NodeCP;
            tmp.Last = NodeCP;
        }
        tmp.SoLuongCB++;
    }
}

void CopyListCBCV(ListCB &LCB, ListCB &tmp)
{
    if (tmp.First != NULL)
    {
        CleanUpFlightList(tmp);
    }
    tmp.First = tmp.Last = NULL;
    tmp.SoLuongCB = 0;

    for (PTRCB p = LCB.First; p != NULL; p = p->next)
    {
        if (p->Data.TrangThai == 1)
        {
            PTRCB NodeCP = TaonodeCB(p->Data);
            if (tmp.First == NULL)
            {
                tmp.First = tmp.Last = NodeCP;
            }
            else
            {
                tmp.Last->next = NodeCP;
                tmp.Last = NodeCP;
            }
            tmp.SoLuongCB++;
        }
    }
}

void CopyListCBDD(ListCB &LCB, ListCB &tmp, string dd)
{
    if (tmp.First != NULL)
    {
        CleanUpFlightList(tmp);
    }
    tmp.First = tmp.Last = NULL;
    tmp.SoLuongCB = 0;

    for (PTRCB p = LCB.First; p != NULL; p = p->next)
    {
        if (strcmp(p->Data.SanBayDen, dd.c_str()) == 0 && (p->Data.TrangThai == 1 || p->Data.TrangThai == 2))
        {
            PTRCB NodeCP = TaonodeCB(p->Data);
            if (tmp.First == NULL)
            {
                tmp.First = tmp.Last = NodeCP;
            }
            else
            {
                tmp.Last->next = NodeCP;
                tmp.Last = NodeCP;
            }
            tmp.SoLuongCB++;
        }
    }
}

void SelectionSortCB(ListCB &LCB)
{
    PTRCB p, q, pmin;
    ChuyenBay min;
    if (LCB.First == NULL)
        return;
    for (p = LCB.First; p->next != NULL; p = p->next)
    {
        min = p->Data;
        pmin = p;
        for (q = p->next; q != NULL; q = q->next)
        {
            if (strcmp(q->Data.MaCB, min.MaCB) < 0)
            {
                min = q->Data;
                pmin = q;
            }
        }
        pmin->Data = p->Data;
        p->Data = min;
    }
}

bool Check_HK_SanSangBay(ListCB LCB, ChuyenBay &cb, const char *CCCD)
{
    for (PTRCB p = LCB.First; p != NULL; p = p->next)
    {
        if (TrongVongBaGio(p->Data.TimeDi, cb.TimeDi) && p->Data.TrangThai != 0 && p->Data.MaCB != cb.MaCB)
        {
            for (int i = 0; i < p->Data.TongSoDaBan; i++)
            {
                if (strcmp(p->Data.TicketList[i].CCCD, CCCD) == 0)
                {
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << "Hanh Khach Khong The";
                    gotoxy(X_Notification, Y_Notification + 4);
                    cout << "Dat Ve Do Da Dat Ve";
                    gotoxy(X_Notification, Y_Notification + 5);
                    cout << "Chuyen Bay " << p->Data.MaCB;
                    gotoxy(X_Notification, Y_Notification + 6);
                    cout << "Khoi Hanh Luc: ";
                    gotoxy(X_Notification, Y_Notification + 7);
                    OutputDateTime(p->Data.TimeDi);
                    return false;
                }
            }
        }
    }
    return true;
}
bool Check_MB_Moi(ListCB LCB, ChuyenBay &cb)
{
    for (PTRCB p = LCB.First; p != NULL; p = p->next)
    {
        if (TrongVongBaGio(p->Data.TimeDi, cb.TimeDi) && strcmp(p->Data.SoHieuMB, cb.SoHieuMB) == 0 && p->Data.TrangThai != 0 && strcmp(p->Data.MaCB, cb.MaCB) != 0)
        {
            gotoxy(X_Notification, Y_Notification + 2);
            cout << "May bay dang thuc";
            gotoxy(X_Notification, Y_Notification + 3);
            cout << "hien chuyen bay ";
            gotoxy(X_Notification, Y_Notification + 4);
            cout << "khac co ma " << p->Data.MaCB;
            return false;
        }
    }
    return true;
}