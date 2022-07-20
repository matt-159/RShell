## CS 100 Programming Project

# Project Information
Quarter and Year: Fall 2019 

# Introduction

The R’shell project will intake a line of Linux commands and reproduce results similar to the Linux terminal. Utilizing a composite pattern structure, the R’shell differentiates between different connector subclasses and splits input based on the connector. The composite portion of the design pattern is comprised of the connector subclasses, while the leaves will consist of a single command and its flags/parameters.

# Diagram

<img src="images/assign4omt.png?raw=true">

# Classes

The RShell class is the Driver class and will contain the main() function. 

The Parser class is a static class and is associated with the Command class because the splitOn functions is utilized by the Command class. The splitOn function takes in a string, sorts through, and separates the commands when a space is detected. Enumeration is used in order to allow for flexibility in the splitOn function.

The Executable class is a base class from which Command and Connector inherit their execute functions. This base class is useful because both Connector subclasses and Command utilize the execute function, but have completely different properties hence their separate classes.

The Command class inherits from the Executable Base class and is associated with Parser and Connector classes because of their usage of Command pointers. The execute function begins with splitting the cmd string on whitespace and does some cleanup depending on the existance of quotes. From there, the execute function passes the recently split string to execvp where the command will be executed. 

The Connector class declares two protected Command pointers, lhs and rhs, and declares the execute function as pure virtual. The Connector class inherits from the Executable base class and has an association with the Command class due to lhs and rhs being Command pointers. lhs and rhs represent the two sides of a connector, its left and right-hand sides, and are initialized in order for subclasses to inherit from the Connector class. 

The Connector subclasses are a class group that inherits from the Connector class. Each connector implements the execute function that executes specific commands based on the particular connector. To start, Connect_And’s execute function processes the lhs command and, if the lhs command returns a zero, the rhs command is processed. Connect_Or’s execute function operates opposite of Connect_And, wherein which lhs is processed and, in the case that the lhs returns a nonzero value, rhs is processed. Connect_Comment’s execute function simply returns the result of the lhs execute function since contents right of the ‘#’ symbol are comments, not commands. Connect_Semicolon’s execute function executes both the lhs and the rhs and returns the result of the rhs. 
