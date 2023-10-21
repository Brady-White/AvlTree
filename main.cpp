//Brady White AVLTREE

#include <iostream>
#include<string>
#include <vector>
#include <stack>
using namespace std;

//initialize a node with all of its info
struct AVLTree
{
    AVLTree* lft;
    AVLTree* rt;
    string studentName;
    int studentID;

    AVLTree(string name, int id)
    {
        lft = nullptr;
        rt = nullptr;
        studentName = std::move(name);
        studentID = id;
    }

    AVLTree()
    {
        lft = nullptr;
        rt = nullptr;
        studentName = " ";
        studentID = 0;
    }


};

//initializes my avlTree
class studentInformation
{
public:

    studentInformation();

    //function that returns the height of the tree
    int height(AVLTree* root);

    //function that prints the height of the tree
    int balFactor(AVLTree* root);

    //function to rotate right
    static AVLTree *rotRight(AVLTree* root);

    //function to rotate left
    static AVLTree *rotLeft(AVLTree* root);

    //function to insert a student node into the tree
    AVLTree* insertStudent(AVLTree* root, AVLTree* newNode);

    //function ot return the student node with the smallest ufid
    static AVLTree* smllNode(AVLTree* root);

    //function to remove a student node from the tree
    AVLTree* removeNode(AVLTree* root, int target);

    //function to remove a student nodes from the tree inorder
    void removeNodeInorder(AVLTree* root, int n);

    //function that prints a name when given an id
    AVLTree* idSearch(AVLTree* root, int target);

    //function that prints an id when given a name
    AVLTree* nameSearch(AVLTree* root, const string &target);

    //function that prints list of nodes inorder
    void printNodeInorder(AVLTree* root);

    //function that prints list of nodes preorder
    void printNodePreorder(AVLTree* root);

    //function that prints list of nodes postorder
    void printNodePostorder(AVLTree* root);

    //function that prints the height of the tree
    void printHeight(AVLTree* root);

    AVLTree* root;

    bool isValid = false;
};

//returns true if the inputed name is valid returns false otherwise
bool validName(const string &data);

//returns true if the inputed id is valid returns false otherwise
bool validId(const string &data);

studentInformation::studentInformation()
{
    root = nullptr;
}

int studentInformation::height(AVLTree* root)
{
    if (root == nullptr)
    {
        return 0;
    }
    else
    {
        int heightLeft = height(root->lft);
        int heightRight = height(root->rt);
        if (heightLeft > heightRight)
        {
            return heightLeft + 1;
        }
        else
        {
            return heightRight + 1;
        }
    }
}

int studentInformation::balFactor(AVLTree *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int heightLeft = height(root->lft);
    int heightRight = height(root->rt);
    return heightLeft - heightRight;
}

AVLTree* studentInformation::rotRight(AVLTree* root)
{
    if (root == nullptr || root->lft == nullptr)
    {
        return root;
    }
    AVLTree* child = root->lft;
    root->lft = child->rt;
    child->rt = root;
    return child;
}

AVLTree* studentInformation::rotLeft(AVLTree* root)
{
    if (root == nullptr || root->rt == nullptr)
    {
        return root;
    }
    AVLTree* child = root->rt;
    root->rt = child->lft;
    child->lft = root;
    return child;
}

AVLTree* studentInformation::insertStudent(AVLTree* root, AVLTree* newNode) {
    if (!validName(newNode->studentName) || !validId(to_string(newNode->studentID)))
    {
        cout << "unsuccessful" << endl;
        return root;
    }

    if (root == nullptr)
    {
        root = newNode;
        cout << "successful" << endl;
        return root;
    }
    else
    {
        if (newNode->studentID < root->studentID)
        {
            root->lft = insertStudent(root->lft, newNode);
        }
        else if (newNode->studentID > root->studentID)
        {
            root->rt = insertStudent(root->rt, newNode);
        }
        else
        {
            cout << "unsuccessful" << endl;
            return root;
        }
    }

    int factor = balFactor(root);
    if (factor > 1 && newNode->studentID < root->lft->studentID)
    {
        return rotRight(root);
    }
    if (factor < -1 && newNode->studentID > root->rt->studentID)
    {
        return rotLeft(root);
    }
    if (factor > 1 && newNode->studentID > root->lft->studentID)
    {
        root->lft = rotLeft(root->lft);
        return rotRight(root);
    }
    if (factor < -1 && newNode->studentID < root->rt->studentID)
    {
        root->rt = rotRight(root->rt);
        return rotLeft(root);
    }
    return root;
}

AVLTree* studentInformation::smllNode(AVLTree* root)    // As the studentName might give away, finds the smallest Node in the AVLTree tree
{
    if (root == nullptr)
    {
        return nullptr;
    }
    while (root->lft != nullptr)
    {
        root = root->lft;
    }
    return root;
}

AVLTree *studentInformation::removeNode(AVLTree* root, int target)  // Removes a targeted node from the AVLTree tree
{
    if (root == nullptr)
    {
        cout << "unsuccessful" << endl;
        return nullptr;
    }
    else if (target < root->studentID)
    {
        root->lft = removeNode(root->lft, target);
    }
    else if (target > root->studentID)
    {
        root->rt = removeNode(root->rt, target);
    }
    else if (root->lft == nullptr && root->rt == nullptr)
    {
        delete root;
        root = nullptr;
        cout << "successful" << endl;
        return root;
    }
    else if (root->lft == nullptr)
    {
        AVLTree *temp = root;
        root = root->rt;
        delete temp;
        cout << "successful" << endl;
        return root;
    }
    else if (root->rt == nullptr)
    {
        AVLTree *temp = root;
        root = root->lft;
        delete temp;
        cout << "successful" << endl;
        return root;
    }
    else
    {
        AVLTree *temp = smllNode(root->rt);
        root->studentID = temp->studentID;
        root->studentName = temp->studentName;
        root->rt = temp->rt;
        delete temp;
        cout << "successful" << endl;
        return root;
    }
    return nullptr;
}

