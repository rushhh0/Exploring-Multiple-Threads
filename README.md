# Exploring-Multiple-Threads

Rushi Trivedi
4348.501

Project #2 Exploring Multiple Threads

Project Description:

A hotel is simulated by using threads and semaphores to model customer and employee behavior. The hotel to be simulated has two employees at the front desk to register guests and two bellhops to handle guests’ bags.  A guest will first visit the front desk to get a room number.  The front desk employee will find an available room and assign it to the guest.  If the guest has less than 3 bags, the guest proceeds directly to the room.  Otherwise, the guest visits the bellhop to drop off the bags.  The guest will later meet the bellhop in the room to get the bags, at which time a tip is given.  

My File Description:

Hotel.cpp contains Guest Class, FrontDesk Class, Bellhop Class and Main:

Guest Class:
- The Guest class represents a hotel guest. Each guest is assigned a unique ID, a room number, and a random number of bags.
- Guests enter the hotel, register at the front desk, receive a room key, and optionally request bellhop assistance for their luggage.
- They then enter their assigned room, and later retire for the evening.

FrontDesk Class:
- The FrontDesk class represents a front desk employee. 2 front desk employees are created to handle guest registrations.
- Front desk employees wait for guests to be ready, assign a room number, and provide room keys.

Bellhop Class:
- The Bellhop class represents a bellhop employee. 2 bellhop employees are created to handle luggage assistance requests from guests.
- Bellhops receive luggage requests from guests, assist with the luggage, and deliver it to the guest's room.

Main:
- The main function serves as the entry point of the program. It initializes semaphores, creates threads for front desk employees, bellhops, and guests, and manages the overall flow of the simulation. 
- Main function is responsible for cleaning up resources after the simulation ends.

How to Compile:

g++ -std=c++11 Hotel.cpp -lpthread -o Hotel

Note: Hotel is the name of my executable file.

How to Run:

./Hotel

Output:

