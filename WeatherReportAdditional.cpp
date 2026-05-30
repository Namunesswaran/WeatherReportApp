// Muhammad Luqman Hakim bin Mohammad 'Asri [24000087]
// Muhammad Faizzuddin bin Mohd Nazli [24000085]
// Namunesswaran A/L Siva Perumal [24000043]
// Ivan Jerard Gnanakannu [24008940]

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct WeatherData {
    string state, district, year;
    double rainfall, humidity;
};

double getPercentile(vector<double> &values, double percentile) {
    if (values.empty()) return 0.0;
    size_t index = static_cast<size_t>(percentile * values.size());
    return values[index];
}

char menu;

// Get average temperature
float getAvgTemp(const string& range) {
    size_t pos = range.find('-');
    if (pos == string::npos) return -1;

    int low = stoi(range.substr(0, pos));
    int high = stoi(range.substr(pos + 1));

    return (low + high) / 2.0;
}

void menuOption();
void heatwaves();
void drought();

int main() {
    menuOption();
    return 0;
}

// Menu interface
void menuOption() {
    do {
        cout << "---------[Welcome to Malaysian Meteorological Department Weather Analysis]---------\n\n";
        cout << "[Choose any of the available options]\n\n";
        cout << "Input 'D' to display Heatwaves Analysis\n";
        cout << "Input 'E' to display Drought Analysis\n";
        cout << "Option (Input X To Exit Program): ";

        cin >> menu;
        cout << endl;

        switch (toupper(menu)) {
            case 'D': heatwaves(); break;
            case 'E': drought(); break;
            case 'X': cout << "Exited the Program.....\n"; break;
            default:
                system("cls");
                cout << "[Please Enter A Valid Menu Option!]\n\n";
        }
    } while (toupper(menu) != 'X');
}

// Heatwaves Analysis
void heatwaves() {
    cout << "Continue with Heatwaves Analysis (Y/N): ";
    cin >> menu;
    if (toupper(menu) == 'Y') {
        system("cls");
        do {
            cout << "-------[Heatwaves Analysis]-------\n\n";

            string inputFilePath = "C:/Users/USER/Downloads/Weather_Statistics.txt";
            string outputFilePath = "Heatwave_Report.txt";

            ifstream inputFile(inputFilePath);
            ofstream outputFile(outputFilePath);

            if (!inputFile.is_open()) {
                cout << "Error: Could not open file at path: " << inputFilePath << endl;
                return;
            }

            if (!outputFile.is_open()) {
                cout << "Error: Could not create file at path: " << outputFilePath << endl;
                return;
            }

            outputFile << "Heatwave Analysis Report\n";
            outputFile << "---------------------------------------\n";
            outputFile << "State, District, Year, Avg Temperature, Severity\n";

            string line;
            getline(inputFile, line); // Skip header

            while (getline(inputFile, line)) {
                string state, district, year, tempRange, rainfallStr, humidityStr;
                stringstream ss(line);

                getline(ss, state, ',');
                getline(ss, district, ',');
                getline(ss, year, ',');
                getline(ss, tempRange, ',');
                getline(ss, rainfallStr, ',');
                getline(ss, humidityStr, ',');

                double avgTemp = getAvgTemp(tempRange);
                string severity = "None";

                if (avgTemp >= 35) {
                    severity = "Extreme Heatwave";
                } else if (avgTemp >= 30) {
                    severity = "Heatwave";
                }

                if (severity != "None") {
                    outputFile << state << ", " << district << ", " << year << ", " << avgTemp << ", " << severity << endl;
                }
            }

            inputFile.close();
            outputFile.close();

            cout << "Heatwave analysis completed. Report saved to " << outputFilePath << ".\n";

            do {
                cout << "Do you want to Continue (Y/N): ";
                cin >> menu;
            } while (toupper(menu) != 'Y' && toupper(menu) != 'N');

        } while (toupper(menu) == 'Y');

        system("cls");
    }
    menuOption();
}

// Drought Analysis
void drought() {
    cout << "Continue with Drought Analysis (Y/N): ";
    cin >> menu;
    if (toupper(menu) == 'Y') {
        do {
            system("cls");
            cout << "-------[Drought Analysis]-------\n\n";

            string inputFilePath = "C:/Users/USER/Downloads/Weather_Statistics.txt";
            string outputFilePath = "Drought_Report.txt";
        
            ifstream inputFile(inputFilePath);
            ofstream outputFile(outputFilePath);
        
            if (!inputFile.is_open()) {
                cout << "Error: Could not open file at path: " << inputFilePath << endl;
                return;
            }
        
            if (!outputFile.is_open()) {
                cout << "Error: Could not create file at path: " << outputFilePath << endl;
                return;
            }
        
            vector<WeatherData> records;
            vector<double> rainfallValues, humidityValues;
            string line;
        
            // Read header line
            getline(inputFile, line);
        
            // Read data and store in vectors
            while (getline(inputFile, line)) {
                string state, district, year, tempRange, rainfallStr, humidityStr;
                stringstream ss(line);
        
                getline(ss, state, ',');
                getline(ss, district, ',');
                getline(ss, year, ',');
                getline(ss, tempRange, ',');
                getline(ss, rainfallStr, ',');
                getline(ss, humidityStr, ',');
        
                try {
                    double rainfall = stod(rainfallStr);
                    double humidity = stod(humidityStr);
        
                    records.push_back({state, district, year, rainfall, humidity});
                    rainfallValues.push_back(rainfall);
                    humidityValues.push_back(humidity);
                } catch (const invalid_argument &) {
                    cout << "Skipping invalid data: " << line << endl;
                }
            }
        
            inputFile.close();
        
            // Sort values for percentile calculation
            sort(rainfallValues.begin(), rainfallValues.end());
            sort(humidityValues.begin(), humidityValues.end());
        
            // Calculate thresholds
            double severeRainfall = getPercentile(rainfallValues, 0.25);  // Bottom 25%
            double moderateRainfall = getPercentile(rainfallValues, 0.50); // Bottom 50%
            double mildRainfall = getPercentile(rainfallValues, 0.75); // Bottom 75%
        
            double severeHumidity = getPercentile(humidityValues, 0.25);
            double moderateHumidity = getPercentile(humidityValues, 0.50);
            double mildHumidity = getPercentile(humidityValues, 0.75);
        
            // Write report header
            outputFile << "Drought Analysis Report\n";
            outputFile << "---------------------------------------\n";
            outputFile << "State, District, Year, Rainfall(mm), Humidity(%), Severity\n";
        
            // Assign severity based on calculated thresholds
            for (const auto &record : records) {
                string severity = "None";
        
                if (record.rainfall <= severeRainfall && record.humidity <= severeHumidity) {
                    severity = "Severe";
                } else if (record.rainfall <= moderateRainfall && record.humidity <= moderateHumidity) {
                    severity = "Moderate";
                } else if (record.rainfall <= mildRainfall && record.humidity <= mildHumidity) {
                    severity = "Mild";
                }
        
                if (severity != "None") {
                    outputFile << record.state << ", " << record.district << ", " 
                               << record.year << ", " << record.rainfall << ", " 
                               << record.humidity << ", " << severity << endl;
                }
            }
        
            outputFile.close();

            cout << "Drought analysis completed. Report saved to " << outputFilePath << "." << endl;

            do {
                cout << "Do you want to Continue (Y/N): ";
                cin >> menu;
            } while (toupper(menu) != 'Y' && toupper(menu) != 'N');

        } while (toupper(menu) == 'Y');

        system("cls");
    }
    menuOption();
}

