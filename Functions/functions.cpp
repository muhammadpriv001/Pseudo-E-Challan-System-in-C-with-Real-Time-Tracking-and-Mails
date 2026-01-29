#include "functions.h"
using namespace std;

//**********Pseudo-Databses**********\\

//String to Integer (Handling String Arrays)
int stringToInt(string num) {
    int sign = 1, result = 0;

    if(num == "") {
        return 0;
    }

    int i = 0;
    if(num[i] == '-') {
        sign = -1;
        i++;
    }

    for(;(num[i] != '\0') && (num[i] >= '0' && num[i] <= '9');i++) {
        result = result*10 + (num[i] - '0');
    }

    return result*sign;
}

//Vehicle
void to_json(json& j, const Vehicle& v) {
    j = json{{"vehicleNum", v.vehicleNum},
            {"wheels", v.wheels}, 
            {"owner", v.owner}, 
            {"email", v.email}, 
            {"address", v.address}};
}

void from_json(const json& j, Vehicle& v) {
    j.at("vehicleNum").get_to(v.vehicleNum);
    j.at("wheels").get_to(v.wheels);
    j.at("owner").get_to(v.owner);
    j.at("email").get_to(v.email);
    j.at("address").get_to(v.address);
}

//Account
void to_json(json& j, const Account& a) {
    j = json{{"owner", a.owner}, 
        {"email", a.email},
        {"password", a.password}, 
        {"address", a.address},
        {"money", a.money}};
}

void from_json(const json& j, Account& a) {
    j.at("owner").get_to(a.owner);
    j.at("email").get_to(a.email);
    j.at("password").get_to(a.password);
    j.at("address").get_to(a.address);
    j.at("money").get_to(a.money);
}

//Challans
void to_json(json& j, const Challans& c) {
    j = json{{"vehicleNum", c.vehicleNum},
            {"challanNo", c.challanNo},
            {"owner", c.owner}, 
            {"email", c.email}, 
            {"address", c.address},
            {"amount", c.amount}};
}

void from_json(const json& j, Challans& c) {
    j.at("vehicleNum").get_to(c.vehicleNum);
    j.at("challanNo").get_to(c.challanNo);
    j.at("owner").get_to(c.owner);
    j.at("email").get_to(c.email);
    j.at("address").get_to(c.address);
    j.at("amount").get_to(c.amount);
}

//Size of Array for Json
void getSize(string file, int &rows, int &cols) {
    json j;
    ifstream read(file);

    if (read.is_open())
        read >> j;

    read.close();

    rows = 1;
    for (auto &entry : j)
        rows++;

    cols = 0;
    for (auto &item : j.at(0).items())
        cols++;
}

//Json to Dynamic 2D Array
void toArray(string file, string **arr, int rows, int cols) {
    json j;
    ifstream read(file);

    if (read.is_open())
        read >> j;

    read.close();

    int c = 0;
    for (auto &item : j.at(0).items())
        arr[0][c++] = item.key();

    for (int r = 1; r < rows; r++) {
        int col = 0;
        for (auto &item : j.at(r - 1).items())
            if(item.value().is_string()) {
                arr[r][col++] = item.value().get<string>();
            } else if(item.value().is_array()) {
                string temp = "";
                for (auto &x : item.value()) {
                    temp += to_string(x.get<int>()) + " ";
                }
                
                arr[r][col++] = temp;
            } else {
                arr[r][col++] = to_string(item.value().get<int>());
            }
    }
}


//**********Admin Controls**********\\

//check if admin exists
bool adminExist(string admin) {
    json j;
    ifstream read("./Admin/Admin.json");
    if (read.is_open()) {
        read >> j;
        read.close();
    }

    for (const auto& entry : j) {
        if (entry["admin"] == admin) {
            return true;
        }
    }

    return false;
}

//Check Password
bool adminLogin(string admin, string password) {
    json j;
    ifstream read("./Admin/Admin.json");
    if (read.is_open()) {
        read >> j;
        read.close();
    }

    for (const auto& entry : j) {
        if (entry["admin"] == admin && entry["password"] == password) {  
            return true;
        }
    }

    return false;
}


//**********Registrations**********\\

