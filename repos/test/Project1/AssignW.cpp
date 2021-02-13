#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>
#include <thread>         // std::thread
#include <mutex>
#include <ctime>
#include <iomanip>

// assumption: key is unique.
// if the pair with existing key arrives it will overwrite the old one
using namespace std;

time_t parseTime(const string& input) {
    struct tm tm;
    std::istringstream iss(input);
    //Feb 13 00:26:36 2018
    iss >> get_time(&tm, "%b %d %H:%M:%S %Y");
    time_t time = mktime(&tm);

    std::cout << time << std::endl;
    return time;
}

struct Info {
    Info(string _key, string _value, string _time="") :
        key(_key), value(_value), expTimeStr(_time) {
        if (expTimeStr != "")
            expTime = parseTime(expTimeStr);
    }
    string key;
    string value;
    string expTimeStr;
    int expTime;
};

void printInfo(Info *inf)
{
    if (inf)
        cout << "  key: " << inf->key << endl << 
                "  value: " << inf->value << endl << 
                "  exp: " << inf->expTimeStr << endl;
}

class Updater {

public:
    void addData(string key, string value, string date="");
    void removeData(string key); // assumption: data can be retrived by key
    Info* retriveData(string key);
    void removeExpired();   

private:
    mutex myMutex;
    unordered_map<string, Info*> infoMap;
    multimap<int, string> expMap;
    
};

//-----------------------------------------------------------
// the data will be added always to the main map
// and to the helper map only when it has experation date
//-----------------------------------------------------------
void Updater::addData(string key, string value, string time) {
    
    lock_guard<mutex> guard(myMutex);
    Info* info = new Info(key, value, time);

    infoMap[key] = info;
    if (time != "")
        expMap.emplace(info->expTime, key);
    std::cout << key << ": " << value << std::endl;
        
}

//----------------------------------------------------------
// the data will be removed from the main map only
// in the helper map it will be removed later by exp date
//----------------------------------------------------------
void Updater::removeData(string key) {
    
    lock_guard<mutex> guard(myMutex);
    if (infoMap.find(key) != infoMap.end())
    {
        infoMap.erase(key);
    }
    else cout << "Warning: no key " << key << "in the map" << endl;
        
}

//-----------------------------------------------------------
// retrives data if key exists or NULL if not
// NULL case should be taken care of in the client application
//------------------------------------------------------------
Info* Updater::retriveData(string key) {
    
    lock_guard<mutex> guard(myMutex);
    auto it = infoMap.find(key);
    if (it != infoMap.end())
    {
        return it->second;
    }
    else {
        cout << "Warning: no key " << key << "in the map" << endl;
        return NULL;
    }
}

//----------------------------------------------------------------------
// removes expired records. Runs in a separate thread that wakes-up every 
// 10 seconds and checkes for expired records
//-----------------------------------------------------------------------
void Updater::removeExpired()
{
        
    while (1) {  
        time_t now = time(0);
        auto it = expMap.begin();
        while (it != expMap.end()) {
            if (it->first <= now) {
                string key = it->second;
                myMutex.lock();
                expMap.erase(it++);
                if (infoMap.find(key) != infoMap.end())
                    infoMap.erase(key);
                myMutex.unlock();
            }
            else
                break;
        }
        for (auto& x : infoMap)
            cout << x.first << ": " << x.second << std::endl;
        cout << "--------------------------" << endl;
        this_thread::sleep_for(10s);
    }
}

int main()
{
    Updater upd;

    thread thr(&Updater::removeExpired, &upd);
    //thr.detach();
    cout << "Adding:" << endl;
    for (int i = 1; i <= 20; i++)
    {
        stringstream ssk, ssv;
        ssk << "key" << i;
        string my_key = ssk.str();
        ssv << "val" << i;
        string my_val = ssv.str();
        
        if (i == 2 || i == 4 || i == 12 || i == 14) upd.addData(my_key, my_val);
        if (i == 5 || i == 6) upd.addData(my_key, my_val, "Feb 13 00:26:36 2018");
        if (i == 15 || i == 16) upd.addData(my_key, my_val, "Nov 06 16:21:00 2020");
        
        
    }
    cout << "Done adding" << endl;

    cout << "Removing:" << endl;
    upd.removeData("key1"); // does not exist
    upd.removeData("key2");
    cout << "Done removing" << endl;

    cout << "Retriving:" << endl;
    Info* inf = upd.retriveData("key15");   
    printInfo(inf);
}

