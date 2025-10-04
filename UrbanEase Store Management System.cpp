#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<cstring>
#include<string>

using namespace std;


void intToStr(int num, char* buffer){    // INT TO CHAR CONVERTER
    sprintf(buffer, "%d", num);
}

struct GeoCoordinates{
    double gLat;
    double gLong;
};

struct Employee{
    int eID;
    char eName[20];
    double salary;
};

struct Product{
    char SKU[10];
    char pName[20];
    double unitPrice;
};

struct SalesData{
    int storeID;
    Product product;
    char date[20];
    char time[20];
    double totalSaleAmount;
};

struct Forecast{
	char time[20];
	double predictedsales;
	double confidancelevel;
	bool warning;
};

struct StoreAnalytics{
	double totalsales;
	double totaloperationalcost;
	double profit;
};

struct Centroid {
    double totalSales;
    double avgSalesPerDay;
    int numCustomers;
};

struct Store{
    char sName[50];
    int sID;
    GeoCoordinates location;
    double monthlyCost;
    Employee manager;
    Employee* staff;
    Forecast sF;
    StoreAnalytics sA;
    int* customerCountMonthly;
    int numStaff;
    SalesData** sales;
    int productCount;    // check how much products is to be given to each store
    double* totalSales;   // calculates the total sales of each product in 2 year
    double avgSalesPerDay;     // find the average sales per day
};

struct SubCluster {
    char ID[10];
    char Name[50];
    Store* storesList; // Dynamic array of stores
    int numStores;     // Number of stores in this subcluster
    Centroid subCenter;
};

struct Cluster {
    char clb[10];
    char Name[50];
    SubCluster* subClusterList; // Dynamic array of subclusters
    int numSubClusters;         // Number of subclusters
    Centroid center;
};

struct Report{
	Store topscore;
	Store bottomscore;
};

// RANDOM PRODUCTS : This function initializes the 35 products assigning then SKU, Name and Unit Price
void generate_product(Product* product,const int MAX_PRODUCTS)
{
    char buffer[10];                  // Buffer is used to help in convert int to char      
	// Generating random Products for the stores 
	for(int i = 0;i < MAX_PRODUCTS; i++) 
	{
        intToStr(i+1,buffer);
		strcpy(product[i].SKU, "P");
        strcat(product[i].SKU, buffer);
        strcpy(product[i].pName, "Product_");
        strcat(product[i].pName, buffer);
        product[i].unitPrice = (rand() % 90) + 10;
    }
}

// RANDOM SALES : This Function initializes random sales with there date, total sales, and average sales per day (used in clustring )
void generate_random_sales(Store& store, Product* product,const int MONTHS, const int MAX_PRODUCTS)
{
	store.sales = new SalesData*[store.productCount];   // Dynamically Allocating Sales Data 
	char buffer[10];
	
	for(int i=0;i < store.productCount;i++)   // product count has been initialized below were the function is called
	{
        store.sales[i] =  new SalesData[MONTHS];
        
		for (int j = 0;j < MONTHS; j++) 
		{
            store.sales[i][j].storeID = store.sID;
            store.sales[i][j].product = product[rand() % MAX_PRODUCTS];
            
			if(j < 12) 
			{
                strcpy(store.sales[i][j].date, "2025-");
                intToStr((j % 12) + 1, buffer);
                strcat(store.sales[i][j].date, buffer);
                strcat(store.sales[i][j].date, "-15");
            } 
			else     // change the year after 12 months 
			{
                strcpy(store.sales[i][j].date, "2026-");
                intToStr((j % 12) + 1, buffer);
                strcat(store.sales[i][j].date, buffer);
                strcat(store.sales[i][j].date, "-15");
            }
			
            strcpy(store.sales[i][j].time, "10:00 AM");
        }
    }
    
    store.totalSales = new double[MONTHS];
    
	for(int i=0;i<MONTHS;i++)  // Generates random total sales
	{
    	store.totalSales[i] = (rand() % 40000) + 10000;
	}
	
	double totalSalesSum = 0;    // count the total sales to calculate the average
    for(int i=0;i < MONTHS;i++) 
	{
        totalSalesSum += store.totalSales[i];
    }
    store.avgSalesPerDay = totalSalesSum / 730.0;   // dividing by 730 because of 2 years time spam
}

