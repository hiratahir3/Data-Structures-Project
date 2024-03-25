#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h> // floor()
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void intro()
{	int j,i,c,d;
	for(j=1;j<7;j++)
	{
	
		system("cls");
	for(i=1;i<j;i++)
	{
		cout << "\n" ;
	}
	
	for(i=1;i<j;i++)
	{
		cout << "\t";
	}
	
	}
		cout << "!!!!  Welcome to SCORE RECORDS  !!!!" << endl ;
		cout << "-------------------------------------                                               ------------------------------------------- "  ;
 		for (c = 1; c <= 32767/3; c++)
    	for (d = 1; d <= 32767/3; d++)
		{}
	
	for (c = 1; c <= 32767; c++)
    	for (d = 1; d <= 32767; d++)
		{}
	cout << "\n\n" ;
}


class ScoreBoard {
public:
	
    string colums[15];
    ScoreBoard() {}
    ScoreBoard(string cols[11]){
		for(int i = 0 ; i < 11 ; i++){
        	colums[i] = cols[i]; 
		}

    }
void display( ) {
       for(int i = 0 ; i < 11 ; i++){
        	cout<<colums[i]<<" : "<< colums[i]<<endl; 
		}
			
		cout<<endl;
		
}
	

};
	
struct H_Node
{
    long int key;      // number
    string val[11] ;
  //  ScoreBoard *value; // value
    H_Node *next;   // pointer to remember memory address of next H_Node

    H_Node() : key(0),  next(0){};
    H_Node(long int Key, string *s  ) :  key(Key), next(0){
				
		for(int i = 0 ;  i < 11 ; i ++){
			val[i] = s[i] ;
		}	
	}

};

class HashTable
{
private:
public:
	string sss ;
	long int max ;
	long int *count_n ;
    H_Node **table; // pointer to pointer, hash table
    void tableDoubling();
    void tableShrinking();
    void reHashing(int size_orig);

    int size,     // size: size of table, count: number of dR
        count;    // count/size = load factor
    HashTable(){};
    HashTable(int m) : size(m), count(0) , max(0) 
    {
    	count_n = new long int[size]{} ;
        table = new H_Node *[size]; // allocate the first demension of table
        for (int i = 0; i < size; i++)
            table[i] = 0; // ensure every slot points to NULL
    }
    ~HashTable();

    int hashFunction(int key); // Multiplication method
    void Insert(long int key , string *s , int num); // consider tableDoubling()
    void Delete(long int key);   // consider tableShrinking()
    void Search(string s);
    void display_score_records(long long int);
    void displaysearch(int i,string s , long long int range);

};


void Search(HashTable *ht, string s , long long int range ) {

	int len = sizeof(s);
	long int asci = 0;
		for(int i = 0 ; i < len && s[i] != '\0' ; i++ ){
			if(s[i] != 34){
			if(s[i] < 'd'){
				asci = asci * 10 ;
			}else {
				asci = asci * 100 ;
			}
			asci = asci + int(s[i]) ;
		}
			}
			cout << asci << endl ;
	int key = ht->hashFunction(asci);
	
	ht->displaysearch(key,s , range );		
	
	
}




void HashTable::Insert(long int key  , string *s , int col)
{
    count++;
    if (count > size)
    {                    // consider load factor
        tableDoubling(); // if n/m > 1, then double the size of table
    }

    int index = hashFunction(key); // get index of slot
    H_Node *newNode = new H_Node(key  , s);     // create new H_Node to store data

    // push_front()
    if (table[index] == NULL)
    {                           // eg: list: (empty), add4
        table[index] = newNode; // eg: list: 4->NULL
    }
    else
    {                                    // eg: list: 5->9->NULL  , add 4
        H_Node *next = table[index]->next; //     list: 5->4->9->NULL
        table[index]->next = newNode;
        newNode->next = next;
    }
  count_n[index] ++ ;
  if(max < count_n[index] ){
  max = count_n[index] ;
  sss = table[index]->val[col] ;
  }
 // cout << count_n[index] << " at index  " << s[33] << endl ;
}

