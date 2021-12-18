#include <iostream>
#include <ctime>
#include "Tree.h"

int main()
{
    std::srand(std::time(nullptr));

    Tree* tree = new Tree(20);
    //int sumValuesBefore = tree->GetRoot()->GetSumChildrensValues();
    
    int valueToAdd = 1;
    double multiThreadStartTime = clock();

#pragma omp parallel default(none) shared(tree) private(valueToAdd)
    {
        valueToAdd = 1;
        tree->GetRoot()->AddValueEachChildren(valueToAdd);
    }
    
    double multiThreadEndTime = clock() - multiThreadStartTime;
    std::cout << "Multi thread time = " << multiThreadEndTime / CLOCKS_PER_SEC << "sec.\n\n\n";

    //int sumValuesAfter = tree->GetRoot()->GetSumChildrensValues();
    //int difference = sumValuesAfter - sumValuesBefore;

    //int treeDepth = tree->GetTreeDepth();
    //int nLeafs = pow(2, treeDepth + 1);
    //int valueToAddT = 1;
    //int computedDifference = nLeafs * valueToAddT;
}