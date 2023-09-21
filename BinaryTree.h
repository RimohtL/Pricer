#pragma once
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

template <typename T>
class BinaryTree
{
    private:
    
        int _depth;
        std::vector<std::vector<T>> _tree;

    public:

        // Constructor
        BinaryTree(int depth)
        {
            _depth = depth;
            _tree.resize(_depth + 1); // Initialize the full size of the tree
            for (int i = 0; i < _tree.size(); i++)
                _tree[i].resize(i + 1); // Initialize the size of each branch
        }

        // Empty Constructor
        BinaryTree() : _depth(0){}

        //Destructor

        ~BinaryTree(){}

        // Return the depth of the tree
        int getDepth() { return _depth; }

        // Set depth of the tree
        void setDepth(int depth)
        {
            if (_depth > depth) // If initial depth is greater than input depth, shrink the tree
            {
                _depth = depth;
                _tree.resize(_depth + 1);
            }
            else { // Otherwise, create new branches
                _tree.resize(depth + 1);
                for (int i = _depth; i < _tree.size(); i++)
                    _tree[i].resize(i + 1);
                _depth = depth;
            }
        }

        // Return the length of a specified branch
        long getLengthVec(int index) { return _tree[index].size(); }

        // Assign a value to a specified node
        void setNode(int index1, int index2, T value) { _tree[index1][index2] = value; }

        // Retrieve the value of a specified node
        T getNode(int index1, int index2) { return _tree[index1][index2]; }

        // Display the tree
        void display()
        {
            for (int i = 0; i < _depth + 1; i++)
            {
                for (int j = 0; j <= i; j++)
                {
                    if (j != i)
                    {
                        std::cout << _tree[i][j] << "\t";
                    }
                    else
                    {
                        std::cout << _tree[i][j] << std::endl;
                    }
                }
            }

            std::cout << std::endl;

            for (int i = 0; i < _tree.size(); i++)
            {
                int space = _depth * 3 + 3 - 3 * i;

                if (i == _tree.size() - 1)
                {
                    for (int k = 0; k < space; k++)
                    {
                        std::cout << " ";
                    }

                    for (int j = 0; j < _tree[i].size(); j++)
                    {
                        long value = 0;
                        if (int(_tree[i][j]) == _tree[i][j])
                            value = std::to_string(int(_tree[i][j])).length();
                        else
                            value = std::to_string(int(_tree[i][j])*100).length() + 1;
                        switch (value)
                        {
                        case 1:
                            std::cout << "  " << _tree[i][j] << "   ";
                            break;

                        case 2:
                            std::cout << "  " << _tree[i][j] << "  ";
                            break;

                        case 3:
                            std::cout << "  " << _tree[i][j] << "  ";
                            break;

                        case 4:
                            std::cout << _tree[i][j] << "  ";
                            break;
                        default:
                                
                            std::cout << "Erreur" << " ";
                        }
                    }
                    std::cout << std::endl << std::endl;
                }
                else
                {
                    for (int k = 0; k < space; k++)
                    {
                        std::cout << " ";
                    }

                    for (int j = 0; j < _tree[i].size(); j++)
                    {
                        long value = 0;
                        if (int(_tree[i][j]) == _tree[i][j])
                            value = std::to_string(int(_tree[i][j])).length();
                        else
                            value = std::to_string(int(_tree[i][j])*100).length() + 1;
                        switch (value)
                        {
                        case 1:
                            std::cout << "  " << _tree[i][j] << "   ";
                            break;

                        case 2:
                            std::cout << "  " << _tree[i][j] << "  ";
                            break;

                        case 3:
                            std::cout << " " << _tree[i][j] << "  ";
                            break;
                        case 4:
                            std::cout << _tree[i][j] << "  ";
                            break;
                        default:
                            std::cout << "Erreur" << " ";
                        }
                    }

                    std::cout << std::endl;

                    for (int k = 0; k < space; k++)
                    {
                        std::cout << " ";
                    }

                    for (int j = 0; j < _tree[i].size(); j++)
                    {
                        std::cout << "/   \\ ";
                    }

                    std::cout << std::endl;
                }
            }
            std::cout << std::endl << std::endl;
        }
};

