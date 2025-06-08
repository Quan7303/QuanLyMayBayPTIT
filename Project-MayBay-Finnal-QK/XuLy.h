#pragma once
#include "UIQK.h"
#include "MayBay.h"
#include "ChuyenBay.h"
#include "HanhKhach.h"
#include "RangBuoc.h"

MayBay mb;
ListMayBay dsmb;
ChuyenBay cb;
ListCB LCB, tmp;
Tree root;

// MAY BAY flag 0
void HienSoLieuMayBay(MayBay *mb, int vitri)
{
    gotoxy(HoanhDoHienThiMB[0] + 3, Y_HienThi + 3 + vitri * 2);
    printf("%-15s", mb->SoHieuMB);
    gotoxy(HoanhDoHienThiMB[1] + 3, Y_HienThi + 3 + vitri * 2);
    printf("%-15s", mb->LoaiMB);
    gotoxy(HoanhDoHienThiMB[2] + 8, Y_HienThi + 3 + vitri * 2);
    printf("%-4d", mb->SoChoMB);
}
// SO CHUYEN DA BAY flag 1
void HienSoLanThucHien(MayBay *mb, int vitri)
{
    gotoxy(HoanhDoHienThiMB[0] + 3, Y_HienThi + 3 + vitri * 2);
    printf("%-15s", mb->SoHieuMB);
    gotoxy(HoanhDoHienThiMB[1] + 12, Y_HienThi + 3 + vitri * 2);
    printf("%-3d", mb->SoChuyenDaBay);
}

void HienSoLieuMayBayTren1Trang(ListMayBay dsmb, int StartIndex, int flag)
{
    gotoxy(55, 5);
    cout << " Sl may bay : " << dsmb.SoLuong;
    int i;
    for (i = 0; i + StartIndex < dsmb.SoLuong && i < NumberPerPage; i++)
    {
        if (flag == 0)
            HienSoLieuMayBay(dsmb.DSMB[i + StartIndex], i);
        else if (flag == 1)
            HienSoLanThucHien(dsmb.DSMB[i + StartIndex], i);
    }
    XoaDuLieuDuThua(i, 3, HoanhDoHienThiMB);
    if (flag == 0)
    {
        gotoxy(105, 27);
        cout << " Trang " << TrangHienTaiMB << "/" << TongSoTrangMB;
    }
    else if (flag == 1)
    {
        gotoxy(88, 27);
        cout << " Trang " << TrangHienTaiMB << "/" << TongSoTrangMB;
    }
}

int MenuDongMB(char ThucDonMB[4][50])
{
    ShowCur(false);
    NormalLine();
    system("cls");
    DrawTableMB();
    TongSoTrangMB = (int)ceil((double)dsmb.SoLuong / NumberPerPage);
    KhungHienThi(ContentAirplane, 3, HoanhDoHienThiMB);
    HienSoLieuMayBayTren1Trang(dsmb, (TrangHienTaiMB - 1) * NumberPerPage, 0);
    gotoxy(75, 5);
    cout << " Quan li may bay";

    for (int i = 0; i < 4; i++)
    {
        gotoxy(3, 17 + i * 2);
        cout << ThucDonMB[i];
    }

    int pointer = 0;
    gotoxy(3, 17 + pointer * 2);
    HighlightLine();
    cout << ThucDonMB[pointer];
    char signal;
    while (true)
    {
        signal = getch();
        if (signal == -32)
        {
            signal = getch();
        }
        switch (signal)
        {
        case KEY_UP:
            if (pointer + 1 > 1)
            {
                NormalLine();
                gotoxy(3, 17 + pointer * 2);
                cout << ThucDonMB[pointer];
                pointer--;
                HighlightLine();
                gotoxy(3, 17 + pointer * 2);
                cout << ThucDonMB[pointer];
            }
            break;
        case KEY_DOWN:
            if (pointer + 1 < 4)
            {
                NormalLine();
                gotoxy(3, 17 + pointer * 2);
                cout << ThucDonMB[pointer];
                pointer++;
                HighlightLine();
                gotoxy(3, 17 + pointer * 2);
                cout << ThucDonMB[pointer];
            }
            break;
        case KEY_LEFT:
            if (TrangHienTaiMB > 1)
            {
                NormalLine();
                TrangHienTaiMB--;
                HienSoLieuMayBayTren1Trang(dsmb, (TrangHienTaiMB - 1) * NumberPerPage, 0);
            }
            break;
        case KEY_RIGHT:
            if (TrangHienTaiMB < TongSoTrangMB)
            {
                NormalLine();
                TrangHienTaiMB++;
                HienSoLieuMayBayTren1Trang(dsmb, (TrangHienTaiMB - 1) * NumberPerPage, 0);
            }
            break;
        case ENTER:
            return pointer + 1;
        }
    }
}

int MenuDongFindMB()
{
    ShowCur(false);
    NormalLine();
    for (int i = 4; i < 28; i++)
    {
        gotoxy(35, i);
        printf("%-120s", " ");
    }
    TrangHienTaiMB = 1;
    TongSoTrangMB = (int)ceil((double)dsmb.SoLuong / NumberPerPage);
    HienSoLieuMayBayTren1Trang(dsmb, 0, 0);
    KhungHienThi(ContentAirplane, 3, HoanhDoHienThiMB);
    gotoxy(75, 5);
    cout << " Quan li may bay";
    int pointer = 0;
    gotoxy(57, 9 + pointer * 2);
    HighlightLine();
    HienSoLieuMayBay(dsmb.DSMB[pointer], pointer);

    char signal;
    while (true)
    {
        signal = getch();
        if (signal == -32)
        {
            signal = getch();
        }
        switch (signal)
        {
        case KEY_UP:
            if (pointer > 0)
            {
                NormalLine();
                gotoxy(57, 9 + pointer * 2);
                HienSoLieuMayBay(dsmb.DSMB[(TrangHienTaiMB - 1) * NumberPerPage + pointer], pointer);
                pointer--;
                HighlightLine();
                gotoxy(57, 9 + pointer * 2);
                HienSoLieuMayBay(dsmb.DSMB[(TrangHienTaiMB - 1) * NumberPerPage + pointer], pointer);
            }
            else if (TrangHienTaiMB > 1) // Nếu ở đầu trang và có trang trước
            {
                NormalLine();
                TrangHienTaiMB--;
                pointer = NumberPerPage - 1; // Chuyển con trỏ xuống cuối trang trước
                HienSoLieuMayBayTren1Trang(dsmb, (TrangHienTaiMB - 1) * NumberPerPage, 0);
                HighlightLine();
                gotoxy(57, 9 + pointer * 2);
                HienSoLieuMayBay(dsmb.DSMB[(TrangHienTaiMB - 1) * NumberPerPage + pointer], pointer);
            }
            break;
        case KEY_DOWN:
            if (pointer < NumberPerPage - 1 && (TrangHienTaiMB - 1) * NumberPerPage + pointer + 1 < dsmb.SoLuong)
            {
                NormalLine();
                gotoxy(57, 9 + pointer * 2);
                HienSoLieuMayBay(dsmb.DSMB[(TrangHienTaiMB - 1) * NumberPerPage + pointer], pointer);
                pointer++;
                HighlightLine();
                gotoxy(57, 9 + pointer * 2);
                HienSoLieuMayBay(dsmb.DSMB[(TrangHienTaiMB - 1) * NumberPerPage + pointer], pointer);
            }
            else if (TrangHienTaiMB < TongSoTrangMB) // Nếu ở cuối trang và có trang sau
            {
                NormalLine();
                TrangHienTaiMB++;
                pointer = 0; // Chuyển con trỏ lên đầu trang sau
                HienSoLieuMayBayTren1Trang(dsmb, (TrangHienTaiMB - 1) * NumberPerPage, 0);
                HighlightLine();
                gotoxy(57, 9 + pointer * 2);
                HienSoLieuMayBay(dsmb.DSMB[(TrangHienTaiMB - 1) * NumberPerPage + pointer], pointer);
            }
            break;
        case KEY_LEFT:
            if (TrangHienTaiMB > 1)
            {
                NormalLine();
                TrangHienTaiMB--;
                pointer = 0; // Đưa con trỏ về đầu trang
                HienSoLieuMayBayTren1Trang(dsmb, (TrangHienTaiMB - 1) * NumberPerPage, 0);
                HighlightLine();
                gotoxy(57, 9 + pointer * 2);
                HienSoLieuMayBay(dsmb.DSMB[(TrangHienTaiMB - 1) * NumberPerPage + pointer], pointer);
            }
            break;
        case KEY_RIGHT:
            if (TrangHienTaiMB < TongSoTrangMB)
            {
                NormalLine();
                TrangHienTaiMB++;
                pointer = 0; // Đưa con trỏ về đầu trang
                HienSoLieuMayBayTren1Trang(dsmb, (TrangHienTaiMB - 1) * NumberPerPage, 0);
                HighlightLine();
                gotoxy(57, 9 + pointer * 2);
                HienSoLieuMayBay(dsmb.DSMB[(TrangHienTaiMB - 1) * NumberPerPage + pointer], pointer);
            }
            break;
        case ENTER:
            return (TrangHienTaiMB - 1) * NumberPerPage + pointer + 1;
        }
    }
}
// DIEM DEN flag 1
void HienSoLieuDiemDen(ChuyenBay cb, int vitri)
{
    gotoxy(HoanhDoHienThiCB[0] + 3, Y_HienThi + 3 + vitri * 2);
    printf("%-15s", cb.MaCB);
    gotoxy(HoanhDoHienThiCB[1] + 3, Y_HienThi + 3 + vitri * 2);
    printf("%-15s", cb.SoHieuMB);
    gotoxy(HoanhDoHienThiCB[2] + 3, Y_HienThi + 3 + vitri * 2);
    OutputDateTime(cb.TimeDi);
    gotoxy(HoanhDoHienThiCB[3] + 8, Y_HienThi + 3 + vitri * 2);
    printf("%-5d", cb.SoVe);
    gotoxy(HoanhDoHienThiCB[4] + 6, Y_HienThi + 3 + vitri * 2);
    printf("%-3d", cb.TongSoDaBan);
    gotoxy(HoanhDoHienThiCB[5] + 6, Y_HienThi + 3 + vitri * 2);
    printf("%-3d", (cb.SoVe - cb.TongSoDaBan));
}
// CHUYEN BAY  flag 0
void HienSoLieuChuyenBay(ChuyenBay cb, int vitri)
{
    gotoxy(HoanhDoHienThiCB[0] + 3, Y_HienThi + 3 + vitri * 2);
    printf("%-15s", cb.MaCB);
    gotoxy(HoanhDoHienThiCB[1] + 3, Y_HienThi + 3 + vitri * 2);
    printf("%-18s", cb.SanBayDen);
    gotoxy(HoanhDoHienThiCB[2] + 3, Y_HienThi + 3 + vitri * 2);
    printf("%-15s", cb.SoHieuMB);
    gotoxy(HoanhDoHienThiCB[3] + 2, Y_HienThi + 3 + vitri * 2);
    OutputDateTime(cb.TimeDi);
    gotoxy(HoanhDoHienThiCB[4] + 6, Y_HienThi + 3 + vitri * 2);
    printf("%-3d", cb.SoVe);
    gotoxy(HoanhDoHienThiCB[5] + 3, Y_HienThi + 3 + vitri * 2);
    // 0: hủy chuyến, 1: còn vé, 2: hết vé,3: hoàn tất ;
    switch (cb.TrangThai)
    {
    case 0:
        cout << "Huy     ";
        break;
    case 1:
        cout << "Con ve  ";
        break;
    case 2:
        cout << "Het ve  ";
        break;
    case 3:
        cout << "Hoan tat";
        break;
    default:
        break;
    }
}

