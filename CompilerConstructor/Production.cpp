#include "Production.hpp"

// ProdNode
ProdNode::ProdNode(std::string ID) {
    this->ID = ID;
}

std::string ProdNode::GetID() {
    return ID;
}
std::string ProdNode::GetType() {
    return type;
}

// Production
Production::Production() {
    rule = new std::list<ProdNode*>();
}

void Production::SetHead(ProdNode* head) {
    this->head = head;
}

void Production::AppendToRule(ProdNode* prodNode) {
    rule->push_back(prodNode);
}

ProdNode* Production::GetHead() {
    return head;
}

std::list<ProdNode*>* Production::GetRule() {
    return rule;
}
