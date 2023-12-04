#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

namespace AoC2023
{
  /* --- Day 3: --- */
  class Day3
  {
    public:
      Day3();
      ~Day3() = default;
  
      void SolvePuzzles();

    private:
      bool PrepareInputData();
      bool CheckSymbol(char ch)
      {
        const char symbolSet[] = { '#', '$', '%','*','/','&','+','=','-'};

        for (char symbol : symbolSet) {
          if (ch == symbol) {
            return true;
          }
        }

        // If the character is not any of the specified symbols
        return false;
      }

      // number, row, index
      std::uint64_t Puzzle1Solver();
      std::uint64_t Puzzle2Solver();
      
      std::ifstream _inputFile;
      bool _inputDataReady;

      std::vector<std::string> _inputData;

      struct Entity
      {
        int value;
        std::uint16_t symRow;
        std::uint16_t symInd;
      };

      std::vector<Entity> gearParts;
  };
}
