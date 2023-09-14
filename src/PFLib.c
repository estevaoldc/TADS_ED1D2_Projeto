#include "PFLib.h"



/// Define o um número fixo para o tamanho da tela para a centralizacao do texto dos títulos e menus
#define tela_tamanho 80



/// Estruturas de dados
// Estrutura de dados dos funcionários, usada pela lista ligada
struct DADOS {
    int     id;
    char    nome[101];
    char    endereco[101];
    int     idade;
    float   salario;
    int     cargo;
};

// Estrutura do nó da lista ligada
struct CADASTRO {
    struct DADOS    dados;
    struct CADASTRO *proximo;
};

// Estrutura de dados da lista estática
struct LE_DADOS {
    int     id;
    char    nome[101];
    int     codigo;
};

// Estrutura da lista estática em si
struct LISTA_ESTATICA {
    struct LE_DADOS     cargo[20];
};



/// Funções para manipulação do console
/* Condições para programação genérica. Permite que as funçõs de limpeza de tela e posição de cursor funcionem tando em Windows,
   quanto em sistemas de base Unix, como o Linux ou MacOS */
#if defined _WIN32 || defined _WIN64
    void limpa(void) {
        HANDLE TELA;
        DWORD ESCRITA = 0;
        COORD POS;
        TELA = GetStdHandle(STD_OUTPUT_HANDLE);
        POS.X = 0;
        POS.Y = 0;
        FillConsoleOutputCharacter(TELA, 32, 100 * 100, POS, &ESCRITA);
    }

    void position(int row, int col) {
        if (col >= 1 && col <= 80 && row >= 1 && row <= 24) {
            HANDLE TELA;
            COORD POS;
            TELA = GetStdHandle(STD_OUTPUT_HANDLE);
            POS.X = col - 1;
            POS.Y = row - 1;
            SetConsoleCursorPosition(TELA, POS);
        }
    }

    void clearline(void) {
        HANDLE TELA;
        COORD POS;
        CONSOLE_SCREEN_BUFFER_INFO VIDEO;
        DWORD ESCRITA = 0;
        TELA = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(TELA, &VIDEO);
        POS.Y = VIDEO.dwCursorPosition.Y;
        POS.X = VIDEO.dwCursorPosition.X;
        FillConsoleOutputCharacter(TELA, 32, 80 - POS.X, POS, &ESCRITA);
    }
#else
    void limpa(void) {
    printf("\033[2J");
    }

    void position(int row, int col) {
    if (col >= 1 && col <= 80 && row >= 1 && row <= 24)
        printf("\033[%d; %dH", row, col);
    }

    void clearline(void) {
        printf("\033[K");
    }
#endif

// Limpa o buffer
void limpa_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}


/// Lista estática
// Cria uma nova lista estática e retorna um ponteiro para o seu endereço
est nova_lista_estatica() {
    est lista = NULL;
    lista = (struct LISTA_ESTATICA*) malloc(sizeof(struct LISTA_ESTATICA));

    // Criação de vetores com os nomes e codigos dos cargos para evitar a digitação exaustiva e minimizar a incidência de erros
    char nomes[20][101] = {
        "Engenheiro aeronautico",
        "Engenheiro agricola",
        "Engenheiro agrimensor",
        "Engenheiro agronomo",
        "Engenheiro civil",
        "Engenheiro de alimentos",
        "Engenheiro de aplicativos em computacao",
        "Engenheiro de controle de qualidade",
        "Engenheiro de controle e automacao",
        "Engenheiro de equipamentos em computacao",
        "Engenheiro de logistica",
        "Engenheiro de manutencao de telecomunicacoes",
        "Engenheiro de pesca",
        "Engenheiro de producao",
        "Engenheiro de redes de comunicacao",
        "Engenheiro de riscos",
        "Engenheiro de seguranca do trabalho",
        "Engenheiro de telecomunicacoes",
        "Engenheiro eletricista",
        "Engenheiro mecanico"
    };

    int codigos [20] = {
        214425,
        222105,
        214805,
        222110,
        214205,
        222205,
        212205,
        214910,
        202110,
        212210,
        214945,
        214335,
        222115,
        214905,
        214350,
        214920,
        214915,
        214340,
        214305,
        214405
    };

    // União dos vetores de nome, código, e número de cada opçãoo na lista estática
    for (int i = 0; i < 20; i++) {
        lista->cargo[i].id = i + 1;
        strcpy(lista->cargo[i].nome, nomes[i]);
        lista->cargo[i].codigo = codigos[i];
    }

    return lista;
}

