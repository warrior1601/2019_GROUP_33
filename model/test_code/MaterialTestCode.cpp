//
//  MaterialTestCode.cpp
//  Computing Project
//
//  Created by Chayanis Kulanumphol on 27/11/2019.
//  This File contains a suitable test for all functions declared
//  in the "Material.h" header file. The correct way to implement
//  the functions is demonstrated in this test file.
//

#include <iostream>
#include "Material.h"

int main()
{
    unsigned int Error = 0;
    int Test_ID = 10;
    double Test_Density = 10;
    std::string Test_Color = "Nothing Here";
    std::string Test_Name = "Nothing Here";

    Material test;

    Test_ID = test.GetID();
    Test_Density = test.GetDensity();
    Test_Color = test.GetColour();
    Test_Name = test.GetName();

    if (Test_ID != 0 )
    {
        Error++;
    }
    if (Test_Density != 0 )
    {
        Error++;
    }
    if (Test_Color.compare(0,3,"N/A") !=0 )
    {
        Error++;
    }
    if (Test_Name.compare(0,3,"N/A") !=0 )
    {
        Error++;
    }

    if (Error == 0 )
    {
        std::cout << "Blank Constructor and Get Functions Work properly" << std::endl;
    }
    else
    {
        std::cout << "Blank Constructor and Get Functions Do Not Working Properly" << std::endl;
        return (Error == 0) ? 0 : 1;
    }

    Material test_2(1);

    Test_ID = 10;
    Test_Density = 10;
    Test_Color = "Nothing Here";
    Test_Name = "Nothing Here";

    Test_ID = test_2.GetID();
    Test_Density = test_2.GetDensity();
    Test_Color = test_2.GetColour();
    Test_Name = test_2.GetName();

    if (Test_ID != 1 )
    {
        Error++;
    }
    if (Test_Density != 0 )
    {
        Error++;
    }
    if (Test_Color.compare(0,3,"N/A") !=0 )
    {
        Error++;
    }
    if (Test_Name.compare(0,3,"N/A") !=0 )
    {
        Error++;
    }

    if (Error == 0 )
    {
        std::cout << "ID Constructor Works properly" << std::endl;
    }
    else
    {
        std::cout << "ID Constructor Does Not Working Properly" << std::endl;
        return (Error == 0) ? 0 : 1;
    }

    Test_ID = 10;
    Test_Density = 10;
    Test_Color = "Nothing Here";
    Test_Name = "Nothing Here";

    Material test_3(2,78.36);

    Test_ID = test_3.GetID();
    Test_Density = test_3.GetDensity();
    Test_Color = test_3.GetColour();
    Test_Name = test_3.GetName();

    if (Test_ID != 2 )
    {
        Error++;
    }
    if (Test_Density != 78.36 )
    {
        Error++;
    }
    if (Test_Color.compare(0,3,"N/A") !=0 )
    {
        Error++;
    }
    if (Test_Name.compare(0,3,"N/A") !=0 )
    {
        Error++;
    }

    if (Error == 0 )
    {
        std::cout << "ID/Density Constructor Works properly" << std::endl;
    }
    else
    {
        std::cout << "ID/Density Constructor Does Not Working Properly" << std::endl;
        return (Error == 0) ? 0 : 1;
    }

    Test_ID = 10;
    Test_Density = 10;
    Test_Color = "Nothing Here";
    Test_Name = "Nothing Here";

    Material test_4(3, 95.63, "FFAAFF");

    Test_ID = test_4.GetID();
    Test_Density = test_4.GetDensity();
    Test_Color = test_4.GetColour();
    Test_Name = test_4.GetName();

    if (Test_ID != 3 )
    {
        Error++;
    }
    if (Test_Density != 95.63 )
    {
        Error++;
    }
    if (Test_Color.compare(0,6,"FFAAFF") !=0 )
    {
        Error++;
    }
    if (Test_Name.compare(0,3,"N/A") !=0 )
    {
        Error++;
    }

    if (Error == 0 )
    {
        std::cout << "ID/Density/Colour Constructor Works properly" << std::endl;
    }
    else
    {
        std::cout << "ID/Density/Colour Constructor Does Not Working Properly" << std::endl;
        return (Error == 0) ? 0 : 1;
    }

    Test_ID = 10;
    Test_Density = 10;
    Test_Color = "Nothing Here";
    Test_Name = "Nothing Here";

    Material test_5(4, 8960, "b87373", "Copper");

    Test_ID = test_5.GetID();
    Test_Density = test_5.GetDensity();
    Test_Color = test_5.GetColour();
    Test_Name = test_5.GetName();

    if (Test_ID != 4 )
    {
        Error++;
    }
    if (Test_Density != 8960 )
    {
        Error++;
    }
    if (Test_Color.compare(0,6,"b87373") !=0 )
    {
        Error++;
    }
    if (Test_Name.compare(0,6,"Copper") !=0 )
    {
        Error++;
    }

    if (Error == 0 )
    {
        std::cout << "ID/Density/Colour/Name Constructor Works properly" << std::endl;
    }
    else
    {
        std::cout << "ID/Density/Colour/Name Constructor Does Not Working Properly" << std::endl;
        return (Error == 0) ? 0 : 1;
    }

    Test_ID = 10;
    Test_Density = 10;
    Test_Color = "Nothing Here";
    Test_Name = "Nothing Here";

    test.SetID(5);
    test.SetDensity(7654);
    test.SetColour("B7C4AA");
    test.SetName("Gold");

    Test_ID = test.GetID();
    Test_Density = test.GetDensity();
    Test_Color = test.GetColour();
    Test_Name = test.GetName();

    if (Test_ID != 5 )
    {
        Error++;
    }
    if (Test_Density != 7654 )
    {
        Error++;
    }
    if (Test_Color.compare(0,6,"B7C4AA") !=0 )
    {
        Error++;
    }
    if (Test_Name.compare(0,4,"Gold") !=0 )
    {
        Error++;
    }

    if (Error == 0 )
    {
        std::cout << "Set Functions Works properly" << std::endl;
    }
    else
    {
        std::cout << "Set Functions Do Not Working Properly" << std::endl;
        return (Error == 0) ? 0 : 1;
    }

    return (Error == 0) ? 0 : 1;
}