//Vehicle Registration
void vehicleRegistration(string vehicleNum,int wheels, string owner,string email,string address) {
    Vehicle vehicle{vehicleNum, wheels, owner, email, address};

    json j;
    ifstream read("./Challans/Vehicle Registration.json");
    if(read.is_open()) {
        read >> j;
        read.close();
    }

    bool exists = false;
    for (const auto& entry : j) {
        if (entry["vehicleNum"] == vehicle.vehicleNum) {
            exists = true;
            break;
        }
    }

    if (exists) {
        cout << "Vehicle with number " << vehicleNum << " is already registered!" << endl;
        sendEmailAsync(email, "Vehicle Already Registered", "Your Vehicle " + vehicleNum + " has already been Registered against " + email);
        return;
    }

    j.push_back(vehicle);

    ofstream write("./Challans/Vehicle Registration.json");
    write << j.dump(4);
    write.close();

    cout << "Vehicle Registered Successfully!" << endl;
    sendEmailAsync(email, "Vehicle Registration Notification", "Your Vehicle " + vehicleNum + " has been Registered against " + email);
}

//Account Registration
void accRegistration(string owner, string email, string password, string address, int money) {
    Account acc{owner, email, password, address, money};

    json j;
    ifstream read("./Finances/Accounts.json");
    if (read.is_open()) {
        read >> j;
        read.close();
    }

    bool exists = false;
    for (const auto& entry : j) {
        if (entry["email"] == acc.email) {
            exists = true;
            break;
        }
    }

    if (exists) {
        cout << "Account with email " << email << " already exists!" << endl;
        sendEmailAsync(email, "Account Already Registered", "Account Already Registered against " + email);
        return;
    }

    j.push_back(acc);

    ofstream outFile("./Finances/Accounts.json");
    outFile << j.dump(4);
    outFile.close();

    cout << "Account registered successfully!" << endl;
    sendEmailAsync(email, "Account Registration Notification", "Your Account has been Registered in our Bank against " + email);
}


//**********Pseudo-Bank System**********\\

//Check if Account Exist
bool accExist(const string& email) {
    json j;
    ifstream read("./Finances/Accounts.json");
    if (read.is_open()) {
        read >> j;
        read.close();
    }

    for (const auto& entry : j) {
        if (entry["email"] == email) {
            return true;
        }
    }

    return false;
}

//Check Password
bool bankLogin(string email, string password) {
    json j;
    ifstream read("./Finances/Accounts.json");
    if (read.is_open()) {
        read >> j;
        read.close();
    }

    for (const auto& entry : j) {
        if (entry["email"] == email && entry["password"] == password) {  
            return true;
        }
    }

    return false;
}

//Money Deposit
void moneyDeposit(string email, int deposit) {
    json j;
    ifstream read("./Finances/Accounts.json");
    if (read.is_open()) {
        read >> j;
        read.close();
    }

    for (auto& entry : j) {
        if (entry["email"] == email) {  
            entry["money"] = entry["money"].get<int>()+deposit;
        }
    }

    ofstream write("./Finances/Accounts.json");
    if (write.is_open()) {
        write << j.dump(4);
        write.close();
    }
}

//Money Credit
void moneyCredit(string email, int credit) {
    json j;
    ifstream read("./Finances/Accounts.json");
    if (read.is_open()) {
        read >> j;
        read.close();
    }

    for (auto& entry : j) {
        if (entry["email"] == email) {  
            if((entry["money"].get<int>()-credit) >= 0) {
                entry["money"] = entry["money"].get<int>()-credit;
                sendEmailAsync(email, "Money Credit Notification", "An amount of " + to_string(credit) + " is creditted from your account!");
            } else {
                cout << "Not Enough Money!" << endl;
                sendEmailAsync(email, "Money Credit Limit Exceed Notification", "Not Enough Money to Credit!");
            }
        }
    }

    ofstream write("./Finances/Accounts.json");
    if (write.is_open()) {
        write << j.dump(4);
        write.close();
    }
}

