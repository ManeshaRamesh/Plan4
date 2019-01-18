#include <cstdlib>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <iomanip> 
#include "Courselist_data_structure.h"
using namespace std;




//Function Declarations
void print_divider_short();
Course* create(int yr, sem, semlist * fall, semlist * spring, semlist * jterm, semlist * summer);
void view(semlist list1, semlist list2);
void load_courses(semlist * fall, semlist* spring, semlist *jterm, semlist *summer);
settings* load_settings();
int add_another_course();
void print_requirements_table(settings* fixed_require, Requirements* user_require,semlist* list1, semlist* list2, semlist* list3, semlist* list4);
void edit(semlist * fall, semlist * spring, semlist * jterm, semlist * summer);
void edit_course(Course * edit_c, semlist* fall, semlist * spring, semlist * jterm, semlist * summer);
void main_menu(int i, semlist* fall, semlist* spring, semlist* jterm, semlist* summer);
int main_menu_display();
int edit_menu(semlist * fall, semlist * spring, semlist * jterm, semlist * summer);
void add_course(semlist* fall, semlist* spring, semlist* jterm, semlist* summer);

//Function Definitions


//this function is for menus, checks if the input is incorrect and within the bounds of the options provided. 
int input_error(int x, int lowb, int highb){

	while ( (!(cin>> x )) || (x<lowb )|| (x>highb)) {
  		cerr<<"Invalid input."<<endl;
  		cin.clear();
  		cin.ignore (numeric_limits<streamsize>::max(), '\n' );
  		cout<<"Enter again: ";
	}
	return x;
}

//this function checks of incorrect input for yes and no user inputs
char input_error_yn(char i){
	cin>>i;

	while( (!cin) && (i!='Y') && ( i!='N')){
		cout<< i<<endl;
		cerr<<"Invalid input."<<endl;
		cin.clear();
		cin.ignore (numeric_limits<streamsize>::max(), '\n' );
		cout<<"Enter again: ";
		cin >> i;
	}

	return (toupper(i));
}

//converts 'y' ad 'n' to bool values and returns them 
int yn(char c){
	if(toupper(c) == 'Y'){
		return  1;
	}
	else if(toupper(c) == 'N'){
		return 0;
	}
	else{
		cout<<"'"<<c<<"' is not a recognized character."<<endl;
		return(-1);
	}
}

