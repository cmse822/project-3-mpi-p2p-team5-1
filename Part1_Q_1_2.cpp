//////////////////////////////////
// Team 5, Project 3: Part 1, 2 //
//////////////////////////////////

#include <mpi.h>
#include <iostream>
#include <cmath>

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
    for (int size = 2; size <= 4096; size *= 2) {
        char* buffer = new char[size];
        double start_time, end_time;
        start_time = MPI_Wtime();
        for (int i = 0; i < PING_PONG_LIMIT; i++) {
            if (world_rank == 0) {
                MPI_Send(buffer, size, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
                MPI_Recv(buffer, size, MPI_BYTE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            } else if (world_rank == 1) {
                MPI_Recv(buffer, size, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(buffer, size, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
            }
        }
        end_time = MPI_Wtime();
        if (world_rank == 0) {
            std::cout << "Message size: " << size << " bytes, "
                      << "Time: " << (end_time - start_time) << " seconds" << std::endl;
        }
        delete[] buffer;
    }
    MPI_Finalize();
    return 0;
}

// Here we allocate the task on two different nodes:
// salloc -N 2 --ntasks-per-node=1 --time=00:10:00