// Apaga uma lista estática
void apagar_lista_estatica(est lista) {
    free(lista);

    return;
}



/// Mensagem
// Função que permite a padronização de alertas
void mensagem(int msg) {
    printf("\n");
    switch (msg) {
        case 0:
            printf("\nOperacao realizada com sucesso! Voltando para o menu principal.");
            break;
        case 1:
            printf("Opcao invalida! Por favor, entre um novo valor.");
            break;
        case 2:
            printf("Lista inesistente!");
            break;
        case 3:
            printf("Lista vazia!");
            break;
        case 4:
            printf("Memoria insuficiente! Operacao abortada.");
            break;
        case 5:
            printf("Cargo invalido! Por favor, escolha uma nova opcao");
            break;
        case 6:
            printf("\nOperacao abortada! Voltando para o menu principal.");
            break;
    }
    limpa_buffer();
    printf("\n\n");

    return;
}



/// Criação e destruição da lista de funcionários
// Cria uma lista ligada para alocação de registros de funcionários
cad *nova_lista() {
    cad *lista = NULL;      // Criação da variável que apontará para a lista dinamicamente alocada
    lista = (cad*) malloc(sizeof(struct CADASTRO));     // Criação da lista
    if (lista != NULL) {        // Verifica não houveram problemas na alocação da memória
        *lista = NULL;          // Se estiver tudo bem, o cabeçário da lista aponta para o primeiro item, atualmente vazio
    }

    return lista;
}

// Apaga uma lista ligada de funcionários
void apagar_lista(cad *lista) {
    if (lista == NULL){     // Verifica se a lista existe. Aqui é irrelevante verificar se a lista está vazia ou não, como em outras funções, pois ele será completamente apagada
        mensagem(2);
        return;
    }

    int i = 0;

    cad ctrl = NULL;        // Variável de controle que servirá para apagar os registros restantes na lista
    while ((*lista) != NULL) {      // Enquanto não for o final da lista
        ctrl = *lista;          // Ctrl aponta para o próximo registro da lista
        i = ctrl->dados.id;
        *lista = (*lista)->proximo;         // Lista se desloca para o próximo registro
        free(ctrl);         // O registro anterior é apagado
        printf("\tRegistro %d apagado\n", i);       // Apresenta os ids dos registros apagados. Apenas � crit�rio de verifica��o, n�o � poss�vel v�-lo no arquivo .exe
    }
    free(lista);            // A lista � apagada
    printf("Lista apagada\n");          // Escreve na tela que a lista foi apagada. Apenas � crit�rio de verifica��o, n�o � poss�vel v�-lo no arquivo .exe

    return;
}


/// Rotinas de a��o
// Insere o registro de um funcion�rio na lista ligada
int func_inserir(cad *lista, dados novo, int *cod) {
    cad ctrl = NULL;            // Cria uma vari�vel do tipo ponteiro que apontar� para o novo registro
    ctrl = (struct CADASTRO*) malloc(sizeof(struct CADASTRO));          // Aloca o registro na mem�ria
    if (ctrl == NULL) {         // Verifica se a aloca��o foi bem sucedida
        return 4;
    }

    ctrl->dados = *novo;            // Passa os valores do novo contato recebidos pela fun��o para a posi��o na mem�ria
    ctrl->dados.id = ++*cod;            // Define um id �nico para o registro, com base na ordem de cadastro
    ctrl->proximo = NULL;           // Limpa o ponteiro proximo, pois esse ser� o �ltimo registro da lista
    if ((*lista) == NULL) {
        *lista = ctrl;          // Se a lista estiver vazia, define o registro como primeiro item da lista, apontando a ele o cabe�alho da lista ligada
    }
    else {
        cad aux = *lista;           // Cria uma vari�vel auxiliar para avan�ar a lista sem perder suas posi��es
        while (aux->proximo != NULL) {          // Caso a lista j� tenha algum regisro avan�a a lista at� o �ltimo registo
            aux = aux->proximo;
        }
        aux->proximo = ctrl;            // Insere o registro na �ltima posi��o
    }

    return 0;
}

