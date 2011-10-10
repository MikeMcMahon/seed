#ifndef __FONTS_H_INCLUDE__
#define __FONTS_H_INCLUDE__

#include <d3d10.h>
#include <D3DX10.h>

#define HELVETICA L"Helvetica"
#define TIMES L"Times"
#define ARIAL L"Arial"

bool InitFont(ID3D10Device*, ID3DX10Font*, int , UINT, UINT, LPCWSTR);

#endif