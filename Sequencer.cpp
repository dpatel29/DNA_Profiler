#include "Sequencer.h"
#include"DNA.h"
//Title: sequencer.cpp
//Author: Deval Patel
//Date: 3/26/2021
//Description: Define sequencer.h functions


/*
 Name: Sequencer (constructor)
 Desc: Creates a Sequencer to hold multiple DNA strands from a file
 Preconditions:  None
 Postconditions: A sequencer created to populate m_suspects and m_evidence
*/
Sequencer::Sequencer(string fileName){

    // setting m_fileName value equal to the fileName which is an input of the file name from user.
    m_fileName = fileName;

    // calling readfile function which will read the inputted file
    ReadFile();

    // calling mainmenu function which will give user a list of stuff they can do with the program.
    MainMenu();
}

/*
 Name:  Sequencer (destructor)
 Desc: Deallocates all dynamic aspects of a Sequencer
 Preconditions: There is an existing DNA strand (linked list)
 Postconditions: All vectors are cleared of DNA strands
*/
Sequencer::~Sequencer(){

    // here i am iterating through the suspect vector using an for loop
    for(unsigned int i = 0; i < m_suspects.size(); i++){

        // here i am deleting whatever is there in the vector.
        delete m_suspects.at(i);
    }

    // i am iterating through the evidence vector using an for loop and deleting stuff inside the vector 
    for(unsigned int i = 0; i < m_evidence.size(); i++){
        delete m_evidence.at(i);
    }
}

/*
 Name:  DisplayStrands
 Desc: Displays each strand in both m_suspects and m_evidence
 Preconditions: At least one linked list is in either m_suspects or m_evidence
 Postconditions: Displays DNA strand from one of the vectors
*/
void Sequencer::DisplayStrands(){
    // here i am iterating through suspects vector
    for(unsigned int i = 0; i < m_suspects.size(); i++){

        // here i am printing out how many suspects are there with the data they contain.
        cout << "Suspect " << i+1 << endl;
        cout << *m_suspects.at(i) << endl;
    }

    // here i am iterating through evidence vector
    for(unsigned int j = 0; j < m_evidence.size(); j++){

        // printing out the evidence with the data it contain.
        cout << "Evidence " << j+1 << endl;
        cout << *m_evidence.at(j) << endl;
    }
}


/*
 Name:  ReadFile
 Desc: Reads in a file that has the name on one line then the sequence on the next
       All sequences will be an indeterminate length. There are an indeterminate number of
       sequences in a file. Hint: Read in the entire sequence into a string then go char
       by char until you hit a new line break. Then insert to the correct vector
 Preconditions: Valid file name of characters (Either A, T, G, or C)
 Postconditions: Populates each DNA strand and puts in either m_suspects or m_evidence
*/
void Sequencer::ReadFile(){

    // assigning name variable which will hold name(suspect or evidence)
    string name;

    // this will hold strand information
    string strand;

    // creating an total variable and set it value to 0
    int total = 0;

    // here i am opening the file
    ifstream file;
    file.open(m_fileName);

    // checking if the file is open, if it is open then it will enter the if statement
    if(file.is_open()){

        // here i am using get-line to read through the file
        while(getline(file, name)){
            getline(file, strand);

            // here i am creating an pointed myDna object and setting it equal to the name of DNA
            DNA *myDna = new DNA(name);

            // using an for loop which will iterate through DNA strand
            for (unsigned int i = 0; i < strand.length(); i++) {
                if (strand[i] != ',' && '\n') {

                    // calling an InsertEnd function and inserting the value of i
                    myDna->InsertEnd(strand[i]);
                }
            }
            // here i am checking if the first letter of name is 'S', if it is then it will add that name
            // into an m_suspects vector
            if (name[0] == 'S') {
                m_suspects.push_back(myDna);
                total ++;
            } else{ // if its not 'S' then it will add the name to m_evidence
                m_evidence.push_back(myDna);
                total ++;
            }
        }
        // closing the opened file
        file.close();
    }else{
        cout << "Sorry I am unable to open the file." << endl;
    }
    // printing out how many strands has been loaded from the file
    cout << total << " strands loaded." << endl;
}


/*
 Name:  MainMenu
 Desc: Displays the main menu and manages exiting
 Preconditions: Populated m_suspects and m_evidence
 Postconditions: None
*/
void Sequencer::MainMenu(){

    // creating an variable num which will hold the input value of user
    int num = 0;

    // this loop will get executed if the num is not equal to 4
    while(num != 4) {

        // printing out bunch of different options for the user
        cout << "What would you like to do?" << endl;
        cout << "1. Display Strand" << endl;
        cout << "2. Reverse Sequence" << endl;
        cout << "3. Check Suspects" << endl;
        cout << "4. Exit" << endl;

        // taking an input from user and storing it into num
        cin >> num;
        cout << endl;

        // this loop is for input validation
        while (cin.fail() || num < 1 || num > 4) {
            cout << "What would you like to do?" << endl;
            cout << "1. Display Strand" << endl;
            cout << "2. Reverse Sequence" << endl;
            cout << "3. Check Suspects" << endl;
            cout << "4. Exit" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> num;
            cout << endl;
        }

        // if the user input is 1 then it will display strands
        if (num == 1) {
            DisplayStrands();
            cout << endl;
            cout << endl;
        }

        // if user input is 2 then it will reverse the sequence by calling the function
        if (num == 2) {
            ReverseSequence();
            cout << endl;
            cout << endl;
        }
        // if the user input is 3 then it will call the function CheckSuspects which will check the
        // suspect with the evidence
        if (num == 3) {
            CheckSuspects();
            cout << endl;
            cout << endl;
        }

        // if the user input is 4 then it will exit the program
        if (num == 4) {
            cout << "DNA removed from memory" << endl;
            cout << "Deleting Suspects" << endl;
            cout << "Deleting Evidence" << endl;
            cout << endl;
            cout << endl;
        }
    }
}