// Realiza uma busca pelo registro de um funcion�rio na lista atrav�s do id
cad func_buscar_id (cad *lista, int *id) {
    cad aux = *lista;           // Vari�vel auxiliar para manipular a lista
    cad pesq = NULL;            // Vari�vel que guardadr� o resultado da pesquisa

    while (aux != NULL) {
        if (aux->dados.id == *id) {         // Procura id correspondente
            pesq = aux;         // Atribui endere�o do correspondente � vari�vel pesq
            return pesq;            // Retorna a correspond�ncia
        }
        aux = aux->proximo;         // Avan�a a lista
    }

    printf("Registro nao encontrado. ");
    return NULL;            // Caso n�o encontrado retorna NULL
}

// Realiza uma busca pelo registro de um funcion�rio na lista atrav�s do nome do funcionario
cad func_buscar_nome (cad *lista, char nome[]) {
    cad aux = *lista;
    cad pesq = NULL;

    while (aux != 0) {
        if (strcmp(aux->dados.nome, nome) == 0) {           // Procura correspond�ncia ao nome
            pesq = aux;
            return pesq;            // Retorna correspond�ncia
        }
        aux = aux->proximo;
    }

    printf("Registro nao encontrado.\n\n\n");
    return NULL;
}

// Fun��o gen�rica para exibi��o de dados dos funcion�rios
void func_exibir(dados func, est lista) {
    int i = 0;
    while (lista->cargo[i].codigo != func->cargo) {         // Procura id correspondente ao codigo do cargo guardado no registro
        i++;
    }

    // Exibi��o dos dados do funcion�rio
    if (func->id != 0) {            // Impede a exibi�ao de valores de id n�o guardados na mem�ria ainda
        printf("\tId......: %d\n", func->id);
    }
    printf("\tNome....: "); fputs(func->nome, stdout);
    printf("\tEndereco: "); fputs(func->endereco, stdout);
    printf("\tIdade...: %d ano", func->idade); (func->idade > 1) ? printf("s\n") : printf("\n");
    printf("\tSalario.: R$ %.2f\n", func->salario);
    printf("\tCargo...: "); fputs(lista->cargo[i].nome, stdout); printf("\n");
    printf("\n");

    return;
}


/// Rotinas de formata��o de texto
// Cria uma linha tracejada para efeitos gr�ficos
void traca_linha() {
    for (int i = 0; i <= tela_tamanho; i++) {
        printf("-");
    }
    printf("\n");

    return;
}

// Centraliza o texto inserido na chamada da fun��o de acordo com o tamanho da tela (80) previamente informado
void centraliza_texto(char texto[]) {
    int lado = (tela_tamanho - strlen(texto))/2;
    for (int i = 0; i <= lado; i++) {
        printf(" ");
    }
    fputs(texto, stdout);
    printf("\n");


    return;
}

// Incorpora recursos das fun��es traca_linha() e centraliza_texto() para a cria��o de um t�tulo grafico padronizado
void titulo(int opcao, char texto[]) {
    if (opcao == 0) {
        traca_linha();
        centraliza_texto(texto);
    }
    else if (opcao == 1) {
        traca_linha();
        centraliza_texto(texto);
        traca_linha();
        printf("\n");
    }

    return;
}

