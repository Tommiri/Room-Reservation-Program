#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct reservation
{
    int reservationNumber{};
    string customerName{};
    int durationOfStay{};
    int roomSize{};
    int roomDiscount{};
    int roomPrice{};
    int finalPrice{};
};

void BookRoom(vector<reservation> &rooms);
void ManageReservation(vector<reservation> &rooms);
void EditReservation(reservation *room);
bool IsRoomReserved(reservation room);

int main()
{
    int option{};
    bool error{};
    bool isActive{};

    srand(time(NULL));

    // Declaring the amountOfRooms variable and initializing it to be a random even number between 40 and 300
    int amountOfRooms = (20 + rand() % (150 - 20 + 1)) * 2;

    vector<reservation> rooms(amountOfRooms);

    cout << "\nWelcome to our hotel's reservation page!\n";
    cout << "\nWe offer two types of room:\n";
    cout << "Single room --- 100€/night\nDouble room --- 150€/night\n";

    // Start of the main loop which runs while the isActive bool is set to true
    do
    {
        cout << "\nWhat would you like to do?\n";

        // Basic user input error check using an error bool, repeated over and over in the code in similar fashion
        do
        {
            // Setting error to false to avoid infinite looping
            error = false;
            cout << "1. Book a room\n2. Manage your reservation\n3. Quit\n";
            cin >> option;

            // If user inputs something other than the expected data type, or if user inputs an integer thats less than 1 or higher than 3
            if (cin.fail() || option < 1 || option > 3)
            {
                // Set error to true to loop to the start
                error = true;
                // Clear the error flag on cin
                cin.clear();
                /* Ignore the last 10000 (arbitrary, could be any large number) characters of user input until the program comes across a new line */
                cin.ignore(10000, '\n');
                // Print out an error message
                cout << "\nERROR: Please enter either 1, 2 or 3.\n\n";
            }

        } while (error);

        switch (option)
        {
            case 1:
                BookRoom(rooms);
                isActive = true;
                break;
            case 2:
                ManageReservation(rooms);
                isActive = true;
                break;
            case 3:
                cout << "\nThank you for booking with us!\nGoodbye!" << endl;
                isActive = false;
                break;
            default:
                cout << "FATAL ERROR: Exiting program";
                return EXIT_FAILURE;
        }
    } while (isActive);

    return EXIT_SUCCESS;
}

