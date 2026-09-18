#include <stdio.h>
#include <stdlib.h>

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
