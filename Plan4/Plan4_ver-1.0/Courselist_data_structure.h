#include <cstdlib>
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <algorithm>
#include <map>
#include <windows.h>
using namespace std;

//prints divider for sectioning
void print_divider(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	for(int i= 0;i<=columns;i++){
		cout<<"-";
	}
	cout<<endl;
}
//shorter version
void print_divider_short(){
	int columns = 40;
	for(int i= 0;i<=columns;i++){
		cout<<"-";
	}
	cout<<endl;
}


//global datatypes
enum CoreType{ No, Data_and_Discovery, Structures_of_thought_and_society, Art_Design_and_Technology, Cultural_Exploration_and_Analysis};
map<CoreType, string> enum_Coretype = {{No, "No"}, {Data_and_Discovery, "Data and Discovery"},{Structures_of_thought_and_society, "Structures of Thought and Society"}, {Art_Design_and_Technology, "Art, Design and Technology"}, {Cultural_Exploration_and_Analysis, "Cultural Exploration and Analysis"}};
enum exreq{ none, QR, IS, EI};
map<exreq, string> enum_exreq = {{none, "No"}, {QR, "Quantitative Reasoning"},{IS, "Islamic Studies"}, {EI, "Experimental Inquiry"}};
enum sem{Fall, Spring, Jterm, Summer};
map<sem, string> enum_sem = {{Fall, "Fall"}, {Spring, "Spring"},{Jterm, "J-Term"}, {Summer, "Summer"}};
map<int, string> enum_yn = {{1, "Yes"}, {0, "No"}};


//it stores information abotu all the graduation requirements in an class
class Requirements{
	public:		
		int COLL_count = 0;
		int MajorReq_count = 0;
		int FYS_count = 0;
		int IS_count = 0;
		int QR_count = 0;
		int EI_count = 0;
		int credits_count = 0;
		int CORE_count = 0;
		int DAD_count = 0;
		int STS_count = 0;
		int ADT_count = 0;
		int CEA_count = 0;
		int course_count = 0;
		vector < pair<string, int> > getmap();	
		void print();
};
vector < pair<string, int> > Requirements::getmap(){
//maps some phrases to all t he requirements to help print stuff
	  vector < pair<string, int> > Grad_Req_array = {{"Total Credits", this->credits_count}, {"Number of Courses", this->course_count},{"Credit Requirement for Major", this->MajorReq_count},{"First Year Writing Seminar", this->FYS_count},{"Islamic Studies", this->IS_count},
			{"Quantitative Reasoning",this->QR_count}, {"Experimental Inquiry", this->EI_count}, {"Core",this->CORE_count},{"Data and Discovery", this->DAD_count},
			{"Structures of Thought and Society", this->STS_count }, {"Art, Design and Technology", this->ADT_count}, {"Cultural Exploration and Analysis", this->CEA_count}, 
			{"Colloquim", this->COLL_count}};
	return(Grad_Req_array);
}

//prtints requirements
void Requirements::print(){
	print_divider_short();
	cout<<"1. Total Credits: "<<this->credits_count<<endl;
	cout<<"1. Number of Courses: "<<this->course_count<<endl;
	cout<<"2. Major Requirements Credits: "<<this->MajorReq_count<<endl;
	cout<<"3. First Year Writing Seminar: "<<this->FYS_count<<endl;
	cout<<"4. Islamic Studies Requirement: "<<this->IS_count<<endl;
	cout<<"5. Quantitative Reasoning Requirement: "<<this->QR_count<<endl;
	cout<<"6. Experimental Inquiry Requirement: "<<this->EI_count<<endl;
	cout<<"7. Core Requirements: "<<this->CORE_count<<endl;
	cout<<"	Data and Discovery Requirement: "<<this->DAD_count<<endl; 
	cout<<"	Structures of Thought and Society Requirement: "<<this->STS_count<<endl; 
	cout<<"	Art, Design and Technology Requirement: "<<this->ADT_count<<endl; 
	cout<<"	Cultural Exploration and Analysis Requirement: "<<this->CEA_count<<endl; 
	cout<<"8. Colloquim: "<<COLL_count<<endl;
}


//class object to store the settings of the user
class settings{
public:
	string Name;
	string Major;
	int Year_count;
	int const jterm_count = 3;
	int const summer = 3;
	void read(ifstream* fptr);
	void print();
	Requirements * static_req = new Requirements;
};

