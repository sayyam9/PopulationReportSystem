# Use an official GCC image as the base image
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /app

# Copy the necessary project files into the container
COPY . /app

# Install MySQL client library and development files
RUN apt-get update && apt-get install -y \
    default-libmysqlclient-dev \
    && rm -rf /var/lib/apt/lists/*

# Compile the C++ code into an executable named 'population_report'
RUN g++ -o population_report main.cpp -L/usr/lib/x86_64-linux-gnu -lmysqlclient

# Set the default command to run when the container starts
CMD ["./population_report"]
