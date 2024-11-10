## Inspiration
Alice's journey in Wonderland resembles the strange, unpredictable patterns from Conway's Game of Life. Conway's classic game follows 2 simple rules, but they lead to strange and mesmerizing patterns, just like something brewed from Wonderland. Alice navigates through Wonderland using logic just like the future generations. This inspired us to use logic gates to develop a circuit that computes the generations.

## The Twist!
The rules of the game are simple, however, this is Wonderland! Life is full of twists and turns. The unexpected occurrence in this circuit is that a random cell in the generation may become ALIVE! This goes against Conway's rules... But this is Alice's Wonderland and anything in this generation is possible!

## How does the project work?
This project uses Software and Hardware to perform Conway's Game of Life with a twist. It is built using C++ to operate an Arduino UNO R4 Microcontroller. The microcontroller stores the current generation in a matrix. The microcontroller also computes the number of neighbors for each cell in another matrix. The binary representation of the number of neighbors is then used to set the outputs as LOW or HIGH.

The outputs act as inputs in the logical circuit. The logical circuit consists of Logical AND, Logical OR, and Logical NOT gates. The gates have been built using NPN Transistors. The inputs power the circuit and give one output. The output will be HIGH if the cell stays ALIVE or LOW if the cell stays DEAD for the next generation. This output is read by the microcontroller as an input.

Based on the input the Microcontroller receives, it changes the state of the cell for the next generation. After determining the complete generation, the grid is displayed using LED Lights. This process is repeated continuously in the flash of a second.

## Challenges we ran into
We faced various challenges while building this project.
 - Building a Logical Circuit is a complicated process, especially with just NPN Transistors. Maintaining the correct voltage and providing precise amounts of resistance is critical for obtaining accurate calculations. This was a tricky task, and it led to a few electrical components getting burned.
 - Communicating between the software and the hardware has to be perfect. This cannot be achieved on the first try. There was no way for us to debug the code on the microcontroller and the logical circuit. For us to view the correct results, we had to have both the components of our project perfect. The challenging part was to find the perfect time to deliver the inputs and read the outputs from the circuit as the computations are done very fast.
 - Integrating the electronic circuit with Conway’s Game of Life was another challenge. Mapping the game’s 2D grid to a physical LED layout while ensuring the correct implementation of Conway’s rules (birth, survival, and death of cells) took several iterations. It was tricky to synchronize the LED behavior with the game logic, especially within the hardware constraints.

## Accomplishments that we're proud of
This project was an excellent and educative journey for us. While we accomplished many things, a few of them are:
 - Building a project with software and hardware components. We had no professional experience working on circuits and integrating them with software, but we are proud to have successfully built a project with both aspects working perfectly with each other.
 - While building the logical circuit and playing with voltages was tricky, we are proud to have learned how to handle various problems faced while building this project.
 - Learning about logical circuits has given us an insight into how computers and other devices do computations. While this project is not as sophisticated as an actual computer, it gives us an idea of how challenging it would be to have millions of transistors and make them work with each other.

## What's next for Alice's Game of Life
We have successfully built a circuit that computes a cell's future state based on the current state and the number of neighbors. We plan to build a larger circuit that computes the neighbors of each cell. We plan to use a combination of full adders and logical gates using transistors and compute the sum of all the neighbors of all the cells. This would make this project heavily dependent on the hardware components, however, it will also make it more difficult to read the output and use it to determine the output in code.
