#include "Headers/time_tester.h"


void Tests::PerformAllTests(int perTestReps, int maxElementsAmount, int amountOfSamples, std::string outputDirectoryPath)
{
    std::cout<<"TEST BEGINS\n\n";
    Tests::PerformDynamicArrayTests(perTestReps, maxElementsAmount, amountOfSamples, outputDirectoryPath);
    printf("\n\n");
    Tests::PerformDoubleLinkedListTests(perTestReps, maxElementsAmount, amountOfSamples, outputDirectoryPath);
    printf("\n\n");
    Tests::PerformHeapTests(perTestReps, maxElementsAmount, amountOfSamples, outputDirectoryPath);
    printf("\n\n");
    // Tests::PerformBstTests(perTestReps, maxElementsAmount, amountOfSamples, outputDirectoryPath);
    // printf("\n\n");
    Tests::PerformRbtTests(perTestReps, maxElementsAmount, amountOfSamples, outputDirectoryPath);
    printf("\nDONE!\n");
}

void Tests::PerformDynamicArrayTests(int perTestReps, int maxElementsAmount, int amountOfSamples, std::string outputDirectoryPath)
{
    std::cout<<"DYNAMIC ARRAY TESTS\n";

    Timer timer;
    RandomGenerator random;
    DynamicArray dynamiArray;
    double time;

    int step = maxElementsAmount/amountOfSamples;
    int constAmount = step;

    std::string path = Tests::SetupFile(outputDirectoryPath + "dynamicArray_Tests.csv");

    for (int elemAmount = step; elemAmount <= maxElementsAmount; elemAmount+=step)
    {
        if(Tests::PrintMessages)
            std::cout<< "\n\n=================================================\nElements amount: " + std::to_string(elemAmount) + " ||\n";

         time = 0;
        for (int i = 0; i < perTestReps; i++)
        {
            if(Tests::PrintMessages)
                printf("AddFirst, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            dynamiArray.AddAll(elemAmount, sample);

            int num = random.GetRandomNumber(-elemAmount,elemAmount);

            timer.StartTimer();   
            dynamiArray.AddFirst(num);
            time += timer.TimerStop(MICRO_SECONDS);

            dynamiArray.RemoveAll();  
            delete[] sample;      
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "AddFirst", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {    
            if(Tests::PrintMessages)
                printf("AddLast, ");
    
            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            dynamiArray.AddAll(elemAmount, sample);

            int num = random.GetRandomNumber(-elemAmount,elemAmount);

            timer.StartTimer();   
            dynamiArray.AddLast(num);
            time += timer.TimerStop(MICRO_SECONDS);

            dynamiArray.RemoveAll();  
            delete[] sample;  
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "AddLast", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {
            if(Tests::PrintMessages)
                printf("AddAtPos, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            dynamiArray.AddAll(elemAmount, sample);

            int num = random.GetRandomNumber(-elemAmount,elemAmount);
            int index = random.GetRandomNumber(0,elemAmount);

            timer.StartTimer();
            dynamiArray.AddAtPos(index, num);
            time += timer.TimerStop(MICRO_SECONDS);

            dynamiArray.RemoveAll(); 
            delete[] sample;   
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "AddAtPos", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {
            if(Tests::PrintMessages)
                printf("RemoveFirst, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            dynamiArray.AddAll(elemAmount, sample);

            timer.StartTimer();   
            dynamiArray.RemoveFirst();
            time += timer.TimerStop(MICRO_SECONDS);

            dynamiArray.RemoveAll();   
            delete[] sample;     
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "RemoveFirst", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {
            if(Tests::PrintMessages)
                printf("RemoveLast, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            dynamiArray.AddAll(elemAmount, sample);

            timer.StartTimer();   
            dynamiArray.RemoveLast();
            time += timer.TimerStop(MICRO_SECONDS);

            dynamiArray.RemoveAll();   
            delete[] sample;
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "RemoveLast", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {
            if(Tests::PrintMessages)
                printf("RemoveAtPos, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            dynamiArray.AddAll(elemAmount, sample);

            int index = random.GetRandomNumber(0, dynamiArray.GetSize() -1);
            
            timer.StartTimer();
            dynamiArray.RemoveAtPos(index);
            time += timer.TimerStop(MICRO_SECONDS);

            dynamiArray.RemoveAll();    
            delete[] sample;
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "RemoveAtPos", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {
            if(Tests::PrintMessages)
                printf("Find, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            dynamiArray.AddAll(elemAmount, sample);

            int toFind = random.GetRandomNumber(-elemAmount, elemAmount);
            
            timer.StartTimer();   
            dynamiArray.FindNumber(toFind);
            time += timer.TimerStop(MICRO_SECONDS);

            dynamiArray.RemoveAll();      
            delete[] sample;
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "Find", path);

        Tests::PrintPercentFinish(elemAmount,maxElementsAmount);
    }
}

void Tests::PerformDoubleLinkedListTests(int perTestReps, int maxElementsAmount, int amountOfSamples, std::string outputDirectoryPath)
{
    std::cout<<"DOUBLE LINKED LIST TESTS\n";

    Timer timer;
    RandomGenerator random;
    DoubleLinkedList list;
    double time;

    int step = maxElementsAmount/amountOfSamples;
    int constAmount = step;

    std::string path = Tests::SetupFile(outputDirectoryPath + "list_Tests.csv");

    
    for (int elemAmount = step; elemAmount <= maxElementsAmount; elemAmount+=step)
    {
        if(Tests::PrintMessages)
            std::cout<< "\n\n=================================================\nElements amount: " + std::to_string(elemAmount) + " ||\n";

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {
            if(Tests::PrintMessages)
                printf("AddFirst, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            list.AddAll(elemAmount, sample);

            int num = random.GetRandomNumber(-elemAmount,elemAmount);

            timer.StartTimer();   
            list.AddFirst(num);
            time += timer.TimerStop(MICRO_SECONDS);

            list.RemoveAll();  
            delete[] sample;      
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "AddFirst", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {    
            if(Tests::PrintMessages)
                printf("AddLast, ");
    
            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            list.AddAll(elemAmount, sample);

            int num = random.GetRandomNumber(-elemAmount,elemAmount);

            timer.StartTimer();   
            list.AddLast(num);
            time += timer.TimerStop(MICRO_SECONDS);

            list.RemoveAll();  
            delete[] sample;  
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "AddLast", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {
            if(Tests::PrintMessages)
                printf("AddAtPos, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            list.AddAll(elemAmount, sample);

            int num = random.GetRandomNumber(-elemAmount,elemAmount);
            int index = random.GetRandomNumber(0,elemAmount);

            timer.StartTimer();
            list.AddAtPos(index, num);
            time += timer.TimerStop(MICRO_SECONDS);

            list.RemoveAll(); 
            delete[] sample;   
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "AddAtPos", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {
            if(Tests::PrintMessages)
                printf("RemoveFirst, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            list.AddAll(elemAmount, sample);

            timer.StartTimer();   
            list.RemoveFirst();
            time += timer.TimerStop(MICRO_SECONDS);

            list.RemoveAll();   
            delete[] sample;     
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "RemoveFirst", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {
            if(Tests::PrintMessages)
                printf("RemoveLast, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            list.AddAll(elemAmount, sample);

            timer.StartTimer();   
            list.RemoveLast();
            time += timer.TimerStop(MICRO_SECONDS);

            list.RemoveAll();   
            delete[] sample;
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "RemoveLast", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {
            if(Tests::PrintMessages)
                printf("RemoveAtPos, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            list.AddAll(elemAmount, sample);

            int index = random.GetRandomNumber(0, list.GetSize() -1);
            
            timer.StartTimer();
            list.RemoveAtPos(index);
            time += timer.TimerStop(MICRO_SECONDS);

            list.RemoveAll();    
            delete[] sample;
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "RemoveAtPos", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {
            if(Tests::PrintMessages)
                printf("Find, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            list.AddAll(elemAmount, sample);

            int toFind = random.GetRandomNumber(-elemAmount, elemAmount);
            
            timer.StartTimer();   
            list.FindNumber(toFind);
            time += timer.TimerStop(MICRO_SECONDS);

            list.RemoveAll();      
            delete[] sample;
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "Find", path);

        Tests::PrintPercentFinish(elemAmount,maxElementsAmount);
    }
}

void Tests::PerformHeapTests(int perTestReps, int maxElementsAmount, int amountOfSamples, std::string outputDirectoryPath)
{
    std::cout<<"BINARY HEAP TESTS\n";

    Timer timer;
    RandomGenerator random;
    BinaryHeap heap;
    double time;

    int step = maxElementsAmount/amountOfSamples;
    int constAmount = step;

    std::string path = Tests::SetupFile(outputDirectoryPath + "heap_Tests.csv");

    
    for (int elemAmount = step; elemAmount <= maxElementsAmount; elemAmount+=step)
    {
        if(Tests::PrintMessages)
            std::cout<< "\n\n=================================================\nElements amount: " + std::to_string(elemAmount) + " ||\n";

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {
            if(Tests::PrintMessages)
                printf("Push, ");
    
            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            heap.PushAllFloyd(elemAmount, sample);
            int num = random.GetRandomNumber(-elemAmount,elemAmount);

            timer.StartTimer();   
            heap.Push(num);
            time += timer.TimerStop(MICRO_SECONDS);

            heap.RemoveAll();
            delete[] sample;    
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "Push", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {    
            if(Tests::PrintMessages)
                printf("Pop, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            heap.PushAllFloyd(elemAmount, sample);

            timer.StartTimer();   
            heap.PopHead();
            time += timer.TimerStop(MICRO_SECONDS);

            heap.RemoveAll();    
            delete[] sample; 
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "Pop", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {
            if(Tests::PrintMessages)
                printf("Find, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            heap.PushAllFloyd(elemAmount, sample);

            int toFind = random.GetRandomNumber(-elemAmount, elemAmount);
            
            timer.StartTimer();   
            heap.Find(toFind);
            time += timer.TimerStop(MICRO_SECONDS);

            heap.RemoveAll();      
            delete[] sample;
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "Find", path);


        Tests::PrintPercentFinish(elemAmount,maxElementsAmount);
    }
}

void Tests::PerformBstTests(int perTestReps, int maxElementsAmount, int amountOfSamples, std::string outputDirectoryPath)
{
    //!!! NOT EDITED
    std::cout<<"BINARY SEARCH TREE TESTS\n";

    Timer timer;
    RandomGenerator random;
    BinarySearchTree bst;
    double time;

    int step = maxElementsAmount/amountOfSamples;
    int constAmount = step;

    std::string path = Tests::SetupFile(outputDirectoryPath + "BST_Tests.csv");

    
    for (int elemAmount = step; elemAmount <= maxElementsAmount; elemAmount+=step)
    {
        if(Tests::PrintMessages)
            std::cout<< "\n\n=================================================\nElements amount: " + std::to_string(elemAmount) + " ||\n";

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {
            if(Tests::PrintMessages)
                printf("Add, ");

            int* sample = random.GetRandomNumbers(-maxElementsAmount,maxElementsAmount,elemAmount);

            timer.StartTimer();   
            for (int s = 0; s < elemAmount; s++)
            {
                bst.Add(sample[s]);
            }
            time += timer.TimerStop(MICRO_SECONDS);
            bst.RemoveAll(); 
            delete[] sample;
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "Add", path);
        
        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {    
            if(Tests::PrintMessages)
                printf("Remove, ");

            int* sample = random.GetRandomNumbers(-maxElementsAmount,maxElementsAmount,elemAmount);

            bst.AddAll(elemAmount, sample);


            timer.StartTimer();   
            for (int s = 0; s < elemAmount; s++)
            {
                bst.Remove(sample[s]);
            }
            time += timer.TimerStop(MICRO_SECONDS);
            bst.RemoveAll(); 
            delete[] sample;
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "Remove", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {    
            if(Tests::PrintMessages)
                printf("Find, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);

            bst.AddAll(elemAmount, sample);

            for (int s = 0; s < constAmount; s++)
            {
                int toFind = random.GetRandomNumber(-elemAmount,elemAmount);
                timer.StartTimer();   
                Node* node = bst.Find(toFind);
                time += timer.TimerStop(MICRO_SECONDS);
            }
            bst.RemoveAll();   
            delete[] sample;
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "Find", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {    
            if(Tests::PrintMessages)
                printf("DSW, ");

            int* sample = random.GetRandomNumbers(-maxElementsAmount,maxElementsAmount,elemAmount);

            bst.AddAll(elemAmount, sample);

            timer.StartTimer();   
            bst.PerformDSW();
            time += timer.TimerStop(MICRO_SECONDS);
            bst.RemoveAll();   
            delete[] sample;
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "DSW", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {    
            if(Tests::PrintMessages)
                printf("DSW FIND, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);

            bst.AddAll(elemAmount, sample);

            bst.PerformDSW();
            for (int s = 0; s < constAmount; s++)
            {
                int toFind = random.GetRandomNumber(-elemAmount,elemAmount);
                timer.StartTimer();   
                Node* node = bst.Find(toFind);
                time += timer.TimerStop(MICRO_SECONDS);
            }
            bst.RemoveAll();     
            delete[] sample;
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "DSW_Find", path);


        Tests::PrintPercentFinish(elemAmount,maxElementsAmount);
    }
}

void Tests::PerformRbtTests(int perTestReps, int maxElementsAmount, int amountOfSamples, std::string outputDirectoryPath)
{
    std::cout<<"RED BLACK TREE TESTS\n";

    Timer timer;
    RandomGenerator random;
    RedBlackTree rbt;
    double time;

    int step = maxElementsAmount/amountOfSamples;
    int constAmount = step;

    std::string path = Tests::SetupFile(outputDirectoryPath + "RBT_Tests.csv");

    
    for (int elemAmount = step; elemAmount <= maxElementsAmount; elemAmount+=step)
    {
        if(Tests::PrintMessages)
            std::cout<< "\n\n=================================================\nElements amount: " + std::to_string(elemAmount) + " ||\n";


        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {
            if(Tests::PrintMessages)
                printf("Add, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            rbt.AddAll(elemAmount, sample);

            int num = random.GetRandomNumber(-elemAmount,elemAmount);
            timer.StartTimer();   
            rbt.Add(num);
            time += timer.TimerStop(MICRO_SECONDS);

            rbt.RemoveAll();   
            delete[] sample; 
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "Add", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {    
            if(Tests::PrintMessages)
                printf("Remove, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);
            rbt.AddAll(elemAmount, sample);

            int index = random.GetRandomNumber(0, elemAmount-1);

            timer.StartTimer();   
            rbt.Remove(sample[index]);
            time += timer.TimerStop(MICRO_SECONDS);

            rbt.RemoveAll();    
            delete[] sample; 
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "Remove", path);

        time = 0;
        for (int i = 0; i < perTestReps; i++)
        {    
            if(Tests::PrintMessages)
                printf("Find, ");

            int* sample = random.GetRandomNumbers(-elemAmount,elemAmount,elemAmount);

            rbt.AddAll(elemAmount, sample);

            int toFind = random.GetRandomNumber(-elemAmount,elemAmount);
            
            timer.StartTimer();   
            NodeRBT* node = rbt.Find(toFind);
            time += timer.TimerStop(MICRO_SECONDS);

            rbt.RemoveAll();   
            delete[] sample; 
        }
        time = time/(double)perTestReps;
        Tests::SavePopAndTimeToFile(elemAmount, time, "Find", path);


        Tests::PrintPercentFinish(elemAmount,maxElementsAmount);
    }
}

void Tests::Fun()
{
    DynamicArray array;
    DoubleLinkedList list;
    BinaryHeap heap;
    BinarySearchTree bst;
    RedBlackTree rbt;


    int amount = 100000;
    RandomGenerator random;
    int sSize = 50;

    for (size_t i = 0; i < amount * 2; i++)
    {

        int choice = random.GetRandomNumber(0,3);
        int num = random.GetRandomNumber(-sSize, sSize);
        int* arr = random.GetRandomNumbers(-sSize, sSize, sSize);
        switch (choice)
        {
        case 0:
            rbt.Add(num);
            break;
        case 1:
            rbt.AddAll(sSize,arr);
            break;
        case 2:
            rbt.Remove(num);
            break;
        case 3:
            rbt.RemoveAll();
            break;
        default:
            break;
        }
        delete[] arr;
    }

    for (size_t i = 0; i < amount * 2; i++)
    {
        // std::cout << array.ToString();
        int choice = random.GetRandomNumber(0,7);
        int num = random.GetRandomNumber(-sSize, sSize);
        int num2 = random.GetRandomNumber(-sSize, sSize);
        int* arr = random.GetRandomNumbers(-sSize, sSize, sSize);
        switch (choice)
        {
        case 0:
            array.AddFirst(num);
            break;
        case 1:
            array.AddLast(num);
            break;
        case 2:
            array.AddAtPos(num, num2);
            break;
        case 3:
            array.RemoveFirst();
            break;
        case 4:
            array.RemoveLast();
            break;
        case 5:
            array.RemoveAtPos(num);
            break;
        case 6:
            array.AddAll(sSize, arr);
            break;
        case 7:
            array.RemoveAll();
            break;
        default:
            break;
        }
        delete[] arr;

    }
    
    for (size_t i = 0; i < amount * 2; i++)
    {
        // std::cout << list.ToStringForward();
        // std::cout << list.ToStringBackward();
        int choice = random.GetRandomNumber(0,7);
        int num = random.GetRandomNumber(-sSize, sSize);
        int num2 = random.GetRandomNumber(-sSize, sSize);
        int* arr = random.GetRandomNumbers(-sSize, sSize, sSize);
        switch (choice)
        {
        case 0:
            list.AddFirst(num);
            break;
        case 1:
            list.AddLast(num);
            break;
        case 2:
            list.AddAtPos(num, num2);
            break;
        case 3:
            list.RemoveFirst();
            break;
        case 4:
            list.RemoveLast();
            break;
        case 5:
            list.RemoveAtPos(num);
            break;
        case 6:
            list.AddAll(sSize, arr);
            break;
        case 7:
            list.RemoveAll();
            break;
        default:
            break;
        }
        delete[] arr;

    }


    for (size_t i = 0; i < amount * 2; i++)
    {
        int choice = random.GetRandomNumber(0,5);
        int num = random.GetRandomNumber(-sSize, sSize);
        int* arr = random.GetRandomNumbers(-sSize, sSize, sSize);
        // std::cout << heap.ToString();

        switch (choice)
        {
        case 0:
            heap.Push(num);
            break;
        case 1:
            if(heap.GetSize() > 0)
                heap.PopHead();
            break;
        case 2:
            heap.PushAllFloyd(sSize,arr);
            break;
        case 3:
            heap.PushAll(sSize,arr);
            break;
        case 4:
            heap.RemoveAll();
            break;
        case 5:
            heap.Find(num);
            break;
        default:
            break;
        }
        delete[] arr;
    }

    for (size_t i = 0; i < amount * 2; i++)
    {
        // std::cout << bst.ToString();

        int choice = random.GetRandomNumber(0,6);
        int num = random.GetRandomNumber(-sSize, sSize);
        int* arr = random.GetRandomNumbers(-sSize, sSize, sSize);
        switch (choice)
        {
        case 0:
            bst.Add(num);
            break;
        case 1:
            bst.Remove(num);
            break;
        case 2:
            bst.RotateLeft(num);
            break;
        case 3:
            bst.RotateRight(num);
            break;
        case 4:
            bst.PerformDSW();
            break;
        case 5:
            bst.AddAll(sSize, arr);
            break;
        case 6:
            bst.RemoveAll();
            break;
        default:
            break;
        }
        delete[] arr;
    }


    std::cout<<"END\n\n";
}


#pragma region TestsHelpers

std::string Tests::SetupFile(std::string name)
{
    std::string baseCsvHead[3] = {"Population size", "Time taken", "Test Type"};
    RemoveFile(name);
    WriteDataToCsv(name, baseCsvHead, 3);
    return name;
}


void Tests::SavePopAndTimeToFile(int populationAmount, double timeTaken, std::string testType, std::string fileName)
{
    std::string toFile[3];
    toFile[0] = std::to_string(populationAmount);
    toFile[1] = std::to_string(timeTaken);
    toFile[2] = testType;
    bool isFileSaved = WriteDataToCsv(fileName, toFile, 3);

    if(Tests::PrintMessages)
    {
        std::cout<<std::fixed << std::setprecision(2)<< "\n||=> Time taken: " << timeTaken;
        std::string fileMess = (isFileSaved)? "\nsaved to file!" : "\nunable to save to file!";
        std::cout<< fileMess;
        printf("\n\n");
    }
}


void Tests::PrintPercentFinish(int current, int all)
{
    float num = (float)current*100/(float)all;
    printf("Completed: [%.2f%]\n", num);
}

#pragma endregion