//this function is called when a course in the four year plan is being edited
void edit_course(Course * edit_c, semlist* fall, semlist * spring, semlist * jterm, semlist * summer){
	//declaring variables
	//intermediate varaiable for data type casting user input
	int user;
	//an intermediate varaible for char to bool conversions
	char bool_yn;

	sem semestertype;

	//course edit form
	cout<<"Course Name: "<<edit_c->Name<<endl;; 
	cout<<"Enter Course Name:"; 
	getline(cin>>ws, edit_c->Name);

	cout<<"Course Code: "<<edit_c->CourseCode<<endl;
	cout<<"Enter Course Code: ";
	getline(cin>>ws, edit_c->CourseCode);

	cout<<"Course credits:"<< edit_c->cred<<endl;
	cout<<"Enter the course credits:";
	cin>>edit_c->cred;

	cout<<"Is this a Core? (y/n): "<<enum_Coretype[edit_c->Core]<<endl;
	cout<<"1. No"<<endl;
	cout<<"2. Data and Discovery"<<endl;
	cout<<"3. Structures of thought and society"<<endl;
	cout<<"4. Art, Design and Technology"<<endl;
	cout<<"5. Cultural Exploration and Analysis"<<endl;
	cout<<"Enter number:";
	user = input_error(user, 1, 5);
	edit_c->Core = static_cast<CoreType>(user);


	cout<<"Does it meet the following requirements? (y/n): "<< enum_exreq[edit_c->extrareq]<<endl;
	cout<<"1. No"<<endl;
	cout<<"2. Quantitative Reasoning"<<endl;
	cout<<"3. Islamic Studies"<<endl;
	cout<<"4. Experimental Inquiry"<<endl;
	cout<<"Enter Number: "<<endl;
	user = input_error(user, 1, 5);
	edit_c->extrareq = static_cast<exreq>(user);



	cout<<"Is it a Colloquim? (y/n):"<< enum_yn[edit_c->Coll]<<endl;
	cin>>bool_yn;
	while(yn(bool_yn) == -1){
		cout<<"Please enter again!: ";
		cin>>bool_yn;
	}
	edit_c->Coll = yn(bool_yn);

	cout<<"Is it a First Year Writing Seminar? (y/n):"<<enum_yn[edit_c->FYS]<<endl;
	cin>>bool_yn;
	while(yn(bool_yn) == -1){
		cout<<"Please enter again!: ";
		cin>>bool_yn;
	}
	edit_c->FYS = yn(bool_yn);

	cout<<"Is it a Major Requirement? (y/n):"<<enum_yn[edit_c->MajorReq]<<endl;
	cin>>bool_yn;
	while(yn(bool_yn) == -1){
		cout<<"Please enter again!: ";
		cin>>bool_yn;
	}
	edit_c->MajorReq = yn(bool_yn);

	cout<<"Is it a General Elective? (y/n):"<<enum_yn[edit_c->GenElec]<<endl;
	cin>>bool_yn;
	while(yn(bool_yn) == -1){
		cout<<"Please enter again!: ";
		cin>>bool_yn;
	}
	edit_c->GenElec = yn(bool_yn);

	cout<<"Enter year number:"<<edit_c->Year<<endl;
	int yr;
	cin>>yr;
	while(yr<1 || yr>4){
		cout<<"Invalid year. Enter Again!: ";
		cin>>yr;
	}

	edit_c->Semester = semestertype;


}

//this function is called when a new course is created. 
Course* create(int yr, sem semestertype, semlist * fall, semlist * spring, semlist * jterm, semlist * summer){
	int user;
	 // form
	
	Course * ptr = new Course;

	cout<<"Enter Course Name:"; 
	string str_name;
	getline(cin>>ws, str_name);
	transform(str_name.begin(), str_name.end(),str_name.begin(), ::toupper);
	ptr->Name = str_name;
	cout<<"Enter Course Code:";
	string str_code;
	getline(cin>>ws , str_code);
	transform(str_code.begin(), str_code.end(),str_code.begin(), ::toupper);
	ptr->CourseCode = str_code;

	cout<<"Enter the course credits:";
	cin>>ptr->cred;

	cout<<"Is this a Core?:"<<endl;
	cout<<"1. No"<<endl;
	cout<<"2. Data and Discovery"<<endl;
	cout<<"3. Structures of thought and society"<<endl;
	cout<<"4. Art, Design and Technology"<<endl;
	cout<<"5. Cultural Exploration and Analysis"<<endl;

	cin>>user;
	ptr->Core = static_cast<CoreType>(user);


	cout<<"Does it meet the following requirements?:"<<endl;
	cout<<"1. No"<<endl;
	cout<<"2. Quantitative Reasoning"<<endl;
	cout<<"3. Islamic Studies"<<endl;
	cout<<"4. Experimental Inquiry"<<endl;
	cin>>user;
	ptr->extrareq = static_cast<exreq>(user);


	char bool_yn;
	cout<<"Is it a Colloquim? (y/n):";
	cin>>bool_yn;
	while(yn(bool_yn) == -1){
		cout<<"Please enter again!: ";
		cin>>bool_yn;
	}
	ptr->Coll = yn(bool_yn);

	cout<<"Is it a First Year Writing Seminar? (y/n):";
	cin>>bool_yn;
	while(yn(bool_yn) == -1){
		cout<<"Please enter again!: ";
		cin>>bool_yn;
	}
	ptr->FYS = yn(bool_yn);

	cout<<"Is it a Major Requirement? (y/n):";
	cin>>bool_yn;
	while(yn(bool_yn) == -1){
		cout<<"Please enter again!: ";
		cin>>bool_yn;
	}
	ptr->MajorReq = yn(bool_yn);

	cout<<"Is it a General Elective? (y/n):";
	cin>>bool_yn;
	while(yn(bool_yn) == -1){
		cout<<"Please enter again!: ";
		cin>>bool_yn;
	}
	ptr->GenElec = yn(bool_yn);

	ptr->Year = yr;	

	ptr->Semester = semestertype;
	//returns pointer to the newly created course
	return (ptr);
}

