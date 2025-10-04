# 🏬 UrbanEase Store Management & Analytics System

A comprehensive **store management and performance analysis system** built in C++.  
This project simulates a multi-store retail network, generating products, employees, and sales data automatically — then ranks stores by performance, forecasts future sales, and saves all reports in external files.  

It demonstrates **object-oriented programming, data analytics, file handling, and forecasting algorithms** in C++.

---

## 📖 About
**UrbanEase** is a console-based management system that automates store operations and analytics.  
It can:
- Generate random store, employee, and sales data
- Forecast future sales using moving averages
- Rank stores based on performance (profit, sales, cost)
- Update existing store details
- Save reports to text files for record-keeping

---

## ✨ Features
- 🏪 **Store Data Simulation:** Randomly generates 100 stores with unique IDs, locations, employees, and sales.
- 👥 **Employee Management:** Assigns managers and staff with salaries.
- 📦 **Product Handling:** Automatically creates 35 products with SKUs and prices.
- 📊 **Performance Analytics:**
  - Calculates total sales, operational cost, and profit.
  - Generates “Top Performer” and “Bottom Performer” reports.
- 📈 **Sales Forecasting:**
  - Predicts sales for upcoming months using moving averages.
  - Adds seasonal multipliers and confidence levels.
- 💾 **File I/O Integration:**
  - Saves data to `UrbanEase_data.txt`
  - Generates `Performance Report.txt`
  - Creates future sales report `Future Sales Forecast.txt`
- 🔁 **Update Functionality:** Allows modification of any store’s manager and monthly cost.
- ✅ **Memory Management:** Frees dynamically allocated memory for staff members.

---

## 🛠 Installation & Run

### Requirements
- C++ Compiler (e.g., g++, MinGW, or MSVC)
- Works on Windows, macOS, or Linux (no `windows.h` dependency)

### Steps
1. Clone this repository:
   ```bash
   git clone https://github.com/your-username/UrbanEase-Management-System.git
   cd UrbanEase-Management-System

2. **Compile the source code using a C++ compiler:**
   
 g++ OOP_Assignment2_24i_3148.cpp -o UrbanEase

3. Run the program:
   
   ./UrbanEase

## 🚀 Usage

From the main menu, you can:

Generate Data → Creates random store, employee, and sales information.

Update Data → Modify an existing store’s details (manager name or cost).

Print Future Forecast → Predicts next 5 months of sales per store.

Generate Data Analytic Report → Produces ranking and performance summaries.

Exit → Closes the program safely and releases memory.

## 📊 Output Files

UrbanEase_data.txt:	          
Contains generated store data, employees, and sales.

Performance Report.txt:	      
Shows top and bottom performing stores.

Future Sales Forecast.txt:	    
Lists predicted future sales and confidence levels.

## 📜 License

This project is licensed under the MIT License.
You’re free to use, modify, and distribute it.

## 👤 Author

Made by @Fahadshoaib1068

