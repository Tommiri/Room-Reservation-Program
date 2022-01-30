## Hotel room reservation program
### Final course project for C++ Basics

#### Functionality

##### struct reservation
Reservation number  
Customer name  
Duration of stay  
Room size  
Room discount  
Room price  
Final price  

##### main()
Welcome message  
Prompt user for input  
-> Book a room  

##### BookRoom function (vector &rooms)
Check if all rooms are reserved  
  
If yes:  
Inform user and send back to main menu.   
  
Else:  
Prompt user for duration of stay  
Prompt user for room size  
Prompt user for name  
Generate room price  
Print reservation details  

Ask user for confirmation  

If yes:  
Generate reservation number    
Assign room details to either the first or last half of rooms vector depending on room size  
Return to main menu  

Else: return to main menu  

##### Main menu
Prompt user for input  
-> Manage your reservation  

##### ManageReservation function (vector &rooms)
Prompt user for search parameters  
-> Reservation number  

Prompt user for reservation number  
Loop through reservation numbers in the rooms vector to find a match, then assign the reference  
value of the matching room to a pointer  

If no match is found:  
Inform user  
Return to main menu  

Else:  
Greet user by name  
Prompt user for action  

-> View my reservation  
Print out reservation details  

-> Edit my reservation  
Call the EditReservation function with room pointer  

-> Back to main menu  
Return to main menu  

##### EditReservation function (reservation *room)
Prompt user for action  

-> Duration of stay  
Prompt user for new duration of stay and assign it to the pointer  
Calculate new price and print it out  

-> Room type  
Prompt user if they want to change their room type  

If yes:  
Assign new room type to pointer  
Calculate new price and print it out  

Else:  
Return to previous menu  

-> Name  
Prompt user for new name  
Assign new name to pointer and print out a success message  

-> Cancel my reservation  
Prompt user for confirmation on cancellation  

If yes:  
Empty pointer values  
Print out a success message  
Return to main menu  

Else:  
Return to previous menu  

-> Back  
Return to previous menu  

##### IsRoomReserved function (reservation room)
Check if given room has a reservation number different from 0  

If yes:  
Return true (room is reserved)  

Else:  
Return false (room is available)  

Works since a room's reservation number will always be 0 unless it is reserved  


#### Additional features

In addition to the given requirements for features in the assignment, my program has:  

- The possibility to search for reservations using either reservation number or name  
- The possibility to edit everything in your reservation with updating prices  
- A well functioning and user friendly interface with plenty of checks for edge cases and solutions for them  