/*
 Name:  CheckSuspects
 Desc: Iterates through each DNA strand in m_suspects to see if there is a match from
       m_evidence. Displays each suspect strand where the evidence matches
 Preconditions: Populated m_suspects and m_evidence
 Postconditions: Displays each suspect that has a match
*/


void Sequencer::CheckSuspects(){

    cout << "Checking all suspects vs evidence " << endl;

    // I am using nexted for loops
    // first loop will iterate over suspect vector
    for(unsigned int i = 0; i < m_suspects.size(); i++){

        // this is an bool which will be used if all the suspect match all the evidence
        bool flag = false;

        // this loop will iterate over evidence vector
        for (unsigned int j = 0; j < m_evidence.size(); j++){
            if(m_suspects.at(i)->CompareSequence(*m_evidence.at(j))){
                cout << "Suspect " << i + 1 << " Matched " << "Evidence " << j + 1<< endl;
            }
            else{
                cout << "Suspect " << i + 1 << " does NOT match " << "Evidence " << j + 1<< endl;

                // setting flag equal to true
                flag = true;
            }
        }

        // if flag is false then it will prints that it matches all evidences
        if(flag == false){
            cout << "Suspect " << i+1 << " matches ALL Evidences" << endl;
        }
    }
}


/*
 Name: ReverseSequence
 Desc: User chooses a sequence from m_suspects or m_evidence and the sequence is reversed
 Preconditions: Populated m_suspects and m_evidence
 Postconditions: Reverses a specific sequence replacing in place
*/
void Sequencer::ReverseSequence() {

    // i am assigning bunch of variables which will be used to store the user's input
    int num_evi = 0;
    int num_seq = 0;
    int sus_input;
    int evi_input;
    int num_input;

    // if num_input is less then 1 or greater then 2 then it will re-prompt the user and will take the input
    while (num_input < 1 || num_input > 2) {
        cout << "Which type of sequence to reverse? " << endl;
        cout << "1. Suspect " << endl;
        cout << "2. Evidence " << endl;
        cin >> num_input;

        // this is an input validation loop which will make sure that user input is only 1 and 2, and nothing else
        while (cin.fail() || num_input < 1 || num_input > 2) {
            cout << "Which type of sequence to reverse? " << endl;
            cout << "1. Suspect " << endl;
            cout << "2. Evidence " << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> num_input;
        }

        // if user chose 1 then it will enter this if statement.
        if (num_input == 1) {

            // here i am checking if the size of m_suspect vector is more then or equal to 1 or not
            if (m_suspects.size() >= 1) {

                // if it is then i am increasing num_seq
                for (unsigned int i = 0; i < m_suspects.size(); i++) {
                    num_seq++;
                }

                // here i am giving an option to user to choose a number between 1 and the other number
                cout << "Choose a number between 1 - " << num_seq << endl;
                cin >> sus_input;
                cout << endl;

                // here i am checking if the user input is not less then 1 and not greater then the num_seq, if it is
                // then it will re-prompt the user and ask for the input again.
                while (sus_input < 1 || sus_input > num_seq) {
                    cout << "Choose a number between 1 - " << num_seq << endl;
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> sus_input;
                    cout << endl;
                }
                // here i am reversing the sequence of the whatever suspect user want to reverse
                m_suspects.at(sus_input - 1)->ReverseSequence();
                cout << "Suspect " << sus_input << " has been reversed." << endl;
            }
        }

        // if user chose 2 then it will goes into this if statement.
        if (num_input == 2) {

            // here i am checking if the size of m_evidence vector is more then or equal to 1 or not
            if(m_evidence.size() >= 1) {

                // if it is then i am iterating through that vector and increasing num_evi
                for (unsigned int i = 0; i < m_evidence.size(); i++) {
                    num_evi++;
                }

                // here i am giving an option to user to choose a number between 1 and the other number
                cout << "Choose a number between 1 - " << num_evi << endl;
                cin >> evi_input;
                cout << endl;

                // here i am checking if the user input is not less then 1 and not greater then the num_seq, if it is
                // then it will re-prompt the user and ask for the input again.
                while (evi_input < 1 || evi_input > num_evi) {
                    cout << "Choose a number between 1 - " << num_seq << endl;
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> evi_input;
                    cout << endl;
                }

                // here i am reversing the sequence of the whatever evidence user want to reverse
                m_evidence.at(evi_input - 1)->ReverseSequence();
                cout << "Evidence " << evi_input << " has been reversed." << endl;
            }
        }
    }
}



