#include "stdafx.h"
#include "Render.h"
#include "stdio.h"
#include "stdlib.h"
typedef struct tga_s
{
	byte	id_length;
	byte	colormap_type;
	byte	image_type;
	word	colormap_index;
	word	colormap_length;
	byte	colormap_size;
	word	x_origin;
	word	y_origin;
	word	width;
	word	height;
	byte	pixel_size;
	byte	attributes;
} tga_t;

bool isPrepare = false;
int scr_Size[2];
ScoreBoard* g_ScoreBoard;
KillMark* g_Killmark;
unsigned char * LoadTgaImage(char *szFileName, tga_t *header)
{
 
	FILE* pFile = fopen(szFileName, "rb");
	if (pFile == NULL)
	{
		LogWriter("Open File Error");
		return NULL;
	}

	
	fseek(pFile, 0, SEEK_END);
	int fileLength = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	byte *buffer = (byte *)malloc(fileLength);
	fread(buffer, 1, fileLength, pFile);


	int	i, columns, rows, row_inc, row, col;
	byte	*buf_p, *pixbuf, *targa_rgba;
	byte	palette[256][4], red = 0, green = 0, blue = 0, alpha = 0;
	int	readpixelcount, pixelcount;
	qboolean	compressed;
	tga_t	targa_header;

	buf_p = (byte *)buffer;
	targa_header.id_length = *buf_p++;
	targa_header.colormap_type = *buf_p++;
	targa_header.image_type = *buf_p++;

	targa_header.colormap_index = buf_p[0] + buf_p[1] * 256;		buf_p += 2;
	targa_header.colormap_length = buf_p[0] + buf_p[1] * 256;		buf_p += 2;
	targa_header.colormap_size = *buf_p;				buf_p += 1;
	targa_header.x_origin = *(short *)buf_p;			buf_p += 2;
	targa_header.y_origin = *(short *)buf_p;			buf_p += 2;
	targa_header.width = *(short *)buf_p;		buf_p += 2;
	targa_header.height = *(short *)buf_p;		buf_p += 2;
	targa_header.pixel_size = *buf_p++;
	targa_header.attributes = *buf_p++;
	if (targa_header.id_length != 0) buf_p += targa_header.id_length;	// skip TARGA image comment

	char fInfo[512];
	sprintf(fInfo, "[W: %d - H: %d]", targa_header.width, targa_header.height);
	LogWriter(fInfo);

	if (targa_header.image_type == 1 || targa_header.image_type == 9)
	{
		// uncompressed colormapped image
		if (targa_header.pixel_size != 8)
		{
			LogWriter("TGA processing error:Only 8 bit images supported for type 1 and 9");
			return NULL;
		}
		if (targa_header.colormap_length != 256)
		{
			LogWriter("TGA processing error:Only 8 bit colormaps are supported for type 1 and 9");
			return NULL;
		}
		if (targa_header.colormap_index)
		{
			LogWriter("TGA processing error:colormap_index is not supported for type 1 and 9");
			return NULL;
		}
		if (targa_header.colormap_size == 24)
		{
			for (i = 0; i < targa_header.colormap_length; i++)
			{
				palette[i][2] = *buf_p++;
				palette[i][1] = *buf_p++;
				palette[i][0] = *buf_p++;
				palette[i][3] = 255;
			}
		}
		else if (targa_header.colormap_size == 32)
		{
			for (i = 0; i < targa_header.colormap_length; i++)
			{
				palette[i][2] = *buf_p++;
				palette[i][1] = *buf_p++;
				palette[i][0] = *buf_p++;
				palette[i][3] = *buf_p++;
			}
		}
		else
		{
			LogWriter("TGA processing error:only 24 and 32 bit colormaps are supported for type 1 and 9");
			return NULL;
		}
	}
	else if (targa_header.image_type == 2 || targa_header.image_type == 10)
	{
		// uncompressed or RLE compressed RGB
		if (targa_header.pixel_size != 32 && targa_header.pixel_size != 24)
		{
			LogWriter( "TGA processing error:Only 32 or 24 bit images supported for type 2 and 10");
			return NULL;
		}
	}
	else if (targa_header.image_type == 3 || targa_header.image_type == 11)
	{
		// uncompressed greyscale
		if (targa_header.pixel_size != 8)
		{
			LogWriter( "TGA processing error:Only 8 bit images supported for type 3 and 11");
			return NULL;
		}
	}

	columns = targa_header.width;
	rows = targa_header.height;

	int size = columns * rows * 4;
	targa_rgba = (byte *)malloc(size);

	pixbuf = targa_rgba + (rows - 1) * columns * 4;
	row_inc = -columns * 4 * 2;

	compressed = (targa_header.image_type == 9 || targa_header.image_type == 10 || targa_header.image_type == 11);
	for (row = col = 0; row < rows; )
	{
		pixelcount = 0x10000;
		readpixelcount = 0x10000;

		if (compressed)
		{
			pixelcount = *buf_p++;
			if (pixelcount & 0x80)  // run-length packet
				readpixelcount = 1;
			pixelcount = 1 + (pixelcount & 0x7f);
		}

		while (pixelcount-- && (row < rows))
		{
			if (readpixelcount-- > 0)
			{
				switch (targa_header.image_type)
				{
				case 1:
				case 9:
					// colormapped image
					blue = *buf_p++;
					red = palette[blue][0];
					green = palette[blue][1];
					alpha = palette[blue][3];
					blue = palette[blue][2];
					//if( alpha != 255 ) image.flags |= IMAGE_HAS_ALPHA;
					break;
				case 2:
				case 10:
					// 24 or 32 bit image
					blue = *buf_p++;
					green = *buf_p++;
					red = *buf_p++;
					alpha = 255;
					if (targa_header.pixel_size == 32)
					{
						alpha = *buf_p++;
						//if( alpha != 255 )
						//image.flags |= IMAGE_HAS_ALPHA;
					}
					break;
				case 3:
				case 11:
					// greyscale image
					blue = green = red = *buf_p++;
					alpha = 255;
					break;
				}
			}


			*pixbuf++ = red;
			*pixbuf++ = green;
			*pixbuf++ = blue;
			*pixbuf++ = alpha;
			if (++col == columns)
			{
				row++;
				col = 0;
				pixbuf += row_inc;
			}
		}
	}

	//  targa_header.height;  targa_header.width; 4  targa_rgba
	// Make a texture 
	
//	free(buffer);
	fclose(pFile);

	*header = targa_header;
	return targa_rgba;
}
 
void Prepare()
{
	LogWriter("Prepare");
	Graphic::prepare();
 	g_ScoreBoard = new ScoreBoard();
	g_Killmark = new KillMark();
	
}
void inGameDraw()
{
	if (g_ScoreBoard != null)
	{
		g_ScoreBoard->Render();
	}
	if (g_Killmark != null)
	{
		g_Killmark->Render();
	}

}
void RunFrame(unsigned int vguiPanel)
{
 
	if (!isPrepare) return;

		g_pVGuiPanel->GetSize(vguiPanel, scr_Size[0], scr_Size[1]);
		if (strcmpi("FocusOverlayPanel", g_pVGuiPanel->GetClassName(vguiPanel)) == 0)
		{
			
			if (!GEnginevgui->IsGameUIVisible()) {
 
				inGameDraw();
 
			}
		}

		
}
void Render_HudVidInt()
{
	if (!isPrepare)
	{
		isPrepare = true;
		Prepare();

		return;
	}
}

void HubUpdate()
{

}
void RunClient( CUserCmd* pCmd )
{
	// Aimbot, no recoil, no spread, and bhop should be done here :D
}