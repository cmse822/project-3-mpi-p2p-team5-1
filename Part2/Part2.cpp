// Part 2 for Q's 1-4 //

#include <mpi.h>
#include <iostream>
#include <cmath>
#include <fstream>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    if (world_size < 2) {
        std::cerr << "World size must be at least two for ping-pong." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    const int PING_PONG_LIMIT = 100;
    std::ofstream myfile;
    myfile.open("output_q2.csv");
    // Updated to include the Total Data Sent and Received header
    myfile << "Message Size (bytes),Time (seconds),Total Data Sent and Received (bytes)\n";
    for (int size = 2; size <= 4096; size *= 2) {
        char* buffer = new char[size];
        double start_time, end_time;
        MPI_Request request;
        MPI_Status status;
        
        start_time = MPI_Wtime();
        // Initialize total data exchanged to 0 at the start of each size iteration
        unsigned long long total_data_exchanged = 0;
        for (int i = 0; i < PING_PONG_LIMIT; i++) {
            if (world_rank == 0) {
                MPI_Isend(buffer, size, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &request);
                MPI_Wait(&request, &status); 
                MPI_Irecv(buffer, size, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &request);
                MPI_Wait(&request, &status);
                // Each send and receive counts towards total data exchanged
                total_data_exchanged += size * 2; // Times 2 because send and receive
            } else if (world_rank == 1) {
                MPI_Irecv(buffer, size, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &request);
                MPI_Wait(&request, &status); 
                MPI_Isend(buffer, size, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &request);
                MPI_Wait(&request, &status); 
                // Note: You might only want to track the data in one rank to avoid double counting
            }
        }
        end_time = MPI_Wtime();
        if (world_rank == 0) {
            std::cout << "Non-blocking. Message size: " << size << " bytes, "
                      << "Time: " << (end_time - start_time) << " seconds, "
                      // Output the total data exchanged
                      << "Total Data: " << total_data_exchanged << " bytes" << std::endl;
            // Write the new data point to the file
            myfile << size << "," << (end_time - start_time) << "," << total_data_exchanged << "\n";
        }
        delete[] buffer;
    }
    myfile.close();
    MPI_Finalize();
    return 0;
}