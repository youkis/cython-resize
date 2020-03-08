#include<stdio.h>
#include"cfunc.h"

void cfunc(unsigned char *tempx, unsigned char *tempy, int ch, int ih, int iw, int oh, int ow){
	int idx,c,n,m;

	for(c=0; c<ch; c++){
	for(n=0; n<oh; n++){
	for(m=0; m<ow; m++){
		unsigned short mm=m*(iw-1);
		unsigned short nn=n*(ih-1);
		unsigned char m0=mm/(ow-1); unsigned char m1=m0+1;
		unsigned char n0=nn/(oh-1); unsigned char n1=n0+1;
		unsigned short dm=mm-m0*(ow-1);
		unsigned short dn=nn-n0*(oh-1);
		if(m1==iw) m1=iw-1;
		if(n1==ih) n1=ih-1;

		unsigned int val =
			  tempx[c*iw*ih + n1*iw + m1] *dm*dn
			+ tempx[c*iw*ih + n0*iw + m1] *dm*(oh-1-dn)
			+ tempx[c*iw*ih + n1*iw + m0] *(ow-1-dm)*dn
			+ tempx[c*iw*ih + n0*iw + m0] *(ow-1-dm)*(oh-1-dn);
		tempy[c*ow*oh + n*ow + m] = val/(ow-1)/(oh-1);
	}
	}
	}
}

