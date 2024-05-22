
#include <iostream>
#include <mysql/mysql.h>

using namespace std;

// Function prototypes
void establishDatabaseConnection(MYSQL& mysqlInstance);
void fetchCountriesByPopulation(MYSQL& mysqlInstance);
void fetchCitiesByPopulation(MYSQL& mysqlInstance);
void fetchCapitalCitiesByPopulation(MYSQL& mysqlInstance);
void fetchTopNPopulatedCountries(MYSQL& mysqlInstance, int N);
void fetchTopNPopulatedCities(MYSQL& mysqlInstance, int N);
void fetchTopNPopulatedCapitalCities(MYSQL& mysqlInstance, int N);
void createPopulationBreakdownReport(MYSQL& mysqlInstance);
void createLanguageSpeakersStatistics(MYSQL& mysqlInstance);

int main() {
    MYSQL mysqlInstance;
    establishDatabaseConnection(mysqlInstance);

    int choice;
    do {
        cout << "\n\n*** Population Report System ***\n";
        cout << "1. Fetch Countries by Population\n";
        cout << "2. Fetch Cities by Population\n";
        cout << "3. Fetch Capital Cities by Population\n";
        cout << "4. Fetch Top N Populated Countries\n";
        cout << "5. Fetch Top N Populated Cities\n";
        cout << "6. Fetch Top N Populated Capital Cities\n";
        cout << "7. Create Population Breakdown Report\n";
        cout << "8. Create Language Speakers Statistics\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            fetchCountriesByPopulation(mysqlInstance);
            break;
        case 2:
            fetchCitiesByPopulation(mysqlInstance);
            break;
        case 3:
            fetchCapitalCitiesByPopulation(mysqlInstance);
            break;
        case 4:
            int N;
            cout << "Enter N: ";
            cin >> N;
            fetchTopNPopulatedCountries(mysqlInstance, N);
            break;
        case 5:
            cout << "Enter N: ";
            cin >> N;
            fetchTopNPopulatedCities(mysqlInstance, N);
            break;
        case 6:
            cout << "Enter N: ";
            cin >> N;
            fetchTopNPopulatedCapitalCities(mysqlInstance, N);
            break;
        case 7:
            createPopulationBreakdownReport(mysqlInstance);
            break;
        case 8:
            createLanguageSpeakersStatistics(mysqlInstance);
            break;
        case 9:
            cout << "Exiting the system...\n";
            break;
        default:
            cout << "Invalid choice! Please choose a valid option.\n";
        }
    } while (choice != 9);

    mysql_close(&mysqlInstance);
    return 0;
}
