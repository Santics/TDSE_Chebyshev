#ifndef SIMULATION
#define SIMULATION

#include"Data_structure.h"
#include"Bessel.h"


void hamiltonian_init(Operator_head* potential,int barriar_index,int slit_index[],Operator_head *operator)
{
	complex double constant=(H/(2*Pi))*(H/(2*Pi))/(MASS*Delta*Delta);
	int i,j;
	bool insert=0;


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
				element_append(operator,-constant,i,j);
		}
	}

	return ;
}

//approximate time evolution operator by chebyshev polynomial
void chebyshev_polynomial_approximation(Operator_head* hamiltonian,complex double evolution_time,int num_of_term,Operator_head *time_evolution_operator)
{
	complex double norm,constant=2,factor;
	int i,Jn_larger_than_this_zero;
	complex double bessel_function[num_of_term];
	double bessel_function_Jn[M]={0};
	Operator_head Tn_plus_1[N*N];
	Operator_head  U[N*N],Tn[N*N],Tn_minus_1[N*N],T_tmp[N*N];

	operator_init(Tn_plus_1);
	operator_init(time_evolution_operator);
	operator_init(T_tmp);
	norm=matrix_normalization(hamiltonian);
	evolution_time*=norm;

	Jn_larger_than_this_zero=Bessel_function(evolution_time,bessel_function_Jn,M);


	operator_init_I(U,bessel_function[0]);
	operator_init_I(Tn_minus_1,bessel_function[0]);
	operator_sum(Tn,hamiltonian);

	for( i=1; i < (num_of_term>Jn_larger_than_this_zero?num_of_term:Jn_larger_than_this_zero); i++ )
	{
		constant*=-I;
		factor=constant*bessel_function_Jn[i];

		//append Tn to the approximation result
		operator_set_null(T_tmp);
		operator_sum(T_tmp,Tn);
		operator_on_number(T_tmp,factor);
		operator_sum(time_evolution_operator,T_tmp);

		//calculate Tn+1
		operator_set_null(Tn_plus_1);
		operator_on_operator(hamiltonian,Tn,Tn_plus_1);
		operator_on_number(Tn_plus_1,2);
		operator_on_number(Tn_minus_1,-1);
		operator_sum(Tn_plus_1,Tn_minus_1);

		//prepare for the next loop Tn->Tn-1,Tn+1->Tn
		operator_transmission(Tn,Tn_minus_1);
		operator_transmission(Tn+1,Tn);

	}


	return ;

}

State* time_evolution_process(Operator_head* U,State *wavefunction_init)
{
	State* state;

	operator_on_state(U,wavefunction_init,state);

	return state;
}

#endif
