#include "tiffio.h"
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
   TIFF* tif = TIFFOpen(argv[1], "r");

   vector<vector<vector<uint16>>> mega;

   if (tif)
   {
      int dircount = 0;
      do
      {
         dircount++;
         uint32 w, h;
         size_t npixels;
         uint32* raster;
         TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
         TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
         uint16 *rcmap, *gcmap, *bcmap;

         uint16 bps, spp, bpp, photo, sampleFormat, config;

         vector<vector <uint16> > stack( h, vector<uint16> (w, 0));

         TIFFGetField(tif, TIFFTAG_COLORMAP, rcmap, gcmap, bcmap);
         TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bps);
         TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &spp);
         TIFFGetField(tif, TIFFTAG_PHOTOMETRIC, &photo);
         TIFFGetField(tif, TIFFTAG_SAMPLEFORMAT, &sampleFormat);
         TIFFGetField(tif, TIFFTAG_PLANARCONFIG, &config);

         uint16* buf;
         buf = (uint16*) _TIFFmalloc(TIFFScanlineSize(tif));
         uint32 row;
         for (row = 0; row < h; row++)
         {
            TIFFReadScanline(tif, buf, row);
            for (int col = 0; col < w; col++)
            {
               stack[row][col] = buf[col];
            }
         }

         mega.push_back(stack);

         _TIFFfree(buf);

      }
      while(TIFFReadDirectory(tif));
      


      printf("%d directories in %s\n", dircount, argv[1]);
      TIFFClose(tif);
   }
   return 0;
}
