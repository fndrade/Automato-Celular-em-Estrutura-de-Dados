#ifndef automato_h
#define automato_h

typedef struct automatocelular AutomatoCelular;

AutomatoCelular* alocarreticulado(int d);
AutomatoCelular* desalocarreticulado(AutomatoCelular* autcel);
void leiturareticulado (AutomatoCelular *autcel);
void evoluirreticulado(AutomatoCelular *autcel, int geracoes);
void imprimereticulado (AutomatoCelular *autcel);
void confereReticulado(AutomatoCelular *autcel, int **matrizaux);




#endif