#include <bits/stdc++.h>
#include <fstream>
#include "json.hpp"

#define endl "\n"
using json = nlohmann::json; 
using namespace std;

int nameWidth = 15; 
int numberWidth = 2;
struct game{
    string playerFirstName;
    string matchDate;
    int runScore;
    int wicketTaken;
    string roleInTeam;
    string playerTeam;
    string oppTeam;
};

struct ListNode{
    game g;
    ListNode* prev;
    ListNode* next;

    ListNode(game d) : g(d), prev(nullptr), next(nullptr) {}
};
// unordered_map<string, vector<game>> m;
unordered_map<string, ListNode*> m;
void table(){
    cout << "---------------------------" << endl;
}
void table1(){
    cout << "------------------" << endl;
}
void addinfo(string name, string date, int runs, int wick, string role, string t1, string t2, string name_dup){
    game g;
    g.playerFirstName = name_dup;
    g.matchDate = date;
    g.runScore = runs;
    g.wicketTaken = wick;
    g.roleInTeam = role;
    g.playerTeam = t1;
    g.oppTeam = t2;

    auto it = m.find(name);
    if(it != m.end()){
        ListNode* node = new ListNode(g);
        node->next = it->second;
        it->second->prev = node;
        it->second = node;
    }else{
        ListNode* node = new ListNode(g);
        m[name] = node;
    }
}

bool check_date(string &date){
    string d;
    string m;
    string y;
    int check = 0;
    for(long long unsigned int i = 0; i< date.length() ; ++i){
        char c = date[i];
        if(c=='/'){
            check++;
            continue;
        }
        if(check==0){
            d += c;
        }else if(check == 1){
            m += c;
        }else if(check == 2){
            y += c;
        }else{
            return false;
        }
    }
    int month = 0;
    int day = 0;
    int year = 0;
    int ii = 0;
    for(int i = d.length()-1;i>=0;i--){
        day += (d[i]-'0')*pow(10,ii);
        ii++;
    }
    ii = 0;
    for(int i = m.length()-1;i>=0;i--){
        month += (m[i]-'0')*pow(10,ii);
        ii++;
    }
    ii = 0;
    for(int i = y.length()-1;i>=0;i--){
        year += (y[i]-'0')*pow(10,ii);
        ii++;
    }
    int check1 = 0;

    if(day > 0 && day <= 31 && month > 0 && month <= 12 && year > 0){
        if (month % 2 == 1 && month <= 7 && day < 32) {
            check1 = 1;
        } else if (month % 2 == 0 && month > 7 && day < 32) {
            check1 = 1;
        } else if (month == 2 && day < 29 && year % 4 != 0) {
            check1 = 1;
        } else if (month == 2 && day <= 29 && year % 4 == 0) {
            check1 = 1;
        } else if (day < 31 && month != 2) {
            check1 = 1;
        } else {
            return false;
        }
    }else{
        return false;
    }
    if(check1 == 1){
        if (day < 10 && month < 10) {
            date = "0" + to_string(day) + "/" + "0" + to_string(month) + "/" + to_string(year);
        } else if (month < 10) {
            date = to_string(day) + "/" + "0" + to_string(month) + "/" + to_string(year);
        } else if (day < 10) {
            date = "0" + to_string(day) + "/" + to_string(month) + "/" + to_string(year);
        } else {
            date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
        }
    }

        
    return true;
}