void HienSoLieuChuyenBayTren1Trang(ListCB LCB, int StartIndex, int flag)
{
    gotoxy(36, 5);
    cout << " So luong chuyen bay : " << LCB.SoLuongCB;

    if (LCB.First == NULL && LCB.Last == NULL)
        return;

    int cnt = -1;
    TuDongCapNhatTrangThai(LCB);
    for (PTRCB p = LCB.First; p != NULL; p = p->next)
    {
        cnt++;
        if (cnt == StartIndex)
        {
            int i = -1;
            while (p != NULL && i < NumberPerPage - 1)
            {
                if (flag == 0)
                    HienSoLieuChuyenBay(p->Data, ++i);
                else if (flag == 1)
                    HienSoLieuDiemDen(p->Data, ++i);
                p = p->next;
            }
            XoaDuLieuDuThua(i + 1, 7, HoanhDoHienThiCB);
            break;
        }
    }
    gotoxy(120, 27);
    cout << "Trang " << TrangHienTaiCB << "/" << TongSoTrangCB;
}

int MenuDongCB(char ThucDonCB[4][50])
{
    ShowCur(false);
    NormalLine();
    system("cls");
    DrawTableMB();

    // TrangHienTaiCB = 1;
    TongSoTrangCB = (int)ceil((double)tmp.SoLuongCB / NumberPerPage);
    KhungHienThi(ContentFlight, 6, HoanhDoHienThiCB);
    HienSoLieuChuyenBayTren1Trang(tmp, (TrangHienTaiCB - 1) * NumberPerPage, 0);

    gotoxy(77, 5);
    cout << " Quan li chuyen bay";

    for (int i = 0; i < 4; i++)
    {
        gotoxy(3, 17 + i * 2);
        cout << ThucDonCB[i];
    }

    int pointer = 0;
    gotoxy(3, 17 + pointer * 2);
    HighlightLine();
    cout << ThucDonCB[pointer];
    char signal;
    while (true)
    {
        signal = getch();
        if (signal == -32)
        {
            signal = getch();
        }
        switch (signal)
        {
        case KEY_UP:
            if (pointer + 1 > 1)
            {
                NormalLine();
                gotoxy(3, 17 + pointer * 2);
                cout << ThucDonCB[pointer];
                pointer--;
                HighlightLine();
                gotoxy(3, 17 + pointer * 2);
                cout << ThucDonCB[pointer];
            }
            break;
        case KEY_DOWN:
            if (pointer + 1 < 4)
            {
                NormalLine();
                gotoxy(3, 17 + pointer * 2);
                cout << ThucDonCB[pointer];
                pointer++;
                HighlightLine();
                gotoxy(3, 17 + pointer * 2);
                cout << ThucDonCB[pointer];
            }
            break;
        case KEY_LEFT:
            NormalLine();
            if (TrangHienTaiCB > 1)
            {
                TrangHienTaiCB--;
                HienSoLieuChuyenBayTren1Trang(tmp, (TrangHienTaiCB - 1) * NumberPerPage, 0);
            }
            break;
        case KEY_RIGHT:
            NormalLine();
            if (TrangHienTaiCB < TongSoTrangCB)
            {
                TrangHienTaiCB++;
                HienSoLieuChuyenBayTren1Trang(tmp, (TrangHienTaiCB - 1) * NumberPerPage, 0);
            }
            break;
        case ENTER:
            return pointer + 1;
        }
    }
}

int MenuDongDiemDenCB(string destination)
{
    NormalLine();
    ShowCur(false);
    for (int i = 4; i < 31; i++)
    {
        gotoxy(27, i);
        printf("%-127s", " ");
    }
    CopyListCBDD(LCB, tmp, destination);
    SelectionSortCB(tmp);
    TrangHienTaiCB = 1;
    TongSoTrangCB = (int)ceil((double)tmp.SoLuongCB / NumberPerPage);
    KhungHienThi(SpecifedFlight, 6, HoanhDoHienThiCB);
    HienSoLieuChuyenBayTren1Trang(tmp, 0, 1);
    gotoxy(77, 5);
    cout << " Danh sach cac chuyen bay toi thanh pho " << destination;
    int pointer = 0;
    gotoxy(57, 9 + pointer * 2);
    HighlightLine();
    PTRCB p = tmp.First;
    for (int i = 0; i < pointer; i++)
        if (p)
            p = p->next;
    if (p)
        HienSoLieuDiemDen(p->Data, pointer);

    char signal;
    while (true)
    {
        signal = getch();
        if (signal == -32)
        {
            signal = getch();
        }
        switch (signal)
        {
        case KEY_UP:
            if (pointer > 0)
            {
                NormalLine();
                gotoxy(57, 9 + pointer * 2);
                p = tmp.First;
                for (int i = 0; i < (TrangHienTaiCB - 1) * NumberPerPage + pointer; i++)
                    if (p)
                        p = p->next;
                if (p)
                    HienSoLieuDiemDen(p->Data, pointer);
                pointer--;
                HighlightLine();
                gotoxy(57, 9 + pointer * 2);
                p = tmp.First;
                for (int i = 0; i < (TrangHienTaiCB - 1) * NumberPerPage + pointer; i++)
                    if (p)
                        p = p->next;
                if (p)
                    HienSoLieuDiemDen(p->Data, pointer);
            }
            else if (TrangHienTaiCB > 1)
            {
                NormalLine();
                TrangHienTaiCB--;
                pointer = NumberPerPage - 1;
                HienSoLieuChuyenBayTren1Trang(tmp, (TrangHienTaiCB - 1) * NumberPerPage, 1);
                HighlightLine();
                gotoxy(57, 9 + pointer * 2);
                p = tmp.First;
                for (int i = 0; i < (TrangHienTaiCB - 1) * NumberPerPage + pointer; i++)
                    if (p)
                        p = p->next;
                if (p)
                    HienSoLieuDiemDen(p->Data, pointer);
            }
            break;
        case KEY_DOWN:
            if (pointer < NumberPerPage - 1 && (TrangHienTaiCB - 1) * NumberPerPage + pointer + 1 < tmp.SoLuongCB)
            {
                NormalLine();
                gotoxy(57, 9 + pointer * 2);
                p = tmp.First;
                for (int i = 0; i < (TrangHienTaiCB - 1) * NumberPerPage + pointer; i++)
                    if (p)
                        p = p->next;
                if (p)
                    HienSoLieuDiemDen(p->Data, pointer);
                pointer++;
                HighlightLine();
                gotoxy(57, 9 + pointer * 2);
                p = tmp.First;
                for (int i = 0; i < (TrangHienTaiCB - 1) * NumberPerPage + pointer; i++)
                    if (p)
                        p = p->next;
                if (p)
                    HienSoLieuDiemDen(p->Data, pointer);
            }
            else if (TrangHienTaiCB < TongSoTrangCB)
            {
                NormalLine();
                TrangHienTaiCB++;
                pointer = 0;
                HienSoLieuChuyenBayTren1Trang(tmp, (TrangHienTaiCB - 1) * NumberPerPage, 1);
                HighlightLine();
                gotoxy(57, 9 + pointer * 2);
                p = tmp.First;
                for (int i = 0; i < (TrangHienTaiCB - 1) * NumberPerPage + pointer; i++)
                    if (p)
                        p = p->next;
                if (p)
                    HienSoLieuDiemDen(p->Data, pointer);
            }
            break;
        case KEY_LEFT:
            if (TrangHienTaiCB > 1)
            {
                NormalLine();
                TrangHienTaiCB--;
                pointer = 0;
                HienSoLieuChuyenBayTren1Trang(tmp, (TrangHienTaiCB - 1) * NumberPerPage, 1);
                HighlightLine();
                gotoxy(57, 9 + pointer * 2);
                p = tmp.First;
                for (int i = 0; i < (TrangHienTaiCB - 1) * NumberPerPage + pointer; i++)
                    if (p)
                        p = p->next;
                if (p)
                    HienSoLieuDiemDen(p->Data, pointer);
            }
            break;
        case KEY_RIGHT:
            if (TrangHienTaiCB < TongSoTrangCB)
            {
                NormalLine();
                TrangHienTaiCB++;
                pointer = 0;
                HienSoLieuChuyenBayTren1Trang(tmp, (TrangHienTaiCB - 1) * NumberPerPage, 1);
                HighlightLine();
                gotoxy(57, 9 + pointer * 2);
                p = tmp.First;
                for (int i = 0; i < (TrangHienTaiCB - 1) * NumberPerPage + pointer; i++)
                    if (p)
                        p = p->next;
                if (p)
                    HienSoLieuDiemDen(p->Data, pointer);
            }
            break;
        case ENTER:
            return (TrangHienTaiCB - 1) * NumberPerPage + pointer + 1;
        case ESC:
            return -1;
        }
    }
}
int MenuDongVe(char ThucDonVe[6][50])
{
    ShowCur(false);
    NormalLine();
    system("cls");
    DrawTableVe();

    CopyListCBCV(LCB, tmp);
    SelectionSortCB(tmp);

    TrangHienTaiCB = 1;
    TongSoTrangCB = (int)ceil((double)tmp.SoLuongCB / NumberPerPage);
    KhungHienThi(ContentFlight, 6, HoanhDoHienThiCB);
    HienSoLieuChuyenBayTren1Trang(tmp, (TrangHienTaiCB - 1) * NumberPerPage, 0);

    gotoxy(77, 5);
    cout << " Quan li cac chuyen bay co trang thai con ve";

    for (int i = 0; i < 6; i++)
    {
        gotoxy(3, 17 + i * 2);
        cout << ThucDonVe[i];
    }
    int pointer = 0;
    gotoxy(3, 17 + pointer * 2);
    HighlightLine();
    cout << ThucDonVe[pointer];
    char signal;
    while (1)
    {
        signal = getch();
        if (signal == -32)
        {
            signal = getch();
        }
        switch (signal)
        {
        case KEY_UP:
            if (pointer + 1 > 1)
            {
                NormalLine();
                gotoxy(3, 17 + pointer * 2);
                cout << ThucDonVe[pointer];
                pointer--;
                HighlightLine();
                gotoxy(3, 17 + pointer * 2);
                cout << ThucDonVe[pointer];
            }
            break;
        case KEY_DOWN:
            if (pointer + 1 < 6)
            {
                NormalLine();
                gotoxy(3, 17 + pointer * 2);
                cout << ThucDonVe[pointer];
                pointer++;
                HighlightLine();
                gotoxy(3, 17 + pointer * 2);
                cout << ThucDonVe[pointer];
            }
            break;
        case KEY_LEFT:
            NormalLine();
            if (TrangHienTaiCB > 1)
            {
                TrangHienTaiCB--;
                HienSoLieuChuyenBayTren1Trang(tmp, (TrangHienTaiCB - 1) * NumberPerPage, 0);
            }
            break;
        case KEY_RIGHT:
            NormalLine();
            if (TrangHienTaiCB < TongSoTrangCB)
            {
                TrangHienTaiCB++;
                HienSoLieuChuyenBayTren1Trang(tmp, (TrangHienTaiCB - 1) * NumberPerPage, 0);
            }
            break;
        case ENTER:
            return pointer + 1;
        }
    }
}