// Esta fun��o apresenta os cargos dispon�veis e retorna o c�digo do cargo selecionado para o funcion�rio
int func_cargo (est lista) {
    int opcao;
    do {
        limpa(), position(1,1);         // Limpa a tela e posiciona cursor na primeira coluna da primeira linha
        titulo(1, "CARGO");         // Exibe o t�tulo

        printf("Escolha um dos cargos a seguir: \n\n\n");

        for (int i = 0; i < 20; i++) {          // Exibe lista de cargos para escolha do usu�rio
            printf("\t[%.2d] ", lista->cargo[i].id);
            fputs(lista->cargo[i].nome, stdout);
            printf("\n");
        }
        printf("\n\nSelecione uma opcao: "); scanf("%d", &opcao); limpa_buffer();

        if (opcao >= 1 && opcao <= 20) {            // Retorna c�digo do cargo escolhido pelo usu�rio
            return lista->cargo[opcao - 1].codigo;
        }
        else {
            printf("\n\nEntre uma opcao valida.");
            limpa_buffer();
        }
    }
    while (!(opcao >= 1 && opcao <= 20));

    return 0;
}



/// Menus
// Fun��o para a inser��o de novos registros na lista ligada
void menu_inserir(cad *lista, int *cod, est lista_est) {
    printf("\n\n");
    limpa(); position(1,1);
    titulo(1, "ADICIONAR FUNCIONARIO");

    struct DADOS novo = {};         // Vari�vel que guardar� os dados do novo funcion�rio antes que seja enviada � lista ligada

    printf("Entre os dados do novo funcionario: \n\n\n");

    novo.id = (*cod + 1);
    printf("\tNome....: "); fgets(novo.nome, sizeof(novo.nome), stdin);
    printf("\tEndereco: "); fgets(novo.endereco, sizeof(novo.endereco), stdin);
    printf("\tIdade...: "); scanf("%d", &novo.idade); limpa_buffer();
    printf("\tSalario.: "); scanf("%f", &novo.salario); limpa_buffer();
    printf("\tCargo...: "); novo.cargo = func_cargo(lista_est);

    // Confirma��o
    printf("\n\n");
    limpa(); position(1,1);
    titulo(1, "ADICIONAR FUNCIONARIO");

    printf("Adicionar funcionario?\n\n\n");
    func_exibir(&novo, lista_est);
    printf("\n[S/N]: ");
    char confirmacao = getchar();
    limpa_buffer();

    if (confirmacao == 's' || confirmacao == 'S' || confirmacao == '1') {
        mensagem(func_inserir(lista, &novo, cod));          // Se confirma��o for positiva, chamaa a fun��o para adicionar o funcion�rio � lista ligada
    }
    else {
        mensagem(6);
    }

    return;
}

// Fun��o para exclus�o de registros da lista ligada
void menu_excluir(cad *lista, est lista_est) {
    if (lista == NULL){         // Verifica se a lista foi criada
        mensagem(2);
        return;
    }
    else if (*lista == NULL){           // Verifica se a lista n�o est� vazia
        mensagem(3);
        return;
    }

    limpa(); position(1,1);
    titulo(1, "EXCLUIR FUNCIONARIO");

    int id;
    printf("Entre o id do funcionario a ser excluido: "); scanf("%d", &id); limpa_buffer();
    printf("\n");

    cad pesquisa = NULL;            // Vari�vel que apontar� para o resultado da pesquisa
    pesquisa = func_buscar_id(lista, &id);          // Chamada da fun��o de pesquisa por id

    if (pesquisa == NULL) {         // Se a fun��o retornar NULL ent�o o registro n�o foi encontrado
        printf("\n\n\nVoltando ao menu principal.");
        limpa_buffer();
        return;
    }

    printf("Excluir funcionario?\n\n\n");
    func_exibir(&(pesquisa->dados), lista_est);         // Exibe registro para confirma��o
    printf("\n[S/N]: ");

    char confirmacao = getchar(); limpa_buffer();            // Rotina de confirma��o
    if (!(confirmacao == 's' || confirmacao == 'S' || confirmacao == '1')) {
        printf("\n\nOperacao abortada. Voltando ao menu principal.");
        limpa_buffer();
        return;
    }

    cad anterior = NULL, aux = NULL;
    aux = *lista;

    while (aux != pesquisa) {           // Avan�a lista para a posi��o da pesquisa guardando uma posi��o anterior
        anterior = aux;
        aux = aux->proximo;
    }
    if (anterior == NULL) {
        *lista = aux->proximo;          // Se a pesquisa retornar o primeiro registro da lista, ent�o o cabe�alho da lista apontar� para o pr�ximo registro
    }
    else {
        anterior->proximo = aux->proximo;           // Caso contr�rio, o registro anterior ao registro a ser apagado apontar� para o pr�ximo registro
    }
    free(aux);          // Libera aloca��o din�mica do registro apagado

    printf("\n\nFuncionario excluido com sucesso. Voltando ao menu principal.");
    limpa_buffer();

    return;
}

