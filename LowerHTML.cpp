/*====================================================*/
/*         Jason's Html Tag Fix Version 2.0           */
/*         Date: 12-12-2016                           */
/*                                                    */
/******************************************************/
/* Searches through html file and change uppercase    */
/* tags to lowercase.                                 */
/*                                                    */
/******************************************************/

#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <cstdlib>

#include <dirent.h>
#include <string.h>
#include <unistd.h>

using namespace std;

class LowerHtml
{
public:
    LowerHtml();
    void fileOpener();
    void searchAndLower(fstream&);
    string pathFix(string);
};

LowerHtml::LowerHtml()
{

}

void LowerHtml::fileOpener()
{
    string fname = "";
    string fpath = "";
    string ext = "";
    string dirAddr = "";
    int s_len = 0;
    bool atExt = false;
    bool isHtml = false;

    DIR *pDIR;
    struct dirent *entry;

    cout << "Enter the folder path you would like to sweep through: " << endl;
    getline(cin, dirAddr);
    dirAddr = pathFix(dirAddr);


    if( pDIR=opendir( dirAddr.c_str() ) ) //C:/Users/Jason.Jason-PC/Desktop/Test here
    {
        while(entry = readdir(pDIR))
        {
            if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
            {
                //cout << entry->d_name << "\n";
                fname = entry->d_name;
                s_len = fname.length();
                for(int i=0; i<s_len; i++)
                {
                    if(fname[i]=='.')
                        atExt = true;
                    if(atExt)
                        ext += fname[i];
                }
                atExt = false;
                if(ext == ".html" || ext == ".htm")
                    isHtml = true;
                ext = ""; //reset
                if(isHtml)
                {
                    fpath = dirAddr;
                    fpath += "/";
                    fpath += fname;
                    cout << fpath << endl;

                    fstream file(fpath.c_str(), std::ios::in | std::ios::out);
                    searchAndLower(file);
                    isHtml = false;
                }
            }
        }
        closedir(pDIR);
    }

    return;
}

void LowerHtml::searchAndLower(fstream& file)
{
    string reader = "";
    int str_len = 0;
    bool inTag = false;
    bool inQuo = false;
    int next_line = 0;
    int line = 0;
    int tol_line_len = 0;
    int qChk = 0;

    while(file)
    {
        getline(file, reader);                              //Reads line in file.
        tol_line_len += reader.length()+1;

        line = tol_line_len - (reader.length()+1);          //Position of beg of read line
        next_line = tol_line_len;                           //Position of next beg of next line
        str_len = reader.length();                          //Length of characters in line.
        file.seekp(line);                                   //Goes back to read line position

        for(int i = 0; i<str_len; i++)
        {
            if(reader[i] == '"')                            //Did it enter a quotation area? odd for in even for out.
            {
                 qChk += 1;
                 if(qChk % 2 != 0)
                    inQuo = true;
                 else if(qChk % 2 ==0)
                    inQuo = false;
            }
            if(reader[i] == '<')
            {
                inTag = true;
                i++;                   //To skip '<' from going through char check
            }
            else if(reader[i] == '>')
                inTag = false;
            if(inTag && !inQuo)
                if(isupper(reader[i]))
                    reader[i] = tolower(reader[i]);
        }
        file << reader;                 //Write corrected line to file.
        file.seekp(next_line);
    }
    file.close();
    return;
}

string LowerHtml::pathFix(string path)
{
    int str_len = 0;
    str_len = path.length();
    for( int i=0; i<str_len; i++ )
        if(path[i] == '\\')
            path[i] = '/';

    return path;
}


int main()
{
    LowerHtml lHtml;

    lHtml.fileOpener();


    return 0;
}







