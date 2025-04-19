#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP
#include "Collection.hpp"

#include <map>

class Analysis {

private:
  enum class CollectionType {
    HEAP = 0, BST = 1
  };

  static constexpr int ITERATIONS = 30;
  static std::map<int, long> analyzeInsert(CollectionType type);
  static std::map<int, long> analyzePeek(CollectionType type);
  static std::map<int, long> analyzeExtractMax(CollectionType type);
  static std::map<int, long> analyzeHeight(CollectionType type);
  static std::map<int, long> analyzeModifyKey(CollectionType type);
  static void writeToFile(const std::string &filename,
                          const std::map<int, long> &data);

public:
  static void analyze();
};

#endif // ANALYSIS_HPP
