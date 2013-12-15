/********************************************************************
	created:	2012/04/07
	filename: 	mybmp.h
	author:		
	
	purpose:	
*********************************************************************/

#ifndef _mybmp_h__
#define _mybmp_h__
//-------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#	define ROOT_PATH "./jni"
#else
#	define ROOT_PATH "/mnt/sdcard"
#endif

enum {
	eRGB_MIN = 0,
	eRGB_565,
	eRGB_888,
	eRGB_MAX
};

static const char * g_rgbstr[] =
{
	"",
	"rgb565",
	"rgb888",
};

enum {
	eACTION_MIN = -1,
	eBMP_RGB565_TO_FB0_RGB565,
	eBMP_RGB565_TO_FB0_RGB888,
	eBMP_RGB888_TO_FB0_RGB565,
	eBMP_RGB888_TO_FB0_RGB888,

	eACTION_MAX,

	eBMP_TO_BMP,//WIN32�²�����
};

//-------------------------------------------------------------------
/*
����λͼ�ļ������
�����ṹ���� �� ��
����λͼ�ļ�ͷ (bitmap-file header) BITMAPFILEHEADER bmfh
����λͼ��Ϣͷ (bitmap-information header) BITMAPINFOHEADER bmih
������ɫ��(color table) RGBQUAD aColors[]
����ͼ�����������ֽ� BYTE aBitmapBits[]
*/
typedef struct bmp_header 
{
	short twobyte			;//�����ֽڣ�������֤�����Ա�������У��������ַ�����д���ļ���
	//14B
	char bfType[2]			;//!�ļ�������,��ֵ������0x4D42��Ҳ�����ַ�'BM'
	unsigned int bfSize		;//!˵���ļ��Ĵ�С�����ֽ�Ϊ��λ
	unsigned int bfReserved1;//��������������Ϊ0
	unsigned int bfOffBits	;//!˵�����ļ�ͷ��ʼ��ʵ�ʵ�ͼ������֮����ֽڵ�ƫ����������Ϊ14B+sizeof(BMPINFO)
}BMPHEADER;

typedef struct tagBMPINFO
{
	//40B
	unsigned int biSize			;//!BMPINFO�ṹ����Ҫ������
	int biWidth					;//!ͼ��Ŀ�ȣ�������Ϊ��λ
	int biHeight				;//!ͼ��Ŀ�ȣ�������Ϊ��λ,�����ֵ��������˵��ͼ���ǵ���ģ������ֵ�Ǹ��������������
	unsigned short biPlanes		;//!Ŀ���豸˵��λ��������ֵ�����Ǳ���Ϊ1
	unsigned short biBitCount	;//!������/���أ���ֵΪ1��4��8��16��24����32
	unsigned int biCompression	;//˵��ͼ������ѹ��������
#define BI_RGB        0L	//û��ѹ��
#define BI_RLE8       1L	//ÿ������8���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ���ɣ��ظ����ؼ�������ɫ��������
#define BI_RLE4       2L	//ÿ������4���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����
#define BI_BITFIELDS  3L	//ÿ�����صı�����ָ�������������
	unsigned int biSizeImage	;//ͼ��Ĵ�С�����ֽ�Ϊ��λ������BI_RGB��ʽʱ��������Ϊ0
	int biXPelsPerMeter			;//ˮƽ�ֱ��ʣ�������/�ױ�ʾ
	int biYPelsPerMeter			;//��ֱ�ֱ��ʣ�������/�ױ�ʾ
	unsigned int biClrUsed		;//λͼʵ��ʹ�õĲ�ɫ���е���ɫ����������Ϊ0�Ļ�����˵��ʹ�����е�ɫ���
	unsigned int biClrImportant	;//��ͼ����ʾ����ҪӰ�����ɫ��������Ŀ�������0����ʾ����Ҫ��
}BMPINFO;

typedef struct tagRGBQUAD {
	unsigned char rgbBlue;
	unsigned char rgbGreen;
	unsigned char rgbRed;
	unsigned char rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPINFO {
    BMPINFO    bmiHeader;
    //RGBQUAD    bmiColors[1];
	unsigned int rgb[3];
} BITMAPINFO;

int save_bmp(const char * path, int w, int h, void * pdata, int bpp);
int screen_shot(const char * path);
int shot(int argc, char * argv[]);

struct tagBMP;
typedef struct tagBMP BMP;

BMP * bmp_open(const char * path);
void bmp_close(BMP * bmp);
int bmp_width(BMP * bmp);
int bmp_height(BMP * bmp);
int bmp_bpp(BMP * bmp);
void * bmp_data(BMP * bmp);
int bmp_forward(BMP * bmp);

typedef struct tagImageInfo {
	int bpp;
	int width;
	int height;
}ImageInfo;
int bmp_info(const char * path, ImageInfo * imageinfo);

//�����ݷ�ת
void rgb565_line_reversal(void * p565, int w, int h);
void rgb888_line_reversal(void * p888, int w, int h);
void * rgb888_to_rgb565_buffer(const void * p888, int w, int h);
void * rgb565_to_rgb888_buffer(const void * p565, int w, int h);

int bmp_to_screen(const char * path);

int tofb(int argc, char * argv[]);

#ifdef __cplusplus
};
#endif

//-------------------------------------------------------------------
#endif // #ifndef _mybmp_h__





















