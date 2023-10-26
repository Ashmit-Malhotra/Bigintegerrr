#include "BigInteger.h"

struct node * reverse(struct node *head)
{
    if(!head||(head)->next==NULL)
    {
        return head;
    }

    struct node *prev=NULL,*cur=head,*fora=(head)->next;
    while(cur!=NULL)
    {
        cur->next=prev;
        prev=cur;
        cur=fora;
        if(fora!=NULL)
        {
            fora=cur->next;
        }
        
    }
    return prev; 
}
struct node* newNode(int val) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = val;
    temp->next = NULL;
    return temp;
}
void insertAtBegin(struct node **head,int val){
    struct node *temp=(struct node *)malloc(sizeof(struct node));

    if(temp==NULL)//if memory is not allocated.
    {
        printf("error in memory allocation");
        return;
    }
    temp->data=val;
    temp->next=NULL;
    if(*head==NULL)
    {
        *head=temp;
        return;
    }
    temp->data=val;
    temp->next=*head;
    *head=temp;//chnaging head.
    return;
}
struct BigInteger initialize(char *s){
    struct BigInteger temp;
    temp.head=NULL;
    temp.length = 0;
    temp.sign = 0;
    int i = 0 ; 
    if(s[i] == '-')
    {
        temp.sign = 1;
        i++;
    }
    while ( s[i] != '\0' )
    {
        insertAtBegin(&temp.head,s[i]-'0');
        i++;
        temp.length++;
    }
    return temp;
}
void printreverse(struct node *head){
    if(!head)
    {
        return;
    }
    printreverse(head->next);
    printf("%d",head->data);
}
void display(struct BigInteger s1){
    struct node *head=s1.head;
    if(s1.sign==1)
    {
        printf("-");
    }
    printreverse(head);
    
    return;
}
int truncate(struct node *head){
    if(!head)
    {
        return 0;
    }

    if(truncate(head->next))
    {
        return 1;
    }
    if(head->next);
        free(head->next);
    head->next=NULL;

    if(head->data==0)
        return 0 ; 

    else
        return 1;
}
int compare(struct BigInteger a,struct BigInteger b){
    truncate(a.head);
    truncate(b.head);
    a.length=count(a.head);
    b.length=count(b.head);

    if(a.length>b.length)
        return 1;
    else if(a.length<b.length)
        return -1;

    else{
        int res = 0;

        struct node *itr1=a.head;
        struct node *itr2=b.head;

        while(itr1!=NULL)
        {
            if(itr1->data>itr2->data)
                res=1;

            else if(itr1->data<itr2->data)
                res =-1;
            
            itr1=itr1->next;
            itr2=itr2->next;

        }
        return res;
    }
}
int count(struct node *l1){
    int count = 0 ; 
    while(l1)
    {
        count++;
        l1=l1->next;
    }
    return count;
}
int signcompare(struct BigInteger s1,struct BigInteger s2)
{   if(s1.sign==1&&s2.sign==1)
        return 2;
    else if((s1.sign==0&&s2.sign==1))
        return 0;
    else if((s1.sign==1&&s2.sign==0))
        return 3;
    else return 1;
}
struct node * addd(struct node *l1,struct node *l2){
    struct node *res=NULL,*itr=res;
    int carry=0;
    if(l1->data==0&&count(l1)==1)
        return l2;
    if(l2->data==0&&count(l2)==1)
        return l1;
    while(l1&&l2)
    {
        int sum = l1->data+l2->data+carry;
        carry=0;
        if(sum>9)
        {
            carry=1;
            sum=sum%10;
        }
        struct node *newnodee=newNode(sum);
        if (res == NULL) {
            res = newnodee;
            itr = res;
        } else {
            itr->next = newnodee;
            itr = itr->next;
        }
        l1=l1->next;
        l2=l2->next;
    }
    while(l1)
    {
        int sum = l1->data+carry;
        carry=0;
        if(sum>9)
        {
            carry=1;
            sum=sum%10;
        }
        struct node *newnodee=newNode(sum);
        if (res == NULL) {
            res = newnodee;
            itr = res;
        } else {
            itr->next = newnodee;
            itr = itr->next;
        }
        l1=l1->next;
    }
    while(l2)
    {
        int sum = l2->data+carry;
        carry=0;
        if(sum>9)
        {
            carry=1;
            sum=sum%10;
        }
        struct node *newnodee=newNode(sum);
        if (res == NULL) {
            res = newnodee;
            itr = res;
        } else {
            itr->next = newnodee;
            itr = itr->next;
        }
        l2=l2->next;
    }