void NhapThongTinMB(ListMayBay &dsmb, bool EditedOrNot = false, bool DeleteOrNot = false)
{
    ShowCur(true);
    bool SaveOrNot = true;  // kiem tra xem duoc luu lai hay chua
    bool MoveOrNot = false; // kiem tra xem nguoi dung co dung phim mui ten de di chuyen khong
    string ID;              // so hieu may bay
    string TypeAirplane;    // loai may bay
    int nChair = 0;         // so cho ngoi
    int ordinal = 0;        // so thu tu bat dau viet
    int target = -1;
    int cf = 0;
    while (true)
    {
        switch (ordinal)
        {
        case 0:
        {
            MoveOrNot = false;
            ConstraintForLetterAndNumber(ID, MoveOrNot, ordinal, SaveOrNot, 12);

            if (SaveOrNot == false)
            {
                RemoveFormComplete();
                return;
            }

            if (ID == "")
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 2);
                cout << " Vui Long Khong  ";
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "  Bo Trong";
                if (MoveOrNot)
                {
                    ordinal = 0;
                }
                break;
            }

            if (DeleteOrNot)
            {
                target = TimKiemMB(dsmb, ID.c_str());
                if (target < 0)
                {
                    RemoveNotification();
                    gotoxy(X_Notification, Y_Notification + 2);
                    cout << "So hieu ko ton tai";
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << "vui long nhap lai";
                    if (MoveOrNot)
                    {
                        ordinal = 0;
                    }
                    break;
                }
                if (TimCBTheoSHMB(LCB, ID.c_str()) != NULL)
                {
                    RemoveNotification();
                    gotoxy(X_Notification + 1, Y_Notification + 2);
                    cout << " May Bay Da Thuc ";
                    gotoxy(X_Notification + 1, Y_Notification + 3);
                    cout << "Hien Bay Khong The";
                    gotoxy(X_Notification + 1, Y_Notification + 4);
                    cout << "      Xoa !    ";
                    if (MoveOrNot)
                    {
                        ordinal = 0;
                    }
                    break;
                }
                else
                {
                    RemoveNotification();
                    cf = RemoveConfirm();
                    NormalLine();
                    if (cf == 0)
                    {
                        if (RemoveAirplaneIsSucceed(dsmb, TimKiemMB(dsmb, ID.c_str())))
                        {
                            RemoveNotification();
                            gotoxy(X_Notification + 1, Y_Notification + 3);
                            cout << " Xoa thanh cong";
                            ShowCur(false);
                            Sleep(1500);
                            return;
                        }
                    }
                    else
                    {
                        RemoveNotification();
                        gotoxy(X_Notification + 1, Y_Notification + 3);
                        cout << " Xoa ko thanh cong";
                        ordinal = 0;
                        break;
                    }
                }
            }

            /*kIEM TRA XEM ID NHAP VAO CO Bi Trung khong*/
            target = TimKiemMB(dsmb, ID.c_str());
            if (target > -1 && EditedOrNot == false)
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 2);
                cout << "So hieu da ton tai";
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "vui long nhap lai";
                if (MoveOrNot)
                {
                    ordinal = 0;
                }
                break;
            }

            if (target < 0 && EditedOrNot == true)
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 2);
                cout << "So hieu ko ton tai";
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "vui long nhap lai";
                break;
            }

            if (EditedOrNot)
            {
                ID = dsmb.DSMB[target]->SoHieuMB;
                TypeAirplane = dsmb.DSMB[target]->LoaiMB;
                nChair = dsmb.DSMB[target]->SoChoMB;

                gotoxy(X_Them + 12, 0 * 3 + Y_Them);
                cout << ID;
                gotoxy(X_Them + 12, 1 * 3 + Y_Them);
                cout << TypeAirplane;
                gotoxy(X_Them + 12, 2 * 3 + Y_Them);
                cout << nChair;
            }

            if (MoveOrNot)
            {
                break;
            }

            ordinal++;
            break;
        }
        case 1: // nhap hang may bay
            MoveOrNot = false;
            ConstraintForLetterAndNumber(TypeAirplane, MoveOrNot, ordinal, SaveOrNot, 12);
            if (SaveOrNot == false)
            {
                RemoveFormComplete();
                return;
            }

            if (TypeAirplane == "")
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 2);
                cout << " Vui Long Khong  ";
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "  Bo Trong";
                if (MoveOrNot)
                {
                    ordinal = 1;
                }
                break;
            }
            // neu di chuyen tim thay cb co ma id thi chi cho sua hang may bay
            if (MoveOrNot && EditedOrNot && (TimCBTheoSHMB(LCB, ID.c_str()) != NULL))
            {
                ordinal = 1;
                break;
            }

            if (MoveOrNot && EditedOrNot)
            {
                ordinal = 2;
                break;
            }

            if (MoveOrNot == true)
            {
                break;
            }

            if (EditedOrNot && (TimCBTheoSHMB(LCB, ID.c_str()) != NULL))
            {
                ordinal = 3;
                break;
            }

            ordinal++;
            break;
        case 2: // nhap so cho ngoi may bay
            MoveOrNot = false;
            ConstraintForOnlyNumber(nChair, MoveOrNot, ordinal, SaveOrNot, 12, 999);
            if (SaveOrNot == false)
            {
                RemoveFormComplete();
                return;
            }

            if (nChair < 1)
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 2);
                cout << " Vui Long Khong  ";
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "  Bo Trong";
                if (MoveOrNot)
                {
                    ordinal = 2;
                }
                break;
            }
            if (nChair < 20)
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << " So cho phai >= 20";
                if (MoveOrNot)
                {
                    ordinal = 2;
                }
                break;
            }

            if (MoveOrNot && EditedOrNot)
            {
                ordinal = 1;
                break;
            }

            if (MoveOrNot)
            {
                break;
            }

            ordinal++;
            break;
        case 3:
        {
            if (MoveOrNot)
            {
                ordinal = 0;
                break;
            }

            if (!AirplaneDataIsEmpty)
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 2);
                cout << "Nhap thieu thong tin";
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "vui long nhap lai!";
                ordinal = 0;
                break;
            }

            /*Chinh sua thong tin*/
            if (EditedOrNot && target > -1)
            {
                RemoveNotification();
                cf = RemoveConfirm();
                NormalLine();
                if (cf == 0)
                {
                    strcpy(dsmb.DSMB[target]->SoHieuMB, ID.c_str());
                    strcpy(dsmb.DSMB[target]->LoaiMB, TypeAirplane.c_str());
                    dsmb.DSMB[target]->SoChoMB = nChair;
                    RemoveNotification();
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << " Sua Thanh Cong ";
                }
                else
                {
                    RemoveNotification();
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << " Sua Khong  ";
                    gotoxy(X_Notification, Y_Notification + 4);
                    cout << " Thanh Cong ";
                    ordinal = 1;
                    ShowCur(true);
                    break;
                }
            }
            /*Them moi*/
            else
            {
                RemoveNotification();
                cf = RemoveConfirm();
                NormalLine();
                if (cf == 0)
                {
                    // dsmb.DSMB[dsmb.SoLuong] = new MayBay;
                    // strcpy(dsmb.DSMB[dsmb.SoLuong]->SoHieuMB, ID.c_str());
                    // strcpy(dsmb.DSMB[dsmb.SoLuong]->LoaiMB, TypeAirplane.c_str());
                    // dsmb.DSMB[dsmb.SoLuong]->SoChoMB = nChair;
                    // dsmb.DSMB[dsmb.SoLuong]->SoChuyenDaBay = 0;
                    MayBay MB;
                    strcpy(MB.SoHieuMB, ID.c_str());
                    strcpy(MB.LoaiMB, TypeAirplane.c_str());
                    MB.SoChoMB = nChair;
                    MB.SoChuyenDaBay = 0;
                    // dsmb.SoLuong++;
                    ThemMB(dsmb, MB);
                    RemoveNotification();
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << " Them thanh cong ";
                }
                else
                {
                    RemoveNotification();
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << " Them may bay ";
                    gotoxy(X_Notification, Y_Notification + 4);
                    cout << "khong thanh cong ";
                    ordinal = 0;
                    ShowCur(true);
                    break;
                }
            }

            WriteMBToFile(dsmb);
            ID = "";
            TypeAirplane = "";
            nChair = 0;
            ordinal = 0;
            RemoveForm();
            break;
        }
        }
    }
    ShowCur(false);
}

