//Christoffer de Pula  Oliveira
//Segundo trabalho prático de AEDS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
typedef struct item{
    int chave;
    char nome [60];
    char telefone[11];
    char cpf[11];
    char endereco[100];
    char outraString1[60];
    char outraString2[70];
    char outraString3[50];
    char outraString4[90];
}Item;

//Protótipos das funções.

void ordem_random(Item *Chave, int n_elem,int t_regis,int *chavei);
void ordem_crescente(Item *Chave, int n_elem,int t_regis,int *chavei);
void ordem_decrescente(Item *Chave, int n_elem,int t_regis,int *chavei);
void ordem_qcrescente(Item *Chave, int n_elem,int t_regis,int *chavei);
void ordem_qdecrescente(Item *Chave, int n_elem,int t_regis,int *chavei);
void SelectionSort(Item *Chave, int n_elem,int t_regis,int *chavei,unsigned long int *comp, unsigned long int *mov);
void InserctionSort(Item *Chave, int n_elem,int t_regis,int *chavei,unsigned long int *comp, unsigned long int *mov);
void ShellSort(Item *Chave, int n_elem,int t_regis,int *chavei,unsigned long int *comp, unsigned long int *mov);
void QuickSort(Item *Chave, int fim,int inicio,int t_regis,int *chavei,unsigned long int *comp, unsigned long int *mov);
void HeapSort(Item *Chave, int n_elem,int t_regis,int *chavei,unsigned long int *comp, unsigned long int *mov);
void CriaHeap(Item *Chave,int inicio,int fim,int t_regis,int *chavei,unsigned long int *comp, unsigned long int *mov);
void MergeSort(Item *Chave, int fim,int inicio,int t_regis,int *chavei,unsigned long int *comp, unsigned long int *mov);
int particiona(Item *Chave, int fim, int inicio,int t_regis,int *chavei,unsigned long int *comp, unsigned long int *mov);
void Merge(Item *Chave, int fim,int meio,int inicio,int t_regis,int *chavei,unsigned long int *comp, unsigned long int *mov);

int main(){
    int i,tamregistro,opc,qtd_elem,*chavei;
    Item *Chave;
    unsigned long int comp = 0;
    unsigned long int mov = 0;

    //Menu para serlecionar a quantidade de elementos a serem ordenados.

    printf("\tSelecione a quantidade de elementos:\n1-20\n2-500\n3-5000\n4-50000\n5-200000\n6-1000000\n");
    scanf("%d",&opc);
    switch(opc){
     case 1:
        qtd_elem = 20;
        break;
     case 2:
        qtd_elem = 500;
        break;
     case 3:
        qtd_elem = 5000;
        break;
     case 4:
        qtd_elem = 50000;
        break;
     case 5:
        qtd_elem = 200000;
        break;
     case 6:
        qtd_elem = 1000000;
        break;
    }

    //Menu para selecionar o tamanho da entrada, (struct ou int).

    printf("\tSelecione o tamanho da entrada:\n1-Registro pequeno\n2-Registro grande\n");
    scanf("%d",&tamregistro);
    switch(tamregistro){
     case 1:
        chavei = (int*) malloc(qtd_elem * sizeof(int));
        break;
     case 2:
       Chave = (Item*) malloc(qtd_elem * sizeof(struct item));
       break;
     default:
        printf("\nsem selecionar");
        break;
     }
    printf("\nSelecione o tipo de ordem inicial\n1-Aleatoria\n2-Crescente\n3-Descrescente\n4-Quase ordenado crescente\n5-Quase ordenado decrescente\n");
    scanf("%d",&opc);
    switch(opc){
     case 1:
        ordem_random(Chave,qtd_elem,tamregistro,chavei);
        break;
     case 2:
        ordem_crescente(Chave,qtd_elem,tamregistro,chavei);
        break;
     case 3:
        ordem_decrescente(Chave,qtd_elem,tamregistro,chavei);
        break;
     case 4:
        ordem_qcrescente(Chave,qtd_elem,tamregistro,chavei);
        break;
     case 5:
        ordem_qdecrescente(Chave,qtd_elem,tamregistro,chavei);
        break;
    }

    //Menu para selecionar o tipo de ordenação a ser utilizada.

    printf("\nSelecione o tipo de sort para ordenar os valores\n1-Selection\n2-Inserction\n3-Shell\n4-Quick\n5-Heap\n6-\n");
    scanf("%d",&opc);
    switch(opc){
     case 1:
        SelectionSort(Chave,qtd_elem,tamregistro,chavei,&comp,&mov);
        break;
     case 2:
        InserctionSort(Chave,qtd_elem,tamregistro,chavei,&comp,&mov);
        break;
     case 3:
        ShellSort(Chave,qtd_elem,tamregistro,chavei,&comp,&mov);
        break;
     case 4:
        QuickSort(Chave,qtd_elem,-1,tamregistro,chavei,&comp,&mov);
        break;
     case 5:
        HeapSort(Chave,qtd_elem,tamregistro,chavei,&comp,&mov);
        break;
     case 6:
        MergeSort(Chave,qtd_elem,0,tamregistro,chavei,&comp,&mov);
    }
    if(tamregistro == 2){
        for(i =0; i < qtd_elem; i++){
            printf("%d ",Chave[i].chave);
        }
        free(Chave);
    }
    else{
        for(i = 0; i < qtd_elem; i++){
            printf("%d ",chavei[i]);
        }
        free(chavei);
    }
    return 0;
}
void ordem_random(Item *Chave, int n_elem,int t_regis,int *chavei){
    int y;
    int i;

    //Atribuindo valores aleatórios no vetor

    srand(10);
    if(t_regis == 2){
        for(i = 0;i < n_elem;i++){
            y = 1 + ( rand() % n_elem );
            Chave[i].chave = y;
        }
    }else{
        for(i = 0;i < n_elem;i++){
            y=1 + ( rand() % n_elem );
            chavei[i] = y;
        }
    }
}