// RANDOM EMPLOYEE : This first initializes a random of 15 employees and give it there salary and names
void generate_random_employee(Store& store)
{
    
	store.numStaff = (rand() % 11) + 5;   // Give a random Number of employee's to each store
    store.staff = new Employee[store.numStaff];
    char buffer[10];

    for(int i=0;i < store.numStaff;i++) 
	{
        store.staff[i].eID = store.sID + i;
        strcpy(store.staff[i].eName, "Employee");
        intToStr(store.sID, buffer);
        strcat(store.staff[i].eName, buffer);
        strcat(store.staff[i].eName, "_");
        intToStr(i + 1, buffer);
        strcat(store.staff[i].eName, buffer);
        store.staff[i].salary = (rand() % 10000) + 15000;   // random salaray to employee
    }
}

// RANDOM STORES : This function initializes the Stores give them a location there name and manager also assign each store with a random number of 
//                 of products to each store and there employees
void generate_random_stores(Store* store, Product* product, const int MAX_STORES, const int MONTHS)
{
    char buffer[10];
	for(int i=0;i < MAX_STORES;i++) 
	{
        store[i].sID = i + 1;
        strcpy(store[i].sName, "Store");
        intToStr(i + 1, buffer);
        strcat(store[i].sName, buffer);
        store[i].location.gLat = (rand() % 180) - 90 + (rand() % 1000) / 1000.0;     // let the location of the store 
        store[i].location.gLong = (rand() % 360) - 180 + (rand() % 1000) / 1000.0;
        store[i].monthlyCost = (rand() % 500000) + 200000;        // tells the monthly cost 
        store[i].manager.eID = i + 100;
        
		strcpy(store[i].manager.eName, "Manager");
        intToStr(i + 1, buffer);
        strcat(store[i].manager.eName, buffer);
        store[i].manager.salary = (rand() % 15000) + 25000;   // Manger salary being greater then the Employees 
        store[i].productCount = (rand() % 4) + 1;    // tells the random number of products assigned to each store

        generate_random_sales(store[i], product,MONTHS,MAX_STORES);   // Calls the above Functions with the generated data 
        generate_random_employee(store[i]);

    }
}

// EQCLIDEAN DISTANCE FOR CLUSTRING : Calculates the euclidean distance 
double euclidean_distance(const Store& store,const Centroid& centroid)
{
	
	int totalCustomers = 0;
    for(int i=0;i<24;i++) 
	{
        totalCustomers += store.customerCountMonthly[i];   // Adding total customers 
    }
    double avgCustomers = totalCustomers / 24;

    // Returning the distance for clustring
	return sqrt(pow(store.totalSales[0] - centroid.totalSales, 2) +
                pow(store.avgSalesPerDay - centroid.avgSalesPerDay, 2) +
                pow(avgCustomers - centroid.numCustomers, 2));
}

