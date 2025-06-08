#pragma once
#include "BienToanCuc.h"

struct MayBay
{
    char SoHieuMB[15];
    char LoaiMB[40];
    int SoChoMB;
    int SoChuyenDaBay;
};
// Mang con tro MayBay
struct ListMayBay
{
    MayBay *DSMB[MaxAirplane];
    int SoLuong;
};

int TrangHienTaiMB = 1;
int TongSoTrangMB = 0;

void InitListMayBay(ListMayBay &dsmb)
{
    dsmb.SoLuong = 0;
    dsmb.DSMB[MaxAirplane]; //= {NULL}
}
// Tim kiem theo ma
int TimKiemMB(ListMayBay dsmb, const char *Ma)
{
    for (int i = 0; i < dsmb.SoLuong; i++)
    {
        if (stricmp(dsmb.DSMB[i]->SoHieuMB, Ma) == 0)
        {
            return i;
        }
    }
    return -1;
}

void ThemMB(ListMayBay &dsmb, MayBay mb)
{
    dsmb.DSMB[dsmb.SoLuong] = new MayBay;
    *dsmb.DSMB[dsmb.SoLuong] = mb;
    dsmb.SoLuong++;
}

// kiem tra xem may bay co nhap day du cac du lieu chua
bool AirplaneDataIsEmpty(MayBay *mb)
{
    /*false la nhap thieu - true la nhap du*/
    if (strlen(mb->SoHieuMB) == 0 || strlen(mb->LoaiMB) == 0 || mb->SoChoMB == 0)
    {
        return false;
    }
    return true;
}
// kiem tra xem da xoa may bay thanh cong chua

bool RemoveAirplaneIsSucceed(ListMayBay &dsmb, int ViTri)
{
    if (ViTri < 0)
    {
        return false;
    }
    delete dsmb.DSMB[ViTri];
    for (int j = ViTri + 1; j < dsmb.SoLuong; j++)
    {
        dsmb.DSMB[j - 1] = dsmb.DSMB[j];
    }
    dsmb.SoLuong--;
    return true;
}

void SwapMayBay(MayBay *&a, MayBay *&b)
{
    MayBay *temp = a;
    a = b;
    b = temp;
}

void CopyListMayBay(const ListMayBay &dsmb, ListMayBay &tmp)
{
    tmp.SoLuong = dsmb.SoLuong;
    for (int i = 0; i < dsmb.SoLuong; i++)
    {
        tmp.DSMB[i] = new MayBay;
        *tmp.DSMB[i] = *dsmb.DSMB[i];
    }
}

void BubbleSort(ListMayBay &dsmb)
{
    for (int i = 0; i < dsmb.SoLuong - 1; i++)
        for (int j = 0; j < dsmb.SoLuong - i - 1; j++)
            if (dsmb.DSMB[j]->SoChuyenDaBay < dsmb.DSMB[j + 1]->SoChuyenDaBay)
                SwapMayBay(dsmb.DSMB[j], dsmb.DSMB[j + 1]);
}

void GiaiPhongMayBay(ListMayBay &dsmb)
{
    for (int i = 0; i < dsmb.SoLuong; i++)
    {
        delete dsmb.DSMB[i];
    }
    dsmb.SoLuong = 0;
}