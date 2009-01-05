/*
 * ETERFORCETEST
 *
 * Copyright 2008 Vitaly Lipatov, Etersoft
 * Copyright 2008 Ilya Shpigor, Etersoft
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

#define MAX_STR 40

BOOL menu_RegisterWindowClasses(void)
{
    WNDCLASSA cls;

    cls.style = CS_DBLCLKS;
    cls.lpfnWndProc = DefWindowProc;
    cls.cbClsExtra = 0;
    cls.cbWndExtra = 0;
    cls.hInstance = GetModuleHandleA(0);
    cls.hIcon = 0;
    cls.hIcon = LoadIconA( 0, (LPSTR)IDI_APPLICATION );
    cls.hCursor = LoadCursorA( 0, (LPSTR)IDC_ARROW );
    cls.hbrBackground = GetStockObject(WHITE_BRUSH);
    cls.lpszMenuName = NULL;
    cls.lpszClassName = "Win";

    if(!RegisterClassA(&cls)) return FALSE;

    cls.lpszClassName = "MenuClass";
    cls.style = CS_HREDRAW | CS_VREDRAW;
    cls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    cls.lpszMenuName = 0;

    if(!RegisterClassA(&cls)) return FALSE;

    return TRUE;
}

void test_menu()
{
    HWND hwnd;
    HMENU hmenu;
    char buffer[MAX_STR];
    DWORD ok;

    printf("\n\n* * *  Menu operations  * * *\n");

    if (!menu_RegisterWindowClasses()) return;

    hwnd = CreateWindowEx( 0, "Win", "Test window",
                            WS_OVERLAPPED | WS_CAPTION,
                            100, 100, 100, 100,
                            0, 0, GetModuleHandle(0), NULL );

    hmenu = CreateMenu();
    AppendMenu( hmenu, MF_STRING, 0, "&Enabled" );
    AppendMenu( hmenu, MF_STRING | MF_DISABLED, 0, "&Disabled" );
    SetMenu( hwnd, hmenu );

    ok = GetMenuStringA( hmenu, 0, buffer, MAX_STR, MF_BYPOSITION );
    MSTART(ok, "GetMenuStringA", 6) {
        GetMenuStringA( hmenu, 0, buffer, MAX_STR, MF_BYPOSITION );
    } MEND

    ok = GetMenuItemID( hmenu, 0 );
    MSTART((ok != -1), "GetMenuItemID", 6) {
        GetMenuItemID( hmenu, 0 );
    } MEND

    ok = GetMenuState( hmenu, 0, MF_BYPOSITION );
    MSTART((ok != -1), "GetMenuState", 6) {
        GetMenuState( hmenu, 0, MF_BYPOSITION );
    } MEND

    ok = GetMenuItemCount(hmenu);
    MSTART((ok != -1), "GetMenuItemCount", 6) {
        GetMenuItemCount(hmenu);
    } MEND

    ok = EnableMenuItem( hmenu, 1, MF_BYPOSITION | MF_ENABLED );
    MSTART((ok != -1), "EnableMenuItem", 6) {
        if (ok == MF_ENABLED)
            ok = EnableMenuItem( hmenu, 1, MF_BYPOSITION | MF_DISABLED );
        else
            ok = EnableMenuItem( hmenu, 1, MF_BYPOSITION | MF_ENABLED );
    } MEND

    ok = AppendMenuA( hmenu, MF_STRING, 0, "Test" );
    MSTART(ok, "AppendMenuA/DeleteMenu", 20){
        DeleteMenu( hmenu, 2, MF_BYPOSITION );
        AppendMenuA( hmenu, MF_STRING, 0, "Test" );
    } MEND

    DestroyMenu(hmenu);
    DestroyWindow(hwnd);
}