// K MEAN CLUSTRING METHORD 
/*
Done on the basis of:-
1. total sales
2. Average sales per day
3. Number of Customers
In this Func initially cluster's are compared with the center cluster and then the minimun distance one goes to that cluster then the function checks if there is a 
change in center if so then it repeats the entire steps and stores it in the subcluster structure
*/
void K_Clustring(Store* stores, int num_stores, Centroid* center_cluster, int num_centroid, Cluster* cluster, const int MONTHS, int max_iteration = 100, int current_iteration = 0) 
{
    
	if(current_iteration >= max_iteration) 
	{
        return;
    }

    for(int i=0;i < num_stores;i++) 
	{
        
		double min_distance = 1e9; // initially assign a large distance
        int index = -1;

        // Calculating the Minimum Distance and knowing its index to assign the stores to there nearest center 
		for(int j=0;j < num_centroid;j++) 
		{
            double distance = euclidean_distance(stores[i], center_cluster[j]);
            
            if(distance < min_distance) 
			{
                min_distance = distance;
                index = j;
            }
        }

        // Adding that store to the relevent Cluster
		SubCluster& sub_cluster = cluster[index].subClusterList[0];
        sub_cluster.storesList[sub_cluster.numStores++] = stores[i];
    }

    // In case changing the center if clustring is not occuring properly
	bool center_change = false;
    for(int i=0;i < num_centroid;i++) 
	{
        // finding total sales and averages to compare them with the clusters sales and averages is not matched then changing the cluster senter
		Centroid new_center = {0, 0, 0};
        int store_in_cluster = cluster[i].subClusterList[0].numStores;

        for(int j=0;j < store_in_cluster;j++) 
		{
            new_center.totalSales += cluster[i].subClusterList[0].storesList[j].totalSales[0];
            new_center.avgSalesPerDay += cluster[i].subClusterList[0].storesList[j].avgSalesPerDay;

            // Calculate the average number of customers
            int totalCustomers = 0;
            
            for(int k = 0; k < MONTHS;k++) 
			{
                totalCustomers += cluster[i].subClusterList[0].storesList[j].customerCountMonthly[k];
            }
            new_center.numCustomers += totalCustomers / MONTHS;
            
        }

        if(store_in_cluster > 0)    // checks that is there any data stored in the structure
		{
            new_center.totalSales /= store_in_cluster;
            new_center.avgSalesPerDay /= store_in_cluster;
            new_center.numCustomers /= store_in_cluster;
            
        }

        if(new_center.totalSales != center_cluster[i].totalSales ||
            new_center.avgSalesPerDay != center_cluster[i].avgSalesPerDay ||
            new_center.numCustomers != center_cluster[i].numCustomers) 
		{
            center_change = true;
        }

        center_cluster[i] = new_center;
    }

    // Checking if the center is changes or NOT
	if(center_change) 
	{
        for(int i=0;i < num_centroid;i++) 
		{
            cluster[i].subClusterList[0].numStores = 0; // clear stores for next iteration
        }

        // if center is changed repeat the entire steps with new center cluster
		K_Clustring(stores, num_stores, center_cluster, num_centroid, cluster, max_iteration, current_iteration + 1);
    }
}

// MAKING TEXT FILE FOR CLUSTERS: This is a simple file creating function whose job is to print the clusters in a seperate text file called as "clustered stores"
void cluter_textfile(const Cluster* clusters, int num_clusters,const int MONTHS) 
{
    
	ofstream outFile("Clustered Stores.txt");
    if(!outFile) 
	{
        cout<<"Error: Unable to open file"<<endl;
        return;
    }

    for(int i=0; i < num_clusters;i++) 
	{
        
		outFile<<"Clustered Data of URBANEASE STORE\n";
		outFile<<"-------------------------------------------\n";
        outFile<<"Centroid: ("<<clusters[i].center.totalSales<<", "<<clusters[i].center.avgSalesPerDay<<", "<<clusters[i].center.numCustomers<<")\n";

        for(int j=0;j < clusters[i].subClusterList[0].numStores;j++) 
		{
            // Calculate total sales for the store from the clustered data 
            double totalSales = 0;
            for(int k=0;k < MONTHS;k++) 
			{
                totalSales += clusters[i].subClusterList[0].storesList[j].totalSales[k];
            }

            // Calculate average number of customers for the store from the clustered data 
            int totalCustomers = 0;
            for(int k=0;k < MONTHS;k++) 
			{
                totalCustomers += clusters[i].subClusterList[0].storesList[j].customerCountMonthly[k];
            }
            double avgCustomers = totalCustomers / MONTHS;

            outFile<<"Store ID: "<<clusters[i].subClusterList[0].storesList[j].sID
                    <<" | Total Sales: "<<totalSales
                    <<" | Avg. Sales/Day: "<<clusters[i].subClusterList[0].storesList[j].avgSalesPerDay
                    <<" | Num Customers: "<<avgCustomers<<"\n";
        }
        outFile<<"\n";
    }

    outFile.close();
    cout<<"Clustering results have been written in 'Clustered Stores.txt'\n";
}

