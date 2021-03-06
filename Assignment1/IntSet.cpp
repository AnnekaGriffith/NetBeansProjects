// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
//  Name: Anneka Bath- CS 3358
//  Date: 1/31/18
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     compile-time array whose size is IntSet::MAX_SIZE;
//     the member variable data references the array.
// (2) The distinct int value with earliest membership is stored
//     in data[0], the distinct int value with the 2nd-earliest
//     membership is stored in data[1], and so on.
//     Note: No "prior membership" information is tracked; i.e.,
//           if an int value that was previously a member (but its
//           earlier membership ended due to removal) becomes a
//           member again, the timing of its membership (relative
//           to other existing members) is the same as if that int
//           value was never a member before.
//     Note: Re-introduction of an int value that is already an
//           existing member (such as through the add operation)
//           has no effect on the "membership timing" of that int
//           value.
// (4) The # of distinct int values the IntSet currently contains
//     is stored in the member variable used.
// (5) Except when the IntSet is empty (used == 0), ALL elements
//     of data from data[0] until data[used - 1] contain relevant
//     distinct int values; i.e., all relevant distinct int values
//     appear together (no "holes" among them) starting from the
//     beginning of the data array.
// (6) We DON'T care what is stored in any of the array elements
//     from data[used] through data[IntSet::MAX_SIZE - 1].
//     Note: This applies also when the IntSet is empry (used == 0)
//           in which case we DON'T care what is stored in any of
//           the data array elements.
//     Note: A distinct int value in the IntSet can be any of the
//           values an int can represent (from the most negative
//           through 0 to the most positive), so there is no
//           particular int value that can be used to indicate an
//           irrelevant value. But there's no need for such an
//           "indicator value" since all relevant distinct int
//           values appear together starting from the beginning of
//           the data array and used (if properly initialized and
//           maintained) should tell which elements of the data
//           array are actually relevant.

#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

IntSet::IntSet(): used(0){}

int IntSet::size() const
{
    // Gets the size of the array 
    return used;
}

bool IntSet::isEmpty() const
{
    if (size() > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool IntSet::contains(int anInt) const
{
    if (0 == size())
    {
        return false;
    }
    else
    {
        for(int i = 0;i <size(); i++)
        {
            if (anInt == data[i])
            {
                return true;
            }
        } 
        return false;
    }
    
}

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{
    int i= 0,
        j =0;
    for(i; i<size(); i++)
    {
        for(j; j < size(); j++)
        {
            if (data[j] == otherIntSet.data[i])
                break; //breaks inner most loop 
        }
        if (i == size())
        {
            cout << "Not a subset" << endl;
            return false; //element from OtherIntSet wasn't in IntSet thus false
        }
    }
    cout << "is a subset" << endl;
    return true;
}

void IntSet::DumpData(ostream& out) const
{  // already implemented ... DON'T change anything
    if (used > 0)
    {
        out << data[0];
        for (int i = 1; i < used; ++i)
        out << "  " << data[i];
    }
}

IntSet IntSet::unionWith(const IntSet& otherIntSet) const
{
    IntSet dataLoad = *this;

    if (size() + (otherIntSet.subtract(*this)).size() <= MAX_SIZE)
    {
        for (int i = 0; i < otherIntSet.size(); ++i)
        {
            dataLoad.add(otherIntSet.data[i]);     
        }
    }
    return dataLoad;
}

IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
    IntSet dataLoad = *this;
    for (int i = 0; i < dataLoad.size(); i++)
    {
        if ((otherIntSet.contains(dataLoad.data[i])) == false)
            cout << dataLoad.data[i]<< endl;
            dataLoad.remove(dataLoad.data[i]);

    }
    return dataLoad; // 
}

IntSet IntSet::subtract(const IntSet& otherIntSet) const
{
    IntSet dataLoad = *this;
    for (int i = 0; i > dataLoad.size(); ++i)
    {
        if ((otherIntSet.contains(dataLoad.data[i])) == true)
        {
            dataLoad.remove(dataLoad.data[i]);
        }
    }
   return dataLoad; //returns the difference between invoking and otherIntSet
}

void IntSet::reset()
{
    if (isEmpty()== true)
    {
        cout << "set is  is empty" << endl;
    }
    else
    {
        while(isEmpty() == false)
        {
            int i =0;
            remove(data[i]);
            i++;
        }
        
    }
}

bool IntSet::add(int anInt)
{
    if(contains(anInt) == false && size() <= MAX_SIZE)
    {
        data[size()] = anInt;
        cout << data[size()]<< endl;
        used++;
        return true;
    }
    else
        false;
}

bool IntSet::remove(int anInt)
{
    if (contains(anInt) == true)
    {
        for (int i= 0 ; i<size(); i++)
        {
            this->data[i]= data[i+1];//this data is now data-1 space in the array
            used--;
            return true;
        }
    }
    else 
    {
        cout <<"not here"<< endl;
        return false;
    }
}

bool equal(const IntSet& is1, const IntSet& is2)
{
    if(is1.size()== 0 && is2.size() == 0)
        return true;
    
    else
    {
        for (int i =0; i<is1.size(); i++)
        {
            for (int j =0; j<is2.size(); j++)
            {
                if (is1.contains(i) == is2.contains(j))
                    break;
                else
                    return false;
            }
        }
        return true;
    }
}
