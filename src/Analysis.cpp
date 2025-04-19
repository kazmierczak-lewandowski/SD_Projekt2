#include "Analysis.hpp"

#include "AVLTree.hpp"
#include "Heap.hpp"

#include <fstream>
#include <iostream>
#include <ncurses.h>
std::map<int, long> Analysis::analyzeInsert(const CollectionType type) {
  clear();
  const auto string = std::format("Analyzing Insertion of {}",
                            type == CollectionType::HEAP ? "Heap" : "BST");
  mvprintw(0,0, "%s", string.c_str());
  for (int i = 100000; i <= 5000000; i+=100000) {

  }
}
void Analysis::writeToFile(const std::string &filename,
                           const std::map<int, long> &data) {
  std::ofstream ofs("../results/" + filename);
  if (!ofs.is_open()) {
    std::cerr << "Failed to open file " << filename << std::endl;
  }
  ofs << "size;time" << std::endl;
  for (const auto &[key, value] : data) {
    ofs << key << ";" << value << std::endl;
  }
  ofs.close();
}
void Analysis::analyze() {
  std::map<int, long> data = analyzeInsert(CollectionType::HEAP);
  writeToFile("InsertionHeap", data);
  data = analyzeInsert(CollectionType::BST);
  writeToFile("InsertionBST", data);
}