void ordem_crescente(Item *Chave, int n_elem,int t_regis,int *chavei){
    int i;

    //Atribuindo valores de 0 até o tamanho do vetor ao vetor.Para os dois tipos de dados.

    if(t_regis == 2){
        for(i = 0; i < n_elem; i++){
            Chave[i].chave = i;
        }
    }
    else{
        for(i = 0; i < n_elem; i++){
            chavei[i] = i;
        }
    }
}

void ordem_decrescente(Item *Chave, int n_elem,int t_regis,int *chavei){
    int i;

    //Atribuindo valores do tamanho do vetor a 0.Para os dois tipos de dados

    if(t_regis == 2){
        for(i = n_elem; i >= 0; i--){
            Chave[i].chave = i;
        }
    }
    else{
        for(i = n_elem; i >= 0; i--){
            chavei[i] = i;
        }
    }
}

void ordem_qcrescente(Item *Chave, int n_elem,int t_regis,int *chavei){
    int i;
    int y;

    /*Atribuindo valores sorteados até metade do tamanho do vetor e preenchendo o restante,
     do tamanho do vetor a 0.Para os dois tipos de dados.*/

    srand( ( unsigned)time(NULL));
    if(t_regis == 2){
        for(i = 0;i < n_elem/2;i++){
            y = 1 + ( rand() % n_elem );
            Chave[i].chave = y;
        }
        for(i = n_elem/2; i < n_elem; i++){
            Chave[i].chave = i;
        }
    }else{
        for(i = 0;i < n_elem/2;i++){
            y=1 + ( rand() % n_elem );
            chavei[i] = y;
        }
        for(i = n_elem/2; i < n_elem; i++){
            chavei[i] = i;
        }
    }
}

void ordem_qdecrescente(Item *Chave, int n_elem,int t_regis,int *chavei){
    int i;
    int y;

    /*Atribuindo valores sorteados até metade do tamanho do vetor e preenchendo o restante,
     de 0 ao tamanho do vetor.Para os dois tipos de dados.*/

    srand( ( unsigned)time(NULL));
    if(t_regis == 2){
        for(i = 0;i < n_elem/2;i++){
            y = 1 + ( rand() % n_elem );
            Chave[i].chave = y;
        }
        for(i = n_elem; i >= n_elem/2; i--){
            Chave[i].chave = i;
        }
    }else{
        for(i = 0;i < n_elem/2;i++){
            y=1 + ( rand() % n_elem );
            chavei[i] = y;
        }
        for(i = n_elem; i >= n_elem/2; i--){
            chavei[i] = i;
        }
    }
}

