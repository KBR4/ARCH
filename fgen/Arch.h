#pragma once
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <list>
#ifndef ARCH_H
#define ARCH_H

using namespace std;

namespace ArgumentsData
{
    enum cVarType { cVInt, cVStr };  //Enumeration for the type of the Variable

    class cVariable         //Variable - can be either an int number, or a string
    {
    private:
        int iVal = 0;   //Int value
        string sVal;    //Str value
        cVarType iType = cVInt; //Value determines the type of the variable
    public:
        cVariable();                //Default constructor - unused
        cVariable(int i);           //Creates a Variable of the type int with the int value of i
        cVariable(string s);        //Creates a Variable of the type string with the string value of s
        int iGetiVal();             //Get Int value
        void iSetiVal(int i);       //Set Int value
        string sGetsVal();          //Get String value
        void sSetsVal(string s);    //Set String value
        void vSetType(cVarType cT); //Set the type of the variable
        bool bIsEmpty();            //Check if the variable is empty
        cVarType iGetType();        //Get the type of the variable
    };

    class cArgument     //Argument of the command line. Example "/f" "str.txt". "/f" - Alias. "str.txt" - value of cVariable c
    {
    private:
        vector <string> vAlias; //Vector of Key - Aliases of the Argument
        string sDescription;    //Description of the Argument
        cVariable c;            //Value of the Argument

    public:
        cArgument();                      //Default constructor - unused
        ~cArgument();                     //Default destructor - check if objects destruct after creation
        cArgument(string sKey1);          //Constructor of an argument with 1 alias
        cArgument(string sKey1, string sDesc);  //Constructor of an argument with 1 alias and description
        cArgument(vector<string> vKeys, string sDesc);  //Constructor with vector of aliases and description
        cArgument(string sKey1, string sDesc, cVariable cc);  //Constructor with vector of aliases, description and set value             
        void vSetValue(string s);   //assign value of string s to Argument
        void vSetValue(int i);      //assign value of int i to Argument
        void vAssignVar(cVariable cV);  //assign value of cVariable cV to Argument
        void add_alias(string s);       //add alias to the vector of aliases
        bool bIsKeyExist(string s);     //dublicate function to the previous one - delete
        string sGetDesc();              //Get description of the Argument
        void sGetAliases();             //Print aliases of the Argument
        void cPrintType();              //Print the type of the Argument
        cVariable cGetValue();
        //void cSetVarType();             //Sets the type of cVariable
        virtual bool bValidate(cVariable cV) { return true; }
        virtual cVarType cGetType();   //Assure the value of the Argument is correct - inherited
        void vArgumentMissing();                   //Print Help      
    };

    class cArgumentFileName : public cArgument  //Derived class of the Argument Class - for the /f aliases
    {
    public:
        cArgumentFileName(vector<string> vKeys, string sDesc) : cArgument{ vKeys, sDesc } {}
        bool bValidate(cVariable cV) override;
        cVarType cGetType() { return cVStr; }
    };

    class cArgumentWidth : public cArgument //Derived class of the Argument Class - for the /w aliases
    {
    public:
        cArgumentWidth(vector<string> vKeys, string sDesc) : cArgument{ vKeys, sDesc } {}
        bool bValidate(cVariable cV) override;
        cVarType cGetType() { return cVInt; }
    };

    class cArgumentNumbStr : public cArgument //Derived class of the Argument Class - for the /n aliases
    {
    public:
        cArgumentNumbStr(vector<string> vKeys, string sDesc) : cArgument{ vKeys, sDesc } {}
        bool bValidate(cVariable cV) override;
        cVarType cGetType() { return cVInt; }
    };

    typedef map<string, cArgument*> mapDEF;
    typedef pair<string, cVariable> PairVar;

    #define cDIV '/'
    #define sMainLabel string("Main.")

    class cVecArgs
    {
        private:
            mapDEF mArgs;               //map of Arguments: string (NAME) - cArgument
            vector<PairVar> vPairs;     //vector of acquired pairs: string (Alias) - cVariable (Value)
            list<string> sHelpList = { "Hello! This manual will teach you how to store data using this program.", 
                "You store data using special data structures called Arguments.", 
                "There are 3 Arguments that are created by Default.",
                "The Arguments with Main. label in their name are considered Required Arguments, and have to be defined.",
                "To define the argument, you need to assign the value of the correct type to it.",
                "To make program understand, which argument you want to assign value to, first you need to type the specific KEY for this argument, then space, and then the value of the correct type.",
                "For example, /f gg.txt will assign the value of gg.txt to the argument Main.FileName."                
            };     //List of strings that get displayed when help used. Can be redefined
        public:
            cVecArgs();
            ~cVecArgs();
            bool bLaunch(int argc, char* argv[]); //getting values from command line
            void cAddArgument(string s, vector<string> sAlias, string st); //adds an Argument of a correct type 
            mapDEF GetArgs();                           //Returns map of Arguments
            void vHelp();                               //Help Manual - prints helplist
            vector<PairVar> GetPairsVector();           //Returns all pairs found
            bool bCheckIfMainArgsDefined();             //Checks if all arguments with sMainLabel are defined
            cVariable bGetArgumentValueByName(string s);//Get Values from the Arguments to use as user wants
            list<string> sGetHelpList();                //returns list of strings that contain help data
            bool sSetHelpList(list<string> sList);      //sets list of string that contain help data
    };
}
#endif