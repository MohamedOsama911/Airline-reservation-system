#include <iostream> // input , output
#include <string>
#include <stdio.h>
#include <iomanip>
#include <stdlib.h>
#include <ctime>  // time function
#include <thread> //for sleep and this dots
#include <chrono>

#ifdef __unix__

//this is used to let the program work in windows bcs it was written in linux os
#elif defined(_WIN32) || defined(WIN32)
#include <conio.h> //for [ getch() ]
#include <Windows.h>
#define OS 1
#define CLEAR_SCREEN "cls"
#endif

using namespace std;

time_t now = time(0); //this 2 lines is used to get the current time in ur pc
string dt(ctime(&now));

const int NumofFlights = 50;
const int Full_Users = 50;
const int Full_Tickets = 50;

const int MAIN = 0;
const int ADMIN_CHECK = 1;
const int ADMIN_DISPLAY = 2;
const int USER = 3;
const int LOGIN = 4;
const int SIGNUP = 5;
const int PASSENGER = 6;
const int SHOW_ADDED_FLIGHTS = 7;
const int SHOW_NEW_TICKET = 8;
const int SHOW_ALL_TICKETS = 9;
const int EXIT = -1;

short arr_of_width[8] = {}; //array carry width each data raw of flight
short arr_of_width_for_tickets[6] = {};

int Num_of_ticket = 0;
int Accounts_Used = 0;
int Start_Flights = 0;

int Entered_Flights, Deleted_Flights = 0, Updated_Flight;

string AdminPassword = "3"; //##the password of the admin##

//structs - by all
struct flight
{
    string flightnumber;
    int availableSeats;
    int day, month, year;
    string departure, arrival;
    float departureTime, arrivalTime;

} f1[NumofFlights] = {}, temp_f1; //temp is used to put the data in it first
struct User                       //if we wont use it we throw it away else f1[]=temp
{
    string username, password;
    string Passenger_ID, name, address, phone_number;
} users[Full_Users] = {};
struct wanted //wanted flights by user after he searched for it or picked it
{
    User Existing_User;                          // has the data of the user that already loged-in or signed-up
    int x;                                       //indx of the flight that we want in the main flight shedul
    int selected_flights[NumofFlights + 1] = {}; //array of index of flights that matches user search
} wanted1 = {};
struct tickets
{
    string index_flightnum;  // flight num booked
    string reservation_date; // auto generate function
    int ticketnum;           // digits between 5 and 10
    string departure_city_ticket, arrival_city_ticket;
    string pasngr_id_tkt; //is the same of the normal passenger id

} tickets1[Full_Tickets] = {};

//Technicals - by omar
void os_sleep(int milliseconds)
{
    cout << flush;
    if (OS)
    {
        _sleep(milliseconds);
    }
}
void loading(string s) //updateing flights ....... "puts this dots"
{
    cout << endl
         << s << ' ';
    for (int i = 0; i < 10; i++)
    {
        os_sleep(200);
        cout << '.';
    }
    cout << endl;
}
void done(string s) //let u know the task u want to do is completed it take string and display it LIKE A SANDWAICH!
{
    int length = s.length();
    cout << "\n\t\t" << string(length, '-') << "\n\t\t" << s << "\n\t\t" << string(length, '-') << endl;
    os_sleep(2000);
}
void error(string s) //same as done but it puts !!!!!!!!! instead of
{
    int length = s.length();
    cout << "\n\t\t" << string(length, '!') << "\n\t\t" << s << "\n\t\t" << string(length, '!') << endl;
    os_sleep(2000);
}
void Invalid() // constant massege pops when u put invalid input same as errorr
{
    string s = "# You entered an invalid input .. Please try again! #";
    int length = s.length();
    cout << "\n\t\t" << string(length, '#') << "\n\t\t" << s << "\n\t\t" << string(length, '#') << endl;
    os_sleep(3000);
}
short string_output(string s)
{
    int length = s.length();
    cout << setw(length + 1) << s << '|';
    return length + 1;
}
bool compareStrings(string s1, string s2) //this mainly made bcs u cant compare 2 strings
{
    int compare = s1.compare(s2);
    bool equal;
    if (compare == 0)
    {
        equal = true;
    }
    else if (compare != 0)
    {
        equal = false;
    }
    return equal;
}

