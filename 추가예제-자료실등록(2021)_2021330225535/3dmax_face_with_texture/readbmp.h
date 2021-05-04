/*
 * This is the header for readbmp.c - functions to read the bitmap file
 * structures.  See readbmp.c for details.
 */

/*
 * Data types used in bitmap files.
 */

#include <stdio.h>

#ifndef __BMPTYPES_H_INCLUDED__
#define __BMPTYPES_H_INCLUDED__

/*****************************************************************************
*
* Data types.
*
* INT8 is an integer of at least 8 bits wide.
* INT16 is an integer of at least 16 bits wide.
* INT32 is an integer of at least 32 bits wide.
*
* UINT8 is an unsigned INT8
* UINT16 is an unsigned INT16
* UINT32 is an unsigned INT32
*/

typedef char           INT8;
typedef short          INT16;
typedef long           INT32;
typedef unsigned char  UINT8;
typedef unsigned short UINT16;
typedef unsigned long  UINT32;

/*****************************************************************************
*
* Constants.  Each set corresponds to a field in a structure.  Note that some
* sets only have one value.  Default values for all fields are the value
* corresponding to 0. 
*/

/*
 * Constants used in the "type" field of BITMAP_FILEHEADER and
 * BITMAPARRAYHEADER structures.  Note that these are all two-character
 * mnemonics as well as integer constants.
 */

#define TYPE_ICO        (0x4349)   /* 'IC' */
#define TYPE_BMP        (0x4d42)   /* 'BM' */
#define TYPE_PTR        (0x5450)   /* 'PT' */
#define TYPE_ICO_COLOR  (0x4943)   /* 'CI' */
#define TYPE_PTR_COLOR  (0x5043)   /* 'CP' */
#define TYPE_ARRAY      (0x4142)   /* 'BA' */
   
/*
 * Compression schemes.  Note that BITFIELDS (from NT) uses the same number as
 * HUFFMAN1D (from OS/2)
 */
#define COMPRESSION_NONE       (0)
#define COMPRESSION_RLE_8      (1)
#define COMPRESSION_RLE_4      (2)
#define COMPRESSION_HUFFMAN1D  (3)
#define COMPRESSION_BITFIELDS  (3)
#define COMPRESSION_RLE_24     (4)
#define COMPRESSION_LAST       (4)
   
/*
 * units of resolution
 */
#define UNITS_PELS_PER_METER (0)
#define UNITS_LAST           (0)

/*
 * origin of coordinate space
 */   
#define ORIGIN_LOWER_LEFT  (0)
#define ORIGIN_LAST        (0)

/*
 * halftoning algorithms
 */   
#define HALFTONING_NONE             (0)
#define HALFTONING_ERROR_DIFFUSION  (1)
#define HALFTONING_PANDA            (2)
#define HALFTONING_SUPER_CIRCLE     (3)
#define HALFTONING_LAST             (3)
   
/*
 * color table encoding
 */
#define COLOR_ENCODING_RGB   (0)
#define COLOR_ENCODING_LAST  (0)

/*****************************************************************************
*
* Structures.
*/
   
/*
 * BITMAP_FILEHEADER defines a single bitmap image.  Its analogue in the
 * Windows SDK is the BITMAP_FILEHEADER.  Its analogues in the OS/2 Toolkit are
 * the BITMAP_FILEHEADER and BITMAP_FILEHEADER2 structures.
 *
 * A BITMAPHEADER structure is always concatenated to the end of a
 * BITMAP_FILEHEADER structure.
 */

typedef struct BITMAP_FILEHEADER
{
    UINT16    type;
    UINT32    size;
    INT16     xHotspot;
    INT16     yHotspot;
    UINT32    offsetToBits;
} BITMAP_FILEHEADER;

/*
 * BITMAPARRAYHEADER is used to establish a linked list of BITMAP_FILEHEADER
 * structures for a bitmap file with multiple images in it.  There is no
 * equivalent structure in the Windows SDK.  Its analogues in the OS/2 toolkit
 * are the BITMAPARRAYFILEHEADER and BITMAPARRAYFILEHEADER2 strucutres.
 *
 * A BITMAP_FILEHEADER structure is always concatenated to the end of a
 * BITMAPARRAYHEADER structure.
 */
typedef struct BITMAPARRAYHEADER
{
    UINT16    type;
    UINT32    size;
    UINT32    next;
    UINT16    screenWidth;
    UINT16    screenHeight;
} BITMAPARRAYHEADER;
   