// RANKING REPORT
/*
Done on the basis of:
1. Total Sales       (30%)
2. Profit            (50%)
3. Operational Cost  (20%)
This is a ranking function is done on the above bases and the top and bottom store is first printed then top 10 and bottom 5 are printed in "Performance Report text file"
*/ 
void DataAnalyticRanking(Store* store,Report &report,const int MAX_STORES, const int MONTHS)
{
	
	double ranking[MAX_STORES];
	ofstream outFile("Performance Report.txt");
	if(!outFile)
	{
		cout<<"Error: Unable to open the file\n";
		return;
	}
	
	// A structure inside a function is defined which helps in ranking the stores
	struct rank{
		Store * store;
		double rank;
	};
	rank RANKING[MAX_STORES];

	// total sales remain same as the orignal total sales 
	for(int i=0;i<MAX_STORES;i++)
	{
		store[i].sA.totalsales = 0;
		for(int j=0;j<MONTHS;j++)
		{
			store[i].sA.totalsales += store[i].totalSales[j];
		}
	}
	
	// profit is calculated on the basess of difference betwrrn the sales and Operational cost 
	// Operational Cost is same as Monthly cost
	for(int i=0;i<MAX_STORES;i++)
	{
		store[i].sA.totaloperationalcost = store[i].monthlyCost;
		// check if there is any profit if not them let it be zero else let it be the difference
		store[i].sA.profit = (store[i].sA.totalsales > store[i].sA.totaloperationalcost) ?  (store[i].sA.totalsales - store[i].sA.totaloperationalcost) : 0;
		
	}
	
	// storing the ranking values for each store
	for(int i=0;i<MAX_STORES;i++)
	{
		ranking[i] = ((store[i].sA.profit * 0.50) +  (store[i].sA.totalsales * 0.30) - (store[i].sA.totaloperationalcost * 0.20));
		RANKING[i].store = &store[i];
		RANKING[i].rank = ranking[i]; 
	}
	
	int top_index=0 , bottom_index = 0;     // for top and bottom rank
	double max=ranking[0] , min= ranking[0];
	for(int i=1;i<MAX_STORES;i++)
	{
		if(ranking[i]>max)
		{
			max = ranking[i];
			top_index = i;
		}
		
		if(ranking[i] < min) 
		{
            min = ranking[i];
            bottom_index = i;
        }
	}

	 //for ranking sorting the data 
	for(int i=0;i<MAX_STORES-1;i++)
	{
		for(int j=i+1;j<MAX_STORES;j++)
		{
			if(RANKING[i].rank < RANKING[j].rank)
			{
				rank temp = RANKING[i];
				RANKING[i] = RANKING[j];
				RANKING[j] = temp;
			}
		}
	}
	
	// assign the top and bottom values to the report structure
	report.topscore = store[top_index];
	report.bottomscore = store[bottom_index];
	
	outFile<<"Top Performance :\n";
    outFile<<"-------------------------------------------\n";
    outFile<<"Store ID: "<<store[top_index].sID<<"\n";
    outFile<<"Store Name: "<<store[top_index].sName<<"\n";
    outFile<<"Total Sales: "<<store[top_index].sA.totalsales<<"\n";
    outFile<<"Profit: "<<store[top_index].sA.profit<<"\n";
    outFile<<"Operational Cost: "<<store[top_index].sA.totaloperationalcost<<"\n";
    outFile<<"Score: "<<max<<"\n\n";
    
    outFile<<"\nBottom Store:\n";
    outFile<<"-----------------------------------------\n";
    outFile<<"Store ID: "<<store[bottom_index].sID<<"\n";
    outFile<<"Store Name: "<<store[bottom_index].sName<<"\n";
    outFile<<"Total Sales: "<<store[bottom_index].sA.totalsales<<"\n";
    outFile<<"Profit: "<<store[bottom_index].sA.profit<<"\n";
    outFile<<"Operational Cost: "<<store[bottom_index].sA.totaloperationalcost << "\n";
    outFile<<"Score: "<<min<<"\n\n";
    
    // Displays thr top 10 stores after the ranking and sorting 
	outFile<<"Top 10 Stores with highest Ranking are:\n";
	outFile<<"---------------------------------------\n";
	for(int i=0;i<10;i++)
	{
		outFile<<i+1<<". "<<RANKING[i].store->sName<<" | Profit: "<<RANKING[i].store->sA.profit<<" | Total Sales: "<<RANKING[i].store->sA.totalsales<<"\n";
	}
	
	// Display the bottom five stores 
	outFile<<"\nBottom 5 Stores (Struggling Locations):\n";
    outFile<<"-----------------------------------------\n";
    for(int i = MAX_STORES - 5; i < MAX_STORES;i++) 
	{
        outFile<<MAX_STORES - i<<". "<<RANKING[i].store->sName<<" | Profit: "<<RANKING[i].store->sA.profit<<" | Total Sales: "<<RANKING[i].store->sA.totalsales<<"\n";
    }
    
	outFile.close();
    cout<<"\nPerformance Report has been generated in 'Performance_Report.txt'"<<endl;
}

