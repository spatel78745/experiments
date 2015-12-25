/*
 * Bst.h
 *
 *  Created on: Nov 11, 2015
 *      Author: spatel78745
 */

#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <initializer_list>
#include <functional>
#include <stdexcept>
#include "Node.h"
#include "treeplot/TreePlot.h"

using std::string;
using std::cout;
using std::cerr;
using std::max;
using std::pair;
using std::vector;
using std::initializer_list;
using std::function;
using std::out_of_range;

/*
 * Design notes:
 * Iterators:
 * - A simple implementation is to put the nodes into a vector and have begin() and end()
 *   return the begin() and end() of the vector. Unfortunately, since Bsts are mutable,
 *   the iterator will be invalidated by if someone puts a new node, uses [] to change a node,
 *   or deletes (TBD) a node.
 * - Another issue is how do you know when to delete the vector? An easy fix is for any
 *   non-const method, update the vector. Repellent yes, but good enough for now.
 *
 * Misc issues
 * - Are any of these methods thread safe? Probably all the const ones are, since const doesn't
 *   doesn't change any of the members. Prove this. And what about the case where const and
 *   non-const functions are running concurrently? And now you know the value of immutable
 *   structures from a "thread-safety" perspective.
 * - Think about coding conventions:
 *   - Should member functions have an "m" prefix?
 *
 * Deletion
 * - In English, here's what I want to do:
 *   - Let's say x is the node that I want to delete. There are 3 cases:
 *     - x has a single child:
 *       1. a left child
 *       2. a right child
 *     - x has two children
 *
 *     Design an if-statement to cover these three cases:
 *     x has one child:
 *     // x has one child
 *     if (x.left == null) return x.right // 1. a right child
 *     if (x.right == null) return x.left // 2. a left child
 *     // x has two children
 *
 *     Perhaps you're over thinking this...but Sedgewick/Wayne have come up with a construction
 *     that you've never used.
 *
 *     Now, can we say that the successor of all the nodes in x.right are bigger than succ(x)?
 *     Well, we know that all the nodes in x.right are bigger than x, that there are no other
 *     nodes between x and succ(x) i.e. we have x, succ(x), and all the rest, so all the rest
 *     have to be bigger than succ(x). Now let's set t = x, and x = succ(x). If we set x.right
 *     = deleteMin(t), then all nodes x.right are bigger then x. And we can set x.left to be
 *     t.left because succ(x) must be bigger then t.left. TODO: please refine this argument.
 *
 *     And now we cooking with gas. Some tips to reduce mental load:
 *     - don't keep too many things at once. Once you've proved a bunch of facts, accept it
 *       and prove more. Stay focused on the point of proof.
 */

// TODO: make a util.(cpp|h)
template <typename A, typename B> string pairStr(pair<A, B> p);

template<typename K, typename V>
class Bst
{
public:
    typedef Node<K, V> NodeT;
    typedef size_t size_type;
    typedef V value_type;
    typedef K key_type;
    typedef typename vector<NodeT>::iterator iterator;
    typedef typename vector<NodeT>::const_iterator const_iterator;
    typedef pair<K, V> PairT;

    Bst() :
            mRoot(nullptr)
    {
    }

    Bst(const vector<PairT> elems) : Bst()
    {
        put(elems);
    }

    Bst(initializer_list<PairT> elems) :
            Bst()
    {
        put(elems);
    }

    ~Bst()
    {
        delete mRoot;
    }

    int draw(const NodeT *x, int colStart, int colEnd, int row, TreePlot& treePlot) const
    {
        if (x == nullptr) return 0;

        int col = (colStart + colEnd) / 2; // TODO: Fix stupid overflow bug if you want
        treePlot.drawNode(row, col, x->mKey);

        if (x->mLeft != nullptr)
        {
            int childCol = draw(x->mLeft, colStart, col, row + 1, treePlot);
            treePlot.drawLeftLeg(row, col, row + 1, childCol);
        }

        if (x->mRight != nullptr)
        {
            int childCol = draw(x->mRight, col, colEnd, row + 1, treePlot);
            treePlot.drawRightLeg(row, col, row + 1, childCol);
        }

        return col;
    }

    void draw() const
    {
        TreePlot treePlot;
        draw(mRoot, 0, treePlot.cols(), 0, treePlot);
    }

    bool isTree()
    {
        bool debug = true;
        function<bool (NodeT *)> _isTree = [&_isTree, debug](NodeT *x)
        {
            if (x == nullptr) return true;

            if (x->mLeft  != nullptr && x->key() < x->mLeft->key())
            {
               if (debug)
               cerr << "tree property 'left < root' violated : " << pairStr(x->pair()) <<
                       " < " << pairStr(x->pair()) << endl;
               return false;
            }
            if (x->mRight != nullptr && x->mRight->key() < x->key())
            {
               if (debug)
               cerr << "tree property 'root < right' violated : " << pairStr(x->mRight->pair()) <<
                       " < " << pairStr(x->pair()) << endl;

               return false;
            }

           return _isTree(x->mLeft) && _isTree(x->mRight);
        };

        return _isTree(mRoot);
    }

