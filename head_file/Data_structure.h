#ifndef DATA_STRUCTURE
#define DATA_STRUCTURE

#define Delta 0.01	//space interval
#define H 6.62606957e-34  //planck constant
#define Pi 3.1415926535
#define M 1e10-34 //mass
#define N 1000  //numbers of discretization samples

#include<complex.h>

/*Data Structure No.1 State*/

typedef struct			//representation of discrete wavefunction

{
	complex double data[N*N] wavefunction;
}State; 			

void wavefunction_init(complex double[][] init_state,State* state)			//map wavefunction from 2-dimensional array to a vector
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
	complex double data;
	int column;
	Operator* next;
}Operator;

typedef struct Operator_head		//choose linklist to represent an operator,set a head for them to save storage resources
{
	Operator* next;
}Operator_head;


void operator_init(Operator_head* operator)       //init an operator with all elements null
{
	int i;
	for(i=0;i<N*N;i++)
	{
		operator[i] -> next = NULL;
	}

	return;
}

void operator_init_I(Operator* operator,complex double x)
{
	int i;
	Operator* operator_node;

	for(i=0;i<N;i++)
	{
		operator_node = (Operator*)malloc(sizeof(Operator));
		operator_node->data=x;
		operator_node->column=i;
		operator_node->next=NULL;

		operator[i]->next=operator_node;
	}

	return;
}

void operator_set_null(Operator_head* operator)		//set all elements of an existing operator to zero
{
	int i;
	Operator* operator_node,operator_node_tmp;

	while(i=0;i<N*N;i++)
	{
		operator_node=operator[i]->next;
		while(operator_node!=NULL)
		{
			operator_tmp=operator_node->next;
			free(operator_node);
			operator_node=operator_tmp;
		}

		return;
	}
}

void operator_transmission(Operator_head* operator_a,Operator_head* operator_b)
{
	int i;

	operator_set_null(operator_b);

	for(i=0;i<N*N;i++)
	{
		operator_b[i]->next=operator_a[i]->next;
		operator_a[i]->next=NULL;
	}

	return;
}

double matrix_normalization(Operator_head* operator) //normalize the matrix with norm and return the norm in roder to compensate in time
{
	Operator* op_ptr=NULL;
	complex double norm=0,sum=0;
	int i=0;

	for(i=0;i<N*N;i++)
	{
		op_ptr = operator[i] -> next;
		while(op_ptr != NULL)
		{
			sum += op_ptr->data;
			op_ptr = op_ptr->next;
		}
		norm = creal(norm)>creal(sum)?creal(norm):creal(sum);
	}

	for(i=0;i<N*N;i++)
	{
		
		op_ptr = operator[i] -> next;
		while(op_ptr != NULL)
		{
			op_ptr->data /= norm;
			op_ptr = op_ptr->next;
		}
	}
	return norm;
}

/*codes of the following function sucks due to the stupid design of data structure "operator head"
 I should have let the head node the same as data node in case I would not have wasted so much time handling the first node
 however,considering I have finished this function as well as my lazy nature,I would not bother recoding them if it do not cause any tr--ouble*/