void NhapThongTinNgayVaGio(DayTime &DT, int &ordinal, bool &MoveOrNot, bool &SaveOrCancel)
{
    int DTordinal = 0; // vi tri khoi dau cho viec nhap
    bool DTMoveOrNot = false;
    /*Hien form hien thi ngay - gio*/
    gotoxy(X_Them + 12 + 2, ordinal * 3 + Y_Them);
    cout << ":";
    gotoxy(X_Them + 12 + 8, ordinal * 3 + Y_Them);
    cout << "/";
    gotoxy(X_Them + 12 + 11, ordinal * 3 + Y_Them);
    cout << "/";

    while (true)
    {
        /*Kiem tra theo trinh tu Hour->Minutes->Day->Month->Year*/
        switch (DTordinal)
        {
        case 0:
            DTMoveOrNot = false;
            ConstraintForDateAndTime(DT.h, ordinal, DTordinal, SaveOrCancel, MoveOrNot, DTMoveOrNot, 12, 24);
            if (SaveOrCancel == false)
            {
                RemoveFormComplete();
                return;
            }
            if (DTMoveOrNot)
            {
                break;
            }
            if (MoveOrNot)
            {
                return;
            }
            DTordinal++;
            break;
        case 1:
            DTMoveOrNot = false;
            ConstraintForDateAndTime(DT.mi, ordinal, DTordinal, SaveOrCancel, MoveOrNot, DTMoveOrNot, 12, 60);
            if (SaveOrCancel == false)
            {
                RemoveFormComplete();
                return;
            }
            if (DTMoveOrNot)
            {
                break;
            }
            if (MoveOrNot)
            {
                return;
            }
            DTordinal++;
            break;
        case 2:
            DTMoveOrNot = false;
            ConstraintForDateAndTime(DT.d, ordinal, DTordinal, SaveOrCancel, MoveOrNot, DTMoveOrNot, 12, 32);
            if (SaveOrCancel == false)
            {
                RemoveFormComplete();
                return;
            }
            if (DTMoveOrNot)
            {
                break;
            }
            if (MoveOrNot)
            {
                return;
            }
            DTordinal++;
            break;
        case 3:
            DTMoveOrNot = false;
            ConstraintForDateAndTime(DT.m, ordinal, DTordinal, SaveOrCancel, MoveOrNot, DTMoveOrNot, 12, 13);
            if (SaveOrCancel == false)
            {
                RemoveFormComplete();
                return;
            }
            if (DTMoveOrNot)
            {
                break;
            }
            if (MoveOrNot)
            {
                return;
            }
            DTordinal++;
            break;
        case 4:
            DTMoveOrNot = false;
            ConstraintForDateAndTime(DT.y, ordinal, DTordinal, SaveOrCancel, MoveOrNot, DTMoveOrNot, 12, 2100);
            if (SaveOrCancel == false)
            {
                RemoveFormComplete();
                return;
            }
            if (DTMoveOrNot)
            {
                break;
            }
            if (MoveOrNot)
            {
                return;
            }
            DTordinal++;
            break;
        case 5:
            if (DTMoveOrNot)
            {
                DTordinal = 0;
                break;
            }
            return;
        }
    } // while( true )
}

