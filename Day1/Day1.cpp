#include "Day1.hpp"
#include <array>

namespace AoC2023
{
  Day1::Day1():
    _inputFile{ "input.txt", std::ios_base::in },
    _inputDataReady{ false }, 
    _elfWithMaxCalories{ 0 },
    _sumOfTop3WithMaxCalories { 0 }
  {  
    if (PrepareInputData())
    {
      _inputDataReady = true;
    }
  }
  
  void Day1::SolvePuzzles()
  {
    std::cout << "[Day 1] Puzzle 1 solution: "
      << Puzzle1Solver() << " | Puzzle 2 solution: "
      << Puzzle2Solver() << std::endl;
  }
  
  bool Day1::PrepareInputData()
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
          _inputData.push_back(line);
        }
      }
      _inputFile.close();
      inputParsed = true;
    }
    return inputParsed;
  }
  
  std::uint64_t Day1::Puzzle1Solver()
  {
    std::uint8_t number = 0;
    std::uint64_t sumOfNumbers = 0;
    if (_inputDataReady)
    {    
      for (const auto& str : _inputData) 
      {
        for (auto it = str.begin(); it != str.end(); ++it)
        {
          if (std::isdigit(*it))
          {
            number = std::stoi(std::string(1, *it)) * 10;
            break;
          }
        }

        for (auto it = str.rbegin(); it != str.rend(); ++it) 
        {
          if (std::isdigit(*it))
          {
            number += std::stoi(std::string(1, *it));
            break;
          }
        }
        sumOfNumbers += number;
      } 
    }    
    return sumOfNumbers;
  }
  
  std::uint64_t Day1::Puzzle2Solver()
  {
    std::uint64_t sumOfNumbers = 0;
    if (_inputDataReady)
    {
      std::uint8_t number = 0;
      std::int8_t firstDigitPos = -1;
      std::int8_t lastDigitPos = -1;

      for (const auto& str : _inputData)
      {
        for (auto it = str.begin(); it != str.end(); ++it)
        {
          if (std::isdigit(*it))
          {
            firstDigitPos = str.find(*it);
            break;
          }
        }
       
        /* Check in reverse order */
        for (auto it = str.rbegin(); it != str.rend(); ++it)
        {
          if (std::isdigit(*it))
          {
            lastDigitPos = str.rfind(*it);
            break;
          }
        }

        std::string lowestKeyStr;
        std::string highestKeyStr;

        size_t lowestStrPos = str.size();
        size_t highestStrPos = 0;

        for (const auto& entry : numbersMap) 
        {
          const std::string& key = entry.first;

          size_t pos = str.find(key);
          if (pos != std::string::npos)
          {
            if (pos < lowestStrPos)
            {
              lowestStrPos = pos;
              lowestKeyStr.clear();
              lowestKeyStr = key;
            }
           
            size_t revPos = str.rfind(key);
            if (revPos != std::string::npos)
            {
              if (revPos > highestStrPos)
              {
                highestStrPos = revPos;
                highestKeyStr.clear();
                highestKeyStr = key;
              }
            }
          }
        }

        /* Check whether digit or string is on leftmost or rightmost
         position and use the corresponding one to form a value.*/
        if (firstDigitPos != -1) // digit is found
        {
          if (firstDigitPos <= lowestStrPos) 
          {
            number = std::stoi(std::string(1, str.at(firstDigitPos)));
          }
          else
          {
            number = numbersMap.find(lowestKeyStr)->second;
          }
        }
        else // no digit in number
        {
          number = numbersMap.find(lowestKeyStr)->second;
        }

        number *= 10;

        if (lastDigitPos != -1) // digit is found
        {
          if (lastDigitPos >= highestStrPos)
          {
            number += std::stoi(std::string(1, str.at(lastDigitPos)));
          }
          else // no digit in number
          {
            number += numbersMap.find(highestKeyStr)->second;
          }
        }
        else
        {
          number += numbersMap.find(highestKeyStr)->second;
        }

        sumOfNumbers += number;
      }
    }
    return sumOfNumbers;
  }
}