string ask_date(){
    string date;
    bool flag = false;
    while(flag==false){
        cout << "Enter match Date (dd/mm/yyyy): ";
        cin >> date;
        flag = check_date(date);
        if(flag == false){
            cout << "Invalid Date Format!" << endl;
            continue;
        }
        // cout << date << endl;
    }
    return date;
}
int add_runs(string name_dup){
    int runs;
    bool flag = false;
    while(flag==false){
        cout << "Enter the number of runs "<<name_dup<<" scored: ";
        cin >> runs;
        if(runs<0){
            cout << "Number of Runs cannot be negative! Try again." << endl;
        }else{
            flag=true;
        }
    }
    return runs;
}
int add_wicks(string name_dup){
    int wicks;
    bool flag = false;
    while(flag==false){
        cout << "Enter the number of wickets "<<name_dup<<" took: ";
        cin >> wicks;
        if(wicks<0){
            cout << "Number of wickets cannot be negative! Try again." << endl;
        }else if(wicks>10){
            cout << "Number of wickets cannot exceed 10! Try again." << endl;
        }else{
            flag=true;
        }
    }
    return wicks;
}
void number1(){
    string sel;

    cout << endl;
    cout << endl;

    cout << "1 \tAdd Player Information \n2 \tAdd Match Inforomation" << endl;
    cout << endl;
    cout << "Enter the value: ";
    cin >> sel;
    cout << endl;
    if(sel == "1"){
        cout << "\tAdd Player Information"<<endl;
        cout << endl;
        string name;
        string date;
        int runs;
        int wick;
        string role;
        string team1;
        string team2;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter the player's name: ";
        getline(cin,name);
        string name_dup = name;
        for(auto &c : name){
            c=tolower(c);
        }
        // cout << name << endl;
        bool flag = false;
        // while(flag==false){
        //     cout << "Enter match Date (dd/mm/yyyy): ";
        //     cin >> date;
        //     flag = check_date(date);
        //     if(flag == false){
        //         cout << "Invalid Date Format!" << endl;
        //         continue;
        //     }
        //     // cout << date << endl;
        // }
        date = ask_date();
        // cout << "Enter the number of runs "<<name_dup<<" scored: ";
        // cin >> runs;
        // cout << "Enter the number of wickets "<<name_dup<<" took: ";
        // cin >> wick;
        runs = add_runs(name_dup);
        wick = add_wicks(name_dup);
        flag = false;
        while(flag==false){
            cout << "Enter the role of "<<name_dup<<": ";
            cin >> role;
            for(auto &c : role){
                c=tolower(c);
            }
            if(role == "bowler" || role == "batsman"){
                flag = true;
            }else{
                cout << "Enter either Bowler or Batsman" << endl;
            }
            // cout << flag << endl;
        }
        cout << "Enter the team "<<name_dup<<" played for: ";
        cin >> team1;
        cout << "Enter the opponent team "<<name_dup<<" faced: ";
        cin >> team2;
        addinfo(name,date,runs,wick,role,team1,team2,name_dup);
        cout << "\nInformation added successfully!" << endl;
    }else if(sel=="2"){
        cout << "Enter the number of players per team: " ;
        int numOfPlayer = 0;
        cin >> numOfPlayer;
        string date;
        string team1;
        string team2;
        cout << "Enter the team names: " << endl;
        cout << "Team 1: ";
        cin >> team1;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Team 2: ";
        cin >> team2;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        bool flag = false;
        // while(flag==false){
        //     cout << "Enter match Date (dd/mm/yyyy): ";
        //     cin >> date;
        //     flag = check_date(date);
        //     if(flag == false){
        //         cout << "Invalid Date Format!" << endl;
        //         continue;
        //     }
        //     // cout << date << endl;
        // }
        date = ask_date();
        cout << "\n\nInformation for "<<team1<<endl;
        for(int i=0 ;i<numOfPlayer;i++){
            string name;
            int runs;
            int wick;
            string role;
            // cout << endl;
            cout << "\nEnter player information for player "<< i+1 <<" :" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter the player's name: ";
            getline(cin,name);
            string name_dup = name;
            for(auto &c : name){
                c=tolower(c);
            }
            // cout << "Enter the number of runs "<<name_dup<<" scored: ";
            // cin >> runs;
            // cout << "Enter the number of wickets "<<name_dup<<" took: ";
            // cin >> wick;
            runs = add_runs(name_dup);
            wick = add_wicks(name_dup);
            flag = false;
            while(flag==false){
                cout << "Enter the role of "<<name_dup<<": ";
                cin >> role;
                for(auto &c : role){
                    c=tolower(c);
                }
                if(role == "bowler" || role == "batsman"){
                    flag = true;
                }else{
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter either Bowler or Batsman" << endl;
                }
                // cout << flag << endl;
            }
            addinfo(name,date,runs,wick,role,team1,team2,name_dup);
        }
        cout << endl << endl;
        cout << "Information for "<<team2<<endl;
        for(int i=0 ;i<numOfPlayer;i++){
            string name;
            int runs;
            int wick;
            string role;
            cout << "\nEnter player information for player "<< i+1 <<" :" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter the player's name: ";
            getline(cin,name);
            string name_dup = name;
            for(auto &c : name){
                c=tolower(c);
            }
            runs = add_runs(name_dup);
            wick = add_wicks(name_dup);
            flag = false;
            while(flag==false){
                cout << "Enter the role of "<<name_dup<<": ";
                cin >> role;
                
                for(auto &c : role){
                    c=tolower(c);
                }
                if(role == "bowler" || role == "batsman"){
                    flag = true;
                }else{
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter either Bowler or Batsman" << endl;
                }
                // cout << flag << endl;
            }
            addinfo(name,date,runs,wick,role,team2,team1,name_dup);
            // cout << "Information added successfully!" << endl;
        }
        cout << "\nInformation added successfully!" << endl;
    }else{
        cout << "Enter the correct value." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        number1();
    }
            
}
void number2(){
    cout << endl;
    cout << "1 \tDisplay match Information of a particular player \n2 \tDisplay Match Information of a particular date \n3 \tDisplay Match Information of all the players" << endl;
    cout << endl;
    cout << "Enter the value: ";
    // cout << "1 to Display match Information of a particular player, 2 to Display Match Information of a particular date, and 3 to Display Match Information of all the players: ";
    int num1 = 0;
    cin >> num1;
    cout << endl;
    if(num1 == 3){
        for(auto it : m){
            // cout << endl;
            // cout <<"Player Name: "<< it.first << endl << endl;
            // ListNode* current = it.second;
            // // cout << "Match Date \t Run Scored \t Wicket Taken \t Role in the Team \t Team \t Opposition Team" << endl;
            // cout << "  --------------------------------------------------------------------------------------------------------" << endl;
            // cout << setw(14) << "Match Date" << " | ";
            // cout << setw(12) << "Run Scored" << " | ";
            // cout << setw(15) << "Wicket Taken" << " | ";
            // cout << setw(20) << "Role in the Team" << " | ";
            // cout << setw(12) << "Team" << " | ";
            // cout << setw(17) << "Opposition Team" << endl;
            // cout << "  --------------------------------------------------------------------------------------------------------" << endl;
            // while (current != nullptr) {
            //     game g = current->g;
            //     // cout << g.matchDate << "\t" << g.runScore << "\t\t" << g.wicketTaken << "\t\t" << g.roleInTeam << "\t\t\t" << g.playerTeam << "\t\t" << g.oppTeam << endl;
            //     cout << setw(14) << g.matchDate << " | ";
            //     cout << setw(12) << g.runScore << " | ";
            //     cout << setw(15) << g.wicketTaken << " | ";
            //     cout << setw(20) << g.roleInTeam << " | ";
            //     cout << setw(12) << g.playerTeam << " | ";
            //     cout << setw(17) << g.oppTeam << endl;
            //     current = current->next;
            // }
            // cout << "  --------------------------------------------------------------------------------------------------------" << endl;
            // cout << endl;
            cout << endl;
            cout << " ----------------------------------------------------------------------------------------------------------" << endl;
            cout <<" Player Name: "<< it.first << endl;
            ListNode* current = it.second;

            cout << " ----------------------------------------------------------------------------------------------------------" << endl;
            cout << "|" << setw(14) << "Match Date" << " | ";
            cout << setw(12) << "Run Scored" << " | ";
            cout << setw(15) << "Wicket Taken" << " | ";
            cout << setw(20) << "Role in the Team" << " | ";
            cout << setw(12) << "Team" << " | ";
            cout << setw(17) << "Opposition Team" << " |" << endl;
            cout << " ----------------------------------------------------------------------------------------------------------" << endl;

            while (current != nullptr) {
                game g = current->g;
                cout << "|" << setw(14) << g.matchDate << " | ";
                cout << setw(12) << g.runScore << " | ";
                cout << setw(15) << g.wicketTaken << " | ";
                cout << setw(20) << g.roleInTeam << " | ";
                cout << setw(12) << g.playerTeam << " | ";
                cout << setw(17) << g.oppTeam << " |" << endl;
                current = current->next;
            }

            cout << " ----------------------------------------------------------------------------------------------------------" << endl;
            cout << endl;

        }
    }else if(num1 == 1){
        string name;
        cout << "Enter the player name: ";
        cin.ignore();
        getline(cin, name);
        cout << endl << endl;
        for (auto &c : name) {
            c = tolower(c);
        }
        auto it = m.find(name);
        if(it != m.end()){
            cout << " ----------------------------------------------------------------------------------------------------------" << endl;
            cout <<" Player Name: "<< it->first << endl;
            ListNode* current = it->second;
            cout << " ----------------------------------------------------------------------------------------------------------" << endl;
            cout << "|" << setw(14) << "Match Date" << " | ";
            cout << setw(12) << "Run Scored" << " | ";
            cout << setw(15) << "Wicket Taken" << " | ";
            cout << setw(20) << "Role in the Team" << " | ";
            cout << setw(12) << "Team" << " | ";
            cout << setw(17) << "Opposition Team" << " |" << endl;
            cout << " ----------------------------------------------------------------------------------------------------------" << endl;

            while (current != nullptr) {
                game g = current->g;
                cout << "|" << setw(14) << g.matchDate << " | ";
                cout << setw(12) << g.runScore << " | ";
                cout << setw(15) << g.wicketTaken << " | ";
                cout << setw(20) << g.roleInTeam << " | ";
                cout << setw(12) << g.playerTeam << " | ";
                cout << setw(17) << g.oppTeam << " |" << endl;
                current = current->next;
            }
            cout << " ----------------------------------------------------------------------------------------------------------" << endl;
        } else {
            cout << "Player not found!" << endl;
        }
    }else if(num1 == 2){
        string date;
        date = ask_date();
        for(auto it : m){
            ListNode* current = it.second;
            vector<game> gg;
            while(current != nullptr){
                game g = current->g;
                if (g.matchDate == date){
                    gg.push_back(g);
                }
                current = current->next;
            }
            if(!gg.empty()){
                // cout << endl;
                cout << " ----------------------------------------------------------------------------------------------------------" << endl;
                cout <<" Player Name: "<< it.first << endl;
                // cout << "Match Date \t Run Scored \t Wicket Taken \t Role in the Team \t Team \t Opposition Team" << endl;
                cout << " ----------------------------------------------------------------------------------------------------------" << endl;
                cout << "|" << setw(14) << "Match Date" << " | ";
                cout << setw(12) << "Run Scored" << " | ";
                cout << setw(15) << "Wicket Taken" << " | ";
                cout << setw(20) << "Role in the Team" << " | ";
                cout << setw(12) << "Team" << " | ";
                cout << setw(17) << "Opposition Team" << " |" << endl;
                cout << " ----------------------------------------------------------------------------------------------------------" << endl;
                for (auto itt : gg) {
                    // cout << itt.matchDate << "\t" << itt.runScore << "\t\t" << itt.wicketTaken << "\t\t" << itt.roleInTeam << "\t\t\t" << itt.playerTeam << "\t\t" << itt.oppTeam << endl;
                    // cout << setw(14) << itt.matchDate << " | ";
                    // cout << setw(12) << itt.runScore << " | ";
                    // cout << setw(15) << itt.wicketTaken << " | ";
                    // cout << setw(20) << itt.roleInTeam << " | ";
                    // cout << setw(12) << itt.playerTeam << " | ";
                    // cout << setw(17) << itt.oppTeam << endl;
                    cout << "|" << setw(14) << itt.matchDate << " | ";
                    cout << setw(12) << itt.runScore << " | ";
                    cout << setw(15) << itt.wicketTaken << " | ";
                    cout << setw(20) << itt.roleInTeam << " | ";
                    cout << setw(12) << itt.playerTeam << " | ";
                    cout << setw(17) << itt.oppTeam << " |" << endl;
                }
                cout << " ----------------------------------------------------------------------------------------------------------" << endl;
            }
            cout << endl << endl;
        }
    }else {
        cout << "Enter the correct value." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        number2();
    }
}
void number3() {
    cout << endl;
    cout << "Enter a number to view the x numbers of top runs per batsman: ";
    int nn = 0;
    cin >> nn;
    int check = 0;
    cout << endl;
    for(auto it : m){
        check = 1;
        string name = it.first;
        ListNode* current = it.second;
        priority_queue<pair<int, string>> p;
        while(current != nullptr) {
            game g = current->g;
            name = g.playerFirstName;
            pair<int, string> temp;
            temp.first = g.runScore;
            temp.second = g.matchDate;
            p.push(temp);
            current = current->next;
        }
        cout << endl << endl;
        // table();
        cout << "--------------------------------" << endl;
        cout << " Player Name: " << name << endl;
        cout << " ------------------------------ " << endl;
        cout << "|" << setw(14) << "Match Date" << " | ";
        cout << setw(12) << "Runs Scored" << " |" << endl;
        cout << "|------------------------------|" << endl;
        for (int j = 0; j < nn && !p.empty(); j++) {
            int runs = p.top().first;
            string date = p.top().second;
            cout << "|" << setw(14) << date << " | ";
            cout << setw(12) << runs << " |" << endl;
            p.pop();
        }
        cout << " ------------------------------ " << endl;

    }
    if(check == 0){
        cout << "No players found in the database." << endl;
    }
}
void number4(){
    cout << endl;
    cout << "Enter the number of top Batsmen and Bowlers you want to display: ";
    int nn;
    cin >> nn;
    cout << endl;
    // vector<int,string> runs;
    // vector<int,string> wicks;
    priority_queue<pair<int, string>> bowl;
    priority_queue<pair<int, string>> bat;

    for(auto it : m){
        string name = it.first;
        ListNode* current = it.second;
        int runs = 0;
        int wicks = 0;

        while(current != nullptr){
            game g = current->g;
            if(g.roleInTeam == "bowler") {
                runs += g.runScore;
            }else {
                wicks += g.wicketTaken;
            }
            current = current->next;
        }

        if(runs != 0){
            bowl.push({runs, name});
        }

        if(wicks != 0){
            bat.push({wicks, name});
        }
    }
    int ch = 0;
    if (!bowl.empty()) {
        ch = 1;
        cout << endl;
        cout << "Top " << nn << " Bowlers (Total Runs):" << endl << endl;
        cout << " ----------------------------- " << endl;
        cout << "| " << setw(13) << "Player" << " | " << setw(11) << "Total Runs  |" << endl;
        cout << "|-----------------------------|" << endl;
    }

    for (int i = 0; i < nn && !bowl.empty(); i++) {
        cout << "| " << setw(13) << bowl.top().second << " | " << setw(11) << bowl.top().first << " |" << endl;
        bowl.pop();
    }
    if(ch==1){
        cout << " ----------------------------- " << endl;
    }
    ch = 0;

    if (!bat.empty()) {
        ch = 1;
        cout << endl << endl;
        cout << "Top " << nn << " Batsmen (Total Wickets):" << endl << endl;
        cout << " --------------------------------- " << endl;
        cout << "| " << setw(15) << "Player" << " | " << setw(13) << "Total Wickets |" << endl;
        cout << "|---------------------------------|" << endl;
    }

    for (int i = 0; i < nn && !bat.empty(); i++) {
        cout << "| " << setw(15) << bat.top().second << " | " << setw(13) << bat.top().first << " |" << endl;
        bat.pop();
    }
    if(ch==1){
        cout << " --------------------------------- " << endl;
    }

}
void number5(){
    cout << endl;
    cout << "Enter the name of the player you want to delete record off: ";
    string name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,name);
    cout << endl;
    for(auto &c : name){
        c=tolower(c);
    }
    if(m.find(name)==m.end()){
        cout << "The player doest exisit."<<endl;
    }else{
        m.erase(name);
        cout << "Record deleted successfully!"<<endl;
    }
}
void number6(){
    cout << endl;
    priority_queue<pair<double, string>> runs;
    priority_queue<pair<double, string>> wicks;
    int check = 0;

    for(auto it : m){
        double totalRun = 0;
        double totalWic = 0;
        string name = it.first;
        ListNode* current = it.second;
        double matches = 0;

        while(current != nullptr){
            game g = current->g;
            totalRun += g.runScore;
            totalWic += g.wicketTaken;
            matches++;
            current = current->next;
        }

        if(matches == 0){
            continue;
        }else{
            check = 1;
            double r = totalRun / matches;
            double w = totalWic / matches;
            runs.push({r, name});
            wicks.push({w, name});
        }
    }

    if(check == 0) {
        cout << "No players found in the database." << endl;
        return;
    }

    // cout << "Runs Average for each player:" << endl;
    // if(!runs.empty()){
    //     cout << endl << "Player \t Average Runs" << endl;
    // }
    
    // while(!runs.empty()) {
    //     cout << runs.top().second << " \t" << runs.top().first << endl;
    //     runs.pop();
    // }

    // cout << "\n\n" << endl;
    // cout << "Wicket Average for each player:" << endl;
    // if(!wicks.empty()){
    //     cout << endl << "Player \t Average Wickets" << endl;
    // }
    // while(!wicks.empty()) {
    //     cout <<wicks.top().second << " \t" << wicks.top().first << endl;
    //     wicks.pop();
    // }
    cout << "Runs Average for each player:" << endl;
    if (!runs.empty()) {
        cout << endl;
        cout << " ------------------------------- " << endl;
        cout << "| " << setw(11) << "Player" << " | " << setw(15) << "Average Runs    |" << endl;
        cout << "|-------------------------------|" << endl;
    }
    
    while (!runs.empty()) {
        cout << "| " << setw(11) << runs.top().second << " | " << setw(15) << runs.top().first << " |" << endl;
        runs.pop();
    }
    cout << " ------------------------------- " << endl;
    cout << "\n\n" << endl;
    cout << "Wicket Average for each player:" << endl;
    if (!wicks.empty()) {
        cout << endl;
        cout << " ------------------------------- " << endl;
        cout << "| " << setw(11) << "Player" << " | " << setw(15) << "Average Wickets |" << endl;
        cout << "|-------------------------------|" << endl;
    }

    while (!wicks.empty()) {
        cout << "| " << setw(11) << wicks.top().second << " | " << setw(15) << wicks.top().first << " |" << endl;
        wicks.pop();
    }
    cout << " ------------------------------- " << endl;

}
void number7(){
    cout << endl;
    int num;
    cout << "Enter the number of top players to display: ";
    cin >> num;
    cout << endl;
    priority_queue<pair<int,string>> cen , half;
    for(auto it : m){
        string name = it.first;
        ListNode* current = it.second;
        int century = 0;
        int halfcen = 0;
        while (current!=nullptr){
            game g = current -> g;
            // cout << name << endl;
            if(g.runScore >= 100){
                // cout << g.runScore << endl;
                century ++;
            }else if(g.runScore >= 50){
                halfcen ++;
            }
            current = current -> next;
        }
        cen.push(make_pair(century,name));
        half.push(make_pair(halfcen,name));
    }
    // if(!cen.empty() && cen.top().first != 0){
    //     cout << endl;
    //     cout << "Player \t Number of centuries" << endl << endl;
    // }
    // for(int i = 0; i < num && !cen.empty() ; i++){
    //     if(cen.top().first == 0){
    //         break;
    //     }
    //     cout <<  cen.top().second << " \t " << cen.top().first << endl; 
    //     cen.pop();
    // }
    // if(!half.empty() && half.top().first!=0){
    //     cout << endl;
    //     cout << "Player \t Number of half-centuries" << endl << endl;
    // }
    // for(int i = 0; i < num && !half.empty() ; i++){
    //     if(half.top().first==0){
    //         break;
    //     }
    //     cout << "|" << half.top().second << " \t| " << half.top().first << endl; 
    //     half.pop();
    // }
    if (!cen.empty() && cen.top().first != 0) {
        cout << endl;
        cout << " ----------------------------------- " << endl;
        cout << "| " << setw(11) << "Player" << " | " << setw(17) << "Number of Centuries |" << endl;
        cout << "|-----------------------------------|" << endl ;
    }

    for (int i = 0; i < num && !cen.empty(); i++) {
        if (cen.top().first == 0) {
            break;
        }
        cout << "| " << setw(11) << cen.top().second << " | " << setw(17) << cen.top().first << "   |" << endl;
        cen.pop();
    }
    cout << " ----------------------------------- " << endl;

    if (!half.empty() && half.top().first != 0) {
        cout << endl;
        cout << " ---------------------------------------- " << endl;
        cout << "| " << setw(11) << "Player" << " | " << setw(21) << "Number of Half-Centuries |" << endl;
        cout << "|----------------------------------------|" << endl;
    }

    for (int i = 0; i < num && !half.empty(); i++) {
        if (half.top().first == 0) {
            break;
        }
        cout << "| " << setw(11) << half.top().second << " | " << setw(21) << half.top().first << "    |" << endl;
        half.pop();
    }
    cout << " ---------------------------------------- " << endl;


}