// FUTURE FORECAST PREDICTION : this function predicts the future sales there warning and confidence level.
/*
1. Moving average is used to calculate predicted sales.
2. warning is displayed if the sales are continuously decreasing for the last 2 months
3. confidence level is calculated by linear regression and coieffcient of determination
*/
void futuresales(Store* store, const int MAX_STORES, const int MONTHS) 
{
    const int SEASONAL_MONTHS[] = {3,5,12,14};
	ofstream outFile("Future Sales Forecast.txt");
    if(!outFile) 
	{
        cout<<"Error: Unable to open the file\n";
        return;
    }

    for(int i = 0;i<MAX_STORES;i++) 
	{
        double movingAverage = 0.0;
        int count = 5; // Using 5 months for moving average

        // Calculating moving average 
        for(int j = MONTHS - count;j < MONTHS;j++) 
		{
            movingAverage += store[i].totalSales[j];
        }
        
        movingAverage /= count;
        store[i].sF.predictedsales = movingAverage;

        // Seasonal jumps 
		for(int j = 0;j<4;j++) 
		{
            if(SEASONAL_MONTHS[j] < MONTHS) 
			{
                store[i].sF.predictedsales *= 1.5;
            }
        }

        // Confidence level calculation using linear regression
        double sum_x = 0.0, sum_y = 0.0, sum_x2 = 0.0, sum_xy = 0.0;
        int n = 12; 

        for(int j = MONTHS - n;j < MONTHS;j++) 
		{
            double x = j - (MONTHS - n);     // TIME 0-11
            double y = store[i].totalSales[j];   // Sales
            sum_x += x;
            sum_y += y;
            sum_xy += x * y;
            sum_x2 += x * x;
        }

        double slope = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);  // slope = m
        double intercept = (sum_y - slope * sum_x) / n;   // intercept = c

        // coefficient of determination methord
		double sstotal = 0.0, ssresidual = 0.0;  // total sum of square calculates the total variation of y
        double mean_Y = sum_y / n; 

        for(int j = MONTHS - n;j < MONTHS;j++) 
		{
            double x = j - (MONTHS - n);
            double y = store[i].totalSales[j];
            double y_prediction = slope * x + intercept;   // y = mx + c (determines the slope i.e prediction)
            sstotal += pow(y - mean_Y, 2);               // total sum is calculated
            ssresidual += pow(y - y_prediction, 2);    // sum of square residual is calculated
        }

        double r_square = 1 - (ssresidual / sstotal);  // calculate the R_SQUARE or coeiffient of determination
        store[i].sF.confidancelevel = r_square * 100;  // convert to percent

        // Display a warning message if the sales are decreasing continuously from the past two months 
		store[i].sF.warning = (store[i].totalSales[MONTHS - 1] < store[i].totalSales[MONTHS - 2]); 

        outFile<<"Store ID: "<<store[i].sID<<"\n";
        outFile<<"Predicted Sales for next five Months: "<<store[i].sF.predictedsales<<"\n";
        outFile<<"Confidence Level: "<<store[i].sF.confidancelevel<<"%\n";
        outFile<<"Warning Flag: "<<(store[i].sF.warning ? "Yes" : "NO")<<"\n";
        outFile<<"-----------------------------------\n";
    }

    outFile.close();
    cout<<"\nFuture Forecast has been generated in 'Future Forecast.txt'"<<endl;
}

