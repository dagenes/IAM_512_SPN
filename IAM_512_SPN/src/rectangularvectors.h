/*
 * Created by HardCore on 18/04/2020.
 */
#pragma once

//----------------------------------------------------------------------------------------
//	Copyright © 2007 - 2020 Tangible Software Solutions, Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class includes methods to convert multidimensional arrays to C++ vectors.
//----------------------------------------------------------------------------------------
#include <vector>

class RectangularVectors
{
public:
    static std::vector<std::vector<int>> RectangularİntVector(int size1, int size2)
    {
        std::vector<std::vector<int>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<int>(size2);
        }

        return newVector;
    }
};