//this function is called to print out the four year plan
void view(semlist* list1, semlist* list2, semlist* list3, semlist* list4){
	int settings = 4;
	int count = 1;
	for(int i = 0; i<4;i++){
		cout<<endl;
	}
	cout<<"FOUR YEAR PLAN!! :)"<<endl;
	for(int i = 0; i<4;i++){
		cout<<endl;
	}

	while(count<=settings){
		print_divider_short();
		cout<<"YEAR"<<count<<endl;
		cout<<"	FALL"<<endl;
		if(list1->print_year(count) == 0){
			cout<<"		"<<"TO BE ADDED"<<endl;
		}
		cout<<endl;
		cout<<"	J-Term"<<endl;
		if(list2->print_year(count) == 0){
			cout<<"		"<<"TO BE ADDED"<<endl;
		}
		cout<<endl;

		cout<<"	SPRING"<<endl;
		if(list3->print_year(count) == 0){
			cout<<"		"<<"TO BE ADDED"<<endl;
		}
		cout<<endl;
	
		cout<<"	SUMMER"<<endl;
		if(list4->print_year(count) == 0){
			cout<<"		"<<"TO BE ADDED"<<endl;
		}
		count++;
		cout<<endl;
	}

}

//loads all teh courses from the files into the linked list datastructures
void load_courses(semlist * fall, semlist* spring, semlist *jterm, semlist *summer){
	ifstream infile; 
	ifstream* infileptr = &infile;
	infile.open("FALL.txt");
	fall->read(infileptr);
	infile.close();
	
	infile.open("SPRING.txt");
	spring->read(infileptr);
	infile.close();

	infile.open("JTERM.txt");
	jterm->read(infileptr);
	infile.close();

	infile.open("SUMMER.txt");
	summer->read(infileptr);
	infile.close();
}

//once the program starts, the infomation about the user and NYUAD requirements is loaded from the file and into an obkect
settings* load_settings(){
	settings * Set = new settings;
	ifstream load_settings;
	load_settings.open("SETTINGS.txt");
	ifstream* settingsptr = &load_settings;
	Set->read(settingsptr);
	load_settings.close();
	return(Set);
}

//adds another course to the four year plan
int add_another_course(){
	int i;
	for(int j = 0; j<2; j++){
		cout<<endl;
	}
	print_divider_short();
	cout<<"Would like to add another course?:"<<endl;
	cout<<"1. Yes"<<endl;
	cout<<"2. No"<<endl;
	cin>>i;
	return(i);
}

//the function prints a table with the user's fulfilled requirements, the university's requirements and the requirements that need to be fulfilled
void print_requirements_table(settings* fix_req, Requirements* user_require,semlist* list1, semlist* list2, semlist* list3, semlist* list4){
	list1->search(user_require);
	list2->search(user_require);
	list3->search(user_require);
	list4->search(user_require);


	cout<<"Graduation Requirements:"<<endl;
	cout<< setw(35)<<left<<"REQUIREMENTS" << setw(35)<<left<<"FULFILLED"<< setw(35)<<left<< "MINIMUM" << setw(35)<<left<<"NEEDED"<< endl;
	print_divider_short();
	vector < pair<string, int> > req_map = user_require->getmap();
	vector < pair<string, int> > fix_req_map = fix_req->static_req->getmap();
		int difference = 0;
	for(int i = 0; i<req_map.size(); i++){
		difference = fix_req_map[i].second - req_map[i].second;
		if (difference < 0){difference = 0;}
	 	cout<< setw(35)<<left<<req_map[i].first <<setw(35)<<left<<req_map[i].second<<setw(35)<<left<<fix_req_map[i].second<< setw(35)<<left<<difference<<endl;

	}

}