// search task
//=============
//emad
void display_selected_flights(int y[])
{
    string date; //we did it to trans the date of flights from int to string
    cout << "\n\n\t\t\t\t\t" << string(36, ' ') << "----------This is available flight schedule----------\n";
    cout << "\t\t\t\t\t" << string(36, ' ') << "================================================\n\n";
    cout << left;
    cout << "\t\t\t\t\t" << '|';
    arr_of_width[0] = string_output(" Index");
    arr_of_width[1] = string_output(" Flight Number");
    arr_of_width[2] = string_output(" Available Seats");
    arr_of_width[3] = string_output(" Flight Date");
    arr_of_width[4] = string_output(" Departure City");
    arr_of_width[5] = string_output(" Arrival City");
    arr_of_width[6] = string_output(" Departure Time");
    arr_of_width[7] = string_output(" Arrival Time");
    cout << endl;
    cout << "\t\t\t\t\t" << '|';
    for (int i = 0; i < 8; i++)
    {
        cout << string(arr_of_width[i], '-') << '|';
    }
    cout << endl;
    int numOFselectedflight = wanted1.selected_flights[NumofFlights + 1]; //we put the number of chosen flights in w.s.f[51]
    for (int i = 0; i < numOFselectedflight; i++)
    {
        date = to_string(f1[wanted1.selected_flights[i]].day) + "/" + to_string(f1[wanted1.selected_flights[i]].month) + "/" + to_string(f1[wanted1.selected_flights[i]].year);
        cout << "\t\t\t\t\t" << '|'
             << setw(arr_of_width[0]) << i + 1 << '|' << setw(arr_of_width[1]) << f1[wanted1.selected_flights[i]].flightnumber << '|' << setw(arr_of_width[2]) << f1[wanted1.selected_flights[i]].availableSeats << '|'
             << setw(arr_of_width[3]) << date << '|'
             << setw(arr_of_width[4]) << f1[wanted1.selected_flights[i]].departure << '|' << setw(arr_of_width[5]) << f1[wanted1.selected_flights[i]].arrival << '|'
             << setw(arr_of_width[6]) << f1[wanted1.selected_flights[i]].departureTime << '|' << setw(arr_of_width[7]) << f1[wanted1.selected_flights[i]].arrivalTime << '|' << "\n";
    }
}
int search()
{
    string choice;
    string to, from;       // depature and arrival place
    int counter_search, c; //counter search tells u how many flight matched ur Itenerary,c index of final picked flight
above1:
    counter_search = 0;
    cout << "\nEnter Your Itenerary: \n"
         << string(22, '-') << endl;
    cout << "From : ";
    cin >> from;
    cout << "To : ";
    cin >> to;
    loading("Searching For Flights");
    for (int i = 0; i < Start_Flights; i++)
    {
        if (f1[i].departure == from && f1[i].arrival == to && f1[i].availableSeats > 0)
        {
            wanted1.selected_flights[counter_search] = i; //we put matched flights indexes from f1 to w.s.f array
            counter_search++;
        }
    }
    wanted1.selected_flights[NumofFlights + 1] = counter_search;
    if (counter_search > 0)
    {

        display_selected_flights(wanted1.selected_flights); //display selected flights
    try_again:
        cout << "Enter Index of flight you want to book : ";
        cin >> c;
        if (c > wanted1.selected_flights[NumofFlights + 1] || c <= 0)
        {
            Invalid();
            cout << endl
                 << "Do you want to try again?..(Y/N)" << endl;
            cin >> choice;
            if (compareStrings(choice, "y") || compareStrings(choice, "Y"))
            {
                goto try_again;
            }
            else
            {
                return PASSENGER;
            }
        }
        wanted1.x = wanted1.selected_flights[c - 1]; //wanted.x now =index of the flight he picked from the small array
        for (int i = 0; i < Num_of_ticket; i++)
        {
            if (f1[wanted1.x].flightnumber == tickets1[i].index_flightnum && wanted1.Existing_User.Passenger_ID == tickets1[i].pasngr_id_tkt)
            {
                error("!! You already booked this flight !!");
                cout << endl
                     << "Do you want to continue?..(Y/N)" << endl;
                cin >> choice;
                if (compareStrings(choice, "y") || compareStrings(choice, "Y"))
                {
                    goto above1;
                }
                else
                {
                    return PASSENGER;
                }
            }
        }
        f1[wanted1.x].availableSeats--;
        done("Flight picked!");
        return SHOW_NEW_TICKET;
    }
    else
    {
        error("!! Invalid Flight !!");
        cout << endl
             << "Do you want to continue?..(Y/N)" << endl;
        cin >> choice;
        if (compareStrings(choice, "y") || compareStrings(choice, "Y"))
        {
            goto above1;
        }
        else
        {
            return PASSENGER;
        }
    }
}

