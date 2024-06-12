using System;
using System.Collections.Generic;
using MySql.Data.MySqlClient;

class Program
{
    static MySqlConnection connection;

    static void Main()
    {
        connection = EstablishDatabaseConnection();

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
                    FetchCountriesByPopulation();
                    break;
                case 2:
                    FetchCitiesByPopulation();
                    break;
                case 3:
                    FetchCapitalCitiesByPopulation();
                    break;
                case 4:
                    Console.Write("Enter N: ");
                    int N = Convert.ToInt32(Console.ReadLine());
                    FetchTopNPopulatedCountries(N);
                    break;
                case 5:
                    Console.Write("Enter N: ");
                    N = Convert.ToInt32(Console.ReadLine());
                    FetchTopNPopulatedCities(N);
                    break;
                case 6:
                    Console.Write("Enter N: ");
                    N = Convert.ToInt32(Console.ReadLine());
                    FetchTopNPopulatedCapitalCities(N);
                    break;
                case 7:
                    CreatePopulationBreakdownReport();
                    break;
                case 8:
                    CreateLanguageSpeakersStatistics();
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

    static void FetchCountriesByPopulation()
    {
        string query = "SELECT Name, Population FROM country ORDER BY Population DESC";
        ExecuteQuery(query);
    }

    static void FetchCitiesByPopulation()
    {
        string query = "SELECT Name, Population FROM city ORDER BY Population DESC";
        ExecuteQuery(query);
    }

    static void FetchCapitalCitiesByPopulation()
    {
        string query = "SELECT city.Name, city.Population FROM city JOIN country ON city.ID = country.Capital ORDER BY city.Population DESC";
        ExecuteQuery(query);
    }

    static void FetchTopNPopulatedCountries(int N)
    {
        string query = $"SELECT Name, Population FROM country ORDER BY Population DESC LIMIT {N}";
        ExecuteQuery(query);
    }

    static void FetchTopNPopulatedCities(int N)
    {
        string query = $"SELECT Name, Population FROM city ORDER BY Population DESC LIMIT {N}";
        ExecuteQuery(query);
    }

    static void FetchTopNPopulatedCapitalCities(int N)
    {
        string query = $"SELECT city.Name, city.Population FROM city JOIN country ON city.ID = country.Capital ORDER BY city.Population DESC LIMIT {N}";
        ExecuteQuery(query);
    }

    static void CreatePopulationBreakdownReport()
    {
        string query = "SELECT Continent, SUM(Population) AS TotalPopulation FROM country GROUP BY Continent";
        ExecuteQuery(query);
    }

    static void CreateLanguageSpeakersStatistics()
    {
        // Dictionary to store language populations
        Dictionary<string, int> languagePopulations = new Dictionary<string, int>();

        // Initialize language populations
        languagePopulations["Chinese"] = 0;
        languagePopulations["English"] = 0;
        languagePopulations["Hindi"] = 0;
        languagePopulations["Spanish"] = 0;
        languagePopulations["Arabic"] = 0;

        // Query to fetch language populations from the database
        string query = "SELECT Language, SUM(Population) AS TotalSpeakers FROM countrylanguage GROUP BY Language";

        // Execute the query
        MySqlCommand command = new MySqlCommand(query, connection);

        // Handle the exception if any
        try
        {
            // Open the reader to fetch data
            using (MySqlDataReader reader = command.ExecuteReader())
            {
                // Check if there is data to read
                if (reader.HasRows)
                {
                    // Iterate through the data
                    while (reader.Read())
                    {
                        // Get language and total speakers from the reader
                        string language = reader.GetString("Language");
                        int totalSpeakers = reader.GetInt32("TotalSpeakers");

                        // Update the language population dictionary
                        if (languagePopulations.ContainsKey(language))
                        {
                            languagePopulations[language] = totalSpeakers;
                        }
                    }
                }
                else
                {
                    Console.WriteLine("No language data found.");
                }
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error fetching language data: {ex.Message}");
            return;
        }

        // Display the language speakers statistics
        Console.WriteLine("Language Speakers Statistics:");
        foreach (var pair in languagePopulations.OrderByDescending(pair => pair.Value))
        {
            double percentage = (double)pair.Value / GetWorldPopulation() * 100;
            Console.WriteLine($"{pair.Key}: {pair.Value} (Percentage: {percentage:F2}%)");
        }
    }

    static void ExecuteQuery(string query)
    {
        MySqlCommand command = new MySqlCommand(query, connection);
        MySqlDataReader reader = command.ExecuteReader();

        while (reader.Read())
        {
            Console.WriteLine($"{reader[0]}: {reader[1]}");
        }

        reader.Close();
    }

    static int GetWorldPopulation()
    {
        // Query to fetch world population from the database
        string query = "SELECT SUM(Population) FROM country";

        // Execute the query and get the result
        MySqlCommand command = new MySqlCommand(query, connection);
        object result = command.ExecuteScalar();

        // Parse the result to integer
        int population = 0;
        if (result != null && result != DBNull.Value)
        {
            int.TryParse(result.ToString(), out population);
        }

        return population;
    }
}
