/**
 * Created: FA17
 *      Lab_trees
 *
 * Modified:
 *      By:
 */
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "catchlib.h"

#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <string>
#include <utility>
#include "../binarytree.h"
#include "../abstractsyntaxtree.h"


using namespace std;
using namespace util;



void assertMirror(vector<int> a, vector<int> b)
{
    REQUIRE(a.size() == b.size());

    for(size_t i = 0; i < a.size(); i++){
        CHECK(a[i] == b[b.size()-1-i]);
    }
}

void assert_path(vector<vector <int> > a, vector<vector<int> > b)
{
    REQUIRE(a.size() == b.size());
    for(size_t i = 0; i < a.size(); i++){
        REQUIRE(a[i].size() == b[i].size());
        for(size_t j=0; j<a[i].size();j++){
            CHECK(a[i][j]==b[i][j]);
        }
    }
}

double pemdas_to_ast(const std::string &pemdas_str, typename BinaryTree<std::string>::Node* &t, vector<std::pair<typename BinaryTree<std::string>::Node*, double>> &subtrees)
{
    std::string spaceless = "";
    for (const char c : pemdas_str) {
        if (c != ' ') {
            spaceless += c;
        }
    }

    // Decent parsing time
    std::string tokenize = "";
    for (size_t i = 0; i < spaceless.length(); ++i)
    {
        if (spaceless[i] == '(')
        {
            int depth = 1;
            string tok = "";
            ++i;
            while (true)
            {
                if (spaceless[i] == '(')
                {
                    ++depth;
                } 
                else if (spaceless[i] == ')')
                {
                    --depth;
                    if (depth == 0)
                    {
                        ++i;
                        break;
                    }
                }
                tok += spaceless[i];
                ++i;
            }
            typename BinaryTree<std::string>::Node* temp_tree;
            double res = pemdas_to_ast(tok, temp_tree, subtrees);
            tokenize += "[" + std::to_string(subtrees.size()) + "]";
            subtrees.push_back({temp_tree, res});
        }
        tokenize += spaceless[i];
    }

    // Recursion Time
    for (size_t i = 0; i < tokenize.length(); ++i) 
    {
        if (tokenize[i] == '+') {
            t = new typename BinaryTree<std::string>::Node("+");
            return pemdas_to_ast(tokenize.substr(0, i), t->left, subtrees) + pemdas_to_ast(tokenize.substr(i+1, tokenize.length()-i-1), t->right, subtrees);
        }
        else if (tokenize[i] == '-') {
            t = new typename BinaryTree<std::string>::Node("-");
            return pemdas_to_ast(tokenize.substr(0, i), t->left, subtrees) - pemdas_to_ast(tokenize.substr(i+1, tokenize.length()-i-1), t->right, subtrees);
        }
    }

    for (size_t i = 0; i < tokenize.length(); ++i)
    {
        if (tokenize[i] == '*') {
            t = new typename BinaryTree<std::string>::Node("*");
            return pemdas_to_ast(tokenize.substr(0, i), t->left, subtrees) * pemdas_to_ast(tokenize.substr(i+1, tokenize.length()-i-1), t->right, subtrees);
        }
        else if (tokenize[i] == '/') {
            t = new typename BinaryTree<std::string>::Node("/");
            return pemdas_to_ast(tokenize.substr(0, i), t->left, subtrees) / pemdas_to_ast(tokenize.substr(i+1, tokenize.length()-i-1), t->right, subtrees);
        }
    }

    if (tokenize[0] == '[')
    {
        int i = 1;
        std::string idx_str = "";
        while (tokenize[i] != ']')
        {
            idx_str += tokenize[i];
            ++i;
        }
        if (idx_str != "")
        {
            int idx = stoi(idx_str);
            t = subtrees[idx].first;
            return subtrees[idx].second;
        }
        cout << "pass" << endl;
    }

    t = new typename BinaryTree<std::string>::Node(tokenize);
    return stod(tokenize);
}

double pemdas_to_ast(const std::string &pemdas_str, typename BinaryTree<std::string>::Node* &t) {
    vector<std::pair<typename BinaryTree<std::string>::Node*, double>> subtrees;
    return pemdas_to_ast(pemdas_str, t, subtrees);
}

////////////////////////////////////////////////////////////////
//////////////////////// Start of Tests ////////////////////////
////////////////////////////////////////////////////////////////

TEST_CASE("test_mirror", "[weight=10]"){
    vector<int> nodes;
    nodes.push_back(58); //         58
    nodes.push_back(35); //
    nodes.push_back(72); //    35        72
    nodes.push_back(10); //
    nodes.push_back(40); //  10  40    61  80
    nodes.push_back(61); //
    nodes.push_back(80); // 0 19            93
    nodes.push_back(93); //
    nodes.push_back(0); //
    nodes.push_back(19); //

    BinaryTree<int> tree;
    for(size_t i = 0; i < nodes.size(); i++)
        tree.insert(nodes[i], true);

    vector<int> beforeMirror;
    vector<int> afterMirror;

    tree.inOrder(beforeMirror);

    tree.mirror();

    tree.inOrder(afterMirror);

    assertMirror(beforeMirror, afterMirror);
}

TEST_CASE("test_isOrderedRecursive", "[weight=10]"){
    vector<int> ordering;
    ordering.resize(10);
    for(size_t i = 0; i < ordering.size(); i++)
        ordering[i] = i;
    srand( 1234 );
    random_shuffle(ordering.begin(), ordering.end());

    BinaryTree<int> tree;
    for (size_t i = 0; i < ordering.size(); i++)
        tree.insert(ordering[i]);

    REQUIRE(tree.isOrderedRecursive() == false);

    ordering.resize(12);
    for (size_t i = 0; i < ordering.size(); i++)
        ordering[i] = i;
    srand( 1234 );
    random_shuffle(ordering.begin(), ordering.end());

    BinaryTree<int> tree2;
    for (size_t i = 0; i < ordering.size(); i++)
        tree2.insert(ordering[i], true);

    REQUIRE(tree2.isOrderedRecursive() == true);
}

