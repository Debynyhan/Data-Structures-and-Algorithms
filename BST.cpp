
//============================================================================
// Name        : BinarySearchTree.cpp 
// Author      : Debynyhan Banks
// Version     : 1.0
// This program extract data from a csv file and store it in a BST.
//============================================================================

#include <iostream>

#include "CSVparser.hpp"

using namespace std;


struct Course {
    string courseId; // unique identifier
    string title;
    string Pre1;
    string Pre2;
    Course() {
        
    }
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Course aCourse) :
        Node() {
        this->course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

class BinarySearchTree {

private:
    Node* root;
    void addNode(Node* node, Course course);
    void inOrder(Node* node);

public:

    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Course course);
    Course Search(string courseId);

};


BinarySearchTree::BinarySearchTree() {

    //root is equal to nullptr
    root = nullptr;
}


BinarySearchTree::~BinarySearchTree() {

}


void BinarySearchTree::InOrder() {

    // call inOrder function and pass root
    this->inOrder(root);

}


void BinarySearchTree::Insert(Course course) {

    // if root equal to null ptr
    if (root == nullptr) {

        // root is equal to new node course
        root = new Node(course);
    }

    // else
    else {

        // add Node root and course
        this->addNode(root, course);
    }
}


Course BinarySearchTree::Search(string courseId) {

    // set current node equal to root
    Node* current = root;

    // keep looping downwards until bottom reached or matching courseId found
    while (current != nullptr) {

        // if match found, return current course
        if (current->course.courseId.compare(courseId) == 0) {
            return current->course;
        }

        // if bid is smaller than current node then traverse left
        if (courseId.compare(current->course.courseId) < 0) {
            current = current->left;
        }
        // else larger so traverse right
        else {
            current = current->right;
        }
    }
    Course course;
    return course;
}


void BinarySearchTree::addNode(Node* node, Course course) {

    // if node is larger then add to left
    if (node->course.courseId.compare(course.courseId) > 0) {

        // if no left node
        if (node->left == nullptr) {

            // this node becomes left
            node->left = new Node(course);
        }

        // else recurse down the left node
        else {
            this->addNode(node->left, course);
        }
    }

    //else
    else {
        // if no right node
        if (node->right == nullptr) {

            // this node becomes right
            node->right = new Node(course);
        }

        //else
        else {

            // recurse down the right node
            this->addNode(node->right, course);
        }
    }
}

void BinarySearchTree::inOrder(Node* node) {

    //if node is not equal to null ptr
    if (node != nullptr) {

        //inOrder not left
        inOrder(node->left);

        //output courseID, title, Pre1, Pre2
        std::cout << node->course.courseId << " " << node->course.title << endl;

        //inOrder right
        inOrder(node->right);
    }

}


void displayCourse(Course course) {

    if (course.Pre1.empty()) {
        std::cout << "Course Number: " << course.courseId << ", " << course.title << endl << endl;
    }

    else {
        if (course.Pre2.empty()) {
            std::cout << "Course Number: " << course.courseId << ", " << course.title << endl << endl;
            std::cout << "Prerequisite: " << course.Pre1 << endl << endl;
        }
        else {
            std::cout << "Course Number: " << course.courseId << ", " << course.title << endl << endl;
            std::cout << "Prerequisites: " << course.Pre1 << ", " << course.Pre2 << endl << endl;
        }
    }

    return;
}


void loadCourses(string csvPath, BinarySearchTree* bst) {
    std::cout << "Loading CSV file " << csvPath << endl << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);


    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of courses
            Course course;
            course.courseId = file[i][0];
            course.title = file[i][1];
            course.Pre1 = file[i][2];
            course.Pre2 = file[i][3];

            // push this course to the end
            bst->Insert(course);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}



int main(int argc, char* argv[]) {

    // Define a binary search tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    string csvPath, courseKey;
    csvPath = "courses.csv";
    courseKey = "";

    int choice = 0;
    bool success = false;

    while (choice != 4) {
        std::cout << "Menu:" << endl;
        std::cout << "  1. Load Courses" << endl;
        std::cout << "  2. Display All Courses" << endl;
        std::cout << "  3. Find Course" << endl;
        std::cout << "  4. Exit" << endl;
        std::cout << "Enter choice: ";
        cin >> choice;


        switch (choice) {

        case 1:

            // Call loadCourses
            loadCourses(csvPath, bst);

            break;

        case 2:
            bst->InOrder();
            break;

        case 3:

            std::cout << "Enter a Course Number: ";

            cin >> courseKey;

            // Capitalize user input
            for (auto& c : courseKey) c = toupper(c);
            std::cout << endl;
            course = bst->Search(courseKey);


            if (!course.courseId.empty()) {
                displayCourse(course);
            }
            else {
                std::cout << "Course Id " << courseKey << " not found." << endl;
            }

            break;

        case 4:

            break;

        default:
            std::cout << "Invalid choice, please try again" << endl;
            success = true;
            break;

        }

        if (success) {
            break;
        }


    }

    std::cout << "Good bye." << endl;   

    return 0;
}




