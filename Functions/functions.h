//**********Defining Header File**********\\

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//**********Libraries**********\\

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>
#include <string>
#include <fstream>
#include <curl/curl.h>
#include <thread>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <cctype>

//**********Namespaces**********\\

using namespace std;
using json = nlohmann::json;
using namespace cv;
using namespace dnn;

//**********Custom Vector**********\\

template<typename T>
class Vector {
public:
    int size;
    int capacity;
    T* arr;

    Vector() {
        size = 0;
        capacity = 1;
        arr = new T[capacity];
    }

    void add(T ele) {
        if (size == capacity) {
            capacity *= 2;
            T* temp = new T[capacity];
            for (int i = 0; i < size; i++) temp[i] = arr[i];
            delete[] arr;
            arr = temp;
        }
        arr[size++] = ele;
    }

    T& get(int idx) { 
        return arr[idx]; 
    }

    void clear() { 
        size = 0; 
    }

    ~Vector() { 
        delete[] arr; 
    }
};

//**********Structs**********\\

//Vehicle
struct Vehicle {
    string vehicleNum;
    int wheels;
    string owner;
    string email;
    string address;
};

//Vehicle Track
struct VehicleTrack { 
    int id;
    Rect bbox;
    int lostFrames;
    bool helmetViolation = false;
    bool redLightViolation = false;
};

//Account
struct Account {
    string owner;
    string email;
    string password;
    string address;
    int money;
};

//Challans
struct Challans {
    string vehicleNum;
    int challanNo;
    string owner;
    string email;
    string address;
    int amount;
};

//Config
struct AppConfig {
    //YOLO files
    string yoloCfg = "Resources/yolov4.cfg";
    string yoloWeights = "Resources/yolov4.weights";
    string classFile = "Resources/classes.txt";

    //Cascades
    string plateCascade = "Resources/haarcascade_russian_plate_number.xml";
    string facCascade = "Resources/haarcascade_frontalface_default.xml";

    //Paths
    string violationDir = "Violators/";
    string challanCounterFile = "Violators/last_challan_no.txt";

    //IP CAM default
    string liveFeedURL = "http://172.16.18.212:4747/video";

    //Detection parameters
    float CONF_THRESHOLD = 0.4f; //Minimum confidence score required to accept a detection (vehicle/person/helmet)
    float NMS_THRESHOLD = 0.4f; //Threshold used in Non-Maximum Suppression (NMS) to remove overlapping duplicate detections
    float HEAD_ROI_RATIO = 0.5f; //Ratio used to estimate the upper portion of a detected person/vehicle bounding box
    float HELMET_OVERLAP_THRESHOLD = 0.05f; //Minimum required overlap (IoU) between a helmet box and a head region to consider the helmet as actually worn
    int MAX_LOST = 15; //Maximum allowed number of frames a tracked vehicle/person can remain “lost” before removing the track
    int MIN_VEHICLE_AREA = 3000; //Minimum bounding-box pixel area required to accept a detection as a vehicle, filters out small/noisy detections
    int MIN_PERSON_AREA = 800; //Minimum bounding-box pixel area required to accept a detection as a person
};

//**********DMA**********\\

void getSize(string file, int &rows, int &cols); //Read Json for 2D Array Size
void toArray(string file, string **arr, int rows, int cols); //Update 2D Array from Json

//**********Admin Controls**********\\

bool adminExist(string admin); //Check for Admin Username
bool adminLogin(string admin, string password); //Admin Credentials Check

//**********Registrations**********\\

void vehicleRegistration(string vehicleNum,int wheels, string owner,string email,string address); //Vehicle Registration
void accRegistration(string owner,string email, string password, string address, int money = 0); //Account Registrations

//**********Finances**********\\

bool accExist(const string& email); //Check for Username
bool bankLogin(string email, string password); //User Credentials Check
void moneyDeposit(string email, int deposit); //Deposit Money
void moneyCredit(string email, int credit); //Credit Money
void payment(string email, string **acc, int rowsAcc, string **challan, int rowsCh); //Pay Challan

//**********E-Challan**********\\

//E-Mail Sending
void sendEmailAsync(const string &to, const string &subject, const string &body, const string &imagePath = "");

//Config
extern AppConfig CONFIG;

//Utility
Rect clipRect(const Rect& r, const Mat& img); //Bounding box stays inside the image boundaries
float intersectionArea(const Rect& a, const Rect& b); //Computes the area of overlap (intersection) between two rectangles
float computeIoU(const Rect& a, const Rect& b); //Calculates the Intersection over Union (IoU) between two bounding boxes
Vector<string> readClasses(const string& path); //Reads class names (YOLO/COCO classes) from a .txt file
int readChallanCounter(const string& filePath); //Ensures challan IDs continue from previous session
void writeChallanCounter(const string& filePath, int counter); //Writes updated challan number back to file after generating a new violation
float redIntensity(const Mat& frame, const Rect& tlBox); //Calculates how much red color is present in a traffic light bounding box
bool vectorContainsInt(Vector<int>& v, int val); //Checks if a custom vector contains a specific integer
string sanitizePlate(const string &raw); //Cleans up OCR-detected license plate text by removing: 1) spaces, 2)invalid chars, 3)lowercase letters
Mat preprocessPlate(const Mat &plate); //Plate preprocessing for OCR

void processVideo(const string& videoSource); //Processing VideoSource

#endif