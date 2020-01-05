#include "ConnectCommand.h"
#include "InterpreterEx3.h"
#include "GlobalTables.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <algorithm>
#include <string.h>

static int socketClient;

/**
 * function name: execute
 * operation: execute data
 * input: vec of strs and index
 * @return int val
 */
int ConnectCommand::execute(vector<string> cmdTemp, int index) {
  InterpreterEx3 *iConnect = new InterpreterEx3();
  int endLine = enterKey(cmdTemp, index);
  string ip = cmdTemp.at(index + 1);
  int porti;
  try {
    //interpreting & calculating cmdTemp.at(index + 2)
    porti = (int) iConnect->calculateExpression(cmdTemp.at(index + 2));
    connectSocket(porti, ip);
    delete iConnect;
  } catch (const char *e) {
    if (iConnect != nullptr) {
      delete iConnect;
    }
    throw e;
  }
  return endLine;
}

/**
 * function name: connectSocket
 * operation: connect the socket
 * input: int (port) and str (ip)
 * @return void
 */
void ConnectCommand::connectSocket(int port, string ip) {
  /* Create a socket point */
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    cerr << "Error creating socket" << endl;
    exit(1);
  }
  sockaddr_in address;
  address.sin_family = AF_INET;
  ip.erase(std::remove(ip.begin(), ip.end(), '"'), ip.end()); //removing '"' from ip
  const char *ipButNotString = ip.c_str();
  address.sin_addr.s_addr = inet_addr(ipButNotString); //ip should be ip.c_str()
  address.sin_port = htons(port);
  int is_connected = connect(sockfd, (struct sockaddr *) &address, sizeof(address));
  if (is_connected == -1) {
    cerr << "Error connecting to server" << endl;
    exit(1);
  }
  socketClient = sockfd;
  newOrder = "";
  pthread_t t2;
  pthread_create(&t2, NULL, &ConnectCommand::updateVal, this);
}

/**
 * function name: updateVal
 * operation: update the value
 * input: args*
 * @return void*
 */
void *ConnectCommand::updateVal(void *args) {
  pthread_mutex_t connect = PTHREAD_MUTEX_INITIALIZER;
  connectLock = connect;
  int n;
  runClient = true;
  pthread_mutex_lock(&connect);
  while (!endSignal) {
    /* Send message to the server */
    if (newOrder.length() > 0) {
      n = send(socketClient, newOrder.c_str(), strlen(newOrder.c_str()), 0);
      if (n < 0) {
        perror("ERROR writing to socket");
        pthread_exit(NULL);
      }
      newOrder = "";
    }
  }
  pthread_mutex_unlock(&connect);
  pthread_exit(&args);
}

/**
 * function name: enterKey
 * operation: enter a key
 * input: vector of strs and index
 * @return int
 */
int ConnectCommand::enterKey(vector<string> vector, int index) {
  int i = 0;
  while (vector.at(index + i) != "\n") {
    i++;
  }
  return i;
}

/**
 * function name: vectorToString
 * operation:convert vec to str
 * input: vector of strs and index
 * @return string
 */
string ConnectCommand::vectorToString(vector<string> vector, int index, int end) {
  string ret = vector.at(index);
  int i = 1;
  while (i < end) {
    ret += vector.at(index + i);
  }
  return ret;
}