// Fun��o para edi��o de registros da lista ligada
void menu_editar(cad *lista, est lista_est) {
    if (lista == NULL){
        mensagem(2);
        return;
    }
    else if (*lista == NULL){
        mensagem(3);
        return;
    }

    limpa(); position(1,1);
    titulo(1, "EDITAR FUNCIONARIO");

    int id;
    printf("Entre o id do funcionario a ser editado: "); scanf("%d", &id); limpa_buffer();
    printf("\n");

    cad pesquisa = NULL;
    pesquisa = func_buscar_id(lista, &id);
    if (pesquisa == NULL) {
        printf("\n\n\nVoltando ao menu principal. ");
        limpa_buffer();
        return;
    }
    printf("\n");
    func_exibir(&(pesquisa->dados), lista_est);         // Para quest�es de compatibilidade com outras fun��es, a rotina de exibi��o s� recebe ponteiros do tipo dados, assim, a fun��o passa apenas o endere�o dos dados do ponteiro pesquisa, e n�o a estrutura inteira
    printf("\nEditar funcionario? [S/N]: ");
    char confirmacao = getchar();
    limpa_buffer();

    if (!(confirmacao == 's' || confirmacao == 'S' || confirmacao == '1')) {
        printf("\n\nOperacao abortada. Voltando ao menu principal. ");
        limpa_buffer();
        return;
    }
    struct DADOS novo = {};         // Vari�vel tempor�ria para guardadar os dados do novo funcion�rio, sem faze-lo diretamente pela lista

    printf("\nEntre os novos dados do funcionario: \n\n\n");

    printf("\tNome....: "); fgets(novo.nome, sizeof(novo.nome), stdin);
    printf("\tEndereco: "); fgets(novo.endereco, sizeof(novo.endereco), stdin);
    printf("\tIdade...: "); scanf("%d", &novo.idade); limpa_buffer();
    printf("\tSalario.: "); scanf("%f", &novo.salario); limpa_buffer();
    printf("\tCargo...: "); novo.cargo = func_cargo(lista_est);
    novo.id = pesquisa->dados.id;

    limpa(); position(1,1);
    titulo(1, "EDITAR FUNCIONARIO");

    printf("Editar contato ?\n\n\n");
    func_exibir(&novo, lista_est);          // Exibi��o do novo funcion�rio para crit�rios de confirma��o
    printf("\n");

    printf("[S/N]: "); confirmacao = getchar(); limpa_buffer();
    if (!(confirmacao == 's' || confirmacao == 'S' || confirmacao == '1')) {
        printf("\n\nOperacao abortada. Voltando ao menu principal. ");
        limpa_buffer();
        return;
    }

    pesquisa->dados = novo;         // Atualiza��o do funcion�rio efetivamente
    printf("\n\nEdicao realizada com sucesso. Voltando ao menu principal.");
    limpa_buffer();

    return;
}

