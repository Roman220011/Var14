#ifndef __HOUSE_H__
#define __HOUSE_H__
 
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdbool>
#include <algorithm>

struct house
{
	std::string adress;
    std::string tel;
    size_t area{0};
    size_t rooms{0};
    size_t price{0};

    void showItem();
};

bool comp (const house * a, const house * b);

void push(std::vector <house *> & temp);
void openFile(std::ifstream & f, std::vector <house *> & temp);
void printList(std::vector <house *> temp);
void writeToFile(std::ofstream & f, std::vector <house *> temp);
house * find(std::vector <house *> temp, std::string initial);
void edit(std::vector <house *> temp);
void add(std::vector <house *> & temp);
void remove(std::vector <house *> & temp);
void sortList(std::vector <house *> & temp);
void clear(std::vector <house *> & temp);

#endif