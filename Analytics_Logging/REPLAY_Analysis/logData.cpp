#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;


class customString {
public:
    string value;
    int occurences;
    
    customString();
};

customString::customString() {
    value = "";
    occurences = 1;
}


void readLogCat(map<string,int>& lineMap) {
    ifstream file;
    string name;
    cout << "Reading logcat output file..." << endl;
    cout << "File name (logcat): ";
    cin >> name;
    file.open(name, ios::in);
    
    
    if(!file.is_open()) {
        cout << "Error: file not opened properly!" << endl;
        exit(1);
    }
    
    string line;
    string matchLine = "I/org.umd.logging";
    vector<string> stringList;
    vector<customString> methodList;
    vector<customString> apiList;
    
    //Put all UMD logging calls into a vector of strings
    while (!file.eof()) {
        getline(file, line);
        
        bool match = true;

        
        for(int i = 0; i < matchLine.length(); i++) {
            if (match == true && line[i] == matchLine[i]) {
                match = true;
            }
            else {
                match = false;
                break;
            }
        }
        
        if (match == true) {
            line.erase(0,matchLine.length() + 9);
            stringList.push_back(line);
        }
        
    }
    
    
    int methodCalls = 0;
    int apiCalls = 0;
    
    // Separate method/api calls into two vectors of custom strings
    for (int i = 0; i < stringList.size(); i++) {
        
        string line = stringList[i];
        
        if(line.front() == 'M') {
            line.erase(0, 9);
            
            //ERASE FIRST HALF BEFORE CALL
            bool done = false;
            while (!done) {
                if (line.front() == ' ') {
                    line.erase(0,1);
                    done = true;
                }
                else {
                    line.erase(0,1);
                }
            }
            
            //ERASE SECOND HALF AFTER CALL
            for (int j = 0; j < line.length(); j++) {
                if(line[j] == '(') {
                    line.erase(j, j-line.length());
                    break;
                }
            }
            
            //CHECK TO SEE IF MATCHES ALREADY EXITING METHOD
            if (methodList.size() == 0) {
                customString custom;
                custom.value = line;
                methodList.push_back(custom);
                methodCalls++;
            }
            else {
                bool found = false;
                for (int j = 0; j < methodList.size(); j++) {
                    if(line == methodList[j].value) {
                        methodList[j].occurences++;
                        methodCalls++;
                        found = true;
                        break;
                    }
                }
                if (found == false) {
                    customString custom;
                    custom.value = line;
                    methodList.push_back(custom);
                    methodCalls++;
                }
            }
            
        }
        else if (line.front() == 'A') {
            line.erase(0, 6);
            
            
            //ERASE FIRST HALF BEFORE CALL
            bool done = false;
            while (!done) {
                if (line.front() == ' ') {
                    line.erase(0,1);
                    done = true;
                }
                else {
                    line.erase(0,1);
                }
            }
            
            
            //ERASE SECOND HALF AFTER CALL
            for (int j = 0; j < line.length(); j++) {
                if(line[j] == '(') {
                    line.erase(j, j-line.length());
                    break;
                }
            }
            //CHECK TO SEE IF MATCHES ALREADY EXITING METHOD
            if (apiList.size() == 0) {
                customString custom;
                custom.value = line;
                apiList.push_back(custom);
                apiCalls++;
            }
            else {
                bool found = false;
                for (int j = 0; j < apiList.size(); j++) {
                    if(line == apiList[j].value) {
                        apiList[j].occurences++;
                        apiCalls++;
                        found = true;
                        break;
                    }
                }
                if (found == false) {
                    customString custom;
                    custom.value = line;
                    apiList.push_back(custom);
                    apiCalls++;
                }
            }
        }
    }
    

    //cout << "The METHOD calls in this apk run are: " << endl;
    for (int i = 0; i < methodList.size(); i++) {
        //cout << methodList[i].value << " OCCURS: " << methodList[i].occurences << "\n" << endl;
        lineMap[methodList[i].value] = methodList[i].occurences;
    }
    //cout << "\n \n \n" << endl;
    //cout << "The API calls in this apk run are: " << endl;
    for (int i = 0; i < apiList.size(); i++) {
        //cout << apiList[i].value << " OCCURS: " << apiList[i].occurences << "\n" << endl;
        lineMap[apiList[i].value] = apiList[i].occurences;
    }
    
    
    cout << "\n \n" << endl;
    //cout << "The number of total method calls: " << methodCalls << endl;
    //cout << "The number of total API calls : " << apiCalls << endl;
    
    
    ofstream outFile;
    string outName;
    cout << "Output file name (.csv): ";
    cin >> outName;
    outFile.open(outName);
    /*for(int i = 0; i < lineList.size(); i++) {
     lineList[i].erase(0,21);
     outFile << lineList[i] << "\n";
     }*/
    
    ofstream logList;
    string logName;
    cout << "Output file name (.txt): ";
    cin >> logName;
    logList.open(logName);
    
    //cout << "lineMap print out.... \n" << endl;
    for (auto& it : lineMap) {
        //cout << it.first << " : " << it.second << endl;
        outFile << it.first << "," << it.second << "\n";
        logList << it.first << endl;
    }
    
    outFile.close();
    logList.close();
    
    cout << "Total logged: " << lineMap.size() << endl;
    
}




map<string,int> readAllLogs() {
    ifstream file;
    string name;
    cout << "Reading total logging file..." << endl;
    cout << "File name (logfile): ";
    cin >> name;
    file.open(name, ios::in);
    
    
    if(!file.is_open()) {
        cout << "Error: file not opened properly!" << endl;
        exit(1);
    }
    
    string line;
    map<string,int> lineMap;
    
    int count = 0;
    while(!file.eof()) {
        getline(file, line);
        
        if(line[7] == 'm') {
            line.erase(0,21);
            for (int i = 0; i < line.size(); i++){
                if (line[i] == '/'){
                    line[i] = '.';
                }
                else if (line [i] == ';'){
                    line[i] = '.';
                    line.erase(i+1, 2);
                }
            }
            lineMap[line] = 0;
            count++;
        }
    }
    
    //cout << "\n \nTotal lines of logging: " << (count - 3) << endl;
    
    return lineMap;
    
}







int main() {
    
    //Read from total logging file (all methods?)
    map<string,int> lineMap;
    lineMap = readAllLogs();
    
    
    // Read from logcat output file to find methods/apis that were called
    readLogCat(lineMap);
}






















