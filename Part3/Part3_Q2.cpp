#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int random_message_size = std::atoi(argv[1]); 
    int* message = new int[random_message_size / sizeof(int)];

    for (int i = 0; i < random_message_size / sizeof(int); i++) {
        message[i] = world_rank * random_message_size + i;
    }

    int* recv_buffer = new int[random_message_size / sizeof(int)];

    int send_to = (world_rank + 1) % world_size;
    int recv_from = (world_rank - 1 + world_size) % world_size;

    MPI_Sendrecv(message, random_message_size / sizeof(int), MPI_INT, send_to, 0,
                 recv_buffer, random_message_size / sizeof(int), MPI_INT, recv_from, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);


    delete[] message;
    delete[] recv_buffer;

    MPI_Finalize();
    return 0;
}
