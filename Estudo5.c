#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// VICENTE DOS SANTOS SILVA && VICTOR SAMUEL DOS SANTOS
// Este código corresponde ao programa 1 do Estudo Dirigido 5

typedef struct no
{
    int save;
    int matricula;
    char nome[64];
    float nota;
    float frequencia;
    char turma;

    struct no *proximo;
} No;

typedef struct
{
    No *inicio;
    No *fim;
} Lista;

Lista *cria_lista()
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));

    if (lista == NULL)
    {
        printf("\nMemoria insuficiente!\n");
        exit(1);
    }

    lista->inicio = NULL;
    lista->fim = NULL;

    return lista;
}

int get_size(const char *file_name)
{
    FILE *file = fopen(file_name, "r");

    if (file == NULL)
        return 0;

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    return size;
}

void insere_lista_fim(Lista *lista, char nome[], float nota, float freq, char turma, int mat, int save)
{
    No *node = (No *)malloc(sizeof(No));
    if (node == NULL)
    {
        printf("\nErro ao alocar memória para o nó da lista\n");
        exit(1);
    }

    node->save = save;
    node->matricula = mat;
    strcpy(node->nome, nome);
    node->nota = nota;
    node->frequencia = freq;
    node->turma = turma;

    node->proximo = NULL;

    if (lista->inicio == NULL)
    {
        lista->inicio = node;
        lista->fim = node;
    }
    else
    {
        lista->fim->proximo = node;
        lista->fim = node;
    }
}

int preenche_lista(Lista *lista)
{
    FILE *file = fopen("arquivo.txt", "a+");

    if (file == NULL)
    {
        return 0;
    }

    char name[64], turma;
    float nota;
    int mat, save, tam_str;
    float freq;

    while (!feof(file))
    {

        fscanf(file, "%d ", &save);
        fscanf(file, "%d ", &mat);
        fscanf(file, "%63[^\n] ", name);
        fscanf(file, "%f ", &nota);
        fscanf(file, "%f ", &freq);
        fscanf(file, "%c ", &turma);

        if (save != 0)
        {
            insere_lista_fim(lista, name, nota, freq, turma, mat, save);
        }
    }

    fclose(file);

    return 1;
}

void verificarAluno(Lista *lista, int mat, int *verif)
{
    No *node;

    for (node = lista->inicio; node != NULL; node = node->proximo)
    {
        if (node->matricula != mat)
        {
            continue;
        }

        if (node->matricula == mat)
        {
            *verif = 0;
        }
    }
}

void gravarDados(Lista *lista)
{
    FILE *file = fopen("arquivo.txt", "w");

    No *node;
    int instante;
    No *aux = (No *)malloc(sizeof(No));

    for (node = lista->inicio; node != NULL; node = node->proximo)
    {
        while (1)
        {
            instante = ftell(file);

            if (!feof(file))
            {
                fscanf(file, "%d ", &aux->save);
                fscanf(file, "%d ", &aux->matricula);
                fscanf(file, "%63[^\n] ", aux->nome);
                fscanf(file, "%f ", &aux->nota);
                fscanf(file, "%f ", &aux->frequencia);
                fscanf(file, "%c ", &aux->turma);
            }

            if (node->matricula != aux->matricula)
            {
                if (aux->save == 0)
                {
                    fseek(file, instante, SEEK_SET);

                    fprintf(file, "%d\n", node->save);
                    fprintf(file, "%d\n", node->matricula);
                    fwrite(node->nome, 1, strlen(node->nome), file);

                    if (node->nota == 10)
                    {
                        fprintf(file, "\n%.4f\n", node->nota);
                    }

                    if (node->nota < 10)
                    {
                        fprintf(file, "\n%.5f\n", node->nota);
                    }

                    if (node->frequencia == 100)
                    {
                        fprintf(file, "%.4f\n", node->frequencia);
                    }

                    if (node->frequencia < 100 && node->frequencia >= 10)
                    {
                        fprintf(file, "%.5f\n", node->frequencia);
                    }

                    if (node->frequencia < 10)
                    {
                        fprintf(file, "%.6f\n", node->frequencia);
                    }

                    fprintf(file, "%c\n", node->turma);

                    break;
                }

                if (feof(file))
                {
                    fseek(file, 0, SEEK_END);

                    fprintf(file, "%d\n", node->save);
                    fprintf(file, "%d\n", node->matricula);
                    fwrite(node->nome, 1, strlen(node->nome), file);

                    if (node->nota == 10)
                    {
                        fprintf(file, "\n%.4f\n", node->nota);
                    }

                    if (node->nota < 10)
                    {
                        fprintf(file, "\n%.5f\n", node->nota);
                    }

                    if (node->frequencia == 100)
                    {
                        fprintf(file, "%.4f\n", node->frequencia);
                    }

                    if (node->frequencia < 100 && node->frequencia >= 10)
                    {
                        fprintf(file, "%.5f\n", node->frequencia);
                    }

                    if (node->frequencia < 10)
                    {
                        fprintf(file, "%.6f\n", node->frequencia);
                    }

                    fprintf(file, "%c\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", node->turma);

                    break;
                }
            }
        }
        fclose(file);
    }
}

