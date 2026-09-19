#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Patient Data
//100 means that our system can store up to 100 patients.

char patientName[100][50];
int patientAge[100];
int urgencyLevel[100];
int specialtyID[100];
int wardID[100];
int daysAdmitted[100];
int registrationOrder[100];
int bedNumber[100];
int patientCount = 0;

//Doctor Specialties

const char *specialtyName[4] = {"Cardiology","Neurology","Paediatrics","General Medicine"};
const double specialtyFee[4] = {5000.0, 4500.0, 4000.0, 3000.0};
const int consultationTime[4] = {20, 25, 15, 10};
const int patientCap[4] = {10, 8, 12, 15};

//Hospital Wards

const char *wardName[4] = {"General Ward", "Private Ward", "Paeditratics Ward", "Emergency Ward"};
const double wardRate[4] = {3000.0, 6000.0, 4000.0, 5000.0};
const int wardCapacity[4] = {20,15,20,10};

//Bed Occupancy

int bedOccupancy[4][20];//4 means 4 wards and 20 means that each ward can have up to 20 beds.
int bedOccupancy[4][20] = {0};//When the hospital system starts, all beds should be available. For that we use {0}//

//Store the Billing values in arrays.

double baseFee[100];
double emergencySurcharge[100];
double wardCost[100];
double grossTotal[100];
double ageDiscount[100];
double finalPayable[100];
double waitTime[100];


//Bed Allocation

int allocateBed(int patientIndex)
{
    int wardIndex = wardID[patientIndex] - 1;

    for(int i =0; i < wardCapacity[wardIndex]; i++)
    {
        if(bedOccupancy[wardIndex][i] == 0)
        {
            bedOccupancy[wardIndex][i] = 1;
            bedNumber[patientIndex] = i + 1;

            return 1;
        }
    }

    return 0;
}

//Billing Calculations

    ///Base Fee///

double calculateBaseFee(int patientIndex)
{
    int specialtyIndex = specialtyID[patientIndex] - 1;

    return specialtyFee[specialtyIndex];
}

    ///Emergency Surcharge = Base fee * surcharge rate///

 double calculateSurcharge(int patientIndex)
 {
     double rate;

     if(urgencyLevel[patientIndex] == 1)
    {
        rate = 0.00;

    } else if(urgencyLevel[patientIndex] == 2)
    {
        rate = 0.20;
     }
     else
     {
         rate = 0.50;
     }

     return baseFee[patientIndex] * rate;
 }

    ///Ward Cost = Number of admitted days * Ward daaily rate///

double calculateWardCost(int patientIndex)
{

    int wardIndex = wardID[patientIndex] - 1;

    return daysAdmitted[patientIndex] * wardRate[wardIndex];

}

    ///Gross Total = Base fee + Emergency surcharge + Ward cost///

double calculateGrossTotal(int patientIndex)
{

    return baseFee[patientIndex] + emergencySurcharge[patientIndex] + wardCost[patientIndex];

}


    ///Age Discount///

double calculateAgeDiscount(int patientIndex)
{
    if(patientAge[patientIndex] < 5 || patientAge[patientIndex] > 65)
    {
        return grossTotal[patientIndex] * 0.15;

    }

    return 0.0;
}

    ///Final Payable Amount = Gross total - Age discount///

double calculateFinalPayable(int patientIndex)
{
    return grossTotal[patientIndex] - ageDiscount[patientIndex];
}


    ///Wait Time = Queue Count * Average Time per Patient///

//Queue count calculation function

int calculateQueueCount(int patientIndex)
{

    int count = 0;

    for(int i = 0; i < patientIndex; i++)
    {

        if(specialtyID[i] == specialtyID[patientIndex])
        {
            count++;
        }

    }

    return count;
}

//wait time function

double calculateWaitTime(int patientIndex)
{

    int queueCount = calculateQueueCount(patientIndex);

    int specialtyIndex = specialtyID[patientIndex] - 1;

    return queueCount * consultationTime[specialtyIndex];
}

///Patients sorting by states named Critical, Urgent and Normal///

//Swap Patients

void swapPatients(int i, int j)
{
    char tempName[50];
    int tempInt;
    double tempDouble;

 //SWAP patient names

    strcpy(tempName, patientName[i]);
    strcpy(patientName[i], patientName[j]);
    strcpy(patientName[j], tempName);

 //SWAP integer data

    tempInt = patientAge[i];
    patientAge[i] = patientAge[j];
    patientAge[j] = tempInt;

    tempInt = urgencyLevel[i];
    urgencyLevel[i] = urgencyLevel[j];
    urgencyLevel[j] = tempInt;

    tempInt = specialtyID[i];
    specialtyID[i] = specialtyID[j];
    specialtyID[j] = tempInt;

    tempInt = wardID[i];
    wardID[i] = wardID[j];
    wardID[j] = tempInt;

    tempInt = daysAdmitted[i];
    daysAdmitted[i] = daysAdmitted[j];
    daysAdmitted[j] = tempInt;

    tempInt = registrationOrder[i];
    registrationOrder[i] = registrationOrder[j];
    registrationOrder[j] = tempInt;

    tempInt = bedNumber[i];
    bedNumber[i] = bedNumber[j];
    bedNumber[j] = tempInt;

 //SWAP billing data

    tempDouble = baseFee[i];
    baseFee[i] = baseFee[j];
    baseFee[j] = tempDouble;

    tempDouble = emergencySurcharge[j];
    emergencySurcharge[i] = emergencySurcharge[j];
    emergencySurcharge[j] = tempDouble;

    tempDouble = wardCost[i];
    wardCost[i] = wardCost[j];
    wardCost[j] = tempDouble;;

    tempDouble = grossTotal[i];
    grossTotal[i] = grossTotal[j];
    grossTotal[j] = tempDouble;

    tempDouble = ageDiscount[i];
    ageDiscount[i] = ageDiscount[j];
    ageDiscount[j] = tempDouble;

    tempDouble = finalPayable[i];
    finalPayable[i] = finalPayable[j];
    finalPayable[j] = tempDouble;

    tempDouble = waitTime[i];
    waitTime[i] = waitTime[j];
    waitTime[j] = tempDouble;

}

