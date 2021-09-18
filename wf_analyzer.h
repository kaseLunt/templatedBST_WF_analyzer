#pragma once
#ifndef WF_ANALYZER_H
#define WF_ANALYZER_H

#include <vector>
#include <iostream>
#include <fstream>
#include "templatedBST.h"


class WordFreqAnalyzer
{
    public:
        WordFreqAnalyzer( );

        // result will hold the parsed text as an vector of strings
        std::vector<std::string> result;
        // uniqueArray holds the parsed words minus the duplicates
        std::vector<std::string>* uniqueArray;
        // freqArray 
        std::vector< WordEntry* >* freqArray;
        BST_T< std::string >* tree;
        

        std::vector< WordEntry* >* toFreqArray( BSTNode< std::string >* root, std::vector< WordEntry* >* vector );
        void displayLeastFreq( int cutoff );
        void displayMostFreq( int cutoff );
        std::vector<std::string> parseText( std::string file_name );
        std::vector<std::string>* formatText( std::string str );
        int totalWords();
        int uniqueWords();
        void saveToFile();
};

WordFreqAnalyzer::WordFreqAnalyzer( )
{
    tree = new BST_T<std::string>();
    freqArray = new std::vector< WordEntry* >;
    result = parseText( "/Users/macpro/CSE240/BST_practice/frost_poems.txt" );

    for( int i = 0; i < result.size(); i++ )
    {
        std::cout << result[i] << std::endl;
        tree->insert( result[i] );
    }

    uniqueArray = tree->toArray( tree->getRoot() );

}

/***********************************************************************************************************
   parseText() : parse through a file and split into words, return vector of strings 
***********************************************************************************************************/ 


std::vector<std::string> WordFreqAnalyzer::parseText( std::string file_name )
{
    // result will save the entire list of individual words
    std::vector<std::string> result;

    // temp will be used to save the results of the formatted text
    std::vector<std::string>* fText;

    std::ifstream file(file_name);
    std::string inputWord;

    while( file >> inputWord ) 
    {
        // format the text and save the result 
        fText = formatText( inputWord );
        
        // if fText contains multiple words, push them each onto the result
        for( int i = 0; i < fText->size(); i++ )
        {
            result.push_back( fText->at( i ) );
        }
    }
    // return the now-full vector containing every word in the file, includes duplicates
    return result ;
}

/***********************************************************************************************************
    formatText() : format a string to lowercase. Split compound-words into individual words, 
        remove punctuation, and return new word or words in a vector
***********************************************************************************************************/ 

std::vector<std::string>* WordFreqAnalyzer::formatText( std::string str )
{
    // temp will act as a buffer to store the word in after tolower()
    std::string temp;

    // tempVec stores the address of a vector of strings on the heap
    std::vector<std::string>* tempVec = new std::vector<std::string>;

    // iterate through the string, split into multiple words if applicable
    for( int i = 0; i < str.size(); i++ ) 
    {
        if( str[i] == '-' )
        {
            // push the word before '-' onto the tempVec vector
            tempVec->push_back( temp );
            // reset the temp string to empty string, to start building the second word
            temp = "";
        }
        else if( str[i] == '\'')    // preserve apostrophe characters
        {
            temp = temp + str[i];
        }
        else if( isalpha( str[i] ) == true ) // make sure it is not a number or punctuation
        {
            str[i] = tolower( str[i] );
            temp = temp + str[i];
        }
    }
    // push the word onto tempVec and return it
    tempVec->push_back( temp );
    return tempVec;    
}

std::vector< WordEntry* >* WordFreqAnalyzer::toFreqArray( BSTNode<std::string>* root, std::vector< WordEntry* >* freqArray )
{
    // first travel the tree in order, and add all the WordEntry pointers to the freqArray vector
    if( root == NULL )
    {
        return freqArray;
    }
    toFreqArray( root->getLeft(), freqArray );
    freqArray->push_back( root->word );
    toFreqArray( root->getRight(), freqArray );

    
    // next, sort the array by frequency, ie wordCount
    for( int i = 0; i < freqArray->size() - 1; i++ )
    {
        int iMin = i;
        for( int j = i + 1; j < freqArray->size(); j++)
        {
            if ( freqArray->at( j )->getCount() < freqArray->at( iMin )->getCount() )
            {
                iMin = j;
            }
        }
        WordEntry* tempW = freqArray->at( i );
        freqArray->at( i ) = freqArray->at( iMin );
        freqArray->at( iMin ) = tempW;
    }
    

    return freqArray;
}

void WordFreqAnalyzer::displayLeastFreq( int cutoff )
{
    std::cout << "Least frequent words: " << std::endl;
    for( int i = 0; i < cutoff; i++ )
    {
        std::cout << "\t" << freqArray->at( i )->getWord() << "\t" << freqArray->at( i )->getCount() << std::endl;
    }
}

void WordFreqAnalyzer::displayMostFreq( int cutoff )
{
    std::cout << "Most frequent words: " << std::endl;
    for( int i = freqArray->size() - 1; i > freqArray->size() - cutoff - 1; i-- )
    {
        std::cout << "\t" << freqArray->at( i )->getWord() << "\t" << freqArray->at( i )->getCount() << std::endl;
    }
}

void WordFreqAnalyzer::saveToFile()
{
    std::string fileName;
    std::cout << "Please enter a valid file pathway to save to: ";
    std::cin >> fileName;

    // open a file in write mode, pass in user's filepath
    std::fstream outfile;
    outfile.open("\"" + fileName + "\"");

    for( int i = 0; i < freqArray->size(); i++ )
    {
        outfile << freqArray->at( i )->getWord() << "\t" << freqArray->at( i )->getCount() << std::endl;
    }

}

int WordFreqAnalyzer::totalWords()
{
    return this->result.size();
}
int WordFreqAnalyzer::uniqueWords()
{
    return uniqueArray->size();
}

#endif