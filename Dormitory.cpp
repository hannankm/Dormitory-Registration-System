#include <iostream>

using namespace std;


// Assigned Room structure implements doubly linked lists:: the list of students that have been assigned to dorms
struct Node{
 int roomNo;
 string studentID;
 string firstName;
 string lastName;
 int phoneNumber;
 char block;

 Node *previous;
 Node *next;
}*head =NULL, *tail=NULL;


//Room structure implements stack with doubly linked lists:: the list of available spaces/ beds in the dorm represented by room keys
struct RoomKey{
    int roomNo;
    char block;
    int floor;

    RoomKey *next;
}*top=NULL;



//Request structure implements queue with doubly linked lists:: the list of dormitory requests made by students
struct Request{
 string studentID;
 string firstName;
 string lastName;
 string email;
 int phoneNumber;

 Request *next;
}*front=NULL, *rear=NULL, *temp;


//Room structure implements doubly linked lists:: list of dorms and respective students
struct Room{
    string studentID;
    int roomNo;
    char block;

    Room *next;
    Room *previous;
}*head1=NULL, *tail1=NULL;



// Functions declaration
void intro();//function to display introduction to the program
void admin_menu();// function to display proctor menu
void student_menu();// function to display student menu
void admin_login();// function to authenticate whether user really is a proctor


void pushRoom(int, int, char);// function so proctors can add rooms when they are available
void displayRooms();
void requestDorm(); // function to request for a dorm
void displayRequests();// so proctors can view all requests
void assignRoom(); //allocating a student to a room
void checkAssigment();// function for a student to view their room details
void viewAssignedRooms();//view rooms that have been assigned to students, but those students haven't checked in/ received their dorm keys
void checkIn();//student has received keys
void viewCheckedIn();// display students that have moved in/ received keys to their dormitories


/*
*************************************************
            MAIN FUNCTION
*************************************************
*/
int main()
    {
        intro();
        int role;
    cout<<endl;
    cout<<"Are you a Proctor or a Student?"<<endl;
    cout<<"1. Proctor"<<endl;
    cout<<"2. Student"<<endl;
    cin>>role;
    if (role==1)
    {
        //optional login();
        admin_login();
    }
    else if (role==2)
    {
        student_menu();
    }
    else
    {
        cout<<"You have entered a wrong button, please try again"<<endl;
    }

    }

