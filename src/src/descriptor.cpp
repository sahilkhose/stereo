#include "descriptor.h"
#include "filter.h"
#include <emmintrin.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;
//..Descriptor has been passed both complete images 1 by 1, half resolution=false
Descriptor::Descriptor(uint8_t* I_du, uint8_t* I_dv,int32_t width,int32_t height, int32_t bpl,bool half_resolution)
{
  I_desc = (uint8_t*)malloc(16*width*height*sizeof(uint8_t));//This is init of member. dont worry abt its use
  createDescriptor(I_du,I_dv,width,height,bpl,half_resolution);
  //free(I_du);
  //free(I_dv);
}

Descriptor::~Descriptor() {
  free(I_desc);
}

void Descriptor::createDescriptor (uint8_t* I_du,uint8_t* I_dv,int32_t width,int32_t height, int32_t bpl,bool half_resolution) {

  uint8_t *I_desc_curr;  
  uint32_t addr_v0,addr_v1,addr_v2,addr_v3,addr_v4;
  
  // do not compute every second line
  if (half_resolution) {
  
    // create filter strip
    for (int32_t v=4; v<height-3; v+=2) {

      addr_v2 = v*bpl;
      addr_v0 = addr_v2-2*bpl;
      addr_v1 = addr_v2-1*bpl;
      addr_v3 = addr_v2+1*bpl;
      addr_v4 = addr_v2+2*bpl;

      for (int32_t u=3; u<width-3; u++) {
        I_desc_curr = I_desc+(v*width+u)*16;
        *(I_desc_curr++) = *(I_du+addr_v0+u+0);
        *(I_desc_curr++) = *(I_du+addr_v1+u-2);
        *(I_desc_curr++) = *(I_du+addr_v1+u+0);
        *(I_desc_curr++) = *(I_du+addr_v1+u+2);
        *(I_desc_curr++) = *(I_du+addr_v2+u-1);
        *(I_desc_curr++) = *(I_du+addr_v2+u+0);
        *(I_desc_curr++) = *(I_du+addr_v2+u+0);
        *(I_desc_curr++) = *(I_du+addr_v2+u+1);
        *(I_desc_curr++) = *(I_du+addr_v3+u-2);
        *(I_desc_curr++) = *(I_du+addr_v3+u+0);
        *(I_desc_curr++) = *(I_du+addr_v3+u+2);
        *(I_desc_curr++) = *(I_du+addr_v4+u+0);
        *(I_desc_curr++) = *(I_dv+addr_v1+u+0);
        *(I_desc_curr++) = *(I_dv+addr_v2+u-1);
        *(I_desc_curr++) = *(I_dv+addr_v2+u+1);
        *(I_desc_curr++) = *(I_dv+addr_v3+u+0);
      }
    }
    
  // compute full descriptor images
  } else {
    
    // create filter strip
    for (int32_t v=3; v<height-3; v++) {

      addr_v2 = v*bpl;
      addr_v0 = addr_v2-2*bpl;
      addr_v1 = addr_v2-1*bpl;
      addr_v3 = addr_v2+1*bpl;
      addr_v4 = addr_v2+2*bpl;

      for (int32_t u=3; u<width-3; u++) {
        I_desc_curr = I_desc+(v*width+u)*16;
        *(I_desc_curr++) = *(I_du+addr_v0+u+0);//Sobel's Row 1 of 5, Col 3
        *(I_desc_curr++) = *(I_du+addr_v1+u-2);//Row 2, Col 1
        *(I_desc_curr++) = *(I_du+addr_v1+u+0);//Row 2, Col 3
        *(I_desc_curr++) = *(I_du+addr_v1+u+2);//Row 2, Col 5                   0 0 1 0 0
        *(I_desc_curr++) = *(I_du+addr_v2+u-1);//Row 3, Col 2                   1 0 1 0 1
        *(I_desc_curr++) = *(I_du+addr_v2+u+0);//Row 3, Col 3                   0 1 1 1 0
        *(I_desc_curr++) = *(I_du+addr_v2+u+0);//Row 3, Col 3                   1 0 1 0 1
        *(I_desc_curr++) = *(I_du+addr_v2+u+1);//Row 3, Col 4                   0 0 1 0 0
        *(I_desc_curr++) = *(I_du+addr_v3+u-2);//Row 4, Col 1
        *(I_desc_curr++) = *(I_du+addr_v3+u+0);//Row 4, Col 3
        *(I_desc_curr++) = *(I_du+addr_v3+u+2);//Row 4, Col 5
        *(I_desc_curr++) = *(I_du+addr_v4+u+0);//Row 5, Col 3

        *(I_desc_curr++) = *(I_dv+addr_v1+u+0);//Row 2, Col 3                   0 0 0 0 0
        *(I_desc_curr++) = *(I_dv+addr_v2+u-1);//Row 3, Col 2                   0 0 1 0 0
        *(I_desc_curr++) = *(I_dv+addr_v2+u+1);//Row 3, Col 4                   0 1 0 1 0
        *(I_desc_curr++) = *(I_dv+addr_v3+u+0);//Row 4, Col 3                   0 0 1 0 0 
      }                                                       //                0 0 0 0 0
    }
  }
}
