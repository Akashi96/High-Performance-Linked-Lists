#include "linked_list2.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cstring>
#include <cstddef>
#include <limits.h>
using namespace std;
/**     INIT FUNCTION IS WORKING FOR THE VERY FIRST TIME ONLY!!!
AFTER DESTROYING THE WHOLE LINKED LIST, IF INIT IS CALLED, AFTER THE VALUE ENTERED FOR FIRST NODE, IT HANGS...**/

int i=0,size=1,payload_size=0;
void* mem_pool=NULL;
void* value_pool=NULL;
int tier_value=(INT_MAX)/2;
int tier_no=0;

void* payload::operator new(size_t,void* loc)
{
    //cout<<"\n In payload placement new\n";
    //cout<<"loc"<<loc;
    return loc;
}
payload::payload(int b,void *ptr)
{
    key=0;
    value_len=0;
    next=NULL;
    //size=sizeof(key)+sizeof(value_len)+sizeof(next);
    int xs=(b-(sizeof(key)+sizeof(value_len)+sizeof(next)))*i;
    value=new(ptr+xs) char;
    //cout<<"b= "<<b<<endl;
    //cout<<sizeof(key)+sizeof(value_len)+sizeof(next)<<endl;
    //cout<<xs<<endl;
    //cout<<ptr;
    //cout<<ptr+xs;
    i++;
   // ptr++;

    //cout<<"value="<<value<<endl;
    //cout<<"Key="<<key<<"\n";
    //cout<<"value length="<<value_len<<"\n";0.
    //char *p;
    //p="Hello";
    //setter(3,5,p);
}
payload::~payload()
{
    cout<<"\n Deleting value";
    delete[] value;
    cout<<"\n value deleted";
}
void payload::setter(int key,int value_len,char* value_ptr)
{
    this->key=key;
    this->value_len=value_len;
    memcpy(this->value,value_ptr,value_len+2);
}

void payload::getter(payload *ptr)
{
    if(ptr == NULL)
        return;
    cout<<"\n Key= "<<ptr->key
        <<"\n Value= "<<ptr->value
        <<"\n Value_length= "<<ptr->value_len;
}
int payload::get_key(payload *ptr)
{
    return ptr->key;
}
payload_pointer* linked_list::Init(int M,int b,int t)
{
    mem_pool=malloc(M);
    //cout<<"mem_pool="<<mem_pool<<endl;

    value_pool=malloc(1000*sizeof(char));
    //cout<<"value_pool"<<value_pool<<endl;
    //payload **start = (payload**)malloc(t*sizeof(*payload));+;
    tier_no=t;
    payload_pointer *start=new payload_pointer[t];
    payload *new_node=new(mem_pool) payload(b,value_pool);
    payload_size=b;
    tier_value=tier_value/t;
    int key,value_len;
    char ch[1000];
    cout<<"\n Enter key";
    cin>>key;
    cout<<"\n Enter value";
    cin>>ch;
    value_len=strlen(ch);
    new_node->setter(key,value_len,ch);
    int prod=1,j=0;
    while(key>((tier_value*prod)-1))
    {
        j++;
        prod++;
    }
    start[j].pointer=new_node;
   // cout<<start[j].pointer->get_key(start[j].pointer);
    char choice;
    cout<<"\n Do you want to enter more nodes?(y/n)";
    cin>>choice;
    while(choice=='Y' || choice=='y')
    {
        new_node=new(mem_pool+sizeof(payload)*size) payload(b,value_pool);
        size++;
        cout<<"\n Enter key";
        cin>>key;
        cout<<"\n Enter value";
        cin>>ch;
        value_len=strlen(ch);
        new_node->setter(key,value_len,ch);
        int prod=1,j=0;
        while(key>((tier_value*prod)-1))
        {
            j++;
            prod++;
        }
        if(start[j].pointer == NULL)
            start[j].pointer=new_node;
        else
        {
            payload *ptr=start[j].pointer;
            while(ptr->next != NULL)
                ptr=ptr->next;
            ptr->next=new_node;
        }
        cout<<"\n Do you want to enter more nodes??(y/n)";
        cin>>choice;
   }
return start;
}
void linked_list::Insert(int x,char* value_ptr,int value_len)
{
    int prod=1,j=0;
    if(this->Head == NULL)
    {
        if(mem_pool == NULL)
        {
            cout<<"\n Memory pool not created yet!!!\nPlease enter size of Memory pool";
            int M;
            cin>>M;
            cout<<"\n Enter the size of payload";
            int b;
            cin>>b;
            cout<<"\n Enter the number of tiers";
            int t;
            cin>>t;
            tier_no=t;
            mem_pool=malloc(M);
    //cout<<"mem_pool="<<mem_pool<<endl;
            value_pool=malloc(1000*sizeof(char));
            payload_size=b;
            tier_value=tier_value/t;
            cout<<"\n Memory pool created!!";
        }
        this->Head=new payload_pointer[tier_no];
        payload *new_node=new(mem_pool+sizeof(payload)*size) payload(payload_size,value_pool);
        size++;
        new_node->setter(x,value_len,value_ptr);
        while(x>((tier_value*prod)-1))
        {
            prod++;
            j++;
        }
        this->Head[j].pointer=new_node;
        return;
    }
    payload *ptr,*n;
    prod=1;
    j=0;
    while(x>(tier_value*prod)-1)
    {
        j++;
        prod++;
    }
    n=this->Head[j].pointer;
    ptr=new(mem_pool+sizeof(payload)*size) payload(payload_size,value_pool);
    size++;
    ptr->setter(x,value_len,value_ptr);
    if(n == NULL)
    {
        this->Head[j].pointer=ptr;
        return;
    }
    while(n->next != NULL)
        n=n->next;
    n->next=ptr;
    n=n->next;
}