void find_total(int flag , int &total){
    if(flag == 0){
        for(auto it : m){
            ListNode* current = it.second;
            while (current != nullptr) {
                total += current->g.runScore;
                current = current->next;
            }
        }
    }else if(flag == 1){
        for(auto it : m){
            ListNode* current = it.second;
            while (current != nullptr) {
                total += current->g.wicketTaken;
                current = current->next;
            }
        }
    }
}

void hist(ListNode* current, string stat,int &total,string name) {
    unordered_map<string, int> data;
    // if(current == NULL){
    //     return;
    // }
    // string name = current->g.playerFirstName;
    while(current != nullptr){
        game g = current->g;
        
        if (data.find(name) == data.end()) {
            data[name] = 0;
        }
        if (stat == "runs") {
            data[name] += g.runScore;
            // total += g.runScore;
        } else if (stat == "wickets") {
            data[name] += g.wicketTaken;
            // total += g.wicketTaken;
        }
        current = current->next;
    }
    // cout << total << endl;
    // cout << "Histogram of " << stat << " per player:" << endl;
    for(auto entry : data){
        string name = entry.first;
        int value = entry.second;
        if(value == 0){
            continue;
        }
        cout << name << "\t";
        // cout << (((float)value*100)/total) << endl;
        for (int i = 0; i < (int)(((float)value*100)/total); i++) {
            cout << "*";
        }
        cout << endl;
    }
}

