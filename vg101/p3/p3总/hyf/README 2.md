### In this parkingarea program(part 1)

#### I created two basic classes Ticket and Vehicle. 

##### In Vehicle classes
###### I write six private characters, which are 
###### 1).licensePlate (used to find the car)
###### 2).type (represented its type, whether it's a car or a bike or a motorcycle or a van)
###### 3).floor and column (represents its parking place, if the parkingarea is free, then the car would be arranged with a parking slot.)
###### 4).arrtime and deptime (used to calculate the price) in the time()function, the arrival time and departure time will be recorded.

###### I write several functions in the Vehicle class
###### 1).parking function: change the "X"(which means that the parking slot has been occupied) into the type(which means the parking area is free again.)
###### 2).price function: get the arrival time and departure time through the time() function, and calculate the parking duration using the difftime()function and calculate the price.
###### 3).parkingcar function: search the parking area, to find a free slot, if found then set the column and floor characters of the vehicle, which means parking the car.



##### In Basic Ticket class
###### I write one pure virtual function printTicket(), used both in ArrTicket and DepTicket

##### The ArrTicket class
###### It is derived from the Basic Ticket classes.
###### In this class, I write three private characters:
###### 1).time
###### 2).floor
###### 3).column
###### In this class, I write two functions 
###### 1).an arrticket constructor: set the time, floor, and column of the arrticket as the car.
###### 2).printTicket()

##### The DepTicket class
###### It is derived from the Basic Ticket classes.
###### In this class, I write three private characters:
###### 1).price
###### 2).timespent
###### 3).type
###### In this class, I write two functions 
###### 1).an depticket constructor: set the price, timespent, and type of the arrticket as the car.
###### 2).printTicket()

#### In the demonstration part(main part)
##### In initialization part
###### I used a map to record each type's card. The make_pair function is used to insert <type,price> to map, which solves the problem that array and vector cannot include two different type data. 
###### then I constructed a new vehicle according to the information given by the user
##### In the printing ticket part, there are two parts.
###### The first one is arrival.
###### The second one is departure. In the departure part, if the car is not found, then it will return "Wrong Command, Please Enter Again!"

#### User guidelines:
##### 1).first input the unit price for each type (following the guide)
##### 2).then choosing 1 or 0 representing entering or departing 
##### 3).input car license licensePlate
##### 4).input vehicle type choosing from the option given by the computer.



