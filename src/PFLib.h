#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>



/// Os typedefs com ponteiros para estruturas permitem ao main.c o acesso �s estruturas no PFLib.c atrav�s de ponteiros
typedef struct DADOS            *dados;
typedef struct CADASTRO         *cad;
typedef struct LISTA_ESTATICA   *est;



/// Fun��es para manipula��o do console
// Realiza a limpeza da tela
void limpa(void);

// Permite posicionar o cursor em qualquer lugar do console
void position(int row, int col);

// Limpa apenas uma linha
void clearline(void);

// Limpa o buffer
void limpa_buffer();



/// Mensagem
// Fun��o que permite a padroniza��o de alertas
void mensagem(int msg);



/// Lista est�tica
// Cria uma nova lista est�tica e retorna um ponteiro para o seu endere�o
est nova_lista_estatica();

// Apaga uma lista ent�tica
void apagar_lista_estatica(est lista);



/// Cria��o e destrui��o da lista de funcion�rios
// Cria uma lista ligada para aloca��o de registros de funcion�rios
cad *nova_lista();

// Apaga uma lista ligada de funcion�rios
void apagar_lista(cad *lista);



/// Rotinas de formata��o de texto
// Incorpora recursos das fun��es traca_linha() e centraliza_texto() para a cria��o de um t�tulo grafico padronizado
void titulo(int opcao, char texto[]);



/// Menus
// Fun��o para a inser��o de novos registros na lista ligada
void menu_inserir(cad *lista, int *cod, est lista_est);

// Fun��o para exclus�o de registros da lista ligada
void menu_excluir(cad *lista, est lista_est);

// Fun��o para edi��o de registros da lista ligada
void menu_editar(cad *lista, est lista_est);

// Menu geral de busca de registros
void menu_buscar(cad *lista, est lista_est);

// Menu geral de exibi��o
void menu_exibir(cad *lista, int *cod, est lista_est);

// Menu gr�fico que apresenta as op��es do menu principal no main.c
void menu();
