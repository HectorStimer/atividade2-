#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Disciplina {
    char nome[50];
    char codigo[10];
    struct Disciplina *prox;
} Disciplina;


typedef struct Aluno {
    char nome[50];
    int matricula;
    Disciplina *disciplinas; 
    struct Aluno *prox;
} Aluno;


Aluno* criarAluno(char *nome, int matricula) {
    Aluno *novo = (Aluno*)malloc(sizeof(Aluno));
    strcpy(novo->nome, nome);
    novo->matricula = matricula;
    novo->disciplinas = NULL;
    novo->prox = NULL;
    return novo;
}


void adicionarDisciplina(Aluno *aluno, char *nomeDisciplina, char *codigo) {
    Disciplina *nova = (Disciplina*)malloc(sizeof(Disciplina));
    strcpy(nova->nome, nomeDisciplina);
    strcpy(nova->codigo, codigo);
    nova->prox = aluno->disciplinas;
    aluno->disciplinas = nova;
}


void imprimirDisciplinas(Disciplina *disciplina) {
    while (disciplina != NULL) {
        printf("  Disciplina: %s (Código: %s)\n", disciplina->nome, disciplina->codigo);
        disciplina = disciplina->prox;
    }
}


void imprimirAluno(Aluno *aluno) {
    printf("Nome: %s\n", aluno->nome);
    printf("Matrícula: %d\n", aluno->matricula);
    printf("Disciplinas:\n");
    imprimirDisciplinas(aluno->disciplinas);
}


void buscarPorDisciplina(Aluno *lista, char *nomeDisciplina) {
    Aluno *atual = lista;
    int encontrou = 0;
    while (atual != NULL) {
        Disciplina *disciplina = atual->disciplinas;
        while (disciplina != NULL) {
            if (strcmp(disciplina->nome, nomeDisciplina) == 0) {
                imprimirAluno(atual);
                encontrou = 1;
                break;
            }
            disciplina = disciplina->prox;
        }
        atual = atual->prox;
    }
    if (!encontrou) {
        printf("Nenhum aluno encontrado na disciplina %s.\n", nomeDisciplina);
    }
}

void imprimirTodosAlunos(Aluno *lista) {
    Aluno *atual = lista;
    while (atual != NULL) {
        imprimirAluno(atual);
        printf("\n");
        atual = atual->prox;
    }
}

int main() {
    Aluno *listaAlunos = NULL;

  
    Aluno *aluno1 = criarAluno("João Silva", 12345);
    adicionarDisciplina(aluno1, "Cálculo", "MAT101");
    adicionarDisciplina(aluno1, "Física", "FIS102");

    Aluno *aluno2 = criarAluno("Maria Oliveira", 67890);
    adicionarDisciplina(aluno2, "Cálculo", "MAT101");
    adicionarDisciplina(aluno2, "Química", "QUI103");

    aluno1->prox = aluno2;
    listaAlunos = aluno1;

    printf("Todos os alunos:\n");
    imprimirTodosAlunos(listaAlunos);

    printf("\nAlunos na disciplina Cálculo:\n");
    buscarPorDisciplina(listaAlunos, "Cálculo");

    return 0;
}