void linked_list::Printlist()
{
    if(this->Head == NULL)
    {
        cout<<"\n No Linked List found";
        return;
    }
    if(size==0)
    {
        cout<<"\n Whole linked list deleted";
        return;
    }
    payload *ptr;
    for(int i=0;i<tier_no;i++)
    {
        ptr=this->Head[i].pointer;
        if(ptr != NULL)
            cout<<"\nTier no:"<<i+1;
        while(ptr != NULL)
        {
            ptr->getter(ptr);
            cout<<"\n";
            ptr=ptr->next;
        }
    }
}
void linked_list::Destroy()
{
    if(this->Head == NULL)
    {
        cout<<"\n No linked list exist";
        return;
    }
    payload *ptr,*del;
    for(int i=0;i<tier_no;i++)
    {
        if(this->Head[i].pointer != NULL)
            cout<<"\nTier Number:"<<i+1<<"\n";
        ptr=this->Head[i].pointer;
        while(ptr != NULL)
        {
            ptr->getter(ptr);
            //cout<<"ptr= "<<ptr;
            //cout<<"\n ptr->next= "<<ptr->next;
            //cout<<"\n del= "<<del;
            del=ptr->next;
            //cout<<"\n del= "<<del;
            ptr->~payload();
            ptr=del;
            //cout<<"\n ptr= "<<ptr;
        }
    }
    free(mem_pool);
    cout<<"\n Memory pool deleted";
    mem_pool=NULL;
    free(value_pool);
    cout<<"\n Value pool deleted";
    value_pool=NULL;
    delete[] this->Head;
    size=0;
  //  cout<<mem_pool<<"\n"
  //      <<value_pool;
    this->Head=NULL;
}

void linked_list::Delete(int x)
{
    if(this->Head == NULL)
    {
        cout<<"\nNo linked List exist";
        return;
    }
   payload *p1,*p2;
   int flag=0;
   int prod=1,j=0;
   while(x>((tier_value*prod)-1))
   {
       prod++;
       j++;
   }
   p1=this->Head[j].pointer;
   if(p1 == NULL)
   {
       cout<<"\n Element Not Found";
       return;
   }
   p2=p1->next;
   if(p1->get_key(p1) == x)
    {
        this->Head[j].pointer=p2;
        p1->~payload();
        size--;
        return;
    }
   while(p2 != NULL)
   {
       if(p2->get_key(p2) == x)
       {
           p1->next = p2->next;
           p2->~payload();
           size--;
           flag=1;
       }
       p1=p1->next;
       p2=p2->next;
   }
    if(!flag)
        cout<<"\n Element not found";
return;
}

payload* linked_list::Lookup(int x)
{
    if(this->Head == NULL)
    {
        cout<<"\nNo Linked List exist";
        return NULL;
    }
    payload *ptr;
    int j=0,prod=1;
    while(x>((tier_value*prod)-1))
    {
        prod++;
        j++;
    }
    ptr=this->Head[j].pointer;
    while(ptr != NULL)
    {
        if(ptr->get_key(ptr) == x)
            return ptr;
        ptr=ptr->next;
    }
 cout<<"\n Element not found";
 return NULL;
}
