#include "arser.hpp"

void pmal(std::unordered_map<std::string,std::string>& map, std::string line)
{
  bool check = arser::map_add_line(map,line);
  if (!check) 
  {
    printf("Failed to print line: %s \n",line.c_str());
  }
}



void test1()
{
  std::unordered_map<std::string,std::string> map;
  // Basic tests
  arser::map_add_line(map,"a=1");
  arser::map_add_line(map,"b=2");
  arser::map_add_line(map,"c=3");

  // Comment tests
  
  pmal(map,"#comment=4");
  pmal(map,"comment#=4");
  pmal(map,"comment=#4");
  pmal(map,"d=4#comment");

  // Whitespace stripping tests
  arser::map_add_line(map," e=e");
  arser::map_add_line(map,"f =f");
  arser::map_add_line(map," g =g");
  arser::map_add_line(map," h = h");
  arser::map_add_line(map," i = i ");
  arser::map_add_line(map," j = j   \t");
  arser::map_add_line(map,"\tk = k   \t");
  arser::map_add_line(map,"L\t= \tL");
  arser::map_add_line(map,"M\n= \nM");    
  
  arser::map_printer(map);
  
}

void test2(int argc, char** argv)
{
  std::unordered_map<std::string,std::string> map;
  arser::map_from_file(map,"test.input");
  arser::map_from_arg(map,argc,argv);  
  arser::map_printer(map);
}

void test3(int argc, char** argv)
{
  std::unordered_map<std::string,std::string> map;
  //arser::map_from_file(map,"test.input");
  //arser::map_from_arg(map,argc,argv);
  arser::map_from_hybrid(map,argc,argv);    
  arser::map_printer(map);

  printf("end map printer\n");
  int a;
  float b;
  double c;
  double fail=10;
  const char* ccs;
  char cs[100];
  std::string ss;


  map["a"] = "1";
  map["b"] = "2";
  map["c"] = "3";  
  arser::assign(a,map["a"]);
  //arser::assign_from_map(a,map,"a");
  arser::assign_from_map(map,b,"b");
  arser::assign_from_map(map,c,"c");
  arser::assign_from_map(map,fail,"fail");

  map["ccs"] = "ccs";
  map["cs"] = "cs";
  map["ss"] = "ss";

  
  // arser::assign_from_map(map,ccs,"ccs");

  arser::assign_from_map(map,cs,"cs");

  arser::assign_from_map(map,ss,"ss");    
  
  printf("a: %i b: %f c: %f fail: %f \n",a,b,c,fail);

  
  printf("cs: %s ss: %s\n",cs,ss.c_str());
      
  
}

int main(int argc, char** argv)
{
  test1();
  test3(argc,argv);
}
