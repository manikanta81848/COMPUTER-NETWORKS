#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

#ifdef __linux__
#define CLRSCR "clear"
#else
#define CLRSCR "cls"
#endif

class simulator
{
    const int FRAME_SIZE = 1024;
    char *channel;
    int isACKRecieved;
    int isFrameRecieved;
    char *frame;
    void sender();
    void reciever();
    void senderRecieveACK();
    void resendFrame();

  public:
    simulator();
    ~simulator();
    void simulate(int count, int isChannelNoisy);
};

int main()
{
    int choice, count;
    simulator sim;
    srand(time(0));
    system(CLRSCR);
    cout << "### STOP AND WAIT PROTOCOL SIMULATOR ###" << endl;
    cout << "Simulating stop and wait for noisy channel" << endl;
    cout << "Number of frames to simulate: ";
    cin >> count;
    sim.simulate(count, 1);
}

simulator::simulator()
{
    this->channel = new char[FRAME_SIZE];
    this->frame = new char[FRAME_SIZE];
}

simulator::~simulator()
{
    delete[] this->channel;
    delete[] this->frame;
}

void simulator::sender()
{
    cout << "Enter frame to send: ";
    cin >> this->frame;
    cout << "SENDER: Sending frame: " << this->frame << endl;
    strcpy(this->channel, this->frame);
}

void simulator::reciever()
{
    while (!isFrameRecieved)
        resendFrame();
    cout << "Recieved Frame: " << channel << endl;
    cout << "Sending ACK" << endl;
}

void simulator::resendFrame()
{
    cout << "SENDER: Timer timed out resending frame (either frame is lost or ACK is lost)" << endl;
    this->isFrameRecieved = rand() % 2;
    this->isACKRecieved = rand() % 2;
}

void simulator::senderRecieveACK()
{
    if (!isACKRecieved)
    {
        resendFrame();
        reciever();
    }

    cout << "SENDER: Recieved ACK sending next frame if any" << endl;
}

void simulator::simulate(int count, int isChannelNoisy = 0)
{
    while (count > 0)
    {
        if (isChannelNoisy)
        {
            this->isACKRecieved = rand() % 2;

            this->isFrameRecieved = rand() % 2;
        }
        sender();
        reciever();
        senderRecieveACK();
        count--;
    }
}