//this function displays the menu options for editing teh four year plan
int edit_menu(semlist * fall, semlist * spring, semlist * jterm, semlist * summer){
	view(fall, jterm, spring, summer);
	int userinput;
	print_divider_short();
	for( int i = 0; i<3;i++){
		cout<<endl;
	}
	cout<<"What would you like to do?"<<endl; 
	cout<<"1. Add a course to your four year plan"<<endl;
	cout<<"2. View and edit a specific course"<<endl;
	cout<<"3. Return to main menu"<<endl;
	cout<<"4. Exit"<<endl;
	cout<<"Enter number: ";
	userinput = input_error(userinput, 1, 4);
	return(userinput);
}

//this function provides teh functionality to each of the options in the above menu
void edit(semlist * fall, semlist * spring, semlist * jterm, semlist * summer){
	int userin = edit_menu(fall, spring, jterm, summer);
	switch(userin){
		//for adding courses
		case 1:
		{
			add_course(fall, spring, jterm, summer);
			break;
		}
		//for viewing and editing a course
		case 2:
		{	//asks which year and semester
			int yr;
			cout<<"Which year?: "<<endl;
			cout<<"Enter year number: ";
			cin>>yr;
			int choice;
			cout<<"Which semester?: "<<endl;
			cout<<"1. Fall"<<endl;
			cout<<"2. Spring"<<endl;
			cout<<"3. J-Term"<<endl;
			cout<<"4. Summer"<<endl;
			cout<<"5. Exit"<<endl;
			cout<<" Enter number: ";
			choice = input_error(choice, 1, 5);	
			switch(choice){
				//fall semester
				case 1:{

					Course * edit_c;
					string course_name;
					char yn;	
					//prints all the courses in the provided semester and year		
					if (fall->print_year(yr)){
						//searches for the course
						cout<<"Which course?"<<endl;
						cout<<"Enter a course name: ";
						do{//seaeches for the course
							getline(cin>>ws, course_name);
							transform(course_name.begin(), course_name.end(),course_name.begin(), ::toupper);
							edit_c = fall->search(course_name);
							if (edit_c == NULL){
								cout<<"NOT FOUND :(";
								cout<<"Please try again!"<<endl;
							}
						}while(edit_c == NULL);
						//displays everything about the selected course
						edit_c->display();
						//asks if the course needs to be edited
						cout<<"Do you wish to edit this course? (y/n):";
						yn = input_error_yn(toupper(yn));
						switch(toupper(yn)){
							case 'Y':
							{	//calls the edit function and updates the file
								ofstream outfile;
								outfile.open("FALL.txt");
								ofstream* outfileptr = &outfile;
								edit_course(edit_c, fall, spring, jterm, summer);
								fall->write_infile(outfileptr);
								outfile.close();
								break;

							}
							case 'N':
							{
								break;
							}
						}
						

					}
					else{cout<<"TO BE ADDED"<<endl;}
					break;
				}
				//spring
				case 2:{
					Course * edit_c;
					string course_name;
					char yn;			
					if (spring->print_year(yr)){
						
						cout<<"Which course?"<<endl;
						cout<<"Enter a course name: ";
						do{
							getline(cin>>ws, course_name);
							transform(course_name.begin(), course_name.end(),course_name.begin(), ::toupper);
							edit_c = spring ->search(course_name);
							if (edit_c == NULL){
								cout<<"NOT FOUND :("<<endl;
								cout<<"Please try again!"<<endl;
							}
						}while(edit_c == NULL);
						edit_c->display();
						cout<<"Do you wish to edit this course? (y/n):";
						yn = input_error_yn(toupper(yn));
						switch(toupper(yn)){
							case 'Y':
							{
								ofstream outfile;
								outfile.open("SPRING.txt");
								ofstream* outfileptr = &outfile;
								edit_course(edit_c, fall, spring, jterm, summer);
								spring->write_infile(outfileptr);
								outfile.close();
								break;

							}
							case 'N':
							{
								break;
							}
						}
						

					}
					else{cout<<"TO BE ADDED"<<endl;}
					break;
				}
				//jterm
				case 3:{
					Course * edit_c;
					string course_name;
					char yn;			
					if (jterm->print_year(yr)){
						
						cout<<"Which course?"<<endl;
						cout<<"Enter a course name: ";
						do{
						cin>> course_name;
						transform(course_name.begin(), course_name.end(),course_name.begin(), ::toupper);
						edit_c = jterm->search(course_name);
							if (edit_c == NULL){
								cout<<"NOT FOUND :(";
								cout<<"Please try again!"<<endl;
							}
						}while(edit_c == NULL);
						edit_c->display();
						cout<<"Do you wish to edit this course? (y/n):";
						yn = input_error_yn(toupper(yn));
						switch(toupper(yn)){
							case 'Y':
							{
								ofstream outfile;
								outfile.open("JTERM.txt");
								ofstream* outfileptr = &outfile;
								edit_course(edit_c, fall, spring, jterm, summer);
								jterm->write_infile(outfileptr);
								outfile.close();
								break;

							}
							case 'N':
							{
								break;
							}
						}
						

					}
					else{cout<<"TO BE ADDED"<<endl;}
					break;
				}
				//summer
				case 4: {
					Course * edit_c;
					string course_name;
					char yn;			
					if (summer->print_year(yr)){
						
						cout<<"Which course?"<<endl;
						cout<<"Enter a course name: ";
						cin>> course_name;
						transform(course_name.begin(), course_name.end(),course_name.begin(), ::toupper);
						edit_c = summer->search(course_name);
						edit_c->display();
						cout<<"Do you wish to edit this course? (y/n):";
						yn = input_error_yn(toupper(yn));
						switch(toupper(yn)){
							case 'Y':
							{
								ofstream outfile;
								outfile.open("SPRING.txt");
								ofstream* outfileptr = &outfile;
								edit_course(edit_c, fall, spring, jterm, summer);
								summer->write_infile(outfileptr);
								outfile.close();
								break;

							}
							case 'N':
							{
								break;
							}
						}
						

					}
					else{cout<<"TO BE ADDED"<<endl;}
					break;
				}	
			}
			break;
		}
		case 3:
		{
			return;
		}
		case 4:
		{ exit(0);
		break;
		}
	
	// edit_menu(fall, spring, jterm, summer);
}
}

