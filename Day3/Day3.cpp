#include "Day3.hpp"

namespace AoC2023
{
  Day3::Day3():
    _inputFile{ "input.txt", std::ios_base::in },
    _inputDataReady{ false }
  {  
    if (PrepareInputData())
    {
      _inputDataReady = true;
    }    
  }
  
  void Day3::SolvePuzzles()
  {
    std::cout << "[Day 2] Puzzle 1 solution: "
      //<< Puzzle1Solver() << " | Puzzle 2 solution: "  
      << Puzzle2Solver() << std::endl;
  }
  
  bool Day3::PrepareInputData()
  {
    bool inputParsed = false;
    if (_inputFile)
    {
      std::string line = "";
      std::uint16_t lineNum = 0;
      while (_inputFile)
      {
        std::getline(_inputFile, line, '\n');

        if (!line.empty())
        {
          //std::cout << line << std::endl;
          _inputData.push_back(line);
        }
      }
      _inputFile.close();
      inputParsed = true;
    }
      return inputParsed;
  }
  
  std::uint64_t Day3::Puzzle1Solver()
  {
    if (_inputDataReady)
    {
      std::string rowPrev;
      std::string rowAfter;

      std::uint16_t firstDigitInd = 0;
      std::uint16_t lastDigitInd = 0;

      std::uint16_t currentRow = 0;
      std::uint16_t currIdxInRow = 0;
      
      std::string stringNumber;
      std::uint64_t sumOfNumbers = 0;
      for (std::string& row : _inputData)
      {   
        std::cout << "\nNEXT ROW, ID = " << currentRow << std::endl;
        for (std::string::iterator it = row.begin(); it != row.end();)
        {
          printf("IND = %d\n", currentRow);
          stringNumber.clear();
          //std::cout << "\nROW IDX = " << currIdxInRow << std::endl;
          // Access and print each character
          if (std::isdigit(*it)) // found first digit
          {
            stringNumber += *it;
            // Find number indexes in current row
            firstDigitInd = currIdxInRow;
            std::cout << "\ncurr ind " << currIdxInRow << "First dig : " << *it << std::endl;

            while (it + 1 != row.end() && std::isdigit(*(++it)))
            {
              //std::cout << "Row in ind: " << currIdxInRow << std::endl;
              stringNumber += *it;              
              if (it + 1 != row.end())
              {
                currIdxInRow++;
                std::cout << "\ncurr ind " << currIdxInRow <<std::endl;
              }
              else
              {
                  it = row.end();
                break;
              }
               std::cout << "curr ind " << currIdxInRow << " Next dig: " << *it << std::endl;
            }
            lastDigitInd = currIdxInRow;

            printf("NUM %d \n", std::stoi(stringNumber));
            printf("-%d----%d--\n", firstDigitInd, lastDigitInd);

            // Check around 

            //  [firstDigitInd - 1], [lastDigitInd + 1]
            bool symbolFound = false;

            /* Define and adjust check boundaries */
            std::uint16_t startCheckInd = firstDigitInd - 1;
            std::uint16_t endCheckInd = lastDigitInd + 1;

            if (firstDigitInd == 0 || lastDigitInd == row.size())
            {
              if (firstDigitInd == 0)
              {
                startCheckInd = 0;
              }
              else if (lastDigitInd == row.size())
              {
                endCheckInd = lastDigitInd;
              }
            }
            
            // Check around the number first
            if (CheckSymbol(row[startCheckInd]) ||
                CheckSymbol(row[endCheckInd]))
            {
               std::cout << "L :" << row[startCheckInd] << std::endl;
               std::cout << "R :" << row[endCheckInd] << std::endl;
               std::cout << "Symbol found around the number" << std::endl;

               symbolFound = true;
            }

            if (!symbolFound)
            {
              std::cout << "Curr row "<< currentRow << " Checking rows "<< currentRow-1 << " and "<< currentRow+1 << " between idx " << startCheckInd << " and " << endCheckInd << std::endl;
              for (auto ind = startCheckInd; ind <= endCheckInd; ind++)
              {
                std::cout << "ind = " << ind << std::endl;

                // [1, ...]
                if (currentRow > 0) // NOT FIRST - skip checking prev row for first one
                {
                  //std::cout << "NOT FIRST ROW" << std::endl;
                  std::cout << "CHECK " << currentRow - 1 << "ROW" << std::endl;

                  rowPrev = _inputData.at(currentRow - 1);
                  // Check row prev.
                  //printf("PREV %s at ind \n", rowPrev.at(ind), ind);
                  if (CheckSymbol(rowPrev.at(ind)))
                  {
                    symbolFound = true;
                    break;
                  }
                }
                //printf("row.size() - 1 = %u\n", row.size() - 1);

                if (currentRow != row.size() - 1) // NOT LAST - row.size() - 1 = 139
                {
                  if(currentRow == 0)
                    std::cout << "FIRST ROW" << std::endl;

                  std::cout << "NOT LAST ROW" << std::endl;
                  std::cout << "CHECK " << currentRow + 1 << " ROW" << std::endl;

                  rowAfter = _inputData.at(currentRow + 1);
                  //printf("AFTER %s at ind \n", rowAfter.at(ind), ind);
                  // Check row after.
                  if (CheckSymbol(rowAfter.at(ind)))
                  {
                    symbolFound = true;
                    break;
                  }
                }
              }
            }

            if (symbolFound)
            {
              sumOfNumbers += std::stoi(stringNumber);
              std::cout << "Symbol found!"<<" Current sum " << sumOfNumbers << std::endl;
              symbolFound = false;
            }
            else
            {
              std::cout << "Symbol NOT found!" << std::endl;
            }
            currIdxInRow++;
          }
          else
          {
            it++;
            currIdxInRow++;
            std::cout << "Curr ind, non digit "<< currIdxInRow << std::endl;
          }
        }

        currentRow++; // [0, vector size]
        currIdxInRow = 0;
      }
      printf("RESULT %d\n", sumOfNumbers);
    }
    return 0;
  }
  
