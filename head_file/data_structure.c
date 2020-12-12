#ifndef DATA_STRUCTURE
#define DATA_STRUCTURE

#define N 1000  //numbers of discretization samples

/*Data Structure No.1 State*/

typedef struct			//representation of discrete wavefunction

{
	data[N*N] wavefunction;
}State; 			

void wavefunction_init(double[][] init_state,State* state)			//map wavefunction from 2-dimensional array to a vector
{
	int i,j;
	for(i=0;i<N;i++)
		for(j=0;k<N;j++)
		{
			state -> wavefunction[i*N+j] = init_state[i][j];
		}

	return;
}			

/*Data Structure No.2 Operator*/

typedef struct	Operator		//representation of operators considering it is usually a sparse matrix
{
	double data;
	int column;
	Operator* next;
}Operator;

typedef struct Operator_head		//choose linklist to represent an operator,set a head for them to save storage resources
{
	Operator* next;
}Operator_head;


void operator_init(Operator_head *operator)
{
	int i;
	for(i=0;i<N;i++)
	{
		operator[i] -> next = NULL;
	}

	return;
}