void NhapThongTinCB(ListCB &LCB, bool EditedOrNot, bool CancelOrNot)
{
    ShowCur(true);
    int ordinal = 0;
    bool MoveOrNot = false; // ko di chuyen
    bool SaveOrNot = true;  // mac dinh la nguoi dung se luu lai
    string ID;              // Ma chuyen bay
    string destination;     // So hieu may bay
    DayTime DT;             // San bay den
    string AirplaneID;      // ngay gio
    int nSoldTicket = 0;    // So ve da ban
    int nTicket = 0;        // so ve trong chuyen bay
    int status = 0;         // luon con ve
    int target = -1;        // kiem tra Ma chuyen bay ton tai hay chua
    int targett = -1;       // kiem tra so hieu may bay co ton tai hay khong
    int kt = 0;             // kiem tra Go FIND lan dau tien
    int cf = 0;             // xac nhan cf
    while (true)
    {
        switch (ordinal)
        {
        case 0: // nhap ma chuyen bay
        {
            MoveOrNot = false;
            ConstraintForLetterAndNumber(ID, MoveOrNot, ordinal, SaveOrNot, 12);
            if (SaveOrNot == false)
            {
                RemoveFormComplete();
                return;
            }
            // xu ly neu bo trong
            if (ID == "")
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 2);
                cout << "Vui Long Khong";
                gotoxy(X_Notification, Y_Notification + 3);
                cout << " Bo Trong";
                if (MoveOrNot)
                {
                    ordinal = 0;
                }
                break;
            }

            // xu ly huy
            if (CancelOrNot)
            {
                target = ViTriCB(LCB, ID.c_str());
                if (target < 0)
                {
                    RemoveNotification();
                    gotoxy(X_Notification, Y_Notification + 2);
                    cout << "Ma chuyen bay khong";
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << "ton tai vui long ";
                    gotoxy(X_Notification, Y_Notification + 4);
                    cout << "nhap lai !!!";
                    if (MoveOrNot)
                    {
                        ordinal = 0;
                    }
                    break;
                }
                else
                {
                    PTRCB noorder = TimCB(LCB, ID.c_str());
                    PTRCB order = TimCB(tmp, ID.c_str());
                    if (noorder->Data.TrangThai == 1 || noorder->Data.TrangThai == 2)
                    {
                        RemoveNotification();
                        cf = RemoveConfirm();
                        NormalLine();
                        if (cf == 0)
                        {
                            noorder->Data.TrangThai = 0;
                            order->Data.TrangThai = 0;
                            RemoveNotification();
                            gotoxy(X_Notification + 1, Y_Notification + 3);
                            cout << "Huy Thanh Cong !";
                            ShowCur(false);
                            Sleep(2000);
                            return;
                        }
                        else
                        {
                            RemoveNotification();
                            gotoxy(X_Notification + 1, Y_Notification + 3);
                            cout << "Huy Ko Thanh Cong !";
                            ordinal = 0;
                            break;
                        }
                    }
                    else
                    {
                        RemoveNotification();
                        gotoxy(X_Notification, Y_Notification + 2);
                        cout << "Chuyen Bay Khong Con";
                        gotoxy(X_Notification, Y_Notification + 3);
                        cout << " Hoat Dong Khong The ";
                        gotoxy(X_Notification, Y_Notification + 4);
                        cout << " Huy Chuyen Bay Nay !";
                        if (MoveOrNot)
                        {
                            ordinal = 0;
                        }
                        break;
                    }
                }
            }
            // tim kiem Ma Chuyen Bay
            target = ViTriCB(LCB, ID.c_str());

            if (target > -1 && EditedOrNot == false)
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 2);
                cout << "Ma chuyen bay da ";
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "ton tai vui long ";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "nhap lai !!! ";
                if (MoveOrNot)
                {
                    ordinal = 0;
                }
                break;
            }

            if (target < 0 && EditedOrNot == true)
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 2);
                cout << "Ma chuyen bay khong ";
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "ton tai vui long ";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "nhap lai !!! ";
                if (MoveOrNot)
                {
                    ordinal = 0;
                }
                break;
            }

            PTRCB EditingFlight = TimCB(LCB, ID.c_str());
            if (EditedOrNot)
            {
                if (EditingFlight->Data.TrangThai == 0 || EditingFlight->Data.TrangThai == 3)
                {
                    RemoveNotification();
                    gotoxy(X_Notification, Y_Notification + 2);
                    cout << "Khong The Hieu ";
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << "Chinh Ngay Gio  !!!";
                    if (MoveOrNot)
                    {
                        ordinal = 0;
                    }
                    break;
                }
                else
                {
                    ID = EditingFlight->Data.MaCB;
                    destination = EditingFlight->Data.SanBayDen;
                    AirplaneID = EditingFlight->Data.SoHieuMB;
                    DT = EditingFlight->Data.TimeDi;
                    nTicket = EditingFlight->Data.SoVe;
                    status = EditingFlight->Data.TrangThai;

                    gotoxy(X_Them + 12, 0 * 3 + Y_Them);
                    cout << ID;
                    gotoxy(X_Them + 12, 1 * 3 + Y_Them);
                    cout << destination;
                    gotoxy(X_Them + 12, 2 * 3 + Y_Them);
                    cout << AirplaneID;
                    gotoxy(X_Them + 12, 3 * 3 + Y_Them);
                    OutputDayTime(DT);
                    gotoxy(X_Them + 12, 4 * 3 + Y_Them);
                    cout << nTicket;
                    gotoxy(X_Them + 12, 5 * 3 + Y_Them);
                    if (status == 1)
                        cout << "CON VE";
                    else if (status == 2)
                        cout << "HET VE";
                    ordinal = 2;
                }
            }
            if (MoveOrNot)
            {
                break;
            }
            ordinal++;
            break;
        }
        case 1: // San bay den
        {
            MoveOrNot = false;
            ConstraintsForLetterAndSpace(destination, MoveOrNot, ordinal, SaveOrNot, 12);
            if (SaveOrNot == false)
            {
                RemoveFormComplete();
                return;
            }
            if (destination == "")
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 2);
                cout << " Vui Long Khong";
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "   Bo Trong ";
                if (MoveOrNot)
                {
                    ordinal = 1;
                }
                break;
            }
            if (MoveOrNot)
            {
                break;
            }
            ordinal++;
            break;
        }

        case 2: // So hieu may bay
        {
            MoveOrNot = false;
            if (kt == 0)
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 2);
                cout << "Go FIND neu can ";
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "tim so hieu MB";
                kt++;
            }
            ConstraintForLetterAndNumber(AirplaneID, MoveOrNot, ordinal, SaveOrNot, 12);

            if (SaveOrNot == false)
            {
                RemoveFormComplete();
                return;
            }
            /*kiem tra xem So hieu may bay nhap vao co ton tai*/
            if (AirplaneID == "")
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 2);
                cout << "Vui Long Khong";
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "  Bo Trong ";
                if (MoveOrNot)
                {
                    ordinal = 2;
                }
                break;
            }

            if (AirplaneID == "FIND")
            {
                int t = MenuDongFindMB();
                AirplaneID = dsmb.DSMB[t - 1]->SoHieuMB;
                ordinal = 2;
                NormalLine();
                for (int i = 4; i < 28; i++)
                {
                    gotoxy(35, i);
                    printf("%-120s", " ");
                }
                KhungHienThi(ContentFlight, 6, HoanhDoHienThiCB);
                HienSoLieuChuyenBayTren1Trang(tmp, (TrangHienTaiCB - 1) * NumberPerPage, 0);
                gotoxy(77, 5);
                cout << " Quan li chuyen bay";
                ShowCur(true);
                break;
            }
            targett = TimKiemMB(dsmb, AirplaneID.c_str());
            // neu may bay khong ton tai
            if (targett < 0)
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 2);
                cout << "So hieu may bay";
                gotoxy(X_Notification, Y_Notification + 3);
                cout << " khong ton tai";
                if (MoveOrNot)
                {
                    ordinal = 2;
                }
                break;
            }

            if (MoveOrNot)
            {
                break;
            }
            ordinal++;
            break;
        }
        case 3: // Nhap thoi gian di cua may bay
        {
            MoveOrNot = false;
            if (!EditedOrNot)
            {
                DT = Time_now(); // khoi tao cac gia tri DateTime la thoi gian he thong
            }
            NhapThongTinNgayVaGio(DT, ordinal, MoveOrNot, SaveOrNot);

            if (SaveOrNot == false)
            {
                RemoveFormComplete();
                return;
            }
            if (!DateTimeIsValid(DT))
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 2);
                cout << "Nhap thoi gian";
                gotoxy(X_Notification, Y_Notification + 3);
                cout << " khong dung";
                if (EditedOrNot || MoveOrNot)
                {
                    ordinal = 3;
                }
                break;
            }
            if (EditedOrNot && MoveOrNot)
            {
                ordinal = 3;
                break;
            }

            if (MoveOrNot)
            {
                break;
            }

            if (EditedOrNot)
            {
                ordinal = 5;
            }

            ordinal++;
            break;
        }

        case 4: // nhap so ve may bay
        {
            MoveOrNot = false;
            targett = TimKiemMB(dsmb, AirplaneID.c_str());
            nTicket = dsmb.DSMB[targett]->SoChoMB;
            ConstraintForOnlyNumber(nTicket, MoveOrNot, ordinal, SaveOrNot, 12, 999);
            RemoveNotification();
            if (SaveOrNot == false)
            {
                RemoveFormComplete();
                return;
            }
            if (nTicket > dsmb.DSMB[targett]->SoChoMB || nTicket < 20)
            {
                gotoxy(X_Notification, Y_Notification + 2);
                cout << "So Ve khong phu";
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "hop voi so cho ";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "tren May Bay";
                gotoxy(X_Notification, Y_Notification + 5);
                cout << "20 <= So cho <=" << dsmb.DSMB[targett]->SoChoMB;
                if (MoveOrNot)
                {
                    ordinal = 4;
                }
                break;
            }
            if (MoveOrNot)
            {
                break;
            }
            ordinal++;
            break;
        }
        case 5:
        {
            status = 1;
            MoveOrNot = false;
            gotoxy(X_Them + 12, 5 * 3 + Y_Them);
            cout << "CON VE";
            if (MoveOrNot)
            {
                break;
            }
            ordinal++;
            break;
        }
        case 6:
        {
            if (MoveOrNot)
            {
                ordinal = 0;
                break;
            }
            strcpy(cb.MaCB, ID.c_str());
            strcpy(cb.SanBayDen, destination.c_str());
            strcpy(cb.SoHieuMB, AirplaneID.c_str());
            cb.TimeDi = DT;
            cb.SoVe = nTicket;
            cb.TrangThai = status;

            if (!Check_MB_Moi(LCB, cb))
            {
                if (EditedOrNot)
                    ordinal = 3;
                else
                    ordinal = 2;
                break;
            }

            if (EditedOrNot && target > -1) // Hieu Chinh
            {
                RemoveNotification();
                /*Lay du lieu ve*/
                cf = RemoveConfirm();
                NormalLine();
                if (cf == 0)
                {
                    PTRCB tempo = TimCB(LCB, cb.MaCB);
                    PTRCB tam = TimCB(tmp, cb.MaCB);
                    cb.TongSoDaBan = tempo->Data.TongSoDaBan;
                    cb.TicketList = tempo->Data.TicketList;
                    tempo->Data = cb;
                    tam->Data = cb;
                    RemoveNotification();
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << " Xua thanh cong ";
                    ShowCur(true);
                }
                else
                {
                    RemoveNotification();
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << " Xua Ko thanh cong ";
                    ordinal = 3;
                    break;
                }
            }
            else // them moi
            {
                RemoveNotification();
                cf = RemoveConfirm();
                NormalLine();
                if (cf == 0)
                {
                    cb.TongSoDaBan = 0;
                    InsertOrder(tmp, cb);
                    InsertEnd(LCB, cb);
                    RemoveNotification();
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << " Them thanh cong ";
                }
                else
                {
                    RemoveNotification();
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << " Them khong ";
                    gotoxy(X_Notification, Y_Notification + 4);
                    cout << " thanh cong ";
                    ordinal = 0;
                    break;
                }
            }

            WriteFlightToFile(LCB);

            ID = "";
            destination = "";
            AirplaneID = "";
            DT = Time_now();
            nTicket = 0;
            nSoldTicket = 0;
            status = 0;
            RemoveForm();
            ordinal = 0;
            break;
        }
        } // end switch(ordinal)
    } // end while( true )
    ShowCur(false);
}
void NhapThongTinHK(Tree &root, bool EditedOrNot, bool &SaveOrNot, string IDPassenger, int &cf)
{
    ShowCur(true);
    bool MoveOrNot = false;

    string FirstName; // Ho
    string LastName;  // Ten
    int gender = 1;   // 0 la nu , 1 la nam

    int ordinal = 0;
    int signal;

    while (true)
    {
        switch (ordinal)
        {
        case 0:
        {
            if (EditedOrNot)
            {
                Tree tmp = FindPassenger(root, IDPassenger.c_str());
                FirstName = tmp->Data.Ho;
                LastName = tmp->Data.Ten;
                gender = tmp->Data.Phai;
                gotoxy(X_Them + 12, 0 * 3 + Y_Them);
                cout << IDPassenger;
                gotoxy(X_Them + 12, 1 * 3 + Y_Them);
                cout << FirstName;
                gotoxy(X_Them + 12, 2 * 3 + Y_Them);
                cout << LastName;
                gotoxy(X_Them + 12, 3 * 3 + Y_Them);
                cout << gender;
            }
            ordinal++;
        }
        break;
        case 1: // NHAP Ho
        {
            MoveOrNot = false;
            ConstraintsForLetterAndSpace(FirstName, MoveOrNot, ordinal, SaveOrNot, 12);
            if (SaveOrNot == false)
            {
                RemoveFormComplete();
                return;
            }
            if (FirstName == "")
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << " Vui Long";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "Khong bo trong";
                if (MoveOrNot)
                {
                    ordinal = 1;
                    break;
                }
                ordinal = 1;
                break;
            }
            if (MoveOrNot)
            {
                break;
            }
            ordinal++;
        }
        break;
        case 2: // Nhap ten
        {
            MoveOrNot = false;
            ConstraintsForLetterAndSpace(LastName, MoveOrNot, ordinal, SaveOrNot, 12);
            if (SaveOrNot == false)
            {
                RemoveFormComplete();
                return;
            }
            if (LastName == "")
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << " Vui Long";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "Khong bo trong";
                if (MoveOrNot)
                {
                    ordinal = 2;
                    break;
                }
                ordinal = 2;
                break;
            }
            if (MoveOrNot)
            {
                break;
            }
            ordinal++;
        }
        break;
        case 3: // nhap gioi tinh
        {
            MoveOrNot = false;
            RemoveNotification();
            gotoxy(X_Notification, Y_Notification + 2);
            cout << " 1 la Nam, 2 la Nu ";
            ConstraintForOnlyGender(gender, MoveOrNot, ordinal, SaveOrNot, 12);
            if (SaveOrNot == false)
            {
                RemoveFormComplete();
                return;
            }
            // 2 la nu , 1 la nam
            if (gender == 0)
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << " Vui Long khong";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "  bo trong !!!";
                if (MoveOrNot)
                {
                    ordinal = 3;
                    break;
                }
                ordinal = 3;
                break;
            }
            if (MoveOrNot)
            {
                break;
            }
            ordinal++;
        }
        break;
        case 4:
        {
            if (MoveOrNot)
            {
                ordinal = 0;
                break;
            }
            HanhKhach P;
            strcpy(P.CCCD, IDPassenger.c_str());
            strcpy(P.Ho, FirstName.c_str());
            strcpy(P.Ten, LastName.c_str());
            P.Phai = gender;
            if (EditedOrNot)
            {
                cf = RemoveConfirm();
                NormalLine();
                if (cf == 0)
                {
                    Tree tmp = FindPassenger(root, IDPassenger.c_str());
                    tmp->Data = P;
                }
            }
            else
            {
                cf = RemoveConfirm();
                NormalLine();
                if (cf == 0)
                {
                    AddPassenger(root, P);
                }
            }
            RemoveFormComplete();
            return;
        }
        break;
        } /*switch(ordinal)*/
    } /*While(true)*/
}
// DAT VE
void TicketStack(int x, int y, int text, int status)
{
    SetColor(11);
    SetBGColor(0);
    gotoxy(x, y - 1);
    cout << char(201) << setw(3) << setfill(char(205)) << char(205) << char(187);
    gotoxy(x, y);
    cout << char(186) << setw(3) << setfill('0') << text << char(186);
    gotoxy(x, y + 1);
    if (status == 1)
    {
        SetBGColor(ColorCode_Red);
    }
    cout << char(200) << setw(3) << setfill(char(205)) << char(205) << char(188);
}
void TicketChairBoard(ChuyenBay cb)
{
    int x = X_TicketChair + 6;
    int y = Y_TicketChair + 3;
    int Limit = cb.SoVe;
    for (int i = 1; i <= Limit; i++)
    {
        TicketStack(x, y, i, CheckOut(cb, i));
        x += 6;
        if (i % 20 == 0)
        {
            y += 3;
            x = X_TicketChair + 6;
        }
    }
}
void EffectTicketMenu(int index)
{
    ShowCur(false);
    int Current = index; // lay vi tri cai ve hien tai

    int column = (Current - 1) % 20;
    int row = (Current - 1) / 20;
    SetBGColor(1); // highligh vi tri hien tai
    gotoxy(X_TicketChair + (column + 1) * 6, Y_TicketChair + (row + 1) * 3);
    cout << char(186) << setw(3) << setfill('0') << Current << char(186);

    /*Tam ve dung truoc tam ve hien tai truoc do*/
    column = (CurPosPreTicket - 1) % 20;
    row = (CurPosPreTicket - 1) / 20;

    SetBGColor(ColorCode_Black);
    gotoxy(X_TicketChair + (column + 1) * 6, Y_TicketChair + (row + 1) * 3);
    cout << char(186) << setw(3) << setfill('0') << CurPosPreTicket << char(186);
    CurPosPreTicket = Current;
}
// flag 0: dat ve flag 1: hieu chinh thong tin
int ChooseTicket(ChuyenBay &cb, int flag)
{
    CurPosTicket = 1;
    CurPosPreTicket = 1;

    TicketChairBoard(cb);
    int signal;
    int PASS = 1;
    SetBGColor(1);
    gotoxy(X_TicketChair + (0 + 1) * 6, Y_TicketChair + (0 + 1) * 3);
    cout << char(186) << setw(3) << setfill('0') << 1 << char(186);

    while (PASS)
    {
        signal = getch();
        if (signal == 0)
            signal = getch();

        switch (signal)
        {
        case KEY_DOWN:
            if (CurPosTicket + 20 <= cb.SoVe)
            {
                CurPosTicket = CurPosTicket + 20;
                EffectTicketMenu(CurPosTicket);
            }
            break;
        case KEY_UP:
            if (CurPosTicket - 20 >= 1)
            {
                CurPosTicket = CurPosTicket - 20;
                EffectTicketMenu(CurPosTicket);
            }
            break;
        case KEY_LEFT:
            if (CurPosTicket > 1)
            {
                CurPosTicket--;
                EffectTicketMenu(CurPosTicket);
            }
            break;
        case KEY_RIGHT:
            if (CurPosTicket < cb.SoVe)
            {
                CurPosTicket++;
                EffectTicketMenu(CurPosTicket);
            }
            break;
        case ESC:
            return -1;
        case ENTER:
            if (CheckOut(cb, CurPosTicket) == 1 && flag == 0)
            {
                NormalLine();
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "Ve nay da co ";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "Hanh khach dat cho ";
                ShowCur(false);
                break;
            }
            else if (CheckOut(cb, CurPosTicket) != 1 && flag == 1)
            {
                NormalLine();
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "Ve nay chua co ";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "Hanh khach dat cho ";
                ShowCur(false);
                break;
            }
            PASS = 0;
            return CurPosTicket;
        }
    }
    return 0;
}