void InserctionSort(Item *Chave, int n_elem,int t_regis,int *chavei,unsigned long int *comp, unsigned long int *mov){
    int i,j,aux;
    Item aux2;
    if(t_regis == 2){ //para tipo struct.
        for(i = 1;i < n_elem; i++){
            aux2 = Chave[i];

            /*Comparando os valores, e se condição satisfeita movendo os valores maiores
             para frente e colocando o menor antes deles.*/

            for(j = i; (j > 0) && (aux2.chave < Chave[j - 1].chave); j--){
                Chave[j] = Chave[j - 1];
                mov++;
                comp++;
            }
            Chave[j] = aux2;
        }
    }else{ //para tipo int.
        for(i = 1; i < n_elem; i++){
            aux = chavei[i];

            /*Comparando os valores, e se condição satisfeita movendo os valores maiores
             para frente e colocando o menor antes deles.*/

            for(j = i; (j > 0) && (aux < chavei[j-1]) ; j--){
                chavei[j] = chavei[j - 1];
                mov++;
                comp++;
            }
            chavei[j] = aux;
        }
    }
}
void SelectionSort(Item *Chave, int n_elem,int t_regis,int *chavei,unsigned long int *comp, unsigned long int *mov){
    int i,j,menor,troca;
    Item troca2;
    if(t_regis == 2){ //Para tipo struct.
        for(i = 0; i < n_elem-1; i++){
            menor = i;

            //Procurando o menor elemnto em relação a'i'.

            for(j = i+1; j < n_elem; j++){
                if(Chave[j].chave < Chave[menor].chave){
                    menor = j;
                    comp++;
                }
            }

            //Troca os valores de posição atual com a 'menor'.

            if(i != menor){
                troca2 = Chave[i];
                Chave[i] = Chave[menor];
                Chave[menor] = troca2;
                mov++;
            }
        }
    }else{ //Para tipo int
        for(i = 0; i < n_elem-1; i++){
            menor = i;

            //Procura o menor valor em reação a 'i';

            for(j = i+1; j < n_elem; j++){
                if(chavei[j] < chavei[menor]){
                menor = j;
                comp++;
                }
            }

            //Troca os valores da posição atual com a 'menor'.

            if(i != menor){
                troca = chavei[i];
                chavei[i] = chavei[menor];
                chavei[menor] = troca;
                mov++;
                comp++;
            }
        }
    }
}
void ShellSort(Item *Chave, int n_elem,int t_regis,int *chavei,unsigned long int *comp, unsigned long int *mov){
    int i,j,aux;
    int h = 1;
    Item aux2;
    do{ //Determinando o valor de 'h'
        h = h * 3 + 1;
    }while(h < n_elem);
    if(t_regis == 2){ // Para tipo struct
        do {
            h = h / 3;
            for (i = h; i < n_elem; i++){
                aux2 = Chave[i];
                j = i;
                comp++;

                //Pegando dois indices do vetor com diferença de 'h', comparando e evetuando a troca se necessário.

                while (Chave[j - h].chave > aux2.chave){
                    Chave[j] = Chave[j - h];
                    j = j - h;
                    mov++;
                    if(j < h){
                        break;
                    }
                }
                Chave[j].chave = aux2.chave;
            }
        }while (h > 1);
    }else{ //Para tipo int
        do {
            h = h / 3;
            for (i = h; i < n_elem; i++){
                aux = chavei[i];
                j = i;
                comp++;

                //Pegando dois indices do vetor com diferença de 'h', comparando e evetuando a troca se necessário.

                while (chavei[j - h] > aux){
                    chavei[j] = chavei[j - h];
                    j = j - h;
                    mov++;
                    if(j < h){
                        break;
                    }
                }
                chavei[j] = aux;
            }
        }while (h > 1);
    }
}
void QuickSort(Item *Chave, int fim,int inicio,int t_regis,int *chavei,unsigned long int *comp, unsigned long int *mov){
    int pivo;
    if(fim > inicio){
        pivo = particiona(Chave,fim,inicio,t_regis,chavei,&comp,&mov); //separa os dados em duas partições.
        QuickSort(Chave,pivo-1,inicio,t_regis,chavei,&comp,&mov);
        QuickSort(Chave,fim,pivo+1,t_regis,chavei,&comp,&mov);
    }
}
int particiona(Item *Chave, int fim, int inicio,int t_regis,int *chavei,unsigned long int *comp, unsigned long int *mov){
    int esq = 0,dir = 0,pivo = 0,aux = 0;
    Item aux2;
    Item pivo2;
    if(t_regis == 2){ //Para tipo struct.
        esq = inicio;
        dir = fim;
        pivo2 = Chave[inicio];
        while(esq < dir){
            while(Chave[esq].chave <= pivo2.chave){ //Avança posição da esquerda
                comp++;
                esq++;
            }
            while(Chave[dir].chave > pivo2.chave){ //Recua posição da direita.
                comp++;
                dir--;
            }
            if(esq < dir){ //Trocando esquerda com direita.
                aux2 = Chave[esq];
                Chave[esq] = Chave[dir];
                Chave[dir] = aux2;
                comp++;
                mov++;
            }
        }
        Chave[inicio] = Chave[dir];
        Chave[dir] = pivo2;
        mov++;
        return dir;
    }else{ //Para tipo int.
        esq = inicio;
        dir = fim;
        pivo = chavei[inicio];
        while(esq <= dir){
            while(chavei[esq] <= pivo){ //Avança posição da esquerda.
                esq++;
                comp++;
            }
            while(chavei[dir] > pivo){ //Recua posição da direita.
                dir--;
                comp++;
            }
            if(esq < dir){ //Troca esquerda com direita.
                aux = chavei[esq];
                chavei[esq] = chavei[dir];
                chavei[dir] = aux;
                comp++;
                mov++;
            }
        }
        chavei[inicio] = chavei[dir];
        chavei[dir] = pivo;
        mov++;
        return dir;
    }
}
void HeapSort(Item *Chave, int n_elem,int t_regis,int *chavei,unsigned long int *comp, unsigned long int *mov){
    int i,aux;
    Item aux2;

    //Cria geap a partir dos dados.

    for(i = (n_elem)/2;i >=0; i--){
        CriaHeap(Chave,i,n_elem-1,t_regis,chavei,&comp,&mov);
    }
    if(t_regis == 2){ //Para tipo struc	[l†∂]Lord_Kylest.

        //Pega o maior elemento da heap e coloca na sua posição correspondente no vetor.

        for(i = n_elem-1; i >=1; i--){
            aux2 = Chave[0];
            Chave[0] = Chave[i];
            Chave[i] = aux2;
            CriaHeap(Chave,0,i-1,t_regis,chavei,&comp,&mov);
        }
    }
    else{ //Para tipo int.

        //Pega o maior elemento da heap e coloca na sua posição correspondente no vetor.
        for(i = n_elem-1; i >=1; i--){
            aux = chavei[0];
            chavei[0] = chavei[i];
            chavei[i] = aux;
            CriaHeap(Chave,0,i-1,t_regis,chavei,&comp,&mov);
            comp++;
            mov++;
        }
    }
}
void CriaHeap(Item *Chave,int inicio,int fim,int t_regis,int *chavei,unsigned long int *comp, unsigned long int *mov){
    Item aux2;
    aux2 = Chave[inicio];
    int aux = chavei[inicio];
    int j = inicio*2+1;
    if(t_regis == 2){ //Para tipo struct.
            while(j <= fim){

            //Verificando se a raiz tem duas folhas e encontrando a maior.

            if(j < fim){
                if(Chave[j].chave < Chave[j+1].chave){
                    j = j+1;
                }
            }

            //Se a folha maior, maior que a raiz a folha se torna raiz.

            if(aux2.chave < Chave[j].chave){
                Chave[inicio] = Chave[j];
                inicio = j;
                j = 2*inicio+1;
                mov++;
                comp++;
            }else{
                j = fim + 1;
            }
            Chave[inicio] = aux2;  //Antiga raiz ocupa lugar da antiga folha analizada.
        }
    }else{ //Para tipo int.

        //Verificando se a raiz tem duas folhas e encontrando a maior.

        while(j <= fim){
            if(j < fim){
                if(chavei[j] < chavei[j+1]){
                    j = j+1;
                    comp++;
                }
            }

            //Se a folha maior, maior que a raiz a folha se torna raiz.

            if(aux < chavei[j]){
                chavei[inicio] = chavei[j];
                inicio = j;
                j = 2*inicio+1;
                comp++;
                mov++;
            }else{
                j = fim + 1;
            }
        }
        chavei[inicio] = aux; //Antiga raiz ocupa lugar da antiga folha analizada.
        mov++;
    }
}

