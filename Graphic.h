#pragma once
#ifndef INC_GRAPHIC
#define INC_GRAPHIC 1
#include "stdafx.h"
class Graphic
{
public:
	Graphic();
	~Graphic();
	static void drawImage(int x,int y, image_t image, int align = 0, float scale=1.0,int alpha = 255);
	static void createImage(char img[], image_t &prtImg);
	static void prepare();
	static void drawNumber(int x, int y, int num, int align = 0);
	static std::vector<image_t>* images;
	static long currentID;
	static long genNewId();

};


#define SCR_V_LEFT		 0x0000
#define SCR_V_RIGHT		 0x0004
#define SCR_V_CENTER	 0x0008
#define SCR_H_LEFT		 0x000c
#define SCR_H_RIGHT		 0x0020
#define SCR_H_CENTER	 0x0040

#define IMG_V_LEFT		 0x0000
#define IMG_V_RIGHT		 0x0400
#define IMG_V_CENTER	 0x0800
#define IMG_H_LEFT		 0x0000
#define IMG_H_RIGHT		 0x0c00
#define IMG_H_CENTER	 0x8000

#endif