// STORING GENERATED DATA IN TEXT FILE : this is the text file generator for task 1 which creates the text file for the stores data
void save_file(Store* stores,const int MAX_STORES, const int MONTHS) 
{
	
    ofstream outFile("UrbanEase_data.txt");
    if (!outFile) 
	{
        cout<<"Error: Unable to open file for writing.\n";
        return;
    }

    // Display the generated data 
	for(int i = 0;i < MAX_STORES; i++) {
        outFile<<"Store ID: "<<stores[i].sID<<"\n";
        outFile<<"Name: "<<stores[i].sName<<"\n";
        outFile<<"Location: "<<stores[i].location.gLat<<", "<<stores[i].location.gLong<<"\n";
        outFile<<"Manager: "<<stores[i].manager.eName<<" (ID: "<<stores[i].manager.eID<<")\n";
        outFile<<"Monthly Cost: "<<stores[i].monthlyCost<<"\n";
        outFile<<"Total Products Assigned: "<<stores[i].productCount<<"\n"<<endl;

		for(int j = 0;j < stores[i].productCount;j++) 
		{
			stores[i].customerCountMonthly = new int[MONTHS];  // Dynamically assigning value to Customer count
			double average=0.0;
			outFile<<"\n  Product: "<<stores[i].sales[j][0].product.pName<<" (SKU: "<<stores[i].sales[j][0].product.SKU<<") (Unit Price:  "<<stores[i].sales[j][0].product.unitPrice<<")\n";
			outFile<<endl;

            for(int k = 0;k < MONTHS; k++) 
			{
				stores[i].customerCountMonthly[k] = (rand() % 500) + 100;   // Randomlly assigning them values
				// calculating the total sales amount using the formula:
				// TOTAL SALES AMOUNT = AVERAGE OF PRODUCTS PER STORE INTO THE MONTHLY COUNT 
				average += stores[i].sales[j][0].product.unitPrice/stores[i].productCount;
				stores[i].sales[j][k].totalSaleAmount = average * stores[i].customerCountMonthly[k];
				
				outFile<<"    Month: "<<stores[i].sales[j][k].date<<" |  Time: "<<stores[i].sales[j][k].time<<" | Sales: "<<stores[i].sales[j][k].totalSaleAmount<<"\n";
            }
        }

        // Displaying the Employee data 
		outFile<<"\nEmployees ("<<stores[i].numStaff<<"):\n";
        
		for(int j = 0; j < stores[i].numStaff; j++) 
		{
            outFile<< "  - "<<stores[i].staff[j].eName<<" (ID: "<<stores[i].staff[j].eID<<") | Salary: "<<stores[i].staff[j].salary<<"\n";
        }

        // Displaying the customer count
		outFile<<"\nCustomer Count per Month:\n";
        
        for (int j = 0;j < MONTHS;j++) 
		{
			outFile<<"  Month "<<(j + 1)<<": "<<stores[i].customerCountMonthly[j]<<" customers\n";
        }

        outFile<<"-----------------------------\n";
    }

    outFile.close();
    cout<<"Data successfully stored in 'UrbanEase_data.txt' \n";
}