//Challan Payment
void payment(string email, string **acc, int rowsAcc, string **challan, int rowsCh) {
    int rowAcc = -1, rowCh = -1, colAcc = 0, colCh = 0;
    
    for(int i = 1;i < rowsAcc;i++) {
        if(acc[i][1] == email) {
            rowAcc = i;
            break;
        }
    }

    for(int i = 0;i < rowsCh;i++) {
        if(challan[i][3] == email) {
            rowCh = i;
            break;
        }
    }

    if(rowCh == -1) {
        cout << "No Challan against email: " << email << endl;
        sendEmailAsync(email, "Challan Payment", "You Currently have No Challans!");
        return;
    }

    int money = stringToInt(acc[rowAcc][2]);
    int fine  = stringToInt(challan[rowCh][1]);

    if(money < fine) {
        acc[rowAcc][2] = "0";
        challan[rowCh][1] = to_string(fine - money);
        cout << "Payment Successful!\tRemaining Fine: " << challan[rowCh][1] << endl;
        sendEmailAsync(email, "Challan Payment", "Payment Successful!\tRemaining Fine: " + challan[rowCh][1]);
    } else {
        challan[rowCh][1] = "0";
        acc[rowAcc][2] = to_string(money - fine);
        cout << "Payment Successful!\tAll Dues Cleared." << endl;
        sendEmailAsync(email, "Challan Payment", "Payment Successful!\tAll Dues Cleared");
    }

    Account account;
    Challans newChallan;

    json jAcc;

    for(int i = 1;i < rowsAcc;i++) {
        account.address = acc[i][0];
        account.email = acc[i][1];
        account.money = stringToInt(acc[i][2]);
        account.owner = acc[i][3];
        account.password = acc[i][4];

        jAcc.push_back(account);
    }

    ofstream writeAcc("./Finances/Accounts.json");
    writeAcc << jAcc.dump(4);
    writeAcc.close();

    json jCh;

    for(int i = 1;i < rowsCh;i++) {
        if(challan[i][1] == "0") {
            continue;
        }

        newChallan.address = challan[i][0];
        newChallan.amount = stringToInt(challan[i][1]);
        newChallan.challanNo = stringToInt(challan[i][2]);
        newChallan.email = challan[i][3];
        newChallan.owner = challan[i][4];
        newChallan.vehicleNum = challan[i][5];

        jCh.push_back(newChallan);
    }

    ofstream writeCh("./Challans/Challans.json");
    writeCh << jCh.dump(4);
    writeCh.close();
}


//**********E-Challan**********\\

string base64_encode(const string &in) { //base64 Encoder
    static const char* chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string out;
    
    int val=0, valb=-6;
    for (unsigned char c : in) {
        val = (val<<8) + c;
        valb += 8;
        while (valb>=0) {
            out.push_back(chars[(val>>valb)&0x3F]);
            valb-=6;
        }
    }
    
    if (valb>-6) {
        out.push_back(chars[((val<<8)>>(valb+8))&0x3F]);
    }

    while (out.size()%4) {
        out.push_back('=');
    }
    
    return out;
}

size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp) { //Callback for CURL to read the email content
    string *payload = (string*)userp;
    size_t max = size * nmemb;
    if(payload->empty()) {
        return 0;
    }

    size_t len = std::min(max, payload->size());
    memcpy(ptr, payload->c_str(), len);
    payload->erase(0, len);

    return len;
}

void sendEmail(const string &to, const string &subject, const string &body, const string &imagePath) {
    bool hasAttachment = !imagePath.empty();
    string encodedImage;

    if (hasAttachment) {
        ifstream file(imagePath, ios::binary);
        if (!file.is_open()) {
            cerr << "Cannot open file\n";
            return;
        }

        ostringstream oss;
        oss << file.rdbuf();
        encodedImage = base64_encode(oss.str());
    }

    ostringstream msg;
    msg << "From: E-Challan <muhammad.priv001@gmail.com>\r\n";
    msg << "To: " << to << "\r\n";
    msg << "Subject: " << subject << "\r\n";
    msg << "MIME-Version: 1.0\r\n";

    if (!hasAttachment) {
        // ---- Plain text email ----
        msg << "Content-Type: text/plain; charset=UTF-8\r\n\r\n";
        msg << body << "\r\n";
    } else {
        // ---- Email with attachment ----
        msg << "Content-Type: multipart/mixed; boundary=\"BOUNDARY\"\r\n\r\n";

        msg << "--BOUNDARY\r\n";
        msg << "Content-Type: text/plain; charset=UTF-8\r\n\r\n";
        msg << body << "\r\n";

        msg << "--BOUNDARY\r\n";
        msg << "Content-Type: image/jpeg; name=\"attachment.jpg\"\r\n";
        msg << "Content-Disposition: attachment; filename=\"attachment.jpg\"\r\n";
        msg << "Content-Transfer-Encoding: base64\r\n\r\n";
        msg << encodedImage << "\r\n";

        msg << "--BOUNDARY--\r\n";
    }

    string emailData = msg.str();

    CURL* curl = curl_easy_init();
    if (!curl) return;

    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_USERNAME, "muhammad.priv001@gmail.com");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "nrxtdhszknqkvtke");
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "<muhammad.priv001@gmail.com>");

    struct curl_slist* recipients = nullptr;
    recipients = curl_slist_append(recipients, to.c_str());

    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, &emailData);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cerr << "Email failed: " << curl_easy_strerror(res) << "\n";
    }

    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);
}

void sendEmailAsync(const string &to, const string &subject, const string &body, const string &imagePath) { //Async wrapper (non-blocking)
    thread([=](){ sendEmail(to, subject, body, imagePath); }).detach();
}

