#include "Data_structure.h"
#include"Data_structure.h"
#include"Simulation.h"
#include"Bessel.h"
#include"Gaussia.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<complex.h>


int main()
{
	complex double  a[N][N];
	Operator *operator_node=(Operator*)malloc(sizeof(Operator));
	Operator *operator_node2;
	Operator_head *operator=(Operator_head*)malloc(sizeof(Operator_head));
	Operator_head *operator2=(Operator_head*)malloc(sizeof(Operator_head));
	Operator_head operator_3[N];
	State state;

	//test operator_init(clear)
	Operator_head hamiltonian[N*N];
	Operator_head hamiltonian2[N*N];
	Operator_head hamiltonian3[N*N];

	//test Gaussia(clear)
	State state_init;

	//test operator_normalization
	Operator* optr=NULL;


	operator_node->next=NULL;
	operator->next = NULL;
	(operator_3+1)->next=NULL;
	state.wavefunction[1]=0;
	wavefunction_initial(a,&state);


	operator_init(hamiltonian);
	operator_init(hamiltonian2);
	operator_init(hamiltonian3);

	Gaussia_Wave_Packet_Init(10,10,20,20,0.23,&state_init);
	

	optr = (operator_3+2)->next;
	optr=NULL;

	operator_init_I(hamiltonian,5);
	operator_init_I(hamiltonian2,2);

	operator_sum(hamiltonian,hamiltonian2);

	operator_on_number(hamiltonian,0.23);
	//operator_set_null(hamiltonian);
	//operator_transmission(hamiltonian2,hamiltonian);
	operator_on_operator(hamiltonian,hamiltonian2,hamiltonian3);
	

	printf("%ld %ld %ld\n",sizeof(operator_node),sizeof(operator_node2),sizeof(operator));


	return 0;
}
