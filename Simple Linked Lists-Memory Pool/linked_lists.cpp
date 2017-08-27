#include "linked_list.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cstring>
#include <cstddef>
using namespace std;

int i=0,size=1,payload_size=0;
void* mem_pool=NULL;
void* value_pool=NULL;

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
payload* linked_list::Init(int M,int b)
{
    mem_pool=malloc(M);
    //cout<<"mem_pool="<<mem_pool<<endl;
    value_pool=malloc(1000*sizeof(char));
    //cout<<"value_pool"<<value_pool<<endl;
    payload_size=b;
    payload *head=new(mem_pool) payload(b,value_pool);
    int key,value_len;
    char ch[1000];
    cout<<"\n Enter key";
    cin>>key;
    cout<<"\n Enter value";
    cin>>ch;
    value_len=strlen(ch);
    head->setter(key,value_len,ch);
    cout<<"\n Do you want to enter more nodes?(y/n)";
    char choice;
    cin>>choice;
    payload *n;
    n=head;
    while(choice=='y' || choice=='Y')
    {
        payload *ptr;
        ptr=new(mem_pool+sizeof(payload)*size) payload(b,value_pool);
        size++;
        cout<<"\n Enter key";
        cin>>key;
        cout<<"\n Enter value";
        cin>>ch;
        value_len=strlen(ch);
        ptr->setter(key,value_len,ch);
        n->next=ptr;
        n=n->next;
        cout<<"\n Do you want to enter more nodes?(y/n)";
        cin>>choice;
    }
    //cout<<"head="<<head;
    return head;
}
void linked_list::Insert(int x,char* value_ptr,int value_len)
{
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
            mem_pool=malloc(M);
    //cout<<"mem_pool="<<mem_pool<<endl;
            value_pool=malloc(1000*sizeof(char));
            payload_size=b;
            cout<<"\n Memory pool created!!";
        }
        this->Head=new(mem_pool) payload(payload_size,value_pool);
        this->Head->setter(x,value_len,value_ptr);
        cout<<"\n Node Inserted\n";
        return;
    }
    payload *ptr,*n;
    n=this->Head;
    while(n->next != NULL)
        n=n->next;
    ptr=new(mem_pool+sizeof(payload)*size) payload(payload_size,value_pool);
    size++;
    ptr->setter(x,value_len,value_ptr);
    n->next=ptr;
    n=n->next;
}
void linked_list::Printlist()
{
    if(this->Head == NULL)
        cout<<"\n No Linked List found";
    payload *ptr;
    ptr=this->Head;
    while(ptr != NULL)
    {
        ptr->getter(ptr);
        ptr=ptr->next;
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
    ptr=this->Head;
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
    free(mem_pool);
    cout<<"\n Memory pool deleted";
    mem_pool=NULL;
    free(value_pool);
    cout<<"\n Value pool deleted";
    value_pool=NULL;
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
   p1=this->Head;
   p2=p1->next;
   if(p1->get_key(p1) == x)
    {
        this->Head=p2;
        p1->~payload();
        return;
    }
   while(p2 != NULL)
   {
       if(p2->get_key(p2) == x)
       {
           p1->next = p2->next;
           p2->~payload();
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
    ptr=this->Head;
    while(ptr != NULL)
    {
        if(ptr->get_key(ptr) == x)
            return ptr;
        ptr=ptr->next;
    }
 cout<<"\n Element not found";
 return NULL;
}