void number8() {
    cout << endl << endl;
    cout << "1 \tRuns Histogram Representation \n2 \tWickets Histogram Representation" << endl;
    cout << endl;
    cout << "Enter the value: ";
    // cout << "Enter 1 for Runs Histogram or 2 for Wickets Histogram: ";
    int choice;
    cin >> choice;
    cout << endl;

    int total = 0;
    if(choice == 1){
        cout << "-----------------------------" << endl;
        cout << "| Displaying Runs Histogram |" << endl;
        cout << "-----------------------------" << endl;
        cout << endl;
        find_total(0,total);
        for (auto it : m) {
            string name = it.first;
            ListNode* current = it.second;
            hist(current, "runs",total,name);
        }
    }else if(choice == 2){
        cout << "--------------------------------" << endl;
        cout << "| Displaying Wickets Histogram |" << endl;
        cout << "--------------------------------" << endl;
        cout << endl;
        find_total(1,total);
        for (auto it : m) {
            string name = it.first;
            ListNode* current = it.second;
            hist(current, "wickets",total,name);
        }
    }else{
        cout << "Enter the correct value." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        number8();
    }
}

void addinfoToJson(json& datasetJson, const std::string& name, const std::string& date, int score, int wickets,
                   const std::string& role, const std::string& team1, const std::string& team2, const std::string& player) {
    json playerJson = {
        {"name", name},
        {"date", date},
        {"score", score},
        {"wickets", wickets},
        {"role", role},
        {"team1", team1},
        {"team2", team2},
        {"player", player}
    };

    datasetJson.push_back(playerJson);
}