void BookRoom(vector<reservation> &rooms)
{
    bool error{};
    reservation room{};
    int option{};
    srand(time(NULL));

    // Checking if all rooms are reserved
    if (IsRoomReserved(rooms[(rooms.size() / 2) - 1]) && IsRoomReserved(rooms[rooms.size() - 1]))
    {
        cout << "\nUnfortunately all our rooms are currently booked. Please try again later!\n";
        return;
    }

    do
    {
        error = false;
        cout << "\nHow many days will you be staying with us?\n";
        cin >> room.durationOfStay;
        // Limiting the duration of stay to be between 1 and 180 days
        if (cin.fail() || room.durationOfStay < 1 || room.durationOfStay > 180)
        {
            error = true;
            cin.clear();
            cin.ignore(10000, '\n');
            if (room.durationOfStay < 1)
            {
                cout << "You have to stay for at least one day.\n";
            }
            else if (room.durationOfStay > 180)
            {
                cout << "You can stay with us for a maximum of 180 days.\n";
            }
            else
            {
                cout << "\nERROR: Please enter a valid value.\n\n";
            }
        }
    } while (error);

    do
    {
        error = false;
        cout << "\nWhat type of room would you like?\n";
        cout << "1. Single (100€/night)\n2. Double (150€/night)\n";
        cin >> room.roomSize;

        if (cin.fail() || room.roomSize < 1 || room.roomSize > 2)
        {
            error = true;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nERROR: Please enter either 1 or 2.\n\n";
        }
            // Checking if all single rooms are reserved. If yes, asking user if they want to cancel their reservation
        else if (room.roomSize == 1 && IsRoomReserved(rooms[(rooms.size() / 2) - 1]))
        {
            cout << "\nUnfortunately all of our Single rooms have been booked.\n";
            do
            {
                error = false;
                cout << "Would you like cancel your reservation?\n";
                cout << "1. Yes\n2. No\n";
                cin >> option;

                if (cin.fail() || option < 1 || option > 2)
                {
                    error = true;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\nERROR: Please enter either 1 or 2.\n";
                }
            } while (error);

            // If user want's to cancel their reservation, return to main
            if (option == 1)
            {
                return;
            }
                // Else loop to start and prompt for room size again
            else
            {
                error = true;
            }
        }
            // Same thing but with double rooms
        else if (room.roomSize == 2 && IsRoomReserved(rooms[rooms.size() - 1]))
        {
            cout << "\nUnfortunately all of our Double rooms have been booked.\n";
            do
            {
                error = false;
                cout << "Would you like cancel your reservation?\n";
                cout << "1. Yes\n2. No\n";
                cin >> option;

                if (cin.fail() || option < 1 || option > 2)
                {
                    error = true;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\nERROR: Please enter either 1 or 2.\n";
                }
            } while (error);

            if (option == 1)
            {
                return;
            }
            else
            {
                error = true;
            }
        }
    } while (error);

    do
    {
        error = false;
        cout << "\nPlease enter your name: ";
        // Using cin.ignore() to ignore previous new line created by user pressing enter and then using getline to get user's full name
        cin.ignore();
        getline(cin, room.customerName);

        if (cin.fail())
        {
            error = true;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "ERROR: Please enter a valid value.\n";
        }

    } while (error);

    // Creating a random value between 0 and 2 for roomDiscount and then assigning it a value of either 0, 10 or 20 depending on the random value
    room.roomDiscount = rand() % 3;

    switch (room.roomDiscount)
    {
        case 0:
            room.roomDiscount = 0;
            break;
        case 1:
            room.roomDiscount = 10;
            break;
        case 2:
            room.roomDiscount = 20;
            break;
        default:
            cout << "FATAL ERROR: Exiting room reservation. No reservation has been made.";
            return;
    }

    // Calculating room price and then adding on the discount
    room.roomPrice = room.durationOfStay * ((room.roomSize == 1) ? 100 : 150);
    room.finalPrice = room.roomPrice - room.roomPrice * (room.roomDiscount * 0.01);

    cout << "\nYour reservation details:\n";
    cout << "Duration of stay: " << room.durationOfStay << " days\n";
    cout << "Room type: ";

    if (room.roomSize == 1)
    {
        cout << "Single\n";
    }
    else
    {
        cout << "Double\n";
    }

    cout << "Name: " << room.customerName << "\n";
    cout << "Room price: " << room.finalPrice << "€\n";

    // Printing out the discount percentage if roomDiscount is other than 0
    if (room.roomDiscount != 0)
    {
        cout << "We applied a " << room.roomDiscount << "% discount to your reservation!\n";
    }

    do
    {
        error = false;
        cout << "\nConfirm your reservation?\n1. Yes\n2. No\n";
        cin >> option;

        if (cin.fail() || option < 1 || option > 2)
        {
            error = true;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "ERROR: Please enter either 1 or 2.\n\n";
        }
    } while (error);

    // If user doesn't want to confirm their reservation, return to main
    if (option == 2)
    {
        return;
    }
    else
    {
        do
        {
            // Creating a random reservation number and checking that it doesn't match with other reservation numbers
            error = false;
            room.reservationNumber = 10000 + (rand() % (99999 - 10000 + 1));

            for (int i = 0; i < rooms.size(); i++)
            {
                if (rooms[i].reservationNumber == room.reservationNumber)
                {
                    error = true;
                    break;
                }
            }
        } while (error);

        cout << "\nThank you for your reservation!\n";
        cout << "Your reservation number is " << room.reservationNumber << ".\n";
    }

    if (room.roomSize == 1)
    {
        // Looping through the first half (single rooms) the rooms vector looking for available rooms in order.
        for (int i = 0; i < (rooms.size() / 2); i++)
        {
            if (!IsRoomReserved(rooms[i]))
            {
                // When found, assign the room variable to the reference rooms vector at index i, therefore saving it in the original vector
                rooms[i] = room;
                // Break out of the loop to avoid unnecessary looping
                break;
            }
        }
    }
    else
    {
        // Same process for the second half (double rooms)
        for (int i = (rooms.size() / 2); i < rooms.size(); i++)
        {
            if (!IsRoomReserved(rooms[i]))
            {
                rooms[i] = room;
                break;
            }
        }
    }
}