void insereAluno(Lista *lista, int mat, char name[], float note, float freq, char class)
{
    if (lista == NULL)
        return;

    No *novo = (No *)malloc(sizeof(No));

    if (lista->inicio == NULL)
    {
        lista->fim = novo;
    }

    if (novo)
    {
        novo->save = 1;
        strcpy(novo->nome, name);
        novo->nota = note;
        novo->matricula = mat;
        novo->frequencia = freq;
        novo->turma = class;

        novo->proximo = lista->inicio;
        lista->inicio = novo;
    }
    else
    {
        printf("Erro ao alocar memória!!");
        exit(1);
    }
}

void save_to_archive(Lista *lista)
{
    FILE *file = fopen("arquivo.txt", "r+");
    int instante, r, tam_str;
    No *node;
    No *aux = (No *)malloc(sizeof(No));

    node = lista->inicio;

    while (1)
    {
        instante = ftell(file);

        if (!feof(file))
        {
            fscanf(file, "%d ", &aux->save);
            fscanf(file, "%d ", &aux->matricula);
            fscanf(file, "%63[^\n] ", aux->nome);
            fscanf(file, "%f ", &aux->nota);
            fscanf(file, "%f ", &aux->frequencia);
            fscanf(file, "%c ", &aux->turma);
        }

        if (aux->save == 0)
        {
            fseek(file, instante, SEEK_SET);

            fprintf(file, "%d\n", node->save);
            fprintf(file, "%d\n", node->matricula);
            fwrite(node->nome, 1, strlen(node->nome), file);

            if (node->nota == 10)
            {
                fprintf(file, "\n%.4f\n", node->nota);
            }

            if (node->nota < 10)
            {
                fprintf(file, "\n%.5f\n", node->nota);
            }

            if (node->frequencia == 100)
            {
                fprintf(file, "%.4f\n", node->frequencia);
            }

            if (node->frequencia < 100 && node->frequencia >= 10)
            {
                fprintf(file, "%.5f\n", node->frequencia);
            }

            if (node->frequencia < 10)
            {
                fprintf(file, "%.6f\n", node->frequencia);
            }

            fprintf(file, "%c\n", node->turma);

            break;
        }

        if (feof(file))
        {
            fseek(file, 0, SEEK_END);

            fprintf(file, "%d\n", node->save);
            fprintf(file, "%d\n", node->matricula);
            fwrite(node->nome, 1, strlen(node->nome), file);

            if (node->nota == 10)
            {
                fprintf(file, "\n%.4f\n", node->nota);
            }

            if (node->nota < 10)
            {
                fprintf(file, "\n%.5f\n", node->nota);
            }

            if (node->frequencia == 100)
            {
                fprintf(file, "%.4f\n", node->frequencia);
            }

            if (node->frequencia < 100 && node->frequencia >= 10)
            {
                fprintf(file, "%.5f\n", node->frequencia);
            }

            if (node->frequencia < 10)
            {
                fprintf(file, "%.6f\n", node->frequencia);
            }

            fprintf(file, "%c\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", node->turma);

            break;
        }
    }
    fclose(file);
}

