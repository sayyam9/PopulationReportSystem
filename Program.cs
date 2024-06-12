using System;
using MySql.Data.MySqlClient;

class Program
{
    static void Main()
    {
        MySqlConnection connection = EstablishDatabaseConnection();

        int choice;
        do
        {
            Console.WriteLine("\n\n*** Population Report System ***");
            Console.WriteLine("1. Fetch Countries by Population");
            Console.WriteLine("2. Fetch Cities by Population");
            Console.WriteLine("3. Fetch Capital Cities by Population");
            Console.WriteLine("4. Fetch Top N Populated Countries");
            Console.WriteLine("5. Fetch Top N Populated Cities");
            Console.WriteLine("6. Fetch Top N Populated Capital Cities");
            Console.WriteLine("7. Create Population Breakdown Report");
            Console.WriteLine("8. Create Language Speakers Statistics");
            Console.WriteLine("9. Exit");
            Console.Write("Enter your choice: ");
            choice = Convert.ToInt32(Console.ReadLine());

            switch (choice)
            {
                case 1:
                    FetchCountriesByPopulation(connection);
                    break;
                case 2:
                    FetchCitiesByPopulation(connection);
                    break;
                case 3:
                    FetchCapitalCitiesByPopulation(connection);
                    break;
                case 4:
                    Console.Write("Enter N: ");
                    int N = Convert.ToInt32(Console.ReadLine());
                    FetchTopNPopulatedCountries(connection, N);
                    break;
                case 5:
                    Console.Write("Enter N: ");
                    N = Convert.ToInt32(Console.ReadLine());
                    FetchTopNPopulatedCities(connection, N);
                    break;
                case 6:
                    Console.Write("Enter N: ");
                    N = Convert.ToInt32(Console.ReadLine());
                    FetchTopNPopulatedCapitalCities(connection, N);
                    break;
                case 7:
                    CreatePopulationBreakdownReport(connection);
                    break;
                case 8:
                    CreateLanguageSpeakersStatistics(connection);
                    break;
                case 9:
                    Console.WriteLine("Exiting the system...");
                    break;
                default:
                    Console.WriteLine("Invalid choice! Please choose a valid option.");
                    break;
            }
        } while (choice != 9);

        connection.Close();
    }

    static MySqlConnection EstablishDatabaseConnection()
    {
        string connectionString = "Server=localhost;Database=world;Uid=root;Pwd=1234;";
        MySqlConnection connection = new MySqlConnection(connectionString);

        try
        {
            connection.Open();
            Console.WriteLine("Database connection established successfully!");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: Unable to connect to database. Exiting... {ex.Message}");
            Environment.Exit(1);
        }

        return connection;
    }

    static void FetchCountriesByPopulation(MySqlConnection connection)
    {
        string query = "SELECT Name, Population FROM country ORDER BY Population DESC";
        ExecuteQuery(connection, query);
    }

    static void FetchCitiesByPopulation(MySqlConnection connection)
    {
        string query = "SELECT Name, Population FROM city ORDER BY Population DESC";
        ExecuteQuery(connection, query);
    }

    static void FetchCapitalCitiesByPopulation(MySqlConnection connection)
    {
        string query = "SELECT city.Name, city.Population FROM city JOIN country ON city.ID = country.Capital ORDER BY city.Population DESC";
        ExecuteQuery(connection, query);
    }

    static void FetchTopNPopulatedCountries(MySqlConnection connection, int N)
    {
        string query = $"SELECT Name, Population FROM country ORDER BY Population DESC LIMIT {N}";
        ExecuteQuery(connection, query);
    }

    static void FetchTopNPopulatedCities(MySqlConnection connection, int N)
    {
        string query = $"SELECT Name, Population FROM city ORDER BY Population DESC LIMIT {N}";
        ExecuteQuery(connection, query);
    }

    static void FetchTopNPopulatedCapitalCities(MySqlConnection connection, int N)
    {
        string query = $"SELECT city.Name, city.Population FROM city JOIN country ON city.ID = country.Capital ORDER BY city.Population DESC LIMIT {N}";
        ExecuteQuery(connection, query);
    }

    static void CreatePopulationBreakdownReport(MySqlConnection connection)
    {
        string query = "SELECT Continent, SUM(Population) AS TotalPopulation FROM country GROUP BY Continent";
        ExecuteQuery(connection, query);
    }

    static void CreateLanguageSpeakersStatistics(MySqlConnection connection)
    {
        string query = "SELECT Language, SUM(Population) AS TotalSpeakers FROM countrylanguage GROUP BY Language";
        ExecuteQuery(connection, query);
    }

    static void ExecuteQuery(MySqlConnection connection, string query)
    {
        MySqlCommand command = new MySqlCommand(query, connection);
        MySqlDataReader reader = command.ExecuteReader();

        while (reader.Read())
        {
            Console.WriteLine($"{reader[0]}: {reader[1]}");
        }

        reader.Close();
    }
}
