#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <chrono>
#include "VisitsToDoctor.cpp"
#include <vector>
using namespace std;

//This function write text in file date.txt
void writeTextInFile(string str){
    ofstream file("data.txt",ios::app);
    file<<str;
    file.close();
}

//This function clear the file date.txt
void clearTextInFile(){
    std::ofstream ofs;
    ofs.open("data.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

//Create visitation and write it to the file if file don't exist create it
void visitDoctor(){
    //This is getting the day,month,year now (From the PC)
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    int day = aTime->tm_mday;
    int month = aTime->tm_mon + 1;
    int year = aTime->tm_year + 1900;

    //User need to enter the information here
    string eng;
    printf("Enter your egn.\n");
    getline(cin,eng);
    string names;
    printf("Enter your names.\n");
    getline(cin,names);
    string complaints;
    printf("Enter your complaints.\n");
    getline(cin,complaints);
    string diagnose;
    printf("Enter your diagnose.\n");
    getline(cin,diagnose);

    //Set the date
    Date date;
    date.set_day(day);
    date.set_month(month);
    date.set_year(year);

    //list of medicines max-5
    //waiting user to input
    list<string>medicines;
    for(int i=0;i<5;i++){
        printf("Enter the medicines (max 5) if you wanna stop entering type end!\n");
        string command;
        getline(cin,command);
        if(!command.compare("end")){
            break;
        }
        medicines.push_back(command);
    }

    //Creating VisitsToDoctor with the information that user entered
    VisitsToDoctor visitation (eng,names,complaints,date,diagnose);

    //Creating string with information for visitation
    string str;
    str += "complaints- ";
    str += complaints;
    str += "\n";
    str += "egn- ";
    str += eng;
    str += "\n";
    str += "names- ";
    str += names;
    str += "\n";
    str += "date- ";
    str += std::to_string(date.get_day());
    str += "/";
    str += std::to_string(date.get_month());
    str += "/";
    str += std::to_string(date.get_year());
    str += "\n";
    str += "diagnose- ";
    str += diagnose;
    str += "\n";
    str+= "medicines- ";
    int length = medicines.size();
    for(int i=0;i<length;i++){
        str+= medicines.front();
        if(i+1==length){
            break;
        }
        str += " ,";
        medicines.pop_front();
    }

    //create file date.txt if don't exist and then open it
    // if exist open it
    ofstream file("data.txt",ios::app);
    //separator for the visitations (better look)
    file << "\n------------------------------------------------------------------------------------------------------------------------------------------------------\n";
   //write the upper string to the file
    file << str;
    //close the file
    file.close();
}

//print all visitation with complains
void showInformationForAllPatientWithComplaints(){
    list<VisitsToDoctor>visitationsWithComplaints;
    //open file
    ifstream file ("data.txt");
    string s;
    VisitsToDoctor visitsToDoctor;
    //flag for complaints 0-no complaints 1 - have complaint
    int flag =0;

    //while loop for the file stream (by lines)
    while(getline(file,s)){
           string strForComplaint = s.substr(0,11);
           if(!strForComplaint.compare("complaints-")){
               //check if have complaint
               if(s.length()>=13){
                 flag =1;
                }else{
                   flag=0;
               }
           }

           //if having complaint print that visitation
           if(flag==1){
               cout<<s<<endl;
           }

    }
}


//search the file for the most common illness and print it
void findMostCommonIllness(){
    string str;
    //open the file
    ifstream file ("data.txt");
    string s;
    //while loop for the file stream (by lines)
    while(getline(file,s)){
        string strForDiagnose = s.substr(0,9);
        //check if the s now is for the diagnose
        if(!strForDiagnose.compare("diagnose-")){
            str += s.substr(10,s.length());
            str += " ";
        }
    }

    //find the most common diagnose from the string(str)
    istringstream input(str);
    map<string, int> count;
    string word;
    decltype(count)::const_iterator most_occurring;
    while (input >> word)
    {
        auto itr = count.emplace(word, 0).first;
        ++itr->second;
        if (count.size() == 1 || itr->second > most_occurring->second)
            most_occurring = itr;
    }
    cout <<"The most common diagnose is '";
    cout << most_occurring->first << "' repeated ";
    cout << most_occurring->second << " times\n";

}

//print all visitation from the last month
void findVisitationInfoLastMonth() {
    //get the current year,month,day
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    int day = aTime->tm_mday;
    int month = aTime->tm_mon + 1;
    int year = aTime->tm_year + 1900;

    //User for the years,months,days from the file
    int day1;
    int month1;
    int year1;

    //open file
    ifstream file("data.txt");
    string s;
    //counter for the field we are in the file 1-complaints, 2-egn ...
    int counter = 0;
    string complaints;
    string egn;
    string names;
    string date;
    string diagnose;
    string medicines;

    //while loop for the file stream (by lines)
    while (getline(file, s)) {
        //if line is empty
        if (!s.compare("")) {
            continue;
        }
        //if line is separator change the counter to 0 reset for the new visitation
        if (!s.compare(
                "------------------------------------------------------------------------------------------------------------------------------------------------------")) {
            counter=0;
            continue;
        }
        //add 1 to the counter
        counter++;


        if(counter==1){
            complaints=s;
        }else if(counter==2){
            egn=s;
        }else if(counter==3){
            names=s;
        }else if(counter==4){
            date=s;
        }else if(counter==5){
            diagnose=s;
        }else if(counter==6) {
            medicines = s;

            //string for the exact information for the date
            //skip date-
            string dateSubst;
            dateSubst = date.substr(6, date.length());

            //Split by /

            //Define string data that will be splitted
            std::string strData = dateSubst;
            //Define contant data that will be worked as delimiter
            const char separator = '/';
            //Define the dynamic array variable of strings
            std::vector<string> outputArray;
            //Construct a stream from the string
            std::stringstream streamData(strData);
            /*
            Declare string variable that will be used
            to store data after split
            */
            std::string val;
            /*
            The loop will iterate the splitted data and
            insert the data into the array
            */
            while (std::getline(streamData, val, separator)) {
                outputArray.push_back(val);
            }
            //stoi() -> int value from string
            day1 = stoi(outputArray[0]);
            month1 = stoi(outputArray[1]);
            year1 = stoi(outputArray[2]);

            //check if the year from the file is like current year
            if (year1 == year) {
                //check if month from the file is like current
                if (month == month1) {
                    //print information for the current visitation
                    printf("\n");
                cout<<egn;
                printf("\n");
                cout<<names;
                printf("\n");
                cout<<complaints;
                printf("\n");
                cout<<date;
                printf("\n");
                cout<<diagnose;
                printf("\n");
                cout<<medicines;
                printf("\n");
                }
                //check if current month-1 is like month from the file
                else if (month - 1 == month1) {
                    //calculate days to check if it is from the last month
                int dayFromPreviousMonth = 31 - day;
                int start = 31 - dayFromPreviousMonth;
                  if (day1 >= start) {
                      //print information for the current visitation
                      printf("\n");
                      cout<<egn;
                      printf("\n");
                      cout<<names;
                      printf("\n");
                      cout<<complaints;
                      printf("\n");
                      cout<<date;
                      printf("\n");
                      cout<<diagnose;
                      printf("\n");
                      cout<<medicines;
                      printf("\n");
                  }
                 }
            }
        }
    }

}

//Edit the information in the file
void editingVisitations(){
    //This string is used for the new information that will be write in file
    string newInformation;
    //ope file
    ifstream file("data.txt");
    string s;
    //This is flag 0 - if editing
    // 1 - if we stop editing
    int flag =0;
    //while loop for the file stream (by lines)
    while (getline(file, s)) {
        //if line is empty
        if (!s.compare("")) {
            continue;
        }
        //if line is separator add it to the new string for the file
        else if(!s.compare(
                "------------------------------------------------------------------------------------------------------------------------------------------------------")) {
            newInformation+=s;
            newInformation+="\n";
            continue;
        }
        string command;
        string str;

        if(flag ==0){
            //Split by -

            //Define string data that will be splitted
            std::string strData = s;
            //Define contant data that will be worked as delimiter
            const char separator = '-';
            //Define the dynamic array variable of strings
            std::vector<string> outputArray;
            //Construct a stream from the string
            std::stringstream streamData(strData);
            /*
            Declare string variable that will be used
            to store data after split
            */
            std::string val;
            /*
            The loop will iterate the splitted data and
            insert the data into the array
            */
            while (std::getline(streamData, val, separator)) {
                outputArray.push_back(val);
            }
            //string with the info of the field like (names-)
            str+=outputArray[0];
            str+="- ";

            //print the current info in the console
            cout<<"This is the current information\n- ";
            cout<<s;
            printf("\n");
            cout<<"If you wanna edit it write the new information,if you wanna leave it that way write ->s,if you are ready with the editing type ->end\n";
            //waiting for command from the user
            getline(cin,command);
        }else{
            newInformation+=s;
        }

        //command s skip this line and leave it how it was
        if(!command.compare("s")){
            newInformation+=s;
            newInformation+="\n";
        }
        //user finish with editing leave the other lines that left be how it was
        //change the flag to 1 - finish with editing
        else if(!command.compare("end")){
           flag=1;
           newInformation+=s;
           newInformation+="\n";
        }
        //user choose to edit and input the new text
        else{
            str+=command;
            newInformation+=str;
            newInformation+="\n";
        }

    }
    //close the file
    file.close();
    //clear the file
    clearTextInFile();
    //write the edited information in the file
    writeTextInFile(newInformation);
}

//delete information from the file
void deleteVisitations(){
    //This string is used for the new information that will be write in file (with deleted lines)
    string newInformation;
    //open file
    ifstream file("data.txt");
    string s;
    //This is flag 0 - if removing
    // 1 - if we stop removing
    int flag =0;
    //while loop for the file stream (by lines)
    while (getline(file, s)) {
        string command;
        //if line is empty
        if (!s.compare("")) {
            continue;
        }
        if(flag==0){
            //print the line from the file
            cout<<s;
            printf("\n");
            //print message in the console
            cout<<"If you wanna remove this -> y If you wanna leave this -> n If you wanna stop removing -> end\n";
            //waiting user to input command
            getline(cin,command);
        }else{
            newInformation+=s;
            newInformation+="\n";
        }

        //y -> for removing the line
        if(!command.compare("y")){
        //don't wanna remove this line - leave it the way it was
        }else if(!command.compare("n")){
            newInformation+=s;
            newInformation+="\n";
        }
        //Finish with removing leave the left lines the way it was
        else if(!command.compare("end")){
            //change the flag to 1 -> Finish removing
            flag=1;
            //add the current line from the file to the string
            newInformation+=s;
            newInformation+="\n";
        }
    }
    //close the file
    file.close();
    //clear the old information from the file
    clearTextInFile();
    //write the new information to the file
    writeTextInFile(newInformation);
}


int main() {
    //when starting program create date.txt if not exist
    ofstream file("data.txt",ios::app);
    file.close();
    string command;
    for(;;){
        //print the menu for the program
        printf("\nSelect command:\n");
        printf(" -> visitDoctor\n");
        printf(" -> editingVisitations\n");
        printf(" -> deleteVisitations\n");
        printf(" -> showAllVisitationWithComplaints\n");
        printf(" -> findMostCommonIllness\n");
        printf(" -> allVisitationInfoLastMonth\n");

        //waiting user input
        getline(cin,command);

        if(!command.compare("end")){
            break;
        }else if(!command.compare("visitDoctor")){
            visitDoctor();
        }else if(!command.compare("editingVisitations")){
            editingVisitations();
        }else if(!command.compare("deleteVisitations")){
            deleteVisitations();
        }else if(!command.compare("showAllVisitationWithComplaints")){
            showInformationForAllPatientWithComplaints();
        }else if(!command.compare("findMostCommonIllness")){
            findMostCommonIllness();
        }else if(!command.compare("allVisitationInfoLastMonth")){
            findVisitationInfoLastMonth();
        }else{
            printf("Please choose correct command from the menu!");
        }
    }

}

