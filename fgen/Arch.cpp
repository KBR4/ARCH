#include "Arch.h"
using namespace std;
using namespace ArgumentsData;
cVariable::cVariable()
{
    vSetType(cVInt); //default type = int
}
cVariable::cVariable(int i)
{
    iSetiVal(i);
    vSetType(cVInt);
}
cVariable::cVariable(string s)
{
    sSetsVal(s);
    vSetType(cVStr);
}
int cVariable::iGetiVal()
{
    return iVal;
}
void cVariable::iSetiVal(int i)
{
    iVal = i;
}
string cVariable::sGetsVal()
{
    return sVal;
}
void cVariable::sSetsVal(string s)
{
    sVal = s;
}
void cVariable::vSetType(cVarType cT)
{
    iType = cT;
}
bool cVariable::bIsEmpty()
{
    switch (iType)
    {
    case cVInt:
        return (iVal == 0);
        break;
    case cVStr:
        return (sVal.empty());
        break;
    }
    return false;
}
cVarType cVariable::iGetType()
{
    return iType;
}


cArgument::cArgument()
{

}
cArgument::~cArgument()
{

}
cArgument::cArgument(string sKey1)
{
    vAlias.push_back(sKey1);
}
cArgument::cArgument(string sKey1, string sDesc)
{
    vAlias.push_back(sKey1);
    sDescription = sDesc;
}
cArgument::cArgument(vector<string> vKeys, string sDesc)
{
    vAlias = vKeys;
    sDescription = sDesc;
}
cArgument::cArgument(string sKey1, string sDesc, cVariable cc)
{
    vAlias.push_back(sKey1);
    sDescription = sDesc;
    c.iSetiVal(cc.iGetiVal());
    c.sSetsVal(cc.sGetsVal());
}
void cArgument::vSetValue(string s)
{
     c.vSetType(cVStr);
     c.sSetsVal(s);
}
void cArgument::vSetValue(int i)
{
    c.vSetType(cVInt);
    c.iSetiVal(i);
}
void cArgument::vAssignVar(cVariable cV)
{
    c = cV;
}
void cArgument::add_alias(string s)
{
    vAlias.push_back(s);
}
bool cArgument::bIsKeyExist(string s)
{
    if (find(vAlias.begin(), vAlias.end(), s) != vAlias.end())
    {
        return true;
    }
    return false;
}
string cArgument::sGetDesc()
{
    return sDescription;
}
void cArgument::sGetAliases()
{
    for (string sAlias : vAlias)
    {
        cout << sAlias << " "; //заменить на / кроме последнего
    }
}
void cArgument::cPrintType()
{
    if (this->bValidate(cVariable(1)))
    {
        cout << " Integer ";
    }
    else
    {
        cout << " String ";
    }

    /*
    if (c.iGetType() == cVInt)
    {
        cout << " Integer ";
    }
    else
    {
        cout << " String ";
    }
    */
}
cVariable cArgument::cGetValue()
{
    return c;
}
/*
cVarType cArgument::cGetType(cVariable cV)
{
    
}
*/
void cArgument::vArgumentMissing()
{  
    cout << "To assign the value to this Argument, use the command of the ""Key"" - ""Value"" type." << endl;
    cout << "First, type one of the ""Keys"" that would specify the argument you want to call." << endl;
    cout << "The current argument's ""Keys"" are: ";
    sGetAliases();
    cout << endl;
    cout << "Next, press Space and type the argument's ""Value"". The type of the ""Value"" for this argument is ";
    cPrintType();
    cout << endl << "This argument describes" << sGetDesc() << ", keep that in mind when assigning the ""Value"" to the argument!" << endl;
    cout << endl;
}

cVarType cArgument::cGetType() 
{ 
    return c.iGetType(); 
}

bool cArgumentFileName::bValidate(cVariable cV)
{
    if (cV.iGetType() == cVStr)
    {
        return true;
    }
    return false;
}


bool cArgumentWidth::bValidate(cVariable cV)
{
    if (cV.iGetType() == cVInt)
    {
        return true;
    }
    return false;
}


bool cArgumentNumbStr::bValidate(cVariable cV)
{
    if (cV.iGetType() == cVInt)
    {
        return true;
    }
    return false;
}

cVecArgs::cVecArgs()
{

}

