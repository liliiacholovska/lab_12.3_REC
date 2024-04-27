#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab12.3(2)/lab12.3(2).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestSwapAdjacentNodes)
        {
            int values[] = { 1, 2, 3, 4, 5 };
            int size = sizeof(values) / sizeof(values[0]);
            Node* head = createListRec(values, size);
            swapAdjacentNodesRec(head, head);

            int expectedValues[] = { 2, 1, 4, 3, 5 };
            Node* currentNode = head;
            int currentIndex = 0;

            while (currentNode != nullptr) {
                Assert::AreEqual(expectedValues[currentIndex], currentNode->data);
                currentNode = currentNode->next;
                currentIndex++;
            }

            Assert::AreEqual(size, currentIndex);

            deleteListRec(head);
        }
	};
}
