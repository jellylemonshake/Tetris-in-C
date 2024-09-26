# **Tetris Game in C**

## ***Introduction:***

This is a simplified version of the classic Tetris game written in C. The game involves a falling piece, known as a Tetrimino, which the player can control to fit within a 10x20 grid. The goal is to clear lines by filling them completely with pieces. This version supports basic controls like moving pieces left, right, rotating them, and speeding up the descent.

![Screenshot (114)](https://github.com/user-attachments/assets/c77654ec-ac69-45c9-8bb7-1e800a1c5cf5)

## ***Features:***

### 1. __Randomly generated Tetrimino pieces:__ 
	
 Pieces are selected randomly from the 7 classic Tetris shapes.

### 2. __Piece movement and rotation:__

You can move pieces left **(a)**, right **(d)**, rotate them **(w)**, and drop them faster **(s)**.

### 3. __Line clearing:__
   
When a row is completely filled, it clears, and all rows above move down.

### 4. __Basic collision detection:__
	
Prevents pieces from moving out of bounds or into other pieces.

## ***Controls:***
* **a:** Move piece left

* **d:** Move piece right

* **w:** Rotate piece

* **s:** Drop piece faster

## **How to Compile and Run**

## ***Requirements:***

* A C compiler (GCC recommended)

* A terminal or command prompt
  
## **Steps to Compile:**
* Save the file as **Tetris.c**

* Open a terminal and navigate to the directory containing the **Tetris.c** file.

## ***Compile the code using the following command:***

	gcc ./Tetris.c -o ./tetris.exe

## ***Run the compiled game using:***

	./tetris.exe

## Important Notes:
* This code is designed for Windows and uses Windows-specific headers like **windows.h** and **conio.h** for handling input and screen clearing.

* **system("CLS")** is used to clear the console, which may not work on non-Windows systems. Similarly, **Sleep(500)** is used to control the speed of the game.

## Game Loop and Input Handling
### **Game Loop:** 
1. **The game runs in an infinite loop where the following occurs:**
* Handle user input using **_kbhit()** and **_getch()** to detect key presses.
* Move the current Tetrimino down automatically over time.
* Check for collisions with the walls or other pieces.
* Place the piece if it collides and spawn a new piece.
* Clear any full rows and update the grid.
* Redraw the entire game to the console.
  
### **Input Handling:**
* Key presses are detected asynchronously with the help of **_kbhit()** and **_getch()** to allow for smooth movement of the pieces.
* 
## Code Overview
1. **Shapes Definition:**
    The shapes array stores 7 different Tetrimino shapes. Each shape is defined in a 4x4 matrix.
2. **Tetris Struct:**
    Stores the current state of the game, including the grid, the current piece, and its position.
3. **Movement and Collision Detection:**
    Functions like **moveLeft()**, **moveRight()**, **moveDown()**, and **rotatePiece()** handle player movement, ensuring the pieces stay within bounds and don’t collide with other placed pieces.
4. **Line Clearing:**
    The **checkLines()** function checks the grid for full rows and clears them if necessary.
5. **Drawing the Grid:**
    The **draw()** function clears the screen and redraws the game grid along with the current falling piece.

## Improvements
### The game could be expanded with more features such as:
* A score system
* Faster game speeds over time
* Better piece rotation handling near walls
* Music and sound effects

