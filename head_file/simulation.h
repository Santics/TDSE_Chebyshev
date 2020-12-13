#ifndef SIMULATION
#define SIMULATION
#define Delta 0.01
#define H 6.62606957e-34
#define Pi 3.1415926535
#define M 1e10-34
#include"data_structure.h"

void bessel_function(int n,complex double[] a);

Operator_head* hamiltonian_init(Operator_head* potential,int barriar_index,int slit_index[])
{
	complex double constant=(H/(2*Pi))*(H/(2*Pi))/(M*Delta*Delta);
	int i,j;
	bool insert=0;

	Operator_head operator[N*N];
	operator_init(operator);

	operator_sum(operator,potential);

	for(i=0;i<N*N;i++)
	{
		insert=0;
		for(j=0;j<N*N;j++)
		{
			if(i-j==1||i-j==-1)
			{
				if(j==barriar_index)  //same column as barriar
				{
					if(i>=slit_index[0]&&i<=slit_index[1]) //but it is a point between the slim
						insert=1;
				}
			}
			if(insert)
				element_append(operator,-constant,i,j)
		}
	}

	return operator;
}

Operator_head* chebyshev_polynomial_approximation(Operator_head* hamiltonian,complex double evolution_time,complex double[] bessel_function,int num_of_term)
{
	complex double norm;
	int i;

	norm=matrix_normalization(hamiltonian);
	evolution_time*=norm;


}