void DatVeCB(Tree &root)
{
    int ordinal = 0;
    bool SaveOrNot = true;
    bool MoveOrNot = false;
    int DestinationExisted = -1; // tim kiem san bay den co ton tai khong
    string destination;
    DayTime DT;
    PTRCB WatchingFlight = NULL;
    int ChoosenTicket;
    int cf = -1;
    string IDHanhKhach;
    while (true)
    {
        switch (ordinal)
        {
        case 0:
        {
            SaveOrNot = true;
            MoveOrNot = false;
            CreateForm(ContentFlight, 1, 2, 35);
            ShowCur(true);
            ConstraintsForLetterAndSpace(destination, MoveOrNot, ordinal, SaveOrNot, 12);
            ShowCur(false);
            if (SaveOrNot == false)
            {
                RemoveFormComplete();
                return;
            }
            if (destination == "")
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "Vui Long Khong";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << " Bo Trong";
                if (MoveOrNot)
                {
                    ordinal = 0;
                }
                break;
            }
            DestinationExisted = ViTriSBDen(LCB, destination.c_str());
            if (DestinationExisted == -1)
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "Khong co chuyen";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "bay toi " << destination;
                gotoxy(X_Notification, Y_Notification + 5);
                cout << "Vui long chon ";
                gotoxy(X_Notification, Y_Notification + 6);
                cout << "dia diem khac";
                if (MoveOrNot)
                {
                    ordinal = 0;
                }
                break;
            }
            if (MoveOrNot)
            {
                ordinal = 0;
                break;
            }
            ordinal++;
        }
        break;
        case 1:
        {
            int t = MenuDongDiemDenCB(destination);
            NormalLine();
            if (t == -1)
            {
                ordinal = 0;
                break;
            }
            WatchingFlight = tmp.First;
            for (int i = 1; i < t && WatchingFlight != NULL; i++)
                WatchingFlight = WatchingFlight->next;
            if (WatchingFlight == NULL)
                return;
            WatchingFlight = TimCB(LCB, WatchingFlight->Data.MaCB);
            if (TG_30p_TruocBay(WatchingFlight->Data.TimeDi))
            {
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "CHUYEN BAY SE CAT ";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "CANH TRONG VONG 30P ";
                gotoxy(X_Notification, Y_Notification + 5);
                cout << "KHONG THE DAT VE !";
                ordinal = 1;
                break;
            }
            RemoveFlight();
            ordinal++;
        }
        break;
        case 2:
        {
            ShowCur(false);
            gotoxy(48, 4);
            cout << " Danh sach hanh khach co ma chuyen bay " << WatchingFlight->Data.MaCB << " toi " << WatchingFlight->Data.SanBayDen;
            cout << " luc ";
            OutputDateTime(WatchingFlight->Data.TimeDi);
            gotoxy(X_Notification, Y_Notification + 9);
            cout << "Ve co mau Do la ve";
            gotoxy(X_Notification, Y_Notification + 10);
            cout << "da co nguoi dat cho!";
            ChoosenTicket = ChooseTicket(WatchingFlight->Data, 0);

            if (ChoosenTicket == -1)
            {
                ordinal = 1;
                break;
            }
            IDHanhKhach = "";
            ordinal++;
        }
        break;
        case 3:
        {
            SaveOrNot = true;
            NormalLine();
            int target = -1;
            CreateForm(ContentPassenger, 2, 3, 35);
            ShowCur(true);
            ordinal = 0;
            ConstraintForNumber(IDHanhKhach, MoveOrNot, ordinal, SaveOrNot, 12);
            ordinal = 3;
            if (SaveOrNot == false)
            {
                RemoveFormComplete();
                ordinal--;
                break;
            }
            if (IDHanhKhach == "")
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "Vui long khong";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "Bo trong";
                if (MoveOrNot)
                {
                    ordinal = 3;
                }
                break;
            }
            if (IDHanhKhach.length() != 9 && IDHanhKhach.length() != 12)
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "CCCD ban nhap sai";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "Vui long nhap lai";
                if (MoveOrNot)
                {
                    ordinal = 3;
                }
                break;
            }
            /*Tim kiem xem cai ID nay co nam trong danh sach ve chua*/
            for (int i = 0; i < WatchingFlight->Data.TongSoDaBan; i++)
            {
                if (strcmp(WatchingFlight->Data.TicketList[i].CCCD, IDHanhKhach.c_str()) == 0)
                {
                    target = i;
                    break;
                }
            }
            /*Da dat ve roi va dat them lan nua*/
            if (target > -1)
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "Ban da dat ve roi";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "Vui long nhap lai";
                if (MoveOrNot)
                {
                    ordinal = 3;
                }
                break;
            }
            // xem thu hk co dat ve chuyen bay khac chua trog vong 3h
            if (!Check_HK_SanSangBay(LCB, WatchingFlight->Data, IDHanhKhach.c_str()))
            {
                if (MoveOrNot)
                {
                    ordinal = 3;
                }
                break;
            }
            SaveOrNot = true;
            /*Khong tim ra*/
            if (target == -1)
            {
                Tree tmp = FindPassenger(root, IDHanhKhach.c_str());
                /*Neu chua ton tai thi nhap moi*/
                if (tmp == NULL)
                {
                    CreateForm(ContentPassenger, 2, sizeof(ContentPassenger) / sizeof(string), 35);
                    gotoxy(X_Them + 12, 0 * 3 + Y_Them);
                    cout << IDHanhKhach;
                    NhapThongTinHK(root, false, SaveOrNot, IDHanhKhach, cf);
                    if (SaveOrNot == false)
                    {
                        RemoveFormComplete();
                        ordinal = 3;
                        break;
                    }
                    nPassenger++;
                }
                else
                {
                    CreateForm(ContentPassenger, 2, 6, 35);
                    NhapThongTinHK(root, true, SaveOrNot, IDHanhKhach, cf);
                    if (SaveOrNot == false)
                    {
                        RemoveFormComplete();
                        ordinal = 3;
                        break;
                    }
                }
                if (cf == 0)
                {
                    RemoveNotification();
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << "Dat ve thanh cong !!!";
                    Ticket AddingTicket;
                    strcpy(AddingTicket.CCCD, IDHanhKhach.c_str());
                    AddingTicket.Status = ChoosenTicket;
                    WatchingFlight->Data.TicketList[WatchingFlight->Data.TongSoDaBan] = AddingTicket;
                    WatchingFlight->Data.TongSoDaBan++;
                    // Het ve
                    if (WatchingFlight->Data.TongSoDaBan == WatchingFlight->Data.SoVe)
                    {
                        WatchingFlight->Data.TrangThai = 2;
                    }
                }
                else
                {
                    RemoveNotification();
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << "Dat ve khong ";
                    gotoxy(X_Notification, Y_Notification + 4);
                    cout << "thanh cong !!!";
                }
            }
            ordinal = 2;
            RemoveFormComplete();
        }
        break;
        }
    }
}