    if(carry)
    {
        struct node *newnodee=newNode(carry);
        if (res == NULL) {
            res = newnodee;
            itr = res;
        } else {
            itr->next = newnodee;
            itr = itr->next;
        }
    }
    return res;
}
struct BigInteger add(struct BigInteger s1,struct BigInteger s2){
    struct BigInteger temp;
    temp.head=NULL;
    temp.length=0;
    temp.sign=0;

    if(signcompare(s1,s2)==1){
        temp.head=addd(s1.head,s2.head);
    }
    else if((signcompare(s1,s2)==2)){
        temp.head=addd(s1.head,s2.head);
        temp.sign=1;
    }
    else if((signcompare(s1,s2)==0)){
        if(compare(s1,s2)==1){
            temp=sub(s1,s2);
        }
        else if(compare(s1,s2)==-1){
            temp=sub(s2,s1);
            temp.sign=1;
        }
        else{
            temp.head=newNode(0);
        }
    }
    else if((signcompare(s1,s2)==3)){
        if(compare(s1,s2)==1){
            temp=sub(s1,s2);
            temp.sign=1;
        }
        else if(compare(s1,s2)==-1){
            temp=sub(s2,s1);
        }
        else{
            temp.head=newNode(0);
        }
    }
    truncate(temp.head);
    temp.length=count(temp.head);
    return temp;
}
struct BigInteger sub(struct BigInteger a,struct BigInteger b){
    if(a.head == NULL) {
        if(b.head == NULL) {
            a.head = newNode(0);
            a.sign = 0;
            a.length = 1;
            return a;
        }
        else {
            a.head = newNode(0);
            return sub(a, b);
        }
    }

    if(b.head == NULL) return a;

    struct BigInteger d;
    d.sign = 0;

    if(a.sign == 0 && b.sign == 1) {
        d.head = addd(a.head, b.head);
        d.sign = 0;
        d.length = count(d.head);
        return d;
    }
    if(a.sign == 1 && b.sign == 0) {
        d.head = addd(a.head, b.head);
        d.sign = 1;
        d.length = count(d.head);
        return d;
    }
    if(a.sign == 1 && b.sign == 1) d.sign = 1;

    int c = compare_div(a.head, b.head), l = 0;

    if(c == 0) {
        a.head = newNode(0);
        a.length = 1;
        a.sign = 0;
        return a;
    } 

    struct node *res = NULL, *itr = NULL;

    if(c == -1) {
        d = sub(b, a);
        res = d.head;
        itr = res;
        while(itr->next) itr = itr->next;
        itr->data = -itr->data;
        d.head = res;
        return d;
    }

    int term, borrow = 0;
    struct node *l1 = a.head, *l2 = b.head;

    while(l2) {
        int x = l1->data;
        int y = l2->data;
        if(x >= (y + borrow)) {
            term = x - y - borrow;
            borrow = 0;
        }
        else {
            term = 10 + x - y - borrow;
            borrow = 1;
        }
        if(res == NULL) {
            itr = newNode(term);
            res = itr;
        } else {
            res->next = newNode(term);
            res = res->next;
        }
        l1 = l1->next;
        l2 = l2->next;
        ++l;
    }

    while(l1) {
        if(borrow) {
            if(l1->data >= borrow) {
                res->next = newNode(l1->data - borrow);
                borrow = 0;
            }
            else {
                res->next = newNode(9);
                borrow = 1;
            }
        }
        else res->next = newNode(l1->data);

        l1 = l1->next;
        res = res->next;
        ++l;
    }

    truncate(itr);

