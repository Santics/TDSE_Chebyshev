#include"Data_structure.h"
#include"Simulation.h"
#include"Bessel.h"
#include"Gaussia.h"
#include<stdio.h>
#include<stdlib.h>

int main()
{
	State state_init,state;
	Operator_head hamiltonian[N*N],pontential[N*N],time_evolution_operator[N*N];
	int slit_index[2]={590,610},num_of_term=10;
	double bessel_function[20];
	complex double evolution_time=0;

	operator_init(potential);
	state_init = Gaussia_Wave_Packet_Init(50,50,200,200,0.23);
	hamiltonian_init(potential,600,slit_index);
	free(potential);
	time_evolution_operator = chebyshev_polynomial_approximation( hamiltonian, evolution_time, bessel_function, 10  );
	state =  time_evolution_process( time_evolution_operator, state_init );

	//next step is to output state->wavefunction[i] to a file and draw it with Matlab or something







	return 0;


}
