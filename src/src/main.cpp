#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "image.h"
#include <vector>
#include "elas.h"
using namespace cv;
using namespace std;

void process (const char* left,const char* right)
{
    cout << "Processing: " << left << ", " << right << endl;
    image<uchar> *I1,*I2;
    I1 = loadPGM(left);
    I2 = loadPGM(right);
    if (I1->width()<=0 || I1->height() <=0 || I2->width()<=0 || I2->height() <=0 || I1->width()!=I2->width() || I1->height()!=I2->height())
    {
	    cout << "ERROR: Images must be of same size, but" << endl;
	    cout << "       I1: " << I1->width() <<  " x " << I1->height() << 
	                 ", I2: " << I2->width() <<  " x " << I2->height() << endl;
	    delete I1;
	    delete I2;
	   	return;    
	  }

	  int32_t width  = I1->width();
  	int32_t height = I1->height();

  	const int32_t dims[3] = {width,height,width};
  	float* D1_data = (float*)malloc(width*height*sizeof(float));
  	float* D2_data = (float*)malloc(width*height*sizeof(float));

  	Elas::parameters param;
  	param.postprocess_only_left = false;
  	Elas elas(param);
  	elas.process(I1->data,I2->data,D1_data,D2_data,dims);
/*
  	float disp_max = 0;
  	for (int32_t i=0; i<width*height; i++)
  	{
    	if (D1_data[i]>disp_max) disp_max = D1_data[i];
    	if (D2_data[i]>disp_max) disp_max = D2_data[i];
  	}

  	// copy float to uchar
  	image<uchar> *D1 = new image<uchar>(width,height);
  	image<uchar> *D2 = new image<uchar>(width,height);
  	
  	for (int32_t i=0; i<width*height; i++)
  	{
    	D1->data[i] = (uint8_t)max(255.0*D1_data[i]/disp_max,0.0);
    	D2->data[i] = (uint8_t)max(255.0*D2_data[i]/disp_max,0.0);
  	}

    char output_1[1024];
   	char output_2[1024];
    strncpy(output_1,left,strlen(left)-4);
    strncpy(output_2,right,strlen(right)-4);
    output_1[strlen(left)-4] = '\0';
    output_2[strlen(right)-4] = '\0';
    strcat(output_1,"_disp.pgm");
    strcat(output_2,"_disp.pgm");
    savePGM(D1,output_1);
    savePGM(D2,output_2);*/
    delete I1;
    delete I2;
    free(D1_data);
    free(D2_data);
    //delete D1;
    //delete D2;
}

int main(int argc, char** argv )
{
    if ( argc != 3 )
    {
        printf("Wrong usage");
        return -1;
    }
    process(argv[1], argv[2]);
    return 0;
}