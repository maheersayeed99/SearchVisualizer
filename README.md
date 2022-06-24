# Search Visualizer
## Description
This is a program that tests the speed and efficiency of different graph search algorithms. It accomplishes this by generating a maze, and placing a marker in a random maze cell. The program will then find the marker using different search algorithms based on user input. After the marker is found, a return path will be drawn to the start marker. Statitstics such as search time and search efficiency will be listed in the side menu.
![Depth First Search with 125 X 250 Maze](https://github.com/maheersayeed99/SearchVisualizer/blob/main/images/Screen%20Shot%202022-06-23%20at%2010.03.54%20PM.png)
## Running the Application
Cmake is used to build and run the program. Create a build directory outside the repository and enter
`cmake add ./SearchVisualizer`. After this, build the program with the command `cmake --build . --target maze --config Release`. 'maze' is the name of the target executable for this program.  
Once the project is built, run by opening the maze.app file `open ./maze/maze.app --args rows`. rows is an integer that represents the number of rows in the maze. The number of columns will be twice the number of rows. A default value of 25 is used for rows in this program.
## Controls
`R` Generates a new maze with a recursive backtracking algorithm.  
`SHIFT + R` Animates the maze generation process and draws it on the window.  
`D` Finds the marker using depth first search. The recursive algorithm is found in maze.h.   
`B` Finds the marker using breadth first search. The iterative queue based algorithm is found in maze.h.  
`ESC` Exits the program
## Menu
After each search, the time taken in seconds is printed on the menu.  
The total number of cells visited before the marker is found is recorded.  
The length of the return path is recorded.  
The percentage of the total cells that needed to be explored for the search to be successful is recorded.  
The efficiency is recorded as the percentage of similarity between the visited and path cells.  
