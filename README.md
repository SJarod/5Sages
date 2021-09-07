# Le dîner des 5 sages
Jarod Sengkeo

### Description
The program is called 5sage. It is a console program that simulates the dinner of 5 (or more) wise men.
To use the program, follow the instructions on the console when it launches.

### UI
The first row shows the state of the wise men :
T : thinking
E : eating
W : waiting
D : done

  T  T  T  T  T

The second tow shows the state of every chopsticks :
0 : chopstick available
1 : chopstick unavailable

0  0  0  0  0


### Features
###### Implemented
- multithreading (for every wise men)
- modifiable values for the dinner
	- dinner time
	- number of wise men
	- action time
- change the display between DEBUG or not
	- choose the display mode at start of program
	- DEBUG mode will show texts while PLAY mode will show a clean UI
	- in DEBUG mode, each wise man will try eating every 1 second
	- in PLAY mode, each wise man will try and retry until success
- make the wise men eat more or not
	- choose if the wise men can eat more than their dinner time
	- they can eat more : they will spend fewer time eating on their last round
	- they cannot eat more : they will always follow their eating rhythm
- display of a timer to help user to count

###### Next implementation
- show the thread's start and end time

### Problems/Bugs
- user can enter text instead of numbers in the first questions
- when there are a lot of wise men, the display will not be fast enough and not accurate