// flight task
//===========
//osama + gamal
void displayflight(flight f1[NumofFlights])
{
    string date; //this string is used to put day,month,year in 1 string
    cout << "\n\n\t\t\t\t\t" << string(36, ' ') << "----------This is full flight schedule----------\n";
    cout << "\t\t\t\t\t" << string(36, ' ') << "================================================\n\n";
    cout << left;

    // title
    cout << "\t\t\t\t\t" << '|';
    arr_of_width[0] = string_output(" Index");         // arr of width da by5zen kol title bya50d mmsa7a ad eh
    arr_of_width[1] = string_output(" Flight Number"); // arr of width da byrga3 short bn7ot el rqam da gowa arr_of_width
    arr_of_width[2] = string_output(" Available Seats");
    arr_of_width[3] = string_output(" Flight Date");
    arr_of_width[4] = string_output(" Departure City");
    arr_of_width[5] = string_output(" Arrival City");
    arr_of_width[6] = string_output(" Departure Time");
    arr_of_width[7] = string_output(" Arrival Time");
    cout << endl;

    // line between title and data
    cout << "\t\t\t\t\t" << '|';
    for (int i = 0; i < 8; i++)
    {
        cout << string(arr_of_width[i], '-') << '|';
    }
    cout << endl;

    // data
    for (int i = 0; i < Start_Flights; i++)
    {
        date = to_string(f1[i].day) + "/" + to_string(f1[i].month) + "/" + to_string(f1[i].year);
        cout << "\t\t\t\t\t" << '|'
             << setw(arr_of_width[0]) << i + 1 << '|'
             << setw(arr_of_width[1]) << f1[i].flightnumber << '|'
             << setw(arr_of_width[2]) << f1[i].availableSeats << '|'
             << setw(arr_of_width[3]) << date << '|'
             << setw(arr_of_width[4]) << f1[i].departure << '|'
             << setw(arr_of_width[5]) << f1[i].arrival << '|'
             << setw(arr_of_width[6]) << f1[i].departureTime << '|'
             << setw(arr_of_width[7]) << f1[i].arrivalTime << '|' << "\n";
    }
}
int addflight(flight f1[NumofFlights])
{
    bool flight_okay = true; //bool to check if we gonna add this flight or not
    int failed_flights = 0;  //we used this to make entered flights is correct
    cout << "\nEnter number of flights you want to add:" << endl;
    cin >> Entered_Flights;
    if (Entered_Flights > NumofFlights)
    {
        error("You entered more than maximum number of flights");
        return ADMIN_DISPLAY;
    } //we created an object from flight struct called temp to put data into it
    for (int i = Start_Flights; i < Start_Flights + Entered_Flights; i++)
    {
        cout << "\nEnter flight number : " << endl;
        cin >> temp_f1.flightnumber;
        cout << "Enter available Seats : " << endl;
        cin >> temp_f1.availableSeats;
        cout << "Enter flight date : " << endl;
        cin >> temp_f1.day >> temp_f1.month >> temp_f1.year;
        cout << "Enter your departure city : " << endl;
        cin >> temp_f1.departure;
        cout << "Enter your arrival city : " << endl;
        cin >> temp_f1.arrival;
        cout << "Enter your departureTime : " << endl;
        cin >> temp_f1.departureTime;
        cout << "Enter your arrivalTime : " << endl;
        cin >> temp_f1.arrivalTime;
        if (compareStrings(temp_f1.arrival, temp_f1.departure))
        {
            error("You go no where :(");
            failed_flights++;
            flight_okay = false;
        } //
        if (flight_okay)
        {
            f1[i] = temp_f1;
        }
    }
    Entered_Flights -= failed_flights;
    if (Entered_Flights != 0)
    {
        Start_Flights += Entered_Flights;
        loading("Adding Flights");
        done("Flights Added Succesfully!");
    }
    return ADMIN_DISPLAY;
}
int deleteflight(flight f1[NumofFlights])
{
    displayflight(f1);
    cout << "Enter index of flight you want to delete : ";
    int z;
    bool loop = false; //used to see if u entered wrong number"z" or correct one
    cin >> z;
    if (z <= 0)
    {
        Invalid();
        return ADMIN_DISPLAY;
    }
    // z-1 is the number must be deleted
    for (int i = z; i <= Start_Flights; i++) //i<=start flight to prevent 2 repeated flights at the end
    {
        loop = true;
        f1[i - 1] = f1[i];
    }
    if (!loop) //if for any reason he didn't enter the previous loop invalid pop up
    {
        Invalid();
        return ADMIN_DISPLAY;
    }
    Start_Flights--;
    loading("Deleting Flights");
    done("Flight Deleted Succesfully!");
    return SHOW_ADDED_FLIGHTS;
}
int updateflight(flight f1[NumofFlights])
{
    displayflight(f1);
    cout << "\n\nEnter index of flight you want to update:" << endl;
    int Updated_Flight;
    cin >> Updated_Flight;
    if (Updated_Flight > Start_Flights)
    {
        Invalid();
        return ADMIN_DISPLAY;
    }
    cout << "\n1- change flight number" << endl;
    cout << "2- change flight available seats" << endl;
    cout << "3- change flight date" << endl;
    cout << "4- change flight departure city" << endl;
    cout << "5- change flight arrival city" << endl;
    cout << "6- change flight departure time" << endl;
    cout << "7- change flight arrival time" << endl
         << endl;
    cout << "Your Choice : ";
    string choice;
    cin >> choice;
    if (compareStrings(choice, "1"))
    {
        cout << "Enter new flight number : ";
        cin >> f1[Updated_Flight - 1].flightnumber;
    }
    else if (compareStrings(choice, "2"))
    {
        cout << "Enter new flight available seats : ";
        cin >> f1[Updated_Flight - 1].availableSeats;
    }
    else if (compareStrings(choice, "3"))
    {
        cout << "Enter new flight date (day) : ";
        cin >> f1[Updated_Flight - 1].day;
        cout << "Enter new flight date (month) : ";
        cin >> f1[Updated_Flight - 1].month;
        cout << "Enter new flight date (year) : ";
        cin >> f1[Updated_Flight - 1].year;
    }
    else if (compareStrings(choice, "4"))
    {
        cout << "Enter new flight arrival city : ";
        cin >> f1[Updated_Flight - 1].departure;
    }
    else if (compareStrings(choice, "5"))
    {
        cout << "Enter new flight arrival city : ";
        cin >> f1[Updated_Flight - 1].arrival;
    }
    else if (compareStrings(choice, "6"))
    {
        cout << "Enter new flight departure time : ";
        cin >> f1[Updated_Flight - 1].departureTime;
    }
    else if (compareStrings(choice, "7"))
    {
        cout << "Enter new flight arrival time : ";
        cin >> f1[Updated_Flight - 1].arrivalTime;
    }
    else
    {
        Invalid();
        return ADMIN_DISPLAY;
    }
    loading("Updating Flights");
    done("Flight Updated Successfully!");
    return SHOW_ADDED_FLIGHTS;
}