    d.head = itr;
    d.length = l;
    return d;

}
struct node *add_mul(struct node *l1, struct node *l2)
{
    struct node *head = NULL;
    l1 = reverse(l1);
    l2 = reverse(l2);
    int carry = 0, sum = 0, a, b;
    while(l1 || l2)
    {
        if(l1)
            a = l1->data;
        else
            a = 0;

        if(l2)
            b = l2->data;
        else
            b = 0;

        sum = a + b + carry;
        carry = sum/10;
        insertAtBegin(&head, sum%10);
        if(l1)
            l1 = l1->next;
        if(l2)
            l2 = l2->next;
    }
    if(carry > 0)
        insertAtBegin(&head, carry);
    return head;
}
struct node * mull(struct node *p1,struct node *p2){
    int mul;
    int pos =0;
    if(p1->data==0&&count(p1)==1)
        return newNode(0);
    if(p2->data==0&&count(p2)==1)
        return newNode(0);
    struct node *result=newNode(0);
    struct node *p=p1;
    while(p2)
    {
        struct node *head = NULL;
        int carry = 0;
        for(int i=0;i<pos;i++)
            insertAtBegin(&head, 0);
        while(p1)
        {
            mul = ((p1->data) * (p2->data)) + carry;
            carry=mul/10;
            insertAtBegin(&head, mul%10);
            p1 = p1->next;
        }
        while(carry!=0)
        {
            insertAtBegin(&head, carry%10);
            carry/=10;
        }
        p2 = p2->next;
        pos++;
        result = add_mul(result, head);
        p1 = p;
    }
    result=reverse(result);

    return result;
}
struct BigInteger mul(struct BigInteger s1,struct BigInteger s2){
    struct BigInteger temp;
    temp.head=NULL;
    temp.length=0;
    temp.sign=0;

    if((signcompare(s1,s2)==1)||((signcompare(s1,s2))==2)){
        if(compare(s1,s2)==1){
            temp.head=mull(s2.head,s1.head);
        }
        else{
            temp.head=mull(s1.head,s2.head);
        }
    }
    if((signcompare(s1,s2)==0)||((signcompare(s1,s2))==3)){
        if(compare(s1,s2)==1){
            temp.head=mull(s2.head,s1.head);
            temp.sign=1;
            if(count(temp.head)==1&&temp.head->data==0)
            temp.sign=0;
        }
        else{
            temp.head=mull(s1.head,s2.head);
            temp.sign=1;
            if(count(temp.head)==1&&temp.head->data==0)
            temp.sign=0;
        }
    }
    truncate(temp.head);
    temp.length=count(temp.head);
    return temp;
}

int compare_div(struct node * l1,struct node *l2){
    int n1=count(l1),n2=count(l2);

    if(n1>n2){
        return 1;
    }
    else if (n2>n1){
        return -1;
    }
    else {
        int res = 0 ; 

        struct node *itr1=l1;
        struct node *itr2=l2;

        while(itr1!=NULL)
        {
            if(itr1->data>itr2->data)
                res=1;

            else if(itr1->data<itr2->data)
                res =-1;
            
            itr1=itr1->next;
            itr2=itr2->next;

        }
        return res;
    }
}

struct node * divv(struct node *l1,struct node *l2 ){
    int n1=count(l1),n2=count(l2);
    if(n2==1&&l2->data==1)
    {
        return l1;
    }
    if(n2==1&&l2->data==0)
    {
        return newNode(0);
    }

    struct node *temp=newNode(0);
    struct node *count=newNode(0);
    struct node *prev=count;

    while(compare_div(l1,temp)>0){
        temp=addd(temp,l2);
        prev=count;
        count=addd(count,newNode(1));        
    }

    if(compare_div(l1,temp)==0)
    return count;
    else{
        return prev;
    }
}

struct BigInteger div1(struct BigInteger s1,struct BigInteger s2){
    struct BigInteger temp;
    temp.head=newNode(0);
    temp.length=0;
    temp.sign=0;

    if(s1.length<s2.length){
        temp.length=1;
        return temp;
    }
    
    if(signcompare(s1,s2)==1||signcompare(s1,s2)==2)
    {
        temp.head=divv(s1.head,s2.head);
    }

    if(signcompare(s1,s2)==0||signcompare(s1,s2)==3)
    {
        temp.sign=1;
        temp.head=divv(s1.head,s2.head);
    }    
    truncate(temp.head);
    temp.length=count(temp.head);
    if(temp.length==1&&temp.head->data==0){
        temp.sign=0;
    }
    return temp;
}

struct BigInteger mod(struct BigInteger a,struct BigInteger b){
    if(a.head == NULL && b.head == NULL) {
        a.head = newNode(0);
        a.sign = 0;
        a.length = 1;
        return a;
    }
    if(a.head == NULL) return a;
    if(b.head == NULL) return b;

    int x = compare_div(a.head, b.head);

    if(x == 0) {
        a.head = newNode(0);
        a.length = 1;
        return a;
    }

    if(x == -1) return a;

    struct BigInteger c = div1(a, b);
    c=mul(c,b);
    c=sub(a,c);
    c.sign = 0;
    c.length = count(c.head);

    return c;
}

