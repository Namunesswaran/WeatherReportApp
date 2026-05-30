// Muhammad Luqman Hakim bin Mohammad 'Asri [24000087]
// Muhammad Faizzuddin bin Mohd Nazli [24000085]
// Namunesswaran A/L Siva Perumal [24000043]
// Ivan Jerard Gnanakannu [24008940]

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>  
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_DISTRICTS 1000  

char menu; 

// Struct to store year and temperature
struct TempRecord {
    int year;
    double avgTemp;
};

//get average temperature
float getAvgTemp(const string& range) {
    size_t pos = range.find('-');
    if (pos == string::npos) return -1; 

    int low = stoi(range.substr(0, pos));  
    int high = stoi(range.substr(pos + 1)); 

    return (low + high) / 2.0; 
}

void menuOption();
void tempTrend();
void rainfall();
void climate();

int main (){
    menuOption();
    return 0;
}

// menu interface
void menuOption(){
    do{
    cout<<"---------[Welcome to Malaysian Meteorological Department Weather Analysis]---------"<<endl<<endl;

    cout<<"[Choose any of the available options]"<<endl<<endl;
    cout<<"Input 'A' to display Temperature Trends"<<endl;
    cout<<"Input 'B' to display Rainfall Analysis"<<endl;
    cout<<"Input 'C' to display Climate Change Impact"<<endl;
    cout<<"Option (Input X To Exit Program): ";

    cin>>menu;
    cout<<endl;

    switch(menu){
        case 'A': tempTrend(); break;
        case 'B': rainfall(); break;
        case 'C': climate(); break;
        case 'X': cout << "Exited the Program.....\n"; break;
        default : system("cls"); cout<<"[Please Enter A Valid Menu Option!]"<<endl; cout<<endl;
    }
    } while (menu != 'X');
}

// temperature trend function
void tempTrend(){
    do {
        cout << "Continue with Temperature Trends? (Y/N): ";
        cin >> menu;

        if (menu == 'Y' || menu == 'y') {
            system("cls");
            ifstream inputFile("C:/Users/USER/Downloads/Weather_Statistics.txt");
            ofstream highFile("High_Temp.txt");
            ofstream lowFile("Low_Temp.txt");

            if (!inputFile) {
                cout << "Error: Unable to open Weather_Statistics.txt\n";
            }
            if (!highFile || !lowFile) {
                cout << "Error: Unable to create output files\n";
            }

            string line;
            getline(inputFile, line); 

           
            highFile << left << setw(15) << "State" 
                     << setw(15) << "District"
                     << setw(15) << "Temp (°C)" << endl;
            highFile << string(45, '-') << endl;

            lowFile << left << setw(15) << "State" 
                    << setw(15) << "District"
                    << setw(15) << "Temp (°C)" << endl;
            lowFile << string(45, '-') << endl;

            while (getline(inputFile, line)) {
                stringstream ss(line);
                string state, district, year, tempRange, tempRest;

                getline(ss, state, ',');
                getline(ss, district, ',');
                getline(ss, year, ',');
                getline(ss, tempRange, ','); // Get only the temperature range
                getline(ss, tempRest); // Skip the rest of the line

                float avgTemp = getAvgTemp(tempRange);

                // Choose the correct file to write to
                ofstream& outFile = (avgTemp > 30) ? highFile : lowFile;
                outFile << left << setw(15) << state
                        << setw(15) << district
                        << setw(15) << tempRange << endl;
            }

            cout << "Temperature Trends completed. Results saved in High_Temp.txt and Low_Temp.txt\n";
        }

    } while (menu == 'Y' || menu == 'y');

    system("cls");
    menuOption();
}

