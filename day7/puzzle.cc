#include "../AoCHelper/AoCHelper.h"
#include <vector>

struct Directory
{
    std::string name;
    Directory *parent;
    std::vector<Directory> subDirectories;
    std::vector<std::pair<std::string, size_t>> files;
    size_t total_size{0};
};

std::vector<Directory> findAllDirectoriesWithSizeLargerThan(std::vector<Directory> &directories, size_t size)
{
    std::vector<Directory> directoriesWithSizeLargerThan;
    for (Directory directory : directories)
    {
        if (directory.total_size > size)
        {
            directoriesWithSizeLargerThan.push_back(directory);
        }
        std::vector<Directory> subDirectoriesWithSizeLargerThan = findAllDirectoriesWithSizeLargerThan(directory.subDirectories, size);
        directoriesWithSizeLargerThan.insert(directoriesWithSizeLargerThan.end(), subDirectoriesWithSizeLargerThan.begin(), subDirectoriesWithSizeLargerThan.end());
    }
    return directoriesWithSizeLargerThan;
}

size_t findAllDirectoriesWithSizeLessThan(std::vector<Directory> &directories, size_t size)
{
    size_t total{0};
    for (Directory directory : directories)
    {
        if (directory.total_size <= size)
        {
            total += directory.total_size;
        }
        total += findAllDirectoriesWithSizeLessThan(directory.subDirectories, size);
    }
    return total;
}

size_t getDirectorySize(Directory &directory)
{
    size_t size{0};
    for (std::pair<std::string, size_t> file : directory.files)
    {
        size += file.second;
    }
    for (Directory subDirectory : directory.subDirectories)
    {
        size += getDirectorySize(subDirectory);
    }
    return size;
}

void updateAllTotalSizes(Directory &directory)
{
    directory.total_size = getDirectorySize(directory);
    for (Directory &subDirectory : directory.subDirectories)
    {
        updateAllTotalSizes(subDirectory);
    }
}

void puzzle(std::vector<std::string> input)
{
    size_t answer{};
    Directory root{"/", nullptr, {}, {}, 0};
    Directory *currentDirectory = &root;
    for (int i = 0; i < input.size(); i++)
    {
        std::string row = input[i];
        if (row == "$ cd /")
        {
            currentDirectory = &root;
        }
        else if (row == "$ cd ..")
        {
            currentDirectory = currentDirectory->parent;
        }
        else if (row.substr(0, 4) == "$ cd")
        {
            std::string directoryName = myLib::split(row, ' ')[2];
            if (std::any_of(currentDirectory->subDirectories.begin(), currentDirectory->subDirectories.end(), [directoryName](Directory directory)
                            { return directory.name == directoryName; }))
            {
                for (Directory &directory : currentDirectory->subDirectories)
                {
                    if (directory.name == directoryName)
                    {
                        currentDirectory = &directory;
                    }
                }
            }
            else
            {
                Directory newDirectory{directoryName, currentDirectory, {}, {}, 0};
                currentDirectory->subDirectories.push_back(newDirectory);
                currentDirectory = &newDirectory;
            }
        }
        else if (row == "$ ls")
        {
            size_t j = i + 1;
            while (input[j].substr(0, 1) != "$")
            {
                if (input[j].substr(0, 4) == "dir ")
                {
                    std::string subDirectoryName = myLib::split(input[j], ' ')[1];
                    if (std::none_of(currentDirectory->subDirectories.begin(), currentDirectory->subDirectories.end(), [subDirectoryName](Directory directory)
                                     { return directory.name == subDirectoryName; }))
                    {
                        Directory newDirectory{subDirectoryName, currentDirectory, {}, {}, 0};
                        currentDirectory->subDirectories.push_back(newDirectory);
                    }
                }
                else
                {
                    std::string fileName = myLib::split(input[j], ' ')[1];
                    size_t fileSize = std::stoi(myLib::split(input[j], ' ')[0]);
                    currentDirectory->files.push_back(std::make_pair(fileName, fileSize));
                }
                if (j == input.size() - 1)
                {
                    break;
                }
                j++;
            }
        }
    }

    updateAllTotalSizes(root);

    answer = findAllDirectoriesWithSizeLessThan(root.subDirectories, 100000);

    std::cout << "Puzzle one: " << answer << std::endl;
    int freeSpace = 70000000 - root.total_size;

    int neededSpace = 30000000;
    int spaceToBeFreed = neededSpace - freeSpace;
    std::vector<Directory> directoriesWithSizeLargerThan = findAllDirectoriesWithSizeLargerThan(root.subDirectories, spaceToBeFreed);
    std::sort(directoriesWithSizeLargerThan.begin(), directoriesWithSizeLargerThan.end(), [](Directory a, Directory b)
              { return a.total_size < b.total_size; });
    int answerTwo = directoriesWithSizeLargerThan[0].total_size;
    std::cout << "Puzzle two: " << answerTwo << std::endl;
}

int main()
{
    std::vector<std::string> exampleInput{
        "$ cd /",
        "$ ls",
        "dir a",
        "14848514 b.txt",
        "8504156 c.dat",
        "dir d",
        "dir g",
        "$ cd a",
        "$ ls",
        "dir e",
        "29116 f",
        "2557 g",
        "62596 h.lst",
        "$ cd e",
        "$ ls",
        "584 i",
        "$ cd ..",
        "$ cd ..",
        "$ cd d",
        "$ ls",
        "4060174 j",
        "8033020 d.log",
        "5626152 d.ext",
        "7214296 k",
        "dir a", // had to add extra example data to find a bug in my program
        "$ cd a",
        "$ ls",
        "10203 abc",
        "$ cd /",
        "$ cd g",
        "$ ls",
        "2000 b.txt",
        "1000 c.dat",
        "dir k"
        "$ cd k",
        "$ ls",
        "5000 b.txt"};
    AoCHelper a1{"2022", "7"};
    std::vector<std::string> result = a1.get_input();
    puzzle(result);
}