void MergeSort(Item *Chave, int posicaoInicio, int posicaoFim, int t_regis, int *chavei,unsigned long int *comp, unsigned long int *mov) {
    int i, j, k, metadeTamanho, *vetorTemp;

    if(posicaoInicio == posicaoFim) return;

    // ordenacao recursiva das duas metades
    metadeTamanho = (posicaoInicio + posicaoFim ) / 2;
    MergeSort(Chave, posicaoInicio, metadeTamanho + 1, t_regis, chavei,&comp,&mov);
    MergeSort(Chave, metadeTamanho, posicaoFim, t_regis, chavei,&comp,&mov);

    // intercalacao no vetor temporario t
    i = posicaoInicio;
    j = metadeTamanho + 1;
    k = 0;
    vetorTemp = (int *) malloc(sizeof(int) * (posicaoFim - posicaoInicio + 1));
    while(i < metadeTamanho + 1 || j  < posicaoFim + 1) {
        if (i == metadeTamanho + 1 ) { // i passou do final da primeira metade, pegar v[j]
            vetorTemp[k] = chavei[j];
            j++;
            k++;
        }
        else {
            if (j == posicaoFim + 1) { // j passou do final da segunda metade, pegar v[i]
                vetorTemp[k] = chavei[i];
                i++;
                k++;
                comp++;
            }
            else {
                if (chavei[i] < chavei[j]) {
                    vetorTemp[k] = chavei[i];
                    i++;
                    k++;
                    comp++;
                    mov++;
                }
                else {
                    vetorTemp[k] = chavei[j];
                    j++;
                    k++;
                }
            }
        }

    }
    // copia vetor intercalado para o vetor original
    for(i = posicaoInicio; i <= posicaoFim; i++) {
        chavei[i] = vetorTemp[i - posicaoInicio];
    }
    free(vetorTemp);
}

