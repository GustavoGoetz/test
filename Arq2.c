#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc,char **argv)
{
        int rank,size;
        double x=0,y=0,pi,z, temp_ini, temp_fin;
        long int no = 100000000, i=0;
        int count=0, count_aux=0,total_count=0,no_div=0, no_div_aux=0,fin_no = 0 , in, name_len;
        MPI_Status st;
        MPI_Init(NULL,NULL);
        char name[MPI_MAX_PROCESSOR_NAME];
        MPI_Get_processor_name(name, &name_len);
        temp_ini= MPI_Wtime();
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);
        MPI_Comm_size(MPI_COMM_WORLD,&size);
        no_div = no/size;


        srand ( time(NULL) );
        for(i=0;i<no_div;i++)
                {

                x=(rand()%10000)/(double)10000;
                y=(rand()%10000)/(double)10000;
                z=x*x+y*y;
                if(z<=1)
                        count++;
                }


        printf("Name: %s - rank %d count = %d itrr = %d  \n",name,rank,count,no_div);
        if(rank != 0){
				MPI_Send(&count, 1 ,MPI_INT, 0 , 0, MPI_COMM_WORLD);
                MPI_Send(&no_div,1,MPI_INT,0,1,MPI_COMM_WORLD);
                fflush(stdout);
        }


        if(rank ==0)
                {
                        for(in=0; in < (size - 1); in++){
                                MPI_Recv(&count_aux,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&st);
                                count = count + count_aux;
                                MPI_Recv(&no_div_aux,1,MPI_INT,MPI_ANY_SOURCE,1,MPI_COMM_WORLD,&st);
                                no_div = no_div + no_div_aux;
                                fflush(stdout);
                        }

        printf("Total count  = %d, total itrr = %d\n",count,no_div);
        pi = ((double)count)/no*4.0000;
        printf("Pi value = %lf\n",pi);
        temp_fin = MPI_Wtime();
        temp_fin = temp_fin - temp_ini;
		        printf("Time: %f\n",temp_fin);

                }

        MPI_Finalize();

}


