#include <mpi.h>
#include <iostream>
#include <vector>
#include <cmath>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Message sizes: 2 to 4 kilobts
    std::vector<int> message_sizes = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};

    for (int size : message_sizes) {
        char* send_buf = new char[size];
        char* recv_buf = new char[size];
        double start_time, total_time;

        for (int i = 0; i < size; ++i) {
            send_buf[i] = (char)((i + world_rank) % 256); // Arbitrary
        }

        MPI_Barrier(MPI_COMM_WORLD); 
        start_time = MPI_Wtime();

        int send_to = (world_rank + 1) % world_size;
        int recv_from = (world_rank - 1 + world_size) % world_size;

        for (int i = 0; i < world_size; ++i) {
            MPI_Sendrecv(send_buf, size, MPI_BYTE, send_to, 0,
                         recv_buf, size, MPI_BYTE, recv_from, 0,
                         MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        }

        MPI_Barrier(MPI_COMM_WORLD);
        total_time = MPI_Wtime() - start_time;

        if (world_rank == 0) {
            std::cout << "Message size: " << size << " bytes, Total time: " << total_time << " seconds" << std::endl;
        }

        delete[] send_buf;
        delete[] recv_buf;
    }

    MPI_Finalize();
    return 0;
}

// mpic++ Part3_Q2.cpp -o shift_q2
// mpiexec -n 4 ./shift_q2 

// Message size: 2 bytes, Total time: 2.93367e-05 seconds
// Message size: 4 bytes, Total time: 7.75978e-06 seconds
// Message size: 8 bytes, Total time: 2.56374e-05 seconds
// Message size: 16 bytes, Total time: 2.98582e-05 seconds
// Message size: 32 bytes, Total time: 7.57352e-06 seconds
// Message size: 64 bytes, Total time: 6.34789e-06 seconds
// Message size: 128 bytes, Total time: 1.09263e-05 seconds
// Message size: 256 bytes, Total time: 2.57157e-05 seconds
// Message size: 512 bytes, Total time: 2.09212e-05 seconds
// Message size: 1024 bytes, Total time: 2.32905e-05 seconds
// Message size: 2048 bytes, Total time: 9.46969e-06 seconds
// Message size: 4096 bytes, Total time: 6.09681e-05 seconds