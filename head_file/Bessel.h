#ifndef BESSEL
#define BESSEL

#define EPSILON 1e-18
#define M 1000

#include<math.h>

int BesselJ(double x , double *Jn , int m , int m0);
int normalize(double *Jn,int m0);
void rescale(double *Jn , int m0);

int normalize(double *Jn,int m0)
{
        int tmp = 0,zero = 0;
        double sum = 0;
        bool judge = 1;

        for(tmp = 1 ; tmp < m0 ; tmp++)
        {
                sum  += Jn[tmp]*Jn[tmp];
        }

        sum =sqrt(2*sum + Jn[0]*Jn[0]);

        for(tmp = 0 ; tmp < m0 ; tmp++)
        {
                Jn[tmp] = Jn[tmp]/sum;
                if(abs(Jn[tmp])<EPSILON)
                {
                        zero = tmp;
                        for(;tmp < m0;tmp++)
                                Jn[tmp] = 0;
                        break;
                }
        }

        return zero;
}



void rescale(double *Jn,int m0)
{
        int tmp = 1;
        for(tmp = 1 ; tmp <= m0 ;tmp++)
                Jn[M-tmp] *= EPSILON;
}

//x:Independent variable in Jn(x)
//*Jn:array to store the value of Jn(x)
//m:the result to be returned , if n>m , we set Jn(x)=0 for it is fairly small
//m0:I forgot why I would set this input , do not bother to understand it here because I simply let it be M of all time
int BesselJ(double x , double *Jn , int m0)  
{
        int tmp = 0;
	int m=0;

        m0--;
        Jn[m0] = 0;             //JM = 0
        Jn[m0-1] = 1;           //JM-1 = 1

        for(tmp = 2 ; tmp <= m0 ; tmp++)
        {
                Jn[m0-tmp] = 2*(m0-tmp+1)*Jn[m0-tmp+1]/x-Jn[m0-tmp+2];
                if(abs(Jn[m0-tmp])*EPSILON > 1)
                        rescale(Jn,tmp+1);
        }
        m = normalize(Jn,m0);

        return m;
}

#endif