// ticket task
//============
//muhammad ahmed + ibrahim
void display_all_tickets(tickets tickets1[Full_Tickets])
{
    cout << "\n\n\t\t" << string(36, ' ') << "----------This is your reservation log----------\n";
    cout << "\t\t" << string(36, ' ') << string(48, '=');
    cout << "\n\n\t\t" << string(36, ' ') << "Your Passenger ID : " << wanted1.Existing_User.Passenger_ID << endl;
    cout << "\t\t" << string(36, ' ') << string(48, '=') << "\n\n";
    cout << left;

    // title
    cout << "\t\t\t\t\t" << '|';
    arr_of_width_for_tickets[0] = string_output(" Index");
    arr_of_width_for_tickets[1] = string_output(" Flight Number");
    arr_of_width_for_tickets[2] = string_output(" Ticket Number");
    arr_of_width_for_tickets[3] = string_output(" Departure City");
    arr_of_width_for_tickets[4] = string_output(" Arrival City");
    arr_of_width_for_tickets[5] = string_output("     Reservation Date    ");
    cout << endl;

    // line between title and data
    cout << "\t\t\t\t\t" << '|';
    for (int i = 0; i < 6; i++)
    {
        cout << string(arr_of_width_for_tickets[i], '-') << '|';
    }
    cout << endl;

    // data
    int count = 0;                          // index of ticket at table
    for (int i = 0; i < Num_of_ticket; i++) // num of ticket in the arr of total tickets[]
    {
        if (wanted1.Existing_User.Passenger_ID == tickets1[i].pasngr_id_tkt)
        {
            count++;
            cout << "\t\t\t\t\t "
                 << setw(arr_of_width_for_tickets[0]) << count << '|'
                 << setw(arr_of_width_for_tickets[1]) << tickets1[i].index_flightnum << '|'
                 << setw(arr_of_width_for_tickets[2]) << tickets1[i].ticketnum << '|'
                 << setw(arr_of_width_for_tickets[3]) << tickets1[i].departure_city_ticket << '|'
                 << setw(arr_of_width_for_tickets[4]) << tickets1[i].arrival_city_ticket << '|'
                 << setw(arr_of_width_for_tickets[5]) << tickets1[i].reservation_date;
        }
    }
}
void save_Ticket(tickets tickets1[Full_Tickets])
{
    tickets1[Num_of_ticket].index_flightnum = f1[wanted1.x].flightnumber;
    tickets1[Num_of_ticket].pasngr_id_tkt = wanted1.Existing_User.Passenger_ID;
    tickets1[Num_of_ticket].reservation_date = dt;
    tickets1[Num_of_ticket].ticketnum = rand() % 1000000000 + 10000;
    tickets1[Num_of_ticket].departure_city_ticket = f1[wanted1.x].departure;
    tickets1[Num_of_ticket].arrival_city_ticket = f1[wanted1.x].arrival;
}
int modify_ticket(tickets tickets1[Full_Tickets])
{
    display_all_tickets(tickets1);
    int z;
    bool loop = false;
    cout << "Enter Index of ticket you want to modify : ";
    cin >> z;
    if (z <= 0)
    {
        Invalid();
        return PASSENGER;
    }
    // z-1 is the number must be deleted
    for (int i = z; i <= Num_of_ticket; i++)
    {
        loop = true;
        tickets1[i - 1] = tickets1[i];
    }
    if (!loop)
    {
        Invalid();
        return PASSENGER;
    }
    Num_of_ticket--;
    loading("Modifying Ticket");
    return search();
}
int cancel_ticket(tickets tickets1[Full_Tickets])
{
    display_all_tickets(tickets1);
    int z;
    bool loop = false; // if you entered the delete loop , then loop will be true , that means he will delete.
    cout << "Enter Index of ticket you want to cancel : ";
    cin >> z;
    if (z <= 0)
    {
        Invalid();
        return PASSENGER;
    }
    // z-1 is the number must be deleted
    for (int i = z; i <= Num_of_ticket; i++)
    {
        loop = true;
        tickets1[i - 1] = tickets1[i];
    }
    if (!loop)
    {
        Invalid();
        return PASSENGER;
    }
    Num_of_ticket--;
    loading("Canceling Ticket");
    done("Ticket Successfuly Canceled!");
    return SHOW_ALL_TICKETS;
}
void display_new_ticket(tickets tickets1[Full_Tickets])
{
    // show the user that he now will see his ticket
    cout << left;
    cout << "\n\n\t\t\t\t\t\t\t " << string(22, '*') << "\n";
    cout << "\t\t\t\t\t\t\t Welcome to your ticket\n ";
    cout << "\t\t\t\t\t\t\t " << string(22, '*') << "\n";
    cout << "\n\t\t" << string(18, '@') << string(100, '=') << string(18, '@') << "\n";
    cout << "\n\n\t\t Ticket Number: " << setw(16) << tickets1[Num_of_ticket].ticketnum;
    cout << "Passenger ID: " << setw(16) << tickets1[Num_of_ticket].pasngr_id_tkt;
    cout << "Flight Number: " << setw(16) << tickets1[Num_of_ticket].index_flightnum;
    cout << "Reservation Date: " << setw(26) << tickets1[Num_of_ticket].reservation_date;
    cout << "\n\t\t" << string(18, '@') << string(100, '=') << string(18, '@') << "\n";
}

