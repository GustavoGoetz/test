#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include <time.h>
int main(int argc,char **argv)
{
	int rank,size,i;
	double x=0,y=0,pi,z;
	int no = atoi(argv[1]);
	int count=0,total_count=0,no_div=0,fin_no = 0;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	no_div = no/size;
	srand ( time(NULL) );
	for(i=0;i<no_div;i++)
		{

		x=(rand()%100)/(double)100;
		y=(rand()%100)/(double)100;
		z=x*x+y*y;
		if(z<=1)
			count++;

		}
	printf("For rank %d count = %d itrr = %d\n",rank,count,no_div);
	MPI_Reduce(&count,&total_count,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Reduce(&no_div,&fin_no,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

	if(rank ==0)
		{
	printf("Total count  = %d, total itrr = %d\n",total_count,fin_no);
	pi = ((double)total_count)/fin_no*4.0000;


	printf("Pi value = %lf",pi);


		}
	MPI_Finalize();


}
