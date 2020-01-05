#include "OpenServerCommand.h"
#include "GlobalTables.h"
#include "InterpreterEx3.h"
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>

static int socketServer;

/**
 * function name: execute
 * operation: execute a data
 * input: vector of strs and index
 * @return int
 */
int OpenServerCommand::execute(vector<string> cmdTemp, int index) {
  InterpreterEx3 *iOpenServer = new InterpreterEx3();
  string port;
  int pos = 0;
  int endLine = enterKey(cmdTemp, index);
  string s = vectorToString(cmdTemp, index, index + endLine);
  if (s.find(",", pos) == string::npos) {
    try {
      port = to_string(iOpenServer->calculateExpression(cmdTemp.at(index + 1)));
      openSocket(stoi(port));
      delete iOpenServer;
    } catch (const char *e) {
      if (iOpenServer != nullptr) {
        delete iOpenServer;
      }
      throw e;
    }
  } else {
    try {
      port = to_string(iOpenServer->calculateExpression(s.substr(0, pos)));
      openSocket(stoi(port));
      delete iOpenServer;
    } catch (const char *e) {
      if (iOpenServer != nullptr) {
        delete iOpenServer;
      }
      throw e;
    }
  }
  return 2;
}

/**
 * function name: openSocket
 * operation: opening socket
 * input: int - port number
 * @return void
 */
void OpenServerCommand::openSocket(int port) {
  int sockfd, newsockfd, portno;
  /* First call to socket() function */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("ERROR opening socket");
    exit(1);
  }
  portno = port;
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(portno);
  /* Now bind the host address using bind() call.*/
  if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) < 0) {
    perror("ERROR on binding");
    exit(1);
  }
  socketServer = sockfd;
  /* Now start listening for the clients, here process will
     * go in sleep mode and will wait for the incoming connection
  */
  listen(sockfd, 25);
/* Accept actual connection from the client */
  newsockfd = accept(sockfd, (struct sockaddr *) &address, (socklen_t *) &address);
  if (newsockfd < 0) {
    perror("ERROR on accept");
    exit(1);
  }
  socketServer = newsockfd;
  pthread_t t2;
  pthread_create(&t2, nullptr, &OpenServerCommand::runServer, this);
}

/**
 * function name: runServer
 * operation: running the server
 * input: void* args
 * @return void
 */
void *OpenServerCommand::runServer(void *args) {
  char buffer[1024] = {0};
  int n;
  vector<double> vecTemp;
  string token;
  string rem = "";
  string readfrom = "";

  while (!endSignal) {
    n = read(socketServer, buffer, 1024);
    //cout<<buffer<<endl;
    if (n != -1) {
      vecTemp = buffToDouble(string(buffer));
      updateTable(vecTemp);
    }
  }
  pthread_exit(&args);
}

/**
 * function name: buffToDouble
 * operation: converting buffer (string) to be vector of doubles
 * input: string - buffer
 * @return vector of doubles
 */
vector<double> OpenServerCommand::buffToDouble(string buffer) {
  string temp = buffer;
  vector<double> vecTemp;
  std::size_t pos = 0;
  string token;
  //assuming there are 36 values in buffer, like generic_xml
  for (int i = 0; i < 35; i++) {
    pos = temp.find(',');
    vecTemp.push_back(stod(temp.substr(0, pos)));
    temp.erase(0, pos + 1);
  }
  vecTemp.push_back(stod(temp));
  return vecTemp;
}

/**
 * function name: updateTable
 * operation: updating tables from GlobalTables
 * input: vector of doubles
 * @return void
 */
void OpenServerCommand::updateTable(vector<double> vecTemp) {
  string location;
  while (!runClient) {
    this_thread::sleep_for(chrono::milliseconds(10));
  }
  try {
    for (int i = 0; i < (int) (vecTemp.size()); i++) {
      location = tableOrder.at(i);
      symbolServer.at(location) = vecTemp.at(i);
    }
    for (auto it : simToVar) {
      symbolTable[it.second] = symbolServer[it.first];
    }
  } catch (std::out_of_range) {
    printf("Index exceding vector's size\n");
  }
}

/**
 * function name: enterKey
 * operation: enter a key
 * input: vector of strs and index
 * @return int
 */
int OpenServerCommand::enterKey(vector<string> vec, int index) {
  int i = 0;
  while (vec.at(index + i) != "\n") {
    i++;
  }
  return i;
}

/**
 * function name: vectorToString
 * operation:convert vector (part of it) to a string
 * input: vector of strs, index and end index
 * @return string
 */
string OpenServerCommand::vectorToString(vector<string> vector, int index, int end) {
  string ret = vector.at(index) + " ";
  int i = 1;
  while (index + i < end) {
    if (ret.length() > 1)
      ret += vector.at(index + i) + " ";
    else {
      break;
    }
    i++;
  }
  return ret;
}