// login task + base (Pages)
//==========================
//muhammad ahmed + ibrahim
int Show_All_Tickets_Display()
{
    display_all_tickets(tickets1);
    cout << "Press Enter to get back to passenger page...";
    getchar();
    getchar();
    return PASSENGER;
}
int Show_New_Ticket_Display()
{
    save_Ticket(tickets1);
    loading("Loading Ticket");
    display_new_ticket(tickets1);
    Num_of_ticket++;
    string choice;
    cout << "1- Confirm\n2- Cancel\n\n";
    cout << "Your Choice : ";
    cin >> choice;
    if (compareStrings(choice, "1"))
    {
        loading("Saving Ticket");
        done("Successfully Registration!");
        return PASSENGER;
    }
    else if (compareStrings(choice, "2"))
    {
        Num_of_ticket--;
        //tickets1[Num_of_ticket]={0};
        loading("Canceling Reservation");
        done("Canceled Successfully!");
        return PASSENGER;
    }
    else
    {
        Invalid();
        return SHOW_NEW_TICKET;
    }
}
//osama + gamal
int ShowFlightsDisplay()
{
    displayflight(f1);
    cout << "Press Enter to get back to admin page...";
    getchar(); //wont do anyting till u press enter
    getchar();
    return ADMIN_DISPLAY;
}
//muhammad ahmed + ibrahim
int PassengerDisplay()
{
    string choice;
    cout << "\n\t    ==================================================\nPassenger Menu:\n-----------\n";
    cout << "1- Add new reservation\n2- Cancel existing reservation\n3- Modify existing reservation\n4- Show reservation log\n5- Logout\n\n";
    cout << "Your Choice : ";
    cin >> choice;
    if (compareStrings(choice, "1"))
    {
        system(CLEAR_SCREEN); //creat a new page
        cout << "\n\t    ==================================================\n";
        return search();
    }
    else if (compareStrings(choice, "2"))
    {
        system(CLEAR_SCREEN);
        return cancel_ticket(tickets1);
    }
    else if (compareStrings(choice, "3"))
    {
        system(CLEAR_SCREEN);
        return modify_ticket(tickets1);
    }
    else if (compareStrings(choice, "4"))
    {
        return SHOW_ALL_TICKETS;
    }
    else if (compareStrings(choice, "5"))
    {
        done("You Are Loged out!");
        return USER;
    }
    else
    {
        Invalid();
        return PASSENGER;
    }
}
//omar
int SignupDisplay()
{
    string temp_username, temp_id;
    bool new_user = true; //check if user is new not saved in the system
    bool new_id = true;
    cout << "\n\t    ==================================================\nSignup Menu:\n-----------\n";
    if (Accounts_Used == Full_Users)
    {
        cout << "\t\tSorry but the amount of users is full\n";
        return USER;
    }
    else
    {
        cout << "Hello Passenger!\nPlease enter your data\n";

        cout << string(22, '_') << "\nUsername : ";
        cin >> temp_username;
        cout << "Password : ";
        cin >> users[Accounts_Used].password;
        cout << string(22, '_') << "\nPassenger ID : ";
        cin >> temp_id;
        for (int i = 0; i < Full_Users; i++)
        {
            if (compareStrings(temp_username, users[i].username))
            {
                new_user = false;
                error("!!!! This Username is already used !!!!");
                return USER;
            }
            if (compareStrings(temp_id, users[i].Passenger_ID))
            {
                new_id = false;
                error("!!!! This Passenger ID is already used !!!!");
                return USER;
            }
        }
        if (new_user)
        {
            users[Accounts_Used].username = temp_username;
        }
        if (new_user)
        {
            users[Accounts_Used].Passenger_ID = temp_id;
        }

        cout << "Name : ";
        cin >> users[Accounts_Used].name;
        cout << "Address : ";
        cin >> users[Accounts_Used].address;
        cout << "Phone Number : ";
        cin >> users[Accounts_Used].phone_number;
        wanted1.Existing_User = users[Accounts_Used];
        Accounts_Used++;
        done("Account Created Succesfully!");
        return PASSENGER;
    }
}
int LoginDisplay()
{
    string temp_username, temp_password;
    bool found_user = false;
    cout << "\n\t    ==================================================\nLogin Menu:\n-----------\n";
    cout << "Username : ";
    cin >> temp_username;
    cout << "Password : ";
    cin >> temp_password;
    for (int i = 0; i < Full_Users; i++)
    {
        if (compareStrings(temp_username, users[i].username) && compareStrings(temp_password, users[i].password))
        {
            found_user = true;
            wanted1.Existing_User = users[i];
            break;
        }
    }
    if (found_user)
    {
        done("Login Succesfully!");
        return PASSENGER;
    }
    else
    {
        error("!!!!Invalid username and password !!!!");
        return USER;
    }
}
//osama + gamal
int AdminDisplay()
{
    cout << "\n\t    ==================================================\n";
    cout << "\n\t\t" << string(16, '-') << "\n\t\t"
         << "Welcome Admin :)"
         << "\n\t\t" << string(16, '-') << endl;
    cout << "Admin Menu:\n-----------\n";
    string choice;
    cout << "\n1- Add flights schedule\n2- Delete existing flight schedule\n3- Update existing flight schedule\n4- Show existing flights schedule\n5- Return to main menu\n\n";
    cout << "Your Choice : ";
    //cin.clear();
    cin >> choice;
    if (compareStrings(choice, "1"))
    {
        system(CLEAR_SCREEN);
        cout << "\n\t    ==================================================\n";
        return addflight(f1);
    }
    else if (compareStrings(choice, "2"))
    {
        system(CLEAR_SCREEN);
        return deleteflight(f1);
    }
    else if (compareStrings(choice, "3"))
    {
        system(CLEAR_SCREEN);
        return updateflight(f1);
    }
    else if (compareStrings(choice, "4"))
    {
        return SHOW_ADDED_FLIGHTS;
    }
    else if (compareStrings(choice, "5"))
    {
        return MAIN;
    }
    else
    {
        Invalid();
        return ADMIN_DISPLAY;
    }
}
//omar
int AdminCheck()
{
    string admin_password;
    cout << "\n\t    ==================================================\nAdmin Login Menu:\n"
         << string(17, '-') << endl;
    cout << "Password : ";
    cin >> admin_password;
    if (!compareStrings(admin_password, AdminPassword))
    {
        error("!!!! Invalid admin password !!!!");
        return MAIN;
    }
    return ADMIN_DISPLAY;
}
int UserDisplay()
{
    string choice;
    cout << "\n\t    ==================================================\nUser Menu:\n----------\n";
    cout << "1- Existing User\n2- New User\n3- Return to main menu\n\n";
    cout << "Your Choice : ";
    cin >> choice;
    if (compareStrings(choice, "1"))
    {
        return LOGIN;
    }
    else if (compareStrings(choice, "2"))
    {
        return SIGNUP;
    }
    else if (compareStrings(choice, "3"))
    {
        return MAIN;
    }
    else
    {
        Invalid();
        return USER;
    }
}
int MainDisplay()
{
    string choice;
    cout << "\n\t    ==================================================\nMain Menu:\n-----------\n";
    cout << "1- Admin\n2- User\n3- Exit\n\n";
    cout << "Your Choice : ";
    cin >> choice;
    if (compareStrings(choice, "1"))
    {
        return ADMIN_CHECK;
    }
    else if (compareStrings(choice, "2"))
    {
        return USER;
    }
    else if (compareStrings(choice, "3"))
    {
        return EXIT;
    }
    else
    {
        Invalid();
        return MAIN;
    }
}