//this is to add a new course to your four year plan
void add_course(semlist* fall, semlist* spring, semlist* jterm, semlist* summer){
		sem semestertype;
		ofstream outfile;
		ofstream* outfileptr = &outfile; 
		//read semester type to direct to the correct linked list
		int year;
		cout<<"For which year?:"<<endl;
		cin>>year;
		while(year<1 || year>4){
			cout<<"Invalid year. Enter Again!: ";
			cin>>year;
		}
		int uinp;
		cout<<"For which semester?:"<<endl;
		cout<<"1. Fall"<<endl;
		cout<<"2. Spring"<<endl;
		cout<<"3. J-term"<<endl;
		cout<<"4. Summer"<<endl;
		cout<<" Enter number: ";
		cin>>uinp;
		semestertype = static_cast<sem>(uinp);
		Course* cr;
		//go to the fall semester linked list
		switch(uinp){
			case 1:
			{

				//variable  - if the user wants to add another course
				int useroption;
				// open output file
				
				outfile.open("FALL.txt");
				do{	
					cr = create(year, semestertype, fall, spring, jterm, summer);
					fall->add_front(cr);
					useroption = add_another_course();		
				}while(useroption == 1);
				fall->write_infile(outfileptr);

				outfile.close();
				break;
			}
			case 2:
			{	//variable  - if the user wants to add another course
				int useroption;
				// open output file
				
				outfile.open("SPRING.txt");
				do{
					cr = create(year, semestertype, fall, spring, jterm, summer);
					spring->add_front(cr);
					useroption = add_another_course();	
				}while(useroption == 1);
				spring->write_infile(outfileptr);
				outfile.close();
				break;
			}
			case 3:
			{
				//variable  - if the user wants to add another course
				int useroption;
				// open output file
				
				outfile.open("JTERM.txt");
				do{
					cr = create(year, semestertype, fall, spring, jterm, summer);
					jterm->add_front(cr);
					useroption = add_another_course();	
				}while(useroption == 1);
				jterm->write_infile(outfileptr);
				outfile.close();
				break;
			}	
			case 4:
			{
				//variable  - if the user wants to add another course
				int useroption;
				// open output file
				
				outfile.open("SUMMER.txt");
				do{
					cr = create(year, semestertype, fall, spring, jterm, summer);
					summer->add_front(cr);
					useroption = add_another_course();	
				}while(useroption == 1);
				summer->write_infile(outfileptr);
				outfile.close();
				break;
			}
		}
}