// Sub menu de busca pelo id
void menu_buscar_id(cad *lista, est lista_est) {
    printf("\n\n");
    limpa(); position(1,1);
    titulo(1, "BUSCAR FUNCIONARIO PELO ID");

    int pesq;
    printf("Entre o numero id do funcionario a ser pesquisado: "); scanf("%d", &pesq); limpa_buffer();       // Guarda o id do funcion�rio a ser pesquisado
    printf("\n");

    cad pesquisa = NULL;
    pesquisa = func_buscar_id(lista, &pesq);        // Busca por id

    if(pesquisa != NULL) {
        printf("Registro encontrado:\n\n\n");
        func_exibir(&(pesquisa->dados), lista_est);     // Se o registro for encontrado, exibe o registro
        printf("\n");
    }
    else {
        printf("\n\n\n");
    }

    printf("Voltando para o menu principal.");
    limpa_buffer();
    printf("\n\n\n");

    return;
}

// Sub menu de busca pelo nome
void menu_buscar_nome(cad *lista, est lista_est) {
    printf("\n\n");
    limpa(); position(1,1);
    titulo(1, "BUSCAR FUNCIONARIO PELO NOME");

    char pesq[101];
    printf("Entre o nome do funcionario a ser pesquisado: "); fgets(pesq, sizeof(pesq), stdin);     // Guarda o nome do funcion�rio a ser pesquisado
    printf("\n");

    cad pesquisa;
    pesquisa = func_buscar_nome(lista, pesq);

    if(pesquisa != NULL) {
        printf("Registro encontrado:\n\n\n");
        func_exibir(&(pesquisa->dados), lista_est);     // Se o registro for encontrado, exibe o registro
        printf("\n");
    }

    printf("Voltando para o menu principal.");
    limpa_buffer();
    printf("\n\n\n");

    return;
}

// Menu geral de busca de registros
void menu_buscar(cad *lista, est lista_est) {
    if (lista == NULL){
        mensagem(2);
        return;
    }
    else if (*lista == NULL){
        mensagem(3);
        return;
    }


    int opcao;
    printf("\n\n");
    limpa(); position(1,1);
    do {
        titulo(1, "BUSCAR FUNCIONARIO");

        centraliza_texto("[1] BUSCAR FUNCIONARIO PELO ID  ");
        centraliza_texto("[2] BUSCAR FUNCIONARIO PELO NOME");
        centraliza_texto("[0] RETORNAR AO MENU PRINCIPAL  ");
        printf("\n\n");

        printf("Selecione uma opcao: "); scanf("%d", &opcao); limpa_buffer();

        switch (opcao) {
            case 0: printf("\n\n");                         break;
            case 1: menu_buscar_id(lista, lista_est);       break;      // Passa lista ligada e lista estática para consulta
            case 2: menu_buscar_nome(lista, lista_est);     break;      // Passa lista ligada e lista estática para consulta
            default: mensagem(1);                           break;
        }
    }
    while (opcao < 0 || opcao > 2);

    if (opcao == 0) {
        printf("Operacao abortada. Voltando ao menu principal.");
        limpa_buffer();
    }

    return;
}

// Sub menu de exibi��o pelo id
void menu_exibir_id(cad *lista, est lista_est) {        // Exibe todos os registros ordenados por id, a ordena��o padr�o
    printf("\n\n");
    limpa(); position(1,1);
    titulo(1, "EXIBIR FUNCIONARIOS PELO ID");

    cad aux = *lista;
    do {
        func_exibir(&(aux->dados), lista_est);
        aux = aux->proximo;
    }
    while (aux != NULL);
    printf("\n");

    return;
}

