#ifndef BigInteger_h
#define BigInteger_h


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    int data;
    struct node *next;
};

struct BigInteger
{
    struct node *head;
    int length;
    int sign;
};
struct node * reverse(struct node *);
struct node* newNode(int);
void insertAtBegin(struct node ** , int );
struct BigInteger initialize(char *);
void printreverse(struct node *);
void display(struct BigInteger);
int truncate(struct node *);
int compare(struct BigInteger ,struct BigInteger);
int count(struct node *);
int signcompare(struct BigInteger,struct BigInteger);
struct node * addd(struct node *,struct node *);
struct BigInteger add(struct BigInteger ,struct BigInteger );
struct BigInteger sub(struct BigInteger,struct BigInteger);
struct node *add_mul(struct node *, struct node *);
struct node * mull(struct node *,struct node *);
struct BigInteger mul(struct BigInteger,struct BigInteger);
int compare_div(struct node *,struct node *);
struct node * divv(struct node *,struct node *);
struct BigInteger div1(struct BigInteger,struct BigInteger);
struct BigInteger mod(struct BigInteger,struct BigInteger);


#endif