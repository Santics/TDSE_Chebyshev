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
	State state , state_init;
	static Operator_head hamiltonian[N*N],potential[N*N],time_evolution_operator[N*N];
	int slit_index[2]={145,155},num_of_term=10;
	complex double evolution_time=0;

	operator_init(hamiltonian);
	operator_init(potential);
	operator_init(time_evolution_operator);
	
	Gaussia_Wave_Packet_Init(50,50,100,100,0.23,&state_init);
	hamiltonian_init(potential,200,slit_index,hamiltonian);
	chebyshev_polynomial_approximation( hamiltonian, evolution_time,  10 ,time_evolution_operator );
	time_evolution_process( time_evolution_operator, &state_init, &state);

	//next step is to output state->wavefunction[i] to a file and draw it with Matlab or something







	return 0;


}