void getVehicleDetails(const string& vehicleNum, string& owner, string& email, string& address) { //Getting Vehicle Details
    if(vehicleNum == "NONE") {
        owner = "UNKNOWN";
        email = "pseudo-nadra@gmail.com";
        address = "UNKNOWN";
        return;
    }

    string file = "./Challans/Vehicle Registration.json";
    int rows = 0, cols = 0;

    try {
        getSize(file, rows, cols);

        string **arr = new string*[rows];
        for(int i = 0; i < rows; i++)
            arr[i] = new string[cols];

        toArray(file, arr, rows, cols);

        owner = "UNKNOWN";
        email = "pseudo-nadra@gmail.com";
        address = "UNKNOWN";

        for(int i = 1; i < rows; i++) {  
            if(arr[i][3] == vehicleNum) {
                address = arr[i][0];
                email   = arr[i][1];
                owner   = arr[i][2];
                break;
            }
        }

        for(int i = 0; i < rows; i++)
            delete[] arr[i];
        delete[] arr;

    } catch(...) {
        owner = "UNKNOWN";
        email = "pseudo-nadra@gmail.com";
        address = "UNKNOWN";
    }
}

void Challan(const string& vehicleNum, int challanNo, int violationType, string filename) { //Updating Challan Database
    int amount;

    if(violationType == 0) {
        amount = 1000;
    } else {
        amount = 500;
    }

    string owner, email, address;
    getVehicleDetails(vehicleNum, owner, email, address);

    string subject, message;

    if(vehicleNum == "NONE") {
        subject = "Violator Identification Request";
        message = "Request for Identification of the Violator. Challan Amount = " + to_string(amount) + "\n See Attached Image";
    } else {
        subject = "Traffic Violation Notice";
        message = "Dear, " + owner + " a new traffic violation has been registered for your vehicle " + vehicleNum + ". Challan Amount = " + to_string(amount) + "\nSee Attached Image!";
    }

    sendEmailAsync(email, subject, message, filename);

    Challans challan{vehicleNum, challanNo, owner, email, address, amount};

    json j;
    ifstream read("./Challans/Challans.json");
    if(read.is_open()) {
        read >> j;
        read.close();
    }

    j.push_back(challan);

    ofstream outFile("./Challans/Challans.json");
    outFile << j.dump(4);
    outFile.close();

    cout << "Challan Generated for Vehicle: " << vehicleNum << " | Amount: " << amount << " | Owner: " << owner << endl;
}

//Config
AppConfig CONFIG;

//Utility
Rect clipRect(const Rect& r, const Mat& img) { //Bounding box stays inside the image boundaries
    int x = max(r.x, 0), y = max(r.y, 0);
    int w = min(r.width, img.cols - x);
    int h = min(r.height, img.rows - y);
    return Rect(x, y, w, h);
}

float intersectionArea(const Rect& a, const Rect& b) { //Computes the area of overlap (intersection) between two rectangles
    Rect i = a & b;
    if(i.width > 0 && i.height > 0) {
        return float(i.area());
    }

    return 0.0f;
}

float computeIoU(const Rect& a, const Rect& b) { //Calculates the Intersection over Union (IoU) between two bounding boxes
    float inter = intersectionArea(a, b);
    float uni = float(a.area() + b.area()) - inter;
    if(uni > 0.0f) {
        return inter / uni;
    }

    return 0.0f;
}

Vector<string> readClasses(const string& path) {
    Vector<string> cls;
    ifstream file(path);
    
    if (!file.is_open()) {
        cout << "Cannot open classes file: " << path << endl;
        return cls;
    }

    string word;
    while (file >> word) {
        cls.add(word);
    }

    return cls;
}

int readChallanCounter(const string& filePath) { //Ensures challan IDs continue from previous session
    int counter = 1;
    ifstream fin(filePath);
    if (fin.is_open()) { 
        fin >> counter; 
        fin.close(); 
    }

    return counter;
}

void writeChallanCounter(const string& filePath, int counter) { //Writes updated challan number back to file after generating a new violation
    ofstream fout(filePath);
    if (fout.is_open()) { 
        fout << counter; 
        fout.close(); 
    }
}

float redIntensity(const Mat& frame, const Rect& tlBox) { //Calculates how much red color is present in a traffic light bounding box
    Rect r = clipRect(tlBox, frame);
    if (r.area() == 0) {
        return 0.0f;
    }

    Mat roi, hsv, mask1, mask2, mask;
    roi = frame(r);
    cvtColor(roi, hsv, COLOR_BGR2HSV);
    inRange(hsv, Scalar(0,100,100), Scalar(10,255,255), mask1);
    inRange(hsv, Scalar(160,100,100), Scalar(179,255,255), mask2);
    bitwise_or(mask1, mask2, mask);

    return float(countNonZero(mask)) / float(roi.rows*roi.cols);
}

