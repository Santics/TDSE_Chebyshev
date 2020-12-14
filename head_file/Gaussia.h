#ifndef GAUSSIA
#define GAUSSIA

#include"Data_structure.h"
#include<math.h>

State* Gaussia_Wave_Packet_Init(double sigmax,double sigmay,double center_x0,double center_y0,double wave_vector)
{
	double normalization_const=sqrt(2*Pi*sigmax*sigmay);
	complex double wavefunction[N][N]={0};
	int x,y;

	for(x=0;x<N;x++)
	{
		for(y=0;y<N;y++)
		{
			if(x*Delta->rangex||y>rangey)
			{
				wavefunction[x][y]=0;
			}

			else
			{
				wavefunction[x][y]=normalization*Delta*Delta*cexp(-1*(()))
			}
		}
	}
}