void destroi_lista(Lista *lista)
{
    if (lista == NULL)
        return;

    if (lista->inicio == NULL)
        return;

    No *node;

    while (lista->inicio != NULL)
    {
        node = lista->inicio;
        lista->inicio = node->proximo;
        free(node);
    }

    free(lista);
}

void imprime(Lista *lista)
{

    if (lista == NULL)
    {

        printf("lista nao criada!\n");
        return;
    }

    if (lista->inicio == NULL)
    {
        printf("lista vazia!\n");
        return;
    }

    No *novo;

    for (novo = lista->inicio; novo != NULL; novo = novo->proximo)
    {
        printf("\nNome: %s\n", novo->nome);
        printf("Nota: %.2f\n", novo->nota);
        printf("Matricula: %d\n", novo->matricula);
        printf("Frequencia: %.2f\n", novo->frequencia);
        printf("Turma: %c\n", novo->turma);

        if (novo->proximo == NULL)
        {
            printf("\nExibicao completa!\n");
        }
        else
        {
            printf("\n");
        }
    }
}

int remove_lista(Lista *lista, int mat)
{
    if (lista == NULL)
        return 0;

    if (lista->inicio == NULL)
        return 0;

    No *before, *after;
    FILE *arq = fopen("arquivo.txt", "r+");
    No *auxiliar = (No *)malloc(sizeof(No));
    int instante;

    for (after = lista->inicio; after != NULL; before = after, after = after->proximo)
    {
        if (after->matricula == mat)
        {
            if (lista->inicio == lista->fim)
            {
                lista->inicio = NULL;
                lista->fim = NULL;
            }

            else
            {
                if (after == lista->inicio)
                {
                    lista->inicio = after->proximo;
                }

                else if (after == lista->fim)
                {
                    lista->fim = before;
                    before->proximo = NULL;
                }

                else
                {
                    before->proximo = after->proximo;
                }
            }

            if (after->save == 1)
            {
                int r;

                while (!feof(arq))
                {
                    instante = ftell(arq);

                    fscanf(arq, "%d ", &auxiliar->save);
                    fscanf(arq, "%d ", &auxiliar->matricula);
                    fscanf(arq, "%127[^\n] ", auxiliar->nome);
                    fscanf(arq, "%f ", &auxiliar->nota);
                    fscanf(arq, "%f ", &auxiliar->frequencia);
                    fscanf(arq, "%c ", &auxiliar->turma);

                    if (after->matricula == auxiliar->matricula)
                    {
                        auxiliar->save = 0;
                        fseek(arq, instante, SEEK_SET);

                        fprintf(arq, "%d\n", auxiliar->save);
                        fprintf(arq, "%d\n", auxiliar->matricula);
                        fwrite(auxiliar->nome, 1, strlen(auxiliar->nome), arq);

                        if (auxiliar->nota == 10)
                        {
                            fprintf(arq, "\n%.4f\n", auxiliar->nota);
                        }

                        if (auxiliar->nota < 10)
                        {
                            fprintf(arq, "\n%.5f\n", auxiliar->nota);
                        }

                        if (auxiliar->frequencia == 100)
                        {
                            fprintf(arq, "%.4f\n", auxiliar->frequencia);
                        }

                        if (auxiliar->frequencia < 100 && auxiliar->frequencia >= 10)
                        {
                            fprintf(arq, "%.5f\n", auxiliar->frequencia);
                        }

                        if (auxiliar->frequencia < 10)
                        {
                            fprintf(arq, "%.6f\n", auxiliar->frequencia);
                        }

                        if (feof(arq))
                        {
                            fprintf(arq, "%c\n", auxiliar->turma);
                        }

                        else
                        {
                            fprintf(arq, "%c", auxiliar->turma);
                        }

                        break;
                    }
                }

                fclose(arq);
            }

            free(after);
            free(auxiliar);

            return 1;
        }
    }

    return 0;
}

