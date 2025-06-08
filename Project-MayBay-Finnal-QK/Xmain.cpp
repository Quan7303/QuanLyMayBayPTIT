#include <iostream>
#include "XuLy.h"
int main()
{
    fullscreen();
    haha();

    InitListMayBay(dsmb);
    ReadMBFromFile(dsmb);

    InitChuyenBay(cb);
    InitListCB(LCB);
    ReadFlightFileFromFile(LCB, dsmb);

    CreateTree(root);
    ReadPassengerFromFile(root);

    system("cls");
    int ConTro;
    int ConTroMB;
    int ConTroCB;
    int ConTroVe;
    bool Exit = false;
    int cf = -1;
    while (Exit == false)
    {
        ConTro = MenuDong(ThucDon);
        bool ExitMB = false;
        bool ExitCB = false;
        bool ExitVe = false;
        switch (ConTro)
        {
        case 1:
            while (ExitMB == false)
            {
                ConTroMB = MenuDongMB(ThucDonMB);
                switch (ConTroMB)
                {
                case 1:
                    NormalLine();
                    if (dsmb.SoLuong == MaxAirplane)
                    {
                        gotoxy(X_Notification, Y_Notification + 2);
                        cout << " Danh sach day,";
                        gotoxy(X_Notification, Y_Notification + 3);
                        cout << " khong the them";
                        break;
                    }
                    CreateForm(ContentAirplane, 0, 3, 35);
                    NhapThongTinMB(dsmb);
                    ShowCur(false);
                    break;
                case 2:
                    NormalLine();
                    if (dsmb.SoLuong == 0)
                    {
                        gotoxy(X_Notification, Y_Notification + 2);
                        cout << "Danh sach rong";
                        gotoxy(X_Notification, Y_Notification + 3);
                        cout << " khong the xoa!";
                        break;
                    }
                    CreateForm(ContentAirplane, 0, 1, 35);
                    NhapThongTinMB(dsmb, false, true);
                    ShowCur(false);
                    break;
                case 3:
                    NormalLine();
                    CreateForm(ContentAirplane, 0, 3, 35);
                    NhapThongTinMB(dsmb, true, false);
                    ShowCur(false);
                    break;
                case 4:
                    ExitMB = true;
                    break;
                }
            }
            break;
        case 2:
            CopyListCB(LCB, tmp);
            SelectionSortCB(tmp);
            while (ExitCB == false)
            {
                ConTroCB = MenuDongCB(ThucDonCB);
                switch (ConTroCB)
                {
                case 1:
                    NormalLine();
                    CreateForm(ContentFlight, 0, 6, 35);
                    NhapThongTinCB(LCB, false, false);
                    ShowCur(false);
                    break;
                case 2:
                    NormalLine();
                    CreateForm(ContentFlight, 0, 1, 35);
                    NhapThongTinCB(LCB, false, true);
                    ShowCur(false);
                    break;
                case 3:
                    NormalLine();
                    CreateForm(ContentFlight, 0, 6, 35);
                    NhapThongTinCB(LCB, true, false);
                    ShowCur(false);
                    break;
                case 4:
                    ExitCB = true;
                    break;
                }
            }
            break;
        case 3:
            TuDongCapNhatTrangThai(LCB);
            while (ExitVe == false)
            {
                ConTroVe = MenuDongVe(ThucDonVe);
                switch (ConTroVe)
                {
                case 1:
                    NormalLine();
                    DatVeCB(root);
                    break;
                case 2:
                    NormalLine();
                    HuyVeCB(root);
                    break;
                case 3:
                    NormalLine();
                    DiemDen();
                    break;
                case 4:
                    NormalLine();
                    SoDoChoNgoi();
                    break;
                case 5:
                    NormalLine();
                    cf = RemoveConfirmVe();
                    if (cf == 0)
                    {
                        NormalLine();
                        XemDSHanhKhach(root, 0);
                    }
                    else if (cf == 1)
                    {
                        NormalLine();
                        XemDSHanhKhach(root, 1);
                    }
                    break;
                case 6:
                    ExitVe = true;
                    break;
                }
            }
            break;
        case 4:
            NormalLine();
            SoLanThucHienChuyenBay();
            break;
        case SoItem:
            WriteMBToFile(dsmb);
            TuDongCapNhatTrangThai(LCB);
            WriteFlightToFile(LCB);
            SavePassengerToFile(root);
            GiaiPhong(root);
            GiaiPhongMayBay(dsmb);
            delete[] cb.TicketList;
            CleanUpFlightList(LCB);
            CleanUpFlightList(tmp);
            system("color 0B");
            Exit = true;
            system("cls");
            break;
        }
    }
}
