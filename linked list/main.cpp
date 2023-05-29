#include <iostream>
#include <assert.h>

using namespace std;


template <class type >
class linked_list{

        struct Node{
            type item ;
            Node *next ;
            Node *prev ;

        };

    public:
    Node *head , *tail ,*dummy;
    int length = 0 ;

    linked_list ( type value , int initial_size){
        dummy= new Node;
        dummy->item = 0;
        head = tail = dummy ;
        if(initial_size < 1){
            cout << " Invalid initial size !!" << endl;
        }else{
            for(int i =0 ;  i < initial_size ; i++){
                this->push_back(value);
            }
        }
    }

     linked_list(){
            dummy = new Node ;
            dummy->item = 0;
            head = tail = dummy ;
        }

    /*
        Start of iterator class
    */
            class iterator{
                    Node *position ;
                    public:
                        iterator(){}
                        iterator(Node *mynode){
                            position = mynode ;
                        }
                    void operator ++(int){                    // Overloading the increment operator in postfix form
                        try{
                            if(position ->next ==NULL ){
                                throw 1;
                            }else{
                                position = position->next ;
                            }
                        }catch(int x){
                            cout << "  Error number " << x <<  " : The iterator pointing after the last node ! " << endl;
                        }
                    }

                    type &operator* (){

                        if(position->next == NULL)
                            cout << " The dummy node has no value "<< endl;
                        return position->item ;
                    }

                    void operator --(int){                    // Overloading the decrement operator in postfix form
                        try{
                            if(position->prev == NULL){
                                throw 2;
                            }else{
                                position = position->prev;
                            }
                        }catch(int x){
                            cout << " Error number " << x << " : The iterator pointing on the first node !" << endl;
                        }
                    }
                    bool operator == (const iterator & it){
                        return (position == it.position);
                    }
                    void operator = (const iterator&it){
                        this->position = it.position;
                    }
            };


    /*
        End of iterator class
    */



        iterator begin(){
            iterator it(head);
            return it ;
        }
        iterator end(){
            iterator it(dummy);
            return it ;
        }

        iterator erase(iterator pos){
            try{
                if(pos == this->end()){
                    throw 3;
                }else{
                    length--;
                    Node *ptr = new Node ;
                    ptr = head;
                    iterator it = this->begin();
                    pos--;
                    while ( !(pos == it) ){
                        ptr = ptr->next;
                        it++;
                    }
                    Node *del = new Node ;
                    del = ptr->next ;
                    ptr->next = ptr->next->next ;
                    ptr->next->prev = ptr ;
                    delete del ;
                    pos++;
                    return pos ;
                }

            }catch(int x){
                cout << " Error number " << x << " : The iterator pointing after the last node ! \n ( you can't delete the dummy node )" << endl;
                return pos ;
            }
        }

        void push_back(type x ){
            length++;
            Node *temp = new Node ;
            temp->item = x ;
                if( head == dummy){
                    head = temp ;
                    tail = temp;

                    //dummy node

                    tail->next = dummy ;
                    dummy->prev = tail;
                    head->prev = NULL;
                    dummy->next = NULL;
                }else{
                    temp->prev = tail ;
                    tail->next = temp ;
                    tail = temp ;

                    //dummy node

                    tail->next = dummy ;
                    dummy->prev = tail;
                    head->prev = NULL;
                    dummy->next = NULL;
                }
        }

        void push_front(type x ){
            length++;
            Node *temp = new Node ;
            temp->item = x ;
                if( head == dummy){
                    head = temp ;
                    tail = temp;

                    //dummy node

                    tail->next = dummy ;
                    dummy->prev = tail;
                    head->prev = NULL;
                    dummy->next = NULL;
                }else{
                    temp->next = head;
                    head->prev = temp ;
                    temp->prev = NULL ;
                    head = temp;

                    //dummy node

                    tail->next = dummy ;
                    dummy->prev = tail;
                    head->prev = NULL;
                    dummy->next = NULL;
                }
        }
        void insert (type value , iterator pos){
            iterator it ;
            it = this->begin() ;
                if(pos == this->begin()){
                    this->push_front(value);
                    return ;
                }else{
                    if(pos == this->end()){
                        this->push_back(value);
                    return ;
                    }
                }
            length++;
            Node *ptr = new Node ;
            ptr = head ;
            pos--;              // to insert at the specified position and to shift the other after it
                while ( !(it == pos)) {
                    ptr = ptr->next;
                    it++;
                }


            Node *newnode = new Node ;
            newnode->item = value ;
            newnode->next = ptr->next ;
            (ptr->next)->prev = newnode ;
            ptr->next = newnode ;
            newnode->prev = ptr ;

        }

