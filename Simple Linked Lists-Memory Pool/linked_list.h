#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED
#include <stdlib.h>
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
class linked_list
{
public:
    payload *Head=NULL;
   /// void* operator new(size_t,void* loc);
    payload* Init(int M=512000,int b=128);
    void Insert(int x, char * value_ptr, int value_len);
    void Printlist();
    void Destroy();
    void Delete(int x);
    payload* Lookup(int x);
};


#endif // LINKED_LIST_H_INCLUDED
