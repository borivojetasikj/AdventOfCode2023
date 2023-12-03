#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

namespace AoC2023
{
   
  /* --- Day 1: Trebuchet?! --- */
  class Day1
  {
    public:
      Day1();
      ~Day1() = default;
  
      void SolvePuzzles();
    
    private:
      bool PrepareInputData();
      std::uint64_t Puzzle1Solver();
      std::uint64_t Puzzle2Solver();
      
      std::ifstream _inputFile;
      bool _inputDataReady;
      std::vector<std::string> _inputData;
      
      std::uint64_t _elfWithMaxCalories; 
      std::uint32_t _sumOfTop3WithMaxCalories; 
      
      std::map<std::string, int> numbersMap {
      {"one", 1},
      {"two", 2 },
      {"three", 3 },
      {"four", 4 },
      {"five", 5 },
      {"six", 6 },
      {"seven", 7 },
      {"eight", 8 },
      {"nine", 9 }};
  };
}