// done by all
int main()
{
    srand(time(0));
    int state = MAIN;
    cout << "\n\t\tWelcome to Airline Reservation Application";
    do
    {
        system(CLEAR_SCREEN);
        if (state == EXIT)
        {
            break;
        }
        switch (state)
        {
        case MAIN:
            state = MainDisplay();
            break;
        case ADMIN_CHECK:
            state = AdminCheck();
            break;
        case ADMIN_DISPLAY:
            state = AdminDisplay();
            break;
        case USER:
            state = UserDisplay();
            break;
        case LOGIN:
            state = LoginDisplay();
            break;
        case SIGNUP:
            state = SignupDisplay();
            break;
        case PASSENGER:
            state = PassengerDisplay();
            break;
        case SHOW_NEW_TICKET:
            state = Show_New_Ticket_Display();
            break;
        case SHOW_ALL_TICKETS:
            state = Show_All_Tickets_Display();
            break;
        case SHOW_ADDED_FLIGHTS:
            state = ShowFlightsDisplay();
            break;

        default:
            Invalid();
            state = MAIN;
            break;
        }
    } while (true);
    cout << "\t\tThank you for using our application!\n\t\t" << string(36, '=') << endl;
    cout << "Press Enter to exit...";
    getchar();
    getchar();
    return 0;
}