void ManageReservation(vector<reservation> &rooms)
{
    int option{};
    int reservationNumber{};
    string name{};
    reservation *room{};
    bool error{};
    bool isActive{};

    do
    {
        error = false;
        cout << "\nHow would you like to search for your reservation?\n";
        cout << "1. Reservation number\n2. Name\n";
        cin >> option;

        if (cin.fail() || option < 1 || option > 2)
        {
            error = true;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nERROR: Please enter either 1 or 2.\n\n";
        }
    } while (error);

    // If user wants to search for their reservation with their reservation number
    if (option == 1)
    {
        do
        {
            error = false;
            cout << "\nPlease enter your reservation number: ";
            cin >> reservationNumber;

            if (cin.fail() || reservationNumber < 10000 || reservationNumber > 99999)
            {
                error = true;
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\nERROR: Your reservation number must be between 10000 and 99999\n\n";
            }
        } while (error);

        // Looping through all rooms searching for matches
        for (int i = 0; i <= rooms.size(); i++)
        {
            if (rooms[i].reservationNumber == reservationNumber)
            {
                // If found, setting the room pointer variable to the reference of the rooms vector at index i
                room = &rooms[i];
                // Breaking out of the loop after finding the match
                break;
            }
                /* Checking if the program has looped through the whole vector without finding a match
                since the last index of the vector is [rooms.size() - 1] */
            else if (i == rooms.size())
            {
                cout << "We could not find a reservation with your reservation number.\n";
                return;
            }
        }
    }
        // If user wants to search for their reservation using their name
    else
    {
        do
        {
            error = false;
            cout << "\nPlease enter your name: ";
            cin.ignore();
            getline(cin, name);

            if (cin.fail())
            {
                error = true;
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\nERROR: Please enter a valid value.\n\n";
            }
        } while (error);

        // Same process as with the reservation number but using the customerName variable
        for (int i = 0; i <= rooms.size(); i++)
        {
            if (rooms[i].customerName == name)
            {
                room = &rooms[i];
                break;
            }
            else if (i == rooms.size())
            {
                cout << "We could not find a reservation with your name.\n";
                return;
            }
        }
    }

    // Greeting the user with their name, note the arrow operator (->) since the program is using a pointer
    cout << "\nHello " << room->customerName << ". ";

    // Start of the main loop of the function
    do
    {
        isActive = false;

        do
        {
            error = false;
            cout << "What would you like to do?\n";
            cout << "1. View my reservation\n2. Edit my reservation\n3. Back to main menu\n";
            cin >> option;

            if (cin.fail() || option < 1 || option > 3)
            {
                error = true;
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\nERROR: Please enter either 1, 2 or 3.\n\n";
            }
        } while (error);

        switch (option)
        {
            // Printing out user's reservation details
            case 1:
                isActive = true;
                cout << "\nYour reservation details:\n";
                cout << "Reservation number: " << room->reservationNumber << "\n";
                cout << "Duration of stay: " << room->durationOfStay << " days\n";
                cout << "Room type: ";
                if (room->roomSize == 1)
                {
                    cout << "Single\n";
                }
                else
                {
                    cout << "Double\n";
                }
                cout << "Name: " << room->customerName << "\n";
                cout << "Room price: " << room->finalPrice << "€\n\n";
                break;
                // If user wants to edit their reservation
            case 2:
                isActive = true;
                // Calling the EditReservation function with the room pointer
                EditReservation(room);
                // After coming out of EditReservation: checking if user has cancelled their reservation
                if (!IsRoomReserved(*room))
                {
                    // Returning to main
                    return;
                }
                break;
            case 3:
                isActive = false;
                break;
            default:
                cout << "\nFATAL ERROR: Returning to main menu.\n";
                return;
        }
    } while (isActive);

    return;
}

// Simple function that checks for reserved rooms
bool IsRoomReserved(reservation room)
{
    // Since a room's reservation number is always 0 the program can check:
    // If the room's reservation number is different from 0
    if (room.reservationNumber != 0)
    {
        // Room is reserved, so return true
        return true;
    }
    else
    {
        // Room is available, so return false
        return false;
    }
}

