/***********************************************/
/*      bmpinfo.h - bitmap file format info       */
/**********************************************/

#ifndef __BMPINFO__
#define __BMPINFO__
#define BMPSIGN 0x4d42  /* bitmap signature 'BM' */

typedef unsigned char                   BYTE;
typedef unsigned short                  WORD;
typedef unsigned long                   DWORD;

typedef struct {        
        WORD    bfType;                 /* bitmap signature 'BM' (0x4d42) */
        DWORD   bfSize;                         /* size of bitmap file in bytes */
        WORD    bfReserved1;            /* must be set to 0 */
        WORD    bfReserved2;            /* must be set to 0 */
        DWORD   bfOffBits;              /* offset to actual bitmap bits */
} BMFH;         /* bitmap file header */    
                    
typedef struct {
        DWORD   biSize; 
        long    biWidth;                        /* width of bitmap in pixels */
        long    biHeight;               /* height of bitmap in pixels:
                                   (+) for bottom-up, (-) for top-down bitmap */
        WORD    biPlanes;               /* number of planes, must be set to 1 */
        WORD    biBitCount;     

        /* bits per pixels: 1, 4, 8, 16, 24 or 32 */
		DWORD   biCompression;      /* compression type for bottom-up bitmap:
                                   0(uncompressed), 1(8bit-RLE), 2(4bit-RLE) */
		DWORD   biSizeImage;        /* size of bitmap
                                   (without header, compressed) in bytes */
        long    biXPelsPerMeter;         /* horizontal resolution: in pixels per meter */
        long    biYPelsPerMeter;         /* vertical resolution: in pixels per meter */
        DWORD   biClrUsed;                      /* colors used */
        DWORD   biClrImportant;      /* colors important */
} BMIH;         /* bitmap info header */        

/* for 1-, 4-, and 8-bit bitmap: using palette */
typedef struct { 
    BYTE    rgbBlue;                    /* intensity of blue in the color */
    BYTE    rgbGreen;                   /* intensity of green in the color */
    BYTE    rgbRed;                     /* intensity of red in the color */
    BYTE    rgbReserved;                /* must be set to 0 */
} RGBQUAD;      

/* for 24-bit bitmap */
typedef struct {
    BYTE    rgbBlue;                    /* intensity of blue in the color */
    BYTE    rgbGreen;                   /* intensity of green in the color */
    BYTE    rgbRed;                             /* intensity of red in the color */
} RGB;  
        
typedef struct {
        BMFH    Bmfh;
        BMIH    Bmih;
        
        /* for 1-, 4-, and 8-bit bitmap */
        RGBQUAD *pRgbQuad;
        BYTE    *pIndex;
        /* for 24-bit bitmap */
        RGB     *pRgb;
} BMP;

#endif