void test(HashTable *tr){
	
	cout << tr->sss << endl;
	cout << tr->max << endl ;
	
}

int HashTable::hashFunction(int key)
{
    // Multiplication method
    double A = 0.6180339887, frac = key * A - floor(key * A);
    return floor(this->size * frac);
}

void HashTable::tableDoubling()
{
    int size_orig = size; // size_orig represents the original size of table
    size *= 2;            // double the size of table
    reHashing(size_orig); // create new table with new larger size
}

void HashTable::tableShrinking()
{
    int size_orig = size; // size_orig represents the original size of table
    size /= 2;            // shrink the size of table
    reHashing(size_orig); // create new table with new smaller size
}

void HashTable::reHashing(int size_orig)
{
	long int *newcount = new long int [size] ; 
    H_Node **newtable = new H_Node *[size]; 	
	for (int i = 0; i < size; i++)
    {                    // initializetion
    	newcount[i] = 0 ;
	    newtable[i] = 0; // ensure every H_Node in slot points to NULL
    }

    for (int i = 0; i < size_orig; i++)
    { // visit every H_Node in the original table

        H_Node *curr_orig = table[i], // curr_orig: current H_Node in original table
            *prev_orig = NULL;      // prev_orig: following curr_orig
		
        while (curr_orig != NULL)
        { // traversal in list of each slot in original table
            prev_orig = curr_orig->next; // curr_orig will be directly move to new table
                                         // need prev_orig to keep pointer in original table

            int index = hashFunction(curr_orig->key); // get index of slot in new table

            // push_front(), do not allocate new memory space for data
            // directly move H_Node in original table to new table
            if (newtable[index] == NULL)
            { // means newtable[index] is empty
                newtable[index] = curr_orig;
                newtable[index]->next = 0; // equivalent to curr_orig->next = 0;
            }
            else
            {                                       // if newtable[index] is not empty
                H_Node *next = newtable[index]->next; // push_front()
                newtable[index]->next = curr_orig;
                curr_orig->next = next;
            }
            curr_orig = prev_orig; // visit the next H_Node in list in original table
        	newcount[index] ++ ;
		}
    }
    delete [] count_n ;
    this->count_n = newcount ;
    delete[] table;         // release memory of original table
    this->table = newtable; // point table of object to new table
}

HashTable::~HashTable()
{
    for (int i = 0; i < size; i++)
    {                             // visit every H_Node in table and release the memory of each H_Node
        H_Node *current = table[i]; // point *current to first H_Node in list
        while (current != NULL)
        { // traversal in list
            H_Node *previous = current;
            current = current->next;
            delete previous;
            previous = 0;
        }
    }
    delete[] table;
}

void HashTable::display_score_records(long long int lmop)
{
	int k=0;
	
    for (int i = 0; i < size; i++)
    { // visit every H_Node in table
        H_Node *current = table[i];
        while (current != NULL && k<lmop)
        {
            for(int j = 0 ; j < 11 ; j++){
            	cout << current->val[j] << "    "  ;
			}
			cout <<endl ;
            current = current->next;
            k++;
        }
        cout << endl;
    }
    cout << endl;
}

void HashTable::displaysearch(int i,string s , long long int range ){
	int count = 0;
	H_Node *current = table[i];
        while (current != NULL && count < range)
        {
            for(int j = 0 ; j < 11 ; j++){
            	cout << current->val[j] << "    "  ;
			}
			cout <<endl ;
			count++;
            current = current->next;
        }
        cout << endl ;
	
	cout<<endl<<endl;
	
	
//	cout<<"The Total Number of "<<s<<" is : "<<count;
	
}

