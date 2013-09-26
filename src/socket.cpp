// ****************************************************************************
// SocketMud II Copyright 2004 Brian Graversen
// ****************************************************************************
// Revision History
// ----------------
// 19/01/04) Initial socket code released
// ****************************************************************************
// This product can be used freely as long as this copyright header remains
// intact. This header may not be removed or changed, and any work released
// based on this code must contain this header information in all files.
// ****************************************************************************

#include <unistd.h>
#include <errno.h>
#include "socket.h"

Socket::Socket(int desc)
{
    control = desc;
}

Socket::~Socket()
{
    if (control != -1)
        close(control);
}

int Socket::GetControl() const
{
    return control;
}

bool Socket::Read()
{
    char temp[4096 + 2];
    int size = 0;

    while (true)
        {
            if ((size = read(control, temp, 4096)) > 0)
                {

                    temp[size] = '\0';
                    inBuffer += (std::string) temp;

                    if (temp[size - 1] == '\n' || temp[size-1] == '\r')
                        break;
                }
            else if (size == 0)
                return false;
            else if (errno == EAGAIN || size == 4096)
                break;
            else
                return false;
        }

    return true;
}

void Socket::Write(const std::string &txt)
{
    outBuffer += txt;
}

bool Socket::Flush()
{
    int b = 0;
    int w = 0;

    // empty the entire buffer
    while (outBuffer.length() > 0)
        {
            b = (outBuffer.length() < 4096) ? outBuffer.length() : 4096;

            // any write failures ?
            if ((w = write(control, outBuffer.c_str(), b)) == -1)
                return false;

            // move the buffer down
            outBuffer.erase(0, w);
        }

    return true;
}

std::string Socket::GetInBuffer() const
{
    return inBuffer;
}

void Socket::ClrInBuffer()
{
    inBuffer.clear();
}