/*
 * BITMAPHEADER defines the properties of a bitmap.  Its analogues in the
 * Windows SDK are the BITMAPCOREINFOHEADER and BITMAPINFOHEADER structures.
 * Its analogues in the OS/2 Toolkit are the BITMAPINFOHEADER and
 * BITMAPINFOHEADER2 structures.
 *
 * A color table is concatenated to this structure.  The number of elements in
 * the color table determined by the bit-depth of the image.
 *
 * Note, that if the field "size" is 12 or less, then the width and height
 * fields should be read as UINT16's instead of UINT32's.
 *
 * Also note that if the field "size" is greater than 12, then the color table
 * will have an extra byte of padding between each structures (to longword
 * align it)
 *
 * The different sizes for the width, height, and color table are the only
 * differences between the "old" and "new" bitmap file formats.
 */
typedef struct BITMAPHEADER
{
    UINT32 size;
    INT32  width;
    INT32  height;
    UINT16 numBitPlanes;
    UINT16 numBitsPerPlane;
    UINT32 compressionScheme;
    UINT32 sizeOfImageData;
    UINT32 xResolution;
    UINT32 yResolution;
    UINT32 numColorsUsed;
    UINT32 numImportantColors;
    UINT16 resolutionUnits;
    UINT16 padding;
    UINT16 origin;
    UINT16 halftoning;
    UINT32 halftoningParam1;
    UINT32 halftoningParam2;
    UINT32 colorEncoding;
    UINT32 identifier;
} BITMAPHEADER;


/*
 * RGB defines a single color palette entry.  Its analogues in the Windows SDK
 * are the RGBTRIPLE and RGBQUAD structures.  Its analogues in the OS/2
 * Toolkit are the RGB and RGB2 structure. 
 */
typedef struct RGB
{
    UINT8 blue;
    UINT8 green;
    UINT8 red;
} RGB;

#endif   /* __BMPTYPES_H_INCLUDED__ */

#ifndef __ENDIAN_H_INCLUDED__
#define __ENDIAN_H_INCLUDED__
 
/*
 * Read the basic types as little-endian values.  The return value will be
 * zero if successful, EOF, otherwise.
 */
int readINT8little(FILE *f, INT8 *i);
int readINT16little(FILE *f, INT16 *i);
int readINT32little(FILE *f, INT32 *i);
int readUINT8little(FILE *f, UINT8 *i);
int readUINT16little(FILE *f, UINT16 *i);
int readUINT32little(FILE *f, UINT32 *i);

/*
 * Write the basic types as little-endian values.  The return value will be
 * zero if successful, EOF otherwise.
 */
int writeINT8little(FILE *f, INT8 i);
int writeINT16little(FILE *f, INT16 i);
int writeINT32little(FILE *f, INT32 i);
int writeUINT8little(FILE *f, UINT8 i);
int writeUINT16little(FILE *f, UINT16 i);
int writeUINT32little(FILE *f, UINT32 i);

#endif  /* __ENDIAN_H_INCLUDED__ */

#ifndef __READBMP_H_INCLUDED__
#define __READBMP_H_INCLUDED__

/*
 * Mid-level functions
 */
int readBitmapFileHeader(FILE *fp, BITMAP_FILEHEADER *bfh);
int readBitmapArrayHeader(FILE *fp, BITMAPARRAYHEADER *bah);
int readBitmapHeader(FILE *fp, BITMAPHEADER *bh);
int readRgb(FILE *fp, RGB *rgb, int numBytes);
int readColorTable(FILE *fp, RGB *rgb, int numEntries, int numBytesPerEntry);

int readBitsUncompressed(FILE *fp, RGB *image, int width, int height,
			 int depth, RGB* colorTable);
int readMaskBitsUncompressed(FILE *fp, char *image, int width, int height);

void reflectYRGB(RGB *image, int width, int height);
void reflectYchar(char *image, int width, int height);

/*
 * High level functions.
 */
int readSingleImageBMP(FILE *fp, RGB **argb, UINT32 *width, UINT32 *height);
int readSingleImageICOPTR(FILE *fp, char **xorMask, char **andMask,
		          UINT32 *width, UINT32 *height);
int readSingleImageColorICOPTR(FILE *fp, RGB **argb, char **xorMask,
			       char **andMask, UINT32 *width, UINT32 *height);
int readMultipleImage(FILE *fp, RGB ***argbs, char ***xorMasks,
		      char ***andMasks, UINT32 **widths, UINT32 **heights,
		      int *imageCount);

#endif

/*
 * Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:4
 * c-brace-offset:-4
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:4
 * c-label-offset:-4
 * End:
 */