void saveDatasetToJson() {
    json datasetJson;


    for(auto it : m){
        ListNode* current = it.second;
        while (current != nullptr) {
            game g = current->g;
            addinfoToJson(datasetJson,it.first,g.matchDate,g.runScore,g.wicketTaken,g.roleInTeam,g.playerTeam,g.oppTeam,g.playerFirstName);
            current = current->next;
        }
    }
    
    // addinfoToJson(datasetJson,"ravi", "01/01/2023", 50, 2, "batsman", "India", "Pakistan", "Ravi");
    // addinfoToJson(datasetJson,"ravi", "01/03/2023", 60, 3, "batsman", "India", "Australia", "Ravi");
    // addinfoToJson(datasetJson,"ravi", "13/02/2023", 550, 2, "bowler", "India", "Australia", "Ravi");

    // addinfoToJson(datasetJson,"neha", "01/01/2023", 30, 1, "batsman", "India", "Pakistan", "Neha");
    // addinfoToJson(datasetJson,"neha", "11/01/2023", 12, 2, "batsman", "India", "Australia", "Neha");
    // addinfoToJson(datasetJson,"neha", "03/03/2023", 23, 2, "batsman", "India", "Pakistan", "Neha");

    // addinfoToJson(datasetJson,"amit", "01/01/2023", 20, 3, "bowler", "India", "Pakistan", "Amit");
    // addinfoToJson(datasetJson,"amit", "01/02/2023", 48, 0, "batsman", "Pakistan", "Australia", "Amit");
    // addinfoToJson(datasetJson,"amit", "01/02/2023", 23, 1, "bowler", "Australia", "England", "Amit");

    // addinfoToJson(datasetJson,"kiran", "01/01/2023", 15, 2, "batsman", "Pakistan", "India", "Kiran");
    // addinfoToJson(datasetJson,"kiran", "01/03/2023", 10, 1, "batsman", "Australia", "India", "Kiran");
    // addinfoToJson(datasetJson,"kiran", "02/02/2023", 122, 2, "batsman", "India", "England", "Kiran");

    // addinfoToJson(datasetJson,"arun", "01/02/2023", 45, 0, "batsman", "India", "England", "Arun");
    // addinfoToJson(datasetJson,"arun", "02/02/2023", 49, 6, "batsman", "India", "England", "Arun");
    // addinfoToJson(datasetJson,"arun", "05/02/2023", 60, 5, "batsman", "India", "England", "Arun");

    // addinfoToJson(datasetJson,"saloni", "01/02/2023", 25, 2, "bowler", "India", "England", "Saloni");
    // addinfoToJson(datasetJson,"saloni", "03/02/2023", 55, 2, "bowler", "India", "Australia", "Saloni");
    // addinfoToJson(datasetJson,"saloni", "02/02/2023", 205, 2, "bowler", "India", "Pakistan", "Saloni");

    // addinfoToJson(datasetJson,"david", "01/02/2023", 35, 0, "batsman", "England", "India", "David");
    // addinfoToJson(datasetJson,"david", "11/02/2023", 30, 0, "batsman", "England", "India", "David");
    // addinfoToJson(datasetJson,"david", "04/05/2023", 75, 0, "batsman", "England", "India", "David");

    // addinfoToJson(datasetJson,"akshay", "01/01/2023", 40, 2, "batsman", "Pakistan", "India", "Akshay");
    // addinfoToJson(datasetJson,"akshay", "01/03/2023", 65, 3, "batsman", "Australia", "Pakistan", "Akshay");
    // addinfoToJson(datasetJson,"akshay", "01/11/2023", 49, 2, "batsman", "Pakistan", "India", "Akshay");

    // addinfoToJson(datasetJson,"priya", "01/01/2023", 28, 1, "batsman", "England", "India", "Priya");
    // addinfoToJson(datasetJson,"priya", "11/03/2023", 48, 5, "batsman", "Pakistan", "Australia", "Priya");
    // addinfoToJson(datasetJson,"priya", "01/07/2023", 85, 9, "batsman", "Pakistan", "Australia", "Priya");

    // addinfoToJson(datasetJson,"olivia", "01/02/2023", 23, 1, "bowler", "Australia", "England", "Olivia");
    // addinfoToJson(datasetJson,"olivia", "01/06/2023", 103, 4, "bowler", "Australia", "England", "Olivia");
    // addinfoToJson(datasetJson,"olivia", "11/02/2023", 203, 6, "bowler", "Australia", "England", "Olivia");

    // addinfoToJson(datasetJson,"rushil", "01/02/2023", 33, 0, "batsman", "England", "Australia", "Rushil");
    // addinfoToJson(datasetJson,"rushil", "02/02/2023", 200, 0, "batsman", "England", "New Zealand", "Rushil");
    // addinfoToJson(datasetJson,"rushil", "03/02/2023", 303, 0, "batsman", "England", "India", "Rushil");

    // addinfoToJson(datasetJson,"siddh", "13/02/2023", 550, 2, "bowler", "India", "Australia", "Siddh");
    // addinfoToJson(datasetJson,"siddh", "23/02/2023", 122, 2, "bowler", "India", "England", "Siddh");
    // addinfoToJson(datasetJson,"siddh", "03/03/2023", 23, 2, "bowler", "India", "Pakistan", "Siddh");
    

    
    ofstream jsonFile("dataset.json");
    jsonFile << std::setw(4) << datasetJson;  
    jsonFile.close();
}

