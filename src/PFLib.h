#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>



/// Os typedefs com ponteiros para estruturas permitem ao main.c o acesso às estruturas no PFLib.c através de ponteiros
typedef struct DADOS            *dados;
typedef struct CADASTRO         *cad;
typedef struct LISTA_ESTATICA   *est;



/// Funções para manipulação do console
// Realiza a limpeza da tela
void limpa(void);

// Permite posicionar o cursor em qualquer lugar do console
void position(int row, int col);

// Limpa apenas uma linha
void clearline(void);

// Limpa o buffer
void limpa_buffer();



/// Mensagem
// Função que permite a padronização de alertas
void mensagem(int msg);



/// Lista estática
// Cria uma nova lista estática e retorna um ponteiro para o seu endereço
est nova_lista_estatica();

// Apaga uma lista entática
void apagar_lista_estatica(est lista);



/// Criação e destruição da lista de funcionários
// Cria uma lista ligada para alocação de registros de funcionários
cad *nova_lista();

// Apaga uma lista ligada de funcionários
void apagar_lista(cad *lista);



/// Rotinas de formatação de texto
// Incorpora recursos das funções traca_linha() e centraliza_texto() para a criação de um título grafico padronizado
void titulo(int opcao, char texto[]);



/// Menus
// Função para a inserção de novos registros na lista ligada
void menu_inserir(cad *lista, int *cod, est lista_est);

// Função para exclusão de registros da lista ligada
void menu_excluir(cad *lista, est lista_est);

// Função para edição de registros da lista ligada
void menu_editar(cad *lista, est lista_est);

// Menu geral de busca de registros
void menu_buscar(cad *lista, est lista_est);

// Menu geral de exibição
void menu_exibir(cad *lista, int *cod, est lista_est);

// Menu gráfico que apresenta as opções do menu principal no main.c
void menu();
