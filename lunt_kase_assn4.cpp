/*

Author: Kase Lunt

Date:   7/7/21

Description: This is the main file for a word frequency analyzer. It creates a wordfrequencyAnalyzer object which parses the text file
and splits input into words, and saves those into a BST. The BST can then be searched, as well as saved to a file, sorted by frequency.

*/


#include "templatedBST.h"
#include "wf_analyzer.h"


int main(int argc, char** argv)
{
    // create a new analyzer instance, calling default constructor
    WordFreqAnalyzer analyzer;

    // wordP will point to a vector of WordEntry pointers
    std::vector< WordEntry* >* wordP;

    // call analyzer's toFreqArray to create a vector of words sorted by frequency (wordCount)
    wordP = analyzer.toFreqArray( analyzer.tree->getRoot(), analyzer.freqArray );

    // summarize the analysis and display to console
    std::cout << "Total words: " << analyzer.totalWords() << std::endl;
    std::cout << "Total unique words: " << analyzer.uniqueWords() << std::endl;
    analyzer.displayLeastFreq(5);
    analyzer.displayMostFreq(5);

    // menu 
    bool continueMenu = true;
    std::string tempString;
    BSTNode<std::string>* tempPtr;
    int input;
    while( continueMenu )
    {
        std::cout << "Please enter a word to search and show frequency: \n<<";
        std::cin >> tempString;
        if( analyzer.tree->elementExists(tempString) )
        {
            tempPtr = analyzer.tree->find( tempString );
            std::cout << tempPtr->word->getWord() << "\t" << tempPtr->word->getCount() << std::endl;
        }
        
        std::cout << "What would you like to do now? \n";
        std::cout << "1. Save to file \n" <<
                     "2. Search for another word \n"
                     "3. Exit ";
        std::cin >> input;

        switch(input)
        {
            case 1: analyzer.saveToFile(); break;
            case 2: break;
            case 3: continueMenu = false;
        }

    }
    for( int i = 0; i < wordP->size(); i ++)
    {
       // std::cout << std::endl << wordP->at( i )->getCount() << " " << wordP->at( i )->getWord() << std::endl;
    }
    
    

    for( int i = 0; i < wordP->size(); i++)
    {
        //std::cout << std::endl << wordP->at(i)->getWord() << " " << wordP->at(i)->getCount() << std::endl;
    }

    


}

