/*

��������� Pn(x) = a_n*x^n+a_{n-1}*x^{n-1}+...+a_1*x+a0 �������� � ���� ������:
��������: S = 52*x^{40} - 3*x^8 + x

�������:

1. �������� ������� ����������� �� ��������� ��� ����������( x+1 = 1+x !!!)
2.+���������, ��������� ����������� ���������� �.
3.+��������� �������� ���� �����������.
4.+��������� ����������� �������� ���������� � ����� �.
5.-���. ���������, ������� �� ������ � ���������� ���� char ������� ���������.
   (��������: ��� ���������� S � ���������� t ������ ���� ���������� -
   52 * t^40 - 3 * t^8 + t)
6.-���.���������, ������� �� ������, ���������� ������������ ������� ����������, ��������� ������.
7.+��������� ��������/���������� �������, �������� �����������.
8. �������� �������� ��������� � ����������.
9.+����� ������������ ���� �����������.
10.���� ��� ���������� P(x) � Q(x). ����� ��������� R(x), �����, ��� P(x) = Q(x) + R(x)
11.* ���� ��� ���������� P(x) � Q(x). ����� ���������� D(x) � R(x), �����,
   ��� P(x) = Q(x) *D(x) + R(x) (������� D(x) - ����������� ���������)
12. ������� ��������� P(x), �������������� �� ����� �������

�������:
void L_print(list *L) { // ����� �� �����
void L_start(list *L, int n, double a) { // L:=������ �� ������ �������� a*x^n
void L_pop_front(list *L, int n, double a) { // �������� ����� a*x^n � ������ ������ L
void L_pop(list *L, int i, int n, double a) { // �������� ����� v ����� ������� i � ������ L
void L_pop(list *L, int i, int n, double a) { // �������� ����� v ����� ������� i � ������ L
void L_popA(list *L, int i, int n, double a) { // �������� ����� v ����� ������ i � ������ L
void L_popE(list *L, int n, double a) { // �������� ����� v � ����� ������ L
void L_del1(list *L) { // ������� ������ �������
void L_del(list *L, int i) { // ������� i-� �������
void L_copy(list *dst, list *src) { // dst:=src
-----------------------------
void L_diff(list *L, list *D) {     // D:=diff(L)
void L_add(list *sum, list *L1, list *L2) {     // sum:=L1+L2
double  L_value(list *L, double x) {     // return L(x)
bool  L_even(list *L) {     // ����� �� ��������� ������
bool  L_odd(list *L) {     // ����� �� ��������� ��������
void L_mult(list *M, list *L1, list *L2) {     // M:=L1*L2


*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

typedef struct link {
    int n;              // �������
    double a;           // �����������
    struct link *next;
  } list;

void L_print(list *L) { // ����� �� �����
    for(;;) {
        double a = L->a;
        if(a==0) continue;
        printf("%+8.2f",a);     // ������� ����� �� ������
        int n = L->n;
        if(n>1)printf("x^%d ",n);
        else if(n==1) printf("x ");
        else printf(" ");

        if( L->next==NULL) break;
        L = L->next;
    }
    printf("\n");
}
void L_start(list *L, int n, double a) { // L:=������ �� ������ �������� a*x^n
    L->n = n;
    L->a = a;
    L->next = NULL;
}
void L_pop_front(list *L, int n, double a) { // �������� ����� a*x^n � ������ ������ L
    link *L1 = new link;
    L1->n = L->n;
    L1->a = L->a;
    L1->next = L->next;
    L->n = n;
    L->a = a;
    L->next = L1;
}
void L_pop(list *L, int i, int n, double a) { // �������� ����� v ����� ������� i � ������ L
    for( int j=0; j<i; j++) {
        if( (L = L->next)==NULL) return;  // ������
    }
    L_pop_front(L, n, a);
}
void L_popA(list *L, int i, int n, double a) { // �������� ����� v ����� ������ i � ������ L
    for( int j=0; j<=i; j++) {
        if( (L = L->next)==NULL) return;  // ������
    }
    L_pop_front(L, n, a);
}
void L_popE(list *L, int n, double a) { // �������� ����� v � ����� ������ L
    while( L->next != NULL) L = L->next;
    link *L1 = new link;
    L->next = L1;
    L1->n = n;
    L1->a = a;
    L1->next = NULL;
}
void L_del1(list *L) { // ������� ������ �������
    link *L1 = L->next;
    L->n = L1->n;
    L->a = L1->a;
    L->next = L1->next;
    delete L1;
}
void L_del(list *L, int i) { // ������� i-� �������
    for( int j=0; j<i; j++) {
        if( (L = L->next)==NULL) return;  // ������
    }
    L_del1(L);
}
void L_copy(list *dst, list *src) { // dst:=src
    L_start(dst, src->n, src->a);
    while(src != NULL) {
        L_popE(dst, src->n, src->a);
        src = src->next;
    }
}
//------------------------------------------------------
void L_diff(list *L, list *D) {     // D:=diff(L)
    if( L->n==0) L=L->next;
    L_start(D, L->n-1, L->n*L->a );
    L = L->next;
    while(L != NULL) {
        L_popE(D, L->n -1, L->n *L->a );
        L = L->next;
    }
}
//------------------------------------------------------
void L_add(list *sum, list *L1, list *L2) {     // sum:=L1+L2
    bool first=true;                            // sum ��� �� �����
    int d1=999999999, d2=999999999, d;
    if(L1 != NULL)d1 = L1->n;
    if(L2 != NULL)d2 = L2->n;
    double a;
    for(;;) {
        d1 = (L1==NULL? 999999999 : L1->n);
        d2 = (L2==NULL? 999999999 : L2->n);
        if( d1==999999999 && d2==999999999) break;
        if( d1<d2) {
            d = d1;
            a = L1->a;
            L1 = L1->next;
        }
        else if( d1>d2) {
            d = d2;
            a = L2->a;
            L2 = L2->next;
        }
        else {
            d=d1;
            a = L1->a + L2->a;
            L1 = L1->next;
            L2 = L2->next;
        }
        if(first) {
            L_start(sum, d, a);
            first = false;
        }
        else
            L_popE(sum, d, a );

    }
}
//------------------------------------------------------
double  L_value(list *L, double x) {     // return L(x)
    double f=0;
    while(L != NULL) {
        f += L->a*pow(x, L->n);
        L = L->next;
    }
    return f;
}
//------------------------------------------------------
bool  L_even(list *L) {     // ����� �� ��������� ������
    while(L != NULL) {
        if( L->n %2) return false;  // ���� �������� �������
        L = L->next;
    }
    return true;
}
bool  L_odd(list *L) {     // ����� �� ��������� ��������
    while(L != NULL) {
        if( (L->n %2)==0) return false;  // ���� ������ �������
        L = L->next;
    }
    return true;
}
//------------------------------------------------------
void L_mult1(list *dst, list *src, int n, double a) {     // dst := a*x^n*src
    L_copy(dst, src);
    do {
        dst->n += n;
        dst->a *= a;
        dst=dst->next;
    }while(dst != NULL);
}
//------------------------------------------------------
void L_mult(list *M, list *L1, list *L2) {     // M:=L1*L2
    list M1, tmp;
    L_mult1(M, L2, L1->n, L1->a);
    L1 = L1->next;
    while(L1!=NULL) {
        L_mult1(&M1, L2, L1->n, L1->a);
        L_add(&tmp, M, &M1);
        L_copy(M, &tmp);
        L1 = L1->next;
    }
}
//------------------------------------------------------
int main()
{
    list L, D, S;
    L_start(&L, 1,11.);
    //L_popE(&L, 1, 11.);
    L_popE(&L, 5,-15.);
    L_popE(&L, 9, 19.);
    printf("Polynom:  L="); L_print(&L);

    L_diff(&L, &D);
    printf("Derivative:  D=L'="); L_print(&D);

    L_add(&S, &L, &D);
    printf("summ: L+D="); L_print(&S);
    printf("P(-1)=%8.2f\n", L_value(&L, -1.0));
    printf("L odd : %d\n", L_odd(&L));
    printf("L even: %d\n", L_even(&L));
    L_mult(&S, &L, &D);
    printf("L*D :"); L_print(&S);
    return 0;
}