void insert_t(vector<ScoreBoard>& score ,HashTable *ht , int col  ,long long int range ){

	string s ;
	long long int j = 0 ;
	for(auto sub_data : score ){
	long int asci = 0 ;
		if(j != 0){
		int len = sizeof(sub_data.colums[col]) ;
		s = sub_data.colums[col] ;
		for(int i = 0 ; i <= len && s[i] != '\0' ; i++ ){
			if(s[i] != 34){
			if(s[i] < 'd'){
				asci = asci * 10 ;
			}else {
				asci = asci * 100 ;
			}
			asci = asci + int(s[i]) ;
		}
			}	
		ht->Insert(asci , sub_data.colums ,col );

	}
		j++ ;
		if(j > range){
			break ;
		}
	}
	
}  

	
int main(){
	
	intro() ;
    int n , flag = 1;
  	string sss ;
	int s ;
	long long int range ;
	HashTable *hash = new HashTable (11) ;
	ifstream inputFile;
    inputFile.open("Submissions.csv");
    string line  , opt ;
	int k = 0 ;
    vector<ScoreBoard> score ;
    while (getline(inputFile, line) ) {
		string colums[11] ;
		int i=0;
        stringstream inputString(line);
		for(i=0;i<11;i++){
        	getline(inputString, colums[i], ',');
		}	
        ScoreBoard sub_data(colums);
        score.push_back(sub_data);
        line = "";\
        
    }
    
    do{
    	
    system("cls") ;	
    cout << "------------------SCORES RECORDS--------------------" << endl ;
    cout << "1. Search records of a particular date " << endl ;
    cout << "2. Submitted scores after the deadline " << endl ;
    cout << "3. Print all the records " << endl ;
    cout << "4. Exit " << endl ;
    cin >> n ;
    switch (n){
    	case 1:
    		system("cls") ;
			cout << "0. ID" << endl ;	
			cout << "1. SUBMITTED USER ID " << endl ;	
		    cout << "2. TEAM ID " << endl ;	
		    cout << "3. SOURCE KERNEL VERSION ID " << endl ;
			cout << "4. SUBMISSION DATE " << endl ;
			cout << "5. SCORE DATE " << endl << "6. IS AFTER DEADLINE " << endl << "7. PUBLIC SCORE LEADER BOARD DISPLAY "<< endl << "8. PUBLIC SCORE FULL PRECISION "<< endl << "9. PRIVATE SCORE LEADER BOARD DISPLAY " << endl  ;		
			cout << "10. PRIVATE SCORE FULL PRECISION  " << endl ;
	   		
	    	cout << "Enter the number of rows you want to display " <<endl ;
	    	cin >> range ;
	    	insert_t(score , hash , 4 , 50000 ) ;
	    	cout << "Enter the valid date in the correct format --------------- i.e 09/14/2012 " << endl ;
	  		cin >> sss ;
	  		Search(hash , sss , range) ;
  	
    		break ;
    		
    	case 2:
    		system("cls") ;
			cout << "Following are the records submitted after the deadline " << endl ;
			cout << "Enter the number of records  " << endl  ;
	    	cin >> range ;
	    	insert_t(score , hash , 6 , 50000 ) ;
	  		Search(hash , "False" , range )  ;
    		
    		break ;
    	case 3:
    		system("cls") ;
			cout << "Enter the column choice " << endl  ;
		    cin >> s ;    		
	    	cout << "Enter the number of rows you want to display " <<endl ;
	    	cin >> range ;

    		insert_t(score , hash , s , range ) ;
   			hash->display_score_records(range) ;
    		break ;
    	case 4 :
    		flag = 0 ;
			break ;	
    	default :
    		cout << "---------  Invalid Input  -------  " << endl ;
    		break ;
    	
	}
	if(flag == 1){
	string obt ;
	cout << "Enter any key to continue : " << endl ;
	cin >> obt ;
	}
 }while(n != 4 ) ;
	
	cout << "--------------------------------------THANKS FOR VISITING ----------------------------------------------- "  << endl ;
    
	return 0 ;
}










