#include <stdio.h>
#include "jpeglib.h"

int getHeight(struct jpeg_decompress_struct cinfo)
{
	return cinfo.image_height;
}

int getWidth(struct jpeg_decompress_struct cinfo) 
{
	return cinfo.image_width;
}

int main(void) 
{

	char *filename = "./test.jpg";

	/* Open JPEG image file. Don't forget to use b for binary. */
	FILE *file = fopen(filename, "rb");
	if (!file) {
		printf("Error opening jpeg file %s\n", filename);
		return -1;
	}

	/* 
	 * This struct contains the JPEG compression parameters and pointers to
     * working space (which is allocated as needed by the JPEG library).
	 */
	struct jpeg_decompress_struct cinfo;

	/*
	 * This struct represents a JPEG error handler.
	 */
	struct jpeg_error_mgr jerr;

	/* Setup the error handler */
	cinfo.err = jpeg_std_error(&jerr);

	/* Initialize JPEG decompression object */
	jpeg_create_decompress(&cinfo);

	/* Specify input file */
	jpeg_stdio_src(&cinfo, file);

	/* Read JPEG file header */
	(void)jpeg_read_header(&cinfo, TRUE);

	printf("Image has a height of %i pixels\n", getHeight(cinfo));
	printf("Image has a width of %i pixels\n", getWidth(cinfo));

	/* Release memory */
	jpeg_destroy_decompress(&cinfo);

	/* Close input file */
	fclose(file);

	return 0;
}