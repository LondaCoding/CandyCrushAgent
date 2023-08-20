#include <iostream>
#include <Windows.h>



int main(){


    return(0);
}

void CapturePixels(int x, int y, int width, int height) {
    HDC hdcScreen = GetDC(NULL);  // Get a handle to the entire screen
    HDC hdcMemory = CreateCompatibleDC(hdcScreen);
    
    HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, width, height);
    HBITMAP hBitmapOld = (HBITMAP)SelectObject(hdcMemory, hBitmap);
    
    BitBlt(hdcMemory, 0, 0, width, height, hdcScreen, x, y, SRCCOPY);
    
    // Retrieve pixel data
    BITMAPINFOHEADER bi = {0};
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;  // Negative height to indicate top-down bitmap
    bi.biPlanes = 1;
    bi.biBitCount = 32;     // 32-bit RGBA format
    
    DWORD *pixels = new DWORD[width * height];
    GetDIBits(hdcMemory, hBitmap, 0, height, pixels, (BITMAPINFO *)&bi, DIB_RGB_COLORS);
    
    // Process or save pixel data here
    
    // Clean up
    delete[] pixels;
    SelectObject(hdcMemory, hBitmapOld);
    DeleteObject(hBitmap);
    DeleteDC(hdcMemory);
    ReleaseDC(NULL, hdcScreen);
}