Simulation starts
Front desk employee 0 created
Front desk employee 1 created
Bellhop 0 created
Bellhop 1 created
Guest 0 created
Guest 1 created
Guest 0 enters the hotel with 1 bags
Guest 2 created
Guest 3 created
Guest 1 enters the hotel with 2 bags
Guest 2 enters the hotel with 3 bags
Guest 4 created
Front desk employee 1 registers guest 1 and assigns room 2
Front desk employee 0 registers guest 0 and assigns room 1
Guest 1 receives room key for room 2 from front desk employee 1
Guest 1 enters room 2
Guest 3 enters the hotel with 1 bags
Guest 1 retires for the evening
Guest 1 joined
Guest 4 enters the hotel with 0 bags
Guest 0 receives room key for room 1 from front desk employee 0
Guest 5 created
Guest 0 enters room 1
Front desk employee 0 registers guest 3 and assigns room 4
Front desk employee 1 registers guest 2 and assigns room 3
Guest 3 receives room key for room 4 from front desk employee 0
Guest 0 retires for the evening
Guest 3 enters room 4
Guest 3 retires for the evening
Guest 3 joined
Guest 2 receives room key for room 3 from front desk employee 1
Guest 0 joined
Front desk employee 0 registers guest 4 and assigns room 5
Guest 2 requests help with bags
Bellhop 0 receives bags from guest 2
Guest 4 receives room key for room 5 from front desk employee 0
Guest 2 enters room 3
Bellhop 0 delivers bags to guest 2
Guest 4 enters room 5
Guest 2 receives bags from bellhop 0 and gives tip
Guest 2 retires for the evening
Guest 4 retires for the evening
Guest 2 joined
Guest 4 joined
Guest 6 created
Guest 5 enters the hotel with 3 bags
Front desk employee 1 registers guest 5 and assigns room 6
Guest 6 enters the hotel with 5 bags
Guest 7 created
Guest 5 receives room key for room 6 from front desk employee 1
Guest 8 created
Guest 9 created
Guest 7 enters the hotel with 0 bags
Guest 5 requests help with bags
Guest 9 enters the hotel with 1 bags
Guest 8 enters the hotel with 2 bags
Front desk employee 0 registers guest 6 and assigns room 7
Front desk employee 1 registers guest 7 and assigns room 8
Guest 10 created
Guest 6 receives room key for room 7 from front desk employee 0
Guest 7 receives room key for room 8 from front desk employee 1
Bellhop 1 receives bags from guest 5
Front desk employee 1 registers guest 9 and assigns room 9
Guest 7 enters room 8
Front desk employee 0 registers guest 8 and assigns room 10
Guest 5 enters room 6
Guest 10 enters the hotel with 0 bags
Guest 9 receives room key for room 9 from front desk employee 1
Guest 7 retires for the evening
Guest 11 created
Guest 6 requests help with bags
Guest 8 receives room key for room 10 from front desk employee 0
Bellhop 0 receives bags from guest 6
Guest 12 created
Guest 9 enters room 9
Guest 6 enters room 7
Bellhop 1 delivers bags to guest 5
Guest 11 enters the hotel with 3 bags
Guest 7 joined
Guest 9 retires for the evening
Guest 5 receives bags from bellhop 1 and gives tip
Guest 5 retires for the evening
Guest 5 joined
Front desk employee 0 registers guest 11 and assigns room 12
Guest 9 joined
Front desk employee 1 registers guest 10 and assigns room 11
Bellhop 0 delivers bags to guest 6
Guest 10 receives room key for room 11 from front desk employee 1
Guest 11 receives room key for room 12 from front desk employee 0
Guest 8 enters room 10
Guest 6 receives bags from bellhop 0 and gives tip
Guest 6 retires for the evening
Guest 6 joined
Guest 11 requests help with bags
Guest 10 enters room 11
Bellhop 1 receives bags from guest 11
Guest 8 retires for the evening
Guest 10 retires for the evening
Guest 10 joined
Guest 8 joined
Guest 11 enters room 12
Bellhop 1 delivers bags to guest 11
Guest 11 receives bags from bellhop 1 and gives tip
Guest 11 retires for the evening
Guest 11 joined
Guest 13 created
Guest 12 enters the hotel with 4 bags
Guest 14 created
Front desk employee 0 registers guest 12 and assigns room 13
Guest 13 enters the hotel with 5 bags
Guest 12 receives room key for room 13 from front desk employee 0
Guest 14 enters the hotel with 4 bags
Guest 15 created
Front desk employee 1 registers guest 13 and assigns room 14
Guest 12 requests help with bags
Guest 16 created
Guest 13 receives room key for room 14 from front desk employee 1
Guest 15 enters the hotel with 2 bags
Front desk employee 0 registers guest 14 and assigns room 15
Guest 17 created
Guest 16 enters the hotel with 3 bags
Front desk employee 1 registers guest 15 and assigns room 16
Bellhop 0 receives bags from guest 12
Guest 15 receives room key for room 16 from front desk employee 1
Guest 14 receives room key for room 15 from front desk employee 0
Front desk employee 0 registers guest 16 and assigns room 17
Guest 17 enters the hotel with 0 bags
Guest 13 requests help with bags
Front desk employee 1 registers guest 17 and assigns room 18
Bellhop 1 receives bags from guest 13
Guest 18 created
Guest 13 enters room 14
Guest 16 receives room key for room 17 from front desk employee 0
Guest 15 enters room 16
Guest 19 created
Guest 12 enters room 13
Bellhop 1 delivers bags to guest 13
Guest 20 created
Guest 13 receives bags from bellhop 1 and gives tip
Guest 13 retires for the evening
Guest 13 joined
Guest 18 enters the hotel with 4 bags
Guest 15 retires for the evening
Guest 15 joined
Bellhop 0 delivers bags to guest 12
Guest 21 created
Guest 14 requests help with bags
Guest 17 receives room key for room 18 from front desk employee 1
Guest 20 enters the hotel with 1 bags
Guest 22 created
Guest 16 requests help with bags
Guest 12 receives bags from bellhop 0 and gives tip
Bellhop 0 receives bags from guest 16
Bellhop 1 receives bags from guest 14
Guest 14 enters room 15
Guest 22 enters the hotel with 0 bags
Guest 21 enters the hotel with 4 bags
Front desk employee 1 registers guest 20 and assigns room 20
Guest 19 enters the hotel with 3 bags
Guest 12 retires for the evening
Guest 12 joined
Guest 17 enters room 18
Guest 16 enters room 17
Front desk employee 0 registers guest 18 and assigns room 19
Bellhop 0 delivers bags to guest 16
Bellhop 1 delivers bags to guest 14
Guest 18 receives room key for room 19 from front desk employee 0
Guest 14 receives bags from bellhop 1 and gives tip
Guest 18 requests help with bags
Guest 23 created
Front desk employee 1 registers guest 22 and assigns room 21
Guest 16 receives bags from bellhop 0 and gives tip
Guest 22 receives room key for room 21 from front desk employee 1
Guest 20 receives room key for room 20 from front desk employee 1
Bellhop 0 receives bags from guest 18
Guest 20 enters room 20
Guest 14 retires for the evening
Guest 17 retires for the evening
Guest 22 enters room 21
Guest 22 retires for the evening
Guest 22 joined
Guest 18 enters room 19
Guest 16 retires for the evening
Guest 16 joined
Guest 14 joined
Guest 17 joined
Front desk employee 0 registers guest 21 and assigns room 22
Guest 20 retires for the evening
Guest 21 receives room key for room 22 from front desk employee 0
Front desk employee 1 registers guest 19 and assigns room 23
Bellhop 0 delivers bags to guest 18
Guest 19 receives room key for room 23 from front desk employee 1
Guest 18 receives bags from bellhop 0 and gives tip
Guest 21 requests help with bags
Guest 19 requests help with bags
Guest 18 retires for the evening
Guest 23 enters the hotel with 2 bags
Bellhop 1 receives bags from guest 21
Front desk employee 0 registers guest 23 and assigns room 24
Guest 21 enters room 22
Guest 20 joined
Guest 18 joined
Bellhop 0 receives bags from guest 19
Guest 24 created
Guest 19 enters room 23
Guest 23 receives room key for room 24 from front desk employee 0
Bellhop 0 delivers bags to guest 19
Guest 23 enters room 24
Guest 21 receives bags from bellhop 1 and gives tip
Guest 21 retires for the evening
Bellhop 1 delivers bags to guest 21
Guest 24 enters the hotel with 1 bags
Guest 19 receives bags from bellhop 0 and gives tip
Guest 23 retires for the evening
Front desk employee 1 registers guest 24 and assigns room 25
Guest 19 retires for the evening
Guest 24 receives room key for room 25 from front desk employee 1
Guest 23 joined
Guest 21 joined
Guest 19 joined
Guest 24 enters room 25
Guest 24 retires for the evening
Guest 24 joined
Simulation ends