void loadDatasetFromJson() {
    ifstream inputFile("dataset.json");
    json datasetJson;
    inputFile >> datasetJson;
    inputFile.close();

    for (const auto& playerEntry : datasetJson) {
        string name = playerEntry["name"];
        string date = playerEntry["date"];
        int score = playerEntry["score"];
        int wickets = playerEntry["wickets"];
        string role = playerEntry["role"];
        string team1 = playerEntry["team1"];
        string team2 = playerEntry["team2"];
        string player = playerEntry["player"];

        
        addinfo(name,date,score,wickets,role,team1,team2,player);
    }
}

void dataset(){
    addinfo("ravi", "01/01/2023", 50, 2, "batsman", "India", "Pakistan", "Ravi");
    addinfo("ravi", "01/03/2023", 60, 3, "batsman", "India", "Australia", "Ravi");
    addinfo("ravi", "13/02/2023", 550, 2, "bowler", "India", "Australia", "Ravi");

    addinfo("neha", "01/01/2023", 30, 1, "batsman", "India", "Pakistan", "Neha");
    addinfo("neha", "11/01/2023", 12, 2, "batsman", "India", "Australia", "Neha");
    addinfo("neha", "03/03/2023", 23, 2, "batsman", "India", "Pakistan", "Neha");

    addinfo("amit", "01/01/2023", 20, 3, "bowler", "India", "Pakistan", "Amit");
    addinfo("amit", "01/02/2023", 48, 0, "batsman", "Pakistan", "Australia", "Amit");
    addinfo("amit", "01/02/2023", 23, 1, "bowler", "Australia", "England", "Amit");

    addinfo("kiran", "01/01/2023", 15, 2, "batsman", "Pakistan", "India", "Kiran");
    addinfo("kiran", "01/03/2023", 10, 1, "batsman", "Australia", "India", "Kiran");
    addinfo("kiran", "02/02/2023", 122, 2, "batsman", "India", "England", "Kiran");

    addinfo("arun", "01/02/2023", 45, 0, "batsman", "India", "England", "Arun");
    addinfo("arun", "02/02/2023", 49, 6, "batsman", "India", "England", "Arun");
    addinfo("arun", "05/02/2023", 60, 5, "batsman", "India", "England", "Arun");

    addinfo("saloni", "01/02/2023", 25, 2, "bowler", "India", "England", "Saloni");
    addinfo("saloni", "03/02/2023", 55, 2, "bowler", "India", "Australia", "Saloni");
    addinfo("saloni", "02/02/2023", 205, 2, "bowler", "India", "Pakistan", "Saloni");

    addinfo("david", "01/02/2023", 35, 0, "batsman", "England", "India", "David");
    addinfo("david", "11/02/2023", 30, 0, "batsman", "England", "India", "David");
    addinfo("david", "04/05/2023", 75, 0, "batsman", "England", "India", "David");

    addinfo("akshay", "01/01/2023", 40, 2, "batsman", "Pakistan", "India", "Akshay");
    addinfo("akshay", "01/03/2023", 65, 3, "batsman", "Australia", "Pakistan", "Akshay");
    addinfo("akshay", "01/11/2023", 49, 2, "batsman", "Pakistan", "India", "Akshay");

    addinfo("priya", "01/01/2023", 28, 1, "batsman", "England", "India", "Priya");
    addinfo("priya", "11/03/2023", 48, 5, "batsman", "Pakistan", "Australia", "Priya");
    addinfo("priya", "01/07/2023", 85, 9, "batsman", "Pakistan", "Australia", "Priya");

    addinfo("olivia", "01/02/2023", 23, 1, "bowler", "Australia", "England", "Olivia");
    addinfo("olivia", "01/06/2023", 103, 4, "bowler", "Australia", "England", "Olivia");
    addinfo("olivia", "11/02/2023", 203, 6, "bowler", "Australia", "England", "Olivia");

    addinfo("rushil", "01/02/2023", 33, 0, "batsman", "England", "Australia", "Rushil");
    addinfo("rushil", "02/02/2023", 200, 0, "batsman", "England", "New Zealand", "Rushil");
    addinfo("rushil", "03/02/2023", 303, 0, "batsman", "England", "India", "Rushil");

    addinfo("siddh", "13/02/2023", 550, 2, "bowler", "India", "Australia", "Siddh");
    addinfo("siddh", "23/02/2023", 122, 2, "bowler", "India", "England", "Siddh");
    addinfo("siddh", "03/03/2023", 23, 2, "bowler", "India", "Pakistan", "Siddh");

}

