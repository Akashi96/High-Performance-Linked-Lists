#ifndef LINKED_LIST2_H_INCLUDED
#define LINKED_LIST2_H_INCLUDED

#include<stdlib.h>
class payload
{
private:
    int key;
    int value_len;
    char *value;

public:
    payload *next;
    payload(int b,void *ptr);
    ~payload();
    void* operator new(size_t,void* loc);
   // void* operator new[](size_t,void* loc);
    void setter(int key,int value_len,char* value_ptr);
    void getter(payload *ptr);
    int get_key(payload *ptr);


};
struct payload_pointer
{
    payload *pointer=NULL;
};
class linked_list
{
public:
    payload_pointer *Head=NULL;
    payload_pointer* Init(int M=512000,int b=128,int t=16);
    void Insert(int x, char * value_ptr, int value_len);
    void Destroy();
    void Printlist();
    void Delete(int x);
    payload* Lookup(int x);
};

#endif // LINKED_LIST2_H_INCLUDED