// HUY VE
void HuyVeCB(Tree root)
{
    int ordinal = 0;
    bool SaveOrNot = true;
    bool MoveOrNot = false;
    int DestinationExisted = -1; // tim kiem san bay den co ton tai khong
    string destination;
    DayTime DT;
    PTRCB WatchingFlight = NULL;

    int ChoosenTicket;
    int cf = -1;
    string IDHanhKhach;

    while (true)
    {
        switch (ordinal)
        {
        case 0:
        {
            SaveOrNot = true;
            MoveOrNot = false;
            CreateForm(ContentFlight, 1, 2, 35);
            ShowCur(true);
            ConstraintsForLetterAndSpace(destination, MoveOrNot, ordinal, SaveOrNot, 12);
            if (SaveOrNot == false)
            {
                RemoveFormComplete();
                return;
            }
            if (destination == "")
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "Vui Long Khong";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << " Bo Trong";
                if (MoveOrNot)
                {
                    ordinal = 0;
                }
                break;
            }
            DestinationExisted = ViTriSBDen(LCB, destination.c_str());
            if (DestinationExisted == -1)
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "Khong co chuyen";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "bay toi " << destination;
                gotoxy(X_Notification, Y_Notification + 5);
                cout << "Vui long chon ";
                gotoxy(X_Notification, Y_Notification + 6);
                cout << "dia diem khac";
                if (MoveOrNot)
                {
                    ordinal = 0;
                }
                break;
            }
            if (MoveOrNot)
            {
                ordinal = 0;
                break;
            }
            ordinal++;
        }
        break;
        case 1:
        {
            int t = MenuDongDiemDenCB(destination);
            NormalLine();
            if (t == -1)
            {
                ordinal = 0;
                break;
            }
            WatchingFlight = tmp.First;
            for (int i = 1; i < t && WatchingFlight != NULL; i++)
                WatchingFlight = WatchingFlight->next;
            if (WatchingFlight == NULL)
                return;
            WatchingFlight = TimCB(LCB, WatchingFlight->Data.MaCB);
            RemoveFlight();
            ordinal++;
        }
        break;
        case 2:
        {
            ShowCur(false);
            gotoxy(48, 4);
            cout << " Danh sach hanh khach co ma chuyen bay " << WatchingFlight->Data.MaCB << " toi " << WatchingFlight->Data.SanBayDen;
            cout << " luc ";
            OutputDateTime(WatchingFlight->Data.TimeDi);
            gotoxy(X_Notification, Y_Notification + 9);
            cout << "Ve co mau Do la ve";
            gotoxy(X_Notification, Y_Notification + 10);
            cout << "da co nguoi dat cho!";
            ChoosenTicket = ChooseTicket(WatchingFlight->Data, 1);

            if (ChoosenTicket == -1)
            {
                ordinal = 1;
                break;
            }
            IDHanhKhach = "";
            ordinal++;
        }
        break;
        case 3:
        {
            int target = -1;
            NormalLine();
            for (int i = 0; i < WatchingFlight->Data.TongSoDaBan; i++)
            {
                if (WatchingFlight->Data.TicketList[i].Status == ChoosenTicket)
                {
                    IDHanhKhach = WatchingFlight->Data.TicketList[i].CCCD;
                }
            }
            for (int i = 0; i < WatchingFlight->Data.TongSoDaBan; i++)
            {
                if (WatchingFlight->Data.TicketList[i].CCCD == IDHanhKhach)
                {
                    target = i;
                    break;
                }
            }
            Tree tmp = FindPassenger(root, IDHanhKhach.c_str());
            CreateForm(ContentPassenger, 2, 6, 35);
            gotoxy(X_Them + 12, 0 * 3 + Y_Them);
            cout << IDHanhKhach;
            gotoxy(X_Them + 12, 1 * 3 + Y_Them);
            cout << tmp->Data.Ho;
            gotoxy(X_Them + 12, 2 * 3 + Y_Them);
            cout << tmp->Data.Ten;
            gotoxy(X_Them + 12, 3 * 3 + Y_Them);
            cout << tmp->Data.Phai;
            RemoveNotification();
            cf = RemoveConfirm();
            NormalLine();
            if (cf == 0)
            {
                for (int i = target + 1; i < WatchingFlight->Data.TongSoDaBan; i++)
                {
                    WatchingFlight->Data.TicketList[i - 1] = WatchingFlight->Data.TicketList[i];
                }
                WatchingFlight->Data.TongSoDaBan--;
                if (WatchingFlight->Data.TrangThai == 2 && WatchingFlight->Data.TongSoDaBan < WatchingFlight->Data.SoVe)
                {
                    WatchingFlight->Data.TrangThai = 1;
                }
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "Huy ve thanh cong !!!";
                ordinal = 2;
                RemoveFormComplete();
            }
            else
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 4);
                cout << " Huy ve khong ";
                gotoxy(X_Notification, Y_Notification + 5);
                cout << " thanh cong !!!";
                ordinal = 2;
                RemoveFormComplete();
            }
        }
        break;
        }
    }
}

// SO DO CHO NGOI
void SoDoChoNgoi()
{
    int ordinal = 0;
    bool SaveOrNot = true;
    bool MoveOrNot = false;
    int DestinationExisted = -1; // tim kiem san bay den co ton tai khong
    string destination;
    DayTime DT;
    PTRCB WatchingFlight = NULL;
    int ChoosenTicket;
    int cf = -1;
    string IDHanhKhach;
    while (true)
    {
        switch (ordinal)
        {
        case 0:
        {
            SaveOrNot = true;
            MoveOrNot = false;
            CreateForm(ContentFlight, 1, 2, 35);
            ShowCur(true);
            ConstraintsForLetterAndSpace(destination, MoveOrNot, ordinal, SaveOrNot, 12);
            if (SaveOrNot == false)
            {
                RemoveFormComplete();
                return;
            }
            if (destination == "")
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "Vui Long Khong";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << " Bo Trong";
                if (MoveOrNot)
                {
                    ordinal = 0;
                }
                break;
            }
            DestinationExisted = ViTriSBDen(LCB, destination.c_str());
            if (DestinationExisted == -1)
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "Khong co chuyen";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "bay toi " << destination;
                gotoxy(X_Notification, Y_Notification + 5);
                cout << "Vui long chon ";
                gotoxy(X_Notification, Y_Notification + 6);
                cout << "dia diem khac";
                if (MoveOrNot)
                {
                    ordinal = 0;
                }
                break;
            }
            if (MoveOrNot)
            {
                ordinal = 0;
                break;
            }
            ordinal++;
        }
        break;
        case 1:
        {
            int t = MenuDongDiemDenCB(destination);
            NormalLine();
            if (t == -1)
            {
                ordinal = 0;
                break;
            }
            WatchingFlight = tmp.First;
            for (int i = 1; i < t && WatchingFlight != NULL; i++)
                WatchingFlight = WatchingFlight->next;
            if (WatchingFlight == NULL)
                return;
            WatchingFlight = TimCB(LCB, WatchingFlight->Data.MaCB);
            RemoveFlight();
            ordinal++;
        }
        break;
        case 2:
        {
            ShowCur(false);
            gotoxy(48, 4);
            cout << " Danh sach hanh khach co ma chuyen bay " << WatchingFlight->Data.MaCB << " toi " << WatchingFlight->Data.SanBayDen;
            cout << " luc ";
            OutputDateTime(WatchingFlight->Data.TimeDi);
            gotoxy(X_Notification, Y_Notification + 9);
            cout << "Ve co mau Do la ve";
            gotoxy(X_Notification, Y_Notification + 10);
            cout << "da co nguoi dat cho!";
            if (WatchingFlight->Data.TrangThai == 0 || WatchingFlight->Data.TrangThai == 3)
            {
                TicketChairBoard(WatchingFlight->Data);
                int signal;
                while (true)
                {
                    signal = getch();
                    if (signal == ESC)
                    {
                        return;
                    }
                }
            }
            else
            {
                ChoosenTicket = ChooseTicket(WatchingFlight->Data, 1);
            }
            if (ChoosenTicket == -1)
            {
                ordinal = 1;
                break;
            }
            IDHanhKhach = "";
            ordinal++;
        }
        break;
        case 3:
        {
            SaveOrNot = true;
            int target = -1;
            NormalLine();
            for (int i = 0; i < WatchingFlight->Data.TongSoDaBan; i++)
            {
                if (WatchingFlight->Data.TicketList[i].Status == ChoosenTicket)
                {
                    IDHanhKhach = WatchingFlight->Data.TicketList[i].CCCD;
                }
            }
            Tree tmp = FindPassenger(root, IDHanhKhach.c_str());
            CreateForm(ContentPassenger, 2, 6, 35);
            ShowCur(true);
            NhapThongTinHK(root, true, SaveOrNot, IDHanhKhach.c_str(), cf);
            if (SaveOrNot == false)
            {
                RemoveFormComplete();
                ordinal = 2;
                break;
            }
            if (cf == 0)
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "Xua ve thanh cong !!!";
            }
            else
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "Xua ve khong";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "thanh cong !!!";
            }
            ordinal = 2;
            RemoveFormComplete();
        }
        break;
        }
    }
}

// DIEM DEN
void DiemDen()
{
    system("color 0B");
    int ordinal = 0;
    bool SaveOrNot = true;
    bool MoveOrNot = false;
    bool flag = true;
    int DestinationExisted = -1; // tim kiem san bay den co ton tai khong
    string destination;
    DayTime DT;
    while (true)
    {
        switch (ordinal)
        {
        case 0:
        {
            MoveOrNot = false;
            CreateForm(ContentFlight, 1, 2, 30);
            ShowCur(true);
            ConstraintsForLetterAndSpace(destination, MoveOrNot, ordinal, SaveOrNot, 12);
            if (SaveOrNot == false)
            {
                RemoveFormComplete();
                return;
            }
            if (destination == "")
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "Vui Long Khong";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << " Bo Trong";
                if (MoveOrNot)
                {
                    ordinal = 0;
                }
                break;
            }
            DestinationExisted = ViTriSBDen(LCB, destination.c_str());
            if (DestinationExisted == -1)
            {
                RemoveNotification();
                gotoxy(X_Notification, Y_Notification + 3);
                cout << "Khong co chuyen";
                gotoxy(X_Notification, Y_Notification + 4);
                cout << "bay toi " << destination;
                gotoxy(X_Notification, Y_Notification + 5);
                cout << "Vui long chon ";
                gotoxy(X_Notification, Y_Notification + 6);
                cout << "dia diem khac";
                if (MoveOrNot)
                {
                    ordinal = 0;
                }
                break;
            }
            if (MoveOrNot)
            {
                ordinal = 0;
                break;
            }
            RemoveFlight();
            ordinal++;
        }
        break;
        case 1:
        {
            flag = true;
            ShowCur(false);
            CopyListCBDD(LCB, tmp, destination);
            SelectionSortCB(tmp);
            TrangHienTaiCB = 1;
            TongSoTrangCB = (int)ceil((double)tmp.SoLuongCB / NumberPerPage);
            KhungHienThi(SpecifedFlight, 6, HoanhDoHienThiCB);
            HienSoLieuChuyenBayTren1Trang(tmp, 0, 1);
            gotoxy(77, 5);
            cout << " Danh sach cac chuyen bay toi thanh pho " << destination;
            int signal;
            while (flag == true)
            {
                while (kbhit())
                {
                    signal = getch();
                    if (signal == ESC)
                    {
                        flag = false;
                        ordinal = 0;
                        break;
                    }
                    else if (signal == KEY_LEFT && TrangHienTaiCB > 1)
                    {
                        HienSoLieuChuyenBayTren1Trang(tmp, (TrangHienTaiCB - 1) * NumberPerPage, 1);
                    }
                    else if (signal == KEY_RIGHT && TrangHienTaiCB < TongSoTrangCB)
                    {
                        HienSoLieuChuyenBayTren1Trang(tmp, (TrangHienTaiCB - 1) * NumberPerPage, 1);
                    }
                }
            }
        }
        break;
        }
    }
}

