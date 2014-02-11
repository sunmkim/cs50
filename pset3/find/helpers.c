/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
 
// Recursive helper function for binary search 
bool recursion(int value, int values[], int upper, int lower)
{
    // If array of one element
    if (upper - lower == 0)
    {
        if (value == values[upper])
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    int midpoint = (lower + upper )/ 2;
    
    // Search lower half
    if (value <= values[midpoint])
    {
        return recursion(value, values, midpoint, lower);
    }
    
    // Search upper half
    else if (value > values[midpoint])
    {
        return recursion(value, values, upper, midpoint + 1);
    }
    
    return false;
}
    
    
bool search(int value, int values[], int n)
{   
    return recursion(value, values, n-1, 0);   
}


/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    for (int i = 0; i < n-1; i++)
    {
        int min_val = i;
        for (int j = i+1; j < n; j++)
        {
            if (values[j] < min_val)
            {
                min_val = values[j];
            }
        }
        if (min_val != i)
        {
            min_val = values[i];
        }
    }
    return;
}
