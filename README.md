# Malaysian Meteorological Department Weather Analysis

A C++ console application that reads weather data from a CSV/text file and performs five types of meteorological analysis for Malaysian states and districts.

---

## Authors

| Name | Student ID |
|------|------------|
| Muhammad Luqman Hakim bin Mohammad 'Asri | 24000087 |
| Muhammad Faizzuddin bin Mohd Nazli | 24000085 |
| Namunesswaran A/L Siva Perumal | 24000043 |
| Ivan Jerard Gnanakannu | 24008940 |

---

## Features

### `WeatherReport.cpp`
| Option | Feature | Output File |
|--------|---------|-------------|
| A | **Temperature Trends** – Classifies districts as high (>30°C) or low temperature | `High_Temp.txt`, `Low_Temp.txt` |
| B | **Rainfall Analysis** – Calculates total and average rainfall per district; flags districts above 1000mm | `Rainfall_Analysis.txt` |
| C | **Climate Change Impact** – Detects year-over-year temperature changes ≥ 2°C | `Climate_Change_Impact.txt` |

### `WeatherReportAdditional.cpp`
| Option | Feature | Output File |
|--------|---------|-------------|
| D | **Heatwaves Analysis** – Flags districts with average temp ≥ 30°C (Heatwave) or ≥ 35°C (Extreme Heatwave) | `Heatwave_Report.txt` |
| E | **Drought Analysis** – Uses percentile thresholds on rainfall & humidity to classify Mild / Moderate / Severe drought | `Drought_Report.txt` |

---

##  Project Structure

```
├── WeatherReport.cpp            # Main program (options A, B, C)
├── WeatherReportAdditional.cpp  # Additional analyses (options D, E)
├── Weather_Statistics.txt       # Input data file (not included – see below)
└── README.md
```

---

##  Input File Format

The program expects a file named `Weather_Statistics.txt` with the following CSV structure:

```
State,District,Year,Temperature,Rainfall,Humidity
Selangor,Petaling,2020,28-32,1200,80
...
```

| Column | Type | Description |
|--------|------|-------------|
| State | String | Malaysian state name |
| District | String | District name |
| Year | Integer | Year of record |
| Temperature | String | Range format e.g. `28-32` (°C) |
| Rainfall | Integer | Rainfall in mm |
| Humidity | Float | Humidity percentage |

> **Note:** The average temperature is computed as `(low + high) / 2` from the range string.

---

##  Prerequisites

- A C++ compiler supporting **C++11** or later (e.g. g++, MSVC, MinGW)
- Windows OS (the code uses `system("cls")` for screen clearing)

---

##  Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/your-username/weather-analysis.git
cd weather-analysis
```

### 2. Update the input file path

In both `.cpp` files, update the hardcoded path to point to your `Weather_Statistics.txt`:

```cpp
// WeatherReport.cpp & WeatherReportAdditional.cpp
ifstream inputFile("C:/Users/USER/Downloads/Weather_Statistics.txt");
//                  ^^^ Change this to your actual file path
```

### 3. Compile

**WeatherReport.cpp**
```bash
g++ -o WeatherReport WeatherReport.cpp
```

**WeatherReportAdditional.cpp**
```bash
g++ -o WeatherReportAdditional WeatherReportAdditional.cpp
```

### 4. Run

```bash
./WeatherReport
./WeatherReportAdditional
```

---

##  Usage

Both programs present an interactive text menu:

```
---------[Welcome to Malaysian Meteorological Department Weather Analysis]---------

[Choose any of the available options]

Input 'A' to display Temperature Trends
Input 'B' to display Rainfall Analysis
Input 'C' to display Climate Change Impact
Option (Input X To Exit Program):
```

Follow the on-screen prompts (`Y` to proceed, `N` to go back, `X` to exit).

---