//reading setting from a file
void settings::read(ifstream* fptr){
	string name;
	string getline;
	while(*fptr>>name){
		this->Name = name;
		*fptr>>this->Major;
		*fptr>>this->Year_count;
		(*fptr).ignore((numeric_limits<streamsize>::max)(),':');
		*fptr>>this->static_req->COLL_count;
		(*fptr).ignore((numeric_limits<streamsize>::max)(),':');
		*fptr>>this->static_req->MajorReq_count;
		(*fptr).ignore((numeric_limits<streamsize>::max)(),':');
		*fptr>>this->static_req->FYS_count;
		(*fptr).ignore((numeric_limits<streamsize>::max)(),':');
		*fptr>>this->static_req->IS_count;
		(*fptr).ignore((numeric_limits<streamsize>::max)(),':');
		*fptr>>this->static_req->QR_count;
		(*fptr).ignore((numeric_limits<streamsize>::max)(),':');
		*fptr>>this->static_req->EI_count;
		(*fptr).ignore((numeric_limits<streamsize>::max)(),':');
		*fptr>>this->static_req->credits_count;
		(*fptr).ignore((numeric_limits<streamsize>::max)(),':');
		*fptr>>this->static_req->CORE_count;
		(*fptr).ignore((numeric_limits<streamsize>::max)(),':');
		*fptr>>this->static_req->DAD_count;
		(*fptr).ignore((numeric_limits<streamsize>::max)(),':');
		*fptr>>this->static_req->STS_count;
		(*fptr).ignore((numeric_limits<streamsize>::max)(),':');
		*fptr>>this->static_req->ADT_count;
		(*fptr).ignore((numeric_limits<streamsize>::max)(),':');
		*fptr>>this->static_req->CEA_count;
		(*fptr).ignore((numeric_limits<streamsize>::max)(),':');
		*fptr>>this->static_req->course_count;



	}
}

//prints setting on screen
void settings::print(){
	cout<<"Settings"<<endl;
	print_divider_short();
	cout<<"Name: "<<this->Name<<endl;
	cout<<"Major: "<<this->Major<<endl;
	cout<<"Years: "<<this->Year_count<<endl;
	cout<<endl;
	cout<<"Graduation Requirements: "<<endl;
	this->static_req->print(); 
}



//COURSE Noderand method definitions
class Course{
public:
	string Name = "XX";
	string CourseCode = "xx";
	int cred = 0;
	CoreType Core = No;
	exreq extrareq = none;
	bool Coll = 0;
	bool FYS = 0;
	bool MajorReq = 0; 
	bool GenElec = 0;
	int Year = 0;
	sem Semester = Fall;
	Course *next = NULL;
	Course *prev = NULL;
	void write_infile(ofstream* fptr);
	void print();
	void display();
};

//displays all teh elements in a course
void Course::display(){
	print_divider_short();
	cout<<" Course Name: "<<this->Name<<endl;
	cout<<" Course Code: "<<this->CourseCode<<endl;
	cout<<" Credits: "<<this->cred<<endl;
	cout<<" Core: " <<enum_Coretype[this->Core]<<endl;
	cout<<" Miscellaneous Requirements: "<<enum_exreq[this->extrareq]<<endl;
	cout<<" Colloquim: "<<enum_yn[Coll]<<endl;
	cout<<" First Year Writing Seminar: "<< enum_yn[this->FYS]<<endl;
	cout<<" Major Requirement: "<<enum_yn[this->MajorReq]<<endl;
	cout<<" General Elective; "<<enum_yn[this->GenElec]<<endl;
	cout<<" Year: "<<this->Year<<endl;
	cout<<" Semester: "<<enum_sem[this->Semester]<<endl;
	print_divider_short();
	cout<<endl;
}

//writes teh coursei n file
void Course::write_infile(ofstream* fptr){
	*fptr<<1<<endl;
	*fptr<< this->Name<<endl;
	*fptr<<this->CourseCode<<endl;
	*fptr<<this->cred <<" "<< this->Core << " "<<this->extrareq <<" "<< this->Coll<< " "<< this->FYS;
	*fptr<<" "<<this->MajorReq << " "<< this->GenElec << " "<< this->Year <<" "<< this->Semester <<endl;
}

//print them as they ared
void Course::print(){
	print_divider_short();
	cout<< this->Name<<" "<< this->CourseCode<<" "<< this->cred <<" "<< this->Core << " "<<this->extrareq <<" "<< this->Coll<< " "<< this->FYS;
	cout<<" "<<this->MajorReq << " "<< this->GenElec << " "<< this->Year <<" "<< this->Semester << endl;
}

// Semlist Class and method defintions
class semlist{
public:
	Course *head = NULL;
	void add_front(Course* ptr);
	void write_infile(ofstream* fptr);
	void read(ifstream* fptr);
	void print();
	bool isend(Course* cur);
	int print_year(int yr);
	int check(int year);
	Course * search(string);
	Requirements* search(Requirements * user);
};

