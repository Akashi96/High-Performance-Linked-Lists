#include <iostream>
#include <string.h>
#include "linked_list.h"
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    linked_list L1;
    //cout<<L1.Head;
    int choice;
    int M,b,x;
    while(1){
    cout<<"\n***********************HIGH PERFORMANCE LINKED LISTS****************************"
        <<"\n Enter 1:To initialize the linked list"
        <<"\n Enter 2:To destroy a linked list"
        <<"\n Enter 3:To insert in a linked list"
        <<"\n Enter 4:To delete a node from the linked list"
        <<"\n Enter 5:To Lookup for a node in the linked list"
        <<"\n Enter 6:To print the linked list"
        <<"\n Enter 7:To Exit"
        <<"\n Enter your choice";
    cin>>choice;
    switch(choice)
    {
        case 1: cout<<"\n Enter size of Memory pool to be allocated ";
                cin>>M;
                cout<<"\n Enter size of payload";
                cin>>b;
                L1.Head=L1.Init(M,b);
                break;
        case 2: L1.Destroy();
                break;
        case 3: cout<<"\nEnter key";
                int x;
                cin>>x;
                cout<<"\n Enter value";
                char value_ptr[200];
                cin>>value_ptr;
                int value_len;
                value_len=strlen(value_ptr);
                L1.Insert(x,value_ptr,value_len);
                break;
        case 4: cout<<"\n Enter the node to be deleted";
                cin>>x;
                L1.Delete(x);
                break;
        case 5: cout<<"\n Enter the key";
                cin>>x;
                payload* ptr;
                ptr=L1.Lookup(x);
                ptr->getter(ptr);
                break;
        case 6: L1.Printlist();
                break;
        case 7: return 0;

        default:cout<<"\n Wrong Choice";

    }
}
return 0;
}
