#include "Graphic.h"



Graphic::Graphic()
{
  
}

Graphic::~Graphic()
{
}
  void Graphic::drawImage(int x, int y, image_t image, int align,float scale,int alpha) {
	 
	  if (GSurface->IsTextureIDValid(image.id)) {
		  int dx = 0, dy = 0, w = (int)(image.width*scale), h = (int)(image.height*scale);
		  
		  GSurface->DrawSetColor(255, 255, 255, alpha);
		  GSurface->DrawSetTexture(image.id);

		  if (align == 0) {
			  dx = x;
			  dy = y;
		  }
		  else {
			  dx = x;
			  if (align&SCR_H_RIGHT)
				  dx = scr_Size[0] - x;
			  else if (align&SCR_H_CENTER)
				  dx = scr_Size[0] / 2.0 + x;

			  dy = y;
			  if (align&SCR_V_RIGHT)
				  dy = scr_Size[1] - y;
			  else if (align&SCR_V_CENTER)
				  dy = scr_Size[1] / 2.0 + y;

			   if (align&IMG_H_CENTER)

				   dx -= w / 2;
			  else if (align&IMG_H_RIGHT)
				  dx -= w;
			
			  else  if (align&IMG_H_LEFT)
				  dx += 0;
			  if (align&IMG_V_CENTER)
				  dy -= h / 2.0;

			  else if (align&IMG_V_RIGHT)
				  dy -= h;
			  else if (align&IMG_V_LEFT)
				  dy += 0;
		  }
		  GSurface->DrawTexturedRect(dx, dy, dx + w, dy + h);
		  GSurface->DrawSetTexture(0);
		 

	  }
}
  void Graphic::createImage(char img[], image_t &prtImg)
{
	 
	prtImg.id = Graphic::genNewId();
	GSurface->DrawSetTextureFile(prtImg.id, img, false, false);
	GSurface->DrawGetTextureSize(prtImg.id, prtImg.width, prtImg.height);
	GSurface->DrawSetTexture(0);
	char fInfo[512];
	sprintf(fInfo, "%s [W: %d - H: %d] %d", img, prtImg.width, prtImg.height , prtImg.id);
	LogWriter(fInfo);
	 
}
  void Graphic::prepare()
  {
	  for (int i = 0; i < 10; i++)
	  {
		  char number[32];
		  sprintf(number, "hud/number/number_%d",i);
		  image_t img;
		  Graphic::createImage(number, img);
		  Graphic::images->push_back(img);
	  }
  }
  void Graphic::drawNumber(int x, int y, int num, int align  ) {
	  char number[10];
	  sprintf(number, "%d", num);
	  int length = strlen(number);
	  int dx = 0, dy = 0, index = 0;
	  int w, h;
	  int inc = 1;

	  dx = x+ length *14/2;
	  dy = y;

	  if (align == IMG_H_CENTER)
	  {
		  inc = 1;
	  }
	  else  if (align == IMG_H_RIGHT){
		  dx -= (length * 14) / 2;
	  }
	  else {
		
		  dx += length * 14 / 2;
	  }
 
	  do {
		  int lx = num % 10;
		  num /= 10;
		  image_t img = Graphic::images->at(lx);
		  GSurface->DrawSetColor(255, 255, 255, 255);
		  GSurface->DrawSetTexture(img.id);
		  dx += 14*inc*-1;
		  GSurface->DrawTexturedRect(dx , dy, dx + img.width, dy + img.height);
		
		  index++;
	  } while (num > 0);
	  


}
  long Graphic::genNewId()
  {
	  if (Graphic::currentID == 0)
	  {
		  Graphic::currentID = 254279700;
	  }
			 Graphic::currentID += 1;
	  return Graphic::currentID;
  }
  std::vector<image_t>* Graphic::images = new std::vector<image_t>();
  long Graphic::currentID = 0;
