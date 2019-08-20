/**
 * @file appImage.cpp
 * @brief Get maximum, minimum values and print image. 
 * @author Ricardo Dutra da Silva
 */


#include <cg.h>


int main(int argc, char** argv)
{

	/* Check input arguments. */
	if (argc != 2)
	{
		fprintf(stderr, "%s image.pgm\n", argv[0]); 
		exit(1);
	}

	/* Read image. */
	cgMat2i img  = cgReadPGMImage(argv[1]);

	if (img == NULL)
	{
		fprintf(stdout, "FAILURE.\n");
		return EXIT_FAILURE;
	}

	/* Print min and max values. */
	printf("%d\n", cgMatMinValue2i(img));
	printf("%d\n", cgMatMaxValue2i(img));

	/* Print image. */
	for (int r = 0; r < img->height; r++)
	{
		for (int c = 0; c < img->width; c++)
		{
			printf("%d ", img->val[r][c]);
		}
		printf("\n");
	}

	cgFreeMat2i(img);

	return EXIT_SUCCESS;
}