/*
*************************************************
            ADMIN MENU
*************************************************
*/
void admin_menu()
{
    int choice, sure, rNo, flr;
   char blk;
    do
        {
    cout<<endl;
    cout <<endl<<endl<<"\t\t    ------ ADMIN MENU ------"<<endl<<endl<<endl;
	cout << "\t\t\t 1.ADD TO AVAILABLE ROOMS LIST (WITH EMPTY BEDS)" << endl;//push to stack
	cout << "\t\t\t 2.VIEW ALL ROOMS WITH AVAILABLE BEDS" << endl;//display stack
	cout << "\t\t\t 3.VIEW ALL ASSIGNED BEDS" << endl;//display linked list
	cout << "\t\t\t 4.VIEW ALL BED REQUESTS" << endl;//display queue
	cout << "\t\t\t 5.ASSIGN ROOM TO STUDENT" << endl;//dequeue request, pop room, insert to linked list
	cout << "\t\t\t 6.ADD STUDENT CHECKED IN " << endl;// delete from specific point in linked list
    cout << "\t\t\t 7.VIEW STUDENTS THAT HAVE CHECKED IN " << endl;// insert to end of linked list
	cout << "\t\t\t 8.EXIT"<<endl;//exit
	cout << "\t\t\t 9.LOG OUT OF ADMIN" << endl;
	cout<<"Choose an option(1-9) "<<endl;
	cin>> choice;

	switch (choice) {

   case 1:
        cout << "\n\n\t\t    ------ ADD ROOM KEY ------\n\n\n";
        cout<<"Enter Room Number: ";
        cin>>rNo;
        cout<<"Enter Room Floor: ";
        cin>>flr;
        cout<<"Enter Room Block: ";
        cin>>blk;
        pushRoom(rNo, flr, blk);

   break;

   case 2:
        cout << "\n\n\t\t    ------ VIEW AVAILABLE ROOMS (with empty beds) ------\n\n\n";
   displayRooms();

   break;

   case 3:
        cout << "\n\n\t\t    ------ ASSIGNED ROOMS ------\n\n\n";
   viewAssignedRooms();

   break;

   case 4:
       cout << "\n\n\t\t    -------- REQUESTS -------\n\n\n";
   displayRequests();

   break;

    case 5:
       cout << "\n\n\t\t   -------- ASSIGN ROOM -------\n\n\n";
   assignRoom();

   break;

    case 6:
       cout << "\n\n\t\t    ------- ADD STUDENT CHECK-IN -------\n\n\n";
       checkIn();
       break;
    case 7:
           cout << "\n\n\t\t    -------- VIEW STUDENTS THAT CHECKED IN -------\n\n\n";
       viewCheckedIn();
       break;

    case 8:
       cout<<"Are you sure you want to exit the system?\n";
       cout<<"1. YES \n2. CANCEL\n";
       cin>>sure;

       if(sure==1){
       cout << "\n\n\t\t    ------  EXIT ------\n\n\n";
       exit(1);
       }
       else if (sure==2)
        admin_menu();
       else
        cout<<"Invalid button";
            break;

    case 9:
        main();
        break;

   default:
   cout<<"Oops! You have entered an invalid choice"<<endl;
}
 }while (choice!=8);
}



/*
*************************************************
            STUDENT MENU
*************************************************
*/
void student_menu()
{
    int choice;
    int sure;
    do {
            cout<<endl;
    cout <<endl<<endl<<"\t\t    ------ STUDENT MENU ------"<<endl<<endl<<endl;
	cout << "\t\t\t 1.REQUEST FOR DORMITORY SERVICES" << endl;
	cout << "\t\t\t 2.CHECK MY ASSIGNMENT STATUS" << endl;
	cout << "\t\t\t 3.EXIT" << endl;
	cout << "\t\t\t 4.VIEW MAIN MENU"<<endl<<endl;
	cout<<"Choose an option(1-4) "<<endl;

cin>>choice;

    switch (choice) {
    case 1:
       requestDorm();
    break;

    case 2:
        checkAssigment();
    break;

    case 3:
        cout<<"Are you sure you want to exit the system?\n";
       cout<<"1. YES \n2. CANCEL\n";
       cin>>sure;

       if(sure==1){
       cout << "\n\n\t\t    ------  EXIT ------\n\n\n";
         cout << endl << endl;
       exit(1);
       }
       else if (sure==2)
        main();
       else
        cout<<"Invalid button";
          break;

    case 4:
        main();
        break;

    default:
        cout<<"Sorry mate, You have clicked on an invalid alternative. Please try again\n";
}
} while(choice!=3);

}

/*
*************************************************
            ADMIN LOGIN
*************************************************
*/
void admin_login(){
    string username;
    string password;
cout<<"-------Admin Login-------\n";
cout<<"Enter your username: \n";
cin>>username;
cout<<"Enter your password: \n";
cin>>password;
if(username=="Admin" && password== "admin123"){
        cout<<"Welcome ADMIN!\n";
    admin_menu();
}
else{
    cout<<"Invalid credentials:(\n";
    main();
}



}
/*
*************************************************
            ADD NEW AVAILABLE ROOM(KEY)
*************************************************
*/
void pushRoom(int rNo, int flr, char blk){
    RoomKey *newRoomKey= new RoomKey;
    newRoomKey->roomNo= rNo;
    newRoomKey->floor= flr;
    newRoomKey->block= blk;
    newRoomKey->next= top;
    top=newRoomKey;
}