        void print(){
            iterator it ;
            it = this->begin();
            for (int i=0 ; i<this->size() ; i++){
                cout << *it << endl;
                it++;
            }
        }

        type front(){
            return head->item ;
        }

        type back(){
            return tail->item ;
        }


        int size(){
            return length ;
        }
         linked_list<type>& operator =( linked_list <type>  mylist){
            iterator it = mylist.begin();
            for(int i =0 ; i<mylist.size() ; i++){
                this->push_back(*it);
                it++;
            }
            return this ;
        }

        ~linked_list(){
            Node *del = new Node ;
            del = tail ;
            tail = tail->prev ;
            for(int i = 0 ; i<length-1 ; i++){
                delete del ;
                del = tail ;
                tail = tail->prev ;
            }
            delete tail ;
        }

};


int main()
{
    cout << "******************** Creating the first list without using the parameterized constructor ********************" << endl;
    cout << "   type : int " << endl;
    cout << "   Name : mylist1" << endl;
    linked_list<int> mylist1 ;
    cout << "   Creating an iterator called 'it' with type int to traverse the list " << endl;
    cout << "   Inserting some elements to the list by using tail insertion " << endl << endl;
    mylist1.push_back(1);
    mylist1.push_back(2);
    mylist1.push_back(3);
    mylist1.push_back(4);
    mylist1.push_back(5);
    linked_list<int> ::iterator it  = mylist1.begin() ;
    cout << "   Printing the elements using a function uses iterators : " << endl;
    mylist1.print();
    cout << "   Inserting the element (36) at the head of the list " << endl;
    mylist1.push_front(36) ;
    cout << "   After the modification the list will be like : " << endl;
    mylist1.print();
    cout << "   Inserting element (99) at the index 3 using 'it' iterator " << endl;
    it++;
    it++;
    cout << *it << endl;
    mylist1.insert(99,it);
    cout << "   The list after : " << endl;
    mylist1.print();
    cout << "   Deleting the element of index 4 using 'it' iterator " << endl;
    it++;
    linked_list<int> ::iterator it2 = mylist1.erase(it);
    cout << "   The list after : " << endl;
    mylist1.print();
    it = mylist1.begin() ;
    it2 = mylist1.end() ;
    cout << " If we tried to increment an iterator that points after the last node : " << endl << endl;
    it2++;
    cout << " If we tried to decrement an iterator that points on the head of the list : " << endl << endl;
    it--;
    cout << endl << endl;
    cout << "******************** Creating the second list using the parameterized constructor ********************" << endl;
    cout << "   Type : char " << endl;
    cout << "   Name : mylist2 " << endl;
    cout << "   The parameters of the constructor is ('a',5) which will insert the element 'a' five times" << endl;
    linked_list<char> mylist2('a',5);
    linked_list<char> :: iterator it3 ;
    cout << "   The list after : " << endl;
    mylist2.print();
    it3 = mylist2.begin();
    it3++;
    it3++;
    cout << "   Inserting the element 't' at the index 3 using iterator" << endl;
    mylist2.insert('t',it3);
    cout << "   The list after : " << endl;
    mylist2.print();
    cout << "   Displaying the size of the list using the size function : " << mylist2.size() << endl << endl;
    cout << "******************** Creating the third list using the assignment operator with mylist2 ********************" << endl;

    linked_list<char> mylist3 = mylist2;
    cout << "   modifying the third list without modifying mylist2 " << endl;
    mylist3.push_back('r');
    cout << "   After modification : " << endl;
    cout << "   The third list : " << endl;
    mylist3.print();
    cout << "   The second list : " << endl;
    mylist2.print();



    return 0;
}
