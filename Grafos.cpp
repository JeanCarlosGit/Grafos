#include <stdio.h>
#include <malloc.h>

struct aresta;
struct vertice{
	struct vertice *prox;
	char name;
	struct aresta *adj;
}*start=NULL;

struct aresta{
	char dest;
	struct aresta *link;
};

struct vertice *buscar(char item);
int cont_vertice = 0;
int cont_aresta = 0;

void insert_vertice(char vertice){
	cont_vertice++;
	struct vertice *tmp,*ptr;
	tmp=(struct vertice *)malloc(sizeof(struct vertice));
	tmp->name=vertice;
	tmp->prox=NULL;
	tmp->adj=NULL;

	if(start==NULL){
		start=tmp;
		return;
	}
	ptr=start;
	while( ptr->prox!=NULL)
		ptr=ptr->prox;
	ptr->prox=tmp;

}

void delete_vertice(char u){
	cont_vertice--;
	struct vertice *tmp,*q;
	if(start->name == u)
	{
		tmp=start;
		start=start->prox;
		free(tmp);
		return;
	}
	q=start;
	while(q->prox->prox != NULL){
		if(q->prox->name==u){
			tmp=q->prox;
			q->prox=tmp->prox;
			free(tmp);
			return;
		}
		q=q->prox;
	}
	if(q->prox->name==u){
		tmp=q->prox;
		free(tmp);
		q->prox=NULL;
	}
}

void delvertice_aresta(char u){
	cont_aresta--;
	struct vertice *ptr;
	struct aresta *q,*start_aresta,*tmp;
	ptr=start;
	while(ptr!=NULL)
	{
		if(ptr->adj->dest == u){
			tmp=ptr->adj;
			ptr->adj=ptr->adj->link;
			free(tmp);
			continue;
		}
		q=ptr->adj;
		while(q->link->link != NULL){
			if(q->link->dest==u){
				tmp=q->link;
				q->link=tmp->link;
				free(tmp);
				continue;
			}
			q=q->link;
		}
		if(q->link->dest==u){
			tmp=q->link;
			free(tmp);
			q->link=NULL;
		}
		ptr=ptr->prox;
	}
}

void insert_aresta(char u,char v){
	cont_aresta++;
	struct vertice *locu,*locv;
	struct aresta *ptr,*tmp;
	locu=buscar(u);
	locv=buscar(v);

	if(locu==NULL ){
		printf("ERRO. Vertice de origem inexistente %c\n",u);
		return;
	}
	if(locv==NULL ){
		printf("ERRO. Vertice destino inexistente %c\n",v);
		return;
	}
	tmp=(struct aresta *)malloc(sizeof(struct aresta));
	tmp->dest=v;
	tmp->link=NULL;


	if(locu->adj==NULL){
		 locu->adj=tmp;
		  return;
	}
	ptr=locu->adj;
	while(ptr->link!=NULL)
		ptr=ptr->link;
	ptr->link=tmp;
}

struct vertice *buscar(char item){
	struct vertice *ptr,*loc;
	ptr=start;
	while(ptr!=NULL){
		if(item==ptr->name){
			loc=ptr;
			return loc;
		}
		else
			ptr=ptr->prox;
	}
	loc=NULL;
	return loc;
}

void del_aresta(char u,char v){
	struct vertice *locu,*locv;
	struct aresta *ptr,*tmp,*q;
	locu=buscar(u);

	if(locu==NULL ){
		printf("ERRO. Aresta inexistente\n");
		return;
	}

	if(locu->adj->dest == v){
		tmp=locu->adj;
		locu->adj=locu->adj->link;
		free(tmp);
		return;
	}
	q=locu->adj;
	while(q->link->link != NULL){
		if(q->link->dest==v){
			tmp=q->link;
			q->link=tmp->link;
			free(tmp);
			return;
		}
		q=q->link;
	}
	if(q->link->dest==v){
		tmp=q->link;
		free(tmp);
		q->link=NULL;
		return;
	}
	printf("ERRO. Aresta inexistente\n");
}

void imprimir(){
	struct vertice *ptr;
	struct aresta *q;

	ptr=start;
	while(ptr!=NULL)
	{
		printf("%c ->",ptr->name);
		q=ptr->adj;
		while(q!=NULL)
		{
			printf(" %c",q->dest);
			q=q->link;
		}
		printf("\n");
		ptr=ptr->prox;
	 }
}
main()
{
	int x;
	char vertice,origem,destino;
	while(1)
	{
		printf("1.Inserir um vertice\n");
		printf("2.Inserir uma aresta\n");
		printf("3.Deletar um vertice\n");
		printf("4.Deletar uma aresta\n");
		printf("5.Imprimir\n");
		printf("6.Contagem de vertices\n");
		printf("7.Contagem de arestas\n");
		printf("8.Sair\n\n");
		scanf("%d",&x);

		switch(x)
		{
		 case 1:
			printf("Digite o vertice a ser inserido: ");
			fflush(stdin);
			scanf("%c",&vertice);
			insert_vertice(vertice);
			break;
		 case 2:
			printf("Digite a aresta a ser inserida: ");
			fflush(stdin);
			scanf("%c %c",&origem,&destino);
			insert_aresta(origem,destino);
			break;
		 case 3:
			printf("Digite o vertice a ser deletado : ");
			fflush(stdin);
			scanf("%c",&vertice);
			delete_vertice(vertice);
			delvertice_aresta(vertice);
			break;
		 case 4:
			printf("Digite a aresta a ser deletada: ");
			fflush(stdin);
			scanf("%c %c",&origem,&destino);
			del_aresta(origem,destino);
			break;
		 case 5:
			imprimir();
			break;
		 case 6:
			printf("\n Numero de vertices: %d\n", cont_vertice);
			break;
		 case 7:
			printf("\n Numero de arestas: %d\n", cont_aresta);
			break;
		 case 8:
			break;
		 default:
			printf("...\n");
			break;
		 }
	}
}