void EditReservation(reservation *room)
{
    bool error{};
    int option{};

    do
    {
        error = false;
        cout << "\nWhat would you like to edit?\n";
        cout << "1. Duration of stay\n2. Room type\n3. Name\n4. Cancel my reservation\n5. Back\n";
        cin >> option;

        if (cin.fail() || option < 1 || option > 5)
        {
            error = true;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nERROR: Please enter one of the options.\n";
        }
    } while (error);

    switch (option)
    {
        // If user wants to change their duration of stay
        case 1:
            do
            {
                error = false;
                cout << "\nHow many nights do you wish to stay with us?\n";
                // Input new duration which then gets assigned to the room pointer therefore assigning it to the original room vector
                cin >> room->durationOfStay;

                if (cin.fail() || room->durationOfStay < 1 || room->durationOfStay > 180)
                {
                    error = true;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    if (room->durationOfStay < 1)
                    {
                        cout << "\nYou have to stay for at least one night.\n";
                    }
                    else if (room->durationOfStay > 180)
                    {
                        cout << "\nYou can stay with us for a maximum of 180 days.\n";
                    }
                    else
                    {
                        cout << "\nERROR: Please enter a valid value.\n";
                    }
                }
            } while (error);

            // Recalculating the room price
            room->roomPrice = room->durationOfStay * ((room->roomSize == 1) ? 100 : 150);
            room->finalPrice = room->roomPrice - room->roomPrice * (room->roomDiscount * 0.01);

            // Printing out the changes
            cout << "\nThe duration of your stay has successfully been changed to " << room->durationOfStay << " days.\n";
            cout << "Your room's new price is " << room->finalPrice << "€.\n\n";
            break;

            // If user wants to change their room type
        case 2:
            do
            {
                error = false;
                cout << "\nWould you like to change your room type to ";
                if (room->roomSize == 1)
                {
                    cout << "Double?\n";
                }
                else
                {
                    cout << "Single?\n";
                }
                cout << "1. Yes\n2. No\n";
                cin >> option;

                if (cin.fail() || option < 1 || option > 2)
                {
                    error = true;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\nPlease enter either 1 or 2.\n";
                }
            } while (error);

            if (option == 1)
            {
                if (room->roomSize == 1)
                {
                    room->roomSize = 2;
                    cout << "\nYour room type has been changed to Double.\n";
                }
                else
                {
                    room->roomSize = 1;
                    cout << "\nYour room type has been changed to Single.\n";
                }
            }
            else
            {
                cout << "\nNo changes have been made.\n\n";
            }

            room->roomPrice = room->durationOfStay * ((room->roomSize == 1) ? 100 : 150);
            room->finalPrice = room->roomPrice - room->roomPrice * (room->roomDiscount * 0.01);
            cout << "Your room's new price is " << room->finalPrice << "€.\n\n";
            break;

            // If user wants to change the name on the reservation
        case 3:
            do
            {
                cout << "\nWhat would you like to change the name on your reservation to?\n";
                cin.ignore();
                getline(cin, room->customerName);

                if (cin.fail())
                {
                    error = true;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\nERROR: Please enter a valid value.\n";
                }
            } while (error);

            cout << "\nThe name on your reservation has successfully been changed to " << room->customerName << ".\n\n";
            break;

            // If user wants to cancel their reservation
        case 4:
            do
            {
                error = false;
                cout << "\nAre you sure you want to cancel your reservation?\n";
                cout << "1. Yes\n2. No\n";
                cin >> option;

                if (cin.fail() || option < 1 || option > 2)
                {
                    error = true;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\nERROR: Please enter either 1 or 2.\n";
                }
            } while (error);

            // If yes, setting all room variables to 0
            if (option == 1)
            {
                room->customerName = {};
                room->durationOfStay = {};
                room->finalPrice = {};
                room->reservationNumber = {};
                room->roomDiscount = {};
                room->roomPrice = {};
                room->roomSize = {};
                cout << "\nYour reservation has been cancelled.\n";
            }
            else
            {
                cout << "\nNo changes have been made.\n\n";
                break;
            }
            break;

            // If user wants to go back
        case 5:
            // Break to go back to previous menu
            break;
        default:
            cout << "\nFATAL ERROR: Returning to previous menu. No changes have been made.\n";
            return;
    }
}