cVecArgs::~cVecArgs()
{

}
void cVecArgs::vHelp()
{
    list<string> sL = sGetHelpList();
    for (list<string>::iterator it = sL.begin(); it != sL.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << endl;
}
void cVecArgs::cAddArgument(string s, vector<string> sAlias, string st)
{
    string sCopy = s;
    size_t pos = s.find(sMainLabel);
    if (pos != string::npos)
    {
        s.erase(pos, sMainLabel.length());
    }
    
    if (s == "FileName")
    {
        cArgumentFileName* c = new cArgumentFileName(sAlias, st);
        mArgs[sCopy] = c;
        return;
    }
    if (s == "WidthOfString")
    {
        cArgumentWidth* c = new cArgumentWidth(sAlias, st);
        mArgs[sCopy] = c;
        return;
    }
    if (s == "NumbOfStrings")
    {
        cArgumentNumbStr* c = new cArgumentNumbStr(sAlias, st);
        mArgs[sCopy] = c;
        return;
    }
}

mapDEF cVecArgs::GetArgs()
{
    return mArgs;
}
vector<PairVar> cVecArgs::GetPairsVector()
{
    return vPairs;
}
list<string> cVecArgs::sGetHelpList()
{
    return sHelpList;
}
bool cVecArgs::sSetHelpList(list<string> sList)
{
    sHelpList.clear();
    sHelpList = sList;
    return true;
}
bool cVecArgs::bCheckIfMainArgsDefined()
{
    bool bMainArgUndefined = false;

    for (mapDEF::iterator mapIT = mArgs.begin(); mapIT != mArgs.end(); mapIT++)
    {
        string sArg = mapIT->first;
        if (sArg.substr(0, sMainLabel.length()) == sMainLabel)  //Check if starts with sMainLabel
        {
            if (mapIT->second->cGetValue().bIsEmpty())
            {
                bMainArgUndefined = true;

                cout << "Error! Required Argument " << mapIT->first << " value is not defined" << endl;
                cArgument* cA = mapIT->second;
                cA->vArgumentMissing();
            }
        }
    }  
    if (bMainArgUndefined == true)
    {
        return false;
    }
    return true;
}
bool cVecArgs::bLaunch(int argc, char* argv[])
{
    //Grabbing Pairs From Command Line
    bool bFoundFirst = false;
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == cDIV)
        {
            bFoundFirst = true; //Checking for cDIV
        }
        else
        {
            if (bFoundFirst == true)
            {
                //Check if Number. Positive Integer counts as a Number.
                char* p;
                long converted = strtol(argv[i], &p, 10);
                if (*p)
                {
                    vPairs.push_back(PairVar(argv[i - 1], cVariable(argv[i])));
                }
                else
                {
                    vPairs.push_back(PairVar(argv[i - 1], cVariable(converted))); //Check?
                }
                bFoundFirst = false;
            }
        }
    }
    //Assigning Correct Values From Pairs
    for (PairVar vP : vPairs)
    {
        string sFirst = vP.first;
        for (mapDEF::iterator mapIT = mArgs.begin(); mapIT != mArgs.end(); mapIT++)
        {
            cArgument* cA = mapIT->second;
            if (cA->bIsKeyExist(sFirst))
            {               
                if (cA->bValidate(vP.second)) // тогда это значение v.vAssignVar(vP.second);
                {                    
                    cA->vAssignVar(vP.second);
                    //cout << "a";
                }
                else
                {
                    cout << "You attempted to assign the value of ";                   
                    switch (vP.second.iGetType())
                    {
                    case cVInt:
                        cout << vP.second.iGetiVal() <<", which type is Integer, to the Argument " << mapIT->first << endl;
                        cout << "Argument " << mapIT -> first <<" requires a value of String Type, for example: ff.txt." << endl << "Entry that contains anything except positive Integer is considered String." << endl;
                        cout << endl;
                        break;
                    case cVStr:
                        cout << vP.second.sGetsVal() <<", which type is String, to the Argument " << mapIT->first << endl;
                        cout << "Argument " << mapIT->first << " requires a value of Positive Integer Type, for example: 562." << endl << "Negative and float numbers aren't supported." << endl;
                        cout << endl;
                        break;
                    }
                }
            }
        }
    }
    
    if (!bCheckIfMainArgsDefined())
    {
        cout << "Not all main arguments were defined! Check the error log to see which ones are missing or were defined incorrectly." << endl << endl;
    }
    //Checking If All Arguments Have No Value
    bool bNoCorrectValues = true;
    for (mapDEF::iterator mapIT = mArgs.begin(); mapIT != mArgs.end(); mapIT++)
    {
        if (!mapIT->second->cGetValue().bIsEmpty())
        {
            bNoCorrectValues = false;
            break;
        }
    } 
    //If No Values Entered Correct - Help For Starters Called
    if (bNoCorrectValues == true)
    {
        vHelp();
    }
    
    return true;
}

cVariable cVecArgs::bGetArgumentValueByName(string s)
{
    for (mapDEF::iterator mapIT = mArgs.begin(); mapIT != mArgs.end(); mapIT++)
    {
        if (mapIT->first == s)
        {
            cArgument* cA = mapIT->second;
            cVariable c = cA->cGetValue();
            return c;
        }
    }
    cVariable c;
    return c;
}