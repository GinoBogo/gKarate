/*!
 * =============================================================================
 *
 *   @file: gXmlNode.cpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#include "gXmlNode.hpp"

#include <qforeach.h>

gXmlNode::gXmlNode(gXmlNode* parent) {
    this->parent = parent;

    if (parent != nullptr) {
        parent->children.append(this);
    }
}

gXmlNode::~gXmlNode() {
    clear();
}

void gXmlNode::clear() {
    name.clear();
    text.clear();
    attributes.clear();

    foreach (gXmlNode* child, children) {
        if (child != nullptr) {
            child->~gXmlNode();
        }
    }
}
