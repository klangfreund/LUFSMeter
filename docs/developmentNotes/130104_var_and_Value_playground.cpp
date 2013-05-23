/*
  ==============================================================================

    author: Samuel Gaehwiler (klangfreund.com)

    Just playing around to get familiar with storing arrays in var and Value
    objects.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>
using namespace std;


//==============================================================================
int main (int argc, char* argv[])
{
    cout << "------------------" << endl;
    cout << "Various var's     " << endl;
    cout << "------------------" << endl;
    
    var aVar;
    aVar.append (1.2);  // This also converts the value inside the var
                        // to an Array<var>.
    aVar.append (2.2);
    aVar.append (3.2);

    double d0 = aVar.getArray()->getReference (0);
        // Like ...getUnchecked(0), but returns a direct reference to
        // the element, so that you can alter it directly (dangerous).
    double d1 = aVar[1];   // Does EXACTLY the same as the line above
                            // ( getArray()->getReference (1) ),
                            // but looks nicer. :)
    cout << "first value = " << d0 << endl;
    cout << "second value = " << d1 << endl;

    // Overwrite a value.
    aVar[2] = 4.2;
    cout << "third value = " << double (aVar[2]) << endl;

    // Overwrite a value with another type.
    aVar[2] = "Hi there.";
    cout << "third value = " << aVar[2].toString() << endl; // << endl;
        // Can't use String (aVar[2]) here because String(juce::var&)
        // is ambiguous at compilation time.
    
    
    
    
    
    cout << "------------------" << endl;
    cout << "Evaluating Values." << endl;
    cout << "------------------" << endl;
    
    
    const Array<var> tempArrayOfVars;
    var tempVar (tempArrayOfVars);
    Value valery (tempVar); // valery now contains a copy of v.
    
    valery.getValue().append(0.0);
        // This does NOT WORK, since getValue returns a
        // copy of its var.
    cout << "valery is an Array = " << valery.getValue().isArray() << endl;
    cout << "valery.getValue().size() =" << valery.getValue().size() << endl;
    
    // It's only possible to change a Value by using setValue or the operator=.
    tempVar.append (0.1);
    tempVar.append (1.1);
    valery.setValue (tempVar);
    cout << "valery.getValue().size() =" << valery.getValue().size() << endl;
    
    tempVar[0] = 0.2;
    tempVar[1] = 1.2;
    cout << "valery.getValue()[0] = " << double (valery.getValue()[0]) << endl;
    
    valery = tempVar; // SET A BREAKPOINT AND STEP INTO...
        // Question: Does this delete the array inside of valery and
        //  assign new memory for the new array?
        // Reply:
        //  operator= calls valerysValue->setValue (newValue).
        //  So does val->setValue (tempVar) assign new memory?
        //   Yes, it does.
        //   This calls var::VariantType_Array.cleanUp -> delete data.arrayValue;
        //  YES.
        //
        //  ( Take a look at all the var::operator=, and you see: )
        // ---------------------------------------------------------------------
        //  EVERY TIME AN ARBITRARY Value IS CHANGED (beeing it int, double,
        //  Array or whatever), the memory of the old value is released and new
        //  memory is allocated.
        // ---------------------------------------------------------------------

    cout << "valery.getValue()[0] = " << double (valery.getValue()[0]) << endl;
    
    // Therefore:
    // Don't use a Value object to transmit n doubles to the
    // MultiChannelLoudnessBar 20 times a second.

    return 0;
}
