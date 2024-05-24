//
//#include <iostream>
//#include <mysql/mysql.h>
//
//using namespace std;
//
//// Function prototypes
//void establishDatabaseConnection(MYSQL & mysqlInstance);
//void fetchCountriesByPopulation(MYSQL & mysqlInstance);
//void fetchCitiesByPopulation(MYSQL & mysqlInstance);
//void fetchCapitalCitiesByPopulation(MYSQL & mysqlInstance);
//void fetchTopNPopulatedCountries(MYSQL & mysqlInstance, int N);
//void fetchTopNPopulatedCities(MYSQL & mysqlInstance, int N);
//void fetchTopNPopulatedCapitalCities(MYSQL & mysqlInstance, int N);
//void createPopulationBreakdownReport(MYSQL & mysqlInstance);
//void createLanguageSpeakersStatistics(MYSQL & mysqlInstance);
//
//int main() {
//    MYSQL mysqlInstance;
//    establishDatabaseConnection(mysqlInstance);
//
//    int choice;
//    do {
//        cout << "\n\n*** Population Report System ***\n";
//        cout << "1. Fetch Countries by Population\n";
//        cout << "2. Fetch Cities by Population\n";
//        cout << "3. Fetch Capital Cities by Population\n";
//        cout << "4. Fetch Top N Populated Countries\n";
//        cout << "5. Fetch Top N Populated Cities\n";
//        cout << "6. Fetch Top N Populated Capital Cities\n";
//        cout << "7. Create Population Breakdown Report\n";
//        cout << "8. Create Language Speakers Statistics\n";
//        cout << "9. Exit\n";
//        cout << "Enter your choice: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1:
//            fetchCountriesByPopulation(mysqlInstance);
//            break;
//        case 2:
//            fetchCitiesByPopulation(mysqlInstance);
//            break;
//        case 3:
//            fetchCapitalCitiesByPopulation(mysqlInstance);
//            break;
//        case 4:
//            int N;
//            cout << "Enter N: ";
//            cin >> N;
//            fetchTopNPopulatedCountries(mysqlInstance, N);
//            break;
//        case 5:
//            cout << "Enter N: ";
//            cin >> N;
//            fetchTopNPopulatedCities(mysqlInstance, N);
//            break;
//        case 6:
//            cout << "Enter N: ";
//            cin >> N;
//            fetchTopNPopulatedCapitalCities(mysqlInstance, N);
//            break;
//        case 7:
//            createPopulationBreakdownReport(mysqlInstance);
//            break;
//        case 8:
//            createLanguageSpeakersStatistics(mysqlInstance);
//            break;
//        case 9:
//            cout << "Exiting the system...\n";
//            break;
//        default:
//            cout << "Invalid choice! Please choose a valid option.\n";
//        }
//    } while (choice != 9);
//
//    mysql_close(&mysqlInstance);
//    return 0;
//}
//
//void establishDatabaseConnection(MYSQL & mysqlInstance) 
//{
//    mysql_init(&mysqlInstance);
//    if (!mysql_real_connect(&mysqlInstance, "localhost", "your_username", "your_password", "world", 0, nullptr, 0)) {
//        cerr << "Error: Unable to connect to database. Exiting..." << endl;
//        exit(1);
//    }
//    cout << "Database connection established successfully!" << endl;
//}
//
//void fetchCountriesByPopulation(MYSQL & mysqlInstance) {
//    if (mysql_query(&mysqlInstance, "SELECT Name, Population FROM country ORDER BY Population DESC")) {
//        cerr << "Error: " << mysql_error(&mysqlInstance) << endl;
//        return;
//    }
//
//    MYSQL_RES* result = mysql_store_result(&mysqlInstance);
//    if (result) {
//        MYSQL_ROW row;
//        while ((row = mysql_fetch_row(result))) {
//            cout << "Country: " << row[0] << ", Population: " << row[1] << endl;
//        }
//        mysql_free_result(result);
//    }
//    else {
//        cerr << "Error: " << mysql_error(&mysqlInstance) << endl;
//    }
//}
//
//void fetchCitiesByPopulation(MYSQL & mysqlInstance) {
//    if (mysql_query(&mysqlInstance, "SELECT Name, Population FROM city ORDER BY Population DESC")) {
//        cerr << "Error: " << mysql_error(&mysqlInstance) << endl;
//        return;
//    }
//
//    MYSQL_RES* result = mysql_store_result(&mysqlInstance);
//    if (result) {
//        MYSQL_ROW row;
//        while ((row = mysql_fetch_row(result))) {
//            cout << "City: " << row[0] << ", Population: " << row[1] << endl;
//        }
//        mysql_free_result(result);
//    }
//    else {
//        cerr << "Error: " << mysql_error(&mysqlInstance) << endl;
//    }
//}
//
//void fetchCapitalCitiesByPopulation(MYSQL & mysqlInstance) {
//    if (mysql_query(&mysqlInstance, "SELECT city.Name, city.Population FROM city JOIN country ON city.ID = country.Capital ORDER BY city.Population DESC")) {
//        cerr << "Error: " << mysql_error(&mysqlInstance) << endl;
//        return;
//    }
//
//    MYSQL_RES* result = mysql_store_result(&mysqlInstance);
//    if (result) {
//        MYSQL_ROW row;
//        while ((row = mysql_fetch_row(result))) {
//            cout << "Capital City: " << row[0] << ", Population: " << row[1] << endl;
//        }
//        mysql_free_result(result);
//    }
//    else {
//        cerr << "Error: " << mysql_error(&mysqlInstance) << endl;
//    }
//}
//
//void fetchTopNPopulatedCountries(MYSQL & mysqlInstance, int N) {
//    string query = "SELECT Name, Population FROM country ORDER BY Population DESC LIMIT " + to_string(N);
//    if (mysql_query(&mysqlInstance, query.c_str())) {
//        cerr << "Error: " << mysql_error(&mysqlInstance) << endl;
//        return;
//    }
//
//    MYSQL_RES* result = mysql_store_result(&mysqlInstance);
//    if (result) {
//        MYSQL_ROW row;
//        while ((row = mysql_fetch_row(result))) {
//            cout << "Country: " << row[0] << ", Population: " << row[1] << endl;
//        }
//        mysql_free_result(result);
//    }
//    else {
//        cerr << "Error: " << mysql_error(&mysqlInstance) << endl;
//    }
//}
//
//void fetchTopNPopulatedCities(MYSQL & mysqlInstance, int N) {
//    string query = "SELECT Name, Population FROM city ORDER BY Population DESC LIMIT " + to_string(N);
//    if (mysql_query(&mysqlInstance, query.c_str())) {
//        cerr << "Error: " << mysql_error(&mysqlInstance) << endl;
//        return;
//    }
//
//    MYSQL_RES* result = mysql_store_result(&mysqlInstance);
//    if (result) {
//        MYSQL_ROW row;
//        while ((row = mysql_fetch_row(result))) {
//            cout << "City: " << row[0] << ", Population: " << row[1] << endl;
//        }
//        mysql_free_result(result);
//    }
//    else {
//        cerr << "Error: " << mysql_error(&mysqlInstance) << endl;
//    }
//}
//void fetchTopNPopulatedCapitalCities(MYSQL& mysqlInstance, int N) {
//    string query = "SELECT city.Name, city.Population FROM city JOIN country ON city.ID = country.Capital ORDER BY city.Population DESC LIMIT " + to_string(N);
//    if (mysql_query(&mysqlInstance, query.c_str())) {
//        cerr << "Error: " << mysql_error(&mysqlInstance) << endl;
//        return;
//    }
//
//    MYSQL_RES* result = mysql_store_result(&mysqlInstance);
//    if (result) {
//        MYSQL_ROW row;
//        while ((row = mysql_fetch_row(result))) {
//            cout << "Capital City: " << row[0] << ", Population: " << row[1] << endl;
//        }
//        mysql_free_result(result);
//    }
//    else {
//        cerr << "Error: " << mysql_error(&mysqlInstance) << endl;
//    }
//}
//
//void createPopulationBreakdownReport(MYSQL& mysqlInstance) {
//    string query = "SELECT Continent, SUM(Population) AS TotalPopulation FROM country GROUP BY Continent";
//    if (mysql_query(&mysqlInstance, query.c_str())) {
//        cerr << "Error: " << mysql_error(&mysqlInstance) << endl;
//        return;
//    }
//
//    MYSQL_RES* result = mysql_store_result(&mysqlInstance);
//    if (result) {
//        cout << "Population Breakdown by Continent:\n";
//        MYSQL_ROW row;
//        while ((row = mysql_fetch_row(result))) {
//            cout << "Continent: " << row[0] << ", Total Population: " << row[1] << endl;
//        }
//        mysql_free_result(result);
//    }
//    else {
//        cerr << "Error: " << mysql_error(&mysqlInstance) << endl;
//    }
//}
//
//void createLanguageSpeakersStatistics(MYSQL& mysqlInstance) {
//    string query = "SELECT Language, SUM(Population) AS TotalSpeakers FROM countrylanguage GROUP BY Language";
//    if (mysql_query(&mysqlInstance, query.c_str())) {
//        cerr << "Error: " << mysql_error(&mysqlInstance) << endl;
//        return;
//    }
//
//    MYSQL_RES* result = mysql_store_result(&mysqlInstance);
//    if (result) {
//        cout << "Language Speakers Statistics:\n";
//        MYSQL_ROW row;
//        while ((row = mysql_fetch_row(result))) {
//            cout << "Language: " << row[0] << ", Total Speakers: " << row[1] << endl;
//        }
//        mysql_free_result(result);
//    }
//    else {
//        cerr << "Error: " << mysql_error(&mysqlInstance) << endl;
//    }
//}
//
