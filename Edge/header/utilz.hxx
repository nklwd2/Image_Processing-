
#ifndef _utilz__
#define _utilz__
#include "CImg.h"
#include <iostream> 
#include <math.h>
void edge_detection(cimg_library::CImg<> &image,cimg_library::CImg<> &grayscale_image, cimg_library:: CImg<> &output_img, cimg_library:: CImg<> &edege_detected_img_x, cimg_library:: CImg<> &edege_detected_img_y, cimg_library:: CImg<> &edege_detected_img_x_y,cimg_library:: CImg<> &edege_detected_img_x_y2, cimg_library:: CImg<> &edege_detected_img_x2,cimg_library:: CImg<> &edege_detected_img_y2){
    	
	grayscale_image.assign(image.width(),image.height(),1,1);
	output_img.assign(grayscale_image.width()+2,grayscale_image.height()+2,1,1);
	edege_detected_img_x.assign(image.width(),image.height(),1,1,0);
	edege_detected_img_y.assign(image.width(),image.height(),1,1,0);
	edege_detected_img_x_y.assign(image.width(),image.height(),1,1,0);
	edege_detected_img_x2.assign(image.width(),image.height(),1,1,0);
	edege_detected_img_y2.assign(image.width(),image.height(),1,1,0);
	edege_detected_img_x_y2.assign(image.width(),image.height(),1,1,0);
    //grayscale_image.fill(0);
    
    	if(image.spectrum()>1){
        	int R,G,B;
        	for (int r = 0 ; r< image.height(); r++){
           		for (int c= 0 ; c < image.width(); c++){
                		R = (int)image(c,r,0,0);
                		G = (int)image(c,r,0,1);
                		B = (int)image(c,r,0,2);
                		grayscale_image(c,r,0,0) = (float) (0.2989 * R + 0.5870 * G + 0.1140 * B);
            			}
        		}
    	}else if(image.spectrum()==1){
        	grayscale_image=image;
    	}
	for (int r = 0; r < output_img.height(); r++){
		for(int c = 0; c < output_img.width(); c++){
			if(c == 0){
				output_img(c,r,0,0) = 255;
			}else if(c == output_img.width()-1){
				output_img(c,r,0,0) = 255;
			}else if(r == 0){
				output_img(c,r,0,0) = 255;
			}else if( r == output_img.height()-1){
				output_img(c,r,0,0) = 255;
			}else{
				output_img(c,r,0,0) = grayscale_image(c-1,r-1,0,0);
			}
		}
	}



	
	
	
	double x[3][3] = {	{0.25,0,-0.25},
				{0.50,0,-0.50},
				{0.25,0,-0.25}};
	
	double y[3][3] = {	{0.25,0.50,0.25},
				{0,0,0},
				{-0.25,-0.50,-0.25}};

	float pix_x = 0, pix_y = 0, value = 0;
	double theta = 0;
	//printf("value1 = %f", value);
	for (int j = 1; j < output_img.height()-1; j++){
		for(int i = 1; i < output_img.width()-1; i++){
			//printf("Hello");
			
			pix_x = (x[0][0]*output_img(i-1,j-1,0,0))
				+(x[0][1]*output_img(i,j-1,0,0))
				+(x[0][2]*output_img(i+1,j-1,0,0))
				+(x[1][0]*output_img(i-1,j,0,0))
				+(x[1][1]*output_img(i,j,0,0))
				+(x[1][2]*output_img(i+1,j,0,0))
				+(x[2][0]*output_img(i-1,j+1,0,0))
				+(x[2][1]*output_img(i,j+1,0,0))
				+(x[2][2]*output_img(i+1,j+1,0,0));
			
			//printf("%f -> xval", pix_x);
			pix_y = (y[0][0]*output_img(i-1,j-1,0,0))
				+(y[0][1]*output_img(i,j-1,0,0))
				+(y[0][2]*output_img(i+1,j-1,0,0))
				+(y[1][0]*output_img(i-1,j,0,0))
				+(y[1][1]*output_img(i,j,0,0))
				+(y[1][2]*output_img(i+1,j,0,0))
				+(y[2][0]*output_img(i-1,j+1,0,0))
				+(y[2][1]*output_img(i,j+1,0,0))
				+(y[2][2]*output_img(i+1,j+1,0,0));
			
			
			value = sqrt((pix_x*pix_x)+(pix_y*pix_y));
			theta = atan2(pix_y,pix_x);		
			edege_detected_img_x(i-1,j-1,0,0) = pix_x;
			edege_detected_img_y(i-1,j-1,0,0) = pix_y;
			edege_detected_img_x_y(i-1,j-1,0,0) = value;
			theta = (theta/3.14)*180;
			if(theta < 0){
				theta = 360 + theta;
			}
				
			//std::cout<<"theta = "<<theta<<" degrees"<<std::endl;
			//HSVtoRGB(H,S,V)
			//H = theta/360    S = 1   V = 1
		}
	}
	for (int j = 1; j < output_img.height()-1; j++){
		for(int i = 1; i < output_img.width()-1; i++){
			//printf("Hello");
			
			pix_x = (x[0][0]*edege_detected_img_x(i-1,j-1,0,0))				
				+(x[0][1]*edege_detected_img_x(i,j-1,0,0))
				+(x[0][2]*edege_detected_img_x(i+1,j-1,0,0))
				+(x[1][0]*edege_detected_img_x(i-1,j,0,0))
				+(x[1][1]*edege_detected_img_x(i,j,0,0))
				+(x[1][2]*edege_detected_img_x(i+1,j,0,0))
				+(x[2][0]*edege_detected_img_x(i-1,j+1,0,0))
				+(x[2][1]*edege_detected_img_x(i,j+1,0,0))
				+(x[2][2]*edege_detected_img_x(i+1,j+1,0,0));
			
			pix_y = (y[0][0]*edege_detected_img_y(i-1,j-1,0,0))				
				+(y[0][1]*edege_detected_img_y(i,j-1,0,0))
				+(y[0][2]*edege_detected_img_y(i+1,j-1,0,0))
				+(y[1][0]*edege_detected_img_y(i-1,j,0,0))
				+(y[1][1]*edege_detected_img_y(i,j,0,0))
				+(y[1][2]*edege_detected_img_y(i+1,j,0,0))
				+(y[2][0]*edege_detected_img_y(i-1,j+1,0,0))
				+(y[2][1]*edege_detected_img_y(i,j+1,0,0))
				+(y[2][2]*edege_detected_img_y(i+1,j+1,0,0));
			
			
			value = sqrt((pix_x*pix_x)+(pix_y*pix_y));	
			edege_detected_img_x2(i-1,j-1,0,0) = pix_x;
			edege_detected_img_y2(i-1,j-1,0,0) = pix_y;
			edege_detected_img_x_y2(i-1,j-1,0,0) = value;

		}
	}	
	
	
	
}
void thresh_img(cimg_library::CImg<> &image,cimg_library::CImg<> &output_image){
	output_image.assign(image.width(),image.height(),1,1);

	for (int r = 0; r < image.height(); r++){
		for(int c = 0; c < image.width(); c++){
			if (image(c,r,0,0) >= 25){
				output_image(c,r,0,0) = 0;
			}else{
				output_image(c,r,0,0) = 255;
			}
		}
	}
}
#endif
