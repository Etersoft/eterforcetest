/*
 * ETERFORCETEST
 *
 * Copyright 2008 Vitaly Lipatov, Etersoft
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include <windows.h>
#include "eterforcetest.h"

static INT_PTR CALLBACK MSGBOX_DlgProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
 DWORD ok;
 HWND ctrl;

 switch (message)
 {
    case WM_INITDIALOG:

        ok = (DWORD)GetDlgItem( hWnd, IDOK );
        MSTART(ok, "GetDlgItem", 200) {
            GetDlgItem( hWnd, IDOK );
        } MEND

        ctrl = GetDlgItem( hWnd, IDOK );

        ok = GetDlgCtrlID(ctrl);
        MSTART(ok, "GetDlgCtrlID", 6) {
            GetDlgCtrlID(ctrl);
        } MEND

        EndDialog( hWnd, 0 );
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
 }

 return 0;
}

BOOL dlg_RegisterWindowClasses(void)
{
    WNDCLASSA cls;

    cls.style = CS_DBLCLKS;
    cls.lpfnWndProc = DefWindowProc;
    cls.cbClsExtra = 0;
    cls.cbWndExtra = 0;
    cls.hInstance = GetModuleHandleA(0);
    cls.hIcon = 0;
    cls.hCursor = LoadCursorA(0, (LPSTR)IDC_ARROW);
    cls.hbrBackground = GetStockObject(WHITE_BRUSH);
    cls.lpszMenuName = NULL;
    cls.lpszClassName = "WinDlg";

    if(!RegisterClassA(&cls)) return FALSE;

    return TRUE;
}

LPWORD lpwAlign(LPWORD lpIn)
{
    ULONG ul;

    ul = (ULONG)lpIn;
    ul ++;
    ul >>=1;
    ul <<=1;
    return (LPWORD)ul;
}

void test_dialog()
{
    HWND hwnd;
    HGLOBAL hgbl;
    LPDLGTEMPLATE lpdt;
    LPDLGITEMTEMPLATE lpdit;
    LPWORD lpw;
    LPWSTR lpwsz;
    int nchar;

    printf("\n\n* * *  Dialog operations  * * *\n");

    if (!dlg_RegisterWindowClasses()) return;

    hwnd = CreateWindowEx( 0, "WinDlg", "Test window",
                            WS_OVERLAPPED | WS_CAPTION,
                            100, 100, 100, 100,
                            0, 0, GetModuleHandle(0), NULL );

    hgbl = GlobalAlloc( GMEM_ZEROINIT, 1024 );
    if (!hgbl)
        return;

    lpdt = (LPDLGTEMPLATE)GlobalLock(hgbl);

    lpdt->style = WS_OVERLAPPED | WS_CAPTION;
    lpdt->dwExtendedStyle = 0;
    lpdt->cdit = 1;
    lpdt->x = 0;
    lpdt->y = 0;
    lpdt->cx = 100;
    lpdt->cy = 100;

    lpw = (LPWORD)(lpdt + 1);
    *lpw++ = 0;             /* No menu */
    *lpw++ = 0;             /* Predefined dialog box class (by default) */

    lpwsz = (LPWSTR)lpw;
    nchar = 1 + MultiByteToWideChar( CP_ACP, 0, "Test Dialog", -1, lpwsz, 50 );
    lpw += nchar;

    lpw = lpwAlign(lpw);    /* Align DLGITEMTEMPLATE on DWORD boundary */
    lpdit = (LPDLGITEMTEMPLATE)lpw;
    lpdit->x  = 10; lpdit->y  = 70;
    lpdit->cx = 80; lpdit->cy = 20;
    lpdit->id = IDOK;       /* OK button identifier */
    lpdit->style = WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON;

    lpw = (LPWORD)(lpdit + 1);
    *lpw++ = 0xFFFF;
    *lpw++ = 0x0080;        /* Button class */

    lpwsz = (LPWSTR)lpw;
    nchar = 1 + MultiByteToWideChar( CP_ACP, 0, "OK", -1, lpwsz, 50 );
    lpw += nchar;
    lpw = lpwAlign(lpw);    /* Align creation data on DWORD boundary */
    *lpw++ = 0;             /* No creation data */

    GlobalUnlock(hgbl);

    DialogBoxIndirectW( GetModuleHandleA(0), (LPDLGTEMPLATE)hgbl, hwnd, (DLGPROC)MSGBOX_DlgProc );

    GlobalFree(hgbl);
    DestroyWindow(hwnd);
}