void element_append(Operator_head* operator,complex double data,int row,int column) //auxiliary function to append matrix element to an operator
{
	Operator* op_ptr=operator[row]->next,op_ptr_pre=operator[row]->next;		//Caution:row&column range from 0 to N-1 !!
	Operator* op_append=NULL;


	if(data==0)       							       //omit elements with null value
		return;

	op_append=(Operator*)malloc(sizeof(Operator));
	op_append->next=NULL;
	op_append->data=data;
	op_append->column=column;


	if(op_ptr==NULL)		//insert before the first data node
	{
		op_append -> next = operator -> next;
		operator -> next = op_append;
		return;
	}
	else if(op_ptr->column>=column)
	{
		if(op_ptr->column>column)
		{
			op_append -> next = operator -> next;
			operator -> next = op_append;
			return;
		}
		else if(op_ptr->column==column)
		{
			if(op_ptr->data+data == 0)
			{
				free(op_append);
				operator->next=op_ptr->next;
				free(op_ptr);
				return;
			}
			else
			{
				op_ptr->data+=data;
				free(op_append);
				return;
			}
		}
	}
	else	//insert after the first data node
	{
		op_ptr = op_prt->next;
		while(op_ptr!=NULL && op_ptr->column<column)
		{
			op_ptr_pre=op_ptr;
			op_ptr=op_ptr->next;
		}
		if(op_ptr==NULL||op_ptr->column>column)
		{
			op_append -> next = op_ptr_pre -> next;
			op_ptr_pre -> next = op_append;
			return;
		}
		else    //op_ptr->column == column
		{
			if(op_ptr->data+data==0)
			{
				op_ptr_pre->next=op_ptr->next;
				free(op_append);
				free(op_ptr);
				return;
			}
			else
			{
				op_ptr->data += data;
				free(op_append);
				return;
			}

		}
		
	}
}

void operator_sum(Operator_head* operator1,Operator_head* operator2)	//sum of two operators,result stores in the former
{
	int i=0;
	Operator* operator_node=NULL;

	for(i=0;i<N*N;i++)
	{
		operator_node=operator[i]->next;
		while(operator_node!=NULL)
		{
			element_append(operator1,operator_node->data,i,operator->column);
			operator_node = operator_node->next;
		}
	}
}
void  operator_on_number(Operator_head operator,complex double number)
{
	int i;
	Operator* operator_node;

	for(i=0;i<N*N;i++)
	{
		operator_node=operator[i]->next;
		while(operator_node!=NULL)
		{
			operator_node->data *= number;
			operator_node=operator_node->next;
		}
	}

	return;
}


State* oprtator_on_state(Operator_head* operator,State* state)	
{
	int i;
	complex double sum;
	State state_tmp;
	Operator* operator_node;

	while(i=0;i<N*N;i++)
	{
		operator_node=operator[i]->next;
		sum=0;
		while(operator_node!=NULL)
		{
			sum += operator_node->data*state->wavefunction[i*N+operator_node->column];
			operator_node=operator_node->next;
		}
		state_tmp.wavefunction[i]=sum;
	}

	return state_tmp;
}

Operator_head* operator_transpose(Operator_head* operator)   //this function is designed to simplify operator_on_operator function below
{
	int i,j;
	Operator operator_node;
	Operator_head operator_tmp[N*N];

	operator_init(operator_tmp);

	for(i=0;i<N*N;i++)
	{
		operator_node = operator[i]->next;
		while(operator_node!=NULL)
		{
			element_append(operator_tmp,operator_node->data,operator_column,i);
		}
	}

	return operator_tmp;
}


Operator_head* operator_on_operator(Operator_head* operator1,Operator_head* operator2)
{
	int i,j;
	complex double sum;
	Operator_head operator_tmp1[N*N],operator_tmp2[N*N];

	Operator operator_node1,operator_node2;

	operator_init(operator_tmp1);
	operator_init(operator_tmp2);

	operator_tmp1=operator_transpose(operator2);


	for(i=0;i<N*N;i++)
	{
		for(j=0;j<N*N;j++)
		{
			operator_node1=operator1[i]->next;
			operator_node2=operator_tmp1[j]->next;
			sum=0;
			while(operator_node1!=NULL&&operator_node2!=NULL)
			{
				if(operator_node1->column==operator_node2->column)
					sum+=operator_node1->data*operator_node2->data;
				else if(operator_node1->column>operator_node1->column)
					operator_node1=operator_node1->next;
				else if(operator_node2->column>operator_node2->column)
					operator_node2=operator_node2->next;
				if(sum!=0)
					element_append(operator_tmp2,sum,i,j);
			}
		}
	}

	return operator_tmp2;
}


#endif