//searches the lined list
Course * semlist::search(string name){
		cout<<"entered"<<endl;
		Course * cur = this->head;
		if(cur==NULL){
			cout<<"NULL"<<endl;
			return(NULL);
			
		}
		if (cur->next == cur ){
			if (cur->Name == name){
				
				return(cur);
			}
			else{
				
				return(NULL);
			}
		}
		do {

			if (cur->Name == name){
				cout<<"MORE"<<endl;
				return(cur);
			}
			cur= cur->next;
		}while(cur!=NULL);
		cout<<"Not Found! :("<<endl;
		return(NULL);
}


//checks if a course of vertain year is in teh linked list
int semlist::check(int year){
	Course* cur = this->head;

	int count=0;
	if( cur == NULL){
		return (count);
	}
	if(cur->next == cur){
		if (cur->Year == year){
			count++;
			return(count);
		}
	}
	do{
		if (cur->Year == year){
			count++;
		}
		cur= cur->next;
	}while(cur!=head);
	return(count);
}

//searches if the course meets the requirements for graduation
Requirements* semlist::search(Requirements * user){
	Course* cur = this->head;
	if (head == NULL){
		return(user);
	}
	do{
		user->course_count++;
		user->credits_count = user->credits_count + cur->cred;
		if(cur->Core == 2){
			user->DAD_count++;
			user->CORE_count++;
		}
		else if(cur->Core == 3){
			user->STS_count++;
			user->CORE_count++;
		}
		else if(cur->Core == 4){
			user->ADT_count++;
			user->CORE_count++;
		}
		else if(cur->Core == 5){
			user->CEA_count++;
			user->CORE_count++;
		}

		if(cur->FYS == true){
			user->FYS_count++;
		}
		if(cur->extrareq == 2){
			user->IS_count++;
		}
		if(cur->extrareq == 3){
			user->QR_count++;
		}
		if(cur->extrareq == 4){
			user->EI_count++;
		}
		if(cur->MajorReq == true){
			user->MajorReq_count = user->MajorReq_count + cur->cred;
		}
		if(cur->Coll == true){
			user->COLL_count++;
		}
		
		cur = cur->next;
	}while(cur!=head);
	return(user);
}

//prints teh course of a given year in the specific linked list
int semlist::print_year(int yr){
	Course* cur = this->head;
	int count = 0;
	if (head == NULL){
		return(0);
	}
	if (head->next == head){
		if(cur->Year == yr){
			cout<<"		";
			cout<<count+1<<". "<<cur->Name<<endl;
			count++;
		}
			return(count);
	}
	do{
		if(cur->Year == yr){
			cout<<"		";
			cout<<count+1<<". "<<cur->Name<<endl;
			count++;
		}
		cur = cur->next;
	}while(cur!=head);
	return(count);

}

bool semlist::isend(Course* cur){
	return(cur == NULL);
}

//reads courses from file
void semlist::read(ifstream *fptr){
	int flag;
	streampos current = fptr->tellg();
	fptr->seekg(0, (*fptr).end);
	bool empty = !fptr->tellg(); // true if empty file
	fptr->seekg (current, fptr->beg);
	if (empty){
		return;
	}
	while(*fptr >> flag){
		Course * addcur = new Course;
		int get;
		getline(*fptr>>ws, addcur->Name);
		getline(*fptr>>ws, addcur->CourseCode);
		*fptr >> addcur->cred;
		 *fptr >> get;
		addcur->Core = static_cast<CoreType>(get);
		*fptr >> get;
		addcur->extrareq = static_cast<exreq>(get);
		*fptr>>addcur->Coll>>addcur->FYS>>addcur->MajorReq>>addcur->GenElec>>addcur->Year;
		*fptr >> get;
		addcur->Semester = static_cast<sem>(get);
		this->add_front(addcur);
	}
}

//adds course to the linked list
void semlist::add_front(Course* crptr){
	if(head == NULL){
		head = crptr;
		crptr->next = crptr;
		crptr->prev = crptr;
	}
	else if (head->next == head){
		crptr->next = this->head->next;
		crptr->prev = this->head->prev;
		head->next = crptr;
		head->prev = crptr;
		this->head = crptr;
	}
	else{
		crptr->next = this->head;
		crptr->prev = this->head->prev;
		head->prev->next = crptr;
		head->next->prev = crptr;
		head = crptr;
	}
}

//writes in the linked list into a file
void semlist::write_infile(ofstream* fptr){
	Course *cursor = head;
	if (head==NULL){
		*fptr<<"Empty"<< endl;
		return;
	}
	if(head->next == head){
		cursor->write_infile(fptr);
		return;
	}
	do{
		cursor->write_infile(fptr);
		cursor = cursor->next;
	}while (cursor!=head);
}

//prints the linked list on the screen
void semlist::print(){
	Course *cursor = head;
	if (head ==NULL){
		cout<<"Empty"<< endl;
		return;
	}
	if(head->next == head){
		cursor->print();
		return;
	}
	do{
		cursor->print();
		cursor = cursor->next;
	}while (cursor!= head);
}