int ordenaNome(Lista *lista)
{
    if (lista == NULL)
        return 0;

    if (lista->inicio == NULL)
        return 3;

    if (lista->inicio == lista->fim)
    {
        return 2;
    }

    No *aux = (No *)malloc(sizeof(No));
    No *pi, *pj;

    for (pi = lista->inicio; pi != NULL; pi = pi->proximo)
    {
        for (pj = lista->inicio; pj != NULL; pj = pj->proximo)
        {
            if (strcmp(pi->nome, pj->nome) < 0)
            {
                strcpy(aux->nome, pj->nome);
                strcpy(pj->nome, pi->nome);
                strcpy(pi->nome, aux->nome);

                aux->matricula = pj->matricula;
                pj->matricula = pi->matricula;
                pi->matricula = aux->matricula;

                aux->frequencia = pj->frequencia;
                pj->frequencia = pi->frequencia;
                pi->frequencia = aux->frequencia;

                aux->nota = pj->nota;
                pj->nota = pi->nota;
                pi->nota = aux->nota;

                aux->turma = pj->turma;
                pj->turma = pi->turma;
                pi->turma = aux->turma;
            }
        }
    }
    free(aux);
    return 1;
}

int mostrar_por_nota(Lista *lista)
{

    if (lista == NULL)
        return 0;

    if (lista->inicio == NULL)
        return 4;

    if (lista->inicio == lista->fim)
    {
        return 2;
    }

    float menor_val = 999.0, maior_val = 0.0;

    No *node;

    for (node = lista->inicio; node != NULL; node = node->proximo)
    {
        if (node->nota > maior_val)
        {
            maior_val = node->nota;
        }
        if (node->nota < menor_val)
        {
            menor_val = node->nota;
        }
    }

    if (menor_val == maior_val)
    {
        return 3;
    }

    printf("Alunos com a maior nota:\n");

    for (node = lista->inicio; node != NULL; node = node->proximo)
    {
        if (node->nota == maior_val)
        {
            printf("\nNome: %s\n", node->nome);
            printf("Nota: %.2f\n", node->nota);
            printf("Matricula: %d\n", node->matricula);
            printf("Frequencia: %.2f\n", node->frequencia);
            printf("Turma: %c\n", node->turma);
        }
    }
    printf("\nAlunos com a menor nota:\n");

    for (node = lista->inicio; node != NULL; node = node->proximo)
    {
        if (node->nota == menor_val)
        {
            printf("\nNome: %s\n", node->nome);
            printf("Nota: %.2f\n", node->nota);
            printf("Matricula: %d\n", node->matricula);
            printf("Frequencia: %.2f\n", node->frequencia);
            printf("Turma: %c\n", node->turma);
        }
    }

    return 1;
}

int pesquisar_por_nome(Lista *lista, char name[])
{

    if (lista == NULL)
        return 0;

    if (lista->inicio == NULL)
        return 0;

    No *node;

    for (node = lista->inicio; node != NULL; node = node->proximo)
    {

        if (strcmp(node->nome, name) == 0)
        {
            printf("\nAluno encontrado!\n\n");
            printf("Nome: %s\n", node->nome);
            printf("Nota: %.2f\n", node->nota);
            printf("Matricula: %d\n", node->matricula);
            printf("Frequencia: %.2f\n", node->frequencia);
            printf("Turma: %c\n\n", node->turma);
            system("pause");

            return 1;
        }
    }
    return 0;
}

int pesquisar_por_matricula(Lista *lista, int mat)
{

    if (lista == NULL)
        return 0;

    if (lista->inicio == NULL)
        return 0;

    No *node;

    for (node = lista->inicio; node != NULL; node = node->proximo)
    {

        if (node->matricula == mat)
        {
            printf("\nAluno encontrado!\n\n");
            printf("Nome: %s\n", node->nome);
            printf("Nota: %.2f\n", node->nota);
            printf("Matricula: %d\n", node->matricula);
            printf("Frequencia: %.2f\n", node->frequencia);
            printf("Turma: %c\n\n", node->turma);
            system("pause");

            return 1;
        }
    }
    return 0;
}

