#include "pch.h"
#include "CppUnitTest.h"
#include "../PDS_LAB_12/PDS_LAB_12.cpp"
#include <vector>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(TestReadGraph)
        {
            vector<vector<pair<int, int>>> adjList;
            int n, m;

            ofstream testFile("123.txt");
            testFile << "4 5\n";
            testFile << "0 1 1\n";
            testFile << "0 2 4\n";
            testFile << "1 2 2\n";
            testFile << "1 3 6\n";
            testFile << "2 3 3\n";
            testFile.close();

            readGraph("123.txt", adjList, n, m);

            Assert::AreEqual(n, 4);
            Assert::AreEqual(m, 5);
            Assert::AreEqual((int)adjList[0].size(), 2);
            Assert::AreEqual(adjList[0][0].first, 1);
            Assert::AreEqual(adjList[0][1].first, 2);
        }

        TEST_METHOD(TestDijkstra)
        {
            vector<vector<pair<int, int>>> adjList = {
                {{1, 1}, {2, 4}},
                {{2, 2}, {3, 6}},
                {{3, 3}},
                {}
            };

            vector<int> previous;
            vector<int> distances = dijkstra(adjList, 0, previous);

            Assert::AreEqual(distances[0], 0);
            Assert::AreEqual(distances[1], 1);
            Assert::AreEqual(distances[2], 3);
            Assert::AreEqual(distances[3], 6);
        }
    };
}