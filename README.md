# 🚦 Pseudo E‑Challan System

An **Automated Traffic Violation Detection & Management System** built as a **Semester Project (BS Software Engineering)**. This project demonstrates how computer vision and lightweight data handling can be combined to simulate a real‑world **digital e‑challan** ecosystem.

---

## 📌 Project Overview

The **Pseudo E‑Challan System** automates the detection of traffic violations, extracts vehicle number plates, generates proof‑based challans, and notifies vehicle owners via email — all without using heavy SQL databases.

The system is designed to be:
- ⚡ **Lightweight** (JSON‑based pseudo databases)
- 🤖 **Automated** (Computer Vision driven)
- 💰 **Cost‑Effective** (No enterprise infrastructure required)
- 🧪 **Educational** (Focus on concepts over production deployment)

---

## ❗ Problem Statement

Traditional traffic challan systems suffer from:
- Manual inefficiency and human error
- Delays between violation and fine issuance
- Lack of image‑based proof
- Heavy database overhead for small‑scale systems

This project addresses these issues by introducing **real‑time detection**, **evidence‑backed challans**, and **instant notifications**.

---

## 🎯 Core Objectives

- Detect traffic violations using Computer Vision
- Extract vehicle number plates from images/video
- Maintain vehicle and challan records using JSON
- Automatically calculate and issue fines
- Notify vehicle owners via email with proof

---

## 🏗️ System Architecture

```
Camera / Image Input
        ↓
OpenCV Processing Engine (C++)
        ↓
Violation Detection & Plate Extraction
        ↓
JSON Pseudo Database
        ↓
CLI Dashboard + Email Notification
```

### Architecture Layers
- **Input Module**: Camera stream or static images
- **Processing Engine**: OpenCV + C++ logic
- **Data Layer**: JSON files as pseudo‑databases
- **Output Layer**: CLI dashboards and SMTP email alerts

---

## 🧰 Technology Stack

| Technology | Purpose |
|---------|--------|
| **C++** | Core system logic & performance |
| **OpenCV** | Image processing & plate detection |
| **YOLO** | Vehicle / object detection |
| **Haarcascade** | Number plate recognition |
| **JSON** | Lightweight data storage |
| **SMTP** | Email notifications |
| **Python** | Auxiliary streaming utilities |

---

## 🗄️ JSON Pseudo Database Design

The project avoids SQL by using structured JSON files for:

- Vehicle registration records
- Challan history
- Payment status
- Revenue tracking

This approach keeps the system simple while demonstrating CRUD operations and data consistency handling.

---

## 🧩 Modules Breakdown

### 1️⃣ Vehicle Registration Module

Registers vehicles before monitoring begins.

**Features:**
- Owner & vehicle details input
- Unique vehicle ID generation
- Automatic JSON serialization

---

### 2️⃣ Challan Generation Module

Triggered automatically upon violation detection.

**Features:**
- Number plate extraction
- Violation proof image capture
- Fine calculation based on violation type
- Challan ID linking

---

### 3️⃣ Payment Handling Module

Simulates challan payment lifecycle.

**Features:**
- Payment status updates
- Revenue tracking
- JSON record synchronization

---

### 4️⃣ Admin Dashboard (CLI)

Central monitoring and management interface.

**Features:**
- Live challan monitoring
- Vehicle & challan CRUD operations
- Revenue analytics

---

### 5️⃣ Email Notification System

Automatically informs vehicle owners.

**Features:**
- SMTP‑based email alerts
- Proof image attachment
- Near real‑time delivery

---

## 🖼️ OpenCV Detection Workflow

- Frame acquisition
- Grayscale conversion
- Gaussian blur for noise reduction
- Plate detection using Haarcascade
- Vehicle detection using YOLO
- Cropped proof image saved and linked to challan

---

## 🛠️ Installation & Setup Guide

### Prerequisites
- C++ Compiler (GCC / MinGW)
- OpenCV installed & configured
- Python 3.x (for streaming utilities)

### Clone Repository
```bash
git clone https://github.com/muhammadpriv001/Pseudo-E-Challan-System-in-C-with-Real-Time-Tracking-and-Mails.git
cd Pseudo-e-challan-System_Semester-Project-Group-D
```

### Build & Run
```bash
g++ pseudo_echallan.cpp -o echallan `pkg-config --cflags --libs opencv4`
./echallan
```

*(Commands may vary depending on OS and OpenCV setup)*

---

## 🎬 Demo & Usage

1. Register a vehicle
2. Provide image/video input
3. System detects violation
4. Challan is generated with proof
5. Email notification is sent
6. Admin monitors records via CLI

Screenshots, presentation slides, and demo files are included in the repository.

---

## 🚧 Challenges & Solutions

| Challenge | Solution |
|--------|---------|
| Low detection accuracy | Image preprocessing & filtering |
| JSON concurrency issues | Controlled file streaming |
| CLI usability | Structured menus & validation |

---

## 📌 Project Status

✅ Core functionality complete  
🧪 Educational prototype  
🚫 Not intended for real‑world deployment

---

## 👥 Team Members

- Muhammad
- Fatima Saeed
- Eman Fatima
- Minahil Hammad

---

## 📄 License

This project is developed for **academic purposes only**.

---

## ⭐ Acknowledgments

- OpenCV Community
- Course Instructors & Mentors
- Open‑source contributors

---

> "Automating traffic enforcement through evidence‑based systems improves transparency, efficiency, and road safety."