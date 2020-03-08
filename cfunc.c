#include<stdio.h>
#include<math.h>
#include"cfunc.h"
#include <pthread.h>

#define NUM_THREAD 8

typedef struct{
  unsigned char *arr_inp;
  unsigned char *arr_out;
  int ih;
  int iw;
  int oh;
  int ow;
  int n_ch;
} thread_data;

void *resize_img(thread_data *args){
	for(int c=0; c<args->n_ch; c++){
	for(int n=0; n<args->oh; n++){
		for(int m=0; m<args->ow; m++){
			unsigned short mm=m*(args->iw-1);
			unsigned short nn=n*(args->ih-1);
			unsigned char m0=mm/(args->ow-1); unsigned char m1=m0+1;
			unsigned char n0=nn/(args->oh-1); unsigned char n1=n0+1;
			unsigned short dm=mm-m0*(args->ow-1);
			unsigned short dn=nn-n0*(args->oh-1);
			if(m1==args->iw) m1=args->iw-1;
			if(n1==args->ih) n1=args->ih-1;

			unsigned int val =
				  args->arr_inp[c*(args->iw*args->ih) + n1*(args->iw) + m1] *dm*dn
				+ args->arr_inp[c*(args->iw*args->ih) + n0*(args->iw) + m1] *dm*(args->oh-1-dn)
				+ args->arr_inp[c*(args->iw*args->ih) + n1*(args->iw) + m0] *(args->ow-1-dm)*dn
				+ args->arr_inp[c*(args->iw*args->ih) + n0*(args->iw) + m0] *(args->ow-1-dm)*(args->oh-1-dn);
			args->arr_out[c*(args->ow*args->oh) + n*(args->ow) + m] = val/(args->ow-1)/(args->oh-1);
		}
	}
	}
}

void cfunc(unsigned char *tempx, unsigned char *tempy, int ch, int ih, int iw, int oh, int ow){
	pthread_t thread[NUM_THREAD];
	thread_data thdata[NUM_THREAD];
	int n = (int)floorf((float)ch/NUM_THREAD);
	// prepare inputs
	for(int t=0; t<NUM_THREAD; t++){
		thdata[t].ih = ih;
		thdata[t].iw = iw;
		thdata[t].oh = oh;
		thdata[t].ow = ow;
		thdata[t].n_ch = n;
		thdata[t].arr_inp = tempx + ih*iw*n*t;
		thdata[t].arr_out = tempy + oh*ow*n*t;
	}
	if(ch%NUM_THREAD != 0){
		int n_remind = ch-n*NUM_THREAD;
		for(int t=0; t<NUM_THREAD; t++){
			if(t<n_remind){
				thdata[t].n_ch += 1;
				thdata[t].arr_inp += ih*iw*t;
				thdata[t].arr_out += oh*ow*t;
			}else{
				thdata[t].arr_inp += ih*iw*n_remind;
				thdata[t].arr_out += oh*ow*n_remind;
			}
		}
	}
	// create threads
	for(int t = 0; t < NUM_THREAD; t++){
		pthread_create(&thread[t], NULL, resize_img, &thdata[t]);
	}
	// join threads
	for(int t=0; t<NUM_THREAD; t++){
		pthread_join(thread[t], NULL);
		//resize_img(&thdata[t]);
	}
}

