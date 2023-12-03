#include "Day2.hpp"

namespace AoC2023
{
  Day2::Day2():
    _inputFile{ "input.txt", std::ios_base::in },
    _inputDataReady{ false }
  {  
    if (PrepareInputData())
    {
      _inputDataReady = true;
    }    
  }
  
  void Day2::SolvePuzzles()
  {
    std::cout << "[Day 2] Puzzle 1 solution: "
      << Puzzle1Solver() << " | Puzzle 2 solution: "
      << Puzzle2Solver() << std::endl;
  }
  
  bool Day2::PrepareInputData()
  {
    bool inputParsed = false;
    if (_inputFile)
    {
      std::string line = "";

      while (_inputFile)
      {
        getline(_inputFile, line, '\n');

        if (!line.empty())
        {
          Game game;
          game.SetGameId(std::stoi(line.substr(5, line.find_first_of(":") - 5)));

          std::string sets = line.substr(line.find_first_of(":") + 2);          
          // Start the search from the beginning of the string
          std::string::iterator it = sets.begin();

          // Continue searching until the end of the string
          while (it != sets.end()) {
            // Find the next occurrence of the target character
            std::string::iterator nextOccurrence = std::find(it, sets.end(), ';');

            // Check if the character is found at least once
            if (nextOccurrence != sets.end()) {
              // Create a substring from the current iterator to the next occurrence
              std::string substring(it, nextOccurrence);

              // Output the substring
              CubeSet cubeSet = ExtractCubeSetColor(substring);
              game.AddCubeSet(cubeSet); // r,g,b
              // Update the iterator to continue the search from the next position
              it = nextOccurrence + 1;
            }
            else
            {
              std::string substringLast(it, sets.end());

              // No more occurrences found, exit the loop
              CubeSet latestcubeSet = ExtractCubeSetColor(substringLast);              
              game.AddCubeSet(latestcubeSet); // r,g,b
              break;
            }
          }
          _games.push_back(game);
        }
      }
      _inputFile.close();
      inputParsed = true;
    }
    return inputParsed;
  }
  
  std::uint64_t Day2::Puzzle1Solver()
  {
    std::uint64_t sumOfPossibleGamesIds = 0;
    if (_inputDataReady)
    {
      for (auto& game : _games)
      {
        std::uint8_t gameId = game.GetGameId();
        if (gameId != 0xFF)
        {
          if (game.IsPossible())
          {
            sumOfPossibleGamesIds += game.GetGameId();
          }
        }
      }
    }
    return sumOfPossibleGamesIds;
  }
  
  std::uint64_t Day2::Puzzle2Solver()
  {
    std::uint64_t sumOfMinPowers = 0;
    if (_inputDataReady)
    {
      for (auto& game : _games)
      {
        std::uint8_t gameId = game.GetGameId();
        if (gameId != 0xFF)
        {
          sumOfMinPowers += game.PowerSetOfMinCubes();
        }
      }
    }
    return sumOfMinPowers;
  }

}