// rainfall analysis function
void rainfall(){
    cout << "Continue with Rainfall Analysis (Y/N): ";
    cin >> menu;

    if (menu == 'Y' || menu == 'y') {
        system("cls"); 

        ifstream inputFile("C:/Users/USER/Downloads/Weather_Statistics.txt");
        ofstream outputFile("Rainfall_Analysis.txt");

        if (!inputFile) {
            cout << "Error: Unable to open Weather_Statistics.txt\n";
        }
        if (!outputFile) {
            cout << "Error: Unable to create Rainfall_Analysis.txt\n";
        }

        string district[MAX_DISTRICTS];
        int totalRainfall[MAX_DISTRICTS] = {0};
        int count[MAX_DISTRICTS] = {0};
        int index = 0;

        string line, state, dist, year, temperature, humidity;
        int rainfall;

        getline(inputFile, line);  

        while (getline(inputFile, line)) {
            stringstream ss(line);
            getline(ss, state, ',');
            getline(ss, dist, ',');
            getline(ss, year, ',');
            getline(ss, temperature, ',');

            string rainfallStr;
            getline(ss, rainfallStr, ',');
            getline(ss, humidity, ',');

            try {
                rainfall = stoi(rainfallStr);
            } catch (invalid_argument&) {
                cout << "Warning: Invalid rainfall value '" << rainfallStr << "' in line: " << line << endl;
                continue;
            }

            string fullDistrict = state + " " + dist;

            int i;
            for (i = 0; i < index; i++) {
                if (district[i] == fullDistrict) {
                    totalRainfall[i] += rainfall;
                    count[i]++;
                    break;
                }
            }

            if (i == index) {
                if (index >= MAX_DISTRICTS) {
                    cout << "Error: Maximum district limit reached!" << endl;
                    break;
                }
                district[index] = fullDistrict;
                totalRainfall[index] = rainfall;
                count[index] = 1;
                index++;
            }
        }

       
        outputFile << left << setw(25) << "District"
                   << setw(15) << "Total Rainfall"
                   << setw(20) << "Average Rainfall\n";
        outputFile << string(60, '-') << "\n";

        for (int i = 0; i < index; i++) {
            double avgRainfall = static_cast<double>(totalRainfall[i]) / count[i];
            outputFile << left << setw(25) << district[i]
                       << setw(15) << totalRainfall[i]
                       << setw(20) << fixed << setprecision(2) << avgRainfall << "\n";

            if (totalRainfall[i] > 1000) {
                cout << "District " << district[i] << " has annual rainfall above 1000mm.\n";
            }
        }

        cout << "Rainfall analysis completed. Results saved in Rainfall_Analysis.txt\n";

        inputFile.close();
        outputFile.close();
    } 
    else if (menu == 'N' || menu == 'n') {
        system("cls");
        menuOption();  
    } 
    else {
        cout << "Invalid input! Please enter Y or N.\n";
    }
}

// climate change function
void climate(){
    do {
        cout << "Continue with Climate Change Impact (Y/N): ";
        cin >> menu;
        if (menu == 'Y' || menu == 'y') {
            system("cls");

            ifstream file("C:/Users/USER/Downloads/Weather_Statistics.txt");
    ofstream outFile("Climate_Change_Impact.txt");

    if (!file || !outFile) {
        cout << "Error: Unable to open Weather_Statistics.txt\n" << endl;
    }

    string line, state, district, yearStr, tempRange, rainfall, humidity;
    map<string, vector<TempRecord>> data;
    map<string, string> districtStates;

    
    getline(file, line); 
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, state, ',');
        getline(ss, district, ',');
        getline(ss, yearStr, ',');
        getline(ss, tempRange, ',');
        getline(ss, rainfall, ',');
        getline(ss, humidity, ',');

        int year = stoi(yearStr);
        double avgTemp = getAvgTemp(tempRange);
        data[district].push_back({year, avgTemp});
        districtStates[district] = state;
    }
    file.close();

    
    cout << "Analysis complete! Here are the significant temperature changes:\n\n";
    
    
    outFile << "+----------------+----------------+--------+---------------+\n";
    outFile << "| State          | District       | Year   | Temp Change   |\n";
    outFile << "+----------------+----------------+--------+---------------+\n";
    
   
    vector<tuple<string, string, int, double>> allChanges;
    
    for (auto &entry : data) {
        string district = entry.first;
        vector<TempRecord> &records = entry.second;
        string state = districtStates[district];

        
        sort(records.begin(), records.end(), [](TempRecord a, TempRecord b) {
            return a.year < b.year;
        });

        
        for (size_t i = 1; i < records.size(); i++) {
            double change = records[i].avgTemp - records[i - 1].avgTemp;
            if (abs(change) >= 2.0) {
                
                allChanges.push_back(make_tuple(state, district, records[i].year, change));
            }
        }
    }
    
    
    sort(allChanges.begin(), allChanges.end());
    
    
    for (const auto &record : allChanges) {
        string state, district;
        int year;
        double change;
        tie(state, district, year, change) = record;
        
        
        outFile << "| " << left << setw(14) << state 
                << "| " << setw(14) << district 
                << "| " << setw(6) << year 
                << "| " << right << setw(11) << fixed << setprecision(2) << change << "°C |\n";
        

        cout << state << ", " << district << " " << year << " Change: " << fixed << setprecision(2) << change << "°C" << endl;
    }
    
   
    outFile << "+----------------+----------------+--------+---------------+\n";

    outFile.close();

        } else if (menu == 'N' || menu == 'n') {
            system("cls");
            break;  
        }
    } while (menu == 'Y' || menu == 'y');

    system("cls");
} 

