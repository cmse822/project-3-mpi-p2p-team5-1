#include <mpi.h>
#include <iostream>
#include <unistd.h> // For sleep

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int message = world_rank; 
    int right = (world_rank + 1) % world_size;
    int left = (world_rank - 1 + world_size) % world_size;

    for (int step = 0; step < world_size; ++step) {
        int recv_message;
        // send message to the right and receives from the left.
        MPI_Sendrecv(&message, 1, MPI_INT, right, 0,
                     &recv_message, 1, MPI_INT, left, 0,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        message = recv_message;

        // Synchronize
        MPI_Barrier(MPI_COMM_WORLD);
        if (world_rank == 0) {
            std::cout << "Step " << step << ", Process " << world_rank 
                      << " received message: " << message << std::endl;

            sleep(1); 
        }
        MPI_Barrier(MPI_COMM_WORLD);

        for (int i = 1; i < world_size; ++i) {
            if (world_rank == i) {
                std::cout << "Step " << step << ", Process " << world_rank 
                          << " received message: " << message << std::endl;
                sleep(1);
            }
            MPI_Barrier(MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}

// mpic++ Part3_Q1.cpp -o shift_q1
// mpiexec -n 4 ./shift_q1 

// Step 0, Process 0 received message: 3
// Step 0, Process 1 received message: 0
// Step 0, Process 2 received message: 1
// Step 0, Process 3 received message: 2
// Step 1, Process 0 received message: 2
// Step 1, Process 1 received message: 3
// Step 1, Process 2 received message: 0
// Step 1, Process 3 received message: 1
// Step 2, Process 0 received message: 1
// Step 2, Process 1 received message: 2
// Step 2, Process 2 received message: 3
// Step 2, Process 3 received message: 0
// Step 3, Process 0 received message: 0
// Step 3, Process 1 received message: 1
// Step 3, Process 2 received message: 2
// Step 3, Process 3 received message: 3