bool vectorContainsInt(Vector<int>& v, int val) { //Checks if a custom vector contains a specific integer
    for(int i=0;i<v.size;i++) {
        if(v.get(i)==val) {
            return true;
        }
    }

    return false;
}

string sanitizePlate(const string &raw) { //Cleans up OCR-detected license plate text by removing: 1) spaces, 2)invalid chars, 3)lowercase letters
    if(raw.empty()) {
        return string("NONE");
    }

    string s;
    for(char c : raw) {
        if(isalnum((unsigned char)c)) {
            s.push_back(c);
        } else {
            s.push_back('_');
        }
    }

    if(s.empty()) {
        return string("NONE");
    }

    return s;
}

void detectAndTrack(Mat &frame, Net &net, vector<string> &outNames, Vector<Rect> &lastPersonBoxes, Vector<Rect> &lastHelmetBoxes, Vector<Rect> &lastMotorbikeBoxes, Vector<Rect> &lastBicycleBoxes, Vector<Rect> &lastCarBoxes, Vector<Rect> &lastTrafficLightBoxes, Vector<VehicleTrack> &trackedVehicles, int &nextTrackId, int personClass, int helmetClass, int motorbikeClass, int bicycleClass, int carClass, int trafficLightClass) { //Detection and Tracking
    Mat blob;
    blobFromImage(frame, blob, 1/255.0, Size(416,416), Scalar(), true, false);
    net.setInput(blob);
    vector<Mat> outputs;
    net.forward(outputs, outNames);

    vector<int> classIds;
    vector<float> confidences;
    vector<Rect> boxes;

    for(size_t k=0;k<outputs.size();k++) {
        float* data = (float*)outputs[k].data;
        
        for(int i=0;i<outputs[k].rows;i++, data+=outputs[k].cols) {
            float conf = data[4];
            if(conf<CONFIG.CONF_THRESHOLD) {
                continue;
            }
            float maxScore=-1; int clsId=-1;
            
            for(int c=5;c<outputs[k].cols;c++) {
                if(data[c]>maxScore) { maxScore=data[c]; 
                    clsId=c-5; 
                }
            }
            
            if(maxScore<CONFIG.CONF_THRESHOLD) {
                continue;
            }
            int cx=int(data[0]*frame.cols);
            int cy=int(data[1]*frame.rows);
            int w=int(data[2]*frame.cols);
            int h=int(data[3]*frame.rows);
            
            boxes.push_back(Rect(cx-w/2, cy-h/2, w, h));
            classIds.push_back(clsId);
            confidences.push_back(maxScore);
        }
    }

    vector<int> idx;
    NMSBoxes(boxes,confidences,CONFIG.CONF_THRESHOLD,CONFIG.NMS_THRESHOLD,idx);

    lastPersonBoxes.clear(); 
    lastHelmetBoxes.clear(); 
    lastMotorbikeBoxes.clear();
    lastBicycleBoxes.clear(); 
    lastCarBoxes.clear(); 
    lastTrafficLightBoxes.clear();

    for(int ii=0; ii<(int)idx.size(); ii++) {
        int id=idx[ii];
        int cls = classIds[id];
        Rect box = boxes[id];

        if(cls==personClass) {
            lastPersonBoxes.add(box);
        } else if(cls==helmetClass) {
            lastHelmetBoxes.add(box);
        } else if(cls==motorbikeClass) {
            lastMotorbikeBoxes.add(box);
        } else if(cls==bicycleClass) {
            lastBicycleBoxes.add(box);
        } else if(cls==carClass) {
            lastCarBoxes.add(box);
        } else if(cls==trafficLightClass) {
            lastTrafficLightBoxes.add(box);
        }
    }

    //Vehicle tracking logic
    Vector<Rect> vehicleBoxes;
    for(int i=0;i<lastMotorbikeBoxes.size;i++) {
        if(lastMotorbikeBoxes.get(i).area()>=CONFIG.MIN_VEHICLE_AREA) {
            vehicleBoxes.add(lastMotorbikeBoxes.get(i));
        }
    }

    for(int i=0;i<lastBicycleBoxes.size;i++) {
        if(lastBicycleBoxes.get(i).area()>=CONFIG.MIN_VEHICLE_AREA) {
            vehicleBoxes.add(lastBicycleBoxes.get(i));
        }
    }

    for(int i=0;i<lastCarBoxes.size;i++) {
        if(lastCarBoxes.get(i).area()>=CONFIG.MIN_VEHICLE_AREA) {
            vehicleBoxes.add(lastCarBoxes.get(i));
        }
    }

    for(int t=0;t<trackedVehicles.size;t++) {
        trackedVehicles.get(t).lostFrames++;
    }

    for(int v=0;v<vehicleBoxes.size;v++) {
        Rect det = vehicleBoxes.get(v);
        float maxIoU=0.0f; int bestTrack=-1;
        for(int t=0;t<trackedVehicles.size;t++) {
            float iou = computeIoU(det,trackedVehicles.get(t).bbox);
            if(iou>maxIoU) { 
                maxIoU=iou; 
                bestTrack=t; 
            }
        }

        if(maxIoU>0.3f && bestTrack!=-1) {
            trackedVehicles.get(bestTrack).bbox = det;
            trackedVehicles.get(bestTrack).lostFrames = 0;
        } else {
            VehicleTrack vt; vt.id=nextTrackId++; 
            vt.bbox=det; vt.lostFrames=0;
            trackedVehicles.add(vt);
        }
    }

    // Remove lost tracks
    Vector<VehicleTrack> newTracked;
    for(int t=0;t<trackedVehicles.size;t++) {
        if(trackedVehicles.get(t).lostFrames<=CONFIG.MAX_LOST) {
            newTracked.add(trackedVehicles.get(t));
        }
    }

    trackedVehicles.clear();
    for(int t=0;t<newTracked.size;t++) {
        trackedVehicles.add(newTracked.get(t));
    }
}

