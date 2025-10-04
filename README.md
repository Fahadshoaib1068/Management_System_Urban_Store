# 🏙️ UrbanEase Store Analytics

**A Data-Driven Store Management and Analytics System**  
Built in **C++**, this console-based software simulates and analyzes retail store performance using data generation, clustering, forecasting, and ranking methods.

---

## 📘 Overview

UrbanEase Store Analytics is a **console-based C++ application** that simulates a network of retail stores and provides insights into their performance.  
It leverages **data generation**, **K-Means clustering**, **predictive forecasting**, and **performance ranking** to deliver a complete data analytics experience — right from the terminal.

---

## 🚀 Features

### 🧮 Automated Data Generation
- Dynamically generates **100 stores** and **35 products** with random values.  
- Each store has:
  - Manager and employee data  
  - Sales records for 24 months (2 years)  
  - Product details and customer statistics  

### 📊 Smart Analytics
- **K-Means Clustering:**  
  Classifies stores into 3 clusters based on:
  - Total Sales  
  - Average Sales per Day  
  - Customer Volume  
  → Results saved in `Clustered Stores.txt`.

- **Performance Ranking System:**  
  Evaluates stores based on:
  - Profit (50%)  
  - Total Sales (30%)  
  - Operational Cost (20%)  
  → Full report saved in `Performance Report.txt`.

- **Future Sales Forecasting:**  
  Predicts sales trends using:
  - Moving Average  
  - Linear Regression (R² Confidence Level)  
  - Automatic Warning Flags for negative growth  
  → Output saved in `Future Sales Forecast.txt`.

### 🎨 Visual Representation
- Displays **ASCII bar charts** of monthly sales trends per store directly in the terminal.

### 🧩 Data Editing
- Allows users to **update store data** (manager name or monthly cost).  
- Updates reflect automatically in `UrbanEase_data.txt`.

---

## 🗂️ Generated Files

| File | Description |
|------|--------------|
| `UrbanEase_data.txt` | All generated store, employee, and product data |
| `Clustered Stores.txt` | Results from the K-Means clustering algorithm |
| `Performance Report.txt` | Ranked list of top and low-performing stores |
| `Future Sales Forecast.txt` | Forecasted sales, confidence levels, and warnings |

---

## ⚙️ Menu Options

| Option | Description |
|--------|-------------|
| `1` | Generate Random Data |
| `2` | Update Existing Store Details |
| `3` | Perform K-Means Clustering |
| `4` | Predict Future Sales |
| `5` | Generate Performance Report |
| `6` | Display Monthly Sales Graph |
| `7` | Exit and Free Memory |

---

## 🧠 Core Concepts Used

- **Object-Oriented Programming**
  - Struct-based modular data models
  - Dynamic Memory Allocation (DMA)
  - File Handling for data persistence  
- **Data Science Techniques**
  - K-Means Clustering  
  - Moving Average Forecasting  
  - Linear Regression (Confidence Scoring)
- **Console Visualization**
  - Text-based bar graphs using ASCII art  

---

## 💻 How to Run

### Requirements
- Windows OS (for color and console output support)
- C++ compiler (MinGW, MSVC, or g++ supporting C++98)

### Steps
```bash
git clone https://github.com/your-username/urbanease-analytics.git
cd urbanease-analytics
g++ UrbanEase Store Management System.cpp -o urbanease.exe
urbanease.exe
```

## 🧹 Memory Management

All dynamically allocated data — including:

Employee arrays

Product sales

Subclusters and Clusters
— are properly freed before exit, ensuring zero memory leaks.

## 🏆 Highlights

End-to-end simulation of a multi-store retail system

Combines data analytics + business logic

Cleanly structured, modular, and reusable C++ code

Ideal demonstration of OOP + Analytical Programming concepts

## 📄 License

This project is licensed under the MIT License.
You’re free to use, modify, and share it for educational or professional purposes.

## ⭐ Developed by: Fahad Shoaib
📊 UrbanEase — Intelligent Store Analytics System
