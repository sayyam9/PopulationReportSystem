  PopulationReportSystem is a C++ and MySQL application for generating detailed population reports. Users can access and analyze data at various levels, including countries and cities, organized by size. It provides statistics on language speakers and population distributions.
# PopulationReportSystem

PopulationReportSystem is a C++ and MySQL application for generating detailed population reports. Users can access and analyze data at various levels, including countries and cities, organized by size. It provides statistics on language speakers and population distributions.

## Getting Started

1. Clone the repository.
2. Configure the database connection in `config.ini`.
3. Build the project using CMake.
4. Run the executable to generate reports.

## Dependencies

- C++11 or higher
- MySQL
- CMake
- Docker (optional, for containerized setup)

## Usage

```bash
mkdir build
cd build
cmake ..
make
./PopulationReportSystem
