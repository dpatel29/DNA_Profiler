#include "DNA.h"
//Title: DNA.cpp
//Author: Deval Patel
//Date: 3/26/2021
//Description: Define DNA.h functions

/*
 Name: DNA() - Default Constructor
 Desc: Used to build a new DNA sequence
 Preconditions: None
 Postconditions: Creates a new DNA where m_head and m_tail point to nullptr
*/
DNA::DNA(){

    // setting m_name equal to the blank string
    m_name = " ";
    // setting head to an nullptr
    m_head = nullptr;

    // setting tail to an nullptr
    m_tail = nullptr;

    // setting size to an 0
    m_size = 0;

}


/*
 Name: DNA(string) - Overloaded Constructor
 Desc: Used to build a new DNA sequence with the name passed
 Preconditions: None
 Postconditions: Creates a new DNA where m_head and m_tail point to nullptr and name is passed
*/
DNA::DNA(string name){

    // here i am assigning m_name equal to name
    m_name = name;

    // setting m_head equal to an null pointer
    m_head = nullptr;

    // setting m_tail equal to an null pointer
    m_tail = nullptr;

    // setting m_size to 0
    m_size = 0;
}


/*
 Name: ~DNA() - Destructor
 Desc: Used to destruct a strand of DNA
 Preconditions: There is an existing DNA strand with at least one node
 Postconditions: DNA is deallocated (including all dynamically allocated nodes)
                 to have no memory leaks!
*/
DNA::~DNA(){

    // creating a node and setting it equal to m_head
    Node *current = m_head;

    // checking if current is not equal to nullptr if it's not then it will enter this while loop
    while(current != nullptr){

        // setting m_head equal to current
        m_head = current;

        // moving current to next node and storing that in current variable
        current = current->m_next;

        // deleting m_head
        delete m_head;
    }
    // setting m_head to nullptr
    m_head = nullptr;

    // setting tail equal to nullptr
    m_tail = nullptr;

    // setting size to
    m_size = 0;
}


/*
 Name: InsertEnd
 Preconditions: Takes in a char. Creates new node.
                Requires a DNA strand
 Postconditions: Adds the new node to the end of the DNA strand.
*/
void DNA::InsertEnd(char data){

    // here i am creating an temp and setting it equal to new node()
    Node *temp = new Node();

    // moving temp to next and setting it equal to nullptr
    temp->m_next = nullptr;

    // moving temp to m_data and setting it equal to data
    temp->m_data = data;

    // checking if m_tail is equal to nullptr or not, if it is then it will go into this if statment
    if(m_tail == nullptr){

        // setting m_tail to temp
        m_tail = temp;

        // setting m_head to temp
        m_head = temp;
    }else{

        // if the above if statement dont get executed then it will goes in here
        // setting temp-> next to null
        temp->m_next = nullptr;

        // moving tail to next and setting equal to temp
        m_tail->m_next = temp;

        // setting tail equal to temp
        m_tail = temp;
    }
    // incrementing m_size
    m_size ++;
}


/*
 Name: GetName()
 Preconditions: Requires a DNA sequence
 Postconditions: Returns m_name;
*/
string DNA::GetName(){

    // This function returns the name
    return m_name;
}


/*
 Name: GetSize()
 Preconditions: Requires a DNA sequence
 Postconditions: Returns m_size;
*/
int DNA::GetSize(){

    // this function returns the size
    return m_size;
}


/*
 Name: ReverseSequence
 Preconditions: Reverses the DNA sequence
 Postconditions: DNA sequence is reversed in place; nothing returned
*/
void DNA::ReverseSequence(){

    // creating node named curr and setting it equal to m_head
    Node *curr = m_head;

    // creating prev and setting it equal to null
    Node *prev = nullptr;

    // creating next and setting it equal to null
    Node *next = nullptr;

    // checking if the curr is not equal to null, if it's not then it will enter this while loop
    while(curr != nullptr){

        // setting next to curr->m_next
        next = curr->m_next;

        // moving curr to next node and setting it equal to pre
        curr->m_next = prev;

        // setting prev equal to curr
        prev = curr;

        // setting curr equal to next
        curr = next;
    }
    // setting m_head equal to prev
    m_head = prev;
}


/*
 Name: CompareSequence
 Preconditions: Requires two DNA sequence (suspect and passed evidence DNA)
 Postconditions: Returns true if evidence sequence exists; else false
*/

bool DNA::CompareSequence(DNA &evidence){

    // creating sus node which and setting it equal to m_head
    Node *sus = m_head;

    // creating evi node and setting it to parameter.m_head
    Node *evi = evidence.m_head;

    // creating ptr and setting equal to sus
    Node *ptr1 = sus;

    // creating ptr and setting it equal to evi
    Node *ptr2 = evi;

    // creating an counter and assigning it equal to
    int counter = 0;

    // here i have an while loop which will check if the sus is not equal to nullptr, if its not then it will enter in
    while(sus!= nullptr) {

        // setting ptr1 equal to sus
        ptr1 = sus;

        // here i am using another while loop which will check if ptr1 and ptr3 is not equal not null and it also checks
        // if ptr1->data and ptr2->data is equal to each other, if it is then it will enter in this loop
        while (ptr2 != nullptr && ptr1 != nullptr && ptr1->m_data == ptr2->m_data) {

            // incrementing counter
            counter++;

            // moving ptr to next node
            ptr1 = ptr1->m_next;

            // moving ptr2 to next node
            ptr2 = ptr2->m_next;
        }

        // here i am checking if the counter is equal to the evidence size or not, if it is then it will enter this
        // if statement
        if (counter == evidence.GetSize()) {

            // returning true
            return true;
        } else {

            // setting ptr2 equal to evidence.m_head
            ptr2 = evidence.m_head;

            // setting counter back to 0
            counter = 0;

            // moving sus to next node
            sus = sus->m_next;
        }
    }

    // returning false
    return false;
}


/*
 Name: GetData
 Desc: Returns the data at a specific location in the DNA sequence
 Preconditions: Requires a DNA sequence
 Postconditions: Returns a single char from a node
*/
char DNA::GetData(int nodeNum){
    // create an curr node pointer and set it equal to m_head
    Node *curr = m_head;
    char character;
    // creating an number variable and setting it equal to 0
    int number = 0;

    // using an while which will check if the curr is not null if its not then it will enter this loop
    while(curr != nullptr){

        // checking if the nodeNum is equal to number
        if(number == nodeNum){

            // if it is then return curr data
            character = curr->m_data;
        }

        // moving curr to next
        curr = curr->m_next;

        // increasing number
        number++;
    }
    return character;
}


/*
 Name: operator<<
 Desc: Overloaded << operator to return ostream from DNA
 Preconditions: Requires a DNA sequence
 Postconditions: Returns ostream populated from each node
*/
ostream &operator<< (ostream &output, DNA &myDNA){

    // checking if the dna size is = 0, if it is then it will says that there is nothing inside the linked list
    if(myDNA.m_size == 0){
        output << "The linked list is empty! " << endl;
    }else{

        // else it will print out whatever data is there inside the list
        Node *temp = myDNA.m_head;
        while(temp != nullptr){
             output << temp->m_data << "->" ;
            temp = temp->m_next;
        }
        output << "END" << endl;
    }
    return output;
}
