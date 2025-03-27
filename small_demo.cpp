#include <bits/stdc++.h>
// https://github.com/campfireai/lavastone
// Lavastone es una librería que se encarga de manejar containers de 
// tamaños que sobrepasan a la memoria
#include "lavastone.hpp"

#define CHUNK_SIZE 1024

#define timeit(code, str)                                                      \
  {                                                                            \
    auto start = std::chrono::steady_clock::now();                             \
    code;                                                                      \
    auto end = std::chrono::steady_clock::now();                               \
    std::cout << str                                                           \
              << std::chrono::duration_cast<std::chrono::milliseconds>(end -   \
                                                                       start)  \
                     .count()                                                  \
              << "\n";                                                         \
  }

using namespace std;

  char buffer[CHUNK_SIZE];
  int curr = -1;
  int offset = 0;

  vector<string> filepaths = {
      "random_file_1.txt",
      "random_file_2.txt",
      "random_file_3.txt",
      "random_file_4.txt"
  };

  int currFile = -1;

  bool readChunk()
  {
      std::ifstream file(filepaths[currFile], std::ios::binary);
      if (!file)
      {
          std::cerr << "Error1" << std::endl;
          return false;
      }

      file.seekg(offset, std::ios::beg);
      if (file.fail())
      {
          std::cerr << "Error2" << std::endl;
          return false;
      }

      memset((void*)buffer, '\n', sizeof(char) * CHUNK_SIZE);
      bool out = file.read(buffer, CHUNK_SIZE) || (file.gcount() > 0);
    //   if (out)
    //       std::cout.write(buffer.data(), file.gcount());

      file.close();

      return out;
  }

  int next(char &c)
  {
      curr++;

      if (curr >= CHUNK_SIZE)
      {
          if (readChunk())
          {
              curr = 0;
              c = buffer[0];
              offset += CHUNK_SIZE;
              return c == ' ' || c == '\n' || c == '\r';
          }
          return 2;
      }

      c = buffer[curr];
      return c == ' ' || c == '\n' || c == '\r';
  }

  bool compute_hash(int& hash_value)
  {
      const int p = 31;
      const int m = 1e9 + 9;
      hash_value = 0;
      long long p_pow = 1;
      char c;
      int out;
      while ((out = next(c)) == 0)
      {
          hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
          p_pow = (p_pow * p) % m;
      }
      return out == 1;
  }

  bool readWord(string& val)
  {
      val = "";
      char c;
      int out;
      while ((out = next(c)) == 0)
          val.push_back(c);
      return out == 1;
  }

  
struct Program
{

  lava::Ref<map<string, vector<int>>> invIndex1;
  lava::Ref<map<int, string>> invIndex2;

  int wordNum = 0;

  void readFile()
  {
      currFile++;
      curr = CHUNK_SIZE-1;
      offset = 0;

      string word;
      while (readWord(word))
      {
        if (word == "")
            continue;
          int old = invIndex1.size();
          invIndex1[word];
          if (invIndex1.size() != old)
          {
            invIndex2[wordNum] = word;
            for(int j = 0; j < filepaths.size(); j++)
              invIndex1[word].push_back(0);
            wordNum++;
          }
          invIndex1[word][currFile] = true;
      }
  }
  
    void printIndex()
    {
        for (int i = 0; i < invIndex2.size(); i++)
        {
            string p = invIndex2.at(i);
            cout << p << ": ";
            for (int j = 0; j < filepaths.size(); j++)
                if (invIndex1.at(p).at(j) == 1)
                    cout << j << ' ';
                cout << endl;
        }
    }
    
    void processFiles()
    {
        for (int i = 0; i < filepaths.size(); i++)
        {
            readFile();
        }
    }
};

int main()
{
    lava::init();

    Program p;

    timeit(p.processFiles(), "! TIME (MS): ");

    // p.printIndex();

    return 0;
}