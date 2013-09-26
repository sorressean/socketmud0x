// ****************************************************************************
// SocketMud II Copyright 2004 Brian Graversen
// ****************************************************************************
// Revision History
// ----------------
// 19/01/04) Initial SocketMud II code released
// ****************************************************************************
// This product can be used freely as long as this copyright header remains
// intact. This header may not be removed or changed, and any work released
// based on this code must contain this header information in all files.
// ****************************************************************************

#include "server.h"

int main(int argc, char** argv) {
  Server *mServer = new Server();
  int port;

  switch(argc) {
    case 2:
      port = atoi(argv[1]);
      if (port < 1024 || port > 9999) {
	printf("[port] must be between 1024 and 9999\n");
	return 1;
      }
      break;

    default:
      printf("Syntax: %s [port]\n", argv[0]);
      return 1;
  }

  mServer->Connect(port);

  while(1) {
    // poll all sockets for incoming data
    mServer->PollSockets();

    std::list<Socket*> socketList = mServer->GetSocketList();
    std::list<Socket*>::iterator iSocket;
    Socket *pSocket;

    // echo everything that each socket has sent to us
    for (iSocket = socketList.begin(); iSocket != socketList.end(); ) {
      pSocket = *iSocket++;

      pSocket->Write(pSocket->GetInBuffer());
      pSocket->ClrInBuffer();
    }

    // flush all outgoing data
    mServer->FlushSockets();

    // sleep the rest of the pulse
    mServer->Sleep(5);
  }

  return 1;
}