// UPDATE STORES DATA DETAIL : Allows the user to update any currently generated stores data i.e Monthly cost and Manager Name
void updateStore(Store* stores, int count,const int MONTHS)
{
    int sID;
    top:
    cout<<"Enter Store ID (1-100) to update: ";
    cin>>sID;
    if(sID<0 || sID >100)
	{
    	cout<<"------Invalid Input-------"<<endl;
    	goto top;
	}
                              // Comapare the stores id and and user id if found update it else show and error message
    bool found = false;
    for(int i = 0;i < count; i++) 
	{
        if (stores[i].sID == sID) 
		{
            found = true;
            cout<<"Updating Store: "<<stores[i].sName<<endl;
            cout<<"Enter new Monthly Cost: ";
            cin>>stores[i].monthlyCost;
            
            while(stores[i].monthlyCost < 1)
			{
            	cout<<"Enter a valid Monthly Cost."<<endl;
            	cout<<"Enter new Monthly Cost: ";
            	cin>>stores[i].monthlyCost;
			}
			
            cout<<"Enter new Manager Name: ";
            cin.ignore();  
            cin.getline(stores[i].manager.eName,10);

            cout<<"Store updated successfully.\n";
            save_file(stores,count,MONTHS);  // updating the Urban ease text file
            return;
        }
    }

    if(!found)
	{
        cout<<"Store ID not found!\n";
    }
}

// FREEING ALL THE MEMBER SPACES : this function frees all the Dynamically Allocated Memory
void freeMemory(Store* stores,const int MAX_STORES) 
{
    for(int i=0;i<MAX_STORES;i++) 
	{
        for(int j=0;j < stores[i].productCount;j++) 
		{
            delete[] stores[i].sales[j];
        }
        
		delete[] stores[i].staff;
        delete[] stores[i].customerCountMonthly;
        delete[] stores[i].totalSales;
        
        delete[] stores[i].sales;
    }
}

// BONUS GRAPH FUNC 1 : this print the graph for the first bonus i.e. monthly sales
void drawBarGraph(int data[], string labels[], int size, int size2) 
{  
	// Find max value 
    int maxValue = 1; 
    
    for(int i=0;i< size2;i++) 
	{
        if(data[i] > maxValue) 
		{
            maxValue = data[i];
        }
    }

    // Taking an set height for overall bar graph 
	int maxHeight = 20; 
    double scale = (double)maxHeight / maxValue; // Scaling the height according to the set height 

    // Print the bars from top to bottom
    for(int i=maxHeight;i>0;i--) 
	{
        for(int j=0;j < size2;j++) 
		{
            if(i <= data[j] * scale) 
			{
                cout<<"  *  "; 
            } 
			else 
			{
                cout<<"     "; 
            }
        }
        cout<<endl;
    }

    cout<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
    
    // Print month labels below bars
    for(int i=0;i < size;i++) 
	{
        cout<<" "<<labels[i]<<" ";
    }
    for(int i=0;i < size;i++)   // printing the months twice because of 24 months sales 
	{
        cout<<" "<<labels[i]<<" ";
    }
    cout<<endl;
}

// BONUS GRAPH FUNC 2 : this function calls the above function for printing this function consists of the user id where the sales are to be printed
//                      and pass the months and sales
void bonus_graph(Store* store, int count) 
{
    int id;
    goback:
    cout<<"Enter Store ID whose graph is to be made (1 to "<<count<<"): ";
    cin>>id;

    if(id<1 || id>count) 
	{
        cout << "Invalid Store ID! Please try again."<<endl;
        goto goback;
    }

    int index = id - 1;   // -1 is done to convert it into array index
    // Displaying error message if stores are not generated
    if(store[index].sales == NULL) 
	{
        cout<<"OOPS! No sales data available for this store!"<<endl;
        return;
    }

    int monthlySales[24] = {0};   // bar graph is printed on monthly sales basis 

    for(int i=0;i<24;i++) 
	{
        for(int j=0;j < store[index].productCount;j++) 
		{
            monthlySales[i] += store[index].sales[j][i].totalSaleAmount;
        }
    }

    string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
                         "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    cout<<"\nMonthly Sales Trends for Store "<<id<<" ("<<store[index].sName<<"):"<<endl;
    
    drawBarGraph(monthlySales, months, 12, 24);
}