int pesquisar_por_turma(Lista *lista, char turma)
{

    if (lista == NULL)
        return 0;

    if (lista->inicio == NULL)
        return 2;

    int conf = 0;

    No *node;

    if (turma != 'A' && turma != 'B')
    {
        return 3;
    }

    for (node = lista->inicio; node != NULL; node = node->proximo)
    {
        if (node->turma == turma)
        {
            printf("\nNome: %s\n", node->nome);
            printf("Nota: %.2f\n", node->nota);
            printf("Matricula: %d\n", node->matricula);
            printf("Frequencia: %.2f\n", node->frequencia);
            printf("Turma: %c\n", node->turma);
            conf = 1;
        }
        if (node->proximo == NULL && conf == 1)
        {
            printf("\n");
            system("pause");
            return 1;
        }
    }

    return 4;
}

int main()
{

    int menu = 0, i = -1, aux_mat, contador = 0, bolean_nota, remove, res1, res2, verif = 0, conf_tur = 0;
    float aux_nota, aux_freq;
    char aux_name[64], aux_turma;
    int achei, src, error;
    char confirm;

    // criando a lista
    Lista *lista = cria_lista();

    FILE *file;
    file = fopen("arquivo.txt", "a+");

    if (file == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        system("pause");
        exit(1);
    }

    if (get_size("arquivo.txt") != 0)
    {
        error = preenche_lista(lista);
        if (error == 0)
        {
            printf("Ocorreu um erro ao preencher a lista com os dados anteriores!");
            exit(1);
        }
    }

    while (menu != 9)
    {

        system("cls");
        printf("\n-------------------");
        printf("\nMenu");
        printf("\n-------------------");
        printf("\n1 - Cadastrar aluno");
        printf("\n2 - Remover aluno");
        printf("\n3 - Pesquisar aluno por nome");
        printf("\n4 - Pesquisar aluno por matricula");
        printf("\n5 - Mostrar todos os alunos de uma turma");
        printf("\n6 - Ordenar toda a lista de alunos pelo nome");
        printf("\n7 - Mostrar os alunos com a maior e menor nota");
        printf("\n8 - Gravar Dados");
        printf("\n9 - Sair");
        printf("\nQual opcao desejas seguir? R:");
        scanf("%d", &menu);
        system("cls");

        /*Cadastrar Aluno*/

        if (menu == 1)
        {
            printf("\nCadastro do Aluno\n\n");

            setbuf(stdin, NULL);
            printf("Digite o nome do aluno: ");
            gets(aux_name);

            bolean_nota = 0;

            while (bolean_nota == 0)
            {
                printf("\nDigite a nota do aluno: ");
                scanf("%f", &aux_nota); // aqui ele deve alocar no Nó da lista

                if (aux_nota < 0 || aux_nota > 10)
                {
                    printf("\n----------------------------------------------------");
                    printf("\n NOTA INVALIDA, DIGITE NOVAMENTE");
                    printf("\n----------------------------------------------------\n");
                }
                else
                {
                    bolean_nota = 1;
                }
            }

            printf("\nDigite a frequencia (em porcentagem): ");
            scanf("%f", &aux_freq);

            for (int conf = 0; conf != 1; conf = conf)
            {
                if (aux_freq < 0 || aux_freq > 100)
                {
                    printf("\n----------------------------------------------------");
                    printf("\n VALOR INVALIDO");
                    printf("\n----------------------------------------------------\n");
                    printf("\nDigite outro valor para frequencia(entre 0 e 100) : ");
                    scanf("%f", &aux_freq);
                }
                else
                {
                    conf = 1;
                }
            }

            setbuf(stdin, NULL);
            printf("\nDigite a turma do aluno ( A ou B): ");
            scanf("%c", &aux_turma);

            if (aux_turma == 'A' || aux_turma == 'B')
            {
                conf_tur = 0;
            }
            if (aux_turma != 'A' && aux_turma != 'B')
            {
                conf_tur = 1;
            }

            while (conf_tur == 1)
            {
                printf("\n----------------------------------------------------");
                printf("\n TURMA INVALIDA!");
                printf("\n----------------------------------------------------\n");
                setbuf(stdin, NULL);
                printf("\nDigite a turma do aluno ( A ou B) : ");
                scanf("%c", &aux_turma);

                if (aux_turma == 'A' || aux_turma == 'B')
                {
                    conf_tur = 0;
                }
                if (aux_turma != 'A' && aux_turma != 'B')
                {
                    conf_tur = 1;
                }
            }

            while (verif == 0)
            {
                verif = 1;
                printf("\nDigite a matricula do aluno (entre 0 e 99999): ");
                scanf("%d", &aux_mat);
                if (aux_mat > 0 && aux_mat < 99999)
                {
                    verificarAluno(lista, aux_mat, &verif);

                    if (verif == 0)
                    {
                        printf("\n----------------------------------------------------");
                        printf("\n MATRICULA INVALIDA!");
                        printf("\n----------------------------------------------------\n");
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    printf("\n-------------------------------------------------------------------------");
                    printf("\n ESSE NUMERO DE MATRICULA E INVALIDO. INSIRA A MATRICULA NOVAMENTE");
                    printf("\n-------------------------------------------------------------------------\n");
                    verif = 0;
                }
            }

            verif = 0;
            contador++;

            insereAluno(lista, aux_mat, aux_name, aux_nota, aux_freq, aux_turma);

            printf("\nDeseja cadastrar este aluno no arquivo? (S/N) : ");
            setbuf(stdin, NULL);
            scanf("%c", &confirm);

            while (confirm != 'S' && confirm != 's' && confirm != 'N' && confirm != 'n')
            {
                printf("\n\nPor favor, digite um valor valido (S/N) : ");
                setbuf(stdin, NULL);
                scanf("%c", &confirm);
            }

            if (confirm == 'S' || confirm == 's')
            {
                save_to_archive(lista);
            }

            printf("\n\nCadastro Realizado com Sucesso!\n");
            system("pause");
        }

        if (menu == 2)
        {
            achei = 0;
            printf("\nRemover Aluno\n\n");

            printf("Digite a matricula do aluno que voce deseja excluir : ");
            scanf("%d", &remove);

            achei = remove_lista(lista, remove);

            if (achei == 1)
            {
                printf("\n----------------------------------------------------");
                printf("\nAluno removido com sucesso!");
                printf("\n----------------------------------------------------\n");
                contador--;
                system("pause");
            }
            else
            {
                printf("\n----------------------------------------------------");
                printf("\nNao foi possivel fazer a remocao, aluno nao encontrado!");
                printf("\n----------------------------------------------------\n");
                system("pause");
            }
        }

        if (menu == 3)
        {
            printf("\nPesquisar Aluno por Nome\n\n");

            printf("Digite o Nome do Aluno que deseja encontrar: ");
            setbuf(stdin, NULL);
            gets(aux_name);

            src = pesquisar_por_nome(lista, aux_name);

            if (src == 0)
            {
                printf("\n----------------------------------------------------");
                printf("\nO NOME INSERIDO NAO ESTA CADASTRADO");
                printf("\n----------------------------------------------------\n");
                system("pause");
            }
        }

        if (menu == 4)
        {

            printf("\nPesquisar Aluno por Matricula\n\n");

            printf("Digite a Matricula do Aluno que deseja encontrar: ");
            scanf("%d", &aux_mat);

            src = pesquisar_por_matricula(lista, aux_mat);

            if (src == 0)
            {
                printf("\n----------------------------------------------------");
                printf("\nA MATRICULA INSERIDA NAO ESTA CADASTRADA");
                printf("\n----------------------------------------------------\n");
                system("pause");
            }
        }

        if (menu == 5)
        {

            printf("\nMostrar todos os alunos de uma turma\n\n");

            printf("Digite a Turma ( A ou B): ");
            setbuf(stdin, NULL);
            scanf("%c", &aux_turma);

            src = pesquisar_por_turma(lista, aux_turma);

            if (src == 0)
            {
                printf("\n----------------------------------------------------");
                printf("\nA LISTA NAO FOI CRIADA");
                printf("\n----------------------------------------------------\n");
                system("pause");
            }
            if (src == 2)
            {
                printf("\n----------------------------------------------------");
                printf("\nA LISTA ESTA VAZIA");
                printf("\n----------------------------------------------------\n");
                system("pause");
            }
            if (src == 3)
            {
                printf("\n----------------------------------------------------");
                printf("\nA TURMA INSERIDA NAO EXISTE");
                printf("\n----------------------------------------------------\n");
                system("pause");
            }
            if (src == 4)
            {
                printf("\n----------------------------------------------------");
                printf("\nA TURMA INSERIDA NAO POSUI ALUNOS MATRICULADOS");
                printf("\n----------------------------------------------------\n");
                system("pause");
            }
        }

        if (menu == 6)
        {
            printf("\nOrdenar toda a lista de alunos pelo nome\n");

            src = ordenaNome(lista);

            if (src == 0)
            {
                printf("----------------------------------------------------");
                printf("\nOCORREU UM ERRO AO CRIAR A LISTA");
                printf("\n----------------------------------------------------\n");
            }

            if (src == 2)
            {
                printf("----------------------------------------------------");
                printf("\nNO MOMENTO SO HA UM ALUNO CADASTRADO.\nENTAO NAO EH POSSIVEL USAR ESTA OPCAO");
                printf("\n----------------------------------------------------\n\n");
            }

            if (src == 3)
            {
                printf("----------------------------------------------------");
                printf("\nA LISTA ESTA VAZIA");
                printf("\n----------------------------------------------------\n\n");
            }

            if (src == 1)
            {
                imprime(lista);
            }

            system("pause");
        }

        if (menu == 7)
        {
            printf("\nMostrar os alunos com a maior e menor nota\n");

            src = mostrar_por_nota(lista);

            printf("\n");

            if (src == 0)
            {
                printf("----------------------------------------------------");
                printf("\nOCORREU UM ERRO AO CRIAR A LISTA");
                printf("\n----------------------------------------------------\n");
            }

            if (src == 2)
            {
                printf("----------------------------------------------------");
                printf("\nNO MOMENTO SO HA UM ALUNO CADASTRADO.\nENTAO NAO EH POSSIVEL USAR ESTA OPCAO");
                printf("\n----------------------------------------------------\n\n");
            }

            if (src == 3)
            {
                printf("----------------------------------------------------");
                printf("\nTODOS OS ALUNOS CADASTRADOS POSSUEM A MESMA NOTA.\nLOGO NAO EH POSSIVEL CLASSIFICA-LOS");
                printf("\n----------------------------------------------------\n\n");
            }

            if (src == 4)
            {
                printf("----------------------------------------------------");
                printf("\nA LISTA ESTA VAZIA");
                printf("\n----------------------------------------------------\n\n");
            }

            system("pause");
        }

        if (menu == 8)
        {
            char resposta;
            printf("\nGravar dados no arquivo\n");

            printf("\nTem certeza que deseja gravar os dados atuais? (S/N): ");
            setbuf(stdin, NULL);
            scanf("%c", &resposta);
            printf("\n");

            while (resposta != 'S' && resposta != 's' && resposta != 'N' && resposta != 'n')
            {
                printf("Por favor, insira um valor valido (S/N): ");
                setbuf(stdin, NULL);
                scanf("%c", &resposta);
                printf("\n");
            }

            if (resposta == 'S' || resposta == 's')
            {
                gravarDados(lista);
                printf("Os dados foram gravados com sucesso no arquivo!\nRetornando ao menu. . .\n");
                system("pause");
            }

            if (resposta == 'N' || resposta == 'n')
            {
                printf("Nenhuma tarefa foi executada!\nRetornando ao menu. . .\n");
                system("pause");
            }
        }

        if (menu > 9 || menu < 1)
        {
            printf("Digite um valor valido!!\n");
            system("pause");
        }
    }

    fclose(file);
    destroi_lista(lista);
    printf("\nPrograma Finalizado!\nTenha um Bom dia!");

    return 0;
}