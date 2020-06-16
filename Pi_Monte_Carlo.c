#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc,char **argv)
{
	int rank,size;
	double x=0,y=0,pi,z, temp_ini, temp_fin;
	long int no = 1000000000, i=0;
	int count=0,total_count=0,no_div=0,fin_no = 0;
	MPI_Init(NULL,NULL);
	char name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(name, &name_len);
	temp_ini= MPI_Wtime();
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	no_div = no/size;
	srand ( time(NULL) );
	for(i=0;i<no_div;i++)
		{

		x=(rand()%1000)/(double)1000;
		y=(rand()%1000)/(double)1000;
		z=x*x+y*y;
		if(z<=1)
			count++;

		}
	printf("For rank %d count = %d itrr = %d  name = %s\n",rank,count,no_div);
	MPI_Reduce(&count,&total_count,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Reduce(&no_div,&fin_no,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	fflsuh(stdout);
	if(rank ==0)
		{
	printf("Total count  = %d, total itrr = %d\n",total_count,fin_no);
	pi = ((double)total_count)/fin_no*4.0000;


	printf("Pi value = %lf\n",pi);
	temp_fin = MPI_Wtime();
	temp_fin = temp_fin - temp_ini;
	printf("Time: %f\n",temp_fin);

		}
	MPI_Finalize();


}
