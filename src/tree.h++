#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <random>
#include <type_traits>
#include <list>
#include <thread>


using namespace std;


namespace tree {

    template <typename Type>
    class TreeNode {
        public:
        TreeNode() : parent(NULL), data{}, nodeID(0) {} //For head node
        TreeNode(size_t newNodeID, Type &newData, TreeNode *newParent) : parent(newParent), data(newData), nodeID(newNodeID) {}

        list<TreeNode<Type>> derivedNodes;
        TreeNode<Type> *parent;
        Type data;
        size_t nodeID;
    };

    template <typename Type>
    class Tree {
        public:
        Tree() {
            Type dummy{};
            head = TreeNode<Type>(0, dummy, nullptr);
            IDtoNode[0] = &head;
            traverseCurrent = &head;
        }

        TreeNode<Type>* get_root() {
            return &head;
        }

        void add_node(size_t nodeIDParent, size_t newNodeID, Type &newData) {
            TreeNode<Type> *parent = IDtoNode[nodeIDParent];

            parent->derivedNodes.emplace_front(newNodeID, newData, parent);
            IDtoNode[newNodeID] = &parent->derivedNodes.front();
            return;
        }

        void delete_node(size_t nodeID) {
            TreeNode<Type> *current = IDtoNode[nodeID];
            TreeNode<Type> *parent = current->parent;

            if(traverseCurrent->nodeID == current->nodeID) {
                traverseCurrent = &head;
            }
            
            size_t numChildren = current->derivedNodes.size();
            //Add the child nodes to the parent from the current
            parent->derivedNodes.splice(parent->derivedNodes.end(), current->derivedNodes);

            //Delete the child node from the parent list
            for (auto it = parent->derivedNodes.begin(); it != parent->derivedNodes.end(); ++it) {
                if (it->nodeID == current->nodeID) {
                    parent->derivedNodes.erase(it);
                    current = NULL;
                    break;
                }
            }

            //Update the hashmap
            IDtoNode.erase(nodeID);

            auto rit = parent->derivedNodes.rbegin();
            for (size_t i = 0; i < numChildren; ++i, ++rit) {
                IDtoNode[rit->nodeID] = &(*rit);
                rit->parent = parent;
            }
            return;
        }

        vector<Type> peak(size_t nodeID) {
            TreeNode<Type> *current = IDtoNode[nodeID];

            vector<Type> ret;
            for(TreeNode<Type> item : current->derivedNodes) {
                ret.emplace_back(item.data);
            }
            return ret;
        }

        void traverse(size_t nodeID, size_t directionIndex) { //0 to go up, 1,2,3,... to move from left to right
            if(directionIndex == 0) {
                traverseCurrent = traverseCurrent->parent;
            } else {
                auto it = traverseCurrent->derivedNodes.begin();
                advance(it, directionIndex - 1);
                traverseCurrent = &(*it);
            }
            return;
        }
        

        private:
        unordered_map<size_t, TreeNode<Type>*> IDtoNode;
        TreeNode<Type> head; //Head has ID of 0
        TreeNode<Type> *traverseCurrent; //Current traversed
    };
}









#endif