  std::uint64_t Day3::Puzzle2Solver()
  {
    if (_inputDataReady)
    {
      std::string rowPrev;
      std::string rowAfter;

      std::uint16_t firstDigitInd = 0;
      std::uint16_t lastDigitInd = 0;

      std::uint16_t currentRow = 0;
      std::uint16_t currIdxInRow = 0;

      std::string stringNumber;
      std::uint64_t sumOfNumbers = 0;

      std::int16_t symbolIndex = -1;
      std::int16_t symRowInd = -1;
      std::uint64_t totalSymbolsFound = 0;
      for (std::string& row : _inputData)
      {
        //std::cout << "\nNEXT ROW, ID = " << currentRow << std::endl;
        for (std::string::iterator it = row.begin(); it != row.end();)
        {
          symbolIndex = -1;
          symRowInd = -1;
          stringNumber.clear();
          //std::cout << "\nROW IDX = " << currIdxInRow << std::endl;
          // Access and print each character
          if (std::isdigit(*it)) // found first digit
          {
            stringNumber += *it;
            // Find number indexes in current row
            firstDigitInd = currIdxInRow;

            while (it + 1 != row.end() && std::isdigit(*(++it)))
            {
              //std::cout << "Row in ind: " << currIdxInRow << std::endl;
              stringNumber += *it;
              if (it + 1 != row.end())
              {
                currIdxInRow++;
                //std::cout << "\ncurr ind " << currIdxInRow << std::endl;
              }
              else
              {
                it = row.end();
                break;
              }
            }
            lastDigitInd = currIdxInRow;

            // Check around 
            //  [firstDigitInd - 1], [lastDigitInd + 1]
            bool symbolFound = false;

            /* Define and adjust check boundaries */
            std::uint16_t startCheckInd = firstDigitInd - 1;
            std::uint16_t endCheckInd = lastDigitInd + 1;

            if (firstDigitInd == 0 || lastDigitInd == row.size())
            {
              if (firstDigitInd == 0)
              {
                startCheckInd = 0;
              }
              else if (lastDigitInd == row.size())
              {
                endCheckInd = lastDigitInd;
              }
            }

            // Check around the number first
            if (row[startCheckInd] == '*')
            {
              symbolIndex = startCheckInd;
              symRowInd = currentRow;
              symbolFound = true;
            }

            else if(row[endCheckInd] == '*')
            {
              symbolIndex = endCheckInd;
              symRowInd = currentRow;
              symbolFound = true;
            }

            if (!symbolFound)
            {
              //std::cout << "Curr row " << currentRow << " Checking rows " << currentRow - 1 << " and " << currentRow + 1 << " between idx " << startCheckInd << " and " << endCheckInd << std::endl;
              for (auto ind = startCheckInd; ind <= endCheckInd; ind++)
              {
                //std::cout << "ind = " << ind << std::endl;

                // [1, ...]
                if (currentRow > 0) // NOT FIRST - skip checking prev row for first one
                {
                  //std::cout << "NOT FIRST ROW" << std::endl;

                  rowPrev = _inputData.at(currentRow - 1);
                  // Check row prev.
                  //printf("PREV %s at ind \n", rowPrev.at(ind), ind);
                  if (rowPrev.at(ind) == '*')
                  {
                    symbolIndex = ind;
                    symRowInd = currentRow - 1;
                    symbolFound = true;
                    break;
                  }
                }

                if (currentRow != row.size() - 1) // NOT LAST - row.size() - 1 = 139
                {
                  rowAfter = _inputData.at(currentRow + 1);
                  // Check row after.
                  if (rowAfter.at(ind) == '*')
                  {
                    symbolIndex = ind;
                    symRowInd = currentRow + 1;
                    symbolFound = true;
                    break;
                  }
                }
              }
            }

            if (symbolFound)
            {
              std::cout << "Symbol * found!" << " Num:  " << std::stoi(stringNumber) << " Row "<< currentRow << " | Sym ind " << symbolIndex << " Sym row ind " << symRowInd << std::endl;
              Entity entity{ std::stoi(stringNumber), symbolIndex, symRowInd };
              gearParts.push_back(entity);
              symbolFound = false;
              totalSymbolsFound++;
            }
            else
            {
              //std::cout << "Symbol NOT found!" << std::endl;
            }
            currIdxInRow++;
          }
          else
          {
            it++;
            currIdxInRow++;
            //std::cout << "Curr ind, non digit " << currIdxInRow << std::endl;
          }
        }

        currentRow++; // [0, vector size]
        currIdxInRow = 0;
      }

      //int ind = 0;
      //for (const auto& part : gearParts)
      //{
      //  printf("VAL = %d, SYM ROW = %u, SYM IND = %u\n", part.value, part.symRow, part.symInd);
      //
      //}

      std::uint64_t sum = 0;
      std::uint64_t product = 1;

      // Iterate through the vector and check for duplicates
      for (size_t i = 0; i < gearParts.size(); ++i) {
        for (size_t j = i + 1; j < gearParts.size(); ++j) {
          if (gearParts[i].symRow == gearParts[j].symRow && gearParts[i].symInd == gearParts[j].symInd) {
            // Found elements with the same symRow and symInd
            printf("VAL = %d, SYM ROW = %u, SYM IND = %u\n", gearParts[i].value, gearParts[i].symRow, gearParts[i].symInd);

            product = (gearParts[i].value * gearParts[j].value);
            sum += product;
          }
        }
      }

      printf("Total symbols found: %d RESULT 2: %d\n", totalSymbolsFound, sum);
    }
    return 0;
  }

}