    PairT deleteMin()
    {
        PairT deleted;
        bool debug = false;

        function<NodeT* (NodeT *)> _deleteMin = [&_deleteMin, &deleted, &debug](NodeT *x)
        {
            if (x->mLeft == nullptr)
            {
                deleted.first = x->mKey;
                deleted.second = x->mVal;

                cerr << "deleteMin(): deleted (" << deleted.first << ", " << deleted.second << ")" << endl;
                return x->mRight;
            }

            x->mLeft = _deleteMin(x->mLeft);

            return x;
        };

        if (mRoot == nullptr)
        {
            throw out_of_range("tree is empty");
        }

        /*
         * Big bug caught by the test: the result wasn't assigned to mRoot. If the minimum element
         * is the root, then _deleteMin returns the right subtree, but mRoot wasn't updated.
         */
        mRoot = _deleteMin(mRoot);

        return deleted;
    }

    iterator begin()
    {
        return mIterVec.begin();
    }

    /*
     * NB: If this isn't a const member, then the compiler complains that it conflicts with
     * the non-const version because you can't overload functions based on return-type.
     *
     */
    const_iterator begin() const
    {
        return mIterVec.begin();
    }

    iterator end()
    {
        return mIterVec.end();
    }

    const_iterator end() const
    {
        return mIterVec.end();
    }

    /*
     * TODO: Another more serious issue: if the user changes a node, the tree might not be a BST
     * anymore. Just out of curiosity, how could the user mess it up? There are a couple of
     * possibilities:
     * - If the node is the parent of a left child and is made smaller then this child
     * - If the node is the parent of a right child and is made larger then this child
     * - If the node is the left child of the parent and it's made larger then the parent
     * - If the node is the right child of the parent and it's made smaller then the parent
     *
     * We could fix this by deleting the node and putting it in.
     *
     * Disable it for now...re-enabled because I can use it to test isTree.
     */
    NodeT& operator[](K key)
    {
        NodeT *node = get(mRoot, key);

        return (node == nullptr) ? NodeT::null() : *node;
    }

    /*
     * TODO: How do I fix this code duplication? A lambda?
     * Another idea here is to hide NodeT from client code and return pairT
     */
    const NodeT& operator[](K key) const
    {
        NodeT *node = get(mRoot, key);

        return (node == nullptr) ? NodeT::null() : *node;
    }

    template <typename T>
    void put(T elems)
    {
        for (pair<K, V> p : elems)
        {
            put(p.first, p.second);
        }
    }

    void put(const K key, const V val)
    {
        NodeT *node = new NodeT(key, val);
        mRoot = put(mRoot, node);

    }

    size_type size() const
    {
        return size(mRoot);
    }

    size_type height() const
    {
        return height(mRoot);
    }

    void print() const
    {
        cerr << "size: " << size() << endl;
        cerr << "height: " << height() << endl;
        print(mRoot);
        cerr << endl;
    }

    vector<K> keys() const
    {
        vector<K> ks;

        keys(mRoot, ks);

        return ks;
    }

    NodeT& floor(K key) const
    {
        NodeT *_floor = floor(mRoot, key);
        if (_floor == nullptr)
        {
            return NodeT::null();
        }

        return *_floor;
    }

    void inOrder(vector<PairT>& res) const
    {
        inOrder(mRoot, res);
    }

    PairT min()
    {
        if (mRoot == nullptr)
        {
            throw out_of_range("tree is empty");
        }

        return minNode(mRoot)->pair();
    }

private:
    NodeT *minNode(const NodeT *x) const
    {
        if (x->mLeft == nullptr)
        {
            return x;
        }

        return minNode(x->mLeft);
    }

    void inOrder(const NodeT *x, vector<PairT>& res) const
    {
        static const bool debug = false;

        if (x == nullptr)
        {
            return;
        }

        inOrder(x->mLeft, res);

        if (debug)
        {
            cerr << "about to push_back: " << x->key() << ", " << x->val() << endl;
        }

        res.push_back(PairT(x->key(), x->val()));

        if (debug)
        {
            cerr << "push_back complete: " << x->key() << ", " << x->val() << " size " << res.size() << endl;
        }

        inOrder(x->mRight, res);
    }

