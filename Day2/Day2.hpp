#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <array>

namespace AoC2023
{
  static constexpr std::uint8_t BAG_LOADED_CUBES_RED = 12;
  static constexpr std::uint8_t BAG_LOADED_CUBES_GREEN = 13;
  static constexpr std::uint8_t BAG_LOADED_CUBES_BLUE = 14;
  
  struct CubeSet
  {
    std::uint8_t redCubes;
    std::uint8_t greenCubes;
    std::uint8_t blueCubes;
  };

  class Game
  {
    public:
      Game():
        _id{0xFF}
      {};

      ~Game() = default;

      void SetGameId(std::uint8_t id)
      {
        _id = id;
      }

      std::uint8_t GetGameId()
      {
        return _id;
      }

      void AddCubeSet(CubeSet set)
      {
        _cubeSets.push_back(set);
      }

      bool IsPossible()
      {
        bool isPossible = true;
        for (auto& set : _cubeSets)
        {
          if (set.redCubes > BAG_LOADED_CUBES_RED ||
              set.greenCubes > BAG_LOADED_CUBES_GREEN ||
              set.blueCubes > BAG_LOADED_CUBES_BLUE)
          {
            isPossible = false;
            break;
          }
        }
        return isPossible;
      }

      std::uint64_t PowerSetOfMinCubes()
      {
        std::uint64_t res = 0;
        std::uint8_t redMax = _cubeSets.at(0).redCubes;
        std::uint8_t greenMax = _cubeSets.at(0).greenCubes;
        std::uint8_t blueMax = _cubeSets.at(0).blueCubes;
        
        // CubeSet {r,g,b}
        for (auto& set : _cubeSets)
        {
          if (redMax < set.redCubes)
          {
            redMax = set.redCubes;
          }
          if (greenMax < set.greenCubes)
          {
            greenMax = set.greenCubes;
          }
          if (blueMax < set.blueCubes)
          {
            blueMax = set.blueCubes;
          }
        }
        res = static_cast<std::uint64_t>(redMax * blueMax * greenMax);
        return res;
      }

    private:
      std::uint8_t _id;
      std::vector<CubeSet> _cubeSets;
  };

  /* --- Day 2: Cube Conundrum --- */
  class Day2
  {
    public:
      Day2();
      ~Day2() = default;
  
      void SolvePuzzles();

      CubeSet ExtractCubeSetColor(std::string input)
      {
        std::istringstream iss(input);
        CubeSet cube{ 0,0,0 };

        // Variables to store extracted values
        int value;
        std::string color;

        // Process each pair of value and color
        while (iss >> value >> color) {

          if (color.find("red") != std::string::npos) {
            cube.redCubes = value; 
          }
          else if (color.find("green") != std::string::npos) {
            cube.greenCubes = value;
          }
          else if (color.find("blue") != std::string::npos) {
            cube.blueCubes = value;
          }
          else
          {
            cube.redCubes = 0;
            cube.greenCubes = 0;
            cube.blueCubes = 0;
          }
          // Check if there is a comma
          if (iss.peek() == ',') {
            iss.ignore(); // Ignore the comma
          }
        }
        return cube;
      }

    private:
      bool PrepareInputData();

      std::uint64_t Puzzle1Solver();
      std::uint64_t Puzzle2Solver();
      
      std::ifstream _inputFile;
      bool _inputDataReady;

      std::vector<Game> _games;      
  };
}
