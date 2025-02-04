# Yahtzee C++  

## Author  
Saurav Dahal  

## Description  
This project is a C++ implementation of the popular dice game **Yahtzee**. The program supports both human and computer players and includes various features such as game serialization, AI assistance, and a structured tournament mode.  

## Features  

### Implemented Features  
- **AI Player**: The computer can make strategic moves based on the best possible category available.  
- **Tournament Mode**: Multiple rounds where a human competes against the computer.  
- **Scorecard Assistance**: The program provides hints on possible scoring categories.  
- **Saving & Loading**: The game state can be saved and loaded using a serialization system.  

### Missing Features  
- The game does not support suspending a turn without saving progress.  
- Available scoring categories are not displayed immediately after each roll, only at the start of a turn.  

## Classes & Data Structures  

### **Game Flow Management**  
- **Tournament Class**: Manages multiple rounds of Yahtzee.  
- **Round Class**: Handles each round of the tournament.  
- **Turn Class**: Manages individual player turns.  

### **Player System**  
- **Player Class**: Base class for human and computer players.  
- **Human Class**: Manages human player decisions.  
- **Computer Class**: Implements AI logic for playing Yahtzee.  

### **Core Game Mechanics**  
- **Dice Class**: Manages rolling dice and storing results.  
- **ScoreCard Class**: Maintains and calculates player scores.  
- **Serialization Class**: Handles saving and loading game data.  

## Inheritance & Polymorphism  
- **Human and Computer classes inherit from the Player class**, allowing polymorphic behavior for taking turns.  
- **Player Class defines a virtual playTurn() function**, which is implemented differently for human and computer players.  

## Installation & Usage  

### **Requirements**  
- C++ Compiler (G++ or Visual Studio C++)  
- Standard Template Library (STL)  
- `chrono` library for timing functions  

### **Compilation**  
Use the following command to compile the program:  
```bash
g++ -o yahtzee Dice.cpp Player.cpp Round.cpp ScoreCard.cpp Turn.cpp Yahtzee.cpp -std=c++11
```

### **Running the Program**  
```bash
./yahtzee
```

### **Saving & Loading**  
- The game automatically saves progress after each turn.  
- Use the **loadGame()** function to restore a previous game state.  

## Debugging & Development Log  
The project was developed over a period of **77 hours**, with detailed logs of debugging sessions, feature implementations, and AI strategy improvements. The logs document how strategies evolved, how bugs were resolved, and how the AI was designed to optimize decision-making.  

## AI Assistance  
- Used AI tools to **design the computer strategy** but did not copy any AI-generated code.  
- AI helped debug issues and improve documentation readability.  

## Future Improvements  
- Display available scoring categories after every roll.  
- Implement an option to pause the game without saving progress.  
- Enhance AI decision-making with more advanced probabilistic strategies.  