void studentInformation::removeNodeInorder(AVLTree* root, int n)
{
    if (root == nullptr)
    {
        cout << "unsuccessful" << endl;
        return;
    }

    int count = 0;
    AVLTree* current = root;
    stack<AVLTree *> s;
    while (current != nullptr || !s.empty())
    {
        while (current != nullptr)
        {
            s.push(current);
            current = current->lft;
        }

        current = s.top();
        s.pop();

        if (++count == n + 1)
        {
            removeNode(root, current->studentID);
            return;
        }

        current = current->rt;
    }

    cout << "unsuccessful" << endl;
}

AVLTree* studentInformation::idSearch(AVLTree* root, int target)
{
    if (root == nullptr)
    {
        return root;
    }
    else if (root->studentID == target)
    {
        cout << root->studentName << endl;
        isValid = true;
        return root;
    }
    else if (target < root->studentID)
        return idSearch(root->lft, target);
    else
        return idSearch(root->rt, target);
}

AVLTree* studentInformation::nameSearch(AVLTree* root, const string &target)
{
    if (root == nullptr)
    {
        return root;
    }
    else if (root->studentName == target)
    {
        cout << root->studentID << endl;
        isValid = true;
    }
    nameSearch(root->lft, target);
    nameSearch(root->rt, target);
    return root;
}

void studentInformation::printNodeInorder(AVLTree* root)
{
    if (root == nullptr)
    {
        return;
    }
    printNodeInorder(root->lft);
    if (root->lft != nullptr)
    {
        cout << ", ";
    }
    cout << root->studentName;
    if (root->rt != nullptr)
    {
        cout << ", ";
    }
    printNodeInorder(root->rt);
}

void studentInformation::printNodePreorder(AVLTree* root)
{
    if (root == nullptr)
    {
        return;
    }
    cout << root->studentName;
    if (root->lft != nullptr)
    {
        cout << ", ";
        printNodePreorder(root->lft);
    }
    if (root->rt != nullptr)
    {
        cout << ", ";
        printNodePreorder(root->rt);
    }
}

void studentInformation::printNodePostorder(AVLTree* root)
{
    if (root != nullptr)
    {
        printNodePostorder(root->lft);
        if (root->rt)
        {
            cout << ", ";
        }
        printNodePostorder(root->rt);
        if (root->lft)
        {
            cout << ", ";
        }
        cout << root->studentName;
    }
}

void studentInformation::printHeight(AVLTree* root)
{
    cout << height(root) << endl;
}


bool validName(const string &data)
{
    for (char i : data)
    {
        if (!isalpha(i))
        {
            if (i == ' ')
            {
                continue;
            }
            return false;
        }
    }
    return true;
}


bool validId(const string &data)
{
    int count = 0;
    for (char i : data)
    {
        if (!isdigit(i))
        {
            if (i == ' ')
            {
                continue;
            }
            return false;
        }
        count++;
    }
    return (count == 8);
}

int main()
{
    studentInformation stud;
    string studName;
    string studInfo;
    string idNum;
    string inp;
    int inputTotal;
    cin >> inputTotal;

    for (int i = 0; i < inputTotal; i++)
    {
        cin >> inp;

        auto *newNode = new AVLTree();

        if (inp == "insert")
        {

            getline(cin, studInfo);

            int firstQuote = studInfo.find_first_of('"');
            int lastQuote = studInfo.find_last_of('"');
            studName = studInfo.substr(firstQuote + 1, lastQuote - 2);
            idNum = studInfo.substr(lastQuote + 1, studInfo.length() - 1);

            if (!validId(idNum)|| studName.empty())
            {
                cout << "unsuccessful" << endl;
                continue;
            }

            if (!validName(studName))
            {
                cout << "unsuccessful" << endl;
                continue;
            }

            newNode->studentName = studName;
            newNode->studentID = stoi(idNum);
            stud.root = stud.insertStudent(stud.root, newNode);

        }
        else if (inp == "remove")
        {
            string target;
            getline(cin, target);

            if (!validId(target))
            {
                cout << "unsuccessful" << endl;
                continue;
            }
            stud.root = stud.removeNode(stud.root, stoi(target));

        }
        else if (inp == "search")
        {
            string target;
            getline(cin, target);
            int firstQuote = target.find_first_of('"');
            int lastQuote = target.find_last_of('"');
            if (firstQuote > -1)
            {
                stud.nameSearch(stud.root, target.substr(firstQuote + 1, lastQuote - 2));
            }
            else
            {
                if (!validId(target))
                {
                    cout << "unsuccessful" << endl;
                    continue;
                }
                stud.idSearch(stud.root, stoi(target));
            }
            if (!stud.isValid)
                cout << "unsuccessful" << endl;
            stud.isValid = false;

        }
        else if (inp == "printPreorder")
        {
            stud.printNodePreorder(stud.root);
            cout << endl;

        }
        else if (inp == "printInorder")
        {
            stud.printNodeInorder(stud.root);
            cout << endl;

        }
        else if (inp == "printPostorder")
        {
            stud.printNodePostorder(stud.root);
            cout << endl;

        }
        else if (inp == "printLevelCount")
        {
            stud.printHeight(stud.root);
        }
        else if (inp == "removeInorder")
        {
            int input;
            cin >> input;
            stud.removeNodeInorder(stud.root, input);
        }
    }
    return 0;
}