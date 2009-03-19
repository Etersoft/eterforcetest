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

#define COLOR_TEST 0xF0F0F0

void test_memdc()
{
    HDC hdc, hdcsrc;
    RECT rc, dst;
    POINT pt;
    HBRUSH hbr = CreateSolidBrush(COLOR_TEST);
    LOGBRUSH lgbr;
    HBITMAP hbmp;
    LOGPALETTE lgp;
    HPALETTE hpl;
    char bmibuf[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
    BITMAPINFO *bmi;
    BYTE *bits;
    DWORD ok;

    printf("\n\n* * *  memory DC operations  * * *\n");

    ok = (DWORD)CreateCompatibleDC(NULL);
    MSTART(ok, "CreateCompatibleDC/DeleteDC", 1000) {
        hdc = CreateCompatibleDC(NULL);
        DeleteDC(hdc);
    } MEND
    DeleteDC((HDC)ok);

    hdc = CreateCompatibleDC(NULL);
    hdcsrc = CreateCompatibleDC(NULL);

    ok = (DWORD)CreateCompatibleBitmap( hdc, 200, 200 );
    MSTART(ok, "CreateCompatibleBitmap/DeleteObject", 100) {
        hbmp = CreateCompatibleBitmap( hdc, 200, 200 );
        DeleteObject(hbmp);
    } MEND
    DeleteObject((HBITMAP)ok);

    ok = (DWORD)CreateBitmap( 200, 200, 1, 16, NULL );
    MSTART(ok, "CreateBitmap/DeleteObject", 100) {
        hbmp = CreateBitmap( 200, 200, 1, 16, NULL );
        DeleteObject(hbmp);
    } MEND
    DeleteObject((HBITMAP)ok);

    if (!hdc || !hbmp || !hdcsrc) return;

    bmi = ( BITMAPINFO* ) bmibuf;
    memset( bmi, 0, sizeof(bmibuf) );

    bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi->bmiHeader.biHeight = 200;
    bmi->bmiHeader.biWidth = 200;
    bmi->bmiHeader.biPlanes = 1;
    bmi->bmiHeader.biBitCount = 24;
    bmi->bmiHeader.biCompression = BI_RGB;
    bmi->bmiHeader.biSizeImage = bmi->bmiHeader.biHeight * bmi->bmiHeader.biWidth * 4;

    hbmp = CreateDIBSection( hdc, bmi, DIB_RGB_COLORS, (void**)&bits, 0, 0 );
    SelectObject( hdc, hbmp );
    hbmp = CreateDIBSection( hdcsrc, bmi, DIB_RGB_COLORS, (void**)&bits, 0, 0 );
    SelectObject( hdcsrc, hbmp );

    ok = MoveToEx( hdc, 10, 10, &pt );
    MSTART(ok, "MoveToEx", 100) {
        MoveToEx( hdc, 10, 10, &pt );
    } MEND

    ok = StretchBlt( hdc, 100, 100, 16, 16, hdcsrc, 0, 0, 32, 32, SRCCOPY );
    MSTART(ok, "StretchBlt", 5000) {
        StretchBlt( hdc, 100, 100, 16, 16, hdcsrc, 0, 0, 32, 32, SRCCOPY );
    } MEND

    SelectObject( hdc, hbr );

    ok = PatBlt( hdc, 100, 100, 16, 16, PATCOPY );
    MSTART(ok, "PatBlt", 100) {
        PatBlt( hdc, 100, 100, 16, 16, PATCOPY );
    } MEND

    ok = GetObjectA( hbr, sizeof(lgbr), &lgbr );
    MSTART(ok, "GetObjectA", 100) {
        GetObjectA( hbr, sizeof(lgbr), &lgbr );
    } MEND

    ok = GetObjectW( hbr, sizeof(lgbr), &lgbr );
    MSTART(ok, "GetObjectW", 100) {
        GetObjectW( hbr, sizeof(lgbr), &lgbr );
    } MEND

    ok = BitBlt( hdc, 100, 100, 32, 32, hdcsrc, 0, 0, SRCCOPY );
    MSTART(ok, "BitBlt", 100) {
        BitBlt( hdc, 100, 100, 32, 32, hdcsrc, 0, 0, SRCCOPY );
    } MEND

    SetRect( &rc, 10, 10, 50, 50 );

    ok = FillRect( hdc, &rc, hbr );
    MSTART(ok, "FillRect", 100) {
        FillRect( hdc, &rc, hbr );
    } MEND

    ok = OffsetRect( &rc, 1, 1 );
    MSTART(ok, "OffsetRect", 1) {
        OffsetRect( &rc, 1, 1 );
    } MEND

    ok = CopyRect( &dst, &rc );
    MSTART(ok, "CopyRect", 1) {
        CopyRect( &dst, &rc );
    } MEND

    SetRect( &rc, 10, 10, 50, 50 );
    pt.x = 15;
    pt.y = 15;

    ok = PtInRect( &rc, pt );
    MSTART(ok, "PtInRect", 1) {
        PtInRect( &rc, pt );
    } MEND

    ok = InflateRect( &rc, 1, 1 );
    MSTART(ok, "InflateRect", 1) {
        InflateRect( &rc, 1, 1 );
    } MEND

    ok = (DWORD)SelectObject( hdc, hbr );
    MSTART(ok, "SelectObject", 50) {
        SelectObject( hdc, hbr );
    } MEND

    ok = GetSysColor(COLOR_WINDOW);
    MSTART(ok, "GetSysColor", 1) {
        GetSysColor(COLOR_WINDOW);
    } MEND

    ok = DeleteObject(hbr);
    MSTART(ok, "Create/DeleteObject", 10) {
        hbr = CreateSolidBrush(COLOR_TEST);
        DeleteObject(hbr);
    } MEND

    ok = SetTextColor( hdc, COLOR_TEST );
    MSTART((ok != CLR_INVALID), "SetTextColor", 10) {
        SetTextColor( hdc, COLOR_TEST );
    } MEND

    ok = SetBkColor( hdc, COLOR_TEST );
    MSTART((ok != CLR_INVALID), "SetBkColor", 10) {
        SetBkColor( hdc, COLOR_TEST );
    } MEND

    lgp.palVersion = 1;
    lgp.palNumEntries = 1;

    ok = (DWORD)CreatePalette(&lgp);
    MSTART(ok, "CreatePalette/DeleteObject", 10) {
        hpl = CreatePalette(&lgp);
        DeleteObject(hpl);
    } MEND
    DeleteObject((HPALETTE)ok);

    hpl = CreatePalette(&lgp);

    ok = (DWORD)SelectPalette( hdc, hpl, FALSE );
    MSTART(ok, "SelectPalette/RealizePalette", 10) {
        SelectPalette( hdc, hpl, FALSE );
        RealizePalette(hdc);
    } MEND

    DeleteDC(hdc);
}
