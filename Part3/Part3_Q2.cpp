#include <mpi.h>
#include <iostream>
#include <cmath> 
#include <fstream> 
using namespace std;

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int message_size = std::atoi(argv[1]); 
    int* message = new int[message_size / sizeof(int)]; 
    
    for (int i = 0; i < message_size / sizeof(int); i++) {
        message[i] = world_rank * message_size + i;
    }

    int* recv_buffer = new int[message_size / sizeof(int)];

    int send_to = (world_rank + 1) % world_size;
    int recv_from = (world_rank - 1 + world_size) % world_size;
    std::ofstream myfile;
    myfile.open("output.csv", ios::out | ios::app);
    double start_time, end_time;

    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();

    MPI_Sendrecv(message, message_size / sizeof(int), MPI_INT, send_to, 0,
                 recv_buffer, message_size / sizeof(int), MPI_INT, recv_from, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Barrier(MPI_COMM_WORLD);
    end_time = MPI_Wtime();

    if (world_rank == 0) {
            cout << "Message Size: " << message_size << " bytes" << endl;
            cout << "Processes: " << world_size << endl;
            // cout << "Processe number : " << world_rank << endl;
            cout << "Time Taken: " << (end_time - start_time) << " seconds" << endl;

            // double bandwidth = message_size / (end_time - start_time);
            // double latency = (end_time - start_time) / world_size;

            // cout << "Bandwidth: " << bandwidth << " bytes/second" << endl;
            // cout << "Latency: " << latency << " seconds" << endl;
            cout << endl;
            myfile << message_size << "," << world_size << "," << (end_time - start_time) << "\n";
        }

    delete[] message;
    delete[] recv_buffer;

    MPI_Finalize();
    return 0;
}
