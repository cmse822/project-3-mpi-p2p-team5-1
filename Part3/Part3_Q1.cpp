#include <mpi.h>
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    const int random_message_size = 5; 
    int* message = new int[random_message_size];
    for (int i = 0; i < random_message_size; i++) {
        message[i] = world_rank * random_message_size + i; 
    }

    int* recv_buffer = new int[random_message_size];

    int send_to = (world_rank + 1) % world_size;
    int recv_from = (world_rank - 1 + world_size) % world_size;

    MPI_Sendrecv(message, random_message_size, MPI_INT, send_to, 0,
                 recv_buffer, random_message_size, MPI_INT, recv_from, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);


    for (int rank = 0; rank < world_size; ++rank) {
        MPI_Barrier(MPI_COMM_WORLD); 
        if (rank == world_rank) {
            std::cout << "Process " << world_rank << " received data from process " << recv_from << ": ";
            for (int i = 0; i < random_message_size; i++) {
                std::cout << recv_buffer[i] << " ";
            }
            std::cout << std::endl;
        }
        MPI_Barrier(MPI_COMM_WORLD); 
    }

    delete[] message;
    delete[] recv_buffer;

    MPI_Finalize();
    return 0;
}


// mpic++ Part3_Q1.cpp -o shift_q1
// mpiexec -n 6 ./shift_q1
// Process 0 received data from process 5: 25 26 27 28 29 
// Process 1 received data from process 0: 0 1 2 3 4 
// Process 2 received data from process 1: 5 6 7 8 9 
// Process 3 received data from process 2: 10 11 12 13 14 
// Process 4 received data from process 3: 15 16 17 18 19 
// Process 5 received data from process 4: 20 21 22 23 24 