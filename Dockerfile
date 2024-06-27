# Use the official gcc image from the Docker Hub
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /usr/src/app

# Copy the current directory contents into the container at /usr/src/app
COPY BruteForce.cpp /usr/src/app/
COPY S-P-G_algorithm.cpp /usr/src/app/

# Compile the C++ program
RUN g++ -o myapp BruteForce.cpp S-P-G_algorithm.cpp

# Command to run the executable
CMD ["./myapp"]