void processViolations(Mat &frame, Mat &cleanFrame, CascadeClassifier &plateCascade, tesseract::TessBaseAPI &ocr, Vector<Rect> &lastPersonBoxes, Vector<Rect> &lastHelmetBoxes, Vector<Rect> &lastMotorbikeBoxes, Vector<Rect> &lastBicycleBoxes, Vector<Rect> &lastCarBoxes, Vector<Rect> &lastTrafficLightBoxes, Vector<VehicleTrack> &trackedVehicles, Vector<int> &issuedHelmetChallans, Vector<int> &issuedRedLightChallans, int &challanCounter, const string &violationDir, const string &challanFilePath) { //Generating Challans on Violations
    //Helmet Violation
    for(int i=0;i<lastPersonBoxes.size;i++) {
        Rect p = lastPersonBoxes.get(i);
        if(p.area()<CONFIG.MIN_PERSON_AREA) {
            continue;
        }

        bool onBike=false; 
        Rect vehicleBBox;

        //Check motorbike
        for(int m=0;m<lastMotorbikeBoxes.size;m++) {
            if(intersectionArea(p,lastMotorbikeBoxes.get(m))/float(p.area())>0.05f) {
                onBike=true; 
                vehicleBBox=lastMotorbikeBoxes.get(m); 
                break;
            }
        }

        // Check bicycle
        if(!onBike){
            for(int b=0;b<lastBicycleBoxes.size;b++) {
                if(intersectionArea(p,lastBicycleBoxes.get(b))/float(p.area())>0.05f) {
                    onBike=true; 
                    vehicleBBox=lastBicycleBoxes.get(b); 
                    break;
                }
            }
        }

        if(!onBike) {
            continue;
        }

        bool hasHelmet=false;
        Rect headROI(p.x,p.y,p.width,int(p.height*CONFIG.HEAD_ROI_RATIO));
        headROI=clipRect(headROI,frame);
        for(int h=0;h<lastHelmetBoxes.size;h++) {
            if(intersectionArea(headROI,lastHelmetBoxes.get(h))/float(max(1,headROI.area()))>=CONFIG.HELMET_OVERLAP_THRESHOLD) {
                hasHelmet=true;
            }
        }

        if(!hasHelmet) {
            int vid=-1;
            for(int t=0;t<trackedVehicles.size;t++) {
                if(computeIoU(vehicleBBox,trackedVehicles.get(t).bbox)>0.3f){ 
                    vid=trackedVehicles.get(t).id; 
                    break;}
            }

            if(vid!=-1) {
                for(int t=0;t<trackedVehicles.size;t++) {
                    if(trackedVehicles.get(t).id == vid) {
                        trackedVehicles.get(t).helmetViolation = true;
                        break;
                    }
                }
            }
        }
    }

    // ---------------- Red-light Violation ----------------
    float maxRed=0.0f;
    for(int i=0;i<lastTrafficLightBoxes.size;i++) {
        maxRed = max(maxRed, redIntensity(frame,lastTrafficLightBoxes.get(i)));
    }

    if(maxRed>0.05f) {
        Rect stopLineROI(0,int(frame.rows*0.7),frame.cols,50);
        stopLineROI = clipRect(stopLineROI,frame);

        Vector<Rect> vehicles;
        for(int i=0;i<lastMotorbikeBoxes.size;i++) {
            vehicles.add(lastMotorbikeBoxes.get(i));
        }
        for(int i=0;i<lastBicycleBoxes.size;i++) {
            vehicles.add(lastBicycleBoxes.get(i));
        }
        for(int i=0;i<lastCarBoxes.size;i++) {
            vehicles.add(lastCarBoxes.get(i));
        }

        for(int i=0;i<vehicles.size;i++) {
            Rect v = vehicles.get(i);
            if(v.area()==0) {
                continue;
            }

            if(intersectionArea(v,stopLineROI)/float(v.area())>0.01f) {
                int vid=-1;
                for(int t=0;t<trackedVehicles.size;t++) {
                    if(computeIoU(v,trackedVehicles.get(t).bbox)>0.3f) { 
                        vid=trackedVehicles.get(t).id; 
                        break;
                    }
                }

                if(vid!=-1) {
                    for(int t=0;t<trackedVehicles.size;t++) {
                        if(trackedVehicles.get(t).id == vid) {
                            trackedVehicles.get(t).redLightViolation = true;
                            break;
                        }
                    }
                }
            }
        }
    }

    // ---------------- Draw Tracked Vehicles & OCR Plates ----------------
    for(int t=0;t<trackedVehicles.size;t++) {
        VehicleTrack& vt = trackedVehicles.get(t);
        Scalar color = Scalar(0,255,0); // green
        if(vt.helmetViolation || vt.redLightViolation) {
            color = Scalar(0,0,255); // red for violators
        }

        rectangle(frame, vt.bbox, color, 3);
        putText(frame, "ID:"+to_string(vt.id), Point(vt.bbox.x, vt.bbox.y-5), FONT_HERSHEY_SIMPLEX, 0.6, color, 2);

        // Detect plate if violator
        if(vt.helmetViolation || vt.redLightViolation) {
            Rect plateSearch = vt.bbox;
            plateSearch.y += plateSearch.height/2;
            plateSearch.height = plateSearch.height/4;
            plateSearch.x = max(0, plateSearch.x - plateSearch.width/4);
            plateSearch.width = min(frame.cols - plateSearch.x, plateSearch.width + plateSearch.width/2);
            plateSearch = clipRect(plateSearch, frame);

            vector<Rect> plates;
            plateCascade.detectMultiScale(frame(plateSearch), plates, 1.1, 10);

            string plateText="NONE";
            if(!plates.empty()) {
                Mat plateROI = frame(plateSearch)(plates[0]);
                Mat processed = preprocessPlate(plateROI);
                ocr.SetImage(processed.data, processed.cols, processed.rows, 1, processed.step);
                string text = string(ocr.GetUTF8Text());

                for(char &c : text) {
                    if(!isalnum((unsigned char)c)) {
                        c=' ';
                    }
                }
                size_t first = text.find_first_not_of(' ');
                size_t last = text.find_last_not_of(' ');
                if(first!=string::npos && last!=string::npos) {
                    plateText = text.substr(first, last-first+1);
                } else if(first!=string::npos) {
                    plateText = text.substr(first);
                }
            }

            putText(frame, "Plate:"+plateText, Point(vt.bbox.x, vt.bbox.y+vt.bbox.height+20), FONT_HERSHEY_SIMPLEX, 0.6, color,2);
            cout << "VehID " << vt.id << " Plate: " << plateText << endl;

            // ---------------- Save Violation Image ----------------
            int violationType = -1;
            if(vt.helmetViolation) {
                violationType = 0;
            }
            if(vt.redLightViolation) {
                violationType = 1;
            }

            if(violationType != -1) {
                bool alreadyIssued;
                if(violationType == 0) {
                    alreadyIssued = vectorContainsInt(issuedHelmetChallans, vt.id);
                } else {
                    alreadyIssued = vectorContainsInt(issuedRedLightChallans, vt.id);
                }

                if(alreadyIssued) {
                    continue;
                }

                string plateFixed = sanitizePlate(plateText);
                Rect saveBox = clipRect(vt.bbox, frame);
                if(saveBox.area()>0) {
                    Mat cropped = cleanFrame(saveBox).clone();
                    string filename = violationDir +
                        "ViolationID-" + to_string(violationType) +
                        "_ChallanNo-" + to_string(challanCounter) +
                        "_Plate-" + plateFixed + ".jpg";

                    if(imwrite(filename, cropped)) {
                        cout << "Saved: " << filename << endl;

                        Challan(plateFixed, challanCounter, violationType, filename);

                        if(violationType==0) {
                            issuedHelmetChallans.add(vt.id);
                        } else {
                            issuedRedLightChallans.add(vt.id);
                        }

                        challanCounter++;
                        writeChallanCounter(challanFilePath, challanCounter);
                    } else {
                        cout << "Failed to save: " << filename << endl;
                    }
                } else {
                    cout << "Invalid save box for VehID " << vt.id << endl;
                }
            }
        }
    }
}