/*
*************************************************
            DISPLAY AVAILABLE ROOMS(KEY)
*************************************************
*/
void displayRooms(){
RoomKey *ptr;
if(top==NULL)
    cout<<"There are no rooms available! \n";
else{
    ptr=top;
    cout<<"The Rooms with beds available are: \n";
    cout<<"RoomNo  Floor\tBlock\n";
    while(ptr!= NULL){
    cout<< ptr->roomNo<<"\t"<<ptr->floor<< "\t"<<ptr->block<<endl;
    ptr=ptr->next;
        }
    }
cout<<endl;
}

/*
*************************************************
            REQUEST DORM ROOM(KEY):: ENQUEUE
*************************************************
*/
void requestDorm(){
    string fname, lname, gmail, sid;
    int pNo;
    cout<<"----------Request Dorm----------\n";
    cout<<"Please note you should be a student in CNCS to request for a dorm here, and you are required to bring proofs in order to receive your keys!"<<endl<<endl;
    cout<<"Enter your First Name: ";
    cin>>fname;
    cout<<"Enter your Last Name: ";
    cin>>lname;
    cout<<"Enter your Student ID: ";
    cin>>sid;
    cout<<"Enter your email address: ";
    cin>>gmail;
    cout<<"Enter your phone number: ";
    cin>>pNo;
    if(rear==NULL){
        rear=new Request;
        rear->next=NULL;
        rear->firstName= fname;
        rear->lastName= lname;
        rear->studentID= sid;
        rear->email= gmail;
        rear->phoneNumber=pNo;
        front=rear;
    } else{
        temp=new Request;
        rear->next=temp;
        temp->firstName= fname;
        temp->lastName= lname;
        temp->studentID= sid;
        temp->email= gmail;
        temp->phoneNumber=pNo;
        temp->next=NULL;
        rear=temp;
    }
 }

 /*
*************************************************
            DISPLAY DORM ROOM REQUESTS(KEY)
*************************************************
*/
 void displayRequests(){
temp= front;
if((front==NULL) && (rear==NULL)){
    cout<<"There are no current requests\n";
    return;
}
cout<<"Requests are: \n";
cout<<"Name\t\tID\tEmail\t\tPhoneNo\n";
while(temp!=NULL){
    cout<<temp->firstName<<" "<<temp->lastName<<"\t"<<temp->studentID<<"\t"<<temp->email<<"  "<<temp->phoneNumber<< " "<< endl;
    temp=temp->next;
}
cout<<endl;

 }

/*
*************************************************
            ASSIGN ROOMS TO STUDENTS::
*************************************************
pop, dequeue and insert to linked list
*/
void assignRoom(){

    temp=front;
    if(top==NULL){
        cout<<"No available rooms! \n";
        return;
    } else{

    if(front==NULL){
    cout<<"There are no current requests\n";
    return;
    }

    else if(temp->next!=NULL){
    Node *newNode= new Node;
    temp=temp->next;
    cout<<"Student "<<front->studentID<<" has been allocated to dorm room number "<<top->roomNo<< " in block "<<top->block<<"."<<endl;



    newNode->firstName=front->firstName;
    newNode->lastName =front->lastName;
    newNode->studentID= front->studentID;
    newNode->phoneNumber=front->phoneNumber;
    newNode->roomNo=top->roomNo;
    newNode->block=top->block;

    newNode->next=NULL;

    if(head==NULL)
        {
    newNode->next=NULL;
    head=newNode;
    tail=newNode;
        }
    else
        {
    newNode->previous=tail;
    tail->next=newNode;
    tail=newNode;
        }
    top=top->next;
    free(front);
    front=temp;
    }

    else{
    cout<<"Student "<<front->studentID<<" has been allocated to dorm room number "<<top->roomNo<< " in block "<<top->block<<"."<<endl;
    Node *newNode= new Node;
    newNode->firstName=front->firstName;
    newNode->lastName =front->lastName;
    newNode->studentID= front->studentID;
    newNode->phoneNumber=front->phoneNumber;
    newNode->roomNo=top->roomNo;
    newNode->block=top->block;

    newNode->next=NULL;

    if(head==NULL)
        {
    newNode->next=NULL;
    head=newNode;
    tail=newNode;
        }
    else
        {
    newNode->previous=tail;
    tail->next=newNode;
    tail=newNode;
        }

    top=top->next;
    free(front);
    front=NULL;
    rear=NULL;
        }

    }
}
/*
*************************************************
            VIEW ROOMS ASSIGNED TO STUDENTS::
*************************************************
*/
void viewAssignedRooms(){
    if(head==NULL)
        cout<<"There are no rooms assigned\n";
    else
    {
    Node *temp1=head;
    cout<<"RoomNo Block Student ID\tName\t\tPhone No\n";
    while(temp1!=NULL)
        {
       cout<<temp1->roomNo<<"\t"<<temp1->block<<"\t"<<temp1->studentID<<"\t"<<temp1->firstName<<" "<<temp1->lastName<<"\t"<<temp1->phoneNumber<<"\n";
    temp1=temp1->next;
        }
    }
     }