void sortPatients()
{
   for(int i =0; i < patientCount - 1; i++)
    {

        for(int j = 0; j < patientCount - i; j++)
        {

            if(urgencyLevel[j] < urgencyLevel[j + 1] || (urgencyLevel[j] == urgencyLevel[j + 1] && registrationOrder[j] > registrationOrder[j + 1]))
                {
                    swapPatients(j, j+1);

                }

        }


    }

}


//Patient Intake & Registration

void registerPatient()
{
//Registration form.

    printf("--- PATIENT REGISTRATION ---\n");

    //Name Input
    printf("Enter patient name: ");

    scanf(" %[^\n]", patientName[patientCount]);

    //Age Input
    printf("Enter age: ");

    scanf("%d", &patientAge[patientCount]);

    //Urgency Level
    printf("Enter urgency level (1=Normal, 2=Urgent, 3=Critical): ");

    scanf("%d", &urgencyLevel[patientCount]);

    //specialtyID Input
    printf("Enter specialty ID (1-4): ");

    scanf("%d", &specialtyID[patientCount]);

    //WardID Input
    printf("Enter ward ID (1-4): ");

    scanf("%d", &wardID[patientCount]);

    //Admitted Date Input
    printf("Enter number of days admitted: ");

    scanf("%d", &daysAdmitted[patientCount]);

    //Assign the registration order automatically

    registrationOrder[patientCount] = patientCount + 1;

    //Increase the patient count

    patientCount++;

    //Bed allocation
    if(allocateBed(patientCount))
    {

        printf("BED ALLOCATED SUCCESSFULLY.\n");
    }
    else
    {
        printf("NO BED AVAILABLE IN THE SELECTED WARD.\n");

        return;
    }

    //Billing calculations

    baseFee[patientCount] = calculateBaseFee(patientCount);

    emergencySurcharge[patientCount] = calculateSurcharge(patientCount);

    wardCost[patientCount] = calculateWardCost(patientCount);

    grossTotal[patientCount] = calculateGrossTotal(patientCount);

    ageDiscount[patientCount] = calculateAgeDiscount(patientCount);

    finalPayable[patientCount] = calculateFinalPayable(patientCount);

    waitTime[patientCount] = calculateWaitTime(patientCount);

    printf("--- PATIENT REGISTERED SUCCESSFULLY. --- \n");

}

/// Bill Display/Bill Summary ///

void displayBill(int patientIndex)
{
    int specialtyIndex;
    int wardIndex;

    specialtyIndex = specialtyID[patientIndex] - 1;
    wardIndex = wardID[patientIndex] - 1;

    printf("=======================================================\n");
    printf("                    PATIENT BILL\n                      ");
    printf("========================================================\n");

    printf("Patient Name        : %s\n", patientName[patientIndex]);

    printf("Age                 : %d\n", patientAge[patientIndex]);

    printf("Urgency Level       : %d\n", urgencyLevel[patientIndex]);

    printf("Specialty           : %s\n", specialtyName[specialtyIndex]);

    printf("Ward                : %s\n", wardName[wardIndex]);

    printf("Bed Number          : %d\n", bedNumber[patientIndex]);

    printf("Days Admitted       : %d\n", daysAdmitted[patientIndex]);

    printf("Estimated Wait Time : %.2f minutes\n", waitTime[patientIndex]);

    printf("-------------------------------------------------------------------");

    printf("Base Fee            : Rs.%.2f\n", baseFee[patientIndex]);

    printf("Emergency Surcharge : Rs.%.2f\n", emergencySurcharge[patientIndex]);

    printf("Ward Cost           : Rs.%2f\n", wardCost[patientIndex]);

    printf("Gross Total         : Rs.%.2f\n", wardCost[patientIndex]);

    printf("Age Discount        : Rs.%.2f\n", ageDiscount[patientIndex]);

    printf("-------------------------------------------------------------------");

    printf("Final payable       : Rs.%.2f\n", finalPayable[patientIndex]);

    printf("============================= END =================================\n");
}


int main()
{
    registerPatient();
    registerPatient();
    registerPatient();

    sortPatients();

    for(int i = 0; i < patientCount; i++)
    {
        displayBill(i);
    }

    return 0;
}