    /*
     * Returns the largest key in the tree that's less then the parameter "key"
     *
     * The naive algorithm is:
     * - If the tree is empty, the floor is undefined, therefore return
     *   NodeT::null()
     * - Make a list of the keys in the tree and sort them ascending order
     * - For each key in the list
     *   - If the key is bigger than the parameter "key, " then by definition
     *     it can't be the floor, so continue.
     *   - If the key is less, then return it.
     * - If we're here, all the keys were bigger then "key" so return null
     *
     * By now you should be used to thinking about the floor, so let's proceed
     * with the recursive implementation. The basic idea is this:
     *
     * For any node x:
     * - If (x == nullptr) then the floor is undefined, so return nullptr
     * - If (x->key > "key") then it can't be the floor. If there is a floor, it
     *   must be in the left subtree, so return the floor of the left subtree.
     * - If (x->key == "key") then it's the floor, so return it
     * - If (x->key < "key") then it might be the floor. However, the right
     *   sub-tree contains keys that bigger then x->key. Some of them may
     *   also be less then "key", so the floor may be in the right subtree.
     *   So compute the floor of the right subtree, and call it FRS. If FRS
     *   is null, then the floor must be x->key. If FRS is bigger than x->key
     *   then it must be the floor, so return it. Otherwise, the only
     *   remaining possibility is that the floor is the x->key.
     *
     *   Oh my god....
     */
    NodeT *floor(NodeT *x, K key) const
    {
        /*
         * First, the easy case. If the tree is empty, then the floor is
         * undefined, so return nullptr in this case.
         */
        if (x == nullptr)
        {
            return nullptr;
        }

        /*
         * The next easiest case (for me to understand) is if x->key is
         * larger then key. If this is true, then x->key can't be floor(key)
         * because, by definition, floor(key) <= key. If there is a floor(key),
         * it must be in the left sub-tree, so return floor(x->left, key)
         */
        if (key < x->key())
        {
            return floor(x->mLeft, key);
        }

        /*
         * And now for the trickiest case. If x->key is less then key, it may
         * be floor(key). But the right sub-tree contains keys that are larger
         * then x->key. Some of them may also be less than key, so the floor
         * may be in the right subtree. So:
         * - If floor(x->right)
         *   - is nullptr, then either the right subtree is empty, or all the
         *     keys are larger then key. So the floor must be x->key, so
         *     return it.
         *   - if larger or equal, then x->key, then it must be the floor, so return
         *     floor(x->right).
         */
        NodeT *frs = floor(x->mRight, key);

        if (frs == nullptr)
        {
            return x;
        }

        if (x->key() < frs->key())
        {
            return frs;
        }

        return x;
    }

    void keys(NodeT *x, vector<K>& ks) const
    {
        if (x != nullptr)
        {
            ks.push_back(x->mKey);

            keys(x->mLeft, ks);
            keys(x->mRight, ks);
        }
    }

    size_type size(NodeT *x) const
    {
        if (x == nullptr)
        {
            return 0;
        }
        else
        {
            return x->mSize;
        }
    }

    size_type height(NodeT *x) const
    {
        if (x == nullptr)
        {
            return 0;
        }

        return max(1 + height(x->mLeft), 1 + height(x->mRight));
    }

    NodeT *get(NodeT *x, K key) const
    {
        if (x == nullptr)
        {
            return nullptr;
        }

        if (key < x->mKey)
        {
            return get(x->mLeft, key);
        }

        if (x->mKey < key)
        {
            return get(x->mRight, key);
        }

        return x;
    }

    NodeT *put(NodeT *x, NodeT *node)
    {
        bool debug = false;

        std::string parentKey =
                ((x == nullptr || x->mParent == nullptr) ? "null" : x->mParent->mKey);

        if (x == nullptr)
        {
            if (debug)
                std::cerr << "Inserting " << node->mKey << " " << parentKey << "\n";

            return node;
        }

        if (*node < *x)
        {
            if (debug)
                std::cerr << "Going left from " << x->mKey << " to insert " << node->mKey
                        << " parent " << parentKey << "\n";
            x->mLeft = put(x->mLeft, node);
            x->mLeft->mParent = x;
        }
        else if (*x < *node)
        {
            if (debug)
                std::cerr << "Going right from " << x->mKey << " to insert " << node->mKey
                        << " parent " << parentKey << "\n";
            x->mRight = put(x->mRight, node);
            x->mRight->mParent = x;
        }
        else
        {
            if (debug)
                std::cout << "Replacing value in " << node->mKey << "\n";
            x->mVal = node->mVal;
        }

        x->mSize = size(x->mRight) + size(x->mLeft) + 1;

        return x;
    }

    void print(NodeT *x) const
    {
        if (x == nullptr)
        {
            return;
        }

        string parentKey = ((x->mParent == nullptr) ? "null" : x->mParent->mKey);

        cerr << x->mKey << "/" << parentKey << "/" << size(x) << " ";
        print(x->mLeft);
        print(x->mRight);
    }

    /*
     * The root of the BST
     */
    NodeT *mRoot;

    vector<NodeT> mIterVec;

};

#endif /* BST_H_ */