int main() 
{
	
	srand(time(0));
	const int MAX_STORES = 100;
	const int MAX_PRODUCTS = 35;
	const int MONTHS = 24;
	int choice ;
	char update ;
    Store* stores = new Store[MAX_STORES];         // Dynamically Allocating Stores
    Product* products = new Product [MAX_PRODUCTS];   //Dynamically Allocating Products
    Report r;
    Centroid center_cluster[3] =     // Creating a center cluster for clustring 
    {
    	{20000,150,1000},
    	{30000,200,3500},
    	{35000,400,4000}
	};
	int num_centroid = sizeof(center_cluster)/ sizeof(center_cluster[0]);   // determining the size of the center cluster
	
	// Simply Initializing the clusters 
	Cluster clusters[num_centroid];
	for(int i=0;i<num_centroid;i++)
	{
		strcpy(clusters[i].clb, "C1");
        strcpy(clusters[i].Name, "Cluster");
        clusters[i].subClusterList = new SubCluster[1];    //Dynamically initializing the Sub clusters
        clusters[i].subClusterList[0].storesList = new Store[MAX_STORES];         //Dynamically initializing the Sub clusters store list
        clusters[i].subClusterList[0].numStores = 0;
        clusters[i].center = center_cluster[i];
	}
	
    while(true)
	{
    	cout<<"\n\t\t\t\t\t   URBAN EASE STORE ANALATICS."<<endl;
    	cout<<"1. Genererate Data."<<endl;
    	cout<<"2. Update Data."<<endl;
    	cout<<"3. Print the Clustered Data"<<endl;
    	cout<<"4. Print Future Forecast."<<endl;
    	cout<<"5. Generate Data Analytic Report"<<endl;
    	cout<<"6. Show bar graph"<<endl;
    	cout<<"7. Exit"<<endl;
    	cout<<"\nEnter Choice: ";
    	cin>>choice;
    	
		while(choice<1 || choice>7)    // Validation Check
		{
    		cout<<"-------Invalid Choice Entered--------"<<endl;
    		cout<<"\nEnter Choice: ";
    		cin>>choice;
		}
		
    	switch(choice)
		{
			case 1:
			{
				generate_product(products, MAX_PRODUCTS);
            	generate_random_stores(stores, products, MAX_STORES,MONTHS);    //generating data and storing in file 
            	save_file(stores,MAX_STORES,MONTHS);
				break;
			}
			
			case 2:
			{
				back:
				cout<<"\nDo you want to update any store detail, (Y,N): ";
           		cin>>update;
            	if(update == 'y' || update == 'Y')
				{
    	    		updateStore(stores,MAX_STORES,MONTHS);      // Updating generated stores data
        		}
        		else if(update == 'n' || update == 'N' )
				{
        			break;
				}
				else
				{
					cout<<"----Invalid Option------"<<endl;
        			goto back;
				}
				break;
			}
			
			case 3:
			{
				K_Clustring(stores,MAX_STORES,center_cluster,num_centroid,clusters,MONTHS);    // Creating clusters and saving in a seperate text file
				cluter_textfile(clusters,num_centroid,MONTHS);
				break;
			}
			
			case 4:
			{
				futuresales(stores,MAX_STORES,MONTHS);    // predicting future sales
				break;
			}
			
			case 5:
			{
				DataAnalyticRanking(stores,r,MAX_STORES,MONTHS);   //showing ranking report
				break; 
			}
			
			case 6:
			{
				bonus_graph(stores,MAX_STORES);   // making bar graph of desired store monthly sales 
				break;
			}
			
			case 7:
			{
				cout<<"Have a nice day GOOD BYE!!"<<endl;     // Exiting program and deleting DMA storage 
				freeMemory(stores,MAX_STORES);
				delete [] stores;
				delete [] products;
				for(int i = 0; i < num_centroid;i++) 
				{
        			delete[] clusters[i].subClusterList[0].storesList;
       				delete[] clusters[i].subClusterList;
    			}
				return 0;
				break;
			}
		}
	}
}
