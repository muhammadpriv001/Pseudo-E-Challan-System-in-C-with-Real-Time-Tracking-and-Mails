#include "Functions/functions.h"

// ---------------- Video selection ----------------
string selectVideo() {
    cout << "\n========= VIDEO MENU =========\n";
    cout << "1. Sample_1.mp4\n";
    cout << "2. Sample_2.mp4\n";
    cout << "3. Sample_3.mp4\n";
    cout << "4. Sample_4.mp4\n";
    cout << "5. Sample_5.mp4\n";
    cout << "6. Sample_6.mp4\n";
    cout << "7. Sample_7.mp4\n";
    cout << "8. Enter custom path\n";
    cout << "9. Live Feed\n";
    cout << "0. EXIT program\n";
    cout << "==============================\n";
    cout << "Enter choice: ";

    int ch;  
    cin >> ch;

    if(ch == 0) {
        return "EXIT";
    }
    if(ch >= 1 && ch <= 7) {
        return "Samples/Sample_" + to_string(ch) + ".mp4";
    }
    if(ch == 8) {
        string path;
        cout << "Enter full video path: ";
        cin >> path;
        return path;
    }
    if(ch == 9) {
        return CONFIG.liveFeedURL;
    }

    cout << "Invalid option! Try again.\n";
    return selectVideo();
}

// ---------------- Main ----------------
int main() {
    while(true) {
        string videoSource = selectVideo();
        if(videoSource == "EXIT") {
            break;
        }

        processVideo(videoSource);
    }
    return 0;
}