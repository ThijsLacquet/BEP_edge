#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "Network/TCPServer.h"
#include "Network/UDP.h"
#include "Functions/FFT.h"
#include <complex.h>
#include "Functions/QAM.h"
#include "Other/mathextension.h"
#include <thread>
#include "Functions/OFDM.h"
#include <time.h>
#include <fftw3.h>

#define NUMBEROFREQUESTHANDLERS 8
#define DATASIZE 10240 //In bytes
#define FFTCMND 0
#define QAM16CMND 2
#define DEQAM16CMND 3
#define OFDM1024CMND 4
#define DEOFDM1024CMND 5

using namespace std;

struct buffer{
    struct timespec beginTime;
    char command;
    int length;
    int n;
    char data[DATASIZE];
};

struct response {
    struct timespec beginTime;
    int length;
    char data[DATASIZE];
};

void printcomplex(complex<short> *input, size_t n) {
    for (int i = 0; i < n; i++) {
        printf("%hi + %hij\n", input[i].real(), input[i].imag());
    }
}

void requestHandlerThread(__int16_t serverPort, bool *running, char* name, bool *complete) {
    printf("Starting thread %s at port %d\n", name, serverPort);

    QAM myQAM = QAM(16);
    FFT myFFT = FFT();
    //OFDM myOFDM = OFDM(1024);

    TCPServer myTCPServer = TCPServer(serverPort);
    struct buffer *buffer = (struct buffer*) malloc (sizeof(struct buffer));
    struct response *response = (struct response*) malloc (sizeof(struct response));

    while (*running) {
        myTCPServer.listenAccept();
        printf("Accepted client at port %d\n", serverPort);

        while (myTCPServer.readTCP(buffer, sizeof(struct buffer)) > 0 && *running) {
            if (buffer != NULL) {
                if (buffer->data != NULL) {
                    //printf("Command: %c, id: %d\n", buffer->command, buffer->id);
                    response->beginTime = buffer->beginTime;

                    switch (buffer->command) {
                        case FFTCMND:
                            response->length = buffer->length;
                            complex<short> *buffer_segment;
                            complex<short> *response_segment;
                            int mode;
                            int n_abs;

                            if (buffer->n < 0) {
                                n_abs = -buffer->n;
                                mode = FFTW_BACKWARD;
                            } else {
                                n_abs = buffer->n;
                                mode = FFTW_FORWARD;
                            }

                            for (int i = 0; i < buffer->length / n_abs; i++) {
                                buffer_segment = &(((complex<short> *) buffer->data)[i * n_abs]);
                                response_segment = &(((complex<short> *) response->data)[i * n_abs]);
                                myFFT.compute(buffer_segment, response_segment, n_abs, mode);
                            }
                            break;
                        case QAM16CMND:
                            response->length = buffer->length;
                            myQAM.compute_QAM((short *) buffer->data, (complex<short> *) response->data, buffer->length);
                            break;
                        case DEQAM16CMND:
                            response->length = buffer->length;
                            myQAM.compute_deQAM((complex<short> *) buffer->data, (short *) response->data, buffer->length);
                            break;

                        default:
                            printf("Wrong command: %c\n", buffer->command);
                    }
                    if (myTCPServer.sendTCP(response, sizeof(struct response)) == -1) {
                        if (errno == 104) { //Connection reset by peer
                            printf("Connection reset by peer at port %d\n", serverPort);
                            break;
                        } else {
                            printf("An error has occured at %d while sending the TCP message, closing connection: %d\n", serverPort, errno);
                        }
                    }
                }
            }
        }
        printf("Disconnected client\n");
    }

    //Free memory
    free(buffer);
    free(response);
    *complete = true;
    printf("Thread %s terminated\n", name);
}

int main() {
    bool running = true;

    //Allocate memory for threads
    thread *requestHandlers = (thread *) malloc (sizeof(thread) * NUMBEROFREQUESTHANDLERS);
    char **name = (char **) malloc (sizeof(char*) * NUMBEROFREQUESTHANDLERS);
    bool *complete = (bool *) malloc (sizeof(bool) * NUMBEROFREQUESTHANDLERS);

    //Start threads
    for (int i = 0; i < NUMBEROFREQUESTHANDLERS; i++) {
        //Allocate and initialize memory for specific thread
        name[i] = (char*) malloc (sizeof(char) * 15);
        complete[i] = false;

        //Create name of thread
        sprintf(name[i], "Bep_edge_th%d", i);

        //Create thread
        requestHandlers[i] = thread(requestHandlerThread, 6200 + i, &running, name[i], &(complete[i]));
        pthread_setname_np(requestHandlers[i].native_handle(), name[i]);
    }

    char input[100];

    while (running) {
        scanf("%s", input);
        if (strcmp(input, "stop\n")) {
            printf("Stopping\n");
            running = false;
            sleep(1);
        }
    }

    //Wait till are threads are stopped
    for (int i = 0; i < NUMBEROFREQUESTHANDLERS; i++) {
        if (complete[i] == false) { //Reset counter if thread did not stop
            i = 0;
        } else  if (i == NUMBEROFREQUESTHANDLERS) { //All threads are stopped
            break;
        }
    }

    //Free memory
    for (int i = 0; i < NUMBEROFREQUESTHANDLERS; i++) {
        free(name[i]);
    }
    free(name);
    free(complete);

    printf("All threads have terminated\n");

    return 0;
}