Mat preprocessPlate(const Mat &plate) { //Plate preprocessing for OCR
    Mat gray, thresh, resized;
    cvtColor(plate, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gray, Size(3,3), 0);
    adaptiveThreshold(gray, thresh, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, 10);
    resize(thresh, resized, Size(), 3, 3, INTER_CUBIC);

    return resized;
}

//Challan Generation
void processVideo(const string& videoSource) { //Processing Given VideoSource
    // YOLO setup
    Net net = readNetFromDarknet(CONFIG.yoloCfg, CONFIG.yoloWeights);
    net.setPreferableBackend(DNN_BACKEND_OPENCV);
    net.setPreferableTarget(DNN_TARGET_CPU);
    vector<string> outNames = net.getUnconnectedOutLayersNames();

    // Read classes
    Vector<string> classes = readClasses(CONFIG.classFile);
    int personClass=-1, helmetClass=-1, motorbikeClass=-1, bicycleClass=-1, carClass=-1, trafficLightClass=-1;

    for(int i=0;i<classes.size;i++) {

        if(classes.get(i)=="person") {
            personClass=i;
        } else if(classes.get(i)=="helmet") {
            helmetClass=i;
        } else if(classes.get(i)=="motorbike") {
            motorbikeClass=i;
        } else if(classes.get(i)=="bicycle") {
            bicycleClass=i;
        } else if(classes.get(i)=="car") {
            carClass=i;
        } else if(classes.get(i)=="traffic_light") {
            trafficLightClass=i;
        }
    }
    
    if(personClass==-1 || helmetClass==-1) { 
        cout<<"Required classes missing\n"; 
        return; 
    }

    // Video capture
    VideoCapture cap(videoSource, cv::CAP_FFMPEG);
    if(!cap.isOpened()) { 
        cout<<"Failed to open video\n"; 
        return; 
    }

    // Plate detection
    CascadeClassifier plateCascade;
    if(!plateCascade.load(CONFIG.plateCascade)) { 
        cout << "Cannot load Haar cascade xml\n"; 
        return; 
    }

    tesseract::TessBaseAPI ocr;
    if (ocr.Init(NULL, "eng", tesseract::OEM_LSTM_ONLY)) { 
        cout << "Cannot initialize Tesseract\n"; 
        return; 
    }

    ocr.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    ocr.SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");

    int challanCounter = readChallanCounter(CONFIG.challanCounterFile);
    int frameIndex=0, detectionInterval=5, nextTrackId=0;

    Vector<Rect> lastPersonBoxes,lastHelmetBoxes,lastMotorbikeBoxes,lastBicycleBoxes,lastCarBoxes,lastTrafficLightBoxes;
    Vector<VehicleTrack> trackedVehicles;
    Vector<int> issuedHelmetChallans, issuedRedLightChallans;

    Mat frame;
    while(cap.read(frame)) {
        frameIndex++;
        bool runDetection = (frameIndex % detectionInterval == 0);
        Mat cleanFrame = frame.clone();

        if(runDetection) {
            detectAndTrack(frame, net, outNames, lastPersonBoxes, lastHelmetBoxes, lastMotorbikeBoxes, lastBicycleBoxes, lastCarBoxes, lastTrafficLightBoxes, trackedVehicles, nextTrackId, personClass, helmetClass, motorbikeClass, bicycleClass, carClass, trafficLightClass);
        }

        processViolations(frame, cleanFrame, plateCascade, ocr, lastPersonBoxes, lastHelmetBoxes, lastMotorbikeBoxes, lastBicycleBoxes, lastCarBoxes, lastTrafficLightBoxes, trackedVehicles, issuedHelmetChallans, issuedRedLightChallans, challanCounter, CONFIG.violationDir, CONFIG.challanCounterFile);

        imshow("Traffic Violation Detection", frame);
        if(waitKey(10)==27) {
            break;
        }
    }

    cap.release();
    destroyAllWindows();
    ocr.End();

    writeChallanCounter(CONFIG.challanCounterFile, challanCounter);
}