int main(){

    // dataset();

    
    loadDatasetFromJson();

    while(1){
        
        cout << endl;
        cout << "   Selection Menu"<<endl;
        cout << "1 \tAdd Match Information \n2 \tDisplay Match Information \n3 \tDisplay player-wise maximum run scored \n4 \tDisplay top bowlers (using total run) and top batsmans (using total wickets)\n5 \tTo delete player information\n6 \tTo Display Average Runs and Wickets\n7 \tTo Display number of Top players who scored the most centuries and half-centuries\n8 \tTo display histogram representation of Runs and Wickets Per Player\n9 \tTo save Data Set to the Json File \n0 \tTo exit the program " << endl<<endl;
        cout << "Enter the value: ";

        string num;
        cin >> num;

        if(num=="0"){
            break;
        }else if(num=="1"){
            number1();
            saveDatasetToJson();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }else if(num=="2"){
            number2(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }else if(num=="3"){
            number3();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }else if(num=="4"){
            number4();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }else if(num == "5"){
            number5();
            saveDatasetToJson();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }else if(num == "6"){
            number6();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }else if(num == "7"){
            number7();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }else if(num == "8"){
            number8();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }else if(num == "9"){
            saveDatasetToJson();
            cout << "Data Set Saved to Json file" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }else{
            cout << "Enter a valid input." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    }
    cout << endl;
    saveDatasetToJson();
    cout << "Successfully exited the program." << endl;
    cout << endl;

    return 0;
}