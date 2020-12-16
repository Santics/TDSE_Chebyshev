#ifndef GAUSSIA
#define GAUSSIA

#include"Data_structure.h"
#include<math.h>

State* Gaussia_Wave_Packet_Init(int sigmax,int sigmay,int center_x0,int center_y0,double wave_vector)
{
	double normalization_const=1/sqrt(2*Pi*sigmax*Delta*sigmay*Delta);
	complex double wavefunction[N][N]={0};
	int x,y;
	State *state;

	for(x=0;x<N;x++)
	{
		if( center_x0-x<3*sigmax )
			continue;
		else if( x-center_x0>3*sigmax)
			break;
		for(y=0;y<N;y++)
		{
			if( center_y0-y<3*sigmay )
				continue;
			else if( y-center_y0>3*sigmay )
				break;
			else
			{
				wavefunction[x][y]=normalization_const * cexp(-1 * ( ( ( (Delta*x-center_x0)/2*sigmax*Delta) * ((Delta*x-center_x0)/2*sigmax*Delta) )   - ( ( (Delta*y-center_y0)/2*sigmay*Delta) * ((Delta*y-center_y0)/2*sigmay*Delta) )  - I*wave_vector*Delta*x )) ;
			}
		}
	}

	wavefunction_init(wavefunction,state);

	return state;
}

#endif
