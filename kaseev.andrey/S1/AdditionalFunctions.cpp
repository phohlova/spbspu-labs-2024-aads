#include "AdditionalFunctions.hpp"
#include "sstream"

namespace kaseev {
  int readList(const std::string &line, kaseev::List<std::pair<std::string, kaseev::List<int>>> &arr)
  {
    std::istringstream iss(line);
    std::string ListName;
    if (!(iss >> ListName))
    {
      std::cerr << "Empty line! \n";
      return 1;
    }
    kaseev::List<int> tempList;
    int num;
    try
    {
      while (iss >> num)
      {
        if (num < 0)
        {
          std::cerr << "Negative number is not allowed! \n";
          return 1;
        }
        tempList.pushBack(num);
      }
    }
    catch (const std::bad_alloc &)
    {
      std::cerr << "List size exceeds maximum limit";
      return 1;
    }
    std::pair<std::string, kaseev::List<int>> list_pair;
    list_pair.first = ListName;
    list_pair.second = kaseev::List<int>(tempList);
    arr.pushBack(list_pair);
    return 0;
  }

  int sumNumbersInString(const std::string &line)
  {
    std::istringstream iss(line);
    int sum = 0;
    int num;
    while (iss >> num)
    {
      sum += num;
    }
    return sum;
  }

  void sumNumbersInArray(const kaseev::List<std::pair<std::string, kaseev::List<int>>> &sums)
  {
    for (int i = 0; i < sums.size(); ++i)
    {
      const auto &pair = sums[i];
      const std::string &line = pair.first;
      int sum = 0;
      sum = sumNumbersInString(line);
      std::cout << sum;
      if (!pair.second.empty() && i < sums.size() - 1)
      {
        std::cout << " 0";
      }
      if ((i > 0) || (i < sums.size()))
      {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }

  void printListNames(const kaseev::List<std::pair<std::string, kaseev::List<int>>> &arr)
  {
    for (int i = 0; i < arr.size(); ++i)
    {
      std::pair<std::string, kaseev::List<int>> list = arr[i];
      std::cout << list.first;
      if (i < arr.size() - 1) {
        std::cout << " ";
      }
    }
    std::cout << "\0";
  }

  kaseev::List<std::pair<std::string, kaseev::List<int>>>
  calculateSumList(const kaseev::List<std::pair<std::string, kaseev::List<int>>> &arr)
  {
    bool finished = false;
    size_t index = 0;
    kaseev::List<std::pair<std::string, kaseev::List<int>>> sum;

    while (!finished)
    {
      finished = true;
      std::string currentString;
      int currentSum = 0;

      for (size_t i = 0; i < arr.size(); ++i)
      {
        const kaseev::List<int> &sublist = arr[i].second;

        if (index < sublist.size())
        {
          if (!currentString.empty())
          {
            currentString += " ";
          }

          currentString += std::to_string(sublist[index]);
          currentSum += sublist[index];
          finished = false;
        }
      }

      if (!finished)
      {
        std::cout << currentString << "\n";
        sum.pushBack({currentString, kaseev::List<int>()});
      }

      index++;
    }

    return sum;
  }
}