TEST_CASE("test_isOrderedIterative", "[weight=10]"){
    vector<int> ordering;
    ordering.resize(10);
    for(size_t i = 0; i < ordering.size(); i++)
        ordering[i] = i;
    srand( 1234 );
    random_shuffle(ordering.begin(), ordering.end());

    BinaryTree<int> tree;
    for (size_t i = 0; i < ordering.size(); i++)
        tree.insert(ordering[i]);

    REQUIRE(tree.isOrderedIterative() == false);

    ordering.resize(12);
    for (size_t i = 0; i < ordering.size(); i++)
        ordering[i] = i;
    srand( 1234 );
    random_shuffle(ordering.begin(), ordering.end());

    BinaryTree<int> tree2;
    for (size_t i = 0; i < ordering.size(); i++)
        tree2.insert(ordering[i], true);

    REQUIRE(tree2.isOrderedIterative() == true);

}

TEST_CASE("test_InorderTraversal", "[weight=10]"){
    vector<int> nodes;
    nodes.push_back(52); //         52
    nodes.push_back(39); //
    nodes.push_back(71); //    39         71
    nodes.push_back(17); //
    nodes.push_back(47); //  17   47     69   80
    nodes.push_back(69); //
    nodes.push_back(80); // 0 24             90
    nodes.push_back(90); //
    nodes.push_back(0); //
    nodes.push_back(24); //

    BinaryTree<int> tree;
    for(size_t i = 0; i < nodes.size(); i++)
        tree.insert(nodes[i], true);

    InorderTraversal<int> t(tree.getRoot());
    TreeTraversal<int>::Iterator it = t.begin();
    REQUIRE( (*it)->elem == 0  ); ++it;
    REQUIRE( (*it)->elem == 17 ); ++it;
    REQUIRE( (*it)->elem == 24 ); ++it;
    REQUIRE( (*it)->elem == 39 ); ++it;
    REQUIRE( (*it)->elem == 47 ); ++it;
    REQUIRE( (*it)->elem == 52 ); ++it;  
    REQUIRE( (*it)->elem == 69 ); ++it;
    REQUIRE( (*it)->elem == 71 ); ++it;
    REQUIRE( (*it)->elem == 80 ); ++it;  
    REQUIRE( (*it)->elem == 90 ); ++it;

}


TEST_CASE("test_getPaths", "[weight=10]"){
    vector<int> nodes;
    nodes.push_back(52); //         52
    nodes.push_back(39); //
    nodes.push_back(71); //    39         71
    nodes.push_back(17); //
    nodes.push_back(47); //  17   47     69   80
    nodes.push_back(69); //
    nodes.push_back(80); // 0 24             90
    nodes.push_back(90); //
    nodes.push_back(0); //
    nodes.push_back(24); //

    BinaryTree<int> tree;
    for(size_t i = 0; i < nodes.size(); i++)
        tree.insert(nodes[i], true);

    vector<vector<int> > treePaths;
    tree.getPaths(treePaths);

    int arr[5][4] = {{52,39,17,0},{52,39,17,24},{52,39,47,-1},{52,71,69,-1},{52,71,80,90}};

    vector<vector <int> > treePathSolution;
    for(int i=0;i<5;i++){
        vector<int> temp;
        for(int j=0; j<4; j++){
            if(arr[i][j]!=-1)
                temp.push_back(arr[i][j]);
        }
        treePathSolution.push_back(temp);
    }
    assert_path(treePathSolution, treePaths);
}


TEST_CASE("test_calcFromAST_simple", "[weight=10]"){
    std::string compute_str = "(5 + 3) * (90 - 3)";
    typename BinaryTree<std::string>::Node* root;
    double res = pemdas_to_ast(compute_str, root);

    AbstractSyntaxTree calc_tree(root);

    REQUIRE(calc_tree.eval() == res);
}

TEST_CASE("test_calcFromAST_intermediate", "[weight=10]"){
    std::string compute_str = "((28 + 69) * (45 / 3)) + (78643 - 10083 * 4)";
    typename BinaryTree<std::string>::Node* root;
    double res = pemdas_to_ast(compute_str, root);

    AbstractSyntaxTree calc_tree(root);

    REQUIRE(calc_tree.eval() == res);
}

TEST_CASE("test_calcFromAST_complex", "[weight=10]"){
    std::string compute_str = "(4 * (6 + (3 - 2) * 9 + 23)) + (1097 * (6784 / ((883 + 237) * 3))) + (70934 - (673 / (5  * (3 * 3))))";
    typename BinaryTree<std::string>::Node* root;
    double res = pemdas_to_ast(compute_str, root);

    AbstractSyntaxTree calc_tree(root);

    REQUIRE(calc_tree.eval() == res);
}

TEST_CASE("test_sumDistances", "[weight=0][extraCredit=1]"){
    vector<int> nodes;
    nodes.push_back(50); //         50
    nodes.push_back(32); //
    nodes.push_back(70); //    32        70
    nodes.push_back(10); //
    nodes.push_back(45); //  10  45    69  88
    nodes.push_back(69);
    nodes.push_back(88);

    BinaryTree<int> tree;
    for(size_t i = 0; i < nodes.size(); i++)
        tree.insert(nodes[i], true);
    REQUIRE(10 == tree.sumDistances());
}
