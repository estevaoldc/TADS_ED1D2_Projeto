// Projeto final - Gerenciamento com Lista CBO 2020_1

/**-----------------------------------------------------------------------------

    O seguinte programa gerencia o resgistro de funcionários utilizando
    algorítmos de Lista Sequencial Dinâmica e Lista Sequencial Estática.
    Nele, é possível adiconar novos registros de funcionários, edita-los,
    remove-los, realizar pesquisa por id e por nome, e por fim, exibir todos
    eles pelo id ou por um intervalo de salário informado pelo usuário.

-----------------------------------------------------------------------------**/

/*
    Autor .............: Estevão Luiz Duarte da Costa
    Matrícula .........: GU3011771
    Data ..............: 24/09/2020
    Versão ............: 1.0
    Revisão ...........: 29/09/2020
*/


#include "PFLib.h"

int main() {
    cad *lista = NULL;
    lista = nova_lista();
    est consulta = NULL;
    consulta = nova_lista_estatica();

    int cod = 0;

    titulo(0, "PROGRAMA DE CADASTRO DE FUNCIONARIOS");
    int opcao;
    do {
        menu();
        scanf("%d", &opcao);
        limpa_buffer();

        switch (opcao) {
            case 0: break;
            case 1: menu_inserir(lista, &cod, consulta);    break;
            case 2: menu_excluir(lista, consulta);          break;
            case 3: menu_editar(lista, consulta);           break;
            case 4: menu_buscar(lista, consulta);           break;
            case 5: menu_exibir(lista, &cod, consulta);     break;
            default: mensagem(1);                           break;
        }
        limpa(); position(1,1);
    }
    while (opcao != 0);

    apagar_lista(lista);
    apagar_lista_estatica(consulta);
    return 0;
}

