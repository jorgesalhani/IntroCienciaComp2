#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FREE -1
#define DEL -2

// Criar tabela de tamanho m
int *create_hash_table(int m);

void destroy_hash_table(int **t);

// Inserir elemento key na tabela t de tamanho m
int insert(int *t, int key, int m);

// Buscar element key na tabela t de tamanho m
int search(int *t, int key, int m);

// Excluir elemento key da tabela t de tamanho m
int remove_hash(int *t, int key, int m);

void print_table(int *t, int m);

int hash_division(int key, int m, int c);

int hash_multi(int key, int m, int c, double A);