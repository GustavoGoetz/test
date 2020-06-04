#include<stdio.h>
#include<math.h>

int posicao(int n, int op){

    int k;
    int i=32, count=0;
    for (i--; i >= 0; i--)
   {
      k = n >> i;
      if (k & 1){
          count++;
          printf("Posicao: %d 1\n",i);
          i=-1;
        }
      else{
          count++;
          printf("Posicao: %d 1\n",i);
      }

    }
    printf("\nCOUNT : %d",count);
    if(op == 1){
        count = 32 - count;
        count = count - 23;
        return count;
    }
    if(op == 2){
        count = 31 - count;
        printf("\nCOUNT : %d",count);
        count = count - 23;
        printf("\nCOUNT : %d",count);
        return count;
    }

}

int expoente(int exp){
   return exp -127;
}

void binario(int n, int i)
{
    int k;
    for (i--; i >= 0; i--)
   {
      k = n >> i;
      if (k & 1)
          printf("1");
      else
         printf("0");
    }
}

typedef union {
	float f;
	struct {
		unsigned int mantissa : 23;
		unsigned int exponente : 8;
		unsigned int sinal : 1;
	} field;
} unionfloat;

int main() {

    int exp1, exp2, exp, shift,oper;
	unsigned int aux1 ,aux2, aux3;
	unionfloat var[3];
    printf("Numero 1: ");
    scanf("%f",&var[0].f);

    printf("\nNumero 2: ");
    scanf("%f",&var[1].f);

    printf("\n1- Soma\n2- Subtracao\n");
    scanf("%d",&oper);

    //system("cls");

    if((var[0].field.sinal == 0) && (var[1].field.sinal == 0)){
        var[2].field.sinal = 0;
    }
    if((var[0].field.sinal == 1) && (var[1].field.sinal == 1)){
        var[2].field.sinal = 1;
    }


    exp1=expoente(var[0].field.exponente);
    exp2=expoente(var[1].field.exponente);

    aux1=var[0].field.mantissa | 0x800000;
    aux2=var[1].field.mantissa | 0x800000;


    if(exp1 > exp2){
        exp = exp1 - exp2;
        aux2 = aux2 >> exp;
        exp = exp1;
        }
    if(exp1 < exp2){
        exp = exp2 - exp1;
        aux1 = aux1 >> exp;
        exp = exp2;
        }
    if(exp1 == exp2){
        exp = exp1;
    }

    if(oper == 1){
    aux3 = aux1 + aux2;
    shift=posicao(aux3,oper);
    aux3 = aux3 >> shift;
    exp= 127 + exp + shift;
    }
    if(oper == 2){
    aux3 = aux1 - aux2;
    shift=posicao(aux3,oper);
    aux3 = aux3 << 8;
    exp = 127 + 1;
    }

    var[2].field.exponente = exp;
    var[2].field.mantissa = aux3;
    printf("\nResultado: ");
    binario(var[2].field.sinal, 1);
    printf(" ");
    binario(var[2].field.exponente, 8);
    printf(" ");
    binario(var[2].field.mantissa, 23);


    printf("\nnumero reconstituido  : %f", pow(-1,(var[2].field.sinal)) * ( 1.0 + var[2].field.mantissa / pow(2,23)) * pow(2,(var[2].field.exponente - 127)));
    printf("\n");

    return 0;
}
