//////////////////////////////////
// Team 5, Project 3: Part 1, 2 //
//////////////////////////////////

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
    myfile.open("output_q4.csv");
    myfile << "Message Size (bytes),Time (seconds),Total Data Sent and Received (bytes)\n";
    for (int size = 2; size <= 4096; size *= 2) {
        char* buffer = new char[size];
        double start_time, end_time;
        start_time = MPI_Wtime();
        // Initialize the total data variable
        unsigned long long total_data = 0;
        for (int i = 0; i < PING_PONG_LIMIT; i++) {
            if (world_rank == 0) {
                MPI_Send(buffer, size, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
                MPI_Recv(buffer, size, MPI_BYTE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                // Update total data for send and receive
                total_data += size * 2;
            } else if (world_rank == 1) {
                MPI_Recv(buffer, size, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(buffer, size, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
                // Update total data for send and receive
                total_data += size * 2;
            }
        }
        end_time = MPI_Wtime();
        if (world_rank == 0) {
            std::cout << "Message size: " << size << " bytes, "
                      << "Time: " << (end_time - start_time) << " seconds, "
                      << "Total Data: " << total_data << " bytes" << std::endl;
            myfile << size << "," << (end_time - start_time) << "," << total_data << "\n";
        }
        delete[] buffer;
    }
    myfile.close();
    MPI_Finalize();
    return 0;
}
// Here we allocate the task on two different nodes:
// salloc -N 1 --ntasks-per-node=2 --time=00:10:00 commands for q2
// salloc -N 2 --ntasks-per-node=1 --time=00:10:00 commands for q4
// mpic++ Part1.cpp -o part1.o
// srun mpiexec -n 2 ./part1.o
