#include <iostream>
#include <cstring>

using namespace std;

// function to perform CRC error detection
void crc_error_detection(string data, string key) {
    int data_len = data.size();
    int key_len = key.size();

    // append zeros to the data
    for (int i = 0; i < key_len - 1; i++) {
        data[data_len + i] = '0';
    }

    // perform division
    for (int i = 0; i < data_len; i++) {
        if (data[i] == '0') continue;
        for (int j = 0; j < key_len; j++) {
            data[i+j] = (data[i+j] == key[j]) ? '0' : '1';
        }
    }

    // check if remainder is all zeros
    for (int i = data_len; i < data_len + key_len - 1; i++) {
        if (data[i] != '0') {
            cout << "Error detected!" << endl;
            return;
        }
    }

    cout << "No error detected." << endl;
}

int main() {
    string data = "",key = "";
    char ch;
    int size;
    
    cout<<"\nEnter the size of the message: ";
    cin>>size;
    
    cout<<"\nEnter the data string: ";
    for(int i=0;i<size;i++){
    	cin>>ch;
    	data += ch;
	}
	
    cout<<"\nEnter the size of the key: ";
    cin>>size;
    
    cout<<"\nEnter the data string: ";    
    for(int i=0;i<size;i++){
    	cin>>ch;
    	key += ch;
	}
	
    crc_error_detection(data, key);

    return 0;
}