// XEM DS HANH KHACH CUA 1 CHUYEN BAY
void HienSoLieuHanhKhach(HanhKhach hk, int vitri, int a)
{
    gotoxy(HoanhDoHienThiHK[0] + 5, Y_HienThi + 3 + vitri * 2);
    printf("%-5d", vitri + a + 1);
    gotoxy(HoanhDoHienThiHK[2] + 3, Y_HienThi + 3 + vitri * 2);
    printf("%-12s", hk.CCCD);
    gotoxy(HoanhDoHienThiHK[3] + 3, Y_HienThi + 3 + vitri * 2);
    printf("%-16s", hk.Ho);
    gotoxy(HoanhDoHienThiHK[4] + 3, Y_HienThi + 3 + vitri * 2);
    printf("%-9s", hk.Ten);
    gotoxy(HoanhDoHienThiHK[5] + 5, Y_HienThi + 3 + vitri * 2);
    if (hk.Phai == 1)
        cout << "Nam";
    if (hk.Phai == 2)
        cout << "Nu ";
}

void HienSoLieuHanhKhachTren1Trang(Tree root, int BeginIndex, ChuyenBay F)
{
    system("color 0B");
    int i;
    for (i = 0; i + BeginIndex < F.TongSoDaBan && i < NumberPerPage; i++)
    {
        Tree p = FindPassenger(root, F.TicketList[i + BeginIndex].CCCD);
        if (p != NULL)
        {
            HienSoLieuHanhKhach(p->Data, i, BeginIndex);
            gotoxy(HoanhDoHienThiHK[1] + 5, Y_HienThi + 3 + i * 2);
            printf("%-3d", F.TicketList[i + BeginIndex].Status);
        }
    }
    XoaDuLieuDuThuaHK(i, 6, HoanhDoHienThiHK);
    gotoxy(118, 27);
    cout << "Trang " << TrangHienTaiHK << "/" << TongSoTrangHK;
}

void XemDSHanhKhach(Tree root, int flag)
{
    bool MoveOrNot = false;
    bool SaveOrNot = true;
    int ordinal = 0;
    PTRCB WatchingFlight = NULL;
    if (flag == 1)
    {
        ordinal = 0;
        string result;
        bool flag = true;
        while (true)
        {
            switch (ordinal)
            {
            case 0:
            {
                SaveOrNot = true;
                MoveOrNot = false;
                CreateForm(ContentFlight, 0, 1, 30);
                ShowCur(true);
                ConstraintForLetterAndNumber(result, MoveOrNot, ordinal, SaveOrNot, 12);
                if (SaveOrNot == false)
                {
                    RemoveFormComplete();
                    return;
                }
                if (result == "")
                {
                    RemoveNotification();
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << "Vui Long Khong";
                    gotoxy(X_Notification, Y_Notification + 4);
                    cout << " Bo Trong";
                    if (MoveOrNot)
                    {
                        ordinal = 0;
                    }
                    break;
                }
                WatchingFlight = TimCB(LCB, result.c_str());
                if (WatchingFlight == NULL)
                {
                    RemoveNotification();
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << " Ma Chuyen Bay";
                    gotoxy(X_Notification, Y_Notification + 4);
                    cout << " khong ton tai";
                    if (MoveOrNot)
                    {
                        ordinal = 0;
                    }
                    break;
                }
                if (MoveOrNot)
                {
                    ordinal = 0;
                    break;
                }
                RemoveFlight();
                ordinal++;
            }
            break;
            case 1:
            {
                flag = true;
                ShowCur(false);
                TrangHienTaiHK = 1;
                TongSoTrangHK = (int)ceil((double)WatchingFlight->Data.TongSoDaBan / NumberPerPage);

                HienSoLieuHanhKhachTren1Trang(root, 0, WatchingFlight->Data);

                KhungHienThi(ContentPassenger, 6, HoanhDoHienThiHK);

                gotoxy(35, 4);
                printf("%-120s", " ");
                gotoxy(35, 5);
                printf("%-120s", " ");
                gotoxy(X_TieuDe, Y_TieuDe + 3);
                cout << " DANH SACH HANH KHACH THUOC CHUYEN BAY " << WatchingFlight->Data.MaCB;
                WatchingFlight->Data.SanBayDen;
                gotoxy(X_TieuDe, Y_TieuDe + 4);
                cout << " Ngay gio khoi hanh: ";
                OutputDateTime(WatchingFlight->Data.TimeDi);
                gotoxy(X_TieuDe + 38, Y_TieuDe + 4);
                cout << "Noi den: " << WatchingFlight->Data.SanBayDen;

                int signal;
                while (flag == true)
                {
                    while (kbhit())
                    {
                        signal = getch();
                        if (signal == ESC)
                        {
                            flag = false;
                            ordinal = 0;
                            break;
                        }
                        if (signal == KEY_LEFT && TrangHienTaiHK > 1)
                        {
                            TrangHienTaiHK--;
                            HienSoLieuHanhKhachTren1Trang(root, (TrangHienTaiHK - 1) * NumberPerPage, WatchingFlight->Data);
                        }
                        else if (signal == KEY_RIGHT && TrangHienTaiHK < TongSoTrangHK)
                        {
                            TrangHienTaiHK++;
                            HienSoLieuHanhKhachTren1Trang(root, (TrangHienTaiHK - 1) * NumberPerPage, WatchingFlight->Data);
                        }
                    }
                }
            }
            break;
            }
        }
    }
    else if (flag == 0)
    {
        ordinal = 0;
        bool flag = true;
        int DestinationExisted = -1; // tim kiem san bay den co ton tai khong
        string destination;
        DayTime DT;
        while (true)
        {
            switch (ordinal)
            {
            case 0:
            {
                MoveOrNot = false;
                CreateForm(ContentFlight, 1, 2, 35);
                ShowCur(true);
                ConstraintsForLetterAndSpace(destination, MoveOrNot, ordinal, SaveOrNot, 12);
                if (SaveOrNot == false)
                {
                    RemoveFormComplete();
                    return;
                }
                if (destination == "")
                {
                    RemoveNotification();
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << "Vui Long Khong";
                    gotoxy(X_Notification, Y_Notification + 4);
                    cout << " Bo Trong";
                    if (MoveOrNot)
                    {
                        ordinal = 0;
                    }
                    break;
                }
                DestinationExisted = ViTriSBDen(LCB, destination.c_str());
                if (DestinationExisted == -1)
                {
                    RemoveNotification();
                    gotoxy(X_Notification, Y_Notification + 3);
                    cout << "Khong co chuyen";
                    gotoxy(X_Notification, Y_Notification + 4);
                    cout << "bay toi " << destination;
                    gotoxy(X_Notification, Y_Notification + 5);
                    cout << "Vui long chon ";
                    gotoxy(X_Notification, Y_Notification + 6);
                    cout << "dia diem khac";
                    if (MoveOrNot)
                    {
                        ordinal = 0;
                    }
                    break;
                }
                if (MoveOrNot)
                {
                    ordinal = 0;
                    break;
                }
                ordinal++;
            }
            break;
            case 1:
            {
                int t = MenuDongDiemDenCB(destination);
                NormalLine();
                if (t == -1)
                {
                    ordinal = 0;
                    break;
                }
                WatchingFlight = tmp.First;
                for (int i = 1; i < t && WatchingFlight != NULL; i++)
                    WatchingFlight = WatchingFlight->next;
                if (WatchingFlight == NULL)
                    return;
                WatchingFlight = TimCB(LCB, WatchingFlight->Data.MaCB);
                ordinal++;
            }
            break;
            case 2:
            {
                flag = true;
                RemoveFlight();
                ShowCur(false);
                TrangHienTaiHK = 1;
                TongSoTrangHK = (int)ceil((double)WatchingFlight->Data.TongSoDaBan / NumberPerPage);

                HienSoLieuHanhKhachTren1Trang(root, 0, WatchingFlight->Data);

                KhungHienThi(ContentPassenger, 6, HoanhDoHienThiHK);

                gotoxy(35, 4);
                printf("%-120s", " ");
                gotoxy(35, 5);
                printf("%-120s", " ");
                gotoxy(X_TieuDe, Y_TieuDe + 3);
                cout << " DANH SACH HANH KHACH THUOC CHUYEN BAY " << WatchingFlight->Data.MaCB;
                WatchingFlight->Data.SanBayDen;
                gotoxy(X_TieuDe, Y_TieuDe + 4);
                cout << " Ngay gio khoi hanh: ";
                OutputDateTime(WatchingFlight->Data.TimeDi);
                gotoxy(X_TieuDe + 38, Y_TieuDe + 4);
                cout << "Noi den: " << WatchingFlight->Data.SanBayDen;

                int signal;
                while (flag == true)
                {
                    while (kbhit())
                    {
                        signal = getch();
                        if (signal == ESC)
                        {
                            ordinal = 1;
                            flag = false;
                            break;
                        }
                        if (signal == KEY_LEFT && TrangHienTaiHK > 1)
                        {
                            TrangHienTaiHK--;
                            HienSoLieuHanhKhachTren1Trang(root, (TrangHienTaiHK - 1) * NumberPerPage, WatchingFlight->Data);
                        }
                        else if (signal == KEY_RIGHT && TrangHienTaiHK < TongSoTrangHK)
                        {
                            TrangHienTaiHK++;
                            HienSoLieuHanhKhachTren1Trang(root, (TrangHienTaiHK - 1) * NumberPerPage, WatchingFlight->Data);
                        }
                    }
                }
            }
            break;
            }
        }
    }
}

// SO LAN THUC HIEN CHUYEN BAY
void SoLanThucHienChuyenBay()
{
    system("cls");
    ListMayBay tmp;
    CopyListMayBay(dsmb, tmp);
    BubbleSort(tmp);

    TongSoTrangMB = (int)ceil((double)tmp.SoLuong / NumberPerPage);
    KhungHienThi(StaticsTable, 2, HoanhDoHienThiMB);
    HienSoLieuMayBayTren1Trang(tmp, 0, 1);
    gotoxy(X_TieuDe - 7, Y_TieuDe + 1);
    cout << " SO CHUYEN BAY DA THUC HIEN CUA CAC MAY BAY";
    int signal;
    while (true)
    {
        while (kbhit())
        {
            signal = getch();
            if (signal == ESC)
            {
                GiaiPhongMayBay(tmp);
                return;
            }
            if (signal == KEY_LEFT && TrangHienTaiMB > 1)
            {
                TrangHienTaiMB--;
                HienSoLieuMayBayTren1Trang(tmp, (TrangHienTaiMB - 1) * NumberPerPage, 1);
            }
            else if (signal == KEY_RIGHT && TrangHienTaiMB < TongSoTrangMB)
            {
                TrangHienTaiMB++;
                HienSoLieuMayBayTren1Trang(tmp, (TrangHienTaiMB - 1) * NumberPerPage, 1);
            }
        }
    }
}