void main_menu(int i, semlist* fall, semlist* spring, semlist* jterm, semlist* summer){
	// variable to read the user input of the main menu
	int userInput;
	//loading the settings from file
	settings* Settings_object = load_settings();
	if (i == 1){
		system("cls");
		for(int j = 0; j<4;j++){
			cout<<endl;
		}
		cout<<"Welcome to PLAN4, a tool to layout your academic plan at NYUAD!"<<endl;
	}
	print_divider_short();
	userInput = main_menu_display();
	//if two
	switch(userInput){
	//directs to the edit menu
	case 1:
	{	system("cls");
		ofstream outfile;
		ofstream* outfileptr = &outfile;
		edit(fall, spring, jterm, summer);
		fall->write_infile(outfileptr);
		outfile.close();
		main_menu(1, fall, spring, jterm, summer);
		break;
	}
	//prints the settings of the user			
	case 3:
	{	system("cls");
		Settings_object->print();
		main_menu(0, fall, spring, jterm, summer);
		break;
	}
	//ptrints the requirements table
	case 2:
	{	system("cls");
		print_divider_short();
		Requirements * user_req = new Requirements;
		print_requirements_table( Settings_object, user_req, fall, jterm, spring, summer);
		main_menu(0, fall, spring, jterm, summer);
		break;
	}
	//exits
	case 4:
	{	
		system("cls");
		for(int i = 0; i<4;i++){
			cout<<endl;
		}

		cout<<"You have exited PLAN4!"<<endl;
		cout<<"Thank you for using me! :)"<<endl;
		cout<<"Contact Manesha Ramesh at manesharamesh@gmail.com for any feedback! :)";
		for(int i = 0; i<4;i++){
			cout<<endl;
		}
		print_divider_short();
		exit(1);
	}

}


}

//displyas teh main menu
int main_menu_display()

{	
	char userInput;

	for( int i = 0; i<3;i++){
		cout<<endl;
	}
	cout<<"MAIN MENU"<<endl;
	cout<<"What would you like to do?:"<<endl;
	cout<<"1. View and edit your four year plan"<<endl;
	cout<<"2. Check remaining requirements to be fulfilled."<<endl;
	cout<<"3. Settings"<<endl;
	cout<<"4. Exit"<<endl;
	cout<<endl;
	cout<<"Enter Number: ";
	userInput = input_error(userInput, 1, 4);
	return(userInput);
	
}
//the main function
int main(){
	
	//Decalre the linked lists for each semester type
	semlist fall, jterm, spring, summer; 
	
	//declare output stream and pointer to it
	//display main menu

	load_courses(&fall, &spring, &jterm, &summer);
	main_menu(1,&fall, &spring, &jterm, &summer);
	
	return(0);
		
}


