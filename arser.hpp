/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>
 */

/*
Alwin Mao
https://github.com/alwinm/arser
 */



#include <string>
#include <unordered_map>
#include <fstream>
namespace arser {

  void assign(int& x, std::string string)
  {
    x = std::stoi(string);
  }

  void assign(long& x, std::string string)
  {
    x = std::stol(string);
  }

  void assign(long long& x, std::string string)
  {
    x = std::stoll(string);
  }

  void assign(unsigned long& x, std::string string)
  {
    x = std::stoul(string);
  }

  void assign(unsigned long long& x, std::string string)
  {
    x = std::stoull(string);
  }

  void assign(float& x, std::string string)
  {
    x = std::stof(string);
  }

  void assign(double& x, std::string string)
  {
    x = std::stod(string);
  }

  void assign(long double& x, std::string string)
  {
    x = std::stold(string);
  }

  void assign(char* x, std::string string)
  {
    strcpy(x, string.c_str());
    //
  }

  void assign(const char* x, std::string string)
  {
    // NOTE: THIS becomes null if/when string is destroyed
    // x = string.c_str();
    // What should I do about attempts to pass const char* to assign?
  }

  void assign(std::string& x, std::string string)
  {
    //x.assign(string); // also works but less obvious
    x = string;
  }  

  
  
  template<typename T, typename S>
  void assign_from_map(std::unordered_map<std::string,std::string>& map, T& x, S string)
  {
    std::string key(string);
    if (map.count(key) == 1) assign(x,map[key]);
  }  
  
  void ltrim(std::string& string)
  {
    string.erase(string.begin(),
		 std::find_if(
			      string.begin(),
			      string.end(),
			      [](unsigned char ch) {return !std::isspace(ch);}
			      )
		 );
  }

  void rtrim(std::string& string)
  {
    string.erase(
		 std::find_if(
			      string.rbegin(),
			      string.rend(),
			      [](unsigned char ch) {return !std::isspace(ch);}
			      ).base(),
		 string.end()
		 );
  }

  void trim(std::string& string)
  {
    ltrim(string);
    rtrim(string);
  }
  
  
  bool map_add_line(std::unordered_map<std::string,std::string>& map, std::string line)
  {
    size_t pos;

    // Anything after # is a comment
    pos = line.find('#');
    if (pos != std::string::npos) line.erase(pos);

    // If line is empty after removing comments, return
    if (line.empty()) return true;
    
    pos = line.find('=');

    if (pos == std::string::npos) {
      return false;
    }    
    
    std::string key = line.substr(0, pos);
    std::string val = line.substr(pos + 1, std::string::npos);
    trim(key);
    trim(val);
    map[key] = val;
    return true;
  }

  void map_from_file(std::unordered_map<std::string,std::string>& map, std::string input_filename)
  {
    std::ifstream infile(input_filename);
    std::string line;
    
    if (not infile.is_open()) return;
    while (std::getline(infile, line))
    {
      map_add_line(map,line);
    }    
  }

  void map_from_arg(std::unordered_map<std::string,std::string>& map, int argc, char** argv)
  {
    // Skip the first arg since it's executable name
    for (int i=1;i<argc;i++) {
      map_add_line(map,argv[i]);
    }    
    
  }
  
  void map_from_hybrid(std::unordered_map<std::string,std::string>& map, int argc, char** argv)
  {
    // This wild beast attempts to interpret each argv as an assignment,
    // otherwise attempts to interpret as a filename
    // Everything is in intuitive order
    
    
    // Skip the first arg since it's executable name
    for (int i=1;i<argc;i++) {
      if (!map_add_line(map,argv[i])) {
	map_from_file(map,std::string(argv[i]));
      }
    }
  }


  void map_printer(std::unordered_map<std::string,std::string>& map)
  {
    for (std::pair<std::string,std::string> const &pair: map) {
      printf("map['%s']='%s'\n",pair.first.c_str(),pair.second.c_str());
    }
  }
  

  
}