// Method that records check in/ students receiving their dorm keys::
//implemented by doubly linked lists (deleting records from doubly linked lists)
/*
*************************************************
            ASSIGN ROOMS TO STUDENTS::
*************************************************
*/
void checkIn(){
    string key;
    int sure;

    cout<<"Which student has checked in? \nPlease enter the student ID: ";
    cin>>key;
 if(head==NULL)
    cout<<"Dorm Assignment list is empty";
else
{
    Node *temp1=head;
    while(temp1->studentID!=key)
           {
        if(temp1->next==NULL)
            {
            cout<<"Given record is not found\nPlease try again!";
            break;
            }
            temp1=temp1->next;
            }



            if(temp1->studentID==key)
      {
    cout<<temp1->roomNo<<"\t"<<temp1->block<<"\t"<<temp1->studentID<<"\t"<<temp1->firstName<<" " <<temp1->lastName<<"\t"<<temp1->phoneNumber<<"\n";
    cout<<"Are you sure this student has checked in? \n1. YES 2. NO\n";
    cin>>sure;
    if(sure==1){
        if(head->next==NULL)
            {
            Room *newRoom= new Room;

                newRoom->roomNo=temp1->roomNo;
                newRoom->block=temp1->block;
                newRoom->studentID=temp1->studentID;

                newRoom->next=NULL;

                if(head1==NULL)
                    {
                newRoom->next=NULL;
                head1=newRoom;
                tail1=newRoom;
                    }
                else
                    {
                newRoom->previous=tail1;
                tail1->next=newRoom;
                tail1=newRoom;
                    }
            head=NULL;
            tail=NULL;
            }
    else
       {
            if(temp1==head)
            {
                Room *newRoom= new Room;

                newRoom->roomNo=temp1->roomNo;
                newRoom->block=temp1->block;
                newRoom->studentID=temp1->studentID;

                newRoom->next=NULL;

                if(head1==NULL)
                    {
                newRoom->next=NULL;
                head1=newRoom;
                tail1=newRoom;
                    }
                else
                    {
                newRoom->previous=tail1;
                tail1->next=newRoom;
                tail1=newRoom;
                    }

                head=head->next;
            (temp1->next)->previous=NULL;
            }
            else if(temp1==tail)
              {
                  //start of insert code
                  Room *newRoom= new Room;

                newRoom->roomNo=temp1->roomNo;
                newRoom->block=temp1->block;
                newRoom->studentID=temp1->studentID;

                newRoom->next=NULL;

                if(head1==NULL)
                    {
                newRoom->next=NULL;
                head1=newRoom;
                tail1=newRoom;
                    }
                else
                    {
                newRoom->previous=tail1;
                tail1->next=newRoom;
                tail1=newRoom;
                    }
                    // end of insert code
            tail=tail->previous;
            (temp1->previous)->next=NULL;
                }
            else
                {
                    //start of insert code
                    Room *newRoom= new Room;

                newRoom->roomNo=temp1->roomNo;
                newRoom->block=temp1->block;
                newRoom->studentID=temp1->studentID;

                newRoom->next=NULL;

                if(head1==NULL)
                    {
                newRoom->next=NULL;
                head1=newRoom;
                tail1=newRoom;
                    }
                else
                    {
                newRoom->previous=tail1;
                tail1->next=newRoom;
                tail1=newRoom;
                    }
                    //end of insert code
            (temp1->previous)->next=temp1->next;
            (temp1->next)->previous=temp1->previous;
                 }
                   }
                  }
        else
            {
        cout<<"Entry has not been deleted";
            }
            cout<<" Student: "<<temp1->firstName<<" "<<temp1->lastName<<" [ "<<temp1->studentID<<" ] has received key for Room "<<temp1->roomNo<<" in Block "<<temp1->block<<" .\n";
    }
                  }
                }

 /*
*************************************************
            VIEW CHECKED IN ROOMS && STUDENTS::
*************************************************
*/
void  viewCheckedIn(){
if(head1==NULL)
        cout<<"There are no rooms assigned\n";
    else
    {
    Room *temp2=head1;
    cout<<"RoomNo\tBlock\tStudent ID\n";
    while(temp2!=NULL)
        {
       cout<<temp2->roomNo<<"\t"<<temp2->block<<"\t"<<temp2->studentID<<"\n";
    temp2=temp2->next;
        }
    }
}
 /*
*************************************************
            STUDENTS CAN CHECK THEIR REQUEST STATUS::
*************************************************
*/
void checkAssigment(){
    int hasRoom;
cout<<"Have you requested for a dorm room in CNCS dormitory service system ? \n";
cout<< "1. Yes       2. No\n";
cin>>hasRoom;
if(hasRoom==1){

    string key;
     cout<<"Enter your student ID: ";
    cin>>key;
 if(head==NULL)
    cout<<"You have not been assigned a dorm yet";
else
{
    Node *temp1=head;
    while(temp1->studentID!=key)
           {
        if(temp1->next==NULL)
            {
          cout<<"You have not been assigned a dorm yet";
            break;
            }
            temp1=temp1->next;
            }
    if(temp1->studentID==key)
      {
    cout<<"Dear Student: "<<temp1->firstName<<" "<<temp1->lastName<<"\n";
    cout<<"You have been allocated to Room number: "<< temp1->roomNo <<"  in Block: "<< temp1->block<<". \n";
    cout<<"Please come to the "<<temp1->block<<" the dormitory office to take your keys, and ID within 2 business days\n";
    cout<<endl<<endl;
    cout<<"Please note that you are required to bring your student ID, national ID, course registration slip, clearance letters(if you've had dorm rooms before), and letter from your sub-city (if you are an Addis Ababa resident) to receive your dorm\n"<<endl;

    cout << "\t........................................................................................................" << endl << endl;
    cout << "\t  Thank you for using College of Natural and Computational Sciences'  digital dormitory service system  " << endl << endl;
    cout << "\t........................................................................................................" << endl << endl;
        }
    }
        }

    else if (hasRoom==2){
    cout<<"You are supposed to first request for a dorm, in order to check your assignment. Please request and try again later\n";
    }

    else{
    cout<<"Invalid button, try again\n";
    }


 }
  /*
*************************************************
            INTRO FUNCTION
*************************************************
*/
void intro()
{

    cout << endl << endl;
    cout << "\t||=================================================================||" << endl << endl;
	cout << "\t||            CNCS DIGITAL DORMITORY SERVICES SYSTEM               ||" << endl << endl;
	cout << "\t||=================================================================||" << endl << endl;
	cout<<endl;
    cout<<"Welcome to CNCS' digital dormitory services system! "<<endl;

}
