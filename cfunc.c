#include<stdio.h>
#include"cfunc.h"

void cfunc(float *tempx, float *tempy){
	int idx,c,n,m;
	for(idx=0,c=0,n=0,m=0; idx<CH*OUTH*OUTW; idx++,m++){
		if(m==OUTW){ m=0; n++; }
		if(n==OUTH){ n=0; c++; }
		const int m0=m*(INW-1)/(OUTW-1); int m1=m0+1;
		const int n0=n*(INW-1)/(OUTW-1); int n1=n0+1;
		const float dm=(float)(m)*(INW-1)/(OUTW-1)-m0;
		const float dn=(float)(n)*(INW-1)/(OUTW-1)-n0;
		if(m1==INW) m1=INW-1;
		if(n1==INH) n1=INH-1;

		tempy[n*CH*OUTW+c*OUTW+m]
			= tempx[n1*CH*INW+c*INW+m1] *dm*dn
			+ tempx[n0*CH*INW+c*INW+m1] *dm*(1-dn)
			+ tempx[n1*CH*INW+c*INW+m0] *(1-dm)*dn
			+ tempx[n0*CH*INW+c*INW+m0] *(1-dm)*(1-dn);
	}
}

