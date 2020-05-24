int
ImageProcessNormal (unsigned long *pPixels, int width, int height)
{
	for(int i = 0; i < width*height; i++){
		pPixels[i] = pPixels[i];	
	}
	return 0;
}



int
ImageProcessGrayscale (unsigned long *pPixels, int width, int height)
{
	unsigned long red, green, blue, luminance;	
	for(int i = 0; i < width*height; i++){
		red = pPixels[i]>> 16 & 255;
		green = pPixels[i]>> 8 & 255;
		blue = pPixels[i]& 255;

		luminance = (red * 0.3) + (green * 0.59) + (blue*0.11);
	
		pPixels[i] = (luminance<<16) + (luminance<<8) + luminance;
		
	}
	/*
	 * this algorithm computes grayscale via luminance computations.
	 * Luminance = 30% of RED value + 59% of GREEN value + 11% of BLUE value.
	 * Set the red/green/blue values of pixel to the luminance value.
	 * When the red/green/blue components are all the same value, a pixel
	 * is considered a shade of gray, and thus, a grayscale image
	 * has 256 levels of gray.
	 */

	return 0;
}	


int
ImageProcessInverse (unsigned long *pPixels, int width, int height)
{
	unsigned long red, green, blue;	
	for(int i = 0; i < width*height; i++){
		red = 255 - (pPixels[i]>> 16 & 255);
		green = 255 - (pPixels[i]>> 8 & 255);
		blue = 255 - (pPixels[i]& 255);	
	
		pPixels[i] = (red<<16) + (green<<8) + blue;
		
	}
	/*
 	 * this algorithm will invert the pixel data to create a
	 * "negative" of the original image
	 */

	return 0;
}

int
ImageProcessPosterize (unsigned long *pPixels, int width, int height)
{
unsigned long red, green, blue;	
int divisions = 31;
	for(int i=0;i<width*height;i++){
		red = pPixels[i]>> 16 & 255;
		green = pPixels[i]>> 8 & 255;
		blue = pPixels[i]& 255;
		
		red = (red / divisions) * divisions;
		green = (green / divisions) * divisions;
		blue = (blue / divisions) * divisions;
		
		pPixels[i] = (red<<16) + (green<<8) + blue;
	
	}
	
	/*
	 * this algorithm will collapse colours into groups
	 * to reduce the number of unique colours. For example, 
	 * pixel values from 0 to 31 could be one group, 32 to 63 could be
	 * a second group, and so forth, to generate 8 groups in total. The
	 * resulting image will appear like a painted poster. Experiment
	 * with the number of groups to determine best level of 
	 * posterization. Google for algorithms to support posterization.
	 */

	return 0;
}	/* end ImageProcessPosterize */