// Sub menu de exibi��o pelo sal�rio
void menu_exibir_salario(cad *lista, int *cod, est lista_est) {     // Exibe funcion�rios com sal�rios numa faixa previamente informada em ordem crescente
    printf("\n\n");
    limpa(); position(1,1);
    titulo(1, "EXIBIR FUNCIONARIOS POR FAIXA SALARIAL");

    float minimo, maximo;

    printf("Valor minimo: "); scanf("%f", &minimo); limpa_buffer();      // Entra valor m�nimo
    printf("Valor maximo: "); scanf("%f", &maximo); limpa_buffer();      // Entra valor m�ximo
    printf("\n\n");

    cad aux = *lista;
    int i = 0;
    int j = 0;
    int k = 0;

    struct DADOS pesquisa[(*cod) + 1];      // Cria um vetor do tipo DADOS para guardar os ponteiros dos registros correspondentes � pesquisa e, posteriormente, pemite a ordena��o dos mesmos
    // *cod � a vari�vel utilizada para atribuir valores �nicos na lista, utilizando-o aqui garante-se que o vetor ser� do tamanho da lista inteira
    struct DADOS x;         // Vari�vel de controle para odena��o dos ponteiros

    while (aux != NULL) {       // Percorre a lista
        if (aux->dados.salario >= minimo && aux->dados.salario <= maximo) {     // Verifica se cada um do elementos da lista corresponde � pesquisa
            pesquisa[i++] = aux->dados;     // Se for encontrado correspondente, o mesmo � guardado na pr�xima posi��o dispon�vel do vetor
            k++;        // Guarda o n�mero de correspond�ncias � pesquisa
        }
        aux = aux->proximo;     // Itera a posi��o na lista
    }

    if (k == 0) {       // Se k for igual a 0 ent�o nenhum registro correspondeu � pesquisa
        printf("Nenhum registro corresponde a pesquisa. ");
        return;
    }

    // Rotina que realiza a ordena��o dos registros por sal�rio de forma crescente, usando a vari�vel x com auxiliar para realizar a troca
    // Se dois ou mair registros tiverem o mesmo sal�rio, os mesmos ser�o ordenados pelo id
    for (i = 0; i < k; i++) {
        for (j = i + 1; j < k; j++) {
            if (pesquisa[j].salario < pesquisa[i].salario) {
                x = pesquisa[i];
                pesquisa[i] = pesquisa[j];
                pesquisa[j] = x;
            }
            else if (pesquisa[j].salario == pesquisa[i].salario) {
                if (pesquisa[j].id < pesquisa[i].id) {
                    x = pesquisa[i];
                    pesquisa[i] = pesquisa[j];
                    pesquisa[j] = x;
                }
            }
        }
    }

    // Exibe o vetor ordenado
    for (i = 0; i < k; i++) {
        func_exibir(&pesquisa[i], lista_est);
    }
    printf("\n");

    return;
}

// Menu geral de exibi��o
void menu_exibir(cad *lista, int *cod, est lista_est) {     // Este menu cont�m uma rotina simples para escolha do usu�rio se quer pesquisar funcion�rios pelo id ou por faixa salarial
    if (lista == NULL){
        mensagem(2);
        return;
    }
    else if (*lista == NULL){
        mensagem(3);
        return;
    }

    printf("\n\n");
    int opcao;
    do {
        limpa(); position(1,1);
        titulo(1, "EXIBIR FUNCIONARIOS");

        centraliza_texto("[1]\tEXIBIR FUNCIONARIOS PELO ID           ");
        centraliza_texto("[2]\tEXIBIR FUNCIONARIOS POR FAIXA SALARIAL");
        centraliza_texto("[0]\tVOLTAR AO MENU PRINCIPAL              ");

        printf("\n\nSelecione uma opcao: ");
        scanf("%d", &opcao); limpa_buffer();

        switch (opcao) {
            case 0: printf("\n\n");                             break;
            case 1: menu_exibir_id(lista, lista_est);           break;
            case 2: menu_exibir_salario(lista, cod, lista_est); break;
            default: mensagem(1);                               break;
        }
    }
    while (opcao < 0 || opcao > 2);
    printf("Voltando ao menu principal.");
    limpa_buffer();
    printf("\n\n");

    return;
}

// Parte gr�fica do menu em main.c
void menu() {
    titulo(1, "MENU");

    centraliza_texto("[1]\tADICIONAR FUNCIONARIO");
    centraliza_texto("[2]\tEXCLUIR FUNCIONARIO  ");
    centraliza_texto("[3]\tEDITAR FUNCIONARIO   ");
    centraliza_texto("[4]\tBUSCAR FUNCIONARIO   ");
    centraliza_texto("[5]\tEXIBIR FUNCIONARIOS  ");
    centraliza_texto("[0]\tFECHAR PROGRAMA      ");

    printf("\n\nSelecione uma opcao: ");

    return;
}
