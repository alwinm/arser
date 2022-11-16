# Arser

A parser with less p (pain? prettiness? pestilence? performance?)

Surely worse than other forms of taking input into your program.

arser.hpp is a header file with the meat of the repo. 

Errors, printfs, and logging are up to you, except in the explicit printing function ```map_printer```.

# C++ Requirements

```
#include <string> // C++98
#include <unordered_map> // C++11
#include <fstream> //
```

# Rules for input file contents and argc/argv 

Anything after # for a given file line or argv string is a comment

Whitespace is stripped from the left and right for keys and for values.

An assigning line must be of form (key)=(value)


# Usage
```
void map_from_file(std::unordered_map<std::string,std::string>& map, std::string input_filename)

arser::map_from_file(map,input_filename); // Adds key/value pairs to map from input filename


void map_from_arg(std::unordered_map<std::string,std::string>& map, int argc, char** argv)

arser::map_from_arg(map,argc,argv); // Adds key/value pairs to map from argc/argv command line input


void map_from_hybrid(std::unordered_map<std::string,std::string>& map, int argc, char** argv)

arser::map_from_hybrid(map,argc,argv); // Adds key/value pairs from map by first attempting each argument as an assignment key=value, and as a filename upon failure
  
  
void assign_from_map(std::unordered_map<std::string,std::string>& map, T& x, S string)

arser::assign_from_map(map,variable,key); // Converts map[key] according to type of variable and assigns
```

# Examples

main.cpp is provided as a basic example

test.